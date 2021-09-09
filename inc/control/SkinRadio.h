//////////////////////////////////////////////////////////////////////////
// 头文件
// 作者：董陈刚
// 创建日期：2007-12-24
// 最后修改日期：2008-1-2
#if !defined(AFX_DIBRADIOBUTTON_H__223671A3_FDF0_4EDE_A13C_31050104D763__INCLUDED_)
#define AFX_DIBRADIOBUTTON_H__223671A3_FDF0_4EDE_A13C_31050104D763__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DibRadioButton.h : header file
//
// 单个位图高
#define BITMAP_HEIGHT 11
// 单个位图宽
#define BITMAP_WIDTH  11
// 每套位图数目
#define BITMAP_PER_SET 6
// 图标套数
#define BITMAP_SETS	   2
/////////////////////////////////////////////////////////////////////////////
// CDibRadioButton window
#define WM_UNCHECKED WM_USER + 0X100

// RadioButton的状态
typedef enum _RadioState_
{
	RADIOSTATE_SELECT,				// 选中
	RADIOSTATE_UNSELECT,			// 未选中
	RADIOSTATE_SELMOUSEHOVER,		// 选中状态鼠标滑过
	RADIOSTATE_UNSELMOUSEHOVER,		// 未选中状态鼠标滑过
	RADIOSTATE_PRESS,				// 选中状态按下
	RADIOSTATE_DISABLE				// 不可用（灰色）
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
	// 设置控件背景色
	void SetBackColor(COLORREF colRGB);
	// 设置文字背景色
	void SetTextBackColor(COLORREF colRGB);
	// 设置高亮文字背景色
	void SetFocusTxtBackColor(COLORREF colRGB);
	// 设置原文字颜色
	void SetOriginalTxtColor(COLORREF colRGB);
	// 设置高亮文字颜色
	void SetFocusTxtColor(COLORREF colRGB);
    // 设置当前文字颜色
	void SetTextColor(COLORREF txtColor = 0);

	// 设置图等套ID
	void SetSetsID(int nSetID);
	// 设置按钮图片
	void SetRadioBitmap(UINT uiID);

	// 得到当前文字颜色
	COLORREF GetCurrentTxtColor();
	// 得到文字高亮颜色
	COLORREF GetFocusTxtColor();
	// 得到原文字颜色
	COLORREF GetOriginalTxtColor();

	// 刷新图标区域
	void InvalidateThumbRect();
	// 重载创建
	BOOL Create(LPCTSTR lpszCaption, DWORD dwStyle, const RECT &rect, CWnd *pParentWnd, UINT nID);
	// 绘制按钮
	void DrawButton(CDC* pDC, UINT state);

	virtual ~CDibRadioButton();

	// Generated message map functions
protected:
	// 按钮的样式
	UINT m_nButtonStyle;
	// 选中标记
	BOOL m_bChecked;
	// 单击按下标记（一个down对应一个up）
//	BOOL m_bHasClickDown;
	// 保存选择后的状态（m_radioState是即时状态，包括鼠标经过时的高亮状态）
	RadioState m_tRadioState;
	// 改变后的当前按钮状态索引号（选中、未选中、鼠标滑过、按下、DISABLE等）
	RadioState m_radioState;
	//按钮的状态
	// 是否Disable标记
	BOOL m_bDisabled;
	// 鼠标位于按钮之上时该值为true，反之为flase
	BOOL m_bMouseOver;
	// 在鼠标按下没有释放时该值为true
	BOOL m_bTracking;
	// 按钮被按下是该值为true
//	BOOL m_bSelected;		// 现在用m_bChecked代替
	// 按下鼠标标记
	BOOL m_bPressed;
	// 按钮为当前焦点所在时该值为true
	BOOL m_bFocused;
	// 按钮背景色
	COLORREF m_BackColor;
	// 文字背景色
	COLORREF m_TextBackColor;
	// 高亮文字背景色
	COLORREF m_FocusTxtBackColor;
	// 按钮图片资源ID
	UINT m_uiBitmap;
	// 按钮选择的套图ID（以套为单位，顺序位移得到）
	int m_nSetsID;
	// 位图的套数（这里代表不同颜色的套图，如橙色一套和蓝色一套）
	int m_nSets;
	// 每套位图的个数
	int m_nBitmapNumPerSet;
	// 选中位图和文字间距
	int m_nSpaceBetween;
	// 文字原本颜色
	COLORREF m_OriginalTxtColor;
	// 高亮文字颜色（默认，当没有获得焦点，即背景色为默认时的文字颜色）
	COLORREF m_txtFocusColor;
	// 当前文字颜色（会随着焦点的转移而变换颜色，适应背景色的不同）
	COLORREF m_txtColor;
	// 显示文字
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
