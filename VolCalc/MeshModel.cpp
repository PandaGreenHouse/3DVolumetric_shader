#include "stdafx.h"
#include "gl/gl.h"
#include "gl/glu.h"
#include "MeshModel.h"



CMeshModel::CMeshModel(void)
{
	m_hDrawDC	= NULL;
	m_hCurRC	= NULL;
	m_bWndDraw	= FALSE;

	m_pComMesh	= NULL;
	m_fAmbient	= m_fDiffuse = 0.25f;
	m_fBackColor.r = 0.0f;
	m_fBackColor.g = 0.65f;
	m_fBackColor.b = 0.8f;
}


CMeshModel::~CMeshModel(void)
{
	CloseOpenGL();
}

void CMeshModel::InitializeMeshObject(COM_MESH* pComMesh)
{
	m_pComMesh = pComMesh;
	InitScene();
}

/*openGL 초기화*/
BOOL IsPixelFormatSet(HDC hDC, BOOL bWndDraw)
{
	PIXELFORMATDESCRIPTOR pfd;
	HBITMAP	hbmp;
	BITMAP	bmInfo;
	int		nFormat;

	//Get Bitmap Info
	hbmp = (HBITMAP)::GetCurrentObject(hDC, OBJ_BITMAP);
	GetObject(hbmp, sizeof(BITMAP), &bmInfo);

	//Initialize PFD
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize		= sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion	= 1;
	pfd.iPixelType	= PFD_TYPE_RGBA;
	pfd.cColorBits	= bmInfo.bmBitsPixel;
	pfd.cDepthBits	= 32;
	pfd.iLayerType	= PFD_MAIN_PLANE;
	if (bWndDraw)
		pfd.dwFlags	= PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |	PFD_DOUBLEBUFFER;
	else
		pfd.dwFlags	= PFD_DRAW_TO_BITMAP | PFD_SUPPORT_OPENGL | PFD_SUPPORT_GDI;

	nFormat = ChoosePixelFormat(hDC, &pfd);
	if (nFormat < 1)
		return FALSE;
	if (!SetPixelFormat(hDC, nFormat, &pfd))
		return FALSE;

	return TRUE;
}

unsigned char threeto8[8] =
{
	0, 0111>>1, 0222>>1, 0333>>1, 0444>>1, 0555>>1, 0666>>1, 0377
};

unsigned char twoto8[4] =
{
	0, 0x55, 0xaa, 0xff
};

unsigned char oneto8[2] =
{
	0, 255
};

static int defaultOverride[13] =
{
	0, 3, 24, 27, 64, 67, 88, 173, 181, 236, 247, 164, 91
};

static PALETTEENTRY defaultPalEntry[20] =
{
	{ 0,   0,   0,    0 },
	{ 0x80,0,   0,    0 },
	{ 0,   0x80,0,    0 },
	{ 0x80,0x80,0,    0 },
	{ 0,   0,   0x80, 0 },
	{ 0x80,0,   0x80, 0 },
	{ 0,   0x80,0x80, 0 },
	{ 0xC0,0xC0,0xC0, 0 },

	{ 192, 220, 192,  0 },
	{ 166, 202, 240,  0 },
	{ 255, 251, 240,  0 },
	{ 160, 160, 164,  0 },

	{ 0x80,0x80,0x80, 0 },
	{ 0xFF,0,   0,    0 },
	{ 0,   0xFF,0,    0 },
	{ 0xFF,0xFF,0,    0 },
	{ 0,   0,   0xFF, 0 },
	{ 0xFF,0,   0xFF, 0 },
	{ 0,   0xFF,0xFF, 0 },
	{ 0xFF,0xFF,0xFF, 0 }
};

BYTE ComponentFromIndex(int i, UINT nbits, UINT shift)
{
	BYTE val;

	val = (BYTE) (i >> shift);
	switch (nbits)
	{
	case 1:
		val &= 0x1;
		return oneto8[val];
	case 2:
		val &= 0x3;
		return twoto8[val];
	case 3:
		val &= 0x7;
		return threeto8[val];
	}

	return 0;
}

void CMeshModel::CreateRGBPalette(HDC hDC)
{
	PIXELFORMATDESCRIPTOR pfd;
	LOGPALETTE *pPal;
	int n, i;

	n = ::GetPixelFormat(hDC);
	::DescribePixelFormat(hDC, n, sizeof(pfd), &pfd);

	if (pfd.dwFlags & PFD_NEED_PALETTE)
	{
		n = 1 << pfd.cColorBits;
		pPal = (PLOGPALETTE) new char[sizeof(LOGPALETTE) + n * sizeof(PALETTEENTRY)];
		if (pPal)
		{
			pPal->palVersion = 0x300;
			pPal->palNumEntries = n;
			for (i=0; i<n; i++)
			{
				pPal->palPalEntry[i].peRed	 = ComponentFromIndex(i, pfd.cRedBits, pfd.cRedShift);
				pPal->palPalEntry[i].peGreen = ComponentFromIndex(i, pfd.cGreenBits, pfd.cGreenShift);
				pPal->palPalEntry[i].peBlue	 = ComponentFromIndex(i, pfd.cBlueBits, pfd.cBlueShift);
				pPal->palPalEntry[i].peFlags = 0;
			}

			/* fix up the palette to include the default GDI palette */
			if ((pfd.cColorBits == 8)                           &&
				(pfd.cRedBits   == 3) && (pfd.cRedShift   == 0) &&
				(pfd.cGreenBits == 3) && (pfd.cGreenShift == 3) &&
				(pfd.cBlueBits  == 2) && (pfd.cBlueShift  == 6))
			{
				for (i = 1 ; i <= 12 ; i++)
					pPal->palPalEntry[defaultOverride[i]] = defaultPalEntry[i];
			}

			m_hPalette = ::CreatePalette(pPal);
			delete [] pPal;
			m_hOldPalette = ::SelectPalette(hDC, m_hPalette, FALSE);
			::RealizePalette(hDC);
		}
	}
}

void CMeshModel::InitOpenGL(HDC hDC, BOOL bWndDraw)
{
	if (!IsPixelFormatSet(hDC, bWndDraw))
		return;

	m_bWndDraw	= bWndDraw;
	m_hDrawDC	= hDC;
	CreateRGBPalette(hDC);
	m_hCurRC = wglCreateContext(hDC);
	wglMakeCurrent(hDC, m_hCurRC);

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
}

void CMeshModel::CloseOpenGL()
{
	if (m_hCurRC)
	{
		if (m_hDrawDC)
			wglMakeCurrent(m_hDrawDC, NULL);
		wglDeleteContext(m_hCurRC);
		m_hCurRC = NULL;
	}
}

void CMeshModel::InitScene()
{
	float fNearPlane, fFarPlane;
	VECTOR3 vEyePos, vLookAt, vUp;
	fNearPlane = 1.0f;
	fFarPlane = 10000.0f*m_pComMesh->fMax;	//5
	vEyePos.x = 0.0f;
	vEyePos.y = 0.0f;
	vEyePos.z = -1.8f*m_pComMesh->fMax;
	vLookAt.x = 0.0f;
	vLookAt.y = 0.0f;
	vLookAt.z = 0.0f;
	vUp.x = 0.0f;
	vUp.y = 1.0f;
	vUp.z = 0.0f;
	SetCamera(fNearPlane,fFarPlane,&vEyePos,&vLookAt,&vUp);	
	//SetMaterialAttributes(&m_pComMesh->pObjects[0].strMat);
    //SetLight();
}

void CMeshModel::DrawScene(float fScale, float fAngleX, float fAngleY, float fAngleZ)
{
	if (m_pComMesh == NULL || m_pComMesh->pVertices == NULL)
		return;

	COM_VERTEX* pVertices = m_pComMesh->pVertices;
	int*		pIndices = m_pComMesh->pIndices;
	DWORD		dwFaces = m_pComMesh->intFaceCount;
	DWORD		dwVxCount = m_pComMesh->intVertexCount;
	FLOAT		r, g, b;
	DWORD		k = 0, m;
	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();
	glScalef (fScale, fScale, fScale);      /* modeling transformation */ 
	//glTranslatef(0.0f, 0.0f, -m_fRadius);
	glRotatef(fAngleX, 1.0f, 0.0f, 0.0f);
	glRotatef(fAngleY, 0.0f, 1.0f, 0.0f);
	glRotatef(fAngleZ, 0.0f, 0.0f, 1.0f);

	for(DWORD i=0; i<dwFaces; i++)
	{
		glBegin(GL_TRIANGLES);
		for(int j=0; j<3; j++)
		{
			m = k;
			if (pIndices)
				m = pIndices[k];
			r = pVertices[m].colorRGB.r;
			g = pVertices[m].colorRGB.g;
			b = pVertices[m].colorRGB.b;
			glColor3f(r, g, b);
			glNormal3f(pVertices[m].vec3Normal.x,pVertices[m].vec3Normal.y,pVertices[m].vec3Normal.z);
			glVertex3f(pVertices[m].vertex.x, pVertices[m].vertex.y, pVertices[m].vertex.z);
			k++;
		}
		glEnd();
	}
	glPopMatrix();
	glFinish();
	SwapBuffers(wglGetCurrentDC());
}

void CMeshModel::DrawScene01(float fScale, float fAngleX, float fAngleY, float fAngleZ)
{
	if (m_pComMesh == NULL || m_pComMesh->pVertices == NULL)
		return;

	PCOM_OBJECT	pObject;
	PCOM_VERTEX pVertices = m_pComMesh->pVertices;
	int*		pIndices = m_pComMesh->pIndices;
	int			k=0, m, i, nFaceIdx, nVertIdx;	//Loop Variables
	float		cx,cy,cz;
	
	glClearColor(m_fBackColor.r, m_fBackColor.g, m_fBackColor.b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SetLight();
	cx = -0.5f*(m_pComMesh->vec3Max.x + m_pComMesh->vec3Min.x);
	cy = -0.5f*(m_pComMesh->vec3Max.y + m_pComMesh->vec3Min.y);
	cz = -0.5f*(m_pComMesh->vec3Max.z + m_pComMesh->vec3Min.z);
	glPushMatrix();
	glScalef (fScale, fScale, fScale);      /* modeling transformation */ 
	glTranslatef(cx, cy, cz);
	glRotatef(fAngleX, 1.0f, 0.0f, 0.0f);
	glRotatef(fAngleY, 0.0f, 1.0f, 0.0f);
	glRotatef(fAngleZ, 0.0f, 0.0f, 1.0f);

	pObject = m_pComMesh->pObjects;
	for(i = 0; i < m_pComMesh->intObjectCount; i++, pObject++)
	{
		SetMaterialAttributes(&(pObject->strMat));
		glBegin(GL_TRIANGLES);
		nFaceIdx = 3 * pObject->nStartFace;
		for (m = 0; m < pObject->nFaceCount; m++)
		{
			for (k = 0; k < 3; k++, nFaceIdx++)
			{
				nVertIdx = pIndices[nFaceIdx];
				glNormal3f(pVertices[nVertIdx].vec3Normal.x,pVertices[nVertIdx].vec3Normal.y,pVertices[nVertIdx].vec3Normal.z);
				glVertex3f(pVertices[nVertIdx].vertex.x, pVertices[nVertIdx].vertex.y, pVertices[nVertIdx].vertex.z);
			}
		}
		glEnd();
	}
	glPopMatrix();
	glFinish();
	if (m_bWndDraw)
		SwapBuffers(wglGetCurrentDC());
}

void CMeshModel::SetCamera(float fNearPlane, float fFarPlane, VECTOR3* vEyePos, VECTOR3* vLookAtPos, VECTOR3* vUp)
{
	float fAspect = 1.0f;
	/*float fNearPlane = 3.0f;
	float fFarPlane = fNearPlane + 20*m_pComMesh->Dz;
	float fMaxObjSize = 3.0f;
	//m_fRadius = fNearPlane + fMaxObjSize / 2.0f;*/
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, fAspect, fNearPlane, fFarPlane);
	glMatrixMode(GL_MODELVIEW);
	/* viewing transformation  */
//	GLfloat fz = 5.0f*(GLfloat)m_pComMesh->Dz;
	gluLookAt (vEyePos->x, vEyePos->y, vEyePos->z, 0.0, 0.0, 0.0, vUp->x, vUp->y, vUp->z);
}

void CMeshModel::SetMaterialAttributes(PCOM_MATINFO pMatAttrib)
{
	float matSpecular[] = {0.6f,0.6f,0.6f,1.0f};
	glMaterialfv( GL_FRONT, GL_AMBIENT, pMatAttrib->matAmbient);//matAmbient );       
	glMaterialfv( GL_FRONT, GL_DIFFUSE, pMatAttrib->matDiffuse);//matDiff );
	glMaterialfv(GL_FRONT, GL_SPECULAR, pMatAttrib->matSpecular);//specular);
	glMaterialf(GL_FRONT, GL_SHININESS, pMatAttrib->fShininess);//shine);*/
}

void CMeshModel::SetLight()
{
	glShadeModel( GL_SMOOTH );                              // 매끄러운 세이딩 사용
    glEnable( GL_DEPTH_TEST );                              // 가려진 면 제거
    //glEnable( GL_CULL_FACE );                               // 후면 제거
    glFrontFace( GL_CCW );                                  // 다각형을 반시계방향으로 감는다.

    glEnable( GL_LIGHTING );                                // 조명 활성화
	// LIGHT0 설정
	// 조명값들 
	float ambientLight[] = { m_fAmbient, m_fAmbient, m_fAmbient, 1.0f };         // 주변광
	float diffuseLight[] = { m_fDiffuse, m_fDiffuse, m_fDiffuse, 1.0f };      // 분산광
	float specularLight[] = {0.60f, 0.6f, 0.6f, 1.0f};		//전반사광
	float lightPosition0[] = { 0.0f, 2000.0f*m_pComMesh->Dy, 0.0f, 0.0f }; // 광원위치
	float lightPosition1[] = { 0.0f, -2000.0f*m_pComMesh->Dy, 0.0f, 0.0f }; // 광원위치
	float lightPosition2[] = { 2000.0f*m_pComMesh->Dx, 0.0f, 0.0f, 0.0f }; // 광원위치
	float lightPosition3[] = { -2000.0f*m_pComMesh->Dx, 0.0f, 0.0f, 0.0f }; // 광원위치
	float lightPosition4[] = { 2000.0f*m_pComMesh->vec3Min.x, 2000.0f*m_pComMesh->vec3Min.y, 2000.0f*m_pComMesh->vec3Min.z, 0.0f }; // 광원위치
	float lightPosition5[] = { 2000.0f*m_pComMesh->vec3Max.x, 2000.0f*m_pComMesh->vec3Max.y, 2000.0f*m_pComMesh->vec3Max.z, 0.0f }; // 광원위치
    glLightfv( GL_LIGHT0, GL_AMBIENT, ambientLight );       // 주변광 성분 설정
    glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseLight );       // 분산광 성분 설정
	glLightfv( GL_LIGHT0, GL_SPECULAR, specularLight );       // 전반사광 성분 설정
    glLightfv( GL_LIGHT0, GL_POSITION, lightPosition0 );     // 광원 위치 설정

	glLightfv( GL_LIGHT1, GL_AMBIENT, ambientLight );       // 주변광 성분 설정
    glLightfv( GL_LIGHT1, GL_DIFFUSE, diffuseLight );       // 분산광 성분 설정
	glLightfv( GL_LIGHT1, GL_SPECULAR, specularLight );       // 전반사광 성분 설정
    glLightfv( GL_LIGHT1, GL_POSITION, lightPosition1 );     // 광원 위치 설정

	glLightfv( GL_LIGHT2, GL_AMBIENT, ambientLight );       // 주변광 성분 설정
    glLightfv( GL_LIGHT2, GL_DIFFUSE, diffuseLight );       // 분산광 성분 설정
	glLightfv( GL_LIGHT2, GL_SPECULAR, specularLight );       // 전반사광 성분 설정
    glLightfv( GL_LIGHT2, GL_POSITION, lightPosition2 );     // 광원 위치 설정

	glLightfv( GL_LIGHT3, GL_AMBIENT, ambientLight );       // 주변광 성분 설정
    glLightfv( GL_LIGHT3, GL_DIFFUSE, diffuseLight );       // 분산광 성분 설정
	glLightfv( GL_LIGHT3, GL_SPECULAR, specularLight );       // 전반사광 성분 설정
    glLightfv( GL_LIGHT3, GL_POSITION, lightPosition3 );     // 광원 위치 설정
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	// LIGHT0을 켠다.
    glEnable( GL_LIGHT0 );
	glEnable( GL_LIGHT1 );
	glEnable( GL_LIGHT2 );
	glEnable( GL_LIGHT3 );
	glEnable(GL_NORMALIZE);
}

void CMeshModel::SetLightVals(float fAmbient, float fDiffuse)
{
	m_fAmbient = fAmbient;
	m_fDiffuse = fDiffuse;
}

void CMeshModel::GetLightVals(float* fAmbient, float* fDiffuse)
{
	*fAmbient = m_fAmbient;
	*fDiffuse = m_fDiffuse;
}

//Set Background Color Format is RRGGBB in Hex Value
void CMeshModel::SetBackColor(DWORD dwColor)
{
	m_fBackColor.r = (float) ((dwColor >> 16) & 0xFF) / 256.0f;
	m_fBackColor.g = (float) ((dwColor >> 8) & 0xFF) / 256.0f;
	m_fBackColor.b = (float) (dwColor & 0xFF) / 256.0f;
}