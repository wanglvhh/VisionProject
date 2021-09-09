// StaticEx.cpp : implementation file
//

#include "stdafx.h"
#include "LabelEx.h"

#include <iostream>
#include <iomanip>
#include <sstream>
// CLabelEx
IMPLEMENT_DYNAMIC(CLabelEx, CWnd)

CLabelEx::CLabelEx()
{
	m_clrBkg	= Color(255,255,  0,  0);
	m_clrText	= Color(255,255,255,255);
	m_clrBorder = Color(255,255,  0,  0);

	m_bEnable	= true;

	m_fSizeBorder	= 4;
	m_fSizeText		= 20;
	m_nOffsetTextX	= 0;
	m_nOffsetTextY	= 0;
	m_nTextAlign1	= 1;
	m_nTextAlign2	= 1;
	m_pBmpImage		= NULL;
	m_strText		= _T("");
	m_strFont		= _T("Arial");

	m_rcImage = Rect(0,0,0,0);
}

CLabelEx::~CLabelEx()
{
	if (m_pBmpImage != NULL)
	{
		delete m_pBmpImage;
		m_pBmpImage = NULL;
	}
}

void CLabelEx::PreSubclassWindow()
{
	CRect rect;
	GetClientRect(&rect);

	m_rcImage = Rect(rect.left, rect.top, rect.Width(), rect.Height());

	CWnd::PreSubclassWindow();
}

BOOL CLabelEx::CreateContol(CWnd* pWnd, CRect rcSize, UINT ID)
{
	if (pWnd == NULL) return false;

	return CWnd::Create(NULL,NULL,WS_CHILD|WS_VISIBLE, rcSize, pWnd, ID );
}

BEGIN_MESSAGE_MAP(CLabelEx, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CLabelEx message handlers
void CLabelEx::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	CRect rect;
	GetClientRect(&rect);

	Graphics mainG (dc.GetSafeHdc());

	// 메모리 생성
	Bitmap memBmp(rect.Width(), rect.Height());
	
	Graphics memG(&memBmp);

	// 잔상을 없애기 위해 white 채움.
	SolidBrush brs(Color(255,0,0,0));
	memG.FillRectangle(&brs,0,0,rect.Width(),rect.Height());

	//----- 메모리상에 그리는 부분 -----//
	DrawBkg(&memG);
	DrawBorder(&memG);
	DrawImage(&memG);
	DrawText(&memG);
	//---------------------------------//

	if (m_bEnable == true)
	{
		// 그려진 메모리를 최종 출력
		mainG.DrawImage(&memBmp,0,0);
	}
	else
	{
		ColorMatrix GrayMat = {	
			0.30f, 0.30f, 0.30f, 0.00f, 0.00f,
			0.59f, 0.59f, 0.59f, 0.00f, 0.00f,
			0.11f, 0.11f, 0.11f, 0.00f, 0.00f,
			0.00f, 0.00f, 0.00f, 1.00f, 0.00f,
			0.00f, 0.00f, 0.00f, 0.00f, 1.00f	};

			ImageAttributes ia;
			ia.SetColorMatrix(&GrayMat);

			RectF grect; grect.X=0, grect.Y=0; grect.Width = (float)rect.Width(); grect.Height = (float)rect.Height();
			mainG.DrawImage(&memBmp, grect, 0, 0, (float)rect.Width(), (float)rect.Height(), UnitPixel, &ia);
	}
}


BOOL CLabelEx::OnEraseBkgnd(CDC* pDC)
{
	//Avoid Flicker.
	//return CWnd::OnEraseBkgnd(pDC);
	return TRUE;
}

void CLabelEx::DrawBorder(Graphics *pG)
{
	CRect rect;
	GetClientRect(&rect);
	
	Pen pen(m_clrBorder,m_fSizeBorder);
	
	pG->DrawRectangle(&pen,rect.left,rect.top,rect.Width(),rect.Height());
}

void CLabelEx::DrawBkg(Graphics *pG)
{
	CRect rect;
	GetClientRect(&rect);

	SolidBrush brs(m_clrBkg);

	pG->FillRectangle(&brs,rect.left,rect.top,rect.right,rect.bottom);
}

void CLabelEx::DrawImage(Graphics *pG)
{
	CRect rect;
	GetClientRect(&rect);
	
	if (m_pBmpImage == NULL) return;

	pG->DrawImage(m_pBmpImage, m_rcImage, 0,0, m_pBmpImage->GetWidth(), m_pBmpImage->GetHeight(), UnitPixel);
}

void CLabelEx::DrawText(Graphics *pG)
{
	CRect rect;
	GetClientRect(&rect);
	
	FontFamily fontptroll(m_strFont);
	Gdiplus::Font font(&fontptroll, m_fSizeText, FontStyleRegular, UnitPixel);
	
	StringFormat formatAlign;
	formatAlign.SetAlignment((Gdiplus::StringAlignment)m_nTextAlign1);		// Left / Center / Right
	formatAlign.SetLineAlignment((Gdiplus::StringAlignment)m_nTextAlign2);	// Top / Middle / Bottom

	SolidBrush brs(m_clrText);
	RectF rc((float)rect.left+m_nOffsetTextX, (float)rect.top+m_nOffsetTextY, (float)rect.Width(),(float)rect.Height());
	
	pG->DrawString(m_strText,m_strText.GetLength(),&font,rc,&formatAlign,&brs);
}

bool CLabelEx::LoadImgFromPath(CString strPath)
{
	if (IsFileExist(strPath) == false) return false;

	if (m_pBmpImage != NULL)
	{
		delete m_pBmpImage;
		m_pBmpImage = NULL;
	}

	m_pBmpImage = (Bitmap*)Image::FromFile(strPath);

	if (m_pBmpImage->GetLastStatus() != Gdiplus::Ok)
		return false;

	Invalidate();

	return true;
}

bool CLabelEx::LoadImgFromResource(UINT ID, bool bPNG)
{
	if (m_pBmpImage != NULL)
	{
		delete m_pBmpImage;
		m_pBmpImage = NULL;
	}

	if (bPNG == false)
	{
		m_pBmpImage = Bitmap::FromResource(AfxGetInstanceHandle(),(WCHAR*)MAKEINTRESOURCE(ID));
	}
	else
	{
		// PNG 리소스는 Bitmap 리소스를 불러오는 것보다 복잡하다.
		HRSRC hResource = ::FindResource(AfxGetApp()->m_hInstance, (WCHAR*)MAKEINTRESOURCEW(ID), _T("PNG"));	// 3번째 인자는 실제 리소스가 분류되는 문자열이 전달되어야 한다.
		if (!hResource) return false;

		DWORD imageSize = ::SizeofResource(AfxGetApp()->m_hInstance, hResource);
		if (!imageSize) return false;

		const void* pResourceData = ::LockResource(::LoadResource(AfxGetApp()->m_hInstance, hResource));
		if (!pResourceData) return false;

		HGLOBAL hBuffer  = ::GlobalAlloc(GMEM_MOVEABLE, imageSize);
		if (hBuffer)
		{
			void* pBuffer = ::GlobalLock(hBuffer);
			if (pBuffer)
			{
				CopyMemory(pBuffer, pResourceData, imageSize);

				IStream* pStream = NULL;
				if (::CreateStreamOnHGlobal(hBuffer, FALSE, &pStream) == S_OK)
				{
					m_pBmpImage = Gdiplus::Bitmap::FromStream(pStream);
					pStream->Release();

					if (m_pBmpImage)
					{
						if (m_pBmpImage->GetLastStatus() != Gdiplus::Ok)
						{
							delete m_pBmpImage;
							m_pBmpImage = NULL;
						}
					}
				}
			}
			::GlobalUnlock(hBuffer);
			::GlobalFree(hBuffer);
		}
	}
	
	
	if (m_pBmpImage->GetLastStatus() != Gdiplus::Ok)
		return false;
	
	Invalidate();

	return true;
}

bool CLabelEx::IsFileExist(CString strPath)
{
	HANDLE hFind;
	WIN32_FIND_DATA fd;
	if ((hFind = ::FindFirstFile(strPath, &fd)) == INVALID_HANDLE_VALUE) 
	{
		FindClose(hFind);
		return false;
	}

	return true;
}

void CLabelEx::SetColorBkg(int nA, COLORREF clrColor)
{
	int r = GetRValue(clrColor);
	int g = GetGValue(clrColor);
	int b = GetBValue(clrColor);

	m_clrBkg = Color(nA, r, g, b); 
	Invalidate();
}

void CLabelEx::SetColorBorder(int nA, COLORREF clrColor)
{
	int r = GetRValue(clrColor);
	int g = GetGValue(clrColor);
	int b = GetBValue(clrColor);

	m_clrBorder = Color(nA, r, g, b); 
	Invalidate();
}

void CLabelEx::SetColorText(int nA, COLORREF clrColor)
{
	int r = GetRValue(clrColor);
	int g = GetGValue(clrColor);
	int b = GetBValue(clrColor);

	m_clrText = Color(nA, r, g, b); 
	Invalidate();
}

void CLabelEx::SetTextDouble(double dValue, int nDigit)
{
	std::ostringstream ostring;
	
	ostring.setf(std::ios::fixed);
	ostring.precision(nDigit);
	ostring << dValue <<std::endl;
	
	m_strText = (CString)ostring.str().c_str();

	Invalidate();
}

bool CLabelEx::SetFontText(CString strFont)
{
	FontFamily fontFam(strFont);
	Gdiplus::Status ret = fontFam.GetLastStatus();
	if (ret != Gdiplus::Ok)
		return false;
	
	m_strFont = strFont;

	Invalidate();
	return true;
}