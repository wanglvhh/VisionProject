#pragma once
#include "afxcmn.h"

// CPara1Dlg 对话框

class CPara1Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPara1Dlg)
public:
	double m_dbWaitTime;
	CRichEditCtrl m_ctlSysTipsDisplay1;
protected:
	CBrush              m_brush;

public:
	void UpdateAllControl() ;
	void SetSysTipsInfo(CString strInfo, COLORREF crColor) ;
private:
	void InitAllControl() ;
	void InitRichEdit() ;
public:
	CPara1Dlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPara1Dlg();

// 对话框数据
	enum { IDD = IDD_PARA1_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnEnChangeEditWaittime();
};
