#pragma once

#include "MyStructure.h"

class CModelFile
{
public:
	CModelFile(void);
	~CModelFile(void);

	virtual BOOL Open(LPCTSTR lpszFilePath, PCOM_MESH pComMesh);
	virtual void Close();
	virtual PCOM_MESH GetMesh();
	void InitMesh(PCOM_MESH pMesh);
};

CModelFile* CreateModelFile(LPCTSTR lpszFilePath);
void ReleaseModelFile(CModelFile** pFile);
