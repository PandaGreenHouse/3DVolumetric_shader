
// VolumeMetricDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VolumeMetric.h"
#include "VolumeMetricDlg.h"
#include "afxdialogex.h"
#include "gl/gl.h"
#include "gl/glu.h"
#include "math.h"
#include "render_api.h"
#include <Eigen/Core>
#include <vector>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void getVertices(COM_MESH& comMesh, std::vector<Eigen::Vector3f> &vertices, std::vector<Eigen::Vector3f> &normals)
{
	vertices.resize(0);
	normals.resize(0);
	int face_count = comMesh.intFaceCount;
	for (int i = 0; i < face_count; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			Eigen::Vector3f v, n;
			v[0] = comMesh.pVertices[comMesh.pIndices[3 * i+j]].vertex.x;
			v[1] = comMesh.pVertices[comMesh.pIndices[3 * i+j]].vertex.y;
			v[2] = comMesh.pVertices[comMesh.pIndices[3 * i+j]].vertex.z;
			n[0] = comMesh.pVertices[comMesh.pIndices[3 * i+j]].vec3Normal.x;
			n[1] = comMesh.pVertices[comMesh.pIndices[3 * i+j]].vec3Normal.y;
			n[2] = comMesh.pVertices[comMesh.pIndices[3 * i+j]].vec3Normal.z;
			vertices.push_back(v);
			normals.push_back(n);
		}
		
	}
}

int getVertices(COM_MESH& comMesh, float** pVertices, float** pNormals)
{
	int vertex_count = 3*comMesh.intFaceCount;
	float* vertices = new float[3*vertex_count];
	float* normals = new float[3*vertex_count];
	UINT l = 0;
	for (int i = 0; i < comMesh.intFaceCount; ++i)
	{
		int vertId = comMesh.pIndices[3 * i];
		vertices[l] = comMesh.pVertices[vertId].vertex.x;
		normals[l] = comMesh.pVertices[vertId].vec3Normal.x; ++l;
		vertices[l] = comMesh.pVertices[vertId].vertex.y;
		normals[l] = comMesh.pVertices[vertId].vec3Normal.y; ++l;
		vertices[l] = comMesh.pVertices[vertId].vertex.z;
		normals[l] = comMesh.pVertices[vertId].vec3Normal.z; ++l;
	}
	*pVertices = vertices;
	*pNormals = normals;
	return vertex_count;
}

DWORD ComputeThreadProc(LPVOID pParam)
{
	if (pParam)
		((CVolumeMetricDlg*) pParam)->ComputeThreadFunc();
	return 0;
}

void VolumeCalcCallbackProc(void* pParams)
{
	if (pParams)
		((CVolumeMetricDlg*)pParams)->VolumeCalcProgressFunc();
}
// CVolumeMetricDlg dialog

CVolumeMetricDlg::CVolumeMetricDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CVolumeMetricDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pModelFile = NULL;
	m_fScale = 1.0f;
	m_fAngleX = 0.0f;
	m_fAngleY = 0.0f;
	m_fAngleZ = 0.0f;
	m_hComputeThread = NULL;
	memset(&m_StrComMesh, 0, sizeof(COM_MESH));
}

void CVolumeMetricDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FACENUM_EDT, m_CtrlFaceCountEdt);
	DDX_Control(pDX, IDC_VERTEXCOUNT_EDT, m_CtrlVertexCountEdt);
	DDX_Control(pDX, IDC_DX_EDT, m_CtrlDxEdt);
	DDX_Control(pDX, IDC_DY_EDT, m_CtrlDyEdt);
	DDX_Control(pDX, IDC_DZ_EDT, m_CtrlDzEdt);
	DDX_Control(pDX, IDC_RESOLUTION_EDT, m_CtrlDeltaEdt);
	DDX_Control(pDX, IDC_CX_EDT, m_CtrlCxEdt);
	DDX_Control(pDX, IDC_CY_EDIT, m_CtrlCyEdt);
	DDX_Control(pDX, IDC_CZ_EDT, m_CtrlCzEdt);
	DDX_Control(pDX, IDC_VOLUME_EDT, m_CtrlVolumeEdt);
	DDX_Control(pDX, IDC_START_BTN, m_CtrlStartBtn);
	DDX_Control(pDX, IDC_STOP_BTN, m_CtrlStopBtn);
	DDX_Control(pDX, IDC_PROGRESS1, m_CtrlProgressBar);
	DDX_Control(pDX, IDC_ROTX_EDT, m_CtrlRotXEdt);
	DDX_Control(pDX, IDC_ROTY_EDT, m_CtrlRotYEdt);
	DDX_Control(pDX, IDC_ROTZ_EDT, m_CtrlRotZEdt);
	DDX_Control(pDX, IDC_OPEN_BTN, m_CtrlOpenBtn);
	DDX_Control(pDX, IDC_ROT_SET, m_CtrlRotSetBtn);
	DDX_Control(pDX, IDC_STOP_BTN, m_CtrlStopBtn);
	DDX_Control(pDX, IDC_PICTURE_STATIC, m_CtrlRenderStatic);
	DDX_Control(pDX, IDC_ZOOM_IN, m_CtrlZoomInBtn);
	DDX_Control(pDX, IDC_ZOOM_OUT, m_CtrlZoomOutBtn);
	DDX_Control(pDX, IDC_SAMPLE_EDIT, m_CtrlSampleEdt);
	DDX_Control(pDX, IDC_SAMPLE_SPIN, m_CtrlSampleSpin);
	DDX_Control(pDX, IDC_SHADER_CHECK, m_shader_check);
}

BEGIN_MESSAGE_MAP(CVolumeMetricDlg, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_BN_CLICKED(IDC_OPEN_BTN, &CVolumeMetricDlg::OnOpenBtn)
	ON_BN_CLICKED(IDC_ZOOM_IN, &CVolumeMetricDlg::OnZoomIn)
	ON_BN_CLICKED(IDC_ZOOM_OUT, &CVolumeMetricDlg::OnZoomOut)
	ON_BN_CLICKED(IDC_ROT_SET, &CVolumeMetricDlg::OnClickedRotSet)
	ON_BN_CLICKED(IDC_START_BTN, &CVolumeMetricDlg::OnStartBtn)
	ON_BN_CLICKED(IDC_STOP_BTN, &CVolumeMetricDlg::OnStopBtn)

//	ON_EN_CHANGE(IDC_RESOLUTION_EDT, &CVolumeMetricDlg::OnEnChangeResolutionEdt)
//	ON_EN_CHANGE(IDC_SAMPLE_EDIT, &CVolumeMetricDlg::OnChangeSampleEdit)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SAMPLE_SPIN, &CVolumeMetricDlg::OnDeltaposSampleSpin)	
	ON_BN_CLICKED(IDC_LIGHTSET_BTN, &CVolumeMetricDlg::OnBnClickedLightsetBtn)
END_MESSAGE_MAP()


// CVolumeMetricDlg message handlers

BOOL CVolumeMetricDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	InitCalcParams();
	m_CtrlSampleSpin.SetBuddy(&m_CtrlSampleEdt);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CVolumeMetricDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		m_ClsMesh.DrawScene01(m_fScale,m_fAngleX,m_fAngleY,m_fAngleZ);
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CVolumeMetricDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CVolumeMetricDlg::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	ReleaseModelFile(&m_pModelFile);

	return CDialogEx::DestroyWindow();
}

void CVolumeMetricDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	OnStopBtn();
	m_bDlgClose = TRUE;
	CDialogEx::OnClose();
}

void CVolumeMetricDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class
	if (m_bDlgClose)
		CDialog::OnCancel();
}

void CVolumeMetricDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	if (m_bDlgClose)
		CDialogEx::OnOK();
}



void CVolumeMetricDlg::InitializeComMesh()
{
	//*****Don't Free Memory. Model File Close Function free memory buffers
	m_StrComMesh.pIndices = NULL;
	m_StrComMesh.pVertices = NULL;
}

void CVolumeMetricDlg::SetFileTitle(LPCTSTR lpszFileName)
{
	TCHAR	szTitle[MAX_PATH];
	if (lpszFileName == NULL || lpszFileName[0] == 0)
		return;

	_stprintf(szTitle, _T("Volume Calculation (%s)"), lpszFileName);
	SetWindowText(szTitle);
}

void CVolumeMetricDlg::InitProgressBar()
{
// Set the range to be 0 to 100.
	m_CtrlProgressBar.SetRange(0, 100);
	m_CtrlProgressBar.SetStep(10);
	m_CtrlProgressBar.SetPos(0);
}

void CVolumeMetricDlg::SetProgressBar(int nPos)
{
	m_CtrlProgressBar.SetPos(nPos);
}

void CVolumeMetricDlg::InitializeOfVals()
{
	m_fScale = 1.0f;
	m_fAngleX = 0.0f;
	m_fAngleY = 0.0f;
	m_fAngleZ = 0.0f;
}

void CVolumeMetricDlg::InitCalcParams()
{
	m_stuCalcParams.bLoopFlag	= FALSE;
	m_stuCalcParams.nProgress	= 0;
	m_stuCalcParams.pfnCallback	= VolumeCalcCallbackProc;
	m_stuCalcParams.pvfnParams	= (void*) this;
}

void CVolumeMetricDlg::InitializeOfControls(BOOL bFileOpen)
{
	TCHAR strText[32];

	m_CtrlRotSetBtn.EnableWindow(bFileOpen);
	m_CtrlStartBtn.EnableWindow(bFileOpen);
	m_CtrlZoomInBtn.EnableWindow(bFileOpen);
	m_CtrlZoomOutBtn.EnableWindow(bFileOpen);
	m_CtrlRotXEdt.EnableWindow(bFileOpen);
	m_CtrlRotYEdt.EnableWindow(bFileOpen);
	m_CtrlRotZEdt.EnableWindow(bFileOpen);

	m_CtrlDeltaEdt.EnableWindow(bFileOpen);
	m_CtrlSampleEdt.EnableWindow(bFileOpen);
	m_CtrlSampleSpin.EnableWindow(bFileOpen);

	m_CtrlSampleSpin.SetBuddy(&m_CtrlSampleEdt);
	m_CtrlSampleSpin.SetBase(10);
	m_CtrlSampleSpin.SetRange(1,100);
	m_CtrlSampleSpin.SetPos(1);

	if(bFileOpen)
	{
		_stprintf(strText,_T("%d"), m_StrComMesh.Cx);
		m_CtrlCxEdt.SetWindowText(strText);
		_stprintf(strText,_T("%d"), m_StrComMesh.Cy);
		m_CtrlCyEdt.SetWindowText(strText);
		_stprintf(strText,_T("%d"), m_StrComMesh.Cz);
		m_CtrlCzEdt.SetWindowText(strText);
		_stprintf(strText,_T("%2.2f"), m_StrComMesh.delta);
		m_CtrlDeltaEdt.SetWindowText(strText);
		_stprintf(strText,_T("%4.2f"), m_StrComMesh.Dx);
		m_CtrlDxEdt.SetWindowText(strText);
		_stprintf(strText,_T("%4.2f"), m_StrComMesh.Dy);
		m_CtrlDyEdt.SetWindowText(strText);
		_stprintf(strText,_T("%4.2f"), m_StrComMesh.Dz);
		m_CtrlDzEdt.SetWindowText(strText);
		_stprintf(strText,_T("%d"), m_StrComMesh.intFaceCount);
		m_CtrlFaceCountEdt.SetWindowText(strText);
		_stprintf(strText,_T("%d"), m_StrComMesh.intVertexCount);
		m_CtrlVertexCountEdt.SetWindowText(strText);
		DisplayLightVals();
	} else
	{
		m_CtrlCxEdt.SetWindowText(_T(""));
		m_CtrlCyEdt.SetWindowText(_T(""));
		m_CtrlCzEdt.SetWindowText(_T(""));
		m_CtrlDeltaEdt.SetWindowText(_T(""));
		m_CtrlDxEdt.SetWindowText(_T(""));
		m_CtrlDyEdt.SetWindowText(_T(""));
		m_CtrlDzEdt.SetWindowText(_T(""));
		m_CtrlFaceCountEdt.SetWindowText(_T(""));
	}

	m_CtrlVolumeEdt.SetWindowText(_T(""));
	m_CtrlRotXEdt.SetWindowText(_T(""));
	m_CtrlRotYEdt.SetWindowText(_T(""));
	m_CtrlRotZEdt.SetWindowText(_T(""));
	m_CtrlStopBtn.EnableWindow(FALSE);
	InitProgressBar();
}


void CVolumeMetricDlg::OnZoomIn()
{
	// TODO: Add your control notification handler code here
	m_fScale += 0.5f;
	Invalidate(FALSE);
}


void CVolumeMetricDlg::OnZoomOut()
{
	// TODO: Add your control notification handler code here
	m_fScale -= 0.5f;
	Invalidate(FALSE);
}


void CVolumeMetricDlg::OnClickedRotSet()
{
	// TODO: Add your control notification handler code here
	TCHAR strText[32];
	m_CtrlRotXEdt.GetWindowText(strText,8);
	m_fAngleX = (float) _tstof(strText);
	m_CtrlRotYEdt.GetWindowText(strText,8);
	m_fAngleY = (float) _tstof(strText);
	m_CtrlRotZEdt.GetWindowText(strText,8);
	m_fAngleZ = (float) _tstof(strText);
	Invalidate(FALSE);
}

BOOL CVolumeMetricDlg::SetDelta()
{
	TCHAR strText[32];

	if (m_StrComMesh.delta <= 0.0f)
	{
		strText[0] = 0;
		m_CtrlCxEdt.SetWindowText(strText);
		m_CtrlCyEdt.SetWindowText(strText);
		m_CtrlCzEdt.SetWindowText(strText);
		return FALSE;
	}
	m_StrComMesh.Cx = (int) (m_StrComMesh.Dx/m_StrComMesh.delta);
	_stprintf(strText,_T("%d"), m_StrComMesh.Cx);
	m_CtrlCxEdt.SetWindowText(strText);
	m_StrComMesh.Cy = (int) (m_StrComMesh.Dy/m_StrComMesh.delta);
	_stprintf(strText,_T("%d"), m_StrComMesh.Cy);
	m_CtrlCyEdt.SetWindowText(strText);
	m_StrComMesh.Cz = (int) (m_StrComMesh.Dz/m_StrComMesh.delta);
	_stprintf(strText,_T("%d"), m_StrComMesh.Cz);
	m_CtrlCzEdt.SetWindowText(strText);
	m_CtrlVolumeEdt.SetWindowTextW(_T(""));
	return TRUE;
}

//void CVolumeMetricDlg::OnEnChangeResolutionEdt()
//{
//	SetDelta();
//}

//void CVolumeMetricDlg::OnChangeSampleEdit()
//{
//	TCHAR	szText[32];
//	int		nPos = 0;
//
//	if (m_CtrlSampleEdt.m_hWnd == NULL)
//		return;
//
//	m_CtrlSampleEdt.GetWindowText(szText, 32);
//	_stscanf(szText, _T("%d"), &nPos);
//	int nDots = DOT_COUNT + 200*nPos;
//	float Dx, Dy;
//	Dx = m_StrComMesh.Dx;
//	Dy = m_StrComMesh.Dy;
//	float delta = Dx*Dy/nDots;
//	delta = sqrtf(delta); 
//	m_StrComMesh.delta = delta;
//	_stprintf(szText, _T("%.2lf"), m_StrComMesh.delta);
//	m_CtrlDeltaEdt.SetWindowText(szText);
//	SetDelta();
//}

void CVolumeMetricDlg::OnDeltaposSampleSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	TCHAR	szText[32];
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	// TODO: Add your control notification handler code here
	*pResult = 0;
	int pos = m_CtrlSampleSpin.GetPos();
	int nDots = DOT_COUNT + 200*pos;
	float Dx, Dy;
	Dx = m_StrComMesh.Dx;
	Dy = m_StrComMesh.Dy;
	float delta = Dx*Dy/nDots;
	delta = sqrtf(delta); 
	m_StrComMesh.delta = delta;
	_stprintf(szText, _T("%.2lf"), m_StrComMesh.delta);
	m_CtrlDeltaEdt.SetWindowText(szText);
	SetDelta();
}

void CVolumeMetricDlg::OnOpenBtn()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE, _T("*.stl"), _T(""), OFN_EXPLORER | OFN_FILEMUSTEXIST,
					_T("3D Model Files(*.stl, *.wrl, *.obj, *.3ds)|*.stl;*.wrl;*.obj;*.3ds|All Files(*.*)|*.*||"), this, 0, TRUE);
	TCHAR	szPath[MAX_PATH], *pszFileName;
	DWORD	dwTime;

	m_bFileOpen = FALSE;
	m_bDlgClose = FALSE;
	bool bShader = false;
	if (dlg.DoModal() == IDOK)
	{
		/*if (MessageBox(_T("shader rendering?"), _T("rendering"), MB_CANCELTRYCONTINUE | MB_OK) == MB_OK)
		{
			bShader = true;
		}*/
		InitializeComMesh();
		_tcscpy(szPath, (LPCTSTR) dlg.GetPathName());
		if (m_pModelFile)
			ReleaseModelFile(&m_pModelFile);
		m_pModelFile = CreateModelFile(szPath);
		m_bFileOpen = FALSE;
		dwTime = GetTickCount();
		if (m_pModelFile)
			m_bFileOpen = m_pModelFile->Open(szPath, &m_StrComMesh);
		dwTime = GetTickCount() - dwTime;
		if (!m_bFileOpen)
		{
			MessageBox(_T("File not found or not supported format."), _T("Error"), MB_ICONERROR | MB_OK);
		} else
		{
			pszFileName = _tcsrchr(szPath, '\\');
			if (pszFileName == NULL)
				pszFileName = _tcsrchr(szPath, '/');
			if (pszFileName == NULL)
				pszFileName = szPath;
			else
				pszFileName++;
			SetFileTitle(pszFileName);
			//m_ClsMesh.InitOpenGL(m_CtrlRenderStatic.GetDC()->GetSafeHdc());
			//m_ClsMesh.InitializeMeshObject(&m_StrComMesh);
			EnableControls();
			_stprintf(szPath, _T("File Opened in %d ms"), dwTime);
			MessageBox(szPath, _T("Time"), MB_OK);
			/*std::vector<Eigen::Vector3f> vertices, normals;
			getVertices(m_StrComMesh, vertices, normals);
			initOpenGL();
			render(vertices, normals);
			vertices.clear();
			normals.clear();*/
		}
		InitializeOfControls(m_bFileOpen);
	}
	InitializeOfVals();
	Invalidate(FALSE);
	renderingByShaders();
}

void CVolumeMetricDlg::renderingByShaders()
{
	std::vector<Eigen::Vector3f> vertices, normals;
	getVertices(m_StrComMesh, vertices, normals);
	initOpenGL();
	render(vertices, normals);
	vertices.clear();
	normals.clear();
}

void CVolumeMetricDlg::EnableControls()
{
	m_CtrlStartBtn.EnableWindow(!m_stuCalcParams.bLoopFlag);
	m_CtrlOpenBtn.EnableWindow(!m_stuCalcParams.bLoopFlag);
	m_CtrlDeltaEdt.EnableWindow(!m_stuCalcParams.bLoopFlag);
	m_CtrlSampleEdt.EnableWindow(!m_stuCalcParams.bLoopFlag);
	m_CtrlSampleSpin.EnableWindow(!m_stuCalcParams.bLoopFlag);
	m_CtrlStopBtn.EnableWindow(m_stuCalcParams.bLoopFlag);
}

void CVolumeMetricDlg::OnStartBtn()
{
	// TODO: Add your control notification handler code here
	/*DWORD dwId = 0;
	if (m_hComputeThread != NULL)
	{
		if (!m_stuCalcParams.bLoopFlag)
		{
			::WaitForSingleObject(m_hComputeThread, INFINITE);
			::CloseHandle(m_hComputeThread);
			m_hComputeThread = NULL;
		} else
			return;
	}

	if (!SetDelta())
	{
		MessageBox(_T("Error"), _T("Delta value is incorrect. Please Input Delta value Again."), MB_ICONERROR | MB_OK);
		return;
	}
	InitProgressBar();
	m_stuCalcParams.bLoopFlag = TRUE;
	m_stuCalcParams.nProgress = 0;
	SetProgressBar(m_stuCalcParams.nProgress);
	m_hComputeThread	= ::CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) ComputeThreadProc, this, 0, &dwId);*/
	m_ClsMetric.CalculateVolume(&m_StrComMesh);
	TCHAR strText[32];
	_stprintf(strText,_T("%.2f"), m_StrComMesh.fVolume);
	m_CtrlVolumeEdt.SetWindowTextW(strText);
}

void CVolumeMetricDlg::OnStopBtn()
{
	// TODO: Add your control notification handler code here
	if (m_hComputeThread == NULL)
		return;

	if (m_stuCalcParams.bLoopFlag)
	{
		m_stuCalcParams.bLoopFlag = FALSE;
		::WaitForSingleObject(m_hComputeThread, INFINITE);
	}

	::CloseHandle(m_hComputeThread);
	m_hComputeThread = NULL;
	EnableControls();
	m_stuCalcParams.nProgress = 0;
	SetProgressBar(m_stuCalcParams.nProgress);
}

void CVolumeMetricDlg::ComputeThreadFunc()
{
	FLOAT fVolume = 0.0f;
	TCHAR strText[60];

	m_ClsMetric.ComputingVolume(&m_stuCalcParams);
	if (m_stuCalcParams.bLoopFlag)
	{
		_stprintf(strText,_T("%5.2f"), m_StrComMesh.fVolume);
		m_CtrlVolumeEdt.SetWindowText(strText);
		m_stuCalcParams.bLoopFlag = FALSE;
		EnableControls();
		m_stuCalcParams.nProgress = 0;
		SetProgressBar(m_stuCalcParams.nProgress);
	}
}

void CVolumeMetricDlg::VolumeCalcProgressFunc()
{
	SetProgressBar(m_stuCalcParams.nProgress);
}


void CVolumeMetricDlg::OnBnClickedLightsetBtn()
{
	// TODO: Add your control notification handler code here
	float fAmbient, fDiffuse;
	TCHAR strText[32];
	m_CtrlDeltaEdt.GetWindowTextW(strText, 8);
	_stscanf(strText, _T("%f"), &fAmbient);
	m_CtrlSampleEdt.GetWindowTextW(strText, 8);
	_stscanf(strText, _T("%f"), &fDiffuse);
	m_ClsMesh.SetLightVals(fAmbient,fDiffuse);
	Invalidate(FALSE);
}

void CVolumeMetricDlg::DisplayLightVals()
{
	TCHAR strText[32];
	float fAmbient, fDiffuse;
	m_ClsMesh.GetLightVals(&fAmbient,&fDiffuse);
	_stprintf(strText,_T("%.2f"),fAmbient);
	m_CtrlDeltaEdt.SetWindowTextW(strText);
	_stprintf(strText,_T("%.2f"),fDiffuse);
	m_CtrlSampleEdt.SetWindowTextW(strText);
}