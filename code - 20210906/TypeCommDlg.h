#pragma once
// CTypeCommDlg �Ի���

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
	CTypeCommDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTypeCommDlg();

// �Ի�������
	enum { IDD = IDD_TYPE_COMM_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioClicked(UINT uRadioId) ;
	afx_msg void OnEnChangeEditCommname();
};
