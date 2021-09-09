#pragma once
// CNewDlg �Ի���

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
	CNewDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNewDlg();

// �Ի�������
	enum { IDD = IDD_NEW_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeEditInfo();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
