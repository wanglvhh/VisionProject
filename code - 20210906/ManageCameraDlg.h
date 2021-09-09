#pragma once
// CManageCameraDlg 对话框

class CManageCameraDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CManageCameraDlg)
public:
	CWinXPButtonST m_btnAddCamera;
	CWinXPButtonST m_btnDelCamera;
	CWinXPButtonST m_btnGrabOne;
	CWinXPButtonST m_btnGrabbing;
	CWinXPButtonST m_btnTriggerMode;
	CWinXPButtonST m_btnOk;
	CWinXPButtonST m_btnCancel;
	BOOL m_bTriggerMode;
	CSkinComboBox m_comboCameraList;

	enum LISTCOLUMN
	{
		E_CAMERA_ID = 0,
		E_CAMERA_SN,
		E_CAMERA_TIPINFO,
		E_CAMERA_COMPANY,
		E_CAMERA_CONNECT,
		E_CAMERA_COLORSPACE,
	};
	CListCtrlCl              m_listCamera;
	CProSliderCtrl           m_sliderExposureTime;
	CProSliderCtrl           m_sliderGain;
	//int                      m_nTriggerMode;
	int                      m_nMirrorMode;
	int                      m_nRotateMode;

	HTuple                   m_lWindowID ;
	HObject                  m_hImage ;
	CMyStatic                m_ctlImageView;

	bool                     m_bDraw;
	HTuple                   m_hRowB ;
	HTuple                   m_hColB ;
	HTuple                   m_hRowE ;
	HTuple                   m_hColE;
	BOOL                     m_bScale ;
	BOOL                     m_bMoveImg ;
	bool                     m_bMoveState;
	double                   m_dbRatioWh ;

private:
	void InitAllControl() ;
	void InitBtnControl() ;
	void InitListControl() ;
	void InitViewControl() ;
	void InitComboControl() ;
	void InitSliderControl() ;
	void InitCameraControl() ;
	static void CallDispImage(void *pOwner,HObject *hImage) ;

protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

public:
	void UpdataAllControl() ;
	void UpdataListControl() ;
	void UpdataComboControl() ;
	void UpdataSliderControl() ;
	void UpdataCamera() ;
	void ReSortCameraId() ;
	CAMERA_CODE ReSetSliderControl(CCameraNode*  pCameraNode) ;
public:
	CManageCameraDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CManageCameraDlg();

// 对话框数据
	enum { IDD = IDD_MANAGE_CAMERA_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnBnClickedBtnGrabone();
	afx_msg void OnBnClickedBtnGrabbing();
	afx_msg void OnCbnSelendokComboCameralist();
	afx_msg void OnRadioClicked(UINT uRadioId) ;
	afx_msg void OnBnClickedOk();
};
