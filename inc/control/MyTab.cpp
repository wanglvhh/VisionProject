// MyTab.cpp : implementation file
//

#include "stdafx.h"

#include "MyTab.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyTab

CMyTab::CMyTab()
{
	m_itemcount=0;
	m_ptTabs.x=4;
	m_ptTabs.y=28;
	m_bMove=true;
	m_ispeed=10;
}

CMyTab::~CMyTab()
{
}

BEGIN_MESSAGE_MAP(CMyTab, CTabCtrl)
	//{{AFX_MSG_MAP(CMyTab)
	ON_WM_TIMER()
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, OnSelchange)
	ON_NOTIFY_REFLECT(TCN_SELCHANGING, OnSelchanging)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyTab message handlers

void CMyTab::AddItem(CWnd *pwnd, LPTSTR name)
{
	TCITEM item;
	item.mask = TCIF_TEXT|TCIF_PARAM;
	item.lParam = (LPARAM) pwnd;
	item.pszText = name;
	InsertItem(m_itemcount, &item);

	pwnd->SetWindowPos(NULL, m_ptTabs.x, m_ptTabs.y , 0, 0,
						SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER);
	if(m_itemcount==0)
	{
		pwnd->ShowWindow(SW_SHOW);//显示第一个子窗体
	}
	else
	{
		pwnd->ShowWindow(SW_HIDE);
	}

	m_itemcount++;
}

void CMyTab::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	CRect rect1;
	m_pCurWnd->GetWindowRect(&rect1);
	ScreenToClient(&rect1);//注意
	GetWindowRect(&m_tabrect);
	ScreenToClient(&m_tabrect);//注意
	if(rect1.left<4-m_ispeed)
	{
		rect1.TopLeft().x+=m_ispeed;
		rect1.BottomRight().x+=m_ispeed;
		m_pCurWnd->MoveWindow(&rect1,true);
	}
	else
	{
		rect1.TopLeft().x=4;
		rect1.BottomRight().x=4+m_wndwidth;
		m_pCurWnd->MoveWindow(&rect1,true);//移到初始位置
		KillTimer(1);
	}
	CTabCtrl::OnTimer(nIDEvent);
}
void CMyTab::OnSelchange(NMHDR* pNMHDR, LRESULT* pResult) //单击选项卡后触发
{
	int iNewTab = GetCurSel();
	TCITEM item;
	CWnd* pWnd;
	item.mask = TCIF_PARAM;
	//** show the selected tab --------
	GetItem(iNewTab, &item);
	pWnd = reinterpret_cast<CWnd*> (item.lParam);
	ASSERT_VALID(pWnd);
	if(m_bMove)
	{
		CRect rect;
		pWnd->GetWindowRect(&rect);

		ScreenToClient(&rect);//注意
		m_wndwidth=rect.Width();
		m_topleft=rect.TopLeft();
		m_bottomright=rect.BottomRight();
		m_topleft.x-=rect.Width();
		m_bottomright.x-=rect.Width();

		rect.SetRect(m_topleft,m_bottomright);
		pWnd->MoveWindow(&rect,true);//将当前子窗体移到左边
		pWnd->ShowWindow(SW_SHOW);
		m_pCurWnd=pWnd;

		SetTimer(1,10,NULL);//开始运动
	}
	else
		pWnd->ShowWindow(SW_SHOW);
	*pResult = 0;
}

void CMyTab::OnSelchanging(NMHDR* pNMHDR, LRESULT* pResult) //单击选项卡时触发
{
	// TODO: Add your control notification handler code here
	int iNewTab = GetCurSel();
	TCITEM item;
	CWnd* pWnd;
	item.mask = TCIF_PARAM;

	//** hide the current tab ---------
	GetItem(iNewTab, &item);
	pWnd = reinterpret_cast<CWnd*> (item.lParam);
	ASSERT_VALID(pWnd);
	pWnd->ShowWindow(SW_HIDE);
	*pResult = 0;
}

int CMyTab::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTabCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	GetWindowRect(&m_tabrect);
	return 0;
}