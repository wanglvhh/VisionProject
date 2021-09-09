#if !defined(AFX_MYTAB_H__35A5A4AD_55EF_4C16_960F_E6CCB76271D6__INCLUDED_)
#define AFX_MYTAB_H__35A5A4AD_55EF_4C16_960F_E6CCB76271D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyTab.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyTab window

class CMyTab : public CTabCtrl
{
// Construction
public:
	CMyTab();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyTab)
	//}}AFX_VIRTUAL

// Implementation
public:

	int m_ispeed;//运动速度
	BOOL m_bMove;//是否运动
	int m_wndwidth;//子窗体的宽度
	CPoint m_bottomright;//子窗体右下角的坐标
	CPoint m_topleft;//子窗体左上角的坐标
	CWnd *m_pCurWnd;//当前窗体
	CRect m_tabrect;//Tab的矩形区域
	CPoint m_ptTabs;//左上角坐标
	void AddItem(CWnd *pwnd,LPTSTR name);//添加选项卡
	int m_itemcount;//Item总数
	virtual ~CMyTab();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyTab)
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSelchange(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchanging(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYTAB_H__35A5A4AD_55EF_4C16_960F_E6CCB76271D6__INCLUDED_)
