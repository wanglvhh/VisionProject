// Para1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "VisionCommWrite.h"
#include "Para1Dlg.h"
#include "afxdialogex.h"
#include "MainDlg.h"

// CPara1Dlg 对话框
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(CPara1Dlg, CDialogEx)

CPara1Dlg::CPara1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPara1Dlg::IDD, pParent)
	, m_strSendData(_T(""))
{
}

CPara1Dlg::~CPara1Dlg()
{
}

void CPara1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SENDDATA, m_strSendData);
}

BEGIN_MESSAGE_MAP(CPara1Dlg, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_EN_CHANGE(IDC_EDIT_SENDDATA, &CPara1Dlg::OnEnChangeEditSenddata)
END_MESSAGE_MAP()

// CPara1Dlg 消息处理程序

BOOL CPara1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_brush.CreateSolidBrush(SYSTEM_BK_COLOR) ;

	InitAllControl() ;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

HBRUSH CPara1Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return m_brush;
}

void CPara1Dlg::InitAllControl()
{
	try
	{
		return ;
	}
	catch (...)
	{
	}
}

void CPara1Dlg::UpdateAllControl()
{
	CMainDlg *pDlg = (CMainDlg *)FindWindow(NULL, _T("通信写入")) ;
	try
	{
		UpdateData(FALSE) ;
	}
	catch (...)
	{
	}
}

void CPara1Dlg::OnEnChangeEditSenddata()
{
	UpdateData(TRUE) ;
}