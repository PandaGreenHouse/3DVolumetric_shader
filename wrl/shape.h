#pragma once
#ifndef __WRL_SHAPE_HEADER__
#define __WRL_SHAPE_HEADER__

#include "MyVrml.h"

//Global Variables
extern COM_MESH	g_sComMesh;

using namespace MyVrml;

extern BOOL WRL_NewObjectBuffer(int nObjCount, int nVertCnt, int nFaceCnt);
extern void WRL_FreeObjectBuffer();


extern void WRL_GetBoxFaces(ShapeNode* shape, BoxNode* pBox);
extern void WRL_GetConeFaces(ShapeNode* shape, ConeNode* pCone);
extern void WRL_GetCylinerFaces(ShapeNode* shape, CylinderNode* pCyl);
extern void WRL_GetElevationGridFaces(ShapeNode* shape, ElevationGridNode* pGrid);
extern void WRL_GetExtrusionFaces(ShapeNode* shape, ExtrusionNode* pExt);
extern void WRL_GetIndexedFaceSetFaces(ShapeNode* shape, IndexedFaceSetNode* pSet);
extern void WRL_GetSphereFaces(ShapeNode* shape, SphereNode* pSphere);

#endif //__WRL_SHAPE_HEADER__