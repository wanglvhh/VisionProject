#include "stdafx.h"
#include "SkinClass.h"

CSkinControl::CSkinControl()
{
	m_thisHwnd = NULL;
	m_nState = SKIN_STATUS_NOR;
	m_bEnable = TRUE;
	m_pFont = NULL;
	m_pPaintDC = NULL;
	m_nfontPixelSize = 0;

	m_bHot = FALSE;
	m_bPre = FALSE;
	m_bHotSpecial = FALSE;
	m_bPreSpecial = FALSE;
	m_bFocus = FALSE;

	m_bTransparent = TRUE;
	m_bTracking = FALSE;

	for (int i=0; i<SKIN_CONTROL_STATUS_COUNT; i++)
	{
		switch (i)
		{
		case SKIN_STATUS_NOR:
			m_clrText[i] = RGB(255, 0, 255);
			m_clrBk[i] = RGB(255, 255, 255);
			m_clrFrame[i] = RGB(100, 10, 10);
			break;

		case SKIN_STATUS_HOT:
			m_clrText[i] = RGB(0, 255, 0);
			m_clrBk[i] = RGB(128, 111, 255);
			m_clrFrame[i] = RGB(10, 180, 210);
			break;

		case SKIN_STATUS_PRE:
			m_clrText[i] = RGB(180, 0, 200);
			m_clrBk[i] = RGB(255, 0, 255);
			m_clrFrame[i] = RGB(0, 200, 0);
			break;

		case SKIN_STATUS_DIS:
			m_clrText[i] = RGB(180, 80, 111);
			m_clrBk[i] = RGB(200, 200, 200);
			m_clrFrame[i] = RGB(250, 0, 0);
			break;

		case SKIN_STATUS_ALL:
			m_clrText[i] = RGB(180, 80, 0);
			m_clrBk[i] = RGB(200, 200, 200);
			m_clrFrame[i] = RGB(60, 150, 130);
			break;

		default:
			break;
		}

		m_hBkBrush[i].DeleteObject();
		m_hBkBrush[i].CreateSolidBrush(m_clrBk[i]);

		m_hFrameBrush[i].DeleteObject();
		m_hFrameBrush[i].CreateSolidBrush(m_clrFrame[i]);

		m_bDrawTextToBottom = FALSE;

		m_imgBk[i] = NULL;
	}

	m_nImgHeight = 0;
	m_nImgHeight = 0;
	m_bAutoImgSize = FALSE;
	m_nAlignment =  BS_CENTER;
	m_pWnd = NULL;
}

CSkinControl::~CSkinControl()
{
	if (NULL != m_pFont)
	{
		delete  m_pFont;
		m_pFont = NULL;
	}

	for (int i=0; i<SKIN_CONTROL_STATUS_COUNT; i++)
	{
		m_hBkBrush[i].DeleteObject();
		m_hFrameBrush[i].DeleteObject();

		if (NULL != m_imgBk[i])
		{
			delete m_imgBk[i];
			m_imgBk[i] = NULL;
		}
	}
}

void CSkinControl::SnEnableWindow(BOOL nEnable)
{
	m_bEnable = nEnable;
	m_bEnable ? m_nState = SKIN_STATUS_NOR : m_nState = SKIN_STATUS_DIS;
}

BOOL CSkinControl::SnIsWindowEnable()
{
	return m_bEnable;
}

void CSkinControl::SnEnableHot(BOOL bEnable)
{
	 m_bHotSpecial = bEnable;
}

void CSkinControl::SnEnablePre(BOOL bEnable)
{
	m_bPreSpecial = bEnable;
}

void CSkinControl::SnEnableTransparent(BOOL bEnable)
{
	m_bTransparent = bEnable;
}

void CSkinControl::SnGetRect()
{
	::GetWindowRect(m_thisHwnd, &m_nRect);
}

void CSkinControl::SnSetTextColor(COLORREF clrText, int nStatus)
{
	if (nStatus >= SKIN_CONTROL_STATUS_COUNT)
	{
		return;
	}

	m_clrText[nStatus] = clrText;
}

void CSkinControl::SnSetTextFont(int fontPixelSize, LPCTSTR fontName)
{
	if (NULL != m_pFont)
	{
		delete  m_pFont;
		m_pFont = NULL;
	}

	m_nfontPixelSize = fontPixelSize;

	m_pFont = new CFont;
	fontPixelSize = int(fontPixelSize * SN_PIXEL_TO_POUND + 0.5);
	m_pFont->CreatePointFont(fontPixelSize, fontName);
}

void CSkinControl::SnDrawText(LPCTSTR strText, CRect nRect)
{
	m_pPaintDC->GetTextExtent(strText);
	m_pPaintDC->SetTextColor(m_clrText[m_nState]);
	m_pPaintDC->SelectObject(m_pFont);
	m_pPaintDC->DrawText(strText, nRect, DT_SINGLELINE|DT_VCENTER|DT_CENTER);
}

void CSkinControl::SnSetBkColor(COLORREF clrBk, int nStatus)
{
	if (nStatus >= SKIN_CONTROL_STATUS_COUNT)
	{
		return;
	}

	m_clrBk[nStatus] = clrBk;
	m_hBkBrush[nStatus].DeleteObject();
	m_hBkBrush[nStatus].CreateSolidBrush(m_clrBk[nStatus]);
}

void CSkinControl::SnSetFrameColor(COLORREF clrFrame, int nStatus)
{
	if (nStatus >= SKIN_CONTROL_STATUS_COUNT)
	{
		return;
	}

	m_clrFrame[nStatus] = clrFrame;
	m_hFrameBrush[nStatus].DeleteObject();
	m_hFrameBrush[nStatus].CreateSolidBrush(m_clrFrame[nStatus]);
}

BOOL CSkinControl::SnLoadImage(LPCTSTR strPath, int nStatus)
{
	if (NULL != m_imgBk[nStatus])
	{
		delete m_imgBk[nStatus];
		m_imgBk[nStatus] = NULL;
	}

	m_imgBk[nStatus] = new CImage;
	m_imgBk[nStatus]->Load(strPath);

	return m_imgBk[nStatus]->IsNull() ? FALSE : TRUE;
}

void CSkinControl::SnTraBkgnd(CImage *pImg)
{
	if(pImg->IsNull())
	{
		return;
	}

	for(int i = 0; i < pImg->GetWidth(); i++)
	{
		for(int j = 0; j < pImg->GetHeight(); j++)
		{
			unsigned char* pucColor = reinterpret_cast<unsigned char *>(pImg->GetPixelAddress(i , j));
			pucColor[0] = pucColor[0] * pucColor[3] / 255;
			pucColor[1] = pucColor[1] * pucColor[3] / 255;
			pucColor[2] = pucColor[2] * pucColor[3] / 255;
		}
	}
}

BOOL CSkinControl::SnIsPNG(LPCTSTR strPath)
{
	CString str = strPath;
	int pos= str.ReverseFind(_T('.'));

	if (-1 == pos)
	{
		return FALSE;
	}

	str = str.Mid(pos + 1, 3);

	if (str == _T("png") || str == _T("PNG"))
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CSkinControl::SnShowImage(LPCTSTR strPath, BOOL bAutoImgSize)
{
	int xPos = 0;
	int nWidth = 0;
	int nHeight = 0;
	SnGetRect();

	BOOL bPng = SnIsPNG(strPath);

	if (!SnLoadImage(strPath, SKIN_STATUS_ALL))
	{
		return FALSE;
	}

	nWidth = m_imgBk[SKIN_STATUS_ALL]->GetWidth() / (SKIN_CONTROL_STATUS_COUNT - 1) ;
	nHeight = m_imgBk[SKIN_STATUS_ALL]->GetHeight();

	m_bAutoImgSize = bAutoImgSize;

	if (m_bAutoImgSize)
	{
		m_nImgWidth = nWidth;
		m_nImgHeight = nHeight;
		::MoveWindow(m_thisHwnd,m_nRect.left, m_nRect.top, m_nImgWidth, m_nImgHeight, TRUE);
	}

	if(bPng)
	{
		SnTraBkgnd(m_imgBk[SKIN_STATUS_ALL]);
	}

	for (int i=0; i<4 && xPos<=(m_imgBk[SKIN_STATUS_ALL]->GetWidth() - nWidth); i++, xPos += nWidth)
	{
		CImage *pMap = new CImage();

		if (m_imgBk[i] != NULL)
		{
			delete m_imgBk[i];
			m_imgBk[i] = NULL;
		}
		m_imgBk[i] = pMap;

		BOOL bState = FALSE;

		if (bPng && 32 == m_imgBk[SKIN_STATUS_ALL]->GetBPP())
		{
			bState = pMap->CreateEx(nWidth, nHeight, m_imgBk[SKIN_STATUS_ALL]->GetBPP(), BI_RGB, NULL, CImage::createAlphaChannel);
		}
		else
		{
			bState = pMap->CreateEx(nWidth, nHeight, m_imgBk[SKIN_STATUS_ALL]->GetBPP(), BI_RGB, NULL);
		}
		ASSERT(bState);

		CImageDC imageDC(*pMap);
		m_imgBk[SKIN_STATUS_ALL]->Draw(imageDC, 0, 0, nWidth, nHeight, xPos, 0, nWidth, nHeight);
	}

	return TRUE;
}

BOOL CSkinControl::SnShowImage(LPCTSTR strPath, int nStatus, BOOL bAutoImgSize)
{
	int xPos = 0;
	int nWidth = 0;
	int nHeight = 0;
	SnGetRect();

	BOOL bPng = SnIsPNG(strPath);

	if (!SnLoadImage(strPath, nStatus))
	{
		return FALSE;
	}

	nWidth = m_imgBk[nStatus]->GetWidth();
	nHeight = m_imgBk[nStatus]->GetHeight();

	m_bAutoImgSize = bAutoImgSize;

	if (m_bAutoImgSize)
	{
		m_nImgWidth = nWidth;
		m_nImgHeight = nHeight;
	}

	if(bPng)
	{
		SnTraBkgnd(m_imgBk[nStatus]);
	}

	return TRUE;
}

BOOL CSkinControl::SnShowImage(LPCTSTR strPath, int nImgPartitionCount, int nPartNum, int nStatus, BOOL bAutoImgSize)
{
	int xPos = 0;
	int nWidth = 0;
	int nHeight = 0;
	BOOL bPng = SnIsPNG(strPath);
	nPartNum -= 1;
	SnGetRect();

	if (!SnLoadImage(strPath, SKIN_STATUS_ALL))
	{
		return FALSE;
	}

	nWidth = m_imgBk[SKIN_STATUS_ALL]->GetWidth() / nImgPartitionCount;
	nHeight = m_imgBk[SKIN_STATUS_ALL]->GetHeight();

	m_bAutoImgSize = bAutoImgSize;
	if (m_bAutoImgSize)
	{
		m_nImgWidth = nWidth;
		m_nImgHeight = nHeight;
	}

	if(bPng)
	{
		SnTraBkgnd(m_imgBk[SKIN_STATUS_ALL]);
	}

	for (int i=0; i<nImgPartitionCount && xPos<=(m_imgBk[SKIN_STATUS_ALL]->GetWidth() - nWidth); i++, xPos += nWidth)
	{
		if (nPartNum == i)
		{
			CImage *pMap = new CImage();

			if (m_imgBk[nStatus] != NULL)
			{
				delete m_imgBk[nStatus];
				m_imgBk[nStatus] = NULL;
			}

			m_imgBk[nStatus] = pMap;
			BOOL bState = FALSE;

			if (bPng && 32 == m_imgBk[SKIN_STATUS_ALL]->GetBPP())
			{
				bState = pMap->CreateEx(nWidth, nHeight, m_imgBk[SKIN_STATUS_ALL]->GetBPP(), BI_RGB, NULL, CImage::createAlphaChannel);
			}
			else
			{
				bState = pMap->CreateEx(nWidth, nHeight, m_imgBk[SKIN_STATUS_ALL]->GetBPP(), BI_RGB, NULL);
			}
			ASSERT(bState);

			CImageDC imageDC(*pMap);
			m_imgBk[SKIN_STATUS_ALL]->Draw(imageDC, 0, 0, nWidth, nHeight, xPos, 0, nWidth, nHeight);
		}
	}

	return TRUE;
}

void CSkinControl::SnSetTextAlign(int nAlign)
{
	switch(nAlign)
	{
	case BS_LEFT:
	case BS_CENTER:
	case BS_RIGHT:
		{
			m_nAlignment = nAlign;
			break;
		}

	default:
		m_nAlignment = BS_LEFT;
		break;
	}
}