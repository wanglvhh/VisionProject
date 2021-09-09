#pragma once
#include "afxcmn.h"

// CAddTcpSlaveDlg �Ի���

class CAddTcpSlaveDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddTcpSlaveDlg)
public:
	CWinXPButtonST m_btnOk;
	CWinXPButtonST m_btnCancel;
	UINT m_uSlaveID;
	CIPAddressCtrl m_IpAddress;
	UINT m_uIpPort;
	CString        m_strIpAddress ;

	TCPSLAVENODE   m_tcpSlaveNode ;

private:
	void InitAllControl() ;
	void InitBtnControl() ;
	void UpdateAllControl() ;
public:
	CAddTcpSlaveDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAddTcpSlaveDlg();

// �Ի�������
	enum { IDD = IDD_ADD_MODBUS_TCPSLAVE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnIpnFieldchangedIpaddress1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeEditSlaveAddress();
	afx_msg void OnEnChangeEditPort();
	afx_msg void OnBnClickedOk();
};
