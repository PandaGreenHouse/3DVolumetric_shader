// wrl.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "wrl.h"
#include <stdlib.h>
#include "MyVrml.h"
#include "shape.h"
#include "common.h"


using namespace MyVrml;

char		g_szErrorString[5120] = "";
SceneGraph	g_sgWrl;



void WRL_GetAllFaces(Node* firstNode);
int	 WRL_GetFaceData(PCOM_MESH	pComMesh);



int  WrlOpenFileA(LPSTR lpszFilePath, PCOM_MESH pComMesh)
{
	int		nFormat;

	if (lpszFilePath == NULL || lpszFilePath[0] == 0 || pComMesh == NULL)
		return WRL_E_INVALID_PARAMETER;

	g_szErrorString[0] = 0;
	nFormat = GetFileFormatA((const char*) lpszFilePath);
	if (nFormat != FILE_FORMAT_VRML)
		return WRL_E_FORMAT_NOT_SUPPORTED;
	if (g_sgWrl.loadA((const char*) lpszFilePath) == false)
	{
		sprintf(g_szErrorString, "Loading Error (%d) : %s, %s",
							g_sgWrl.getParserErrorLineNumber(), 
							g_sgWrl.getParserErrorMessage(),
							g_sgWrl.getParserErrorLineString());
		OutputDebugStringA(g_szErrorString);
		return WRL_E_PARSE_FAILED;
	}

	return WRL_GetFaceData(pComMesh);
}

int  WrlOpenFileW(LPCWSTR lpszFilePath, PCOM_MESH pComMesh)
{
	int		nFormat;

	if (lpszFilePath == NULL || lpszFilePath[0] == 0 || pComMesh == NULL)
		return WRL_E_INVALID_PARAMETER;

	g_szErrorString[0] = 0;
	nFormat = GetFileFormatW((const wchar_t*) lpszFilePath);
	if (nFormat != FILE_FORMAT_VRML)
		return WRL_E_FORMAT_NOT_SUPPORTED;
	if (g_sgWrl.loadW((const wchar_t*) lpszFilePath) == false)
	{
		sprintf(g_szErrorString, "Loading Error (%d) : %s, %s",
							g_sgWrl.getParserErrorLineNumber(), 
							g_sgWrl.getParserErrorMessage(),
							g_sgWrl.getParserErrorLineString());
		OutputDebugStringA(g_szErrorString);
		return WRL_E_PARSE_FAILED;
	}

	return WRL_GetFaceData(pComMesh);
}

int  WRL_GetFaceData(PCOM_MESH	pComMesh)
{
	int	nErrCode = WRL_E_SUCCESS;
	if (!WRL_NewObjectBuffer(1024, 65536, 65536))
		return WRL_E_INSUFFICIENT_MEMORY;

	//Get Faces
	nErrCode = WRL_E_GETFACES_FAILED;
	WRL_GetAllFaces(g_sgWrl.getNodes());
	//Copy COM_MESH Data from Arrays
	g_sComMesh.intObjectCount	= g_arrComObjs.GetCount();
	g_sComMesh.pObjects			= g_arrComObjs.Copy();
	g_sComMesh.intFaceCount		= (int) (g_arrComFaces.GetCount() / 3);	//One Face includes 3 integers
	g_sComMesh.pIndices			= g_arrComFaces.Copy();
	g_sComMesh.intVertexCount	= g_arrComVerts.GetCount();
	g_sComMesh.pVertices		= g_arrComVerts.Copy();
	if (g_sComMesh.pObjects != NULL && g_sComMesh.pVertices != NULL && g_sComMesh.pIndices != NULL)
	{
		MyGetNormals(&g_sComMesh);
		memcpy(pComMesh, &g_sComMesh, sizeof(COM_MESH));
		nErrCode = WRL_E_SUCCESS;
	}
	return nErrCode;
}


void WrlCloseFile(PCOM_MESH pComMesh)
{
	if (pComMesh == NULL)
		return;

	pComMesh->pVertices	= NULL;
	pComMesh->pIndices	= NULL;
	pComMesh->intFaceCount	 = 0;
	pComMesh->intVertexCount = 0;

	g_sgWrl.clear();
	WRL_FreeObjectBuffer();
}

//Copies Error String and Returns Length in Bytes
int  WrlGetErrorTextA(LPSTR	lpszError, int nMaxLen)
{
	int nLen = 0;

	if (lpszError == NULL)
		return 0;

	nLen = strlen(g_szErrorString);
	if (nLen >= nMaxLen)
		nLen = nMaxLen - 1;
	strcpy(lpszError, g_szErrorString);
	return nLen;
}

//Copies Error String and Returns Length in Bytes
int  WrlGetErrorTextW(wchar_t*	lpszError, int nMaxLen)
{
	int nLen = 0;

	if (lpszError == NULL)
		return 0;

	nLen = strlen(g_szErrorString);
	if (nLen >= nMaxLen)
		nLen = nMaxLen - 1;
	nLen = MultiByteToWideChar(CP_ACP, 0, g_szErrorString, nLen + 1, lpszError, nLen);
	return nLen;
}





void WRL_GetShapeFaces(ShapeNode* shape)
{
	if (shape == NULL)
		return;

	Geometry3DNode*	pg = NULL;
	pg = shape->getGeometry3D();
	if (pg == NULL)
		return;

	switch (pg->getType())
	{
	case BOX_NODE:
		WRL_GetBoxFaces(shape, (BoxNode*) pg);
		break;
	case CONE_NODE:
		WRL_GetConeFaces(shape, (ConeNode*) pg);
		break;
	case CYLINDER_NODE:
		WRL_GetCylinerFaces(shape, (CylinderNode*) pg);
		break;
	case SPHERE_NODE:
		WRL_GetSphereFaces(shape, (SphereNode*) pg);
		break;
	case ELEVATIONGRID_NODE:
		WRL_GetElevationGridFaces(shape, (ElevationGridNode*) pg);
		break;
	case EXTRUSION_NODE:
		WRL_GetExtrusionFaces(shape, (ExtrusionNode*) pg);
		break;
	case INDEXEDFACESET_NODE:
		WRL_GetIndexedFaceSetFaces(shape, (IndexedFaceSetNode*) pg);
		break;
	}
}

void WRL_GetAllFaces(Node* firstNode)
{
	if (firstNode == NULL)
		return;

	Node	*node = NULL;

	for (node = firstNode; node; node = node->next())
	{
		if (node->isShapeNode())
			WRL_GetShapeFaces((ShapeNode*) node);
		else
			WRL_GetAllFaces(node->getChildNodes());
	}
}