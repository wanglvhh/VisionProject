#pragma once
// CNewDlg 对话框

class CNewDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNewDlg)
public:
	CBrush m_brushBk ;
	CString m_strStaticInfo ;
	CString m_strInfo;
	CWinXPButtonST m_btnOk;
	CWinXPButtonST m_btnCancel;

private:
	void InitAllControl() ;
	void InitBtnControl() ;

public:
	CNewDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CNewDlg();

// 对话框数据
	enum { IDD = IDD_NEW_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeEditInfo();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
