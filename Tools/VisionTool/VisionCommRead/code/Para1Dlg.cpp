// Para1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "VisionCommRead.h"
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
	, m_dbWaitTime(0)
{
}

CPara1Dlg::~CPara1Dlg()
{
}

void CPara1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_WAITTIME, m_dbWaitTime);
	DDX_Control(pDX, IDC_RICHEDIT21, m_ctlSysTipsDisplay1);
}

BEGIN_MESSAGE_MAP(CPara1Dlg, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_EN_CHANGE(IDC_EDIT_WAITTIME, &CPara1Dlg::OnEnChangeEditWaittime)
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
		//初始化RichEidtControl
		InitRichEdit() ;
	}
	catch (...)
	{
	}
}

void CPara1Dlg::InitRichEdit()
{
	try
	{
		m_ctlSysTipsDisplay1.SetBackgroundColor(FALSE, SYSTEM_WHITE);
	}
	catch (...)
	{
	}
}

void CPara1Dlg::UpdateAllControl()
{
	CMainDlg *pDlg = (CMainDlg *)FindWindow(NULL, _T("通信读取")) ;
	try
	{
		UpdateData(FALSE) ;
	}
	catch (...)
	{
	}
}

void CPara1Dlg::SetSysTipsInfo(CString strInfo, COLORREF crColor)
{
	try
	{
		CHARFORMAT cf;
		memset(&cf, 0, sizeof(CHARFORMAT));

		m_ctlSysTipsDisplay1.GetSelectionCharFormat(cf);
		cf.dwMask = CFM_COLOR | CFM_SIZE;
		cf.yHeight = 218;
		cf.cbSize = 1000;
		cf.crTextColor = crColor;
		cf.dwEffects = 0;
		m_ctlSysTipsDisplay1.SetSelectionCharFormat(cf);

		CString strLine = _T(""), strEdit = _T("");

		m_ctlSysTipsDisplay1.GetWindowText(strEdit);
		m_ctlSysTipsDisplay1.SetSel(-1, -1);
		strLine.Format(_T("%s\r\n"), strInfo);
		m_ctlSysTipsDisplay1.ReplaceSel(strLine);

		HWND  hWnd = (HWND)m_ctlSysTipsDisplay1;
		int line = ::SendMessage(hWnd, EM_GETFIRSTVISIBLELINE, 0, 0);
		int linecount = ::SendMessage(hWnd, EM_GETLINECOUNT, 0, 0);

		::SendMessage(hWnd, EM_LINESCROLL, 0, (linecount - line - 2));

		//Cancel select all text in richedit control
		m_ctlSysTipsDisplay1.SetOptions(ECOOP_OR, ECO_SAVESEL);
	}
	catch (...)
	{
	}
}

void CPara1Dlg::OnEnChangeEditWaittime()
{
	UpdateData(TRUE) ;
}