// BitmapWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "BitmapCtrl.h"
#include <atlimage.h>

#define BITMAPCTRL_CLASSNAME	_T("MFCBitmapCtrl")
#define BITMAPCTRL_WINDOWNAME	_T("BitmapCtrl")
//////////////////////////////////////////////////////////////////////////
// CBitmapCtrl

IMPLEMENT_DYNAMIC(CBitmapCtrl, CWnd)

CBitmapCtrl::CBitmapCtrl()
{
	m_pScrDC = NULL;
	m_pMemDC = NULL;
	m_BitmapSize.cx = m_BitmapSize.cy = 500;
	m_bLoad = FALSE;

	RegisterWindowClass();
}

CBitmapCtrl::~CBitmapCtrl()
{
	if(NULL != m_pMemDC)
	{
		delete m_pMemDC;
		m_pMemDC = NULL;

		m_Bitmap.DeleteObject();
	}
}

BEGIN_MESSAGE_MAP(CBitmapCtrl, CWnd)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CBitmapCtrl 消息处理程序
//////////////////////////////////////////////////////////////////////////
BOOL CBitmapCtrl::RegisterWindowClass()
{
	WNDCLASS wndcls;
	HINSTANCE hInst = AfxGetInstanceHandle();

	if(!(::GetClassInfo(hInst, BITMAPCTRL_CLASSNAME, &wndcls)))
	{
		// otherwise we need to register a new class
		wndcls.style            = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
		wndcls.lpfnWndProc      = ::DefWindowProc;
		wndcls.cbClsExtra       = wndcls.cbWndExtra = 0;
		wndcls.hInstance        = hInst;
		wndcls.hIcon            = NULL;
		wndcls.hCursor          = NULL;
		wndcls.hbrBackground    = (HBRUSH)(COLOR_3DFACE + 1);
		wndcls.lpszMenuName     = NULL;
		wndcls.lpszClassName    = BITMAPCTRL_CLASSNAME;

		if(!AfxRegisterClass(&wndcls))
		{
			AfxThrowResourceException();
			return FALSE;
		}
	}

	return TRUE;
}

BOOL CBitmapCtrl::Create(const RECT& rect, CWnd* parent,
	UINT nID, DWORD dwStyle /* = WS_CHILD | WS_BORDER | WS_TABSTOP | WS_VISIBLE */)
{
	ASSERT(parent->GetSafeHwnd());

	if(!CWnd::Create(BITMAPCTRL_CLASSNAME, BITMAPCTRL_WINDOWNAME, dwStyle, rect, parent, nID))
		return FALSE;

	return TRUE;
}

BOOL CBitmapCtrl::PreCreateWindow(CREATESTRUCT& cs)
{
	return CWnd::PreCreateWindow(cs);
}

BOOL CBitmapCtrl::PreTranslateMessage(MSG* pMsg)
{
	return CWnd::PreTranslateMessage(pMsg);
}

BOOL CBitmapCtrl::OnEraseBkgnd(CDC* pDC)
{
	CWnd::OnEraseBkgnd(pDC);

	Refresh();

	return TRUE;
}

BOOL CBitmapCtrl::LoadBitmap(LPCTSTR lpszPath)
{
	//载入位图
	if(NULL == lpszPath)
		return FALSE;

	CImage image;
	if(S_OK != image.Load(lpszPath))
		return FALSE;

	HBITMAP hBitmap = image.Detach();
	if(NULL == hBitmap)
		return FALSE;

	CBitmap *pBmp = CBitmap::FromHandle(hBitmap);
	if(NULL == pBmp)
	{
		DeleteObject(hBitmap);
		return FALSE;
	}

	BITMAP stuBitmap;
	pBmp->GetBitmap(&stuBitmap);
	m_BitmapSize.cx = stuBitmap.bmWidth;
	m_BitmapSize.cy = stuBitmap.bmHeight;

	CBrush brush;
	brush.CreatePatternBrush(pBmp);

	m_bLoad = TRUE;

	//初始化内存DC
	ReleaseDC();
	InitDC();
	if(NULL == m_pMemDC)
		return FALSE;

	CRect rt(0,0,m_BitmapSize.cx,m_BitmapSize.cy);
	if(m_BitmapSize.cx < m_Rect.Width() && m_BitmapSize.cy < m_Rect.Height())
	{
		rt.left = m_Rect.CenterPoint().x - m_BitmapSize.cx / 2;
		rt.top = m_Rect.CenterPoint().y - m_BitmapSize.cy / 2;
		rt.right = rt.left + stuBitmap.bmWidth;
		rt.bottom = rt.top + stuBitmap.bmHeight;
		rt.NormalizeRect();
		m_pMemDC->SetBrushOrg(rt.left, rt.top);
	}

	rt.DeflateRect(1, 1, 1, 1);
	m_pMemDC->FillRect(rt, &brush);

	brush.DeleteObject();

	Refresh();

	return TRUE;
}

BOOL CBitmapCtrl::LoadBitmap(UINT nID)
{
	//载入图片
	CBitmap bmp;
	bmp.LoadBitmap(nID);

	BITMAP stuBitmap;
	bmp.GetBitmap(&stuBitmap);
	m_BitmapSize.cx = stuBitmap.bmWidth;
	m_BitmapSize.cy = stuBitmap.bmHeight;

	CBrush brush;
	brush.CreatePatternBrush(&bmp);
	bmp.DeleteObject();

	m_bLoad = TRUE;

	//初始化内存DC
	ReleaseDC();
	InitDC();
	if(NULL == m_pMemDC)
		return FALSE;

	CRect rt(0,0,m_BitmapSize.cx,m_BitmapSize.cy);
	if(m_BitmapSize.cx < m_Rect.Width() && m_BitmapSize.cy < m_Rect.Height())
	{
		rt.left = m_Rect.CenterPoint().x - m_BitmapSize.cx / 2;
		rt.top = m_Rect.CenterPoint().y - m_BitmapSize.cy / 2;
		rt.right = rt.left + stuBitmap.bmWidth;
		rt.bottom = rt.top + stuBitmap.bmHeight;
		rt.NormalizeRect();
		m_pMemDC->SetBrushOrg(rt.left, rt.top);
	}

	m_pMemDC->FillRect(rt, &brush);

	brush.DeleteObject();

	Refresh();

	return TRUE;
}

CDC* CBitmapCtrl::GetMemDC()
{
	return m_pMemDC;
}

void CBitmapCtrl::InitDC()
{
	if(m_pMemDC != NULL)
		return;

	if(NULL == m_pScrDC)
	{
		m_pScrDC = GetDC();
		if(NULL == m_pScrDC)
			return;
		m_pScrDC->SetStretchBltMode(HALFTONE);
	}

	GetWindowRect(m_Rect);
	m_Rect.OffsetRect(-m_Rect.left, -m_Rect.top);

	CRect rt = m_Rect;

	if(m_bLoad)
	{
		if(m_Rect.Width() < m_BitmapSize.cx)
			rt.right = m_BitmapSize.cx;

		if(m_Rect.Height() < m_BitmapSize.cy)
			rt.bottom = m_BitmapSize.cy;
	}

	m_pMemDC = new CDC;
	m_pMemDC->CreateCompatibleDC(m_pScrDC);
	m_Bitmap.CreateCompatibleBitmap(m_pScrDC, rt.Width(), rt.Height());
	m_pMemDC->SelectObject(&m_Bitmap);

	m_pMemDC->FillSolidRect(rt, GetSysColor(COLOR_3DFACE));

	CBrush brush;
	brush.CreateSolidBrush(RGB(0, 0, 0));
	m_pMemDC->FrameRect(rt, &brush);
	brush.DeleteObject();
}

void CBitmapCtrl::ReleaseDC()
{
	if(m_pMemDC != NULL)
	{
		delete m_pMemDC;
		m_pMemDC = NULL;
	}

	if(m_Bitmap.GetSafeHandle() != NULL)
		m_Bitmap.DeleteObject();
}

void CBitmapCtrl::Refresh()
{
	InitDC();

	if(NULL != m_pScrDC)
	{
		if(!m_bLoad || (m_BitmapSize.cx <= m_Rect.Width() && m_BitmapSize.cy <= m_Rect.Height()))
		{
			m_pScrDC->BitBlt(0, 0, m_Rect.Width(), m_Rect.Height(), m_pMemDC, 0, 0, SRCCOPY);
		}
		else
		{
			CRect rt = m_Rect;
			//rt.DeflateRect(1, 1, 1, 1);
			//计算纵横比
			double moudlex = double(m_BitmapSize.cx) / double(rt.Width());
			double moudley = double(m_BitmapSize.cy) / double(rt.Height());
			int nShowWidth = 0, nShowHeight = 0;
			if(moudlex > moudley)
			{
				nShowWidth = rt.Width();
				nShowHeight = (int)(rt.Width() * (double(m_BitmapSize.cy) / double(m_BitmapSize.cx)));
			}
			else
			{
				nShowHeight = rt.Height();
				nShowWidth = (int)(rt.Height() * (double(m_BitmapSize.cx) / double(m_BitmapSize.cy)));
			}

			m_pScrDC->FillSolidRect(rt, GetSysColor(COLOR_3DFACE));
			m_pScrDC->StretchBlt((rt.Width() - nShowWidth) / 2, (rt.Height() - nShowHeight) / 2,
				nShowWidth, nShowHeight, m_pMemDC, 0, 0, m_BitmapSize.cx, m_BitmapSize.cy, SRCCOPY);
			CBrush brush(RGB(0, 0, 0));
			m_pScrDC->FrameRect(rt, &brush);
			brush.DeleteObject();
		}
	}
}