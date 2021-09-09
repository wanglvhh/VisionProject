#pragma once
#include "HeaderCtrlCl.h"
// CListCtrlCl
class CListCtrlCl : public CListCtrl
{
	DECLARE_DYNAMIC(CListCtrlCl)
public:
	CListCtrlCl();
	virtual ~CListCtrlCl();
protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
protected:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
protected:
	void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
protected:
	CHeaderCtrlCl m_Header; //��ͷ
	int m_nRowHeight;// �и�
	CPtrList m_ptrListCol;  //��������ɫ
	CPtrList m_ptrListItem; //����Item��ɫ��
	CPtrList m_colTextColor; //������������ɫ
	CPtrList m_ItemTextColor; //���浥Ԫ��������ɫ
	COLORREF m_color;
	int m_fontHeight;   // ����߶�
	int m_fontWith;         // ������
public:
	// ���ñ�ͷ�߶�
	void SetHeaderHeight(float Height);
	// Gradient - ����ϵ�������屳����,���ý�����Ϊ0
	void SetHeaderBKColor(int R, int G, int B, int Gradient);
	int InsertColumn(int nCol, LPCTSTR lpszColumnHeading,
		int nFormat = LVCFMT_LEFT, int nWidth = -1, int nSubItem = -1);
	void SetHeaderFontHW(int nHeight,int nWith); //���ñ�ͷ�����С
	void SetHeaderTextColor(COLORREF color);
	void SetRowHeight(int nHeight); //�����и�
	bool FindColColor(int col ,COLORREF &color); //��������ɫ
	bool FindItemColor(int col,int row,COLORREF &color);
	bool FindColTextColor(int col,COLORREF &color); //������������ɫ
	bool FindItemTextColor(int col,int row,COLORREF &color);
	void SetColColor(int col,COLORREF color);  //��������ɫ
	void SetItemColor(int col,int row,COLORREF color); //����Item��ɫ
	void SetColTextColor(int col,COLORREF color);   //�������ı���ɫ
	void SetItemTextColor(int col,int row,COLORREF color);
	void SetTextColor(COLORREF cr);
	void SetFontHW(int nHeight,int nWith);  //��������ĸߺͿ�
};