#pragma once
#include "stdafx.h"

class CMeshModel
{
public:
	CMeshModel(void);
	~CMeshModel(void);
//Data
protected:
	HPALETTE	m_hPalette, m_hOldPalette;
	COM_MESH*   m_pComMesh;
	float		m_fAmbient;
	float		m_fDiffuse;
//implementation
public:
	void InitOpenGL(HDC hDC);
	void InitializeMeshObject(COM_MESH* pComMesh);
	void InitScene();
	void DrawScene(float fScale, float fAngleX, float fAngleY, float fAngleZ);
	void DrawScene01(float fScale, float fAngleX, float fAngleY, float fAngleZ);
	void SetLightVals(float fAmbient, float fDiffuse);
	void GetLightVals(float* fAmbient, float* fDiffuse);
protected:
	BOOL bSetupPixelFormat(HDC hDC);
	unsigned char ComponentFromIndex(int i, UINT nbits, UINT shift);
	void CreateRGBPalette(HDC hDC);
	void SetCamera(float nearPlane, float farPlane, VECTOR3* vEyePos, VECTOR3* vLookAtPos, VECTOR3* vUp);
	void SetMaterialAttributes(PCOM_MATINFO pMatAttrib);
	void SetLight();
};

