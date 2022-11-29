#include "stdafx.h"
#include "ModelFile.h"
#include "StlFile.h"
#include "VrmlFile.h"
#include "ObjFile.h"
#include "C3dsFile.h"
#include "math.h"

CModelFile::CModelFile(void)
{
}


CModelFile::~CModelFile(void)
{
}

BOOL CModelFile::Open(LPCTSTR lpszFilePath, PCOM_MESH pComMesh)
{
	return TRUE;
}

void CModelFile::Close()
{
}

COM_MESH* CModelFile::GetMesh()
{
	return NULL;
}

void CModelFile::InitMesh(PCOM_MESH pComMesh)
{
	if (pComMesh == NULL || pComMesh->pVertices == NULL)
		return;

	int intVxCount = pComMesh->intVertexCount;
	VECTOR3 vMin, vMax, vCenter;
	COM_VERTEX* pVertices = pComMesh->pVertices;
	vCenter.x = vCenter.y = vCenter.z = 0.0f;
	for(int i=0; i<intVxCount; i++)
	{
		vCenter.x = (i*vCenter.x + pVertices[i].vertex.x)/(i+1);
		vCenter.y = (i*vCenter.y + pVertices[i].vertex.y)/(i+1);
		vCenter.z = (i*vCenter.z + pVertices[i].vertex.z)/(i+1);
	}
	vMin.x = vMax.x = pVertices[0].vertex.x - vCenter.x;
	vMin.y = vMax.y = pVertices[0].vertex.y - vCenter.y;
	vMin.z = vMax.z = pVertices[0].vertex.z - vCenter.z;
	for(int i=0; i<intVxCount; i++)
	{
		pVertices[i].vertex.x -= vCenter.x;
		pVertices[i].vertex.y -= vCenter.y;
		pVertices[i].vertex.z -= vCenter.z;
		if(vMin.x > pVertices[i].vertex.x)
			vMin.x = pVertices[i].vertex.x;
		if(vMin.y > pVertices[i].vertex.y)
			vMin.y = pVertices[i].vertex.y;
		if(vMin.z > pVertices[i].vertex.z)
			vMin.z = pVertices[i].vertex.z;
		if(vMax.x < pVertices[i].vertex.x)
			vMax.x = pVertices[i].vertex.x;
		if(vMax.y < pVertices[i].vertex.y)
			vMax.y = pVertices[i].vertex.y;
		if(vMax.z < pVertices[i].vertex.z)
			vMax.z = pVertices[i].vertex.z;
	}
	pComMesh->Dx = vMax.x - vMin.x;
	pComMesh->Dy = vMax.y - vMin.y;
	pComMesh->Dz = vMax.z - vMin.z;
	pComMesh->vec3Max.x = vMax.x;
	pComMesh->vec3Max.y = vMax.y;
	pComMesh->vec3Max.z = vMax.z;
	pComMesh->vec3Min.x = vMin.x;
	pComMesh->vec3Min.y = vMin.y;
	pComMesh->vec3Min.z = vMin.z;
	float fMax = 0.0f;
	if(fMax < pComMesh->Dx) fMax = pComMesh->Dx;
	if(fMax < pComMesh->Dy) fMax = pComMesh->Dy;
	if(fMax < pComMesh->Dz) fMax = pComMesh->Dz;

	float s = 1.0f;
	if(fMax < 1.0f)
	{
		float fMax0 = fMax;
		while(fMax < 10.0f)
		{
			s = 10.0f*s;
			fMax = s*fMax0;
		}
		for(int i=0; i<intVxCount; i++)
		{
			pVertices[i].vertex.x = s*pVertices[i].vertex.x; 
			pVertices[i].vertex.y = s*pVertices[i].vertex.y; 
			pVertices[i].vertex.z = s*pVertices[i].vertex.z; 
		}
		pComMesh->vec3Max.x = s*vMax.x;
		pComMesh->vec3Max.y = s*vMax.y;
		pComMesh->vec3Max.z = s*vMax.z;
		pComMesh->vec3Min.x = s*vMin.x;
		pComMesh->vec3Min.y = s*vMin.y;
		pComMesh->vec3Min.z = s*vMin.z;
		pComMesh->Dx = s*pComMesh->Dx;
		pComMesh->Dy = s*pComMesh->Dy;
		pComMesh->Dz = s*pComMesh->Dz;
	}
	pComMesh->fMax = fMax;
}

CModelFile* CreateModelFile(LPCTSTR lpszFilePath)
{
	CModelFile*	pFile = NULL;

	if (lpszFilePath == NULL || lpszFilePath[0] == 0)
		return NULL;
	if (C3dsFile::IsModelFile(lpszFilePath))
		pFile = new C3dsFile();
	else if (CVrmlFile::IsModelFile(lpszFilePath))
		pFile = new CVrmlFile();
	else if (CObjFile::IsModelFile(lpszFilePath))
		pFile = new CObjFile();
	else if (CStlFile::IsModelFile(lpszFilePath))
		pFile = new CStlFile();

	return pFile;
}

void ReleaseModelFile(CModelFile** ppFile)
{
	if (ppFile && *ppFile)
	{
		(*ppFile)->Close();
		delete *ppFile;
		*ppFile = NULL;
	}
}