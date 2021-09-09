// AddTcpSlaveDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "VisionProject.h"
#include "AddTcpSlaveDlg.h"
#include "afxdialogex.h"

// CAddTcpSlaveDlg 对话框

IMPLEMENT_DYNAMIC(CAddTcpSlaveDlg, CDialogEx)

CAddTcpSlaveDlg::CAddTcpSlaveDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAddTcpSlaveDlg::IDD, pParent)
	, m_uSlaveID(1)
	, m_uIpPort(502)
{
}

CAddTcpSlaveDlg::~CAddTcpSlaveDlg()
{
}

void CAddTcpSlaveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Text(pDX, IDC_EDIT_SLAVE_ADDRESS, m_uSlaveID);
	DDX_Control(pDX, IDC_IPADDRESS1, m_IpAddress);
	DDX_Text(pDX, IDC_EDIT_PORT, m_uIpPort);
}

BEGIN_MESSAGE_MAP(CAddTcpSlaveDlg, CDialogEx)
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_IPADDRESS1, &CAddTcpSlaveDlg::OnIpnFieldchangedIpaddress1)
	ON_EN_CHANGE(IDC_EDIT_SLAVE_ADDRESS, &CAddTcpSlaveDlg::OnEnChangeEditSlaveAddress)
	ON_EN_CHANGE(IDC_EDIT_PORT, &CAddTcpSlaveDlg::OnEnChangeEditPort)
	ON_BN_CLICKED(IDOK, &CAddTcpSlaveDlg::OnBnClickedOk)
END_MESSAGE_MAP()

// CAddTcpSlaveDlg 消息处理程序

BOOL CAddTcpSlaveDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitAllControl() ;

	UpdateAllControl() ;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CAddTcpSlaveDlg::InitAllControl()
{
	try
	{
		//初始化BtnControl
		InitBtnControl() ;
	}
	catch (...)
	{
	}
}

void CAddTcpSlaveDlg::InitBtnControl()
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

void CAddTcpSlaveDlg::UpdateAllControl()
{
	USES_CONVERSION ;
	try
	{
		UpdateData(TRUE) ;

		CString strIpAddress(m_tcpSlaveNode.strIpAddress.c_str()) ;
		BYTE bIp1,bIp2,bIp3,bIp4;
		vGetBytesIP((LPCSTR)W2A(strIpAddress),bIp1,bIp2,bIp3,bIp4) ;
		m_IpAddress.SetAddress(bIp1,bIp2,bIp3,bIp4) ;
		m_uIpPort = m_tcpSlaveNode.uIpPort ;

		m_uSlaveID = m_tcpSlaveNode.nSlaveID ;

		UpdateData(FALSE) ;
	}
	catch (...)
	{
	}
}

void CAddTcpSlaveDlg::OnIpnFieldchangedIpaddress1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);

	BYTE bytIp1, bytIp2, bytIp3, bytIp4 ;
	m_IpAddress.GetAddress(bytIp1, bytIp2, bytIp3, bytIp4) ;
	CString strIp(_T("")) ;
	strIp.Format(_T("%u.%u.%u.%u"), bytIp1, bytIp2, bytIp3, bytIp4) ;
	m_strIpAddress = strIp ;

	*pResult = 0;
}

void CAddTcpSlaveDlg::OnEnChangeEditSlaveAddress()
{
	UpdateData(TRUE) ;
}

void CAddTcpSlaveDlg::OnEnChangeEditPort()
{
	UpdateData(TRUE) ;
}

void CAddTcpSlaveDlg::OnBnClickedOk()
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

		m_tcpSlaveNode.nSlaveID = (int)m_uSlaveID ;
		m_tcpSlaveNode.strIpAddress = W2A(m_strIpAddress) ;
		m_tcpSlaveNode.uIpPort = m_uIpPort ;
	}
	catch (...)
	{
	}

	CDialogEx::OnOK();
}