#pragma once
#include "afxcmn.h"
// CManageCommunicationDlg 对话框

class CManageCommunicationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CManageCommunicationDlg)
public:
	CWinXPButtonST   m_btnAdd;
	CWinXPButtonST   m_btnEdit;
	CWinXPButtonST   m_btnDel;
	CWinXPButtonST   m_btnReConnect;
	CWinXPButtonST   m_btnOk;
	CWinXPButtonST   m_btnCancel;
	CWinXPButtonST   m_btnSend;
	CWinXPButtonST   m_btnRead;
	CWinXPButtonST   m_btnClear;
	CListCtrlCl      m_listComm;
	CRichEditCtrl    m_ctlSysTipsDisplay1;
	CSkinComboBox    m_comboCommList;
	CString          m_strSendData;

	CRITICAL_SECTION m_csComm ;

	enum LISTCOMM
	{
		E_COMM_ID = 0,
		E_COMM_NAME,
		E_COMM_TYPE,
		E_COMM_VALUE,
	};
private:
	void InitAllControl() ;
	void InitBtnControl() ;
	void InitListControl() ;
	void InitComboControl() ;
	void InitRichEdit() ;
	void SetSysTipsInfo(CString strInfo, COLORREF crColor) ;
public:
	void UpdataAllControl() ;
	void UpdataListControl() ;
	void UpdataComboControl() ;
public:
	CManageCommunicationDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CManageCommunicationDlg();

// 对话框数据
	enum { IDD = IDD_MANAGE_COMMUNICATION_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnEdit();
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnNMDblclkListComm(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnSend();
	afx_msg void OnBnClickedBtnRead();
	afx_msg void OnBnClickedBtnClear();
	afx_msg void OnBnClickedBtnReconnect();
};
