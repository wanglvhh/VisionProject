#include "stdafx.h"
#include "SkinClass.h"
//#include "resource.h"

IMPLEMENT_DYNAMIC(CSkinComboBox, CComboBox)

CSkinComboBox::CSkinComboBox()
{
	m_pEdit = NULL;
	m_clrFrame[SKIN_STATUS_NOR] = RGB(70, 140, 255);
	m_clrFrame[SKIN_STATUS_HOT] = RGB(170, 140, 255);
	m_clrFrame[SKIN_STATUS_PRE] = RGB(70, 140, 15);
	m_clrBk[SKIN_STATUS_HOT] = RGB(22, 222, 22);
	m_clrBk[SKIN_STATUS_NOR] = RGB(222, 22, 22);
}

CSkinComboBox::~CSkinComboBox()
{
}

BEGIN_MESSAGE_MAP(CSkinComboBox, CComboBox)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_CONTROL_REFLECT(CBN_SETFOCUS, OnSetFocus)
	ON_CONTROL_REFLECT(CBN_KILLFOCUS, OnKillFocus)
	ON_CONTROL_REFLECT(CBN_SELCHANGE, &CSkinComboBox::OnCbnSelchange)
END_MESSAGE_MAP()

void CSkinComboBox::SnCreate(int nID, CWnd* pParent)
{
	SubclassDlgItem(nID, pParent);
	m_thisHwnd = m_hWnd;
	SnGetRect();
}

void CSkinComboBox::SnSetTextFont(int fontPixelSize, LPCTSTR fontName)
{
	CSkinControl::SnSetTextFont(fontPixelSize, fontName);
	SetItemHeight(-1, fontPixelSize);
	SetItemHeight(1, fontPixelSize + 6);
	SetFont(m_pFont);
}

LRESULT CSkinComboBox::WindowProc( UINT message, WPARAM wParam, LPARAM lParam )
{
	switch (message)
	{
	case WM_CTLCOLORBTN:
		{
			HWND hWndBtn = (HWND)lParam;
			CButton* pButton = (CButton*)FromHandle(hWndBtn);
			CRect rcBtnClient;
			pButton->GetClientRect(&rcBtnClient);
		}
		break;

	case WM_CTLCOLORSCROLLBAR:
		{
			HWND hWndBtn = (HWND)lParam;
			CScrollBar* pButton = (CScrollBar*)FromHandle(hWndBtn);
			CRect rcBtnClient;
			pButton->GetClientRect(&rcBtnClient);
		}
		break;

	case WM_CTLCOLOREDIT:
		{
			HWND hWndEdit = (HWND)lParam;
			m_pEdit = (CEdit*)FromHandle(hWndEdit);
			//m_pEdit->SetReadOnly(TRUE);
		}
		break;

	case WM_CTLCOLORSTATIC:
		{
			HWND hWndStatic = (HWND)lParam;
			CStatic* pStatic = (CStatic*)FromHandle(hWndStatic);
			CRect rcStaticClient;
			pStatic->GetClientRect(&rcStaticClient);
		}
		break;

	case WM_CTLCOLORLISTBOX:
		{
			HWND hWndListBox = (HWND)lParam;
			m_pListBox = (CListBox*)FromHandle(hWndListBox);

			if (NULL == m_pListBox)
			{
				break;
			}

			CRect rcListBoxClient;
			m_pListBox->GetClientRect(&rcListBoxClient);
			int nItemCount = m_pListBox->GetCount();

			if (CB_ERR == nItemCount)
			{
				break;
			}

			CPoint point;
			GetCursorPos(&point);
			m_pListBox->ScreenToClient(&point);
			CRect rcItem;

			for(int i=0; i<nItemCount; i++)
			{
				m_pListBox->GetItemRect(i, &rcItem);
				if(rcItem.PtInRect(point))
				{
					m_nPreFocusListItem = m_nCurrFocusListItem;
					m_nCurrFocusListItem = i;
					if(m_nCurrFocusListItem != m_nPreFocusListItem)
					{
						CRect rcFocus(rcItem);
						CRect rcPreItem;
						m_pListBox->GetItemRect(m_nPreFocusListItem, &rcPreItem);
						m_pListBox->InvalidateRect(&rcPreItem);

						if(rcFocus.PtInRect(point))
						{
							m_bListItemFocus = TRUE;
							m_nPreFocusListItem = m_nCurrFocusListItem;
							m_pListBox->InvalidateRect(&rcItem);
						}
						else
						{
							m_bListItemFocus = FALSE;
							m_nCurrFocusListItem = m_nPreFocusListItem;
							m_pListBox->InvalidateRect(&rcItem);
						}
					}
				}
			}
		}
		break;

	default:
		break;
	}

	return CComboBox::WindowProc(message, wParam, lParam);
}

BOOL CSkinComboBox::PreTranslateMessage(MSG* pMsg)
{
	return CComboBox::PreTranslateMessage(pMsg);
}

void CSkinComboBox::PreSubclassWindow()
{
	CComboBox::PreSubclassWindow();
}

HBRUSH CSkinComboBox::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CComboBox::OnCtlColor(pDC, pWnd, nCtlColor);

	if(nCtlColor==CTLCOLOR_EDIT)
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(m_clrText[SKIN_STATUS_NOR]);
		return (HBRUSH)m_hBkBrush[m_nState];
	}
	return hbr;
}

void CSkinComboBox::OnPaint()
{
	CPaintDC dc(this);

	SnOnNoFlickerPaint(&dc);
	COMBOBOXINFO combInfo;
	combInfo.cbSize = sizeof(COMBOBOXINFO);
	GetComboBoxInfo(&combInfo);

	CRect rcRect = combInfo.rcButton;
	int nLeft[SKIN_CONTROL_STATUS_COUNT - 2];
	int nTop[SKIN_CONTROL_STATUS_COUNT - 2];
	int nWidth[SKIN_CONTROL_STATUS_COUNT - 2];
	int nHeight[SKIN_CONTROL_STATUS_COUNT - 2];

	for (int i=SKIN_STATUS_NOR; i<SKIN_CONTROL_STATUS_COUNT - 2; i++)
	{
		if (NULL == m_imgBk[i])
		{
			continue;
		}

		if (rcRect.Width() < m_imgBk[i]->GetWidth())
		{
			nLeft[i] = rcRect.left;
			nWidth[i] = rcRect.Width() - 1;
		}
		else
		{
			nLeft[i] = rcRect.left + (rcRect.Width() - m_imgBk[i]->GetWidth()) / 2;
			nWidth[i] = m_imgBk[i]->GetWidth();
		}

		if (rcRect.Height() < m_imgBk[i]->GetHeight())
		{
			nTop[i] = rcRect.top;
			nHeight[i] = rcRect.Height();
		}
		else
		{
			nTop[i] = rcRect.top + (rcRect.Height() - m_imgBk[i]->GetHeight()) / 2;
			nHeight[i] = m_imgBk[i]->GetHeight();
		}
	}

		if (SnPointInBtn() && NULL != m_imgBk[SKIN_STATUS_HOT])
		{
			m_imgBk[SKIN_STATUS_HOT]->Draw(dc, nLeft[SKIN_STATUS_HOT], nTop[SKIN_STATUS_HOT], nWidth[SKIN_STATUS_HOT], nHeight[SKIN_STATUS_HOT]);
		}

		if (!SnPointInBtn() && NULL != m_imgBk[SKIN_STATUS_NOR])
		{
			m_imgBk[SKIN_STATUS_NOR]->Draw(dc, nLeft[SKIN_STATUS_NOR], nTop[SKIN_STATUS_NOR], nWidth[SKIN_STATUS_NOR], nHeight[SKIN_STATUS_NOR]);
		}
}

void CSkinComboBox::SnOnNoFlickerPaint(CDC* pDC)
{
	CRect rcClient;
	GetClientRect(&rcClient);
	CDC dcMem; // 内存设备上下文（DC）
	dcMem.CreateCompatibleDC(pDC); // 创建兼容设备DC
	dcMem.SetMapMode(pDC->GetMapMode()); // 设置映射模式
	CBitmap bitmap; // 创建兼容位图，使其能容下整个窗口图像
	bitmap.CreateCompatibleBitmap(pDC, rcClient.Width(), rcClient.Height());
	CBitmap* pOldBitmap = dcMem.SelectObject(&bitmap); // 用内存DC选择位图
	dcMem.FillSolidRect(rcClient, RGB(255, 255, 255));

	if (m_bFocus)
	{
		dcMem.Draw3dRect(rcClient, m_clrFrame[SKIN_STATUS_PRE],m_clrFrame[SKIN_STATUS_PRE]);
	}
	else
	{
		if(SnPointInRect())
		{
			dcMem.Draw3dRect(rcClient, m_clrFrame[SKIN_STATUS_HOT],m_clrFrame[SKIN_STATUS_HOT]);
		}
		else
		{
			dcMem.Draw3dRect(rcClient, m_clrFrame[SKIN_STATUS_NOR],m_clrFrame[SKIN_STATUS_NOR]);
		}
	}

	pDC->BitBlt(rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height(),&dcMem, rcClient.left, rcClient.top, SRCCOPY);
	dcMem.SelectObject(pOldBitmap);
	bitmap.DeleteObject();
	dcMem.DeleteDC();
}

BOOL CSkinComboBox::SnPointInRect()
{
	CPoint pt;
	GetCursorPos(&pt);
	CRect rcItem;
	GetWindowRect(&rcItem);
	return rcItem.PtInRect(pt);
}

BOOL CSkinComboBox::SnPointInBtn()
{
	CPoint point;
	GetCursorPos(&point);
	ScreenToClient(&point);
	CRect rcClient;
	GetClientRect(&rcClient);
	rcClient.left = rcClient.right - 18;
	return rcClient.PtInRect(point);
}

void CSkinComboBox::OnKillFocus()
{
	m_bFocus = FALSE;
}

void CSkinComboBox::OnSetFocus()
{
	m_bFocus = TRUE;
}

void CSkinComboBox::DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	if(lpDrawItemStruct->CtlType!=ODT_COMBOBOX)
		return ;

	int nItemID = lpDrawItemStruct->itemID;
	CRect rcItem = lpDrawItemStruct->rcItem;
	UINT uItemState = lpDrawItemStruct->itemState;
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

	SnDrawListBox(pDC, nItemID, uItemState, rcItem);
}

void CSkinComboBox::SnDrawListItem(CDC* pDC, CString csText, CRect rcItem, COLORREF clrText, COLORREF clrBg, COLORREF clrFrame )
{
	CPen penFrame;
	penFrame.CreatePen(PS_SOLID, 1, clrFrame);
	CPen* pOldPen = pDC->SelectObject(&penFrame);
	CBrush brushBg;
	brushBg.CreateSolidBrush(clrBg);
	CBrush* pOldBrush = pDC->SelectObject(&brushBg);
	rcItem.InflateRect(0, 1, 0, 1);
	pDC->RoundRect(&rcItem, CPoint(0, 0));
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
	penFrame.DeleteObject();
	brushBg.DeleteObject();

	rcItem.InflateRect(0, -1, 0, -1);
	pDC->SetTextColor(clrText);
	rcItem.left += 3;
	pDC->DrawText(csText, &rcItem, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
}

void CSkinComboBox::SnDrawListBox(CDC* pDC, int nItemID, UINT uState, CRect rcItem)
{
	CString csShowText;
	GetLBText(nItemID, csShowText);

	pDC->SetBkMode(TRANSPARENT);

	if(uState&ODS_SELECTED)
		Invalidate();

	if(nItemID == m_nCurrFocusListItem)
	{
		SnDrawListItem(pDC, csShowText, rcItem, m_clrText[SKIN_STATUS_HOT], m_clrBk[SKIN_STATUS_HOT], m_clrFrame[SKIN_STATUS_HOT]);
		SetWindowText(csShowText);
	}
	else
	{
		SnDrawListItem(pDC, csShowText, rcItem, m_clrText[SKIN_STATUS_NOR], m_clrBk[SKIN_STATUS_NOR], m_clrFrame[SKIN_STATUS_NOR]);
	}

	// 列表框边框
	CBrush brushListFrame;

    brushListFrame.CreateSolidBrush(m_clrFrame[SKIN_STATUS_NOR]);

	CRect rcListClient;
	m_pListBox->GetClientRect(&rcListClient);

	pDC->FrameRect(rcListClient, &brushListFrame);
}

void CSkinComboBox::OnCbnSelchange()
{
	Invalidate();
}