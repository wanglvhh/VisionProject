#include "stdafx.h"
#include "HeaderCtrlCl.h"
// CHeaderCtrlCl
IMPLEMENT_DYNAMIC(CHeaderCtrlCl, CHeaderCtrl)
	CHeaderCtrlCl::CHeaderCtrlCl()
	: m_R(171)
	, m_G(199)
	, m_B(235)
	, m_Gradient(8)
{
	m_Format = "";
	m_Height = 1;
	m_fontHeight = 15;
	m_fontWith = 0;
	m_color = RGB(0,0,0);
}
CHeaderCtrlCl::~CHeaderCtrlCl()
{
}
BEGIN_MESSAGE_MAP(CHeaderCtrlCl, CHeaderCtrl)
	ON_WM_PAINT()
	ON_MESSAGE(HDM_LAYOUT, OnLayout)
END_MESSAGE_MAP()
// CHeaderCtrlCl ��Ϣ�������
void CHeaderCtrlCl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CHeaderCtrl::OnPaint()
	int nItem;
	nItem = GetItemCount();//�õ��м�����Ԫ
	for(int i = 0; i<nItem;i ++)
	{
		CRect tRect;
		GetItemRect(i,&tRect);//�õ�Item�ĳߴ�
		int R = m_R,G = m_G,B = m_B;
		CRect nRect(tRect);//�����ߴ絽�µ�������
		nRect.left++;//�����ָ��ߵĵط�
		//�������屳��
		for(int j = tRect.top;j<=tRect.bottom;j++)
		{
			nRect.bottom = nRect.top+1;
			CBrush _brush;
			_brush.CreateSolidBrush(RGB(R, G, B));//������ˢ
			dc.FillRect(&nRect,&_brush); //��䱳��
			_brush.DeleteObject(); //�ͷŻ�ˢ
			R-=m_Gradient;G-=m_Gradient;B-=m_Gradient;
			if (R<0)R = 0;
			if (G<0)G = 0;
			if (B<0)B= 0;
			nRect.top = nRect.bottom;
		}
		dc.SetBkMode(TRANSPARENT);
		CFont nFont ,* nOldFont;
		//dc.SetTextColor(RGB(250,50,50));
		dc.SetTextColor(m_color);
		nFont.CreateFont(m_fontHeight,m_fontWith,0,0,0,FALSE,FALSE,0,0,0,0,0,0,_TEXT("����"));//��������
		nOldFont = dc.SelectObject(&nFont);
		UINT nFormat = 1;
		if (m_Format[i]=='0')
		{
			nFormat = DT_LEFT;
			tRect.left+=3;
		}
		else if (m_Format[i]=='1')
		{
			nFormat = DT_CENTER;
		}
		else if (m_Format[i]=='2')
		{
			nFormat = DT_RIGHT;
			tRect.right-=3;
		}
		//��������ʾ��һ���ʺϵĸ߶�λ��
		TEXTMETRIC metric;
		dc.GetTextMetrics(&metric);
		int ofst = 0;
		ofst = tRect.Height() - metric.tmHeight;
		tRect.OffsetRect(0,ofst/2);
		dc.DrawText(m_HChar[i],&tRect,nFormat);
		dc.SelectObject(nOldFont);
		nFont.DeleteObject(); //�ͷ�����
	}
	//��ͷ��ʣ�ಿ��(û�б�����ǲ���)
	CRect rtRect;
	CRect clientRect;
	GetItemRect(nItem - 1,rtRect);
	GetClientRect(clientRect); //��ǰ(CHeaderCtrl)�ؼ��Ĵ�С
	rtRect.left = rtRect.right+1;
	rtRect.right = clientRect.right;
	int R = m_R,G = m_G,B = m_B;
	CRect nRect(rtRect);
	//�������屳��
	for(int j = rtRect.top;j<=rtRect.bottom;j++)
	{
		nRect.bottom = nRect.top+1;
		CBrush _brush;
		_brush.CreateSolidBrush(RGB(R,G,B));//������ˢ
		dc.FillRect(&nRect,&_brush); //��䱳��
		_brush.DeleteObject(); //�ͷŻ�ˢ
		R-=m_Gradient;G-=m_Gradient;B-=m_Gradient;
		if (R<0)R = 0;
		if (G<0)G = 0;
		if (B<0)B= 0;
		nRect.top = nRect.bottom;
	}
}
LRESULT CHeaderCtrlCl::OnLayout( WPARAM wParam, LPARAM lParam )
{
	LRESULT lResult = CHeaderCtrl::DefWindowProc(HDM_LAYOUT, 0, lParam);
	HD_LAYOUT &hdl = *( HD_LAYOUT * ) lParam;
	RECT *prc = hdl.prc;
	WINDOWPOS *pwpos = hdl.pwpos;
	//��ͷ�߶�Ϊԭ��1.5�������Ҫ��̬�޸ı�ͷ�߶ȵĻ�����1.5���һ��ȫ�ֱ���
	int nHeight = (int)(pwpos->cy * m_Height);
	pwpos->cy = nHeight;
	prc->top = nHeight;
	return lResult;
} 