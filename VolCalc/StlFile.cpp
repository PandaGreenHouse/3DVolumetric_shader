#include "stdafx.h"
#include "StlFile.h"
#include "common.h"
#include "MyArray.h"

#define		STL_UNKNOWN			0
#define		STL_BINARY_FILE		1
#define		STL_STRING_FILE		2


struct STL_FILE_HEADER
{
	char	name[80];
};

struct STL_FILE_FACE
{
	VECTOR3	vecNormal;
	VECTOR3	vertices[3];
	UINT16	intAttribute;
};

CMyArray<STL_FILE_FACE>	g_arrStlFaces;

//Variables for Sort
CMyArray<int>	g_arrVertsIdx;	//Vertex Index Array where vertexes are sorted in Decrease Order
PCOM_VERTEX		g_pSortVerts = NULL;


BOOL Stl_OpenBinary(LPBYTE pData);
BOOL Stl_OpenString(LPBYTE pData, int nDataSize, char* lpszModelStart, char* lpszModelEnd);
BOOL Stl_ReadVertex(char* pStr, VECTOR3* pVec);

int  Stl_CheckType(LPBYTE pData, DWORD dwSize)
{
	char	szAvailChars[80] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 _.-+\n\r\t"; //Available Chars in String mode
	char	szTemplate[6][32] = {"solid", "facet", "vertex", "normal", "end", "loop" };
	char*	pStr;
	UINT32	nFaces, x, y, nChars;

	//Check String of Header and First Face
	nFaces	= sizeof(STL_FILE_HEADER) + sizeof(STL_FILE_FACE);
	nChars	= (UINT32) strlen(szAvailChars);
	pStr	= (char*) pData;
	for (x = 0; x < nFaces; x++, pStr++)
	{
		for (y = 0; y < nChars; y++)
		{
			if (*pStr == szAvailChars[y])
				break;
		}
		if (y >= nChars)
			break;
	}
	
	if (x < nFaces)
	{ //Binary or Unknown Mode
	memcpy(&nFaces, pData + sizeof(STL_FILE_HEADER), sizeof(UINT32));

	dwSize = (dwSize - sizeof(STL_FILE_HEADER) - sizeof(UINT32)) / sizeof(STL_FILE_FACE);
		if (nFaces <= (UINT32) dwSize)
		return STL_BINARY_FILE;
	} else
	{ //Check for String Mode
	for (x = 0, y = 0; x < 6; x++)
	{
		if (strstr((char*) pData, szTemplate[x]))
			y++;
	}

	if (y >= 6)
		return STL_STRING_FILE;
	}

	//Unknown Mode
	return STL_UNKNOWN;
}

BOOL CStlFile::IsModelFile(LPCTSTR lpszFilePath)
{
	BOOL	bIsType = FALSE;
	DWORD	dwSize;
	DWORD	dwRead = 0;
	LPBYTE	pData = NULL;
	HANDLE	hFile;

	if (lpszFilePath == NULL || lpszFilePath[0] == 0)
		return FALSE;

	hFile = ::CreateFile(lpszFilePath, GENERIC_READ, FILE_SHARE_READ, NULL,
								OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE;

	dwSize = ::SetFilePointer(hFile, 0, NULL, FILE_END);
	pData = (LPBYTE) calloc(dwSize + 16, 1);
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

	bIsType = (Stl_CheckType(pData, dwSize) != STL_UNKNOWN);
	free(pData);

	return bIsType;
}

CStlFile::CStlFile(void)
{
	memset(&m_StrComMesh, 0, sizeof(COM_MESH));
}


CStlFile::~CStlFile(void)
{
	Close();
}

BOOL CStlFile::Open(LPCTSTR lpszFilePath, COM_MESH* pComMesh)
{
	if (lpszFilePath == NULL || lpszFilePath[0] == 0 || pComMesh == NULL)
		return FALSE;

	BOOL	bSuccess = FALSE;
	DWORD	dwSize, dwRead;
	LPBYTE	pData;
	HANDLE	hFile;

	hFile = ::CreateFile(lpszFilePath, GENERIC_READ, FILE_SHARE_READ, NULL,
								OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE;

	dwSize	= ::SetFilePointer(hFile, 0, NULL, FILE_END);
	pData	= (LPBYTE) calloc(dwSize + 16, 1);
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

	//Initialize Arrays
	g_arrStlFaces.Clear();
	g_arrStlFaces.Create(65536, 256);

	//Binary, String mode Check
	switch (Stl_CheckType(pData, dwSize))
	{
	case STL_BINARY_FILE:
		bSuccess = Stl_OpenBinary(pData);
		break;
	case STL_STRING_FILE:
		bSuccess = Stl_OpenString(pData, (int) dwSize, "solid", "endsolid");
		break;
	case STL_UNKNOWN:
		bSuccess = FALSE;
		break;
	}

	//Free Temp memory
	free(pData);
	
	//Convert into Common Mesh
	//---Init Arrays
	dwSize = (DWORD) g_arrStlFaces.GetCount() + 16;
	g_arrComVerts.Clear();
	g_arrComFaces.Clear();
	g_arrVertsIdx.Clear();
	g_arrComFaces.Create((int) dwSize * 3, 192);
	g_arrComVerts.Create((int) dwSize, 64);
	g_arrVertsIdx.Create((int) dwSize, 64);
	//---Convert
	if(bSuccess)
	{
		bSuccess = ConstructingComMesh();
		if (bSuccess)
			memcpy(pComMesh, &m_StrComMesh, sizeof(COM_MESH));
	}

	//return success flag
	return bSuccess;
}

BOOL Stl_OpenBinary(LPBYTE pData)
{
	LPBYTE	pTemp;
	int		nCount = 0;

	pTemp = pData + sizeof(STL_FILE_HEADER);
	memcpy(&nCount, pTemp, sizeof(UINT32));

	pTemp	+= sizeof(UINT32);
	g_arrStlFaces.AddItem((STL_FILE_FACE*) pTemp, nCount);

	return TRUE;
}

BOOL Stl_OpenString(LPBYTE pData, int nDataSize, char* lpszModelStart, char* lpszModelEnd)
{
	char	*pModelStart, *pModelEnd;
	char	*pFaceStart, *pFaceEnd;
	char	*pVertex;	//, *pLoopStart, *pLoopEnd;
	STL_FILE_FACE	sCurFace;
	int		nLen, x;

	//Get Model Start and End Position
	/* pModelStart	= strstr((char*) pData, lpszModelStart);
	pModelEnd	= (char*) pData + nDataSize - 1;
	nLen = strlen(lpszModelEnd);
	while (1)
	{
		if (*pModelEnd == lpszModelEnd[0])
		{
			if (strncmp(pModelEnd, lpszModelEnd, nLen) == 0)
				break;
		}
		pModelEnd--;
	} */

	//Read Faces and Get Count
	pModelStart	= (char*) pData;
	pModelEnd	= pModelStart + nDataSize;
	pFaceStart	= pModelStart;
	while (pFaceStart < pModelEnd)
	{
		//Get Face Start and End Position
		pFaceStart	= strstr(pFaceStart, "facet");
		if (pFaceStart == NULL)
			break;
		pFaceEnd	= strstr(pFaceStart, "endfacet");
		if (pFaceEnd == NULL)
			break;

		//Get Face Data
		//---Normal Vertex
		pVertex = strstr(pFaceStart, "normal");
		if ((pVertex == NULL) || (pVertex >= pFaceEnd))
			break;
		if (!Stl_ReadVertex(pVertex+6, &(sCurFace.vecNormal)))
			break;
		//---Vertexes in Loop
		/*
		pLoopStart	= strstr(pVertex, "loop");
		pLoopEnd	= strstr(pVertex, "endloop");
		if ((pLoopStart == NULL || pLoopEnd == NULL) ||
			(pLoopStart >= pFaceEnd || pLoopEnd >= pFaceEnd))
			break;
		pVertex = pLoopStart + 4;
		x = 0;
		do
		{
			pVertex = strstr(pVertex, "vertex");
			if (pVertex == NULL || pVertex >= pLoopEnd)
				break;
			if (Stl_ReadVertex(pVertex + 6, &(sCurFace.vertices[x])))
				x++;
			if (x >= 3)
				break;
			pVertex += 6;
		} while (1); */

		//---Get Vertices in the face
		pVertex = pFaceStart; x = 0;
		do
		{
			//Find Vertex Start Pointer
			pVertex = strstr(pVertex, "vertex");
			if (pVertex == NULL)
				break;
			//Read Vertex Data of the Face
			if (Stl_ReadVertex(pVertex + 6, &(sCurFace.vertices[x])))
				x++;
			if (x >= 3)
				break;
			//Find for Next Vertex
			pVertex += 6;
		} while (1);

		if (x >= 3)
		{ //Read one Face Successfully
			g_arrStlFaces.AddItem(&sCurFace);
			memset(&sCurFace, 0, sizeof(STL_FILE_FACE));
		}

		//Set Next Position
		pFaceStart = pFaceEnd + 8;
	}

	return (g_arrStlFaces.GetCount() > 0);
}


BOOL Stl_ReadVertex(char* pStr, VECTOR3* pVec)
{
	char* ptr;
	BOOL bResult = TRUE;

	if (pStr == NULL || pStr[0] == 0 || pVec == NULL)
		return FALSE;

	ptr = pStr;
	while (1)
	{
		if (*ptr != ' ')
			break;
		ptr++;
	}

	bResult = (sscanf(ptr, "%f %f %f", &(pVec->x), &(pVec->y), &(pVec->z)) == 3);
	if (!bResult)
		bResult = (sscanf(ptr, "%g %g %g", &(pVec->x), &(pVec->y), &(pVec->z)) == 3);
	if (!bResult)
		bResult = (sscanf(ptr, "%e %e %e", &(pVec->x), &(pVec->y), &(pVec->z)) == 3);

	return bResult;
}

void CStlFile::Close()
{
	//Common Mesh Data
	if (m_StrComMesh.pObjects)
		free(m_StrComMesh.pObjects);
	if (m_StrComMesh.pVertices)
		free(m_StrComMesh.pVertices);
	if (m_StrComMesh.pIndices)
		free(m_StrComMesh.pIndices);
	memset(&m_StrComMesh, 0, sizeof(COM_MESH));
}

PCOM_MESH CStlFile::GetMesh()
{
	return (&m_StrComMesh);
}

typedef int  (*LPCOMPARE_FUNC_PTR)(int, int);



int  Stl_SortVertex(int nNewIdx, LPCOMPARE_FUNC_PTR pFunc)
{
	int	 nResult = -1, a, b, c;	//Index of g_arrVertsIdx array
	int	 d1, d2;	//Compare Result 1, 2

	if (nNewIdx < 0 || pFunc == NULL)
		return -1;
	if (g_arrVertsIdx.GetCount() < 1)
	{
		g_arrVertsIdx.AddItem(&nNewIdx, 1);
		return 0;
	}

	a = 0; b = g_arrVertsIdx.GetCount() - 1;
	nResult = -1;
	do
	{
		c = (a + b) >> 1;
		switch (pFunc(g_arrVertsIdx[c], nNewIdx))
		{
		case  0:
			nResult = c;
			break;
		case  1:	//Vertex at c is larger than Vertex at nNewIdx
			a = c;	//search in range [c, b]
			break;
		case -1:	//Vertex at c is smaller than Vertex at nNewIdx
			b = c;	//search in range [a, c]
			break;
		}
		if (nResult >= 0)
			break;
	} while ((b - a) > 1);

	//Still, Not Found. Difference between a and b is less than 1
	if (nResult < 0)
	{
		d1 = pFunc(g_arrVertsIdx[a], nNewIdx);
		d2 = pFunc(g_arrVertsIdx[b], nNewIdx);
		if (d1 == 0)
			nResult = a;
		else if (d2 == 0)
			nResult = b;
		else if (d1 < 0) //Vertex at <a> is smaller than Vertex at nNewIdx, Add at <a> of Index Array
		{
			g_arrVertsIdx.AddAt(a, &nNewIdx, 1);
			nResult = a;
		} else if ((d1 > 0) && (d2 < 0)) //Vertex at <a> is larger, Vertex at <b> is smaller than Vertex at nNewIdx, Add at <b> of Index Array
		{
			g_arrVertsIdx.AddAt(b, &nNewIdx, 1);
			nResult = b;
		} else if (d2 > 0) //Vertex at <b> is larger than Vertex at nNewIdx, Add at <b> of Index Array
		{
			g_arrVertsIdx.AddAt(b + 1, &nNewIdx, 1);
			nResult = b + 1;
		}
	}

	nResult = g_arrVertsIdx[nResult];
	return nResult;
}


int  Stl_CompareVertex(int a, int b)
{
	PCOM_VERTEX	pt1, pt2;

	pt1 = g_pSortVerts + a;
	pt2 = g_pSortVerts + b;

	//Z Check
	if (pt1->vertex.z > pt2->vertex.z)
		return 1;
	else if (pt1->vertex.z < pt2->vertex.z)
		return -1;
	//Z Same, Y Check
	if (pt1->vertex.y > pt2->vertex.y)
		return 1;
	else if (pt1->vertex.y < pt2->vertex.y)
		return -1;
	//Z and Y Same, X Check
	if (pt1->vertex.x > pt2->vertex.x)
		return 1;
	else if (pt1->vertex.x < pt2->vertex.x)
		return -1;
	//X, Y, Z All Same
	return 0;
}

BOOL CStlFile::ConstructingComMesh()
{
	int		k, m, nVertIdx, nCount;		//Loop Variables
	int		pFaceIdx[3];		//Vertex and Face Index Count
	STL_FILE_FACE*	pSrcFace;	
	COM_VERTEX		sComVert;
	VECTOR3*		pSrcVert;

	if (g_arrStlFaces.GetCount() < 1)
		return FALSE;

	//Set Object and Face Count
	m_StrComMesh.intObjectCount = 1;
	m_StrComMesh.intFaceCount	= g_arrStlFaces.GetCount();

	//Allocate Memory for Objects, Vertexes and Faces
	m_StrComMesh.pObjects	= (PCOM_OBJECT) calloc(1, sizeof(COM_OBJECT));
	if (m_StrComMesh.pObjects == NULL)
		return FALSE;

	//Copy Vertexes and Face Indices
	//---Init Variables
	pSrcFace = g_arrStlFaces.GetItem(0);

	//---Fill Vertex and Face Table
	for(k = 0; k < m_StrComMesh.intFaceCount; k++, pSrcFace++)
	{
		pSrcVert = pSrcFace->vertices;
		for (m = 0; m < 3; m++, pSrcVert++)
		{
			//Get Last Vertex Index
			nCount = g_arrComVerts.GetCount();
			//Add a Vertex
			sComVert.vertex.x = pSrcVert->x;
			sComVert.vertex.y = pSrcVert->y;
			sComVert.vertex.z = pSrcVert->z;
			sComVert.vec3Normal.x = pSrcFace->vecNormal.x;
			sComVert.vec3Normal.y = pSrcFace->vecNormal.y;
			sComVert.vec3Normal.z = pSrcFace->vecNormal.z;
			sComVert.colorRGB.r = (float) ((pSrcFace->intAttribute >> 11) & 31) / 256.0f;
			sComVert.colorRGB.g = (float) ((pSrcFace->intAttribute >>  6) & 31) / 256.0f;
			sComVert.colorRGB.b = (float) ((pSrcFace->intAttribute >>  1) & 31) / 256.0f;
			sComVert.intMaterialId = 0;
			g_arrComVerts.AddItem(&sComVert);

			//Sort Added Vertex and Get Correct Vertex Index
			g_pSortVerts = (PCOM_VERTEX) g_arrComVerts.GetItem(0);
			nVertIdx = Stl_SortVertex(nCount, Stl_CompareVertex);
			//If not addable vertex, delete last added Vertex
			if (nVertIdx < nCount)
				g_arrComVerts.Delete(nCount, 1);
			//Set Face Vertex Index
			pFaceIdx[m] = nVertIdx;
		}
		g_arrComFaces.AddItem(pFaceIdx, 3);
		memset(pFaceIdx, 0, sizeof(int) * 3);
	}

	//Set COM_MESH Vertex Data
	m_StrComMesh.intVertexCount = g_arrComVerts.GetCount();
	m_StrComMesh.pVertices		= g_arrComVerts.Copy();

	//Set COM_MESH Face Data
	m_StrComMesh.pIndices	= g_arrComFaces.Copy();

	//Set COM_MESH Object Data
	m_StrComMesh.pObjects->nStartFace = 0;
	m_StrComMesh.pObjects->nFaceCount = m_StrComMesh.intFaceCount;
	m_StrComMesh.pObjects->strMat.fShininess = 96.0f;
	for (k = 0; k < 3; k++)
	{
		m_StrComMesh.pObjects->strMat.matAmbient[k]	= 0.5f;
		m_StrComMesh.pObjects->strMat.matDiffuse[k]	= 0.5f;
		m_StrComMesh.pObjects->strMat.matSpecular[k]= 0.5f;
		m_StrComMesh.pObjects->strMat.matEmission[k]= 0.5f;
	}
	m_StrComMesh.pObjects->strMat.matAmbient[3]	= 1.0f;
	m_StrComMesh.pObjects->strMat.matDiffuse[3]	= 1.0f;
	m_StrComMesh.pObjects->strMat.matSpecular[3]= 1.0f;
	m_StrComMesh.pObjects->strMat.matEmission[3]= 1.0f;

	//Initialize COM_MESH
	MyGetNormals(&m_StrComMesh);
	InitMesh(&m_StrComMesh);

	return TRUE;
}
