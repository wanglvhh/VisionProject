#pragma once
// CCommConnectDlg 对话框

class CCommConnectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCommConnectDlg)
public:
	CWinXPButtonST     m_btnOk;
	CWinXPButtonST     m_btnCancel;
	CSkinComboBox      m_comboCommList;
	CStringArray       m_arrayCommInfo ;
	CString            m_strSelCommInfo ;

private:
	void InitAllControl() ;
	void InitBtnControl() ;
	void InitComboControl() ;
	void UpdateComboControl() ;
public:
	CCommConnectDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCommConnectDlg();

// 对话框数据
	enum { IDD = IDD_COMM_CONNECT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonClicked(UINT uBtnId) ;
};
