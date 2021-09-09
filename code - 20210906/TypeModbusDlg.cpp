// TypeModbusDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VisionProject.h"
#include "TypeModbusDlg.h"
#include "afxdialogex.h"

// CTypeModbusDlg �Ի���

IMPLEMENT_DYNAMIC(CTypeModbusDlg, CDialogEx)

CTypeModbusDlg::CTypeModbusDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTypeModbusDlg::IDD, pParent)
	, m_nModbusType(0)
	, m_strModbusName(_T(""))
{
}

CTypeModbusDlg::~CTypeModbusDlg()
{
}

void CTypeModbusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Radio(pDX, IDC_RADIO_MODBUS_RTUMASTER, m_nModbusType);
	DDX_Text(pDX, IDC_EDIT_MODBUSNAME, m_strModbusName);
}

BEGIN_MESSAGE_MAP(CTypeModbusDlg, CDialogEx)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO_MODBUS_RTUMASTER, IDC_RADIO_MODBUS_TCPSLAVE, OnRadioClicked)
	ON_EN_CHANGE(IDC_EDIT_MODBUSNAME, &CTypeModbusDlg::OnEnChangeEditModbusname)
END_MESSAGE_MAP()

// CTypeModbusDlg ��Ϣ�������

BOOL CTypeModbusDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitBtnControl() ;

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CTypeModbusDlg::InitAllControl()
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

void CTypeModbusDlg::InitBtnControl()
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

void CTypeModbusDlg::OnRadioClicked(UINT uRadioId)
{
	UpdateData(TRUE) ;
}

void CTypeModbusDlg::OnEnChangeEditModbusname()
{
	UpdateData(TRUE) ;
}