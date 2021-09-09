// TypeCommDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "VisionProject.h"
#include "TypeCommDlg.h"
#include "afxdialogex.h"

// CTypeCommDlg 对话框

IMPLEMENT_DYNAMIC(CTypeCommDlg, CDialogEx)

CTypeCommDlg::CTypeCommDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTypeCommDlg::IDD, pParent)
	, m_nCommType(0)
	, m_strCommName(_T(""))
{
}

CTypeCommDlg::~CTypeCommDlg()
{
}

void CTypeCommDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_COMM232, m_nCommType);
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Text(pDX, IDC_EDIT_COMMNAME, m_strCommName);
}

BEGIN_MESSAGE_MAP(CTypeCommDlg, CDialogEx)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO_COMM232, IDC_RADIO_COMMTCP, OnRadioClicked)
	ON_EN_CHANGE(IDC_EDIT_COMMNAME, &CTypeCommDlg::OnEnChangeEditCommname)
END_MESSAGE_MAP()

// CTypeCommDlg 消息处理程序

BOOL CTypeCommDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitAllControl() ;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CTypeCommDlg::InitAllControl()
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

void CTypeCommDlg::InitBtnControl()
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

void CTypeCommDlg::OnRadioClicked(UINT uRadioId)
{
	UpdateData(TRUE) ;
}

void CTypeCommDlg::OnEnChangeEditCommname()
{
	UpdateData(TRUE) ;
}