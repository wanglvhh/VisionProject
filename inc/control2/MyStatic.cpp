// MyStatic.cpp : 实现文件
//

#include "stdafx.h"
#include "MyStatic.h"

// CMyStatic
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(CMyStatic, CStatic)

CMyStatic::CMyStatic()
{
}

CMyStatic::~CMyStatic()
{
}

BEGIN_MESSAGE_MAP(CMyStatic, CStatic)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

void  CMyStatic::OnMouseMove(UINT   nFlags,   CPoint   point)
{
	//   TODO:   在此添加消息处理程序代码和/或调用默认值

	if(this->GetParent()  !=NULL)
	{
		GetParent()->SendMessage(WM_STATICMOUSE);
	}
    SetFocus() ;
	CStatic::OnMouseMove(nFlags,   point);
}

void  CMyStatic::OnLButtonDown(UINT   nFlags,   CPoint   point)
{
	if(this->GetParent()   !=NULL)
	{
		GetParent()->SendMessage(WM_LBTNDOWN);
	}
    SetFocus() ;
	CStatic::OnLButtonDown(nFlags,point);
}

void  CMyStatic::OnRButtonDown(UINT   nFlags,   CPoint   point)
{
	if(this->GetParent()   !=NULL)
	{
		GetParent()->SendMessage(WM_RBTNDOWN);
	}
    SetFocus() ;
	CStatic::OnLButtonDown(nFlags,point);
}

void  CMyStatic::OnMButtonDown(UINT   nFlags,   CPoint   point)
{
	if(this->GetParent()   !=NULL)
	{
		GetParent()->SendMessage(WM_MBTNDOWN);
	}
    SetFocus() ;
	CStatic::OnMButtonDown(nFlags,point);
}

void  CMyStatic::OnLButtonUp(UINT   nFlags,   CPoint   point)
{
	if(this->GetParent()   !=NULL)
	{
		GetParent()->SendMessage(WM_LBTNUP);
	}
    SetFocus() ;
	CStatic::OnLButtonUp(nFlags,point);
}