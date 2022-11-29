#ifndef __MY_MEM_ALLOC_HEADER__
#define __MY_MEM_ALLOC_HEADER__

#include "MyArray.h"

extern CMyArray<COM_OBJECT>	g_arrComObjs;
extern CMyArray<COM_VERTEX>	g_arrComVerts;
extern CMyArray<int>		g_arrComFaces;

extern void MyVec3Cross(VECTOR3* out, VECTOR3* v0, VECTOR3* v1);
extern void MyGetNormals(PCOM_MESH pComMesh);

#endif	//__MY_MEM_ALLOC_HEADER__