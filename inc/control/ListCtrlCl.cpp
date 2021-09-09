#include "stdafx.h"
#include "ListCtrlCl.h"

struct stColor
{
	int nRow;
	int nCol;
	COLORREF rgb;
};
// CListCtrlCl
IMPLEMENT_DYNAMIC(CListCtrlCl, CListCtrl)
	CListCtrlCl::CListCtrlCl()
	: m_nRowHeight(0)
	, m_fontHeight(12)
	, m_fontWith(0)
{
	m_color = RGB(0,0,0);
}
CListCtrlCl::~CListCtrlCl()
{
	stColor *ptemp = NULL;
	while (m_ptrListCol.GetCount() > 0)
	{
		ptemp = (stColor *)(m_ptrListCol.RemoveHead());
		if ( NULL != ptemp )
		{
			delete ptemp;
			ptemp = NULL;
		}
	}
	while ( m_ptrListItem.GetCount() > 0)
	{
		ptemp = (stColor *)(m_ptrListItem.RemoveHead());
		if ( NULL != ptemp )
		{
			delete ptemp;
			ptemp = NULL;
		}
	}
	while ( m_colTextColor.GetCount() > 0)
	{
		ptemp = (stColor *)(m_colTextColor.RemoveHead());
		if ( NULL != ptemp )
		{
			delete ptemp;
			ptemp = NULL;
		}
	}
	while ( m_ItemTextColor.GetCount() > 0)
	{
		ptemp = (stColor *)(m_ItemTextColor.RemoveHead());
		if ( NULL != ptemp )
		{
			delete ptemp;
			ptemp = NULL;
		}
	}
}
BEGIN_MESSAGE_MAP(CListCtrlCl, CListCtrl)
	ON_WM_MEASUREITEM_REFLECT()
END_MESSAGE_MAP()
// CListCtrlCl ��Ϣ�������

//�ڴ�Դ�����е�����
//֮��������Դ�༭���о�̬���Ͻ�ȥ�ؼ�����������, ��������Ϊ�Ͻ�ȥ�ؼ�ʱ���Ѿ�������styleΪLVS_REPORT, ͨ��ʵ����Է���, �������LVS_REPORTʱ, ��ô��PreSubclassWindow()������GetHeaderCtrl()��Ȼ�᷵��NULL.
//Ψһ�����Ի󲻽����, ��̬���ʱ, �����ָ����styleΪLVS_REPORT, ��ô��ȻPreSubclassWindow()���ǲ����ܵ�, ��OnCreate()��ȴһֱGetHeaderCtrl()������������
//����ԭ��ɲ��յ�http://wangqingyun84.blog.163.com/blog/static/7908361720119744913240/

void CListCtrlCl::PreSubclassWindow()
{
	// TODO: �ڴ����ר�ô����/����û���
	ModifyStyle(0,LVS_OWNERDRAWFIXED);
	CListCtrl::PreSubclassWindow();      //�������� �ؼ����е��Ի�����Դʱ��formview�ȣ�û�����⣬��Ϊ��ʱ��Դ�Ѿ����ڣ�report����Ѿ������������������
	CHeaderCtrl *pHeader = GetHeaderCtrl();                                    //������ɶ�̬���������Ե��˴����ᷢ��pHeaderһֵΪNULL,ԭ���ǣ���ʱ���ڻ�û������
	m_Header.SubclassWindow(pHeader->GetSafeHwnd());//
}
//����취 ����Oncreat��������  ��������ŵ�Oncreat����������void CListCtrlCl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
void CListCtrlCl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO:  ������Ĵ����Ի���ָ����
	TCHAR lpBuffer[256];
	LV_ITEM lvi;
	lvi.mask = LVIF_TEXT | LVIF_PARAM ;
	lvi.iItem = lpDrawItemStruct->itemID ;
	lvi.iSubItem = 0;
	lvi.pszText = lpBuffer ;
	lvi.cchTextMax = sizeof(lpBuffer);
	VERIFY(GetItem(&lvi));
	LV_COLUMN lvc, lvcprev ;
	::ZeroMemory(&lvc, sizeof(lvc));
	::ZeroMemory(&lvcprev, sizeof(lvcprev));
	lvc.mask = LVCF_WIDTH | LVCF_FMT;
	lvcprev.mask = LVCF_WIDTH | LVCF_FMT;
	CDC* pDC;
	pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rtClient;
	GetClientRect(&rtClient);
	for ( int nCol=0; GetColumn(nCol, &lvc); nCol++)
	{
		if ( nCol > 0 )
		{
			// Get Previous Column Width in order to move the next display item
			GetColumn(nCol-1, &lvcprev) ;
			lpDrawItemStruct->rcItem.left += lvcprev.cx ;
			lpDrawItemStruct->rcItem.right += lpDrawItemStruct->rcItem.left;
		}
		CRect rcItem;
		if (!GetSubItemRect(lpDrawItemStruct->itemID,nCol,LVIR_LABEL,rcItem))
			continue;
		::ZeroMemory(&lvi, sizeof(lvi));
		lvi.iItem = lpDrawItemStruct->itemID;
		lvi.mask = LVIF_TEXT | LVIF_PARAM;
		lvi.iSubItem = nCol;
		lvi.pszText = lpBuffer;
		lvi.cchTextMax = sizeof(lpBuffer);
		VERIFY(GetItem(&lvi));
		CRect rcTemp;
		rcTemp = rcItem;
		if (nCol==0)
		{
			rcTemp.left -=2;
		}
		if ( lpDrawItemStruct->itemState & ODS_SELECTED )
		{
			pDC->FillSolidRect(&rcTemp, GetSysColor(COLOR_HIGHLIGHT)) ;
			pDC->SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT)) ;
		}
		else
		{
			COLORREF color;
			color = GetBkColor();
			pDC->FillSolidRect(rcTemp,color);
			if (FindColColor(nCol,color))
			{
				pDC->FillSolidRect(rcTemp,color);
			}
			if (FindItemColor(nCol,lpDrawItemStruct->itemID,color))
			{
				pDC->FillSolidRect(rcTemp,color);
			}
			//pDC->SetTextColor(m_color);
		}
		pDC->SelectObject(GetStockObject(DEFAULT_GUI_FONT));
		UINT   uFormat    = DT_CENTER ;
		if (m_Header.m_Format[nCol]=='0')
		{
			uFormat = DT_LEFT;
		}
		else if (m_Header.m_Format[nCol]=='1')
		{
			uFormat = DT_CENTER;
		}
		else if (m_Header.m_Format[nCol]=='2')
		{
			uFormat = DT_RIGHT;
		}
		TEXTMETRIC metric;
		pDC->GetTextMetrics(&metric);
		int ofst;
		ofst = rcItem.Height() - metric.tmHeight;
		rcItem.OffsetRect(0,ofst/2);
		pDC->SetTextColor(m_color);
		COLORREF color;
		if (FindColTextColor(nCol,color))
		{
			pDC->SetTextColor(color);
		}
		if (FindItemTextColor(nCol,lpDrawItemStruct->itemID,color))
		{
			pDC->SetTextColor(color);
		}
		CFont nFont ,* nOldFont;
		nFont.CreateFont(m_fontHeight,m_fontWith,0,0,0,FALSE,FALSE,0,0,0,0,0,0,_TEXT("����"));//��������
		nOldFont = pDC->SelectObject(&nFont);
		DrawText(lpDrawItemStruct->hDC, lpBuffer, (int)wcslen(lpBuffer),
			&rcItem, uFormat) ;//����Ϊunicode Ӧ��Ϊwcslen��lpBuffer)

		pDC->SelectStockObject(SYSTEM_FONT) ;
	}
}
void CListCtrlCl::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	if (m_nRowHeight>0)
	{
		lpMeasureItemStruct->itemHeight = m_nRowHeight;
	}
}
int CListCtrlCl::InsertColumn(int nCol, LPCTSTR lpszColumnHeading, int nFormat /* = LVCFMT_LEFT */, int nWidth /* = -1 */, int nSubItem /* = -1 */)
{
	m_Header.m_HChar.Add(lpszColumnHeading);
	if (nFormat==LVCFMT_LEFT)
	{
		m_Header.m_Format = m_Header.m_Format + _T("0");
	}
	else if (nFormat==LVCFMT_CENTER)
	{
		m_Header.m_Format = m_Header.m_Format + _T("1");
	}
	else if (nFormat==LVCFMT_RIGHT)
	{
		m_Header.m_Format = m_Header.m_Format + _T("2");
	}
	else
	{
		m_Header.m_Format = m_Header.m_Format + _T("1");
	}
	return CListCtrl::InsertColumn(nCol,lpszColumnHeading,nFormat,nWidth,nSubItem);
}
// Gradient - ����ϵ�������屳����,���ý�����Ϊ0
void CListCtrlCl::SetHeaderBKColor(int R, int G, int B, int Gradient) //���ñ�ͷ����ɫ
{
	m_Header.m_R = R;
	m_Header.m_G = G;
	m_Header.m_B = B;
	m_Header.m_Gradient = Gradient;
}
// ���ñ�ͷ�߶�
void CListCtrlCl::SetHeaderHeight(float Height) //���ñ�ͷ�߶�
{
	m_Header.m_Height = Height;
}
bool CListCtrlCl::FindColColor(int col,COLORREF &color) //��������ɫ
{
	int flag = 0;
	for (POSITION pos = m_ptrListCol.GetHeadPosition();pos!=NULL;)
	{
		stColor *pColor = (stColor*)m_ptrListCol.GetNext(pos);
		if (pColor->nCol==col)
		{
			flag = 1;
			color = pColor->rgb;
			break;
		}
	}
	if (1==flag)
	{
		return true;
	}
	return false;
}
bool CListCtrlCl::FindItemColor(int col,int row,COLORREF &color) //������ɫ
{
	int flag = 0;
	for (POSITION pos = m_ptrListItem.GetHeadPosition();pos!=NULL;)
	{
		stColor *pColor = (stColor*)m_ptrListItem.GetNext(pos);
		if (pColor->nCol==col&&pColor->nRow==row)
		{
			flag = 1;
			color = pColor->rgb;
			break;
		}
	}
	if (1==flag)
	{
		return true;
	}
	return false;
}
void CListCtrlCl::SetColColor(int col,COLORREF color) //��������ɫ
{
	stColor *pColor  = new stColor;
	pColor->nCol = col;
	pColor->rgb = color;
	m_ptrListCol.AddTail(pColor);
}
void CListCtrlCl::SetItemColor(int col,int row,COLORREF color) //���ø�����ɫ
{
	stColor *pColor  = new stColor;
	pColor->nCol = col;
	pColor->nRow = row;
	pColor->rgb = color;
	m_ptrListItem.AddTail(pColor);
}
void CListCtrlCl::SetRowHeight(int nHeight) // �����и�
{
	m_nRowHeight = nHeight;
	CRect rcWin;
	GetWindowRect(&rcWin);
	WINDOWPOS wp;
	wp.hwnd = m_hWnd;
	wp.cx = rcWin.Width();
	wp.cy = rcWin.Height();
	wp.flags = SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER;
	SendMessage(WM_WINDOWPOSCHANGED, 0, (LPARAM)&wp);
}
void CListCtrlCl::SetHeaderFontHW(int nHeight,int nWith) //����ͷ�������͸�
{
	m_Header.m_fontHeight = nHeight;
	m_Header.m_fontWith = nWith;
}
void CListCtrlCl::SetHeaderTextColor(COLORREF color) //����ͷ��������ɫ
{
	m_Header.m_color = color;
}
void CListCtrlCl::SetTextColor(COLORREF cr)  //����������ɫ
{
	m_color = cr;
}
void CListCtrlCl::SetFontHW(int nHeight,int nWith) //��������ߺͿ�
{
	m_fontHeight = nHeight;
	m_fontWith = nWith;
}
void CListCtrlCl::SetColTextColor(int col,COLORREF color)
{
	stColor *pColor = new stColor;
	pColor->nCol = col;
	pColor->rgb = color;
	m_colTextColor.AddTail(pColor);
}
bool CListCtrlCl::FindColTextColor(int col,COLORREF &color)
{
	int flag = 0;
	for (POSITION pos = m_colTextColor.GetHeadPosition();pos!=NULL;)
	{
		stColor *pColor = (stColor*)m_colTextColor.GetNext(pos);
		if (pColor->nCol==col)
		{
			flag = 1;
			color = pColor->rgb;
			break;
		}
	}
	if (1==flag)
	{
		return true;
	}
	return false;
}
bool CListCtrlCl::FindItemTextColor(int col,int row,COLORREF &color)
{
	int flag = 0;
	for (POSITION pos = m_ItemTextColor.GetHeadPosition();pos!=NULL;)
	{
		stColor *pColor = (stColor*)m_ItemTextColor.GetNext(pos);
		if (pColor->nCol==col&&pColor->nRow==row)
		{
			flag = 1;
			color = pColor->rgb;
			break;
		}
	}
	if (1==flag)
	{
		return true;
	}
	return false;
}
void CListCtrlCl::SetItemTextColor(int col,int row,COLORREF color)
{
	stColor *pColor = new stColor;
	pColor->nCol = col;
	pColor->nRow = row;
	pColor->rgb = color;
	m_ItemTextColor.AddTail(pColor);
}