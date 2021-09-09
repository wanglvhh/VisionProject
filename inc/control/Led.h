///////////////////////////////////////////////////////////////////////////////
// Led.h : header file
// Visual Source Safe: $Revision: 1.1 $
//
// Led static control. Will display a LED in 4 different colors and two shapes.
///////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1998-1999 Monte Variakojis ( monte@apollocom.com )
// All rights reserved - not to be sold.
///////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_LEDWND_H__2D837381_FFEC_11D1_A1CE_00A024D311C0__INCLUDED_)
#define AFX_LEDWND_H__2D837381_FFEC_11D1_A1CE_00A024D311C0__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
/////////////////////////////////////////////////////////////////////////////
// CLed window
#define RED   	RGB(255,0,0)
#define	GREEN 	RGB(0,255,0)
#define GRAY    RGB(128, 128, 128)
class CLed : public CStatic
{
protected:
	int m_nLedMode;

public:
	enum {
		LED_ON = 0,							// Column 0
		LED_OFF = 1,						// Column 1
		LED_DISABLED = 2,					// Column 2
	};

// Construction
public:
	CLed();

// Attributes
public:

// Operations
public:
	void SetLed(int nMode);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLed)
	public:
	//}}AFX_VIRTUAL

// Implementation
public:
	void DrawLed( CDC *pDC, int nMode);
	virtual ~CLed();
	// Generated message map functions
protected:
	//{{AFX_MSG(CLed)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEDWND_H__2D837381_FFEC_11D1_A1CE_00A024D311C0__INCLUDED_)
