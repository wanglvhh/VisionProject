#pragma once
#include "afxcmn.h"
// CAddCommTcpDlg 对话框

class CAddCommTcpDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddCommTcpDlg)
public:
	CWinXPButtonST    m_btnOk;
	CWinXPButtonST    m_btnCancel;
	COMMSOCKETNODE    m_commSocketNode ;
	CString           m_strIpAddress ;
	int               m_nSockType;
	UINT              m_uIpPort;
	CIPAddressCtrl    m_IpAddress;

private:
	void InitAllControl() ;
	void InitBtnControl() ;
	void InitRichEdit() ;
	void UpdateAllControl() ;
public:
	CAddCommTcpDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAddCommTcpDlg();

// 对话框数据
	enum { IDD = IDD_ADD_COMMTCP_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog() ;
	afx_msg void OnRadioClicked(UINT uRadioId) ;
	afx_msg void OnBnClickedOk();
	afx_msg void OnIpnFieldchangedIpaddress1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeEditPort();
};
