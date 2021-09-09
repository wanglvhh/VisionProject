#pragma once
// CTypeCommDlg 对话框

class CTypeCommDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTypeCommDlg)
public:
	CWinXPButtonST m_btnOk;
	CWinXPButtonST m_btnCancel;
	int m_nCommType;
	CString m_strCommName;
private:
	void InitAllControl() ;
	void InitBtnControl() ;
public:
	CTypeCommDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTypeCommDlg();

// 对话框数据
	enum { IDD = IDD_TYPE_COMM_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioClicked(UINT uRadioId) ;
	afx_msg void OnEnChangeEditCommname();
};
