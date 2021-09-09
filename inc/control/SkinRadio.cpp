// DibRadioButton.cpp : implementation file
//
//////////////////////////////////////////////////////////////////////////
// Դ�ļ�
// ���ߣ����¸�
// �������ڣ�2007-12-24
// ����޸����ڣ�2008-1-2
// ���ܣ������Զ���λͼ��RadioButton�ؼ�
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
	// ͼ�������ֵļ��
	m_nSpaceBetween = 4;
	// 1������ͼ�꣨0��ʼ��
	m_radioState = RADIOSTATE_UNSELECT;
	m_tRadioState = RADIOSTATE_UNSELECT;
//	m_bSelected = FALSE;
	m_nSets = BITMAP_SETS;
	m_nSetsID = 0;
	m_nBitmapNumPerSet = BITMAP_PER_SET;
	// ��һ��
	m_nSetsID = 0;
	m_bTracking = FALSE;
	m_bMouseOver = FALSE;
	m_bFocused = FALSE;
	m_nButtonStyle = 0;
	m_bChecked = FALSE;
	m_bDisabled = FALSE;

	// �ؼ�����ɫ
	m_BackColor = RGB(250, 250, 240);// ::GetSysColor(COLOR_WINDOWFRAME);
	// ��ǰ���ֱ���ɫ
	m_TextBackColor = m_BackColor;
	// �������ֱ���ɫ
	m_FocusTxtBackColor = ::GetSysColor(COLOR_HIGHLIGHT);
	// ����������ɫΪ��ɫ
	m_txtFocusColor = RGB(255,55,210);
	// ����ԭ����ɫΪ��ɫ
	m_OriginalTxtColor = RGB(0, 0, 255);
	//��ǰ������ɫ
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
	// ���CDC
	CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	int saveDc = pDC->SaveDC();//���浱ǰDC�豸
	UINT style = GetStyle();//��ȡ���ڷ��
	DrawButton(pDC, lpDrawItemStruct->itemState);//���ư�ť
	pDC->RestoreDC(saveDc);	//�ͷ��豸
}
//*
void CDibRadioButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	// ͨ������flag��������껬��������뿪��Ϣ
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
	// ������ڵ�ǰ�ؼ��ϣ����Ұ������±��ΪTrueʱ
	if(hWndMouseOver == m_hWnd && m_bPressed)
	{
		if (m_nButtonStyle == BS_RADIOBUTTON)
		{
			SetCheck(1);
			m_radioState = RADIOSTATE_SELMOUSEHOVER;
			// ������Ҫ������ʱ״̬����Ϊ���ǵ�����뿪�ؼ�ʱ�ܼ�ʱ���¸ı��״̬
			// ȷ������뿪�󣬻ָ�Select״̬��������ѡ���һ����꽹��
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
	// �趨һ������ȥ��ͼ��
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
	// �õ��ؼ�����
 	GetWindowText(m_strTxt);
// 	// ����λͼ��ʽ
 	SetSetsID(1);
//
	m_bChecked = GetCheck();		// ��֮ǰ�����Ѿ�SetCheck
// 	// �õ�Button��ʽ
 	m_nButtonStyle = GetButtonStyle();
 	// ����BS_AUTORADIOBUTTON��BS_RADIOBUTTON��ΪBS_RADIOBUTTON��ʽ
 	if(m_nButtonStyle == BS_AUTORADIOBUTTON || m_nButtonStyle == (BS_AUTORADIOBUTTON | BS_RADIOBUTTON))
 	{
 		m_nButtonStyle = BS_RADIOBUTTON;
 	}
	//SetRadioBitmap(IDB_BITMAP1);
	CButton::PreSubclassWindow();
	// �Ի�
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
	// ����λͼ
	BOOL bRet = cBmp.LoadBitmap(m_uiBitmap);

	BITMAP bitmapInfo;
	if (bRet)
	{
		cBmp.GetBitmap(&bitmapInfo);
	}

	// �ڴ滷��
	CDC dcMemory;
	dcMemory.CreateCompatibleDC(pDC);
	CBitmap *oldBitmap = dcMemory.SelectObject(&cBmp);
	CRect rect;
	GetWindowRect(&rect);//�õ���ť��С
	// �õ���ʾ���ֵĴ�С
	CSize titleSize = pDC->GetTextExtent(m_strTxt);
	// ��ʾ���м�λ��
	int YPos = (rect.Height() - BITMAP_HEIGHT) / 2;
	// ����߿�߶�С��ͼ��߶ȣ�����ˮƽ������
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
	// ���ƿؼ�����ɫ
//	m_BackColor = RGB(255, 255, 255);
	pDC->FillSolidRect(rcClient, m_BackColor);
	pDC->SetBkMode(TRANSPARENT);

	CFont font;
	font.CreatePointFont(110, _T("΢���ź�"));
	pDC->SelectObject(font);

	// �����������ֱ���ɫ
	//if (m_bFocused)
	//{
	//	rcClient.right =  rcClient.left + BITMAP_WIDTH + m_nSpaceBetween + titleSize.cx;
	//	rcClient.left =  rcClient.left + BITMAP_WIDTH + m_nSpaceBetween;
	//	pDC->FillSolidRect(rcClient, m_TextBackColor);
	//}
	// ����λͼ
	pDC->BitBlt(XPos, YPos, BITMAP_WIDTH, BITMAP_HEIGHT, &dcMemory, \
		// �����Ӧλͼ��(��ID��ÿ��λͼ��+״̬����) �� ����ͼ����
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
	// ��ѡ���ͼ������IDС��0���ߴ��������������ޣ������޸�
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
	// ��������״̬��ʽ
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
	// ��ԭ��ʽ
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
	// ��������˫����Ϣ
	if (message == WM_LBUTTONDBLCLK)
	{
		message = WM_LBUTTONDOWN;
	}
	return CButton::DefWindowProc(message, wParam, lParam);
}

LRESULT CDibRadioButton::OnUnCheck( WPARAM wParam, LPARAM lParam )
{
	// ���ﲻҪȥ��SetCheck�������ᴥ��OnSetCheck���ٴ�����������������ѭ��
	if(m_bChecked)
	{
		m_bChecked = FALSE;
		m_radioState = RADIOSTATE_UNSELECT;
		m_tRadioState = m_radioState;
		InvalidateRect(NULL);//ʹ����������Ч ͬInvalidate
	}
	return 0;
}

LRESULT CDibRadioButton::OnSetCheck( WPARAM wParam, LPARAM lParam )
{
	// �����Ŀ���ǰ�ͬ��������radiobutton����ΪunCheck
	// ���ȵõ�check��־
	m_bChecked = (wParam != 0);
	if(m_bChecked)
	{
		CPtrList list;
		list.AddTail((void*)m_hWnd);
		// �õ������ھ��
		HWND hWndParent = GetParent()->GetSafeHwnd();
		// �õ��ؼ����ھ��
		HWND hWnd = GetSafeHwnd();
		while(hWnd)
		{
			// �õ�ͬ���ڵĿռ�Ĵ��ھ��
			hWnd = ::GetNextDlgGroupItem(hWndParent, hWnd, 0);
			CWnd* pWnd = CWnd::FromHandle(hWnd);
			if(pWnd)
			{
				// �õ��ؼ���ԴID
				int nID = pWnd->GetDlgCtrlID();
			}
			// ��list�в����������Ƿ񱻲�ѯ�����������ֻ�е�һ��Group�Ŀؼ���
			POSITION pos = list.Find((void*)hWnd);

			if(pos)
			{
				// ����ҵ������������Ǿʹ���������ͷ��
				hWnd = NULL;
			}
			if(hWnd)
			{
				// û��������һ�飬��ô�Ͱѵ�ǰ�ľ����ӵ�list��ȥ��Ŀ����Ϊ�˲���ͬһ�ؼ�������������Ϣ��
				list.AddTail((void*)hWnd);
				// ������ؼ�����unChecked����Ϣ
				::PostMessage(hWnd, WM_UNCHECKED, 0, 0);
			}
		}
		m_radioState = RADIOSTATE_SELECT;
		m_tRadioState = m_radioState;
	}
	else
	{
		// ���õ�ǰΪchecked
		m_radioState = RADIOSTATE_UNSELECT;
		m_tRadioState = m_radioState;
	}
	InvalidateRect(NULL);
	return 0;
}

LRESULT CDibRadioButton::OnGetCheck( WPARAM wParam, LPARAM lParam )
{
	// ֱ�ӷ���Check��־
	return m_bChecked;
}

LRESULT CDibRadioButton::OnSetStyle( WPARAM wParam, LPARAM lParam )
{
	// �ı���ʽ��ʱ��������Ի���ʽ
	wParam |= BS_OWNERDRAW;

	return DefWindowProc(BM_SETSTYLE, wParam, lParam);
}

void CDibRadioButton::OnSetFocus(CWnd* pOldWnd)
{
	m_bFocused = TRUE;
	// �������ֱ���
	m_TextBackColor = m_FocusTxtBackColor;
	// ����������ɫ
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

	// �������ֱ���
	m_TextBackColor = m_FocusTxtBackColor;
	// ����������ɫ
	m_txtColor = m_OriginalTxtColor;
	// �������ֱ�����ɫ
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
	// ����Ҫ�õ�ԭ���ֵ���ɫ�����Ǹ�����
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