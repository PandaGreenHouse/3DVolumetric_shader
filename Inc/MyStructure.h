#pragma once

#ifndef ___MY_3D_STRUCTURES_HEADER___
#define ___MY_3D_STRUCTURES_HEADER___
#define DOT_COUNT	5000
struct VECTOR3
{
	float x,y,z;
};

struct COLOR3F
{
	float r,g,b;
};
typedef struct tagCOM_VERTEX
{
	VECTOR3 vertex;
	VECTOR3 vec3Normal;
	COLOR3F colorRGB;
	int     intMaterialId;
}COM_VERTEX, *PCOM_VERTEX;

typedef struct tagCOM_MATINFO
{
	float	matAmbient[4];
	float	matDiffuse[4];
	float	matSpecular[4];
	float	matEmission[4];
	float	fShininess;		//0~1
}COM_MATINFO, *PCOM_MATINFO;

typedef struct tagCOM_OBJECT
{
	COM_MATINFO	strMat;
	int		nStartFace;
	int		nFaceCount;
}COM_OBJECT, *PCOM_OBJECT;


typedef struct tagCOM_MESH
{
	int			intObjectCount;
	int			intFaceCount;
	int			intVertexCount;
	PCOM_OBJECT	pObjects;
	COM_VERTEX*	pVertices;
	int*		pIndices;
	VECTOR3		vec3Min, vec3Max;
	int			Cx, Cy, Cz;
	float		Dx, Dy, Dz;
	float		delta,fMax;
	float		fVolume;
} COM_MESH, *PCOM_MESH;

#endif	//___MY_3D_STRUCTURES_HEADER___