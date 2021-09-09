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

	int m_ispeed;//�˶��ٶ�
	BOOL m_bMove;//�Ƿ��˶�
	int m_wndwidth;//�Ӵ���Ŀ��
	CPoint m_bottomright;//�Ӵ������½ǵ�����
	CPoint m_topleft;//�Ӵ������Ͻǵ�����
	CWnd *m_pCurWnd;//��ǰ����
	CRect m_tabrect;//Tab�ľ�������
	CPoint m_ptTabs;//���Ͻ�����
	void AddItem(CWnd *pwnd,LPTSTR name);//���ѡ�
	int m_itemcount;//Item����
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
