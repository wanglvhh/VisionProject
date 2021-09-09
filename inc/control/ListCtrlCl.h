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
	CHeaderCtrlCl m_Header; //表头
	int m_nRowHeight;// 行高
	CPtrList m_ptrListCol;  //保存列颜色
	CPtrList m_ptrListItem; //保存Item颜色表
	CPtrList m_colTextColor; //保存列字体颜色
	CPtrList m_ItemTextColor; //保存单元格字体颜色
	COLORREF m_color;
	int m_fontHeight;   // 字体高度
	int m_fontWith;         // 字体宽度
public:
	// 设置表头高度
	void SetHeaderHeight(float Height);
	// Gradient - 渐变系数，立体背景用,不用渐变设为0
	void SetHeaderBKColor(int R, int G, int B, int Gradient);
	int InsertColumn(int nCol, LPCTSTR lpszColumnHeading,
		int nFormat = LVCFMT_LEFT, int nWidth = -1, int nSubItem = -1);
	void SetHeaderFontHW(int nHeight,int nWith); //设置表头字体大小
	void SetHeaderTextColor(COLORREF color);
	void SetRowHeight(int nHeight); //设置行高
	bool FindColColor(int col ,COLORREF &color); //查找列颜色
	bool FindItemColor(int col,int row,COLORREF &color);
	bool FindColTextColor(int col,COLORREF &color); //查找列字体颜色
	bool FindItemTextColor(int col,int row,COLORREF &color);
	void SetColColor(int col,COLORREF color);  //设置列颜色
	void SetItemColor(int col,int row,COLORREF color); //设置Item颜色
	void SetColTextColor(int col,COLORREF color);   //设置列文本颜色
	void SetItemTextColor(int col,int row,COLORREF color);
	void SetTextColor(COLORREF cr);
	void SetFontHW(int nHeight,int nWith);  //设置字体的高和宽
};