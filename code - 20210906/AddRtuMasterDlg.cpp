// AddRtuMasterDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "VisionProject.h"
#include "AddRtuMasterDlg.h"
#include "afxdialogex.h"

// CAddRtuMasterDlg 对话框

IMPLEMENT_DYNAMIC(CAddRtuMasterDlg, CDialogEx)

CAddRtuMasterDlg::CAddRtuMasterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAddRtuMasterDlg::IDD, pParent)
	, m_uSlaveID(1)
{
}

CAddRtuMasterDlg::~CAddRtuMasterDlg()
{
}

void CAddRtuMasterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_COMBO_PORT, m_comboPort);
	DDX_Control(pDX, IDC_COMBO_BAUDRATE, m_comboBaudRate);
	DDX_Control(pDX, IDC_COMBO_PARITY, m_comboParity);
	DDX_Control(pDX, IDC_COMBO_BITSSIZE, m_comboBitsize);
	DDX_Control(pDX, IDC_COMBO_STOPBITS, m_comboStopBits);
	DDX_Text(pDX, IDC_EDIT_SLAVE_ADDRESS, m_uSlaveID);
}

BEGIN_MESSAGE_MAP(CAddRtuMasterDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAddRtuMasterDlg::OnBnClickedOk)
END_MESSAGE_MAP()

// CAddRtuMasterDlg 消息处理程序

BOOL CAddRtuMasterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitAllControl() ;

	UpdateAllControl() ;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CAddRtuMasterDlg::InitAllControl()
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

void CAddRtuMasterDlg::InitBtnControl()
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

void CAddRtuMasterDlg::InitComboControl()
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

void CAddRtuMasterDlg::UpdateAllControl()
{
	try
	{
		UpdateData(TRUE) ;

		CString strPortName(m_rtuMasterNode.strPortName.c_str()),strBaudRate(_T("")),strBitsize(_T("")) ;
		strBaudRate.Format(_T("%d"), m_rtuMasterNode.nBaudRate) ;
		strBitsize.Format(_T("%d"), m_rtuMasterNode.nDataBits) ;

		int nPort = m_comboPort.FindStringExact(0,strPortName) ;
		int nBaudRate = m_comboBaudRate.FindStringExact(0,strBaudRate) ;
		int nDataBits = m_comboBitsize.FindStringExact(0,strBitsize) ;

		m_comboPort.SetCurSel(nPort) ;
		m_comboBaudRate.SetCurSel(nBaudRate) ;
		m_comboParity.SetCurSel(m_rtuMasterNode.nParity) ;
		m_comboBitsize.SetCurSel(nDataBits) ;
		m_comboStopBits.SetCurSel(m_rtuMasterNode.nStop) ;

		m_uSlaveID = m_rtuMasterNode.nSlaveID ;

		UpdateData(FALSE) ;
	}
	catch (...)
	{
	}
}

void CAddRtuMasterDlg::OnBnClickedOk()
{
	USES_CONVERSION ;
	try
	{
		UpdateData(TRUE) ;

		CString strPortName(_T("")),strBaudRate(_T("")),strBitSize(_T("")) ;

		m_comboPort.GetLBText(m_comboPort.GetCurSel(),strPortName) ;
		m_rtuMasterNode.strPortName = W2A(strPortName) ;

		m_comboBaudRate.GetLBText(m_comboBaudRate.GetCurSel(),strBaudRate) ;
		m_rtuMasterNode.nBaudRate = _wtoi(strBaudRate) ;

		m_rtuMasterNode.nParity = m_comboParity.GetCurSel() ;

		m_comboBitsize.GetLBText(m_comboBitsize.GetCurSel(),strBitSize) ;
		m_rtuMasterNode.nDataBits = _wtoi(strBitSize) ;

		m_rtuMasterNode.nStop = m_comboStopBits.GetCurSel() ;

		m_rtuMasterNode.nSlaveID = (int)m_uSlaveID ;
	}
	catch (...)
	{
	}
	CDialogEx::OnOK();
}