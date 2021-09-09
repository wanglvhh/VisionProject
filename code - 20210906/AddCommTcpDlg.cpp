// AddCommTcpDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VisionProject.h"
#include "AddCommTcpDlg.h"
#include "afxdialogex.h"
#include "ManageCommunicationDlg.h"

// CAddCommTcpDlg �Ի���

IMPLEMENT_DYNAMIC(CAddCommTcpDlg, CDialogEx)

CAddCommTcpDlg::CAddCommTcpDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAddCommTcpDlg::IDD, pParent)
	, m_nSockType(0)
	, m_uIpPort(0)
{
	m_strIpAddress = _T("") ;
}

CAddCommTcpDlg::~CAddCommTcpDlg()
{
}

void CAddCommTcpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_SERVE, m_nSockType);
	DDX_Control(pDX, IDC_IPADDRESS1, m_IpAddress);
	DDX_Text(pDX, IDC_EDIT_PORT, m_uIpPort);
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
}

BEGIN_MESSAGE_MAP(CAddCommTcpDlg, CDialogEx)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO_SERVE, IDC_RADIO_CLIENT, OnRadioClicked)
	ON_BN_CLICKED(IDOK, &CAddCommTcpDlg::OnBnClickedOk)
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_IPADDRESS1, &CAddCommTcpDlg::OnIpnFieldchangedIpaddress1)
	ON_EN_CHANGE(IDC_EDIT_PORT, &CAddCommTcpDlg::OnEnChangeEditPort)
END_MESSAGE_MAP()

// CAddCommTcpDlg ��Ϣ�������

BOOL CAddCommTcpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitAllControl() ;

	UpdateAllControl() ;

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CAddCommTcpDlg::InitAllControl()
{
	try
	{
		//��ʼ��BtnControl
		InitBtnControl() ;
	}
	catch (...)
	{
	}
}

void CAddCommTcpDlg::InitBtnControl()
{
	try
	{
		m_btnOk.SetIcon(IDI_ICON_OK) ;
		m_btnOk.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnOk.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnOk.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnOk.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnOk.SetRounded(TRUE) ;

		m_btnCancel.SetIcon(IDI_ICON_CANCEL) ;
		m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnCancel.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnCancel.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnCancel.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnCancel.SetRounded(TRUE) ;
	}
	catch (...)
	{
	}
}

void CAddCommTcpDlg::UpdateAllControl()
{
	USES_CONVERSION ;
	try
	{
		UpdateData(true) ;

		CString strIpAddress(m_commSocketNode.strIpAddress.c_str()) ;
		BYTE bIp1,bIp2,bIp3,bIp4;
		vGetBytesIP((LPCSTR)W2A(strIpAddress),bIp1,bIp2,bIp3,bIp4) ;

		m_nSockType = m_commSocketNode.nSocketType ;
		m_IpAddress.SetAddress(bIp1,bIp2,bIp3,bIp4) ;
		m_uIpPort = m_commSocketNode.uIpPort ;

		UpdateData(false) ;
	}
	catch (...)
	{
	}
}

void CAddCommTcpDlg::OnRadioClicked(UINT uRadioId)
{
	UpdateData(TRUE) ;
}

void CAddCommTcpDlg::OnIpnFieldchangedIpaddress1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);

	BYTE bytIp1, bytIp2, bytIp3, bytIp4 ;
	m_IpAddress.GetAddress(bytIp1, bytIp2, bytIp3, bytIp4) ;
	CString strIp(_T("")) ;
	strIp.Format(_T("%u.%u.%u.%u"), bytIp1, bytIp2, bytIp3, bytIp4) ;
	m_strIpAddress = strIp ;

	*pResult = 0;
}

void CAddCommTcpDlg::OnEnChangeEditPort()
{
	UpdateData(TRUE) ;
}

void CAddCommTcpDlg::OnBnClickedOk()
{
	USES_CONVERSION ;
	try
	{
		UpdateData(TRUE) ;

		BYTE bytIp1, bytIp2, bytIp3, bytIp4 ;
		m_IpAddress.GetAddress(bytIp1, bytIp2, bytIp3, bytIp4) ;
		CString strIp(_T("")) ;
		strIp.Format(_T("%u.%u.%u.%u"), bytIp1, bytIp2, bytIp3, bytIp4) ;
		m_strIpAddress = strIp ;

		m_commSocketNode.nSocketType = m_nSockType ;
		m_commSocketNode.strIpAddress = W2A(m_strIpAddress) ;
		m_commSocketNode.uIpPort = m_uIpPort ;
	}
	catch (...)
	{
	}

	CDialogEx::OnOK();
}