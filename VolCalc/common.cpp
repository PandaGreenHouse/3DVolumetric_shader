#include "stdafx.h"
#include "common.h"


CMyArray<COM_OBJECT>	g_arrComObjs;
CMyArray<COM_VERTEX>	g_arrComVerts;
CMyArray<int>			g_arrComFaces;


void MyVec3Cross(VECTOR3* out, VECTOR3* v0, VECTOR3* v1)
{
	out->x = v0->y*v1->z - v0->z*v1->y;
	out->y = v0->z*v1->x - v0->x*v1->z;
	out->z = v0->x*v1->y - v0->y*v1->x;
}


void MyGetNormals(PCOM_MESH pComMesh)
{
	int k = 0, m = 0, *pIndex;
	COM_VERTEX	*fv[3];
	VECTOR3		e1, e2, vNormal;

	if (pComMesh == NULL)
		return;
	if (pComMesh->pVertices == NULL || pComMesh->pIndices == NULL)
		return;

	//Init Material ID to 0 for Normal Vector Average Calculation
	for (k = 0; k < pComMesh->intVertexCount; k++)
		pComMesh->pVertices[k].intMaterialId = 0;
	//Compute Normals for Faces and assign it to Face Vertexes.
	for (k = 0, pIndex = pComMesh->pIndices; k < pComMesh->intFaceCount; k++, pIndex += 3)
	{
		//---Get Vertex for a Face
		fv[0] = &pComMesh->pVertices[*pIndex];
		fv[1] = &pComMesh->pVertices[pIndex[1]];
		fv[2] = &pComMesh->pVertices[pIndex[2]];
		//---Get Normal Vector for the Face
		e1.x = fv[1]->vertex.x - fv[0]->vertex.x;
		e1.y = fv[1]->vertex.y - fv[0]->vertex.y;
		e1.z = fv[1]->vertex.z - fv[0]->vertex.z;
		e2.x = fv[2]->vertex.x - fv[0]->vertex.x;
		e2.y = fv[2]->vertex.y - fv[0]->vertex.y;
		e2.z = fv[2]->vertex.z - fv[0]->vertex.z;
		MyVec3Cross(&vNormal,&e1,&e2);
		//---Set Normal Vector to 3 Vertex of the Face
		for (m = 0; m < 3; m++)
		{
			int c;
			c = fv[m]->intMaterialId;	//Previous Normal Calculation Times
			//++++++Get Average Normal Vector for each Vertex
			fv[m]->vec3Normal.x = (fv[m]->vec3Normal.x * c + vNormal.x) / (c + 1);
			fv[m]->vec3Normal.y = (fv[m]->vec3Normal.y * c + vNormal.y) / (c + 1);
			fv[m]->vec3Normal.z = (fv[m]->vec3Normal.z * c + vNormal.z) / (c + 1);
			fv[m]->intMaterialId++;
		}
	}
	//Set All Vertexes' Material ID to 0
	for (k = 0; k < pComMesh->intVertexCount; k++)
		pComMesh->pVertices[k].intMaterialId = 0;
}