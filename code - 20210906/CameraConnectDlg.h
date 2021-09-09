#pragma once

// CCameraConnectDlg 对话框

class CCameraConnectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCameraConnectDlg)
public:
	CWinXPButtonST     m_btnOk;
	CWinXPButtonST     m_btnCancel;
	CSkinComboBox      m_comboCameraList ;
	CStringArray       m_arrayCameraInfo ;
	CString            m_strSelCameraInfo ;

private:
	void InitAllControl() ;
	void InitBtnControl() ;
	void InitComboControl() ;
	void UpdateComboControl() ;
public:
	CCameraConnectDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCameraConnectDlg();

// 对话框数据
	enum { IDD = IDD_CAMERACONNECT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonClicked(UINT uBtnId) ;
};
