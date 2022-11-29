#pragma once
#include "ModelFile.h"

class CVrmlFile : public CModelFile
{
public:
	CVrmlFile(void);
	~CVrmlFile(void);

	static BOOL IsModelFile(LPCTSTR lpszFilePath);

	BOOL Open(LPCTSTR lpszFilePath, COM_MESH* pComMesh);
	void Close();
	COM_MESH* GetMesh();

private:
	COM_MESH    m_StrComMesh;

	BOOL ConstructingComMesh();
};

