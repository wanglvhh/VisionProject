//////////////////////////////////////////////////////////////////////////
// ͷ�ļ�
// ���ߣ����¸�
// �������ڣ�2007-12-24
// ����޸����ڣ�2008-1-2
#if !defined(AFX_DIBRADIOBUTTON_H__223671A3_FDF0_4EDE_A13C_31050104D763__INCLUDED_)
#define AFX_DIBRADIOBUTTON_H__223671A3_FDF0_4EDE_A13C_31050104D763__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DibRadioButton.h : header file
//
// ����λͼ��
#define BITMAP_HEIGHT 11
// ����λͼ��
#define BITMAP_WIDTH  11
// ÿ��λͼ��Ŀ
#define BITMAP_PER_SET 6
// ͼ������
#define BITMAP_SETS	   2
/////////////////////////////////////////////////////////////////////////////
// CDibRadioButton window
#define WM_UNCHECKED WM_USER + 0X100

// RadioButton��״̬
typedef enum _RadioState_
{
	RADIOSTATE_SELECT,				// ѡ��
	RADIOSTATE_UNSELECT,			// δѡ��
	RADIOSTATE_SELMOUSEHOVER,		// ѡ��״̬��껬��
	RADIOSTATE_UNSELMOUSEHOVER,		// δѡ��״̬��껬��
	RADIOSTATE_PRESS,				// ѡ��״̬����
	RADIOSTATE_DISABLE				// �����ã���ɫ��
} RadioState;

class CDibRadioButton : public CButton
{
public:
	CDibRadioButton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDibRadioButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetRadioText(const char* str);
	// ���ÿؼ�����ɫ
	void SetBackColor(COLORREF colRGB);
	// �������ֱ���ɫ
	void SetTextBackColor(COLORREF colRGB);
	// ���ø������ֱ���ɫ
	void SetFocusTxtBackColor(COLORREF colRGB);
	// ����ԭ������ɫ
	void SetOriginalTxtColor(COLORREF colRGB);
	// ���ø���������ɫ
	void SetFocusTxtColor(COLORREF colRGB);
    // ���õ�ǰ������ɫ
	void SetTextColor(COLORREF txtColor = 0);

	// ����ͼ����ID
	void SetSetsID(int nSetID);
	// ���ð�ťͼƬ
	void SetRadioBitmap(UINT uiID);

	// �õ���ǰ������ɫ
	COLORREF GetCurrentTxtColor();
	// �õ����ָ�����ɫ
	COLORREF GetFocusTxtColor();
	// �õ�ԭ������ɫ
	COLORREF GetOriginalTxtColor();

	// ˢ��ͼ������
	void InvalidateThumbRect();
	// ���ش���
	BOOL Create(LPCTSTR lpszCaption, DWORD dwStyle, const RECT &rect, CWnd *pParentWnd, UINT nID);
	// ���ư�ť
	void DrawButton(CDC* pDC, UINT state);

	virtual ~CDibRadioButton();

	// Generated message map functions
protected:
	// ��ť����ʽ
	UINT m_nButtonStyle;
	// ѡ�б��
	BOOL m_bChecked;
	// �������±�ǣ�һ��down��Ӧһ��up��
//	BOOL m_bHasClickDown;
	// ����ѡ����״̬��m_radioState�Ǽ�ʱ״̬��������꾭��ʱ�ĸ���״̬��
	RadioState m_tRadioState;
	// �ı��ĵ�ǰ��ť״̬�����ţ�ѡ�С�δѡ�С���껬�������¡�DISABLE�ȣ�
	RadioState m_radioState;
	//��ť��״̬
	// �Ƿ�Disable���
	BOOL m_bDisabled;
	// ���λ�ڰ�ť֮��ʱ��ֵΪtrue����֮Ϊflase
	BOOL m_bMouseOver;
	// ����갴��û���ͷ�ʱ��ֵΪtrue
	BOOL m_bTracking;
	// ��ť�������Ǹ�ֵΪtrue
//	BOOL m_bSelected;		// ������m_bChecked����
	// ���������
	BOOL m_bPressed;
	// ��ťΪ��ǰ��������ʱ��ֵΪtrue
	BOOL m_bFocused;
	// ��ť����ɫ
	COLORREF m_BackColor;
	// ���ֱ���ɫ
	COLORREF m_TextBackColor;
	// �������ֱ���ɫ
	COLORREF m_FocusTxtBackColor;
	// ��ťͼƬ��ԴID
	UINT m_uiBitmap;
	// ��ťѡ�����ͼID������Ϊ��λ��˳��λ�Ƶõ���
	int m_nSetsID;
	// λͼ���������������ͬ��ɫ����ͼ�����ɫһ�׺���ɫһ�ף�
	int m_nSets;
	// ÿ��λͼ�ĸ���
	int m_nBitmapNumPerSet;
	// ѡ��λͼ�����ּ��
	int m_nSpaceBetween;
	// ����ԭ����ɫ
	COLORREF m_OriginalTxtColor;
	// ����������ɫ��Ĭ�ϣ���û�л�ý��㣬������ɫΪĬ��ʱ��������ɫ��
	COLORREF m_txtFocusColor;
	// ��ǰ������ɫ�������Ž����ת�ƶ��任��ɫ����Ӧ����ɫ�Ĳ�ͬ��
	COLORREF m_txtColor;
	// ��ʾ����
	CString m_strTxt;

	//{{AFX_MSG(CDibRadioButton)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseHover(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG
	afx_msg LRESULT OnUnCheck(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetCheck(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetCheck(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetStyle(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
private:
	// void CancelHover();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIBRADIOBUTTON_H__223671A3_FDF0_4EDE_A13C_31050104D763__INCLUDED_)
