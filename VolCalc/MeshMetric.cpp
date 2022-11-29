#include "stdafx.h"
#include "MeshMetric.h"
#include "math.h"


CMeshMetric::CMeshMetric(void)
{
	m_pStrComMesh = NULL;
	m_pCalcParams = NULL;
}


CMeshMetric::~CMeshMetric(void)
{
	m_pStrComMesh = NULL;
	m_pCalcParams = NULL;
}

void CMeshMetric::SetComMesh(COM_MESH* pStrComMesh)
{
	//m_pStrComMesh = pStrComMesh;
	//m_ClsAABBTree.ConstructingTree(m_pStrComMesh); //2014.08.17
}


long	g_nTotalCount = 1;
long	g_nCurrentCnt = 0;
long	g_nElapsedTime = 0;

float CMeshMetric::ComputingVolume(PCALCPARAMS pParams)
{
	FLOAT fResult = 0.0f;
	/*if (m_pStrComMesh == NULL || pParams == NULL)
		return 0.0f;

	m_pCalcParams = pParams;

	FLOAT dx = m_pStrComMesh->delta;
	FLOAT dy = m_pStrComMesh->delta;
	FLOAT dz = 20.0f;
	int Nx = m_pStrComMesh->Dx/dx;
	int Ny = m_pStrComMesh->Dy/dy;
	VECTOR3 vMin, vMax;
	vMin.x = m_pStrComMesh->vec3Min.x;
	vMin.y = m_pStrComMesh->vec3Min.y;
	vMin.z = m_pStrComMesh->vec3Min.z;
	vMax.x = m_pStrComMesh->vec3Max.x;
	vMax.y = m_pStrComMesh->vec3Max.y;
	vMax.z = m_pStrComMesh->vec3Max.z;
	VECTOR3 vRayPos, vRayDir;
	VECTOR3 v[3];
	FLOAT u,w,dist;
	FLOAT depths1[100];
	FLOAT depths2[100];
	INT intCount[2];
	vRayDir.x = 0.0f;
	vRayDir.y = 0.0f;
	vRayDir.z = 1.0f;

	g_nElapsedTime = 0;

	//Variables for Progress//
	g_nCurrentCnt = 0;
	g_nTotalCount = Nx*Ny;
	//Variables for Progress//

	COM_VERTEX* pVertices = m_pStrComMesh->pVertices;
	VECTOR3 vNormal, e1,e2;
	int* pIndices = m_pStrComMesh->pIndices;
	int intFaceCount = 0;
	int* pFaces = NULL;
	vRayPos.z = vMin.z - dz;
	float Dx, Dy;
	Dx = m_pStrComMesh->Dx;
	Dy = m_pStrComMesh->Dy;
	for(INT iy = 0; iy<Ny+1; iy++)
	{
		//dwTime = GetTickCount();
		vRayPos.y = vMin.y + (float)iy*dy;
		if(iy==Ny) dy = Dy - (float)iy*dy;
		vRayPos.y += (float)0.5f*dy + 0.00001f;
		dx = m_pStrComMesh->delta;
		for(INT ix = 0; ix<Nx+1; ix++)
		{
			intCount[0] = 0;
			intCount[1] = 0;
			vRayPos.x = vMin.x + (float)ix*dx;
			if(ix==Nx) dx = Dx - (float)ix*dx;
			vRayPos.x += 0.5f*dx + 0.00001f;
			
			m_ClsAABBTree.GetFaceCluster(&intFaceCount,&pFaces,&vRayPos,NULL);//2014.08.18
			for(DWORD i=0; i<intFaceCount; i++)
			{
				if (m_pCalcParams->bLoopFlag == FALSE)
				   return 0.0f;
				for(int j=0; j<3; j++)
				{
					int k = pIndices[3*pFaces[i]+j]; //2014.08.17
					//int k = pIndices[3*i+j];
					v[j].x = pVertices[k].vertex.x;
					v[j].y = pVertices[k].vertex.y;
					v[j].z =  pVertices[k].vertex.z;
					k++;
				}
				e1.x = v[1].x - v[0].x;
				e1.y = v[1].y - v[0].y;
				e1.z = v[1].z - v[0].z;
				e2.x = v[2].x - v[0].x;
				e2.y = v[2].y - v[0].y;
				e2.z = v[2].z - v[0].z;
				Vec3Cross(&vNormal,&e1,&e2);
				if(IntersectTri(&v[0], &v[1], &v[2], &vRayPos, &vRayDir, &u, &w, &dist))
				{
					FLOAT dot = Vec3Dot(&vRayDir,&vNormal);
					if(dot<0.0f)
					{
						depths1[intCount[0]] = dist; 
						intCount[0]++;
					}
				}
				if(IntersectTri(&v[2], &v[1], &v[0], &vRayPos, &vRayDir, &u, &w, &dist))
				{
					FLOAT dot = Vec3Dot(&vRayDir,&vNormal);
					if(dot >0.0f)
					{
						depths2[intCount[1]] = dist; 
						intCount[1]++;
					}
				}
			}
			for(int j=0; j<intCount[0]; j++)
			{
				FLOAT min = 50000.0f;
				int count = 0;
				for(int k=0; k<intCount[1]; k++)
				{
					if(depths1[j] < depths2[k])
					{
						count++;
						if(min > depths2[k] - depths1[j])
						{
							min = depths2[k] - depths1[j];
						}
					}
				}
				if(count > 0)
				{
					//fResult += min; 
					fResult += min*dx*dy;
				}
			}
			g_nCurrentCnt++;
			if (m_pCalcParams->bLoopFlag == TRUE)
			{
				m_pCalcParams->nProgress = (g_nCurrentCnt * 100) / g_nTotalCount;
				if (m_pCalcParams->pfnCallback)
					m_pCalcParams->pfnCallback(m_pCalcParams->pvfnParams);
			}
		}
	}

	//fResult = fResult*dx*dy;
	m_pStrComMesh->fVolume = fResult;  */
	return fResult;
}


//--2014.08.07---//
void CMeshMetric::Vec3Cross(VECTOR3* out, VECTOR3* v0, VECTOR3* v1)
{
	out->x = v0->y*v1->z - v0->z*v1->y;
	out->y = v0->z*v1->x - v0->x*v1->z;
	out->z = v0->x*v1->y - v0->y*v1->x;
}

float CMeshMetric::Vec3Dot(VECTOR3* e0, VECTOR3* e1)
{
	float s=e0->x*e1->x + e0->y*e1->y + e0->z*e1->z;
	return s;
}

BOOL CMeshMetric::IntersectTri(VECTOR3* v0, VECTOR3* v1, VECTOR3* v2,
							  VECTOR3* vRayPos, VECTOR3* vRayDir, float* u, float* v, float* dist ) 
{
	VECTOR3 e1;
	e1.x = v1->x - v0->x;
	e1.y = v1->y - v0->y;
	e1.z = v1->z - v0->z;
	VECTOR3 e2;
	e2.x = v2->x - v0->x;
	e2.y = v2->y - v0->y;
	e2.z = v2->z - v0->z;
	VECTOR3 q;
	//D3DXVec3Cross(&q,vRayDir,&e2);
	Vec3Cross(&q,vRayDir,&e2);
	float a = Vec3Dot(&e1,&q);//D3DXVec3Dot(&e1,&q);//e1.dot(q);
	VECTOR3 s;//R.origin() - T.vertex(0);
	s.x = vRayPos->x-v0->x;
	s.y = vRayPos->y-v0->y;
	s.z = vRayPos->z-v0->z;
	VECTOR3 r;
	//D3DXVec3Cross(&r,&s,&e1);//s.cross(e1);
	Vec3Cross(&r,&s,&e1);
	// Barycentric vertex weights
	*u = Vec3Dot(&s,&q)/a;//D3DXVec3Dot(&s,&q)/a;//s.dot(q) / a;
	*v = Vec3Dot(vRayDir,&r)/a;//D3DXVec3Dot(vRayDir,&r)/a;//weight[2] = R.direction().dot(r) / a;
	float w = 1.0f - (*u+*v);//weight[0] = 1.0f - (weight[1] + weight[2]);
	*dist = Vec3Dot(&e2,&r)/a;//D3DXVec3Dot(&e2,&r)/a;//e2.dot(r) / a;
	static const float epsilon = 1e-7f;
	static const float epsilon2 = 1e-10f;
	if ((a <= epsilon) || (*u < -epsilon2) ||
	(*v < -epsilon2) || (w < -epsilon2) ||
	(*dist <= 0.0f)) {
	// The ray is nearly parallel to the triangle, or the
	// intersection lies outside the triangle or behind
	// the ray origin: "infinite" distance until intersection.
		return FALSE;
	}else {
		return TRUE;
	}
}

float CMeshMetric::CalculateVolume(COM_MESH* pStrComMesh)
{
	COM_VERTEX* pVertices = pStrComMesh->pVertices;
	int* pIndices = pStrComMesh->pIndices;
	int intFaceCount = pStrComMesh->intFaceCount;
	int l=0;
	VECTOR3 v[3];
	VECTOR3 vecArea;
	float fVolume = 0.0f;
	for(int i=0; i<intFaceCount; i++)
	{
		for(int j=0; j<3; j++)
		{
			l=3*i+j;
			l = pIndices[l];
			v[j].x = pVertices[l].vertex.x; 
			v[j].y = pVertices[l].vertex.y; 
			v[j].z = pVertices[l].vertex.z; 
		}
		Vec3Cross(&vecArea, &v[0], &v[1]);
		fVolume += Vec3Dot(&vecArea,&v[2])/6.0f;
	}
	fVolume = fabs(fVolume);
	pStrComMesh->fVolume = fVolume;
	return fVolume;
}