#include "stdafx.h"
#include "AABBTree.h"
struct LIST
{
	NODE* pNode;
	LIST* next;
};

CAABBTree::CAABBTree(void)
{
	m_pComMesh = NULL;
	m_pRootNode = NULL;
}


CAABBTree::~CAABBTree(void)
{
	RemoveTree();
}

void CAABBTree::PartitionByXY(int* pFaces0, int* pFaces1, int* FaceCount0, int* FaceCount1,
							  int* pFaces, int nFaceCount, float cz)
{
	int* faces[3];
	faces[0] = pFaces0;
	faces[1] = pFaces1;
	faces[2] = pFaces;
	COM_VERTEX* pVertices = m_pComMesh->pVertices;
	int* pIndices = m_pComMesh->pIndices;
	VECTOR3 v[3];
	int t=0;
	DWORD l=0;
	BOOL flags[2];
	int n0,n1;
	n0 = n1 = 0;
	for(int i=0; i<nFaceCount; i++)
	{
		t = faces[2][i];
		flags[0] = FALSE;
		flags[1] = FALSE;
		for(int j=0; j<3; j++)
		{
			l = 3*t+j;
			v[j].x = pVertices[pIndices[l]].vertex.x;
			v[j].y = pVertices[pIndices[l]].vertex.y;
			v[j].z = pVertices[pIndices[l]].vertex.z;
			if(cz >= v[j].z)
				flags[0] = TRUE;
			else
				flags[1] = TRUE;
		}
		if(flags[0])
		{
			faces[0][n0] = t;
			n0++;
		}
		if(flags[1])
		{
			faces[1][n1] = i;
			n1++;
		}
	}
	*FaceCount0 = n0;
	*FaceCount1 = n1;
}
/*
input: pFaces, nFaceCount, cx - cluster to partition
output: pFaces0, pFaces1, FaceCount0, FaceCount1 - two clusters partitioned
*/
void CAABBTree::PartitionByYZ(int* pFaces0, int* pFaces1, int* FaceCount0, int* FaceCount1,
							  int* pFaces, int nFaceCount, float cx)
{
	int* faces[3];
	faces[0] = pFaces0;
	faces[1] = pFaces1;
	faces[2] = pFaces;
	COM_VERTEX* pVertices = m_pComMesh->pVertices;
	int* pIndices = m_pComMesh->pIndices;
	VECTOR3 v[3];
	int t=0;
	DWORD l=0;
	BOOL flags[2];
	int n0,n1;
	n0 = n1 = 0;
	for(int i=0; i<nFaceCount; i++)
	{
		t= faces[2][i];
		flags[0] = FALSE;
		flags[1] = FALSE;
		for(int j=0; j<3; j++)
		{
			l = 3*t+j;
			v[j].x = pVertices[pIndices[l]].vertex.x;
			v[j].y = pVertices[pIndices[l]].vertex.y;
			v[j].z = pVertices[pIndices[l]].vertex.z;
			if(cx > v[j].x)
				flags[0] = TRUE;
			else
				flags[1] = TRUE;
		}
		if(flags[0])
		{
			faces[0][n0] = t;
			n0++;
		}
		if(flags[1])
		{
			faces[1][n1] = t;
			n1++;
		}
	}
	*FaceCount0 = n0;
	*FaceCount1 = n1;
}

void CAABBTree::PartitionByZX(int* pFaces0, int* pFaces1, int* FaceCount0, int* FaceCount1,
							  int* pFaces, int nFaceCount, float cy)
{
	int* faces[3];
	faces[0] = pFaces0;
	faces[1] = pFaces1;
	faces[2] = pFaces;
	COM_VERTEX* pVertices = m_pComMesh->pVertices;
	int* pIndices = m_pComMesh->pIndices;
	VECTOR3 v[3];
	int t=0;
	DWORD l=0;
	BOOL flags[2];
	int n0,n1;
	n0 = n1 = 0;
	for(int i=0; i<nFaceCount; i++)
	{
		t= faces[2][i];
		flags[0] = FALSE;
		flags[1] = FALSE;
		for(int j=0; j<3; j++)
		{
			l = 3*t+j;
			v[j].x = pVertices[pIndices[l]].vertex.x;
			v[j].y = pVertices[pIndices[l]].vertex.y;
			v[j].z = pVertices[pIndices[l]].vertex.z;
			if(cy > v[j].y)
				flags[0] = TRUE;
			else
				flags[1] = TRUE;
		}
		if(flags[0])
		{
			faces[0][n0] = t;
			n0++;
		}
		if(flags[1])
		{
			faces[1][n1] = t;
			n1++;
		}
	}
	*FaceCount0 = n0;
	*FaceCount1 = n1;
}
/*
partition parent cluster in to two clusters
*/
BOOL CAABBTree::CreatingChilds(NODE** ppChild1, NODE** ppChild2, NODE* parent)
{
	int intFaceCount = parent->intFaceCount;
	if(intFaceCount < 200) 
		return FALSE;
	VECTOR3 vMin, vMax;
	float  Dx,Dy,Dz;
	vMin.x = parent->vMin.x;
	vMin.y = parent->vMin.y;
	vMin.z = parent->vMin.z;
	vMax.x = parent->vMax.x;
	vMax.y = parent->vMax.y;
	vMax.z = parent->vMax.z;
	Dx = vMax.x - vMin.x;
	Dy = vMax.y - vMin.y;
	Dz = vMax.z - vMin.z;
	float fMax = Dx;
	if( fMax < Dy ) fMax = Dy;
	if( fMax < Dz ) fMax = Dz;
	
	VECTOR3 v[3];
	int* ppTempFaces[2];
	ppTempFaces[0] = (int*)calloc(intFaceCount,sizeof(int));
	ppTempFaces[1] = (int*)calloc(intFaceCount,sizeof(int));
	float cx,cy,cz;
	cx = (vMax.x + vMin.x) /2;
	cy = (vMax.y + vMin.y) /2;
	cz = (vMax.z + vMin.z) /2;

	int n0,n1;
	n0 = n1 = 0;
	if(fMax==Dx)
	{
		PartitionByXY(ppTempFaces[0], ppTempFaces[1], &n0, &n1, parent->pFaces, intFaceCount, cz);
	}
	if(fMax==Dy)
	{
		PartitionByZX(ppTempFaces[0], ppTempFaces[1], &n0, &n1, parent->pFaces, intFaceCount, cy);
	}
	if(fMax==Dz)
	{
		PartitionByYZ(ppTempFaces[0], ppTempFaces[1], &n0, &n1, parent->pFaces, intFaceCount, cx);
	}

	NODE* pNodes[2];
	pNodes[0] = new NODE;
	pNodes[0]->intFaceCount = n0;
	pNodes[0]->pFaces = (int*)calloc(n0,sizeof(int));

	pNodes[1] = new NODE;
	pNodes[1]->intFaceCount = n1;
	pNodes[1]->pFaces = (int*)calloc(n1,sizeof(int));

	int t=0;
	DWORD l=0;
	int* pIndices = m_pComMesh->pIndices;
	COM_VERTEX* pVertices = m_pComMesh->pVertices;
	for(int k=0; k<2; k++)
	{
		for(int i=0; i<3; i++)
		{
			l = pIndices[3*ppTempFaces[k][0]+i];
			vMax.x = vMin.x = pVertices[l].vertex.x;
			vMax.y = vMin.y = pVertices[l].vertex.y;
			vMax.z = vMin.z = pVertices[l].vertex.z;
		}
		for(int i=0; i<pNodes[k]->intFaceCount; i++)
		{
			t = pNodes[k]->pFaces[i] = ppTempFaces[k][i];
			for(int j=0; j<3; j++)
			{
				l = pIndices[3*t+j];
				v[j].x = pVertices[l].vertex.x;
				v[j].y = pVertices[l].vertex.y;
				v[j].z = pVertices[l].vertex.z;
				if(vMax.x < v[j].x) vMax.x = v[j].x;
				if(vMax.y < v[j].y) vMax.y = v[j].y;
				if(vMax.z < v[j].x) vMax.z = v[j].z;
				if(vMin.x > v[j].x) vMin.x = v[j].x;
				if(vMin.y > v[j].y) vMin.y = v[j].y;
				if(vMin.z > v[j].x) vMin.z = v[j].z;
			}
		}
		pNodes[k]->vMax.x = vMax.x;
		pNodes[k]->vMax.y = vMax.y;
		pNodes[k]->vMax.z = vMax.z;
		pNodes[k]->vMin.x = vMin.x;
		pNodes[k]->vMin.y = vMin.y;
		pNodes[k]->vMin.z = vMin.z;
		parent->child[k] = pNodes[k];
		free(ppTempFaces[k]);
	}
	*ppChild1 = pNodes[0];
	*ppChild2 = pNodes[1];
	free(parent->pFaces);
	return TRUE;
}

void CAABBTree::ConstructingTree(COM_MESH* pComMesh)
{
	if (pComMesh == NULL || pComMesh->pVertices == NULL || pComMesh->pIndices == NULL)
		return;

	RemoveTree();
	m_pComMesh = pComMesh;
	//뿌리마디초기화
	m_pRootNode = new NODE;
	m_pRootNode->intFaceCount = m_pComMesh->intFaceCount;
	m_pRootNode->pFaces = (int*)calloc(m_pComMesh->intFaceCount,sizeof(int));
	for(int i=0; i<m_pComMesh->intFaceCount; i++)
	{
		m_pRootNode->pFaces[i] = i;
	}
	m_pRootNode->vMin.x = m_pComMesh->vec3Min.x;
	m_pRootNode->vMin.y = m_pComMesh->vec3Min.y;
	m_pRootNode->vMin.z = m_pComMesh->vec3Min.z;

	m_pRootNode->vMax.x = m_pComMesh->vec3Max.x;
	m_pRootNode->vMax.y = m_pComMesh->vec3Max.y;
	m_pRootNode->vMax.z = m_pComMesh->vec3Max.z;
	m_pRootNode->child[0] = NULL;
	m_pRootNode->child[1] = NULL;
	
	//Open목록초기화
	LIST* pFirstList = new LIST;
	LIST* pLastList = pFirstList; 
	LIST* next;
	pFirstList->next = NULL;
	pFirstList->pNode = m_pRootNode;
	NODE* ppChilds[2];
	NODE* pCurNode;
	int nNodeCount = 1;
	while(pFirstList)
	{
		pCurNode = pFirstList->pNode;
		pCurNode->child[0] = NULL;
		pCurNode->child[1] = NULL;
		//if(CreatingChilds(&ppChilds[0], &ppChilds[1], pCurNode))
		if(GeneratingNodes(&ppChilds[0], &ppChilds[1], pCurNode))//pCurNode의 cluster를 삭제
		{
			pCurNode->child[0] = ppChilds[0];
			pCurNode->child[1] = ppChilds[1];
			next = new LIST;
			next->pNode = ppChilds[0];
			next->next = NULL;
			pLastList->next = next;
			pLastList = next;

			next = new LIST;
			next->pNode = ppChilds[1];
			next->next = NULL;
			pLastList->next = next;
			pLastList = next;
			nNodeCount += 2;
		}
		next = pFirstList->next;
		delete pFirstList;
		pFirstList = next;
	}
}

int CAABBTree::IntersectAABBTree(VECTOR3* vRayPos, VECTOR3* vRayDir, int* pIndices)
{
	return 0;
}


/*
2014.08.17
*/
int CAABBTree::GetClustersXY(NODE* pNodes, int* intNodeCount, VECTOR3* vRayPos, VECTOR3* vRayDir)
{
	
	return 0;
}
/*
두개의 자식마디들을 생성하고 생성되는 경우 현재마디의 클라스터를 삭제   
*/
BOOL CAABBTree::GeneratingNodes(NODE** ppNode1, NODE** ppNode2, NODE* pParentNode)
{
	NODE* parent = pParentNode;
	float dx = parent->vMax.x - parent->vMin.x; 
	float dy = parent->vMax.y - parent->vMin.y;
	float delta = m_pComMesh->delta;
	if(dx < delta && dy < delta) return FALSE;
	int nCurFaces = parent->intFaceCount;
	if(nCurFaces==0) return FALSE;//2014.08.19
	int* pCurFaces = parent->pFaces;
	int* pTemp[2];
	int  nFaceCount[2];
	pTemp[0] = (int*)calloc(nCurFaces,sizeof(int));
	pTemp[1] = (int*)calloc(nCurFaces,sizeof(int));
	VECTOR3 vMin, vMax;
	vMin.x = parent->vMin.x;
	vMin.y = parent->vMin.y;
	vMin.z = parent->vMin.z;
	vMax.x = parent->vMax.x;
	vMax.y = parent->vMax.y;
	vMax.z = parent->vMax.z;
	float Dx = vMax.x - vMin.x;
	float Dy = vMax.y - vMin.y;
	VECTOR3 vxMax[2];
	VECTOR3 vxMin[2];
	if(Dx < Dy)
	{
		float cy = (vMax.y + vMin.y)/2;
		PartitionByZX(pTemp[0], pTemp[1], &nFaceCount[0], &nFaceCount[1], pCurFaces, nCurFaces, cy);
		vxMax[0].x = vMax.x;
		vxMax[0].y = cy;
		vxMin[0].x = vMin.x;
		vxMin[0].y = vMin.y;

		vxMax[1].x = vMax.x;
		vxMax[1].y = vMax.y;
		vxMin[1].x = vMin.x;
		vxMin[1].y = cy;
	}
	else
	{
		float cx = (vMax.x + vMin.x)/2;
		PartitionByYZ(pTemp[0], pTemp[1], &nFaceCount[0], &nFaceCount[1], pCurFaces, nCurFaces, cx);
		vxMax[0].x = cx;
		vxMax[0].y = vMax.y;
		vxMin[0].x = vMin.x;
		vxMin[0].y = vMin.y;

		vxMax[1].x = vMax.x;
		vxMax[1].y = vMax.y;
		vxMin[1].x = cx;
		vxMin[1].y = vMin.y;
	}
	NODE* pChildNode[2];
	pChildNode[0] = new NODE;
	pChildNode[0]->intFaceCount = nFaceCount[0];
	pChildNode[0]->pFaces = (int*)calloc(nFaceCount[0], sizeof(int));
	pChildNode[0]->child[0] = NULL;
	pChildNode[0]->child[1] = NULL;
	pChildNode[1] = new NODE;
	pChildNode[1]->intFaceCount = nFaceCount[1];
	pChildNode[1]->pFaces = (int*)calloc(nFaceCount[1], sizeof(int));
	pChildNode[1]->child[0] = NULL;
	pChildNode[1]->child[1] = NULL;
	int l=0;
	COM_VERTEX* pVertices = m_pComMesh->pVertices;
	int* pIndices = m_pComMesh->pIndices;
	for(int i=0; i<2; i++)
	{
		l = 3*pTemp[i][0];	
		for(int j=0; j<nFaceCount[i]; j++)
		{
			pChildNode[i]->pFaces[j] = pTemp[i][j];
		}
		pChildNode[i]->vMax.x = vxMax[i].x;
		pChildNode[i]->vMax.y = vxMax[i].y;
		pChildNode[i]->vMin.x = vxMin[i].x;
		pChildNode[i]->vMin.y = vxMin[i].y;
		free(pTemp[i]);
	}
	free(pParentNode->pFaces);
	pParentNode->pFaces = NULL;
	*ppNode1 = pChildNode[0];
	*ppNode2 = pChildNode[1];
	return TRUE;
}

void CAABBTree::RemoveTree()
{
	if(!m_pRootNode) return;
	LIST* firstList = new LIST;
	LIST* lastList = new LIST;
	firstList->pNode = m_pRootNode;
	firstList->next = NULL;
	lastList = firstList;
	NODE* node;
	LIST* next;
	while(firstList)
	{
		node = firstList->pNode;
		if(node->pFaces)
		{
			free(node->pFaces);
			node->pFaces = NULL;
		}
		node = lastList->pNode;
		if(node->child[0])
		{
			next = new LIST;
			next->pNode = node->child[0];
			next->next = NULL;
			lastList->next = next;
			lastList = next;
		}
		
		if(node->child[1])
		{
			next = new LIST;
			next->pNode = node->child[1];
			next->next = NULL;
			lastList->next = next;
			lastList = next;
		}
		next = firstList->next;
		delete firstList; 
		firstList = next;
	}
}

/*
input
vRayPos, vRayDir
output
nFaceCount, pFace
*/
BOOL CAABBTree::GetFaceCluster(int* nFaceCount, int** ppFaces, VECTOR3* vRayPos, VECTOR3* vRayDir)
{
	float x = vRayPos->x;
	float y = vRayPos->y;
	if( x>=m_pComMesh->vec3Max.x || m_pComMesh->vec3Min.x >= x)	return FALSE;
	if( y>=m_pComMesh->vec3Max.y || m_pComMesh->vec3Min.y >= y)	return FALSE;
	NODE* pNode = m_pRootNode;
	NODE* child[2];

	if (pNode == NULL)
		return FALSE;

	//while(pNode->pFaces==NULL)
	while(pNode->child[0]!=NULL)//2014.08.19
	{
		for(int i=0; i<2; i++)
		{
			child[i] = pNode->child[i];
			if(child[i]->vMax.x >= x && x >= child[i]->vMin.x)
			{
				if(child[i]->vMax.y >= y && y >= child[i]->vMin.y)
				{
					pNode = child[i];
					break;
				}
			}
		}
	}
	*ppFaces = pNode->pFaces;
	*nFaceCount = pNode->intFaceCount;
	return TRUE;
}