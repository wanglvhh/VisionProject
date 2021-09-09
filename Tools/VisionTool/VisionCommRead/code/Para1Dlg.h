#pragma once
#include "afxcmn.h"

// CPara1Dlg �Ի���

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
	CPara1Dlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPara1Dlg();

// �Ի�������
	enum { IDD = IDD_PARA1_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnEnChangeEditWaittime();
};
