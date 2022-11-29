#pragma once
#include "stdafx.h"

class CMeshModel
{
public:
	CMeshModel(void);
	~CMeshModel(void);
//Data
protected:
	HDC			m_hDrawDC;	//DC for Draw
	HGLRC		m_hCurRC;	//Current GL Context
	BOOL		m_bWndDraw;	//Drawing to Window
	HPALETTE	m_hPalette, m_hOldPalette;

	COM_MESH*   m_pComMesh;
	COLOR3F		m_fBackColor;
	float		m_fAmbient;
	float		m_fDiffuse;
//implementation
public:
	void InitOpenGL(HDC hDC, BOOL bWndDraw = TRUE);
	void CloseOpenGL();

	void InitializeMeshObject(COM_MESH* pComMesh);
	void InitScene();
	void DrawScene(float fScale, float fAngleX, float fAngleY, float fAngleZ);
	void DrawScene01(float fScale, float fAngleX, float fAngleY, float fAngleZ);
	void SetLightVals(float fAmbient, float fDiffuse);
	void GetLightVals(float* fAmbient, float* fDiffuse);
	void SetBackColor(DWORD dwColor);

protected:
	void CreateRGBPalette(HDC hDC);
	void SetCamera(float nearPlane, float farPlane, VECTOR3* vEyePos, VECTOR3* vLookAtPos, VECTOR3* vUp);
	void SetMaterialAttributes(PCOM_MATINFO pMatAttrib);
	void SetLight();
};

