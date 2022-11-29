#pragma once
#include "AABBTree.h"
#include "MyStructure.h"

typedef void (*LPCALC_CALLBACK_PROC)(void* pParams);
typedef struct tagCALCPARAMS
{
	BOOL	bLoopFlag;		//Flag for Computing Loop
	long	nProgress;		//Calculation Progress in Percent
	void*	pvfnParams;		//Parameter for pfnCallback func
	LPCALC_CALLBACK_PROC	pfnCallback;
}CALCPARAMS, *PCALCPARAMS;

class CMeshMetric
{
public:
	CMeshMetric(void);
	~CMeshMetric(void);

	void	SetComMesh(COM_MESH* pStrComMesh);
	float	ComputingVolume(PCALCPARAMS pParams);
	float   CalculateVolume(COM_MESH* pStrComMesh);
protected:
	//data
	COM_MESH*	m_pStrComMesh;
	CALCPARAMS*	m_pCalcParams;

	//CAABBTree m_ClsAABBTree;

//Implementation
void	Vec3Cross(VECTOR3* out, VECTOR3* v0, VECTOR3* v1);
float	Vec3Dot(VECTOR3* e0, VECTOR3* e1);
BOOL	IntersectTri(VECTOR3* v0, VECTOR3* v1, VECTOR3* v2,
					VECTOR3* vRayPos, VECTOR3* vRayDir,
					float* u, float* v, float* dist ); 
};

