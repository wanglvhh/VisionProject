// AddTcpMasterDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "VisionProject.h"
#include "AddTcpMasterDlg.h"
#include "afxdialogex.h"

// CAddTcpMasterDlg 对话框

IMPLEMENT_DYNAMIC(CAddTcpMasterDlg, CDialogEx)

CAddTcpMasterDlg::CAddTcpMasterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAddTcpMasterDlg::IDD, pParent)
	, m_uSlaveID(1)
	, m_uIpPort(502)
{
}

CAddTcpMasterDlg::~CAddTcpMasterDlg()
{
}

void CAddTcpMasterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SLAVE_ADDRESS, m_uSlaveID);
	DDX_Control(pDX, IDC_IPADDRESS1, m_IpAddress);
	DDX_Text(pDX, IDC_EDIT_PORT, m_uIpPort);
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
}

BEGIN_MESSAGE_MAP(CAddTcpMasterDlg, CDialogEx)
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_IPADDRESS1, &CAddTcpMasterDlg::OnIpnFieldchangedIpaddress1)
	ON_BN_CLICKED(IDOK, &CAddTcpMasterDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT_SLAVE_ADDRESS, &CAddTcpMasterDlg::OnEnChangeEditSlaveAddress)
	ON_EN_CHANGE(IDC_EDIT_PORT, &CAddTcpMasterDlg::OnEnChangeEditPort)
END_MESSAGE_MAP()

// CAddTcpMasterDlg 消息处理程序

BOOL CAddTcpMasterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitAllControl() ;

	UpdateAllControl() ;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CAddTcpMasterDlg::InitAllControl()
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

void CAddTcpMasterDlg::InitBtnControl()
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

void CAddTcpMasterDlg::UpdateAllControl()
{
	USES_CONVERSION ;
	try
	{
		UpdateData(TRUE) ;

		CString strIpAddress(m_tcpMasterNode.strIpAddress.c_str()) ;
		BYTE bIp1,bIp2,bIp3,bIp4;
		vGetBytesIP((LPCSTR)W2A(strIpAddress),bIp1,bIp2,bIp3,bIp4) ;
		m_IpAddress.SetAddress(bIp1,bIp2,bIp3,bIp4) ;
		m_uIpPort = m_tcpMasterNode.uIpPort ;

		m_uSlaveID = m_tcpMasterNode.nSlaveID ;

		UpdateData(FALSE) ;
	}
	catch (...)
	{
	}
}

void CAddTcpMasterDlg::OnIpnFieldchangedIpaddress1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);

	BYTE bytIp1, bytIp2, bytIp3, bytIp4 ;
	m_IpAddress.GetAddress(bytIp1, bytIp2, bytIp3, bytIp4) ;
	CString strIp(_T("")) ;
	strIp.Format(_T("%u.%u.%u.%u"), bytIp1, bytIp2, bytIp3, bytIp4) ;
	m_strIpAddress = strIp ;

	*pResult = 0;
}

void CAddTcpMasterDlg::OnEnChangeEditSlaveAddress()
{
	UpdateData(TRUE) ;
}

void CAddTcpMasterDlg::OnEnChangeEditPort()
{
	UpdateData(TRUE) ;
}

void CAddTcpMasterDlg::OnBnClickedOk()
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

		m_tcpMasterNode.nSlaveID = (int)m_uSlaveID ;
		m_tcpMasterNode.strIpAddress = W2A(m_strIpAddress) ;
		m_tcpMasterNode.uIpPort = m_uIpPort ;
	}
	catch (...)
	{
	}

	CDialogEx::OnOK();
}