#pragma once
#include "ModelFile.h"
#include "MyArray.h"

class C3dsFile : public CModelFile
{
public:
	C3dsFile(void);
	~C3dsFile(void);

	static BOOL IsModelFile(LPCTSTR lpszFilePath);

	BOOL Open(LPCTSTR lpszFilePath, COM_MESH* pComMesh);
	void Close();
	COM_MESH* GetMesh();

private:
	COM_MESH    m_StrComMesh;

	BOOL LoadModel(DWORD dwLen);
	BOOL ConstructingComMesh();

	BOOL NewComMeshBuffer(int nObjects, int nFaces, int nVerts);
	void FreeComMeshBuffer();
};

