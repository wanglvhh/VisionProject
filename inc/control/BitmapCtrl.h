#pragma once

// CBitmapCtrl

class CBitmapCtrl : public CWnd
{
	DECLARE_DYNAMIC(CBitmapCtrl)

public:
	CBitmapCtrl();
	virtual ~CBitmapCtrl();

	BOOL Create(const RECT& rect, CWnd* parent, UINT nID,
		DWORD dwStyle = WS_CHILD | WS_BORDER | WS_TABSTOP | WS_VISIBLE);

	DECLARE_MESSAGE_MAP()

protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	BOOL	RegisterWindowClass();

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

public:
	BOOL LoadBitmap(LPCTSTR lpszPath);
	BOOL LoadBitmap(UINT nID);
	void Refresh();
	CDC* GetMemDC();

private:
	void	InitDC();
	void	ReleaseDC();

private:
	CDC		*m_pScrDC;
	CDC		*m_pMemDC;
	CBitmap m_Bitmap;
	CRect	m_Rect;
	CSize	m_BitmapSize;
	BOOL	m_bLoad;
};
