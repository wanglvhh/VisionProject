#ifndef     TY_SKIN_CLASS
#define     TY_SKIN_CLASS

#include <afxwin.h>
#include <atlimage.h>
#include <string>
#include <gdiplus.h>
#include <vector>

using namespace std;
using namespace Gdiplus;

#define  SN_PIXEL_TO_POUND           7.4        //像素和英镑的比例
#define  SKIN_CONTROL_STATUS_COUNT   5          //控件状态总数

typedef enum SN_SHOWBK_MODE      //背景显示模式（颜色还是图片）
{
	SKIN_SHOWBK_IMAGE = 1,       //图片背景
	SKIN_SHOWBK_COLOR            //颜色背景
};

enum SN_BORDE_DIRECTION      //对话框边框位置
{
	SKIN_LEFT_BORDER = 0,
	SKIN_RIGHT_BORDER,
	SKIN_TOP_BORDER,
	SKIN_BOTTOM_BORDER
};

enum SN_CONTROL_STATUS       //控件的状态
{
	SKIN_STATUS_NOR = 0,      //正常
	SKIN_STATUS_HOT,          //光标在控件上
	SKIN_STATUS_PRE,          //鼠标左键按下
	SKIN_STATUS_DIS,          //禁用
	SKIN_STATUS_ALL           //所用状态
};

enum TABCTRL_ITEM_STYLE     //tab控件风格
{
	SKIN_TABCTRL_IMAGE_ITEM = 0,
	SKIN_TABCTRL_TEXT_ITEM
};

enum
{
	_nSortNone = 0,
	_nSortUp,
	_nSortDown,
	_nSortCount = 3,
};

class CSkinImage;
class CSkinGifImage;
class CSkinBackground;
class CSkinImage;
class CSkinControl;
class CSkinStatic;
class CSkinGroup;
class CSkinEdit;
class CSkinComboBox;
class CSkinButton;
class CSkinTabCtrl;
class CSkinCheckBox;
class CSkinDialog;

//显示图片类
class CSkinImage   //显示图片类
{
public:
	CSkinImage();

	BOOL         SnLondImage(const WCHAR *szPath);
	BOOL         SnLondImage(HMODULE hModule, const WCHAR *szRsName, const WCHAR *szRsType);
	BOOL         SnShow(BOOL bShow = TRUE);
	BOOL         SnMove(int nLeft, int nTop);
	BOOL         SnClear();
	virtual BOOL SnDraw(HWND hWnd, int nLeft, int nTop, int nWidth = 0, int nHeight = 0);

protected:
	virtual BOOL SnDoClear();
	virtual BOOL SnMessageProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK SnWndProc(HWND h, UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:
	HWND                    m_hImage;
	wstring                 m_strLink;
	ULONG_PTR               m_iToken;
	static LONG_PTR         m_iWndProc;
	Image                  *m_pImage;
	Graphics               *m_pGraphics;
	GUID                   *m_pDimensionIDs;
public:
	virtual ~CSkinImage();
};
//显示GIF动态图片
class CSkinGifImage : public CSkinImage   //显示GIF图片类
{
public:
	CSkinGifImage();
	virtual BOOL SnDraw(HWND hWnd, int nLeft, int nTop, int nWidth = 0, int nHeight = 0);

protected:
	virtual BOOL SnDoClear();
	virtual BOOL SnMessageProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:
	UINT                    m_iActive;
	UINT                    m_iFrameCount;
	PropertyItem          * m_pPropertyItem;
public:
	virtual ~CSkinGifImage();
};
//显示颜色背景
class CSkinBackground
{
public:
	CSkinBackground();

public:
	void    SnLoadColor(COLORREF crColor);     //加载颜色背景
	bool    SnLoadImage(LPCTSTR strPath);      //加载图片背景
	void    SnLoadGrab();

	void    SnShow(CDC *pDC, CRect rtRect);                  //显示背景

	void    SnCaptureClient(CWnd *pParent, LPCTSTR strPath);                  //截取对话框客户区保存为BMP图片
	void    SnCaptureClient(CWnd *pParent, LPCTSTR strPath, CRect rtRect);    //截取对话框客户区保存为BMP图片
	void    SnCaptureWindow(CWnd *pParent, LPCTSTR strPath);                  //截取对话框保存为BMP图片
	void    SnCaptureWindow(CWnd *pParent, LPCTSTR strPath, CRect rtRect);    //截取对话框保存为BMP图片
	void    SnCaptureScreen(CWnd *pParent, LPCTSTR strPath);                  //截取整个屏幕保存为BMP图片

protected:
	PBITMAPINFO   SnCreateBitmapInfoStruct(HWND hwnd, HBITMAP hBmp);
    void          SnCreateBMPFile(HWND hwnd, LPCTSTR pszFile, PBITMAPINFO pbi, HBITMAP hBMP, HDC hDC);  //将HBITMAP保存到文件

public:
	CBrush     m_SnBrush;
	CRect      m_SnRect;
	int        m_SnShowBkMode;

private:
	bool       m_SnDraw;

private:
	IPicture   *m_SnPicture;

public:
	~CSkinBackground();
};
//控件基类
class CSkinControl
{
public:
	CSkinControl();
	virtual ~CSkinControl();

public:
	//控件属性
	void        SnEnableWindow(BOOL nEnable = FALSE);   //控件禁用
	BOOL        SnIsWindowEnable();                     //控件是否禁用
	void        SnEnableHot(BOOL bEnable);              //HOT状态是否有特效
	void        SnEnablePre(BOOL bEnable);              //Pre状态是否有特效
	void        SnEnableTransparent(BOOL bEnable);      //设置是否控件透明

	//文本颜色和字体类型
	void        SnSetTextColor(COLORREF clrText, int nStatus);
	void        SnSetTextFont(int fontPixelSize, LPCTSTR fontName);

	//控件颜色背景
	void        SnSetBkColor(COLORREF clrBk, int nStatus);

	//控件图片背景
	BOOL        SnShowImage(LPCTSTR strPath, BOOL bAutoImgSize); //单张图片分成SKIN_CONTROL_STATUS_COUNT份，按顺序分别显示控件的所有状
	BOOL        SnShowImage(LPCTSTR strPath, int nStatus, BOOL bAutoImgSize);  	//单张图片只显示控件的一种状态

	BOOL        SnShowImage(LPCTSTR strPath,           //图片地址
		                    int nImgPartitionCount,    //单张图片图片平均分成nImgPartitionCount份
							int nPartNum,              //取第nPartNum份显示控件的一种状态
							int nStatus,                //状态类型
						    BOOL bAutoImgSize);         //控件适应图片大小

	//控件边框颜色
	void        SnSetFrameColor(COLORREF clrFrame, int nStatus);
	void        SnSetTextAlign(int nAlign);                //设置文本在控件上的位置

protected:
	BOOL        SnLoadImage(LPCTSTR strPath, int nStatus); //控件不同状态时候，显示不同图片
	BOOL        SnIsPNG(LPCTSTR  strPath);                 //判断图片格式是不是PNG，只有PNG格式才有透明效果
	void        SnTraBkgnd(CImage *pImg);                  //图片为PNG格式时候，调用此函数
	void        SnDrawText(LPCTSTR strText, CRect nRect);  //绘制控件的文本

	//控件大小位置
	void        SnGetRect();                              //获取控件大小

public:
	CWnd         *m_pWnd;
	HWND         m_thisHwnd;            //控件句柄
	int          m_nState;              //控件状态
	CDC          *m_pPaintDC;           //控件重绘时DC
	CFont*       m_pFont;               //控件字体
	BOOL         m_bTransparent;        //控件是否透明
	BOOL         m_bEnable;             //控件是否禁用
	BOOL         m_bFocus;              //焦点是否在控件上
    BOOL         m_bHot;                //HOT状态
	BOOL         m_bPre;                //Pre状态
	BOOL         m_bDrawTextToBottom;   //是否在控件下面显示文字

	BOOL         m_bHotSpecial;         //HOT状态是否有特效
	BOOL         m_bPreSpecial;         //Pre状态是否有特效
	BOOL         m_bAutoImgSize;        //控制是否适应图片大小
	BOOL         m_bTracking;           //鼠标移动是否有消息

	COLORREF     m_clrText[SKIN_CONTROL_STATUS_COUNT];     //不同状态时文本颜色
	COLORREF     m_clrBk[SKIN_CONTROL_STATUS_COUNT];       //不同状态时背景颜色
	CBrush       m_hBkBrush[SKIN_CONTROL_STATUS_COUNT];    //不同状态时背景颜色画刷
	COLORREF     m_clrFrame[SKIN_CONTROL_STATUS_COUNT];    //不同状态时边框颜色
	CBrush       m_hFrameBrush[SKIN_CONTROL_STATUS_COUNT]; //不同状态时边框颜色画刷
	CImage       *m_imgBk[SKIN_CONTROL_STATUS_COUNT];       //不同状态时的图片背景                           //

	int          m_nImgWidth;      //图片宽度
	int          m_nImgHeight;     //图片高度
	CRect        m_nRect;          //控件大小
	int          m_nfontPixelSize; //控件字体大小，像素值
	CString      m_ctrlText;       //控件文本
	int          m_nAlignment;     //控件文本在控件的位置
};
//静态文本
class CSkinStatic : public CStatic, public CSkinControl
{
	DECLARE_DYNAMIC(CSkinStatic)

public:
	CSkinStatic();

public:
	void    SnCreate(int nID, CWnd* pParent);

protected:
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	DECLARE_MESSAGE_MAP()

public:
	virtual ~CSkinStatic();
};
//Group控件
class CSkinGroup : public CButton, public CSkinControl
{
public:
	CSkinGroup();

public:
	void SnCreate(int nID, CWnd* pParent);
	void SnSetTextOffset(int nHoffset, int nVoffset = 0);
	void SnSetLineWidth(int nWidth);
	void SnSetText(CString strText);

protected:
	virtual void PreSubclassWindow();

private:
	BOOL     m_bStyleBitmap;
	int      m_nHOffset;
	int      m_nVOffset;
	int      m_nLineWidth;

protected:
	afx_msg void OnPaint();
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);

	DECLARE_MESSAGE_MAP()

public:
	virtual ~CSkinGroup();
};
//编辑框
class CSkinEdit : public CEdit, public CSkinControl
{
	DECLARE_DYNAMIC(CSkinEdit)

public:
	CSkinEdit();
	virtual ~CSkinEdit();

public:
	void    SnCreate(int nID, CWnd* pParent);
	void    SnPopupDlg(BOOL bPopupDlg);
	void    SnSetTextFont(int fontPixelSize, LPCTSTR fontName);

private:
	void    SnDrawFrame();    //绘制编辑框边框

public:
	BOOL    EnableWindow(BOOL bEnable);

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMouseHover(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnNcPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg LRESULT OnNcHitTest(CPoint point);

	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnUpdate();

public:
	BOOL   m_bPopupDlg;        //是否弹出对话框
	BOOL   m_bPopupClrDlg;     //是否弹出颜色框
};

class CSkinComboBox : public CComboBox, public CSkinControl
{
	DECLARE_DYNAMIC(CSkinComboBox)

public:
	CSkinComboBox();
	virtual ~CSkinComboBox();

protected:
	DECLARE_MESSAGE_MAP()

public:
	void SnCreate(int nID, CWnd* pParent);
	void SnSetTextFont(int fontPixelSize, LPCTSTR fontName);

protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual void    PreSubclassWindow();
	virtual BOOL    PreTranslateMessage(MSG* pMsg);
	virtual	void	DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

private:
	void SnDrawListBox(CDC* pDC, int nItemID, UINT uState, CRect rcItem); // 画下拉列表
	void SnDrawListItem(CDC* pDC, CString csText, CRect rcItem, COLORREF clrText, COLORREF clrBg, COLORREF clrFrame ); // 画下拉列表项背景
protected:
	afx_msg void OnPaint();
	afx_msg void OnKillFocus();
	afx_msg void OnSetFocus();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnCbnSelchange();
	afx_msg LRESULT OnNcHitTest(CPoint point);

private:
	void SnOnNoFlickerPaint(CDC* pDC);          //OnPaint 调用的绘制函数
	BOOL SnPointInRect();
	BOOL SnPointInBtn();

private:
	CEdit*	        m_pEdit;    //编辑框指针
	CListBox*		m_pListBox; //列表框指针
	int				m_nPreFocusListItem;
	int				m_nCurrFocusListItem;
	BOOL			m_bListItemFocus;
};
//按钮
class CSkinButton : public CButton, public CSkinControl
{
	DECLARE_DYNAMIC(CSkinButton)

public:
	CSkinButton();

public:
	void    SnCreate(int nID, CWnd* pParent);
	void    SnDrawTextToBottom();           //在按钮底部显示文本

private:
	void    SnDrawBK(HDC dc, CImage *pImg); //绘制按钮背景

public:
	BOOL    EnableWindow(BOOL bEnable);

protected:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void PreSubclassWindow();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	DECLARE_MESSAGE_MAP()

private:
	BOOL    m_bFirst;

public:
	~CSkinButton();
};
//Tab控件
class CSkinTabCtrl : public CTabCtrl , public CSkinControl
{
	DECLARE_DYNAMIC(CSkinTabCtrl)

public:
	CSkinTabCtrl();
	void    SnCreate(int nID, CWnd* pParent);
	void    SnSetItemStyle(int nItemStyle);
	void	SnSetItemPadding(int nPadding=8);

private:
	void   SnDrawBk();
	void   SnSetButton();
	BOOL   SnGetItemCount();
	void   SnSetTextItem();
	void   SnSetImageItem();

protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

private:
	int	   m_nItempadding;
	int    m_nItemCount;
	int    m_nSel;
	int    m_nItemStyle;

public:
	virtual ~CSkinTabCtrl();
};
//CHeaderCtrl控件
class CSkinHeaderCtrl : public CHeaderCtrl , public CSkinControl
{
	DECLARE_DYNAMIC(CSkinHeaderCtrl)
public:
	CSkinHeaderCtrl();
	virtual ~CSkinHeaderCtrl();
public:
	void SnSetItemSortState(int iItem, UINT sortState);
	UINT SnGetItemSortState(int iItem);
	void SnLoadBkImage(LPCTSTR strPath);
	void SnLoadSubLineImage(LPCTSTR strPath);
private:
	void SnInit();
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnLayout(WPARAM wParam,LPARAM lParam);
public:
	afx_msg void OnPaint();
	virtual void DoPaint(CDC *pDC);
protected:
	virtual void PreSubclassWindow();
public:
	afx_msg void OnHdnItemchanged(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);

private:
	CImage m_imageBk;
	CImage m_imageSubLine;
};
//CListCtrl控件
class CSkinListCtrl : public CListCtrl , public CSkinControl
{
	DECLARE_DYNAMIC(CSkinListCtrl)
public:

public:
	CSkinListCtrl();
	virtual ~CSkinListCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	void SnCreate(int nID, CWnd* pParent);
	void SnSetRowColor(int nRow, COLORREF clrRow);
	void SnSetListItemHeight(unsigned int nHeight);
	void SnLoadHeaderImage(LPCTSTR strBkPath, LPCTSTR strSubLinePath);
	void SnSetHeaderTextColor(COLORREF clrText);
	void SnSetHeaderTextFont(int fontPixelSize, LPCTSTR fontName);

protected:
	void SnInit();
	void SnDrawRowColor(CDC *pDC, CRect nRect, BOOL bSelected, BOOL bFocus,int nRow);
	void SnDrawSubItem(CDC *pDC, int nItem, int nSubItem, CRect &rSubItem, BOOL bSelected, BOOL bFocus);
	void SnDrawRemainSpace(LPNMLVCUSTOMDRAW lpnmcd);
	void SnInvalidateItem(int nItem);

public:
	int InsertItem(int nItem, LPCTSTR lpszItem);
public:
	afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchanged(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHdnItemchanged(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnEndScroll(NMHDR *pNMHDR, LRESULT *pResult);
	virtual void PreSubclassWindow();
private:
	CSkinHeaderCtrl  m_header;
	int              m_nRow;
	COLORREF         m_clrRow;
	vector<COLORREF> m_vecClr;
	unsigned int     m_listItemHeight;
};
//class CS
class CSkinDialog : public CDialog
{
	DECLARE_DYNAMIC(CSkinDialog)

public:
	CSkinDialog(UINT IDDialog, CWnd* pParent = NULL);   //标准构造函数

public:
	void SnShowImageBk(LPCTSTR  strPath, BOOL bAutoImageSize = FALSE);
	void SnShowColorBk(COLORREF crColor);
	void SnMoveWindow(BOOL bMove);                   //设置对话框是否可以移动
	void SnSetTransparent(BOOL bTransparen);         //设置对话是否透明，子对话框可以融合父窗口
	virtual BOOL PreTranslateMessage(MSG* pMsg);
private:
	void SnModifyStyle();
	;

protected:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();

public:
	BOOL               m_bEdit;

private:
	CImage             m_bkImage;
	CBrush             m_bkBrush;
	BOOL               m_bShow;
	BOOL               m_bMove;
	BOOL               m_bTransparent;
public:
	virtual ~CSkinDialog();
};

#endif     //TY_SKIN_CLASS