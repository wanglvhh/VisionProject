// CommConnectDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "VisionProject.h"
#include "CommConnectDlg.h"
#include "afxdialogex.h"

// CCommConnectDlg 对话框
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(CCommConnectDlg, CDialogEx)

CCommConnectDlg::CCommConnectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCommConnectDlg::IDD, pParent)
{
	m_strSelCommInfo = _T("") ;
	m_arrayCommInfo.RemoveAll() ;
}

CCommConnectDlg::~CCommConnectDlg()
{
	m_strSelCommInfo = _T("") ;
	m_arrayCommInfo.RemoveAll() ;
}

void CCommConnectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_COMBO_COMMUNICATIONLIST, m_comboCommList);
}

BEGIN_MESSAGE_MAP(CCommConnectDlg, CDialogEx)
	ON_CONTROL_RANGE(BN_CLICKED, IDOK, IDCANCEL, OnButtonClicked)
END_MESSAGE_MAP()

// CCommConnectDlg 消息处理程序

BOOL CCommConnectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitAllControl() ;

	UpdateComboControl() ;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CCommConnectDlg::InitAllControl()
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

void CCommConnectDlg::InitBtnControl()
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

void CCommConnectDlg::InitComboControl()
{
	try
	{
		m_comboCommList.SetCurSel(0) ;
		m_comboCommList.SnShowImage(_T(".\\res\\bmp\\drop_down.bmp"), 3, 2, SKIN_STATUS_NOR, FALSE);
		m_comboCommList.SnShowImage(_T(".\\res\\bmp\\drop_down.bmp"), 3, 3, SKIN_STATUS_HOT, FALSE);
	}
	catch (...)
	{
	}
}

void CCommConnectDlg::UpdateComboControl()
{
	try
	{
		int nCameraCount = (int)m_arrayCommInfo.GetSize() ;
		if (nCameraCount <= 0)
			return ;

		for (int i = 0 ;i < nCameraCount;i++)
		{
			m_comboCommList.AddString(m_arrayCommInfo.GetAt(i)) ;
		}

		m_comboCommList.SetCurSel(0) ;
	}
	catch (...)
	{
	}
}

void CCommConnectDlg::OnButtonClicked(UINT uBtnId)
{
	try
	{
		switch(uBtnId)
		{
		case IDOK:
			{
				int nCurSel = m_comboCommList.GetCurSel() ;
				m_comboCommList.GetLBText(nCurSel,m_strSelCommInfo) ;

				CDialogEx::OnOK() ;
				break;
			}
		case IDCANCEL:
			{
				CDialogEx::OnCancel() ;
				break ;
			}
		default:
			break;
		}
	}
	catch (...)
	{
	}
}