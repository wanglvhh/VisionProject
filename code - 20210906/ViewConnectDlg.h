#pragma once

// CViewConnectDlg �Ի���

class CViewConnectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CViewConnectDlg)
public:
	CSkinComboBox      m_comboWorkList;
	CWinXPButtonST     m_btnOk;
	CWinXPButtonST     m_btnCancel;
	CString            m_strWorkFlowName ;
private:
	void InitAllControl() ;
	void InitBtnControl() ;
	void InitComboControl() ;
	void UpdateComboControl() ;
public:
	CViewConnectDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CViewConnectDlg();

// �Ի�������
	enum { IDD = IDD_VIEWCONNECT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonClicked(UINT uBtnId) ;
};
