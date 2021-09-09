#pragma once

// CMyStatic
#ifndef MYSTATIC_H
#define MYSTATIC_H

#define WM_STATICMOUSE   WM_USER+500
#define WM_LBTNDOWN      WM_USER+1000
#define WM_RBTNDOWN      WM_USER+1001
#define WM_MBTNDOWN     WM_USER+1002
#define WM_LBTNUP             WM_USER+1003

class CMyStatic : public CStatic
{
	DECLARE_DYNAMIC(CMyStatic)
public:
	CMyStatic();
	virtual ~CMyStatic();
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg   void   OnMouseMove(UINT   nFlags,   CPoint   point) ;
	afx_msg   void   OnLButtonDown(UINT   nFlags,   CPoint   point) ;
	afx_msg   void   OnRButtonDown(UINT   nFlags,   CPoint   point) ;
	afx_msg   void   OnMButtonDown(UINT   nFlags,   CPoint   point) ;
	afx_msg   void   OnLButtonUp(UINT   nFlags,   CPoint   point) ;
};

#endif