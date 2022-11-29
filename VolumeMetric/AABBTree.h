#pragma once
struct NODE
{
	VECTOR3 vMin;
	VECTOR3 vMax;
	int*	pFaces;
	int		intFaceCount;
	NODE*	child[2];
};

class CAABBTree
{
public:
	CAABBTree(void);
	~CAABBTree(void);
	void ConstructingTree(COM_MESH* pComMesh);
	BOOL CreatingChilds(NODE** ppChild1, NODE** ppChild2, NODE* parent);
	int IntersectAABBTree(VECTOR3* vRayPos, VECTOR3* vRayDir, int* pIndices);
	int GetClustersXY(NODE* pNodes, int* intNodeCount, VECTOR3* vRayPos, VECTOR3* vRayDir);
	BOOL GetFaceCluster(int* nFaceCount, int** ppFaces, VECTOR3* vRayPos, VECTOR3* vRayDir);
//Data
protected:
	COM_MESH* m_pComMesh;
	NODE* m_pRootNode;
//Implementation
protected:
void PartitionByXY(int* pIntFaces0, int* pIntFaces1, int* FaceCount0, int* FaceCount1,
							  int* pSourceFaces, int nFaceCount, float cz);
void PartitionByYZ(int* pIntFaces0, int* pIntFaces1, int* FaceCount0, int* FaceCount1,
							  int* pSourceFaces, int nFaceCount, float cx);
void PartitionByZX(int* pIntFaces0, int* pIntFaces1, int* FaceCount0, int* FaceCount1,
							  int* pSourceFaces, int nFaceCount, float cy);
BOOL GeneratingNodes(NODE** ppNode1, NODE** ppNode2, NODE* pParentNode);
void RemoveTree();
};

