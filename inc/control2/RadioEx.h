#pragma once

//----------------------------------------------------------
// RadioEx Control
//----------------------------------------------------------
// Programmed by William Kim
//----------------------------------------------------------
// Last Update : 2017-07-21 10:18
// Modified by William Kim
//----------------------------------------------------------

// CRadioEx

class CRadioEx : public CButton
{
	DECLARE_DYNAMIC(CRadioEx)

public:
	CRadioEx();
	virtual ~CRadioEx();
public :
	//----- Set Enable & Disable Control -----//
	void SetEnable(bool bEnable) { m_bEnable = bEnable; EnableWindow(m_bEnable); Invalidate(); }

	//----- Set Text -----//
	void SetText(CString strText) { SetWindowText(strText); Invalidate(); }

	//----- Set Offset -----//
	// SetSize...() 이후에 선언되어야 함.
	void SetOffsetText	(int nX, int nY) { m_rcCaption.Offset(nX, nY); Invalidate(); }

	//----- Set Size -----//
	void SetSizeText	(float fSize) { m_fSizeText		= fSize; Invalidate(); }
	void SetSizeBorder	(float fSize) { m_fSizeBorder	= fSize; Invalidate(); }
	void SetSizeCheck	(int nSize) { m_nSizeCheck	= nSize; Invalidate(); }
	void SetSizeImage	(int nLeft, int nTop, int nWidth, int nHeight) { m_rcImage = Rect(nLeft, nTop, nWidth, nHeight); Invalidate(); }
	void SetSizeCheckBox(int nLeft, int nTop, int nWidth, int nHeight);

	//----- Set Color -----//
	void SetColorBkg		(int nChkA, int nChkR, int nChkG, int nChkB, int nUnChkA, int nUnChkR, int nUnChkG, int nUnChkB);
	void SetColorChkBkg		(int nA, int nR, int nG, int nB) { m_clrChkBkg		= Color(nA, nR, nG, nB); Invalidate(); }
	void SetColorUnChkBkg	(int nA, int nR, int nG, int nB) { m_clrUnChkBkg	= Color(nA, nR, nG, nB); Invalidate(); }
	void SetColorBorder		(int nA, int nR, int nG, int nB) { m_clrBorder		= Color(nA, nR, nG, nB); Invalidate(); }
	void SetColorBoxBkg		(int nA, int nR, int nG, int nB) { m_clrBoxBkg		= Color(nA, nR, nG, nB); Invalidate(); }
	void SetColorBoxBorder	(int nA, int nR, int nG, int nB) { m_clrBoxBorder	= Color(nA, nR, nG, nB); Invalidate(); }
	void SetColorCheck		(int nA, int nR, int nG, int nB) { m_clrCheck		= Color(nA, nR, nG, nB); Invalidate(); }
	void SetColorText		(int nA, int nR, int nG, int nB) { m_clrText		= Color(nA, nR, nG, nB); Invalidate(); }
	void SetColorBkg		(int nChkA, COLORREF clrChk, int nUnChkA, COLORREF clrUnChk);
	void SetColorChkBkg		(int nA, COLORREF clrColor);
	void SetColorUnChkBkg	(int nA, COLORREF clrColor);
	void SetColorBorder		(int nA, COLORREF clrColor);
	void SetColorBoxBkg		(int nA, COLORREF clrColor);
	void SetColorBoxBorder	(int nA, COLORREF clrColor);
	void SetColorCheck		(int nA, COLORREF clrColor);
	void SetColorText		(int nA, COLORREF clrColor);

	//----- Set Text Alignment -----//
	void SetAlignTextLT() { m_nTextAlign1 = 0; m_nTextAlign2 = 0; Invalidate(); }
	void SetAlignTextCT() { m_nTextAlign1 = 1; m_nTextAlign2 = 0; Invalidate(); }				   
	void SetAlignTextRT() { m_nTextAlign1 = 2; m_nTextAlign2 = 0; Invalidate(); }
	void SetAlignTextLM() { m_nTextAlign1 = 0; m_nTextAlign2 = 1; Invalidate(); }
	void SetAlignTextCM() { m_nTextAlign1 = 1; m_nTextAlign2 = 1; Invalidate(); }
	void SetAlignTextRM() { m_nTextAlign1 = 2; m_nTextAlign2 = 1; Invalidate(); }
	void SetAlignTextLB() { m_nTextAlign1 = 0; m_nTextAlign2 = 2; Invalidate(); }
	void SetAlignTextCB() { m_nTextAlign1 = 1; m_nTextAlign2 = 2; Invalidate(); }
	void SetAlignTextRB() { m_nTextAlign1 = 2; m_nTextAlign2 = 2; Invalidate(); }

	//----- Set Image -----//
	bool LoadImageFromFile(CString strPath);
	bool LoadImageFromResource(UINT ID, bool bPNG);
	bool LoadImageFromFile(CString strCheck, CString strUnCheck);
	bool LoadImageFromResource(UINT idCheck, UINT idUnCheck, bool bPNG);

	//----- Set Group -----//
	void SetGroupBegin() { ModifyStyle(0,WS_GROUP); Invalidate(); }
	void SetGroupEnd() { ModifyStyle(0,WS_TABSTOP); Invalidate(); }

	//----- Set & Get Check -----//
	void SetCheckButton(bool bCheck) { bCheck ? SetCheck(1) : SetCheck(0); }
	bool GetCheckedButton() { int state = GetCheck(); bool ret;state==1 ? ret=true : ret=false; return ret; }

	

private :
	bool	m_bEnable;
	bool	m_bClicked;
	int		m_nOffsetTextX;
	int		m_nOffsetTextY;
	int		m_nTextAlign1;
	int		m_nTextAlign2;
	int		m_nSizeCheck;
	float	m_fSizeText;
	float	m_fSizeBorder;
	float	m_fSizeBoxBorder;
	Color	m_clrChkBkg;
	Color	m_clrUnChkBkg;
	Color	m_clrText;
	Color	m_clrBorder;
	Color	m_clrBoxBorder;
	Color	m_clrBoxBkg;
	Color	m_clrCheck;
	Bitmap* m_pBmpImage;
	Bitmap* m_pBmpCheck;
	Bitmap* m_pBmpUnCheck;
	Rect	m_rcImage;
	Rect	m_rcCaption;
	Rect	m_rcCheckBox;
	BOOL	m_bMouseTrack;

private :
	void DrawBkg(Graphics *pG);
	void DrawBorder(Graphics *pG);
	void DrawBoxBkg(Graphics *pG);
	void DrawBoxBorder(Graphics *pG);
	void DrawCheck(Graphics *pG);
	void DrawImage(Graphics *pG);
	void DrawText(Graphics *pG);
	void DrawBitmap(Graphics *pG);
	bool IsFileExist(CString strPath);

protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnMouseLeave();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};


