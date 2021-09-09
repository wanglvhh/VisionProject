// DibRadioButton.cpp : implementation file
//
//////////////////////////////////////////////////////////////////////////
// 源文件
// 作者：董陈刚
// 创建日期：2007-12-24
// 最后修改日期：2008-1-2
// 功能：可以自定义位图的RadioButton控件
#include "stdafx.h"
#include "SkinRadio.h"
//#include "../resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDibRadioButton

CDibRadioButton::CDibRadioButton()
{
	// 图标与文字的间距
	m_nSpaceBetween = 4;
	// 1号索引图标（0开始）
	m_radioState = RADIOSTATE_UNSELECT;
	m_tRadioState = RADIOSTATE_UNSELECT;
//	m_bSelected = FALSE;
	m_nSets = BITMAP_SETS;
	m_nSetsID = 0;
	m_nBitmapNumPerSet = BITMAP_PER_SET;
	// 第一套
	m_nSetsID = 0;
	m_bTracking = FALSE;
	m_bMouseOver = FALSE;
	m_bFocused = FALSE;
	m_nButtonStyle = 0;
	m_bChecked = FALSE;
	m_bDisabled = FALSE;

	// 控件背景色
	m_BackColor = RGB(250, 250, 240);// ::GetSysColor(COLOR_WINDOWFRAME);
	// 当前文字背景色
	m_TextBackColor = m_BackColor;
	// 高亮文字背景色
	m_FocusTxtBackColor = ::GetSysColor(COLOR_HIGHLIGHT);
	// 高亮文字颜色为白色
	m_txtFocusColor = RGB(255,55,210);
	// 文字原本颜色为黑色
	m_OriginalTxtColor = RGB(0, 0, 255);
	//当前文字颜色
	m_txtColor = m_OriginalTxtColor;
}

CDibRadioButton::~CDibRadioButton()
{
}

BEGIN_MESSAGE_MAP(CDibRadioButton, CButton)
	//{{AFX_MSG_MAP(CDibRadioButton)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover)
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_WM_KEYDOWN()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
	ON_MESSAGE(BM_SETCHECK, OnSetCheck)
	ON_MESSAGE(BM_GETCHECK, OnGetCheck)
	ON_MESSAGE(BM_SETSTYLE, OnSetStyle)
	ON_MESSAGE(WM_UNCHECKED, OnUnCheck)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDibRadioButton message handlers

void CDibRadioButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: Add your code to draw the specified item
	// 获得CDC
	CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	int saveDc = pDC->SaveDC();//保存当前DC设备
	UINT style = GetStyle();//获取窗口风格
	DrawButton(pDC, lpDrawItemStruct->itemState);//绘制按钮
	pDC->RestoreDC(saveDc);	//释放设备
}
//*
void CDibRadioButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	// 通过设置flag，发送鼠标滑过和鼠标离开消息
	if (!m_bTracking)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE | TME_HOVER;
		tme.dwHoverTime = HOVER_DEFAULT;
		m_bTracking = _TrackMouseEvent(&tme);
	}
	CButton::OnMouseMove(nFlags, point);
}

void CDibRadioButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	POINT pt = point;
	::ClientToScreen(m_hWnd, &pt);
	HWND hWndMouseOver = ::WindowFromPoint(pt);
	// 当鼠标在当前控件上，并且按键按下标记为True时
	if(hWndMouseOver == m_hWnd && m_bPressed)
	{
		if (m_nButtonStyle == BS_RADIOBUTTON)
		{
			SetCheck(1);
			m_radioState = RADIOSTATE_SELMOUSEHOVER;
			// 这里需要设置临时状态是因为考虑到鼠标离开控件时能及时更新改变的状态
			// 确保鼠标离开后，恢复Select状态，而不是选中且获得鼠标焦点
			m_tRadioState = RADIOSTATE_SELECT;
		}
	}

	m_bPressed = FALSE;
	InvalidateRect(NULL);
	TRACE("Left Button Up...\nm_bFocused:%d, m_txtColor:%d, m_txtShowColor:%d\n", m_bFocused, m_txtColor, m_txtFocusColor);
	CButton::OnLButtonUp(nFlags, point);
}

void CDibRadioButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	// 设定一个按下去的图标
	m_radioState = RADIOSTATE_PRESS;
	m_bFocused = TRUE;
	m_bPressed = TRUE;

	InvalidateRect(NULL);
	TRACE("Left Button Down...\n");
	CButton::OnLButtonDown(nFlags, point);
}

void CDibRadioButton::PreSubclassWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	// 得到控件文字
 	GetWindowText(m_strTxt);
// 	// 设置位图样式
 	SetSetsID(1);
//
	m_bChecked = GetCheck();		// 在之前可能已经SetCheck
// 	// 得到Button样式
 	m_nButtonStyle = GetButtonStyle();
 	// 设置BS_AUTORADIOBUTTON和BS_RADIOBUTTON都为BS_RADIOBUTTON样式
 	if(m_nButtonStyle == BS_AUTORADIOBUTTON || m_nButtonStyle == (BS_AUTORADIOBUTTON | BS_RADIOBUTTON))
 	{
 		m_nButtonStyle = BS_RADIOBUTTON;
 	}
	//SetRadioBitmap(IDB_BITMAP1);
	CButton::PreSubclassWindow();
	// 自绘
	ModifyStyle(0, BS_OWNERDRAW);
}

void CDibRadioButton::SetRadioBitmap(UINT uiID)
{
	m_uiBitmap = uiID;
}

void CDibRadioButton::SetBackColor(COLORREF colRGB)
{
	m_BackColor = colRGB;
	InvalidateRect(NULL);
}

void CDibRadioButton::SetTextBackColor(COLORREF colRGB)
{
	m_TextBackColor = colRGB;
	InvalidateRect(NULL);
}

void CDibRadioButton::DrawButton(CDC* pDC, UINT state)
{
	CBitmap cBmp;
	// 载入位图
	BOOL bRet = cBmp.LoadBitmap(m_uiBitmap);

	BITMAP bitmapInfo;
	if (bRet)
	{
		cBmp.GetBitmap(&bitmapInfo);
	}

	// 内存环境
	CDC dcMemory;
	dcMemory.CreateCompatibleDC(pDC);
	CBitmap *oldBitmap = dcMemory.SelectObject(&cBmp);
	CRect rect;
	GetWindowRect(&rect);//得到按钮大小
	// 得到显示文字的大小
	CSize titleSize = pDC->GetTextExtent(m_strTxt);
	// 显示在中间位置
	int YPos = (rect.Height() - BITMAP_HEIGHT) / 2;
	// 如果边框高度小于图像高度，对齐水平中心线
 	YPos = YPos >= 0 ? YPos : rect.top - (BITMAP_HEIGHT - rect.Height()) / 2;

	int content_length = BITMAP_WIDTH + m_nSpaceBetween + titleSize.cx;
	int XPos = 0;
	if (ODS_DISABLED & state)
	{
		m_bDisabled = TRUE;
		m_radioState = RADIOSTATE_DISABLE;
	}

	CRect rcClient;
	GetClientRect(rcClient);
	// 绘制控件背景色
//	m_BackColor = RGB(255, 255, 255);
	pDC->FillSolidRect(rcClient, m_BackColor);
	pDC->SetBkMode(TRANSPARENT);

	CFont font;
	font.CreatePointFont(110, _T("微软雅黑"));
	pDC->SelectObject(font);

	// 单独绘制文字背景色
	//if (m_bFocused)
	//{
	//	rcClient.right =  rcClient.left + BITMAP_WIDTH + m_nSpaceBetween + titleSize.cx;
	//	rcClient.left =  rcClient.left + BITMAP_WIDTH + m_nSpaceBetween;
	//	pDC->FillSolidRect(rcClient, m_TextBackColor);
	//}
	// 绘制位图
	pDC->BitBlt(XPos, YPos, BITMAP_WIDTH, BITMAP_HEIGHT, &dcMemory, \
		// 具体对应位图：(套ID×每套位图数+状态索引) × 单个图标宽度
		(m_nSetsID * m_nBitmapNumPerSet + m_radioState) * BITMAP_WIDTH,\
		0, SRCCOPY);

	if (!m_strTxt.IsEmpty())
	{
		CPoint pt(XPos + BITMAP_WIDTH + m_nSpaceBetween, YPos - 5);

		int mode = pDC->SetBkMode(TRANSPARENT);
		if (m_bDisabled)
		{
			pDC->DrawState(pt, titleSize, m_strTxt, DSS_DISABLED, TRUE, 0, (HBRUSH)NULL);
		}
		else
		{
			pDC->SetTextColor(m_txtColor);
			pDC->DrawState(pt, titleSize, m_strTxt, DSS_NORMAL, TRUE, 0, (HBRUSH)NULL);
			if (m_bFocused)
			{
// 				CRect txtRect(pt, titleSize);
// 				txtRect.left -= 1;
// 				txtRect.right += 1;
// 				pDC->DrawFocusRect(&txtRect);
 			}
		}
	}
	cBmp.DeleteObject();
	dcMemory.SelectObject(oldBitmap);
	dcMemory.DeleteDC();
}

void CDibRadioButton::SetTextColor(COLORREF txtColor)
{
	m_txtColor = txtColor;
	InvalidateRect(NULL);
}

void CDibRadioButton::SetSetsID(int nSetID)
{
	// 当选择的图标套数ID小于0或者大于现有套数上限，则不做修改
	if (nSetID < 0 || nSetID > BITMAP_SETS - 1)
	{
		return;
	}
	m_nSetsID = nSetID;
}

LRESULT CDibRadioButton::OnMouseHover( WPARAM wParam, LPARAM lParam )
{
	m_bMouseOver = TRUE;
	TRACE("%s MouseHover ChangeBefore... m_bTracking = %d, mbOver = %d, m_tRadioState = %d,\
		m_radioState = %d\n", m_strTxt, m_bTracking, m_bMouseOver, m_tRadioState, m_radioState);
	// 保存最后的状态样式
	if (m_bChecked)
	{
		m_radioState = RADIOSTATE_SELMOUSEHOVER;
	}
	else
	{
		m_radioState = RADIOSTATE_UNSELMOUSEHOVER;
	}
	TRACE("%s MouseHover ChangeLater... m_bTracking = %d, mbOver = %d, m_tRadioState = %d, m_radioState = %d\n",
		m_strTxt, m_bTracking, m_bMouseOver, m_tRadioState, m_radioState);
	 //SetTextBackColor(RGB(247, 117, 0));
	InvalidateRect(NULL);
	return 0;
}

LRESULT CDibRadioButton::OnMouseLeave( WPARAM wParam, LPARAM lParam )
{
	m_bMouseOver = FALSE;
	m_bTracking = FALSE;
	TRACE("%s MouseLeave ChangeBefore... m_bTracking = %d, mbOver = %d, m_tRadioState = %d, m_radioState = %d\n",
		m_strTxt, m_bTracking, m_bMouseOver, m_tRadioState, m_radioState);
	// 还原样式
	m_radioState = m_tRadioState;
	TRACE("%s, MouseLeave ChangeLater... m_bTracking = %d, mbOver = %d, m_tRadioState = %d, m_radioState = %d\n",
		m_strTxt, m_bTracking, m_bMouseOver, m_tRadioState, m_radioState);
	TRACE("%c", '\n');
	InvalidateRect(NULL);
	return 0;
}

BOOL CDibRadioButton::Create( LPCTSTR lpszCaption, DWORD dwStyle, const RECT &rect, CWnd *pParentWnd, UINT nID )
{
	dwStyle &= ~(0xF);		// remove styles with conflict with group box
	dwStyle |= BS_AUTORADIOBUTTON;	// add group box style
	return CButton::Create(lpszCaption, dwStyle, rect, pParentWnd, nID);
}

LRESULT CDibRadioButton::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class
	// 捕获屏蔽双击消息
	if (message == WM_LBUTTONDBLCLK)
	{
		message = WM_LBUTTONDOWN;
	}
	return CButton::DefWindowProc(message, wParam, lParam);
}

LRESULT CDibRadioButton::OnUnCheck( WPARAM wParam, LPARAM lParam )
{
	// 这里不要去用SetCheck，这样会触发OnSetCheck，再触发本函数而导致死循环
	if(m_bChecked)
	{
		m_bChecked = FALSE;
		m_radioState = RADIOSTATE_UNSELECT;
		m_tRadioState = m_radioState;
		InvalidateRect(NULL);//使整个窗口无效 同Invalidate
	}
	return 0;
}

LRESULT CDibRadioButton::OnSetCheck( WPARAM wParam, LPARAM lParam )
{
	// 这里的目的是把同组内所有radiobutton设置为unCheck
	// 首先得到check标志
	m_bChecked = (wParam != 0);
	if(m_bChecked)
	{
		CPtrList list;
		list.AddTail((void*)m_hWnd);
		// 得到父窗口句柄
		HWND hWndParent = GetParent()->GetSafeHwnd();
		// 得到控件窗口句柄
		HWND hWnd = GetSafeHwnd();
		while(hWnd)
		{
			// 得到同组内的空间的窗口句柄
			hWnd = ::GetNextDlgGroupItem(hWndParent, hWnd, 0);
			CWnd* pWnd = CWnd::FromHandle(hWnd);
			if(pWnd)
			{
				// 得到控件资源ID
				int nID = pWnd->GetDlgCtrlID();
			}
			// 在list中查找这个句柄是否被查询到过（这里就只有第一个Group的控件）
			POSITION pos = list.Find((void*)hWnd);

			if(pos)
			{
				// 如果找到了这个句柄，那就代表搜索到头了
				hWnd = NULL;
			}
			if(hWnd)
			{
				// 没有搜索完一组，那么就把当前的句柄添加到list中去（目的是为了不让同一控件被发送两次消息）
				list.AddTail((void*)hWnd);
				// 对这个控件发送unChecked的消息
				::PostMessage(hWnd, WM_UNCHECKED, 0, 0);
			}
		}
		m_radioState = RADIOSTATE_SELECT;
		m_tRadioState = m_radioState;
	}
	else
	{
		// 设置当前为checked
		m_radioState = RADIOSTATE_UNSELECT;
		m_tRadioState = m_radioState;
	}
	InvalidateRect(NULL);
	return 0;
}

LRESULT CDibRadioButton::OnGetCheck( WPARAM wParam, LPARAM lParam )
{
	// 直接返回Check标志
	return m_bChecked;
}

LRESULT CDibRadioButton::OnSetStyle( WPARAM wParam, LPARAM lParam )
{
	// 改变样式的时候添加上自绘样式
	wParam |= BS_OWNERDRAW;

	return DefWindowProc(BM_SETSTYLE, wParam, lParam);
}

void CDibRadioButton::OnSetFocus(CWnd* pOldWnd)
{
	m_bFocused = TRUE;
	// 设置文字背景
	m_TextBackColor = m_FocusTxtBackColor;
	// 设置文字颜色
	m_txtColor = m_txtFocusColor;
	InvalidateRect(NULL);
	CButton::OnSetFocus(pOldWnd);
}

void CDibRadioButton::OnKillFocus(CWnd* pNewWnd)
{
	if(::GetCapture() == m_hWnd)
	{
        ::ReleaseCapture();
    }

	m_bPressed = FALSE;
	m_bFocused = FALSE;
	m_bMouseOver = FALSE;

	// 设置文字背景
	m_TextBackColor = m_FocusTxtBackColor;
	// 设置文字颜色
	m_txtColor = m_OriginalTxtColor;
	// 设置文字背景颜色
	m_TextBackColor = m_BackColor;
	InvalidateRect(NULL);

	CButton::OnKillFocus(pNewWnd);

	// TODO: Add your message handler code here
}

void CDibRadioButton::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if (m_nButtonStyle && nChar == ' ')
	{
		if (m_nButtonStyle == BS_RADIOBUTTON) SetCheck(1);
	}
	CButton::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CDibRadioButton::InvalidateThumbRect()
{
	CRect rect;
	GetWindowRect(&rect);
	rect.right = BITMAP_WIDTH;
	rect.top = rect.CenterPoint().y - BITMAP_HEIGHT / 2;
	rect.bottom = rect.top + BITMAP_HEIGHT;
	InvalidateRect(&rect);
}

void CDibRadioButton::SetOriginalTxtColor(COLORREF oriTxtColor)
{
	m_OriginalTxtColor = oriTxtColor;
	m_txtColor = oriTxtColor;
	InvalidateRect(NULL);
}

COLORREF CDibRadioButton::GetOriginalTxtColor()
{
	// 这里要得到原文字的颜色，不是高亮的
	return m_OriginalTxtColor;
}

void CDibRadioButton::SetFocusTxtColor(COLORREF txtFocusColor)
{
	m_txtFocusColor = txtFocusColor;
	InvalidateRect(NULL);
}

COLORREF CDibRadioButton::GetFocusTxtColor()
{
	return m_txtFocusColor;
}

COLORREF CDibRadioButton::GetCurrentTxtColor()
{
	return m_txtColor;
}

void CDibRadioButton::SetFocusTxtBackColor(COLORREF focusTxtBackColor)
{
	m_FocusTxtBackColor = focusTxtBackColor;
	InvalidateRect(NULL);
}

void CDibRadioButton::SetRadioText(const char *str)
{
    m_strTxt = str;
}