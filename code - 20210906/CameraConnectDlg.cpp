// CameraConnectDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "VisionProject.h"
#include "CameraConnectDlg.h"
#include "afxdialogex.h"

// CCameraConnectDlg 对话框
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(CCameraConnectDlg, CDialogEx)

CCameraConnectDlg::CCameraConnectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCameraConnectDlg::IDD, pParent)
{
	m_strSelCameraInfo = _T("") ;
	m_arrayCameraInfo.RemoveAll() ;
}

CCameraConnectDlg::~CCameraConnectDlg()
{
	m_strSelCameraInfo = _T("") ;
	m_arrayCameraInfo.RemoveAll() ;
}

void CCameraConnectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CAMERALIST, m_comboCameraList);
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
}

BEGIN_MESSAGE_MAP(CCameraConnectDlg, CDialogEx)
	ON_CONTROL_RANGE(BN_CLICKED, IDOK, IDCANCEL, OnButtonClicked)
END_MESSAGE_MAP()

// CCameraConnectDlg 消息处理程序

BOOL CCameraConnectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitAllControl() ;

	UpdateComboControl() ;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CCameraConnectDlg::InitAllControl()
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

void CCameraConnectDlg::InitBtnControl()
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

void CCameraConnectDlg::InitComboControl()
{
	try
	{
		m_comboCameraList.SetCurSel(0) ;
		m_comboCameraList.SnShowImage(_T(".\\res\\bmp\\drop_down.bmp"), 3, 2, SKIN_STATUS_NOR, FALSE);
		m_comboCameraList.SnShowImage(_T(".\\res\\bmp\\drop_down.bmp"), 3, 3, SKIN_STATUS_HOT, FALSE);
	}
	catch (...)
	{
	}
}

void CCameraConnectDlg::UpdateComboControl()
{
	try
	{
		int nCameraCount = (int)m_arrayCameraInfo.GetSize() ;
		if (nCameraCount <= 0)
			return ;

		for (int i = 0 ;i < nCameraCount;i++)
		{
			m_comboCameraList.AddString(m_arrayCameraInfo.GetAt(i)) ;
		}

		m_comboCameraList.SetCurSel(0) ;
	}
	catch (...)
	{
	}
}

void CCameraConnectDlg::OnButtonClicked(UINT uBtnId)
{
	try
	{
		switch(uBtnId)
		{
		case IDOK:
			{
				int nCurSel = m_comboCameraList.GetCurSel() ;
				m_comboCameraList.GetLBText(nCurSel,m_strSelCameraInfo) ;

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