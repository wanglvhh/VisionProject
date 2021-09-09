#ifndef     TY_SKIN_CLASS
#define     TY_SKIN_CLASS

#include <afxwin.h>
#include <atlimage.h>
#include <string>
#include <gdiplus.h>
#include <vector>

using namespace std;
using namespace Gdiplus;

#define  SN_PIXEL_TO_POUND           7.4        //���غ�Ӣ���ı���
#define  SKIN_CONTROL_STATUS_COUNT   5          //�ؼ�״̬����

typedef enum SN_SHOWBK_MODE      //������ʾģʽ����ɫ����ͼƬ��
{
	SKIN_SHOWBK_IMAGE = 1,       //ͼƬ����
	SKIN_SHOWBK_COLOR            //��ɫ����
};

enum SN_BORDE_DIRECTION      //�Ի���߿�λ��
{
	SKIN_LEFT_BORDER = 0,
	SKIN_RIGHT_BORDER,
	SKIN_TOP_BORDER,
	SKIN_BOTTOM_BORDER
};

enum SN_CONTROL_STATUS       //�ؼ���״̬
{
	SKIN_STATUS_NOR = 0,      //����
	SKIN_STATUS_HOT,          //����ڿؼ���
	SKIN_STATUS_PRE,          //����������
	SKIN_STATUS_DIS,          //����
	SKIN_STATUS_ALL           //����״̬
};

enum TABCTRL_ITEM_STYLE     //tab�ؼ����
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

//��ʾͼƬ��
class CSkinImage   //��ʾͼƬ��
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
//��ʾGIF��̬ͼƬ
class CSkinGifImage : public CSkinImage   //��ʾGIFͼƬ��
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
//��ʾ��ɫ����
class CSkinBackground
{
public:
	CSkinBackground();

public:
	void    SnLoadColor(COLORREF crColor);     //������ɫ����
	bool    SnLoadImage(LPCTSTR strPath);      //����ͼƬ����
	void    SnLoadGrab();

	void    SnShow(CDC *pDC, CRect rtRect);                  //��ʾ����

	void    SnCaptureClient(CWnd *pParent, LPCTSTR strPath);                  //��ȡ�Ի���ͻ�������ΪBMPͼƬ
	void    SnCaptureClient(CWnd *pParent, LPCTSTR strPath, CRect rtRect);    //��ȡ�Ի���ͻ�������ΪBMPͼƬ
	void    SnCaptureWindow(CWnd *pParent, LPCTSTR strPath);                  //��ȡ�Ի��򱣴�ΪBMPͼƬ
	void    SnCaptureWindow(CWnd *pParent, LPCTSTR strPath, CRect rtRect);    //��ȡ�Ի��򱣴�ΪBMPͼƬ
	void    SnCaptureScreen(CWnd *pParent, LPCTSTR strPath);                  //��ȡ������Ļ����ΪBMPͼƬ

protected:
	PBITMAPINFO   SnCreateBitmapInfoStruct(HWND hwnd, HBITMAP hBmp);
    void          SnCreateBMPFile(HWND hwnd, LPCTSTR pszFile, PBITMAPINFO pbi, HBITMAP hBMP, HDC hDC);  //��HBITMAP���浽�ļ�

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
//�ؼ�����
class CSkinControl
{
public:
	CSkinControl();
	virtual ~CSkinControl();

public:
	//�ؼ�����
	void        SnEnableWindow(BOOL nEnable = FALSE);   //�ؼ�����
	BOOL        SnIsWindowEnable();                     //�ؼ��Ƿ����
	void        SnEnableHot(BOOL bEnable);              //HOT״̬�Ƿ�����Ч
	void        SnEnablePre(BOOL bEnable);              //Pre״̬�Ƿ�����Ч
	void        SnEnableTransparent(BOOL bEnable);      //�����Ƿ�ؼ�͸��

	//�ı���ɫ����������
	void        SnSetTextColor(COLORREF clrText, int nStatus);
	void        SnSetTextFont(int fontPixelSize, LPCTSTR fontName);

	//�ؼ���ɫ����
	void        SnSetBkColor(COLORREF clrBk, int nStatus);

	//�ؼ�ͼƬ����
	BOOL        SnShowImage(LPCTSTR strPath, BOOL bAutoImgSize); //����ͼƬ�ֳ�SKIN_CONTROL_STATUS_COUNT�ݣ���˳��ֱ���ʾ�ؼ�������״
	BOOL        SnShowImage(LPCTSTR strPath, int nStatus, BOOL bAutoImgSize);  	//����ͼƬֻ��ʾ�ؼ���һ��״̬

	BOOL        SnShowImage(LPCTSTR strPath,           //ͼƬ��ַ
		                    int nImgPartitionCount,    //����ͼƬͼƬƽ���ֳ�nImgPartitionCount��
							int nPartNum,              //ȡ��nPartNum����ʾ�ؼ���һ��״̬
							int nStatus,                //״̬����
						    BOOL bAutoImgSize);         //�ؼ���ӦͼƬ��С

	//�ؼ��߿���ɫ
	void        SnSetFrameColor(COLORREF clrFrame, int nStatus);
	void        SnSetTextAlign(int nAlign);                //�����ı��ڿؼ��ϵ�λ��

protected:
	BOOL        SnLoadImage(LPCTSTR strPath, int nStatus); //�ؼ���ͬ״̬ʱ����ʾ��ͬͼƬ
	BOOL        SnIsPNG(LPCTSTR  strPath);                 //�ж�ͼƬ��ʽ�ǲ���PNG��ֻ��PNG��ʽ����͸��Ч��
	void        SnTraBkgnd(CImage *pImg);                  //ͼƬΪPNG��ʽʱ�򣬵��ô˺���
	void        SnDrawText(LPCTSTR strText, CRect nRect);  //���ƿؼ����ı�

	//�ؼ���Сλ��
	void        SnGetRect();                              //��ȡ�ؼ���С

public:
	CWnd         *m_pWnd;
	HWND         m_thisHwnd;            //�ؼ����
	int          m_nState;              //�ؼ�״̬
	CDC          *m_pPaintDC;           //�ؼ��ػ�ʱDC
	CFont*       m_pFont;               //�ؼ�����
	BOOL         m_bTransparent;        //�ؼ��Ƿ�͸��
	BOOL         m_bEnable;             //�ؼ��Ƿ����
	BOOL         m_bFocus;              //�����Ƿ��ڿؼ���
    BOOL         m_bHot;                //HOT״̬
	BOOL         m_bPre;                //Pre״̬
	BOOL         m_bDrawTextToBottom;   //�Ƿ��ڿؼ�������ʾ����

	BOOL         m_bHotSpecial;         //HOT״̬�Ƿ�����Ч
	BOOL         m_bPreSpecial;         //Pre״̬�Ƿ�����Ч
	BOOL         m_bAutoImgSize;        //�����Ƿ���ӦͼƬ��С
	BOOL         m_bTracking;           //����ƶ��Ƿ�����Ϣ

	COLORREF     m_clrText[SKIN_CONTROL_STATUS_COUNT];     //��ͬ״̬ʱ�ı���ɫ
	COLORREF     m_clrBk[SKIN_CONTROL_STATUS_COUNT];       //��ͬ״̬ʱ������ɫ
	CBrush       m_hBkBrush[SKIN_CONTROL_STATUS_COUNT];    //��ͬ״̬ʱ������ɫ��ˢ
	COLORREF     m_clrFrame[SKIN_CONTROL_STATUS_COUNT];    //��ͬ״̬ʱ�߿���ɫ
	CBrush       m_hFrameBrush[SKIN_CONTROL_STATUS_COUNT]; //��ͬ״̬ʱ�߿���ɫ��ˢ
	CImage       *m_imgBk[SKIN_CONTROL_STATUS_COUNT];       //��ͬ״̬ʱ��ͼƬ����                           //

	int          m_nImgWidth;      //ͼƬ���
	int          m_nImgHeight;     //ͼƬ�߶�
	CRect        m_nRect;          //�ؼ���С
	int          m_nfontPixelSize; //�ؼ������С������ֵ
	CString      m_ctrlText;       //�ؼ��ı�
	int          m_nAlignment;     //�ؼ��ı��ڿؼ���λ��
};
//��̬�ı�
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
//Group�ؼ�
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
//�༭��
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
	void    SnDrawFrame();    //���Ʊ༭��߿�

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
	BOOL   m_bPopupDlg;        //�Ƿ񵯳��Ի���
	BOOL   m_bPopupClrDlg;     //�Ƿ񵯳���ɫ��
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
	void SnDrawListBox(CDC* pDC, int nItemID, UINT uState, CRect rcItem); // �������б�
	void SnDrawListItem(CDC* pDC, CString csText, CRect rcItem, COLORREF clrText, COLORREF clrBg, COLORREF clrFrame ); // �������б����
protected:
	afx_msg void OnPaint();
	afx_msg void OnKillFocus();
	afx_msg void OnSetFocus();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnCbnSelchange();
	afx_msg LRESULT OnNcHitTest(CPoint point);

private:
	void SnOnNoFlickerPaint(CDC* pDC);          //OnPaint ���õĻ��ƺ���
	BOOL SnPointInRect();
	BOOL SnPointInBtn();

private:
	CEdit*	        m_pEdit;    //�༭��ָ��
	CListBox*		m_pListBox; //�б��ָ��
	int				m_nPreFocusListItem;
	int				m_nCurrFocusListItem;
	BOOL			m_bListItemFocus;
};
//��ť
class CSkinButton : public CButton, public CSkinControl
{
	DECLARE_DYNAMIC(CSkinButton)

public:
	CSkinButton();

public:
	void    SnCreate(int nID, CWnd* pParent);
	void    SnDrawTextToBottom();           //�ڰ�ť�ײ���ʾ�ı�

private:
	void    SnDrawBK(HDC dc, CImage *pImg); //���ư�ť����

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
//Tab�ؼ�
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
//CHeaderCtrl�ؼ�
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
//CListCtrl�ؼ�
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
	CSkinDialog(UINT IDDialog, CWnd* pParent = NULL);   //��׼���캯��

public:
	void SnShowImageBk(LPCTSTR  strPath, BOOL bAutoImageSize = FALSE);
	void SnShowColorBk(COLORREF crColor);
	void SnMoveWindow(BOOL bMove);                   //���öԻ����Ƿ�����ƶ�
	void SnSetTransparent(BOOL bTransparen);         //���öԻ��Ƿ�͸�����ӶԻ�������ںϸ�����
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