// AddRtuSlaveDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "VisionProject.h"
#include "AddRtuSlaveDlg.h"
#include "afxdialogex.h"

// CAddRtuSlaveDlg 对话框

IMPLEMENT_DYNAMIC(CAddRtuSlaveDlg, CDialogEx)

CAddRtuSlaveDlg::CAddRtuSlaveDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAddRtuSlaveDlg::IDD, pParent)
	, m_uSlaveID(1)
{
}

CAddRtuSlaveDlg::~CAddRtuSlaveDlg()
{
}

void CAddRtuSlaveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Text(pDX, IDC_EDIT_SLAVE_ADDRESS, m_uSlaveID);
	DDX_Control(pDX, IDC_COMBO_PORT, m_comboPort);
	DDX_Control(pDX, IDC_COMBO_BAUDRATE, m_comboBaudRate);
	DDX_Control(pDX, IDC_COMBO_PARITY, m_comboParity);
	DDX_Control(pDX, IDC_COMBO_BITSSIZE, m_comboBitsize);
	DDX_Control(pDX, IDC_COMBO_STOPBITS, m_comboStopBits);
}

BEGIN_MESSAGE_MAP(CAddRtuSlaveDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAddRtuSlaveDlg::OnBnClickedOk)
END_MESSAGE_MAP()

// CAddRtuSlaveDlg 消息处理程序

BOOL CAddRtuSlaveDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitAllControl() ;

	UpdateAllControl() ;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CAddRtuSlaveDlg::InitAllControl()
{
	try
	{
		//初始化BtnControl
		InitBtnControl() ;
		//初始化ComboControl
		InitComboControl() ;
	}
	catch (...)
	{
	}
}

void CAddRtuSlaveDlg::InitBtnControl()
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

void CAddRtuSlaveDlg::InitComboControl()
{
	try
	{
		m_comboPort.SetCurSel((int)E_COMM_COM1) ;
		m_comboPort.SnShowImage(_T(".\\res\\bmp\\drop_down.bmp"), 3, 2, SKIN_STATUS_NOR, FALSE);
		m_comboPort.SnShowImage(_T(".\\res\\bmp\\drop_down.bmp"), 3, 3, SKIN_STATUS_HOT, FALSE);

		m_comboBaudRate.SetCurSel((int)E_COMM_BAUDRATE19200) ;
		m_comboBaudRate.SnShowImage(_T(".\\res\\bmp\\drop_down.bmp"), 3, 2, SKIN_STATUS_NOR, FALSE);
		m_comboBaudRate.SnShowImage(_T(".\\res\\bmp\\drop_down.bmp"), 3, 3, SKIN_STATUS_HOT, FALSE);

		m_comboParity.SetCurSel((int)E_COMM_PARITYNONE) ;
		m_comboParity.SnShowImage(_T(".\\res\\bmp\\drop_down.bmp"), 3, 2, SKIN_STATUS_NOR, FALSE);
		m_comboParity.SnShowImage(_T(".\\res\\bmp\\drop_down.bmp"), 3, 3, SKIN_STATUS_HOT, FALSE);

		m_comboBitsize.SetCurSel((int)E_COMM_DATABITS8) ;
		m_comboBitsize.SnShowImage(_T(".\\res\\bmp\\drop_down.bmp"), 3, 2, SKIN_STATUS_NOR, FALSE);
		m_comboBitsize.SnShowImage(_T(".\\res\\bmp\\drop_down.bmp"), 3, 3, SKIN_STATUS_HOT, FALSE);

		m_comboStopBits.SetCurSel((int)E_COMM_STOPONE) ;
		m_comboStopBits.SnShowImage(_T(".\\res\\bmp\\drop_down.bmp"), 3, 2, SKIN_STATUS_NOR, FALSE);
		m_comboStopBits.SnShowImage(_T(".\\res\\bmp\\drop_down.bmp"), 3, 3, SKIN_STATUS_HOT, FALSE);
	}
	catch (...)
	{
	}
}

void CAddRtuSlaveDlg::UpdateAllControl()
{
	try
	{
		UpdateData(TRUE) ;

		CString strPortName(m_rtuSlaveNode.strPortName.c_str()),strBaudRate(_T("")),strBitsize(_T("")) ;
		strBaudRate.Format(_T("%d"), m_rtuSlaveNode.nBaudRate) ;
		strBitsize.Format(_T("%d"), m_rtuSlaveNode.nDataBits) ;

		int nPort = m_comboPort.FindStringExact(0,strPortName) ;
		int nBaudRate = m_comboBaudRate.FindStringExact(0,strBaudRate) ;
		int nDataBits = m_comboBitsize.FindStringExact(0,strBitsize) ;

		m_comboPort.SetCurSel(nPort) ;
		m_comboBaudRate.SetCurSel(nBaudRate) ;
		m_comboParity.SetCurSel(m_rtuSlaveNode.nParity) ;
		m_comboBitsize.SetCurSel(nDataBits) ;
		m_comboStopBits.SetCurSel(m_rtuSlaveNode.nStop) ;

		m_uSlaveID = m_rtuSlaveNode.nSlaveID ;

		UpdateData(FALSE) ;
	}
	catch (...)
	{
	}
}

void CAddRtuSlaveDlg::OnBnClickedOk()
{
	USES_CONVERSION ;
	try
	{
		UpdateData(TRUE) ;

		CString strPortName(_T("")),strBaudRate(_T("")),strBitSize(_T("")) ;

		m_comboPort.GetLBText(m_comboPort.GetCurSel(),strPortName) ;
		m_rtuSlaveNode.strPortName = W2A(strPortName) ;

		m_comboBaudRate.GetLBText(m_comboBaudRate.GetCurSel(),strBaudRate) ;
		m_rtuSlaveNode.nBaudRate = _wtoi(strBaudRate) ;

		m_rtuSlaveNode.nParity = m_comboParity.GetCurSel() ;

		m_comboBitsize.GetLBText(m_comboBitsize.GetCurSel(),strBitSize) ;
		m_rtuSlaveNode.nDataBits = _wtoi(strBitSize) ;

		m_rtuSlaveNode.nStop = m_comboStopBits.GetCurSel() ;

		m_rtuSlaveNode.nSlaveID = (int)m_uSlaveID ;
	}
	catch (...)
	{
	}
	CDialogEx::OnOK();
}