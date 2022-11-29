#include "stdafx.h"
#include "MyVrml.h"
#include "MyStructure.h"
#include "common.h"


typedef struct tagPOLY_INDEX
{
	int		nStart;
	int		nLast;
}SPOLY_INDEX, *PPOLY_INDEX;

typedef struct tagVERT_INDEX
{
	int		nVertex;
	int		nColor;
	int		nNormal;
}SVERT_INDEX, *PVERT_INDEX;

using namespace MyVrml;

//Global Variables
COM_MESH		g_sComMesh;

CMyArray<int>			g_arrNewPolys;		//My New Polygon Vertex Index Array, -1 indicate end of polygon
CMyArray<SPOLY_INDEX>	g_arrShapePolys;	//Polygon Index(Start and Last Vertex Index) Array
CMyArray<int>			g_arrShapeColors;	//Color Index Array
CMyArray<int>			g_arrShapeNormals;	//Normal Index Array




BOOL WRL_NewObjectBuffer(int nObjects, int nVerts, int nFaces)
{
	BOOL bSuccess = TRUE;

	bSuccess &= g_arrComObjs.Create(nObjects, 16);
	bSuccess &= g_arrComVerts.Create(nVerts, 256);
	bSuccess &= g_arrComFaces.Create(nFaces * 3, 256);
	
	return bSuccess;
}

void WRL_FreeObjectBuffer()
{
	g_arrComObjs.Release();
	g_arrComVerts.Release();
	g_arrComFaces.Release();

	if (g_sComMesh.pObjects)
		free(g_sComMesh.pObjects);
	if (g_sComMesh.pVertices)
		free(g_sComMesh.pVertices);
	if (g_sComMesh.pIndices)
		free(g_sComMesh.pIndices);
	memset(&g_sComMesh, 0, sizeof(COM_MESH));
}

void WRL_GetObjectColor(PCOM_OBJECT pObject, ShapeNode* shape)
{
	if (pObject == NULL || shape == NULL)
		return;

	AppearanceNode*	appr;
	MaterialNode*	mat;
	float	fColor;

	//Set Default Colors
	for (int m = 0; m < 4; m++)
	{
		pObject->strMat.matAmbient[m]	= 0.5f;
		pObject->strMat.matDiffuse[m]	= 0.5f;
		pObject->strMat.matSpecular[m]	= 0.5f;
		pObject->strMat.matEmission[m]	= 0.5f;
	}
	pObject->strMat.fShininess = 96.0f;

	//Get From Nodes
	appr = shape->getAppearanceNodes();
	if (appr == NULL)
		return;
	mat = appr->getMaterialNodes();
	if (mat == NULL)
		return;

	fColor = mat->getAmbientIntensity();
	pObject->strMat.matAmbient[0]	= fColor;
	pObject->strMat.matAmbient[1]	= fColor;
	pObject->strMat.matAmbient[2]	= fColor;
	pObject->strMat.matAmbient[3]	= 1.0f;
	mat->getDiffuseColor(pObject->strMat.matDiffuse);
	pObject->strMat.matDiffuse[3]	= 1.0f;
	mat->getSpecularColor(pObject->strMat.matSpecular);
	pObject->strMat.matSpecular[3]	= 1.0f;
	mat->getEmissiveColor(pObject->strMat.matEmission);
	pObject->strMat.matEmission[3]	= 1.0f;
	pObject->strMat.fShininess = mat->getShininess() * 128.0f;	//0~1
}



////////////////////////////////////////////////
//
//
//	   4+--------+5
//	   /|       /|
//	  / |      / |
//	0+--------+1 |
//	 |  |     |  |
//	 | 7+-----|--+6
//	 | /      | /
//	 |/       |/
//	3+--------+2
//
////////////////////////////////////////////////
void WRL_GetBoxFaces(ShapeNode* shape, BoxNode* pBox)
{
	COM_OBJECT	sObject;
	COM_VERTEX	pCurVert[8];
	int nIdxStart, k;
	int nFaceIndex[36] = {0, 3, 2,  0, 2, 1,  0, 1, 5,  0, 5, 4,  0, 4, 7,  0, 7, 3,
						6, 7, 4,  6, 4, 5,  6, 5, 1,  6, 1, 2,  6, 2, 3,  6, 3, 7};

	if (shape == NULL)
		return;

	SFMatrix	tfmat;
	shape->getTransformMatrix(&tfmat);

	//Add Object to Array
	sObject.nStartFace	= (int) (g_arrComFaces.GetCount() / 3);
	sObject.nFaceCount	= 8;
	WRL_GetObjectColor(&sObject, shape);
	g_arrComObjs.AddItem(&sObject, 1);

	//Set Face Vertex indices
	nIdxStart= g_arrComVerts.GetCount();
	for (k = 0; k < 36; k++)
		nFaceIndex[k] += nIdxStart;
	g_arrComFaces.AddItem(nFaceIndex, 36);

	//Set Vertex Coordinates
	pCurVert[0].vertex.x = pCurVert[3].vertex.x = -(pBox->getX() / 2.0f);
	pCurVert[4].vertex.x = pCurVert[7].vertex.x = -(pBox->getX() / 2.0f);
	pCurVert[1].vertex.x = pCurVert[2].vertex.x = pBox->getX() / 2.0f;
	pCurVert[5].vertex.x = pCurVert[6].vertex.x = pBox->getX() / 2.0f;

	pCurVert[2].vertex.y = pCurVert[3].vertex.y = -(pBox->getY() / 2.0f);
	pCurVert[6].vertex.y = pCurVert[7].vertex.y = -(pBox->getY() / 2.0f);
	pCurVert[0].vertex.y = pCurVert[1].vertex.y = pBox->getY() / 2.0f;
	pCurVert[4].vertex.y = pCurVert[5].vertex.y = pBox->getY() / 2.0f;

	pCurVert[4].vertex.z = pCurVert[5].vertex.z = -(pBox->getZ() / 2.0f);
	pCurVert[6].vertex.z = pCurVert[7].vertex.z = -(pBox->getZ() / 2.0f);
	pCurVert[0].vertex.z = pCurVert[1].vertex.z = pBox->getZ() / 2.0f;
	pCurVert[2].vertex.z = pCurVert[3].vertex.z = pBox->getZ() / 2.0f;

	//Apply Transform and color to vertexes
	for (k = 0; k < 8; k++)
	{
		tfmat.multi(&(pCurVert[k].vertex.x), &(pCurVert[k].vertex.y), &(pCurVert[k].vertex.z));
		pCurVert[k].colorRGB.r = 1.0f;
		pCurVert[k].colorRGB.g = 1.0f;
		pCurVert[k].colorRGB.b = 1.0f;
	}
	//Add To Vertex Array
	g_arrComVerts.AddItem(pCurVert, 8);
}

void WRL_GetConeFaces(ShapeNode* shape, ConeNode* pCone)
{
	int		nSlices, i, k, m, d, q;		//for Loop
	int		pnIndex[6], nStartIdx = 0;
	float	fRadius, fAngle;
	COM_OBJECT	sObject;
	COM_VERTEX	sVertex, *pRef;
	SFMatrix	tfmat;	//Transform Matrix

	if (shape == NULL || pCone == NULL)
		return;

	//Get Start Vertex Index
	nStartIdx = g_arrComVerts.GetCount();
	//Get Transform Matrix
	shape->getTransformMatrix(&tfmat);
	//Set COM_MESH Object Info
	sObject.nStartFace = (int) (g_arrComFaces.GetCount() / 3);
	WRL_GetObjectColor(&sObject, shape);

	//Add Vertex Positions at Local Coordinate to COM_MESH Vertex Array
	//---Get Cone Parameters and Calculate Angle and Circle Vertex Count
	fRadius	= pCone->getBottomRadius();	//Bottom Radius
	nSlices	= pCone->getSlices();		//Slice Count
	d = 2 * nSlices;					//latitude Vertex Count
	fAngle	= PI / (float) nSlices;		//alpha for each Slice Angle
	//---Initialize Vertex Color and Material ID
	sVertex.colorRGB.r = 0.75f;
	sVertex.colorRGB.g = 0.75f;
	sVertex.colorRGB.b = 0.75f;
	sVertex.intMaterialId = 0;
	//---Get Positions of Bottom Surface Circle Border
	sVertex.vertex.y = -(pCone->getHeight() / 2.0f);
	for (k = 0; k < d; k++)
	{
		sVertex.vertex.x = fRadius * cos((float) k * fAngle);
		sVertex.vertex.z = fRadius * sin((float) k * fAngle);
		g_arrComVerts.AddItem(&sVertex, 1);
	}
	//---Center of Top and Bottom Surface
	//++++++Top Center
	sVertex.vertex.x = sVertex.vertex.z = 0.0f;
	sVertex.vertex.y =  (pCone->getHeight() / 2.0f);
	g_arrComVerts.AddItem(&sVertex, 1);
	//++++++Bottom Center
	sVertex.vertex.x = sVertex.vertex.z = 0.0f;
	sVertex.vertex.y = -(pCone->getHeight() / 2.0f);
	g_arrComVerts.AddItem(&sVertex, 1);

	//Apply Transforms for all COM_MESH Vertexes
	m	= g_arrComVerts.GetCount() - nStartIdx;
	pRef= g_arrComVerts.GetItem(nStartIdx);
	for (k = 0; k < m; k++, pRef++)
		tfmat.multi(&(pRef->vertex.x), &(pRef->vertex.y), &(pRef->vertex.z));

	//Add COM_MESH faces of side
	m = nStartIdx + d;	//Top Center Index
	i = nStartIdx;		//Circle Vertex Start Index
	//---Round Circle Vertexes
	for (k = 0; k < d; k++)
	{
		q = ((k + 1) % d);
		pnIndex[0]	= m;
		pnIndex[1]	= i + k;
		pnIndex[2]	= i + q;
		g_arrComFaces.AddItem(pnIndex, 3);
	}

	//Add COM_MESH faces of Bottom Surface
	m = nStartIdx + d + 1;	//Bottom Center Index
	i = nStartIdx;			//Circle Vertex Start Index
	//---Round Circle Vertexes
	for (k = 0; k < d; k++)
	{
		q = ((k + 1) % d);
		pnIndex[0] = m;
		pnIndex[1] = i + q;
		pnIndex[2] = i + k;
		g_arrComFaces.AddItem(pnIndex, 3);
	}

	//Add COM_MESH object
	sObject.nFaceCount = (int) (g_arrComFaces.GetCount() / 3) - sObject.nStartFace;
	g_arrComObjs.AddItem(&sObject);
}

void WRL_GetCylinerFaces(ShapeNode* shape, CylinderNode* pCyl)
{
	int		nSlices, i, k, m, d, q;		//for Loop
	int		pnIndex[6], nStartIdx = 0;
	float	fRadius, fAngle;
	COM_OBJECT	sObject;
	COM_VERTEX	sVertex, *pRef;
	SFMatrix	tfmat;	//Transform Matrix

	if (shape == NULL || pCyl == NULL)
		return;

	//Get Start Vertex Index
	nStartIdx = g_arrComVerts.GetCount();
	//Get Transform Matrix
	shape->getTransformMatrix(&tfmat);
	//Set COM_MESH Object Info
	sObject.nStartFace = (int) (g_arrComFaces.GetCount() / 3);
	WRL_GetObjectColor(&sObject, shape);

	//Add Vertex Positions at Local Coordinate to COM_MESH Vertex Array
	//---Get Cylinder Parameters and Calculate Angle and Circle Vertex Count
	fRadius	= pCyl->getRadius();		//Radius
	nSlices	= pCyl->getSlices();		//Slice Count
	d = 2 * nSlices;					//latitude Vertex Count
	fAngle	= PI / (float) nSlices;		//alpha for each Slice Angle
	//---Initialize Vertex Color and Material ID
	sVertex.colorRGB.r = 0.75f;
	sVertex.colorRGB.g = 0.75f;
	sVertex.colorRGB.b = 0.75f;
	sVertex.intMaterialId = 0;
	//---Get Positions of Top Circle Vertexes
	sVertex.vertex.y= pCyl->getHeight() / 2.0f;
	for (k = 0; k < d; k++)
	{
		sVertex.vertex.x = fRadius * cos((float) k * fAngle);
		sVertex.vertex.z = fRadius * sin((float) k * fAngle);
		g_arrComVerts.AddItem(&sVertex, 1);
	}
	//---Get Positions of Bottom Circle Vertexes
	sVertex.vertex.y= -(pCyl->getHeight() / 2.0f);
	pRef = g_arrComVerts.GetItem(nStartIdx);
	for (k = 0; k < d; k++, pRef++)
	{
		sVertex.vertex.x = pRef->vertex.x;
		sVertex.vertex.z = pRef->vertex.z;
		g_arrComVerts.AddItem(&sVertex, 1);
	}
	//---Center of Top and Bottom Surface
	//++++++Top Center
	sVertex.vertex.x = sVertex.vertex.z = 0.0f;
	sVertex.vertex.y =  (pCyl->getHeight() / 2.0f);
	g_arrComVerts.AddItem(&sVertex, 1);
	//++++++Bottom Center
	sVertex.vertex.x = sVertex.vertex.z = 0.0f;
	sVertex.vertex.y = -(pCyl->getHeight() / 2.0f);
	g_arrComVerts.AddItem(&sVertex, 1);

	//Apply Transforms for all COM_MESH Vertexes
	m	= g_arrComVerts.GetCount() - nStartIdx;
	pRef= g_arrComVerts.GetItem(nStartIdx);
	for (k = 0; k < m; k++, pRef++)
		tfmat.multi(&(pRef->vertex.x), &(pRef->vertex.y), &(pRef->vertex.z));

	//Add COM_MESH faces of side
	m = nStartIdx;
	for (k = 0; k < d; k++)
	{
		q = ((k + 1) % d);
		pnIndex[0]	= m + k;
		pnIndex[1]	= m + d + k;
		pnIndex[2]	= m + d + q;
		pnIndex[3]	= m + k;
		pnIndex[4]	= m + d + q;
		pnIndex[5]	= m + q;
		g_arrComFaces.AddItem(pnIndex, 6);
	}

	//Add COM_MESH faces of Top Surface
	m = nStartIdx + 2 * d;	//Top Center Index
	i = nStartIdx;			//Top Circle Vertex Start Index
	for (k = 0; k < d; k++)
	{
		q = ((k + 1) % d);
		pnIndex[0] = m;
		pnIndex[1] = i + k;
		pnIndex[2] = i + q;
		g_arrComFaces.AddItem(pnIndex, 3);
	}
	//Add COM_MESH faces of Bottom Surface
	m = nStartIdx + 2 * d + 1;	//Bottom Center Index
	i = nStartIdx + d;			//Bottom Circle Vertex Start Index
	for (k = 0; k < d; k++)
	{
		q = ((k + 1) % d);
		pnIndex[0] = m;
		pnIndex[1] = i + q;
		pnIndex[2] = i + k;
		g_arrComFaces.AddItem(pnIndex, 3);
	}

	//Add COM_MESH object
	sObject.nFaceCount = (int) (g_arrComFaces.GetCount() / 3) - sObject.nStartFace;
	g_arrComObjs.AddItem(&sObject);
}

void WRL_GetSphereFaces(ShapeNode* shape, SphereNode* pSphere)
{
	int		nSlices, i, k, m, d, q;		//for Loop
	int		pnIndex[6], nStartIdx = 0;
	float	fRadius, fAngle;
	float	fUnitRad;
	COM_OBJECT	sObject;
	COM_VERTEX	sVertex, *pRef;
	SFMatrix	tfmat;	//Transform Matrix

	if (shape == NULL || pSphere == NULL)
		return;

	//Get Start Vertex Index
	nStartIdx = g_arrComVerts.GetCount();
	//Get Transform Matrix
	shape->getTransformMatrix(&tfmat);
	//Set COM_MESH Object Info
	sObject.nStartFace = (int) (g_arrComFaces.GetCount() / 3);
	WRL_GetObjectColor(&sObject, shape);

	//Add Vertex Positions at Local Coordinate to COM_MESH Vertex Array
	fRadius	= pSphere->getRadius();		//Radius
	nSlices	= pSphere->getSlices();		//Slice Count
	d = 2 * nSlices;					//latitude Vertex Count
	fAngle	= PI / (float) nSlices;		//alpha for each Slice Angle

	//---Initialize Vertex Color and Material ID
	sVertex.colorRGB.r = 0.75f;
	sVertex.colorRGB.g = 0.75f;
	sVertex.colorRGB.b = 0.75f;
	sVertex.intMaterialId = 0;
	//---Get Positions of latitude lines' Vertexes
	for (i = 1; i < nSlices; i++)
	{
		fUnitRad		 = fRadius * sin((float) i * fAngle);
		sVertex.vertex.y = fRadius * cos((float) i * fAngle);
		for (k = 0; k < d; k++)
		{
			sVertex.vertex.x = fUnitRad * cos((float) k * fAngle);
			sVertex.vertex.z = fUnitRad * sin((float) k * fAngle);
			g_arrComVerts.AddItem(&sVertex, 1);
		}
	}
	//---Center of Top and Bottom Surface
	//++++++Top Center
	sVertex.vertex.x = sVertex.vertex.z = 0.0f;
	sVertex.vertex.y =  fRadius;
	g_arrComVerts.AddItem(&sVertex, 1);
	//++++++Bottom Center
	sVertex.vertex.x = sVertex.vertex.z = 0.0f;
	sVertex.vertex.y = -fRadius;
	g_arrComVerts.AddItem(&sVertex, 1);

	//Apply Transforms for all COM_MESH Vertexes
	m	= g_arrComVerts.GetCount() - nStartIdx;
	pRef= g_arrComVerts.GetItem(nStartIdx);
	for (k = 0; k < m; k++, pRef++)
		tfmat.multi(&(pRef->vertex.x), &(pRef->vertex.y), &(pRef->vertex.z));

	//Add COM_MESH faces of side
	for (i = 1, m = nStartIdx; i < (nSlices-1); i++, m += d)
	{
		for (k = 0; k < d; k++)
		{
			q = ((k + 1) % d);
			pnIndex[0]	= m + k;
			pnIndex[1]	= m + d + k;
			pnIndex[2]	= m + d + q;
			pnIndex[3]	= m + k;
			pnIndex[4]	= m + d + q;
			pnIndex[5]	= m + q;
			g_arrComFaces.AddItem(pnIndex, 6);
		}
	}

	//Add COM_MESH faces of Top Cap
	m = nStartIdx + d * (nSlices - 1);	//Top Center Index
	i = nStartIdx;						//First Line Vertexes
	for (k = 0; k < d; k++)
	{
		q = ((k + 1) % d);
		pnIndex[0] = m;
		pnIndex[1] = i + k;
		pnIndex[2] = i + q;
		g_arrComFaces.AddItem(pnIndex, 3);
	}
	//Add COM_MESH faces of Bottom Surface
	m = nStartIdx + d * (nSlices - 1) + 1;	//Bottom Center Index
	i = nStartIdx + d * (nSlices - 2);		//Last Line Vertexes
	for (k = 0; k < d; k++)
	{
		q = ((k + 1) % d);
		pnIndex[0] = m;
		pnIndex[1] = i + q;
		pnIndex[2] = i + k;
		g_arrComFaces.AddItem(pnIndex, 3);
	}

	//Add COM_MESH object
	sObject.nFaceCount = (int) (g_arrComFaces.GetCount() / 3) - sObject.nStartFace;
	g_arrComObjs.AddItem(&sObject);
}


void WRL_GetElevationGridFaces(ShapeNode* shape, ElevationGridNode* pGrid)
{

}

void WRL_GetExtrusionFaces(ShapeNode* shape, ExtrusionNode* pExt)
{

}

void WRL_IFS_GetColorNormalIndices(IndexedFaceSetNode* idxFaceSet)
{
	ColorNode*		colorNode;
	NormalNode*		normalNode;
	PPOLY_INDEX	pCurPoly;
	bool		bFlag = false, bNormal = false, bColor = false;
	int	nPolygons;				//Polygon Count
	int nCount, nValues[4];		//Integer Temp Values
	int	k, m;		//for Loop

	colorNode	= idxFaceSet->getColorNodes();
	normalNode	= idxFaceSet->getNormalNodes();

	//Get Color Index Array (equalize coordIndex array)
	nPolygons = g_arrShapePolys.GetCount();
	g_arrShapeColors.Clear();
	if (colorNode)
	{
		nCount	= idxFaceSet->getNColorIndexes();
		bFlag	= idxFaceSet->getColorPerVertex();
		if (bFlag)
		{ //colorPerVertex is TRUE : Color is applied to each vertex
			m = idxFaceSet->getNCoordIndexes();
			for (k = 0; k < m; k++)
			{
				//---Chose Color Index for Vertex
				if (nCount > k) //colorIndex is not empty, use colorIndex to choose color
					nValues[0] = idxFaceSet->getColorIndex(k);
				else //colorIndex is empty, use coordIndex to choose color
					nValues[0] = idxFaceSet->getCoordIndex(k);
				//---Add Color Index
				g_arrShapeColors.AddItem(&nValues[0], 1);
			}
		} else
		{ //colorPerVertex is FALSE : Color is applied to each polygon
			m = idxFaceSet->getNCoordIndexes();	//coordIndex size
			pCurPoly = g_arrShapePolys.GetItem(0);
			for (k = 0; k < nPolygons; k++, pCurPoly++)
			{
				//---Add -1 items
				m = pCurPoly->nStart - g_arrShapeColors.GetCount();
				nValues[1] = -1;
				while (m > 0)
				{
					if (g_arrShapeColors.AddItem(&nValues[1], 1))
						m--;
				}

				//---Chose Color Index for Vertex
				if (nCount > 0) //colorIndex is not empty, use colorIndex to choose color of Polygon
					nValues[1] = idxFaceSet->getColorIndex(k);
				else //colorIndex is empty, use coordIndex to order of Polygon
					nValues[1] = k;
				//---Add Color Indices as many as vertex count of this Polygon
				m = pCurPoly->nLast - pCurPoly->nStart + 1;
				while (m > 0)
				{
					if (g_arrShapeColors.AddItem(&nValues[1], 1))
						m--;
				}
			}
		}
	}

	//Get Normal Index Array (equalize coordIndex array)
	g_arrShapeNormals.Clear();
	if (normalNode)
	{
		nCount	= idxFaceSet->getNNormalIndexes();
		bFlag	= idxFaceSet->getColorPerVertex();
		if (bFlag)
		{ //colorPerVertex is TRUE : Color is applied to each vertex
			m = idxFaceSet->getNCoordIndexes();
			for (k = 0; k < m; k++)
			{
				//---Chose Color Index for Vertex
				if (nCount > k) //colorIndex is not empty, use colorIndex to choose color
					nValues[0] = idxFaceSet->getNormalIndex(k);
				else //colorIndex is empty, use coordIndex to choose color
					nValues[0] = idxFaceSet->getCoordIndex(k);
				//---Add Color Index
				g_arrShapeNormals.AddItem(&nValues[0], 1);
			}
		} else
		{ //colorPerVertex is FALSE : Color is applied to each polygon
			m = idxFaceSet->getNCoordIndexes();	//coordIndex size
			pCurPoly = g_arrShapePolys.GetItem(0);
			for (k = 0; k < nPolygons; k++, pCurPoly++)
			{
				//---Add -1 items
				m = pCurPoly->nStart - g_arrShapeNormals.GetCount();
				nValues[1] = -1;
				while (m > 0)
				{
					if (g_arrShapeNormals.AddItem(&nValues[1], 1))
						m--;
				}

				//---Chose Color Index for Vertex
				if (nCount > 0) //colorIndex is not empty, use colorIndex to choose color of Polygon
					nValues[1] = idxFaceSet->getColorIndex(k);
				else //colorIndex is empty, use coordIndex to order of Polygon
					nValues[1] = k;
				//---Add Color Indices as many as vertex count of this Polygon
				m = pCurPoly->nLast - pCurPoly->nStart + 1;
				while (m > 0)
				{
					if (g_arrShapeNormals.AddItem(&nValues[1], 1))
						m--;
				}
			}
		}
	}
}

void WRL_GetIndexedFaceSetFaces(ShapeNode* shape, IndexedFaceSetNode* idxFaceSet)
{
	SFMatrix		tfmat;
	ColorNode*		colorNode;
	NormalNode*		normalNode;
	CoordinateNode*	vertexNode;
	COM_VERTEX	sNewVert;
	COM_OBJECT	sObject;
	SPOLY_INDEX	sCurPoly, *pCurPoly;
	float		fValues[3];		//float Values
	bool		bFlag = false, bNormal = false, bColor = false;
	int	nPolygons, nStartIdx;	//Polygon Count, COM_MESH Vertex Start Index
	int nCount, nValues[4];		//Integer Temp Values
	int	k, m, i, *pIndex;		//for Loop
	

	if (shape == NULL)
		return;

	//Get Nodes
	colorNode	= idxFaceSet->getColorNodes();
	normalNode	= idxFaceSet->getNormalNodes();
	vertexNode	= idxFaceSet->getCoordinateNodes();
	if (!vertexNode)
		return;

	//Get Polygon Start Index Array
	nCount = idxFaceSet->getNCoordIndexes();
	g_arrShapePolys.Clear();
	g_arrShapePolys.Create(nCount, 256);
	sCurPoly.nStart = 0;
	for (k = 0; k < nCount; k++)
	{
		m = idxFaceSet->getCoordIndex(k);
		if (m == -1)
		{
			if (sCurPoly.nStart != k)
			{
				sCurPoly.nLast = k - 1;
				g_arrShapePolys.AddItem(&sCurPoly, 1);
			}
			sCurPoly.nStart = k + 1;
		}
	}
	nPolygons = g_arrShapePolys.GetCount();

	//Get Color and Normal Index Array
	WRL_IFS_GetColorNormalIndices(idxFaceSet);
	bNormal = (g_arrShapeNormals.GetCount() < 1) ? false : true;
	bColor	= (g_arrShapeColors.GetCount() < 1) ? false : true;

	//Get Transform Matrix
	shape->getTransformMatrix(&tfmat);

	//Add Vertexes and Get Polygon Index Array
	g_arrNewPolys.Clear();
	g_arrNewPolys.Create(65536, 256);
	pCurPoly	= g_arrShapePolys.GetItem(0);
	nStartIdx	= g_arrComVerts.GetCount();
	for (k = 0; k < nPolygons; k++, pCurPoly++)
	{
		for (m = pCurPoly->nStart; m <= pCurPoly->nLast; m++)
		{
			//---Get COM_MESH Vertex Info (Coordinate, Normal and Color)
			memset(&sNewVert, 0, sizeof(COM_VERTEX));
			nValues[0] = idxFaceSet->getCoordIndex(m);
			vertexNode->getPoint(nValues[0], fValues);
			tfmat.multi(fValues);
			sNewVert.vertex.x = fValues[0];
			sNewVert.vertex.y = fValues[1];
			sNewVert.vertex.z = fValues[2];
			if (bNormal)
			{
				nValues[0] = g_arrShapeNormals[m];
				normalNode->getVector(nValues[0], fValues);
				sNewVert.vec3Normal.x = fValues[0];
				sNewVert.vec3Normal.y = fValues[1];
				sNewVert.vec3Normal.z = fValues[2];
			}
			if (bColor)
			{
				nValues[0] = g_arrShapeColors[m];
				colorNode->getColor(nValues[0], fValues);
				sNewVert.colorRGB.r	= fValues[0];
				sNewVert.colorRGB.g	= fValues[1];
				sNewVert.colorRGB.b	= fValues[2];
			} else
			{
				sNewVert.colorRGB.r	= 0.75f;
				sNewVert.colorRGB.g	= 0.75f;
				sNewVert.colorRGB.b	= 0.75f;
			}
			//---Get Index of Current COM_MESH Vertex, if not exists, the vertex is added.
			nValues[0] = g_arrComVerts.GetIndex(nStartIdx, &sNewVert, TRUE);
			
			//---Add Index of New Vertex Array to New Polygon Vertex Array
			g_arrNewPolys.AddItem(nValues, 1);
		}

		nValues[0] = -1;
		g_arrNewPolys.AddItem(nValues, 1);
	}

	//Get Face Info and Add COM_MESH Object
	//---Get Start Face Index and Color of New COM_MESH Object
	sObject.nStartFace = (int) (g_arrComFaces.GetCount() / 3);
	WRL_GetObjectColor(&sObject, shape);
	//---Get Face Vertex orientation flag
	bFlag	= idxFaceSet->getCCW();
	//---Loop all Polygon to Get Triangular Faces
	pIndex	= g_arrNewPolys.GetItem(0);
	nCount	= g_arrNewPolys.GetCount();
	for (k = 0; k < nCount;)
	{
		m = k + 1;
		while (pIndex[m] != -1)
			m++;
		m--;
		if (bFlag)
		{ //Counter Clock Wise
			for (i = k+1; i < m; i++)
			{
				nValues[0] = pIndex[k];
				nValues[1] = pIndex[i];
				nValues[2] = pIndex[i + 1];
				g_arrComFaces.AddItem(nValues, 3);
			}
		} else
		{ //Clock-wise
			for (i = m-1; i > k; i--)
			{
				nValues[0] = pIndex[m];
				nValues[1] = pIndex[i];
				nValues[2] = pIndex[i - 1];
				g_arrComFaces.AddItem(nValues, 3);
			}
		}

		//Prepare Next Loop
		k = m + 2;
		if (k >= nCount)
			break;
		while (pIndex[k] == -1)
			k++;
	}

	//---Get Face Count of New COM_MESH Object and Add to Array
	sObject.nFaceCount = (int) (g_arrComFaces.GetCount() / 3) - sObject.nStartFace;
	g_arrComObjs.AddItem(&sObject);
}