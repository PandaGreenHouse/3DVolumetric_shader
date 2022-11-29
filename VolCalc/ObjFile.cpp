#include "StdAfx.h"
#include "ObjFile.h"
#include "common.h"
#include "MyArray.h"



typedef struct tagOBJ_FACE
{
	int		nVertexIdx[3];
	int		nNormalIdx[3];
	int		nTextureIdx[3];
}OBJ_FACE, *POBJ_FACE;

typedef struct tagOBJ_TEXCOORD
{
	float u, v;
	int		index;
}OBJ_TEXCOORD, *POBJ_TEXCOORD;

typedef struct tagOBJ_MATERIAL
{
	char	szName[256];
	char	map_Kd[256];
	int		illum;	//0. Color on and Ambient off
			//1. Color on and Ambient on
			//2. Highlight on
			//3. Reflection on and Ray trace on
			//4. Transparency: Glass on, Reflection: Ray trace on
			//5. Reflection: Fresnel on and Ray trace on
			//6. Transparency: Refraction on, Reflection: Fresnel off and Ray trace on
			//7. Transparency: Refraction on, Reflection: Fresnel on and Ray trace on
			//8. Reflection on and Ray trace off
			//9. Transparency: Glass on, Reflection: Ray trace off
			//10. Casts shadows onto invisible surfaces
	float	Ns;		//Specular Highlight
	float	Ni;
	float	Ka[3];	//Ambient
	float	Kd[3];	//Diffuse
	float	Ks[3];	//Specular
	float	Tf[3];	//
}OBJ_MATERIAL, *POBJ_MATERIAL;

TCHAR	g_szModelDir[1024];
int		g_nModelDirLen = 0;


CMyArray<OBJ_FACE>		g_arrObjFaces;
CMyArray<VECTOR3>		g_arrObjVerts;
CMyArray<VECTOR3>		g_arrObjNorms;
CMyArray<OBJ_MATERIAL>	g_arrObjMats;
int		g_nCurMatIndex = -1;	//-1 Means No Material is mapped for Last COM_MESH Object


BOOL  OBJ_AddDefaultObject(int nStartFace);
BOOL  OBJ_NewMeshBuffer(int nFaces, int nVerts, int nNorms, int nMats);
void  OBJ_FreeMeshBuffer();
BOOL  OBJ_ReadObjects(char* pData, DWORD dwSize);
void  OBJ_GetFaceInfo(char* pData);
void  OBJ_GetVertexInfo(BOOL bNormal, char* pData);
char* OBJ_GetString(char* pData);
void  OBJ_LoadMaterialLibrary(char* pData);
void  OBJ_SetCurrentMaterial(char* pData);



BOOL CObjFile::IsModelFile(LPCTSTR lpszFilePath)
{
	char	szTemplate[5][32] = {"mtllib", "usemtl", "vt ", "vn ", "f " };
	char	*pData = NULL, *pFound, *pComment, *pLineEnd, *pCur;
	DWORD	dwSize = 0, dwRead = 0;	
	HANDLE	hFile;

	if (lpszFilePath == NULL || lpszFilePath[0] == 0)
		return FALSE;

	hFile = ::CreateFile(lpszFilePath, GENERIC_READ, FILE_SHARE_READ, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE;

	dwSize = ::SetFilePointer(hFile, 0, NULL, FILE_END);
	pData = (char*) calloc(dwSize + 16, 1);
	if (pData == NULL)
	{
		::CloseHandle(hFile);
		return FALSE;
	}

	//Read All Data From File
	::SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
	::ReadFile(hFile, pData, (DWORD) dwSize, &dwRead, NULL);
	//Close File
	::CloseHandle(hFile);

	//Read Size Check
	if ((DWORD) dwSize != dwRead)
		dwSize = (long) dwRead;
	pData[dwSize] = 0;

	//Check File Type
	for (dwRead = 0; dwRead < 5; dwRead++)
	{
		pCur = pData;
		while (1)
		{
			//Find Template
			pFound	= strstr(pCur, szTemplate[dwRead]);
			if (pFound == NULL)
				break;
			//Find Line End before Template
			*pFound	 = 0;
			pLineEnd = strrchr(pCur, '\n');
			//Find Comment Symbol between Line End and Template
			pComment = strchr(pLineEnd, '#');
			//Reset First Char of Found String
			*pFound = szTemplate[dwRead][0];
			//If Comment Symbol Not Found, the Found Template string is valid
			if (pComment == NULL)
			{
				*pFound = szTemplate[dwRead][0];
				break;
			}
			//Prepare for Next Loop
			pCur = pFound + strlen(szTemplate[dwRead]) + 1;
		}
		if (pFound != NULL)
			break;
	}

	//Free File Data
	free(pData);

	return (dwRead < 5);
}

CObjFile::CObjFile(void)
{
	memset(&m_StrComMesh, 0, sizeof(COM_MESH));
}

CObjFile::~CObjFile(void)
{
	Close();
}

BOOL CObjFile::Open(LPCTSTR lpszFilePath, COM_MESH* pComMesh)
{
	if (lpszFilePath == NULL || lpszFilePath[0] == 0 || pComMesh == NULL)
		return FALSE;

	char*	pData;
	BOOL	bSuccess = FALSE;
	DWORD	dwSize, dwRead;
	LPTSTR	pFind;
	HANDLE	hFile;

	//Get Model Directory Path
	_tcscpy(g_szModelDir, lpszFilePath);
	pFind = _tcsrchr(g_szModelDir, '\\');
	if (pFind == NULL)
		pFind = _tcsrchr(g_szModelDir, '/');
	if (pFind == NULL)
		pFind = g_szModelDir;
	else
		pFind++;
	*pFind = 0;
	g_nModelDirLen = pFind - g_szModelDir;

	//Open File
	hFile = ::CreateFile(lpszFilePath, GENERIC_READ, FILE_SHARE_READ, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE;

	//Get File Size and Allocate Buffer
	dwSize	= ::SetFilePointer(hFile, 0, NULL, FILE_END);
	pData	= (char*) calloc(dwSize + 16, 1);
	if (pData == NULL)
	{
		::CloseHandle(hFile);
		return FALSE;
	}

	//Read All Data From File
	::SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
	::ReadFile(hFile, pData, dwSize, &dwRead, NULL);
	//Close File
	::CloseHandle(hFile);

	//Read Size Check
	if (dwSize != dwRead)
		dwSize = dwRead;
	pData[dwSize] = 0;

	//Read Object and Make COM_MESH Data
	//---Allocate New MyFace Buffers
	if (!NewComMeshBuffer(1024, 65536 * 3, 65536))
		return FALSE;

	OBJ_AddDefaultObject(0);
	g_nCurMatIndex = -1;
	//---Read Object Data
	bSuccess = OBJ_ReadObjects(pData, dwSize);
	if (bSuccess)
	{
		bSuccess = ConstructingComMesh();
		if (bSuccess)
			memcpy(pComMesh, &m_StrComMesh, sizeof(COM_MESH));
	}

	free(pData);

	return bSuccess;
}

BOOL CObjFile::NewComMeshBuffer(int nObjects, int nFaces, int nVerts)
{
	int		nNew = 0;
	BOOL	bSuccess = TRUE;

	bSuccess &= g_arrComObjs.Create(nObjects, 16);
	bSuccess &= g_arrComFaces.Create(nFaces, 256);
	bSuccess &= g_arrComVerts.Create(nVerts, 256);

	return bSuccess;
}

void CObjFile::FreeComMeshBuffer()
{
	g_arrComObjs.Release();
	g_arrComFaces.Release();
	g_arrComVerts.Release();

	if (m_StrComMesh.pObjects)
		free(m_StrComMesh.pObjects);
	if (m_StrComMesh.pVertices)
		free(m_StrComMesh.pVertices);
	if (m_StrComMesh.pIndices)
		free(m_StrComMesh.pIndices);
	memset(&m_StrComMesh, 0, sizeof(COM_MESH));
}

BOOL CObjFile::ConstructingComMesh()
{
	int x, k;	//Loop Variable
	int	nFaces, nVerts; //Face and Vertex Count
	int pIndex[3] = {0};
	COM_VERTEX	sDstVert;
	POBJ_FACE	pSrcFace;
	VECTOR3		*pSrcVert, *pSrcNorm;

	nFaces = g_arrObjFaces.GetCount();
	nVerts = g_arrObjVerts.GetCount();
	if (nFaces < 1 || nVerts < 1)
		return FALSE;

	pSrcFace = g_arrObjFaces.GetItem(0);
	pSrcVert = g_arrObjVerts.GetItem(0);
	for (x = 0; x < nFaces; x++)
	{
		for (k = 0; k < 3; k++)
		{
			memset(&sDstVert, 0, sizeof(COM_VERTEX));
			memcpy(&(sDstVert.vertex), (pSrcVert + pSrcFace->nVertexIdx[k]), sizeof(VECTOR3));
			sDstVert.colorRGB.r = sDstVert.colorRGB.g = sDstVert.colorRGB.b = 1.0f;
			if (g_arrObjNorms.GetCount() > 0)
			{
				pSrcNorm = g_arrObjNorms.GetItem(pSrcFace->nNormalIdx[k]);
				memcpy(&(sDstVert.vec3Normal), pSrcNorm, sizeof(VECTOR3));
			}
			sDstVert.intMaterialId = 0;
			g_arrComVerts.AddItem(&sDstVert, 1);
			pIndex[k] = x * 3 + k;
		}
		pSrcFace++;
		g_arrComFaces.AddItem(pIndex, 3);
	}

	//Free Obj Mesh Data
	OBJ_FreeMeshBuffer();

	m_StrComMesh.pObjects		= g_arrComObjs.Copy();
	m_StrComMesh.intObjectCount	= g_arrComObjs.GetCount();
	m_StrComMesh.pIndices		= g_arrComFaces.Copy();
	m_StrComMesh.intFaceCount	= (int) (g_arrComFaces.GetCount() / 3);
	m_StrComMesh.pVertices		= g_arrComVerts.Copy();
	m_StrComMesh.intVertexCount	= g_arrComVerts.GetCount();

	InitMesh(&m_StrComMesh);
	//If no normal for vertex, calculate Default Normal
	if (g_arrObjNorms.GetCount() < 1)
		MyGetNormals(&m_StrComMesh);

	return TRUE;
}

void CObjFile::Close()
{
	FreeComMeshBuffer();
	OBJ_FreeMeshBuffer();
}

PCOM_MESH CObjFile::GetMesh()
{
	return (&m_StrComMesh);
}



BOOL OBJ_NewMeshBuffer(int nFaces, int nVerts, int nNorms, int nMats)
{
	BOOL bSuccess = TRUE;

	bSuccess &= g_arrObjFaces.Create(nFaces, 256);
	bSuccess &= g_arrObjVerts.Create(nVerts, 256);
	bSuccess &= g_arrObjNorms.Create(nNorms, 256);
	bSuccess &= g_arrObjMats.Create(nMats, 64);

	return bSuccess;
}

void OBJ_FreeMeshBuffer()
{
	g_arrObjFaces.Release();
	g_arrObjVerts.Release();
	g_arrObjNorms.Release();
	g_arrObjMats.Release();
}

BOOL OBJ_ReadObjects(char* pData, DWORD dwSize)
{
	char	*pLineStart, *pLineEnd, *pCurPos, *pEndData;

	if (pData == NULL || (long) dwSize < 1)
		return FALSE;

	if (!OBJ_NewMeshBuffer(65536 * 3, 65536, 65536, 8192))
		return FALSE;

	pEndData = pData + dwSize;
	pCurPos	 = pData;
	pLineStart	= pData;
	while (pLineStart < pEndData)
	{
		//Get End of Line
		pLineEnd = strchr(pLineStart, '\n');
		if (pLineEnd == NULL)
			pLineEnd = strchr(pLineStart, '\r');
		if ((pLineEnd == NULL) && (*pLineStart != 0))
			pLineEnd = pEndData;
		//Mark End of Line as String End
		*pLineEnd = 0;
		pCurPos = pLineStart;
		while (pCurPos < pLineEnd)
		{
			if (*pCurPos == '#' || ((*pCurPos >= 'a') && (*pCurPos <= 'z')) ||
				((*pCurPos >= 'A') && (*pCurPos <= 'Z')))
				break;
			pCurPos++;
		}
		if (strncmp(pCurPos, "f", 1) == 0)
		{
			OBJ_GetFaceInfo(pCurPos + 1);
		} else if (strncmp(pCurPos, "vn ", 2) == 0)
		{
			OBJ_GetVertexInfo(TRUE, pCurPos + 2);
		} else if (strncmp(pCurPos, "v", 1) == 0)
		{
			OBJ_GetVertexInfo(FALSE, pCurPos + 1);
		} else if (strncmp(pCurPos, "mtllib", 6) == 0)
		{
			OBJ_LoadMaterialLibrary(pCurPos + 6);
		} else if (strncmp(pCurPos, "usemtl", 6) == 0)
		{
			OBJ_SetCurrentMaterial(pData + 6);
		}

		pLineStart = pLineEnd + 1;
	}

	return (g_arrObjFaces.GetCount() > 0);
}

BOOL OBJ_AddDefaultObject(int nStartFace)
{
	int	k;
	COM_OBJECT	sObject;

	//Set Start Face and Face Count
	sObject.nStartFace	= nStartFace;
	sObject.nFaceCount	= 0;
	//Set Color Info
	sObject.strMat.fShininess = 96.0f;
	for (k = 0; k < 3; k++)
	{
		sObject.strMat.matAmbient[k] = 0.5f;
		sObject.strMat.matDiffuse[k] = 0.5f;
		sObject.strMat.matSpecular[k]= 0.5f;
		sObject.strMat.matEmission[k]= 0.5f;
	}
	sObject.strMat.matAmbient[3] = 1.0f;
	sObject.strMat.matDiffuse[3] = 1.0f;
	sObject.strMat.matSpecular[3]= 1.0f;
	sObject.strMat.matEmission[3]= 1.0f;
	g_arrComObjs.AddItem(&sObject, 1);

	return TRUE;
}

int  OBJ_ParseInts(char* pData, CMyArray<int>* pArray, int* pnFieldCnt)
{
	int nCount, nValue, nFieldCnt = 1;
	BOOL		bFieldCountSet = FALSE;

	if (pData == NULL || pData[0] == 0 || pArray == NULL)
		return 0;

	//Loop until a digit occurred
	while (*pData < '0' || *pData > '9')
		pData++;

	//Parse Integers
	nCount = 0;
	nValue = 0;
	while (*pData)
	{
		if (*pData < '0' || *pData > '9')
		{
			pArray->AddItem(&nValue, 1);
			nValue = 0;
			nCount++;
			switch (*pData)
			{
			case '/':
				if (!bFieldCountSet)
					nFieldCnt++;
				break;
			default:
				if (!bFieldCountSet)
					bFieldCountSet = TRUE;
				break;
			}
			while (*pData != 0 && (*pData < '0' || *pData > '9'))
				pData++;
		} else
		{
			nValue = nValue * 10 + (int) (*pData - '0');
			pData++;
		}
	}
	//Reaches End of String
	if (nValue)
	{
		pArray->AddItem(&nValue, 1);
		nCount++;
	}

	if (pnFieldCnt)
		*pnFieldCnt = nFieldCnt;

	return pArray->GetCount();
}

void OBJ_GetFaceInfo(char* pData)
{
	int	*pnFieldAddr[3], pnStartIdx[3];
	int	nCount, nFieldCnt = 0;
	int k, m, i, n;
	OBJ_FACE	sFace = {{0}, };
	POBJ_FACE	pLast = NULL;
	COM_OBJECT	*pOldObj = NULL;
	CMyArray<int>	arrIndex;

	if (pData == NULL || *pData == 0)
		return;

	//Get Last COM_MESH Object
	pOldObj = g_arrComObjs.GetLast();
	//Create Index Value Array
	if (!arrIndex.Create(128, 16))
		return;
	//Parse Integers and Get Count
	nCount = OBJ_ParseInts(pData, &arrIndex, &nFieldCnt);
	if (nCount < 3)
		return;

	//Add New Faces
	nCount = (int) (nCount / nFieldCnt) - 2;
	for (k = 0; k < nCount; k++)
	{
		//---Field Array Pointers
		pnFieldAddr[0] = sFace.nVertexIdx;
		pnFieldAddr[1] = sFace.nTextureIdx;
		pnFieldAddr[2] = sFace.nNormalIdx;
		//---Index Start Value of Each Field
		pnStartIdx[0] = 0;
		pnStartIdx[1] = (k + 1) * nFieldCnt;
		pnStartIdx[2] = (k + 2) * nFieldCnt;
		//---Set Field Values of 3 Point of this Face
		for (i = 0; i < 3; i++)
		{
			n = pnStartIdx[i];
			for (m = 0; m < nFieldCnt; m++, n++)
				(pnFieldAddr[m])[i] = *(arrIndex.GetItem(n)) - 1;
		}
		//---Add to Face Array
		g_arrObjFaces.AddItem(&sFace, 1);
	}
	//Set COM_MESH Object Face Count
	pOldObj->nFaceCount = g_arrObjFaces.GetCount() - pOldObj->nStartFace;

	arrIndex.Release();
}

void OBJ_GetVertexInfo(BOOL bNormal, char* pData)
{
	VECTOR3 sVert = {0};
	int		nCount;

	//Loop until a float meet
	while (*pData)
	{
		if (*pData == '-' || *pData == '.' || 
			((*pData >= '0') && (*pData <= '9')))
			break;
		pData++;
	}

	nCount = sscanf(pData, "%f %f %f", &(sVert.x), &(sVert.y), &(sVert.z));
	if (nCount < 3)
		return;

	if (bNormal)
		g_arrObjNorms.AddItem(&sVert, 1);
	else
		g_arrObjVerts.AddItem(&sVert, 1);
}

char* OBJ_GetString(char* pData)
{
	char* pEnd = NULL;

	//---Find First Char of Material Library File Name
	while (*pData)
	{
		if ((*pData != ' ') && (*pData != '\t'))
			break;
		pData++;
	}
	//---Find Last Char of Material Library File Name
	pEnd = pData + 1;
	while (*pEnd)
	{
		if ((*pEnd == ' ') || (*pEnd == '\t') ||
			(*pEnd == '\n') || (*pEnd == '\r'))
			break;
		pEnd++;
	}
	*pEnd = 0;

	return pData;
}

BOOL OBJ_MtlReadMats(char* pData, DWORD dwSize)
{
	char		 *pLineStart, *pLineEnd, *pCurPos, *pEndData;
	OBJ_MATERIAL sEmpty, *pMatInfo;

	if (pData == NULL || (long) dwSize < 1)
		return FALSE;

	memset(&sEmpty, 0, sizeof(OBJ_MATERIAL));
	pEndData = pData + dwSize;
	pCurPos	 = pData;
	pLineStart	= pData;
	while (pLineStart < pEndData)
	{
		//Get End of Line
		pLineEnd = strchr(pLineStart, '\n');
		if (pLineEnd == NULL)
			pLineEnd = strchr(pLineStart, '\r');
		if ((pLineEnd == NULL) && (*pLineStart != 0))
			pLineEnd = pEndData;
		//Mark End of Line as String End
		*pLineEnd = 0;
		//Find First English Letter or Digit
		pCurPos = pLineStart;
		while (pCurPos < pLineEnd)
		{
			if (*pCurPos == '#' || ((*pCurPos >= 'a') && (*pCurPos <= 'z')) ||
				((*pCurPos >= 'A') && (*pCurPos <= 'Z')))
				break;
			pCurPos++;
		}
		//Compare strings and Get Values
		if (strncmp(pCurPos, "newmtl", 6) == 0)
		{
			strcpy(sEmpty.szName, OBJ_GetString(pCurPos + 6));
			g_arrObjMats.AddItem(&sEmpty, 1);
			pMatInfo = g_arrObjMats.GetLast();
		} else if (strncmp(pCurPos, "map_Kd", 6) == 0)
		{
			pCurPos = OBJ_GetString(pCurPos + 6);
			strcpy(pMatInfo->map_Kd, pCurPos);
		} else if (strncmp(pCurPos, "illum", 5) == 0)
		{
			sscanf(pCurPos + 5, " %d", &(pMatInfo->illum));
		} else if (strncmp(pCurPos, "Ns", 2) == 0)
		{
			sscanf(pCurPos + 2, "%f", &(pMatInfo->Ns));
		} else if (strncmp(pCurPos, "Ni", 2) == 0)
		{
			sscanf(pCurPos + 2, "%f", &(pMatInfo->Ni));
		} else if (strncmp(pCurPos, "Ka", 2) == 0)
		{
			sscanf(pCurPos + 2, "%f %f %f", &(pMatInfo->Ka[0]), &(pMatInfo->Ka[1]), &(pMatInfo->Ka[2]));
		} else if (strncmp(pCurPos, "Kd", 2) == 0)
		{
			sscanf(pCurPos + 2, "%f %f %f", &(pMatInfo->Kd[0]), &(pMatInfo->Kd[1]), &(pMatInfo->Kd[2]));
		} else if (strncmp(pCurPos, "Ks", 2) == 0)
		{
			sscanf(pCurPos + 2, "%f %f %f", &(pMatInfo->Ks[0]), &(pMatInfo->Ks[1]), &(pMatInfo->Ks[2]));
		} else if (strncmp(pCurPos, "Tf", 2) == 0)
		{
			sscanf(pCurPos + 2, "%f %f %f", &(pMatInfo->Tf[0]), &(pMatInfo->Tf[1]), &(pMatInfo->Tf[2]));
		}
		//Process The Next Line
		pLineStart = pLineEnd + 1;
	}

	return (g_arrObjFaces.GetCount() > 0);
}

void OBJ_LoadMaterialLibrary(char* pData)
{
	int		nLen;
	DWORD	dwRead, dwSize;
	LPTSTR	lpszPath;
	HANDLE	hFile;

	//Get MatLib file path in TCHAR
	//---Get String Path in CHAR
	pData = OBJ_GetString(pData);
	//---Convert File Path
	lpszPath= g_szModelDir + g_nModelDirLen;
	nLen	= strlen(pData);
#ifdef _UNICODE
	MultiByteToWideChar(CP_ACP, 0, (LPCSTR) pData, nLen, lpszPath, nLen);
	lpszPath[nLen] = 0;
#else
	_tcscpy(lpszPath, pData);
#endif

	//File Open
	hFile = CreateFile(g_szModelDir, GENERIC_READ, FILE_SHARE_READ, NULL,
							OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
			return;

	//Get File Size and Allocate Buffer
	dwSize	= ::SetFilePointer(hFile, 0, NULL, FILE_END);
	pData	= (char*) calloc(dwSize + 16, 1);
	if (pData == NULL)
	{
		::CloseHandle(hFile);
			return;
	}

	//Read All Data From File
	::SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
	::ReadFile(hFile, pData, dwSize, &dwRead, NULL);
	//Close File
	::CloseHandle(hFile);

	//Read Size Check
	if (dwSize != dwRead)
		dwSize = dwRead;
	pData[dwSize] = 0;

	OBJ_MtlReadMats(pData, dwSize);

	//Free File Data
	free(pData);

	//Model Dir Path Restore
	g_szModelDir[g_nModelDirLen] = 0;
}

void OBJ_SetCurrentMaterial(char* pData)
{
	PCOM_OBJECT		pObject;
	POBJ_MATERIAL	pCurMat;
	int		nMatCnt, k;

	//Get Material Name
	pData = OBJ_GetString(pData);

	//Find Material by name
	pCurMat	= g_arrObjMats.GetItem(0);
	nMatCnt	= g_arrObjMats.GetCount();
	for (k = 0; k < nMatCnt; k++, pCurMat++)
	{
		if (strcmp(pCurMat->szName, pData) == 0)
			break;
	}

	if (k >= nMatCnt)
		return;

	//Get Last COM_MESH Object
	pObject	= g_arrComObjs.GetLast();
	if (g_nCurMatIndex >= 0 && g_nCurMatIndex != k)
	{
		OBJ_AddDefaultObject((int) (g_arrComFaces.GetCount() / 3));
		pObject = g_arrComObjs.GetLast();
	}

	g_nCurMatIndex = k;
	pObject->strMat.fShininess = 96.0f;	//******Ns: Specular Highlight
	memcpy(pObject->strMat.matAmbient, pCurMat->Ka, 3 * sizeof(float));
	memcpy(pObject->strMat.matDiffuse, pCurMat->Kd, 3 * sizeof(float));
	memcpy(pObject->strMat.matSpecular, pCurMat->Ks, 3 * sizeof(float));
	memset(pObject->strMat.matEmission, 0, 3 * sizeof(float));
}