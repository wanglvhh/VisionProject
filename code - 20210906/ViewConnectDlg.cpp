// ViewConnectDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "VisionProject.h"
#include "ViewConnectDlg.h"
#include "afxdialogex.h"
#include "VisionProjectDlg.h"

// CViewConnectDlg 对话框
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(CViewConnectDlg, CDialogEx)

CViewConnectDlg::CViewConnectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CViewConnectDlg::IDD, pParent)
{
	m_strWorkFlowName = _T("") ;
}

CViewConnectDlg::~CViewConnectDlg()
{
}

void CViewConnectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_WORKLIST, m_comboWorkList);
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
}

BEGIN_MESSAGE_MAP(CViewConnectDlg, CDialogEx)
	ON_CONTROL_RANGE(BN_CLICKED, IDOK, IDCANCEL, OnButtonClicked)
END_MESSAGE_MAP()

// CViewConnectDlg 消息处理程序

BOOL CViewConnectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitAllControl() ;

	UpdateComboControl() ;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CViewConnectDlg::InitAllControl()
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

void CViewConnectDlg::InitBtnControl()
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

void CViewConnectDlg::InitComboControl()
{
	try
	{
		m_comboWorkList.SetCurSel((int)E_TOOL_CAMERA_HALCON-1) ;
		m_comboWorkList.SnShowImage(_T(".\\res\\bmp\\drop_down.bmp"), 3, 2, SKIN_STATUS_NOR, FALSE);
		m_comboWorkList.SnShowImage(_T(".\\res\\bmp\\drop_down.bmp"), 3, 3, SKIN_STATUS_HOT, FALSE);
	}
	catch (...)
	{
	}
}

void CViewConnectDlg::UpdateComboControl()
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		int nWorkFlowDlgCount = pDlg->m_projectData.m_mgWorkFlowDlg.GetWorkFlowDlgListSize() ;
		if (nWorkFlowDlgCount <= 0) return ;
		for (int i = 0 ;i < pDlg->m_projectData.m_mgWorkFlowDlg.GetWorkFlowDlgListSize();i++)
		{
			CInterfaceWorkFlowDlg *pInterfaceWorkFlowDlg = pDlg->m_projectData.m_mgWorkFlowDlg.GetWorkFlowDlgById(i) ;
			m_comboWorkList.AddString(pInterfaceWorkFlowDlg->strWorkFlowDlgName) ;
		}
		m_comboWorkList.SetCurSel(0) ;
	}
	catch (...)
	{
	}
}

void CViewConnectDlg::OnButtonClicked(UINT uBtnId)
{
	try
	{
		switch(uBtnId)
		{
		case IDOK:
			{
				int nCurSel = m_comboWorkList.GetCurSel() ;
				m_comboWorkList.GetLBText(nCurSel,m_strWorkFlowName) ;

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