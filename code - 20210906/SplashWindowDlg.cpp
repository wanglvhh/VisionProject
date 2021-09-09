// SplashWindowDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VisionProject.h"
#include "SplashWindowDlg.h"
#include "afxdialogex.h"

// CSplashWindowDlg �Ի���
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(CSplashWindowDlg, CDialogEx)

CSplashWindowDlg::CSplashWindowDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSplashWindowDlg::IDD, pParent)
{
}

CSplashWindowDlg::~CSplashWindowDlg()
{
}

void CSplashWindowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSplashWindowDlg, CDialogEx)
END_MESSAGE_MAP()

// CSplashWindowDlg ��Ϣ�������

BOOL CSplashWindowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rt;
	GetClientRect(rt);
	m_BitmapCtrl.Create(rt, this, 12345);

	m_BitmapCtrl.LoadBitmap(IDB_BITMAP_SPLASH);
	m_BitmapCtrl.Refresh();

	GetClientRect(m_rtWnd);

	CDC *pDC = m_BitmapCtrl.GetMemDC();
	if(NULL != pDC)
	{
		pDC->SelectObject(&m_Font);
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(SYSTEM_RED);

		CSize size = pDC->GetTextExtent(_T("����"));
		m_nFonHeight = size.cy ;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

BOOL CSplashWindowDlg::PreTranslateMessage(MSG* pMsg)
{
	//���λس���esc
	if(WM_KEYDOWN == pMsg->message && (VK_ESCAPE == pMsg->wParam || VK_RETURN == pMsg->wParam))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CSplashWindowDlg::LoadBitmap(UINT nID)
{
	m_BitmapCtrl.LoadBitmap(nID);
}

void CSplashWindowDlg::ShowTip(LPCTSTR lpszTip)
{
	GetDlgItem(IDC_STATIC_SPLASH)->ShowWindow(SW_HIDE);
	m_BitmapCtrl.LoadBitmap(IDB_BITMAP_SPLASH);

	CDC *pDC = m_BitmapCtrl.GetMemDC();
	if(NULL != pDC)
	{
		pDC->SelectObject(&m_Font);
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(SYSTEM_RED);

		pDC->TextOut(10, m_rtWnd.bottom - m_nFonHeight - 10, lpszTip);
		m_BitmapCtrl.Refresh();
	}
}