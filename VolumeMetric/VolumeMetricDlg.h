
// VolumeMetricDlg.h : header file
//

#pragma once
#include "StlFile.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "MeshModel.h"
#include "MeshMetric.h"


// CVolumeMetricDlg dialog
class CVolumeMetricDlg : public CDialogEx
{
// Construction
public:
	CVolumeMetricDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_VOLUMEMETRIC_DIALOG };

	CEdit m_CtrlFaceCountEdt;
	CEdit m_CtrlVertexCountEdt;
	CEdit m_CtrlDxEdt;
	CEdit m_CtrlDyEdt;
	CEdit m_CtrlDzEdt;
	CEdit m_CtrlDeltaEdt;
	CEdit m_CtrlCxEdt;
	CEdit m_CtrlCyEdt;
	CEdit m_CtrlCzEdt;
	CEdit m_CtrlVolumeEdt;
	CButton m_CtrlStartBtn;
	CButton m_CtrlStopBtn;
	CEdit m_CtrlRotXEdt;
	CEdit m_CtrlRotYEdt;
	CEdit m_CtrlRotZEdt;
	CButton m_CtrlOpenBtn;
	CButton m_CtrlRotSetBtn;
	CButton m_CtrlExitBtn;
	CProgressCtrl m_CtrlProgressBar;
	CStatic m_CtrlRenderStatic;
	CButton m_CtrlZoomInBtn;
	CButton m_CtrlZoomOutBtn;
	CEdit m_CtrlSampleEdt;
	CSpinButtonCtrl m_CtrlSampleSpin;
	CButton m_shader_check;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	HICON	m_hIcon;

	afx_msg void OnOpenBtn();
	afx_msg void OnZoomIn();
	afx_msg void OnZoomOut();
	afx_msg void OnClickedRotSet();
	afx_msg void OnStartBtn();
	afx_msg void OnStopBtn();
//	afx_msg void OnEnChangeResolutionEdt();
//	afx_msg void OnChangeSampleEdit();
	afx_msg void OnDeltaposSampleSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClose();

	virtual void OnOK();
	virtual void OnCancel();
	

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	BOOL		m_bFileOpen;
	BOOL		m_bComputingFlg;
	COM_MESH	m_StrComMesh;
	CModelFile*	m_pModelFile;
	CMeshMetric m_ClsMetric;
	CPalette	m_cPalette;
	CPalette	*m_pOldPalette;
	CMeshModel  m_ClsMesh;  
	float		m_fScale;
	float		m_fAngleX;
	float		m_fAngleY;
	float		m_fAngleZ;

	HANDLE		m_hComputeThread;
	CALCPARAMS	m_stuCalcParams;

	BOOL		m_bDlgClose;

	void InitializeComMesh();
	void InitializeOfControls(BOOL bFlag);
	void InitializeOfVals();
	void InitCalcParams();
	void SetFileTitle(LPCTSTR lpszFileName);
	BOOL SetDelta();

	void InitProgressBar();
	void SetProgressBar(int nPos);
	void EnableControls();
	void DisplayLightVals();

	void renderingByShaders();
public:
	void ComputeThreadFunc();
	void VolumeCalcProgressFunc();
	virtual BOOL DestroyWindow();
	afx_msg void OnBnClickedLightsetBtn();
	// if this is checked, shader based rendering is performed. 
};
