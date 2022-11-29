#include "StdAfx.h"
#include "common.h"
#include "C3dsFile.h"
#include "MyArray.h"



#pragma pack(push, 1)

#define	PRIMARY				0x4D4D
#define FILE_VERSION		0x0002
#define	MAINOBJECT			0x3D3D
#define	EDITKEYFRAME		0xB000
#define	MATERIAL			0xAFFF
#define	OBJECT				0x4000
#define	OBJECT_MESH			0x4100
#define	OBJECT_VERTICES		0x4110
#define	OBJECT_FACES		0x4120
#define	OBJECT_MATERIAL		0x4130
#define	MATNAME				0xA000
#define MAT_AMBIENT			0xa010
#define MAT_DIFFUSE			0xa020
#define MAT_SPECULAR		0xa030
#define MAT_SHININESS		0xa040
#define MAT_TRANSPARENCY	0xa050
#define INT_PERCENTAGE		0x0030
#define FLOAT_PERCENTAGE	0x0031
#define COLOR_F		0x0010
#define COLOR_24	0x0011

#define	MAX_NAME_LEN	256


typedef struct tagS3DS_CHUNK 
{ 
	WORD	ID; 
	DWORD	Len; 
}S3DS_CHUNK, *P3DS_CHUNK;

typedef struct tagS3DS_FACE
{
	int		nIndex[3];
	int		nMatPos;
}S3DS_FACE, *P3DS_FACE;

typedef struct tagS3DS_MATERIAL
{ 
	char	szName[MAX_NAME_LEN]; 
	float	ambientColor[3]; 
	float	diffuseColor[3]; 
	float	specularColor[3]; 
	float	emissiveColor[3]; 
	float	shininess;		//0~1
	float	transparency; 
}S3DS_MATERIAL, *P3DS_MATERIAL;

typedef struct tagS3DS_OBJECT
{
	char	szName[MAX_NAME_LEN];
	int		nStartFace;	//Start Face Index
	int		nFaceCount;	//Face Count
	int		nStartVert;	//Start Vertex Index for Faces
	int		nVertCount;	//Vertex Count
}S3DS_OBJECT, *P3DS_OBJECT;


CMyArray<S3DS_OBJECT>	g_arr3dsObjs;
CMyArray<S3DS_MATERIAL>	g_arr3dsMats;
CMyArray<S3DS_FACE>		g_arr3dsFaces;
CMyArray<VECTOR3>		g_arr3dsVerts;

//3DS File Data Variables
LPBYTE		g_pFileData	 = NULL;
DWORD		g_dwFileSize = 0;
DWORD		g_dwCurPos	 = 0;


BOOL  M3ds_FileReadChunk(HANDLE hFile, P3DS_CHUNK pChunk);
BOOL  M3ds_MemReadChunk(P3DS_CHUNK pChunk);
DWORD M3ds_MemReadData(void* pBuf, DWORD dwSize);
DWORD M3ds_MemReadString(char* pBuffer, DWORD dwMaxLen);
void  M3ds_MemSkipBytes(DWORD nBytes);

BOOL  M3ds_NewModelBuffers(int nObjects, int nMaterials, int nFaces, int nVerts);
void  M3ds_FreeModelBuffers();
BOOL  M3ds_LoadObject(DWORD dwLen);
BOOL  M3ds_LoadMaterial(DWORD dwLen);

BOOL C3dsFile::IsModelFile(LPCTSTR lpszFilePath)
{
	BOOL	bIsType = FALSE;
	DWORD	dwSize = 0;
	HANDLE	hFile;
	S3DS_CHUNK	chkHdr;

	if (lpszFilePath == NULL || lpszFilePath[0] == 0)
		return FALSE;

	hFile = ::CreateFile(lpszFilePath, GENERIC_READ, FILE_SHARE_READ, NULL,
								OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE;

	//Read File and Header Check
	M3ds_FileReadChunk(hFile, &chkHdr);
	dwSize = SetFilePointer(hFile, 0, NULL, FILE_END);
	if (chkHdr.ID == PRIMARY && chkHdr.Len <= dwSize)
		bIsType = TRUE;

	//Close File
	::CloseHandle(hFile);
	return bIsType;
}


C3dsFile::C3dsFile(void)
{
	memset(&m_StrComMesh, 0, sizeof(COM_MESH));
}


C3dsFile::~C3dsFile(void)
{
	Close();
}

BOOL C3dsFile::Open(LPCTSTR lpszFilePath, COM_MESH* pComMesh)
{
	if (lpszFilePath == NULL || lpszFilePath[0] == 0 || pComMesh == NULL)
		return FALSE;

	BOOL	bSuccess = FALSE;
	DWORD	dwSize, dwRead;
	HANDLE	hFile;
	S3DS_CHUNK	sChunk;

	hFile = ::CreateFile(lpszFilePath, GENERIC_READ, FILE_SHARE_READ, NULL,
								OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE;

	dwSize = ::SetFilePointer(hFile, 0, NULL, FILE_END);
	g_pFileData = (LPBYTE) calloc(dwSize + 16, 1);
	if (g_pFileData == NULL)
	{
		::CloseHandle(hFile);
		return FALSE;
	}

	//Read All Data From File
	::SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
	::ReadFile(hFile, g_pFileData, (DWORD) dwSize, &dwRead, NULL);
	//Close File
	::CloseHandle(hFile);

	//Read Size Check
	if ((DWORD) dwSize != dwRead)
		dwSize = (long) dwRead;
	g_pFileData[dwSize] = 0;

	//Start Analyzing
	//---Allocate New MyFace Buffers
	if (!NewComMeshBuffer(1024, 65536 * 3, 65536))
		return FALSE;
	//---Read header Chunk and Get File Data Length
	g_dwCurPos	 = 0;
	g_dwFileSize = dwSize;
	if (M3ds_MemReadChunk(&sChunk))
		g_dwFileSize = sChunk.Len;
	//---Read Chunks and Get Models
	bSuccess = TRUE;
	while (g_dwCurPos < dwSize)
	{
		if (!M3ds_MemReadChunk(&sChunk))
			break;
		if (MAINOBJECT == sChunk.ID)
			bSuccess &= LoadModel(sChunk.Len);
		else 
			M3ds_MemSkipBytes(sChunk.Len - sizeof(S3DS_CHUNK));
	}

	//Free 3DS Model Buffers
	M3ds_FreeModelBuffers();

	//Copy Array Data to COM_MESH struct
	if (bSuccess)
	{
		m_StrComMesh.intObjectCount	= g_arrComObjs.GetCount();
		m_StrComMesh.pObjects		= g_arrComObjs.Copy();
		m_StrComMesh.intFaceCount	= (int) (g_arrComFaces.GetCount() / 3);
		m_StrComMesh.pIndices		= g_arrComFaces.Copy();
		m_StrComMesh.intVertexCount	= g_arrComVerts.GetCount();
		m_StrComMesh.pVertices		= g_arrComVerts.Copy();

		MyGetNormals(&m_StrComMesh);
		InitMesh(&m_StrComMesh);
		memcpy(pComMesh, &m_StrComMesh, sizeof(COM_MESH));
	}

	//return success flag
	return bSuccess;
}

BOOL C3dsFile::LoadModel(DWORD dwLen)
{
	BOOL	bSuccess = FALSE;
	DWORD	dwBeginPos = 0;
	S3DS_CHUNK	sChunk;

	//Initialize 3DS Model Buffers
	if (!M3ds_NewModelBuffers(1024, 8192, 65536 * 3, 65536))
		return FALSE;

	//Get Objects from File
	dwBeginPos = g_dwCurPos - sizeof(S3DS_CHUNK);
	while ((g_dwCurPos - dwBeginPos) < dwLen)
	{
		M3ds_MemReadChunk(&sChunk);
		switch( sChunk.ID ) 
		{ 
		case OBJECT: 
			M3ds_LoadObject(sChunk.Len);
			break; 
		case MATERIAL: 
			M3ds_LoadMaterial(sChunk.Len);
			break; 
		default: 
			M3ds_MemSkipBytes(sChunk.Len - sizeof(S3DS_CHUNK));
		}
	}

	return ConstructingComMesh();
}

BOOL C3dsFile::ConstructingComMesh()
{
	P3DS_OBJECT		p3dsObj;
	P3DS_FACE		p3dsFace;
	VECTOR3*		p3dsVert;
	P3DS_MATERIAL	p3dsMat;
	CMyArray<int>	cMatUse;

	COM_OBJECT	sComObj;
	COM_VERTEX	sComVert;
	int		pnComFace[3];		//COM_MESH Face Index Values
	int		k, m, i, nCount;	//Loop Variables
	int		nObjects;			//3DS Object Count
	int		*pnMatUse;			//Material Use Index Array Pointer
	

	//Copy All Vertexes of This Model
	p3dsVert = g_arr3dsVerts.GetItem(0);
	nCount	 = g_arr3dsVerts.GetCount();
	for (k = 0; k < nCount; k++, p3dsVert++)
	{
		//---Copy Coordinates
		memcpy(&(sComVert.vertex), p3dsVert, sizeof(VECTOR3));
		sComVert.vec3Normal.x = sComVert.vec3Normal.y = sComVert.vec3Normal.z = 0.0f;
		sComVert.colorRGB.r = sComVert.colorRGB.g = sComVert.colorRGB.b = 0.0f;
		sComVert.intMaterialId = 0;
		//---Add
		g_arrComVerts.AddItem(&sComVert, 1);
	}

	//Copy Data of Objects
	p3dsObj	 = g_arr3dsObjs.GetItem(0);
	nObjects = g_arr3dsObjs.GetCount();
	cMatUse.Create(128, 16);
	for (k = 0; k < nObjects; k++, p3dsObj++)
	{
		//Initialize Material Use Index Table
		cMatUse.Clear();
		//---Get Material Use Array
		p3dsFace = g_arr3dsFaces.GetItem(p3dsObj->nStartFace);
		for (m = 0; m < p3dsObj->nFaceCount; m++, p3dsFace++)
		{
			if (!cMatUse.IsExist(&(p3dsFace->nMatPos)))
				cMatUse.AddItem(&(p3dsFace->nMatPos));
		}
		//---Add COM_MESH Objects by Material Use Array
		nCount	= cMatUse.GetCount();
		pnMatUse= cMatUse.GetItem(0);
		for (i = 0; i < nCount; i++, pnMatUse++)
		{
			//Init COM_MESH Object Data
			//+++Set Face Start Index and Count
			sComObj.nStartFace	= (int) (g_arrComFaces.GetCount() / 3);	//3 integers make 1 item
			sComObj.nFaceCount	= 0;
			//+++Material Setting
			for (m = 0; m < 3; m++)
			{
				sComObj.strMat.matAmbient[m] = 0.5f;
				sComObj.strMat.matDiffuse[m] = 0.5f;
				sComObj.strMat.matSpecular[m]= 0.5f;
				sComObj.strMat.matEmission[m]= 0.5f;
			}
			sComObj.strMat.matAmbient[3] = 1.0f;
			sComObj.strMat.matDiffuse[3] = 1.0f;
			sComObj.strMat.matSpecular[3]= 1.0f;
			sComObj.strMat.matEmission[3]= 1.0f;
			sComObj.strMat.fShininess	 = 96.0f;
			if (*pnMatUse > 0)
			{
				p3dsMat = g_arr3dsMats.GetItem(*pnMatUse - 1);
				for (m = 0; m < 3; m++)
				{
					sComObj.strMat.matAmbient[m] = p3dsMat->ambientColor[m];
					sComObj.strMat.matDiffuse[m] = p3dsMat->diffuseColor[m];
					sComObj.strMat.matSpecular[m]= p3dsMat->specularColor[m];
					sComObj.strMat.matEmission[m]= p3dsMat->emissiveColor[m];
				}
				sComObj.strMat.fShininess = p3dsMat->shininess * 128.0f;
			}

			//Add Faces for this COM_MESH Object
			p3dsFace = g_arr3dsFaces.GetItem(p3dsObj->nStartFace);
			for (m = 0; m < p3dsObj->nFaceCount; m++, p3dsFace++)
			{
				if (*pnMatUse == p3dsFace->nMatPos)
				{
					pnComFace[0] = p3dsObj->nStartVert + p3dsFace->nIndex[0];
					pnComFace[1] = p3dsObj->nStartVert + p3dsFace->nIndex[1];
					pnComFace[2] = p3dsObj->nStartVert + p3dsFace->nIndex[2];
					g_arrComFaces.AddItem(pnComFace, 3);
				}
			}
			//Add COM_MESH Object
			sComObj.nFaceCount = (int) (g_arrComFaces.GetCount() / 3) - sComObj.nStartFace;
			g_arrComObjs.AddItem(&sComObj, 1);
		}
	}

	cMatUse.Release();

	return TRUE;
}

void C3dsFile::Close()
{
	FreeComMeshBuffer();
	M3ds_FreeModelBuffers();
}

PCOM_MESH C3dsFile::GetMesh()
{
	return (&m_StrComMesh);
}

BOOL C3dsFile::NewComMeshBuffer(int nObjects, int nFaces, int nVerts)
{
	int		nNew = 0;
	BOOL	bSuccess = TRUE;

	bSuccess &= g_arrComObjs.Create(nObjects, 16);
	bSuccess &= g_arrComFaces.Create(nFaces, 256);
	bSuccess &= g_arrComVerts.Create(nVerts, 256);

	return bSuccess;
}

void C3dsFile::FreeComMeshBuffer()
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


BOOL  M3ds_FileReadChunk(HANDLE hFile, P3DS_CHUNK pChunk)
{
	DWORD	dwRead = 0;

	if (hFile == INVALID_HANDLE_VALUE || pChunk == NULL)
		return FALSE;

	if (!ReadFile(hFile, pChunk, sizeof(S3DS_CHUNK), &dwRead, NULL) || dwRead < sizeof(S3DS_CHUNK))
		return FALSE;

	return TRUE;
}

BOOL  M3ds_MemReadChunk(P3DS_CHUNK pChunk)
{
	if (pChunk == NULL)
		return FALSE;
	if ((g_dwCurPos + sizeof(S3DS_CHUNK)) > g_dwFileSize)
		return FALSE;

	memcpy(pChunk, g_pFileData + g_dwCurPos, sizeof(S3DS_CHUNK));
	g_dwCurPos += sizeof(S3DS_CHUNK);

	return TRUE;
}

DWORD M3ds_MemReadString(char* pBuffer, DWORD dwMaxLen)
{
	char	*pDst, *pSrc;
	DWORD	dwLen = 0;

	if (pBuffer == NULL || dwMaxLen < 1)
		return 0;

	pDst = pBuffer;
	pSrc = (char*) g_pFileData + g_dwCurPos;
	while (*pSrc)
	{
		if (dwLen < dwMaxLen)
		{
			*pDst = *pSrc;
			pDst++;
		}
		pSrc++; g_dwCurPos++;
		dwLen++;
	}
	*pDst = 0;

	//for Last Zero Byte
	g_dwCurPos++; dwLen++;
	return dwLen;
}

DWORD M3ds_MemReadData(void* pBuf, DWORD dwSize)
{
	if (pBuf == NULL || (long) dwSize < 1)
		return 0;

	if ((g_dwCurPos + dwSize) > g_dwFileSize)
		dwSize = g_dwFileSize - g_dwCurPos;

	memcpy(pBuf, g_pFileData + g_dwCurPos, dwSize);
	g_dwCurPos += dwSize;
	return dwSize;
}

void  M3ds_MemSkipBytes(DWORD nBytes)
{
	g_dwCurPos += nBytes;
}

BOOL  M3ds_NewModelBuffers(int nObjects, int nMaterials, int nFaces, int nVerts)
{
	BOOL bSuccess = TRUE;

	bSuccess &= g_arr3dsObjs.Create(nObjects, 16);
	bSuccess &= g_arr3dsMats.Create(nMaterials, 32);
	bSuccess &= g_arr3dsFaces.Create(nFaces, 256);
	bSuccess &= g_arr3dsVerts.Create(nVerts, 256);

	return bSuccess;
}

void  M3ds_FreeModelBuffers()
{
	g_arr3dsObjs.Release();
	g_arr3dsMats.Release();
	g_arr3dsFaces.Release();
	g_arr3dsVerts.Release();

	if (g_pFileData)
	{
		free(g_pFileData);
		g_pFileData = NULL;
	}
	g_dwFileSize = g_dwCurPos = 0;
}


BOOL  M3ds_LoadVertices(P3DS_OBJECT pObject)
{
	int			nCount;
	WORD		wTemp;
	VECTOR3		sVertex;

	if (pObject == NULL)
		return FALSE;

	//Read Count
	M3ds_MemReadData(&wTemp, 2);	//sizeof WORD
	nCount	= (int) wTemp;

	//Set Object Start Vertex Index (That is, size of current Vertex array count before adding new vertices)
	pObject->nStartVert	= g_arr3dsVerts.GetCount();

	//Add Vertexes
	for (int k = 0; k < nCount; k++)
	{
		M3ds_MemReadData(&sVertex, sizeof(VECTOR3));
		sVertex.z *= -1.0;	//Because 3DS Coordinate System differs OpenGL
		g_arr3dsVerts.AddItem(&sVertex, 1);
	}

	//Set Object Vertex Count
	pObject->nVertCount	= g_arr3dsVerts.GetCount() - pObject->nStartVert;

	return TRUE;
}

BOOL  M3ds_LoadFaces(P3DS_OBJECT pObject)
{
	int		nCount;
	WORD	wIndex[4];
	S3DS_FACE	sFace;

	if (pObject == NULL)
		return FALSE;

	//Read Count
	M3ds_MemReadData(&wIndex[0], 2);	//sizeof WORD
	nCount = (int) wIndex[0];

	//Set Object Start Face Index (That is, size of current Face array count before adding new vertices)
	pObject->nStartFace	= g_arr3dsFaces.GetCount();

	//Add Faces
	for (int k = 0; k < nCount; k++)
	{
		M3ds_MemReadData(wIndex, sizeof(WORD) * 4);
		for (int m = 0; m < 3; m++)
			sFace.nIndex[m] = (int) wIndex[m];
		sFace.nMatPos = 0;
		g_arr3dsFaces.AddItem(&sFace, 1);
	}
	//Add Model Face Count
	pObject->nFaceCount =  g_arr3dsFaces.GetCount() - pObject->nStartFace;

	return TRUE;
}

BOOL  M3ds_LoadObjectMats(P3DS_OBJECT pObject)
{
	char	szName[MAX_NAME_LEN];
	WORD	wFacePos;
	int		nCount, k, nMatPos;
	P3DS_FACE		pStartFace;
	P3DS_MATERIAL	pMat;

	if (pObject == NULL)
		return FALSE;

	//Get Material Index from Name
	M3ds_MemReadString(szName, MAX_NAME_LEN - 1);
	pMat	= g_arr3dsMats.GetItem(0);
	nCount	= g_arr3dsMats.GetCount();
	for (k = 0, nMatPos = 0; k < nCount; k++, pMat++)
	{
		if (strcmp(pMat->szName, szName) == 0)
			nMatPos = k + 1;
	}

	//---Set Material Index to faces
	pStartFace = g_arr3dsFaces.GetItem(pObject->nStartFace);
	M3ds_MemReadData(&wFacePos, 2);
	nCount = (int) wFacePos;
	for (k = 0; k < nCount; k++)
	{
		M3ds_MemReadData(&wFacePos, 2);
		pStartFace[wFacePos].nMatPos = nMatPos;
	}

	return TRUE;
}


BOOL  M3ds_LoadMesh(DWORD dwLen)
{
	DWORD		dwBeginPos = 0;
	S3DS_CHUNK	sChunk;
	P3DS_OBJECT	pObject = NULL;

	pObject		= g_arr3dsObjs.GetLast(); //Last Object
	dwBeginPos	= g_dwCurPos - sizeof(S3DS_CHUNK);
	while ((g_dwCurPos - dwBeginPos) < dwLen)
	{
		M3ds_MemReadChunk(&sChunk);
		switch (sChunk.ID)
		{
		case OBJECT_VERTICES:
			M3ds_LoadVertices(pObject);
			break;
		case OBJECT_FACES:
			M3ds_LoadFaces(pObject);
			break;
		case OBJECT_MATERIAL:
			M3ds_LoadObjectMats(pObject); 
			break;
		default:
			M3ds_MemSkipBytes(sChunk.Len - sizeof(S3DS_CHUNK)); 
		}
	}

	return TRUE;
}

BOOL  M3ds_LoadObject(DWORD dwLen)
{
	DWORD		dwBeginPos = 0;
	S3DS_CHUNK	sChunk;
	S3DS_OBJECT	sObject;

	//Initialize Object
	memset(sObject.szName, 0, MAX_NAME_LEN);
	sObject.nStartFace	= g_arr3dsFaces.GetCount();
	sObject.nStartVert	= g_arr3dsVerts.GetCount();
	sObject.nFaceCount	= 0;
	sObject.nVertCount	= 0;
	g_arr3dsObjs.AddItem(&sObject);

	//Read Object Name
	dwBeginPos	= g_dwCurPos - sizeof(S3DS_CHUNK);
	M3ds_MemReadString(sObject.szName, MAX_NAME_LEN - 1);
	//Read Chunk for mesh info
	while ((g_dwCurPos - dwBeginPos) < dwLen)
	{
		M3ds_MemReadChunk(&sChunk);
		if (sChunk.ID == OBJECT_MESH)
			M3ds_LoadMesh(sChunk.Len);
		else
			M3ds_MemSkipBytes(sChunk.Len - sizeof(S3DS_CHUNK));
	}

	return TRUE;
}

void  M3ds_LoadColor(float* color)
{ 
	S3DS_CHUNK	sChunk;
	BYTE		pData[4] = {0,};

	M3ds_MemReadChunk(&sChunk);
	switch(sChunk.ID)
	{ 
	case COLOR_F: 
		M3ds_MemReadData(color, 3 * sizeof(float));
		break; 
	case COLOR_24:
		M3ds_MemReadData(pData, 3);
		for (int x = 0; x < 3; x++) 
			color[x] = (float) pData[x] / 255.0f;
		break;
	default:
		M3ds_MemSkipBytes(sChunk.Len - sizeof(S3DS_CHUNK));
	}
}

void  M3ds_LoadPercent(float* pfValue) 
{
	S3DS_CHUNK	sChunk;
	WORD		wValue;

	if (pfValue == NULL)
		return;

	M3ds_MemReadChunk(&sChunk);
	switch( sChunk.ID ) 
	{
	case INT_PERCENTAGE:
		wValue = 0;
		M3ds_MemReadData(&wValue, 2);	//size of USHORT
		*pfValue = (float) wValue / 100.0f;
		break; 
	case FLOAT_PERCENTAGE:
		M3ds_MemReadData(pfValue, 4);	//size of FLOAT
		break; 
	default:
		M3ds_MemSkipBytes(sChunk.Len - sizeof(S3DS_CHUNK));
	}
}

BOOL  M3ds_LoadMaterial(DWORD dwLen)
{
	DWORD			dwBeginPos;
	S3DS_CHUNK		sChunk;
	S3DS_MATERIAL	sMaterial;

	memset(&sMaterial, 0, sizeof(S3DS_MATERIAL));
	dwBeginPos	= g_dwCurPos - sizeof(S3DS_CHUNK);
	while ((g_dwCurPos - dwBeginPos) < dwLen)
	{
		M3ds_MemReadChunk(&sChunk);
		switch(sChunk.ID) 
		{ 
		case MATNAME:
			M3ds_MemReadString(sMaterial.szName, MAX_NAME_LEN - 1);
			break;
		case MAT_AMBIENT:
			M3ds_LoadColor(sMaterial.ambientColor);
			break;
		case MAT_DIFFUSE:
			M3ds_LoadColor(sMaterial.diffuseColor);
			break;
		case MAT_SPECULAR:
			M3ds_LoadColor(sMaterial.specularColor);
			break;
		case MAT_SHININESS:
			M3ds_LoadPercent(&(sMaterial.shininess));
			break;
		case MAT_TRANSPARENCY:
			M3ds_LoadPercent((&sMaterial.transparency));
			break;
		default: 
			M3ds_MemSkipBytes(sChunk.Len - sizeof(S3DS_CHUNK));
		}
	}
	g_arr3dsMats.AddItem(&sMaterial, 1);

	return TRUE;
}


#pragma pack(pop)