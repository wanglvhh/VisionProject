#pragma once
// CAddCameraDlg 对话框

class CAddCameraDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddCameraDlg)
public:
	CWinXPButtonST       m_btnOk;
	CWinXPButtonST       m_btnCancel;
	CString              m_strCameraSn;
	CString              m_strCameraTipInfo;
	CSkinComboBox        m_comboCameraCompany;
	CSkinComboBox        m_comboCameraConnect;
	CSkinComboBox        m_comboCameraColorSpace;

	CCameraNode*         m_pCameraNode ;
private:
	void InitAllControl() ;
	void InitBtnControl() ;
	void InitComboControl() ;
	void InitEditControl() ;

public:
	CAddCameraDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAddCameraDlg();

// 对话框数据
	enum { IDD = IDD_ADDCAMERA__DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnEditChange(UINT uEditId) ;
	afx_msg void OnCbnSelOk(UINT uComboId) ;
	afx_msg void OnButtonClicked(UINT uBtnId) ;
};
