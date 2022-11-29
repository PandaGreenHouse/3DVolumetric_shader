#pragma once
#include "ModelFile.h"
#include "MyArray.h"

class CObjFile : public CModelFile
{
public:
	CObjFile(void);
	~CObjFile(void);

	static BOOL IsModelFile(LPCTSTR lpszFilePath);

	BOOL Open(LPCTSTR lpszFilePath, COM_MESH* pComMesh);
	void Close();
	COM_MESH* GetMesh();

private:
	COM_MESH    m_StrComMesh;

	BOOL ConstructingComMesh();
	BOOL NewComMeshBuffer(int nObjects, int nFaces, int nVerts);
	void FreeComMeshBuffer();
};

