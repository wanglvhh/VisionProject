#pragma once
#include "..\inc\control\newlabel.h"
// CGobalViarentDlg 对话框

class CGobalViarentDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGobalViarentDlg)
public:
	CWinXPButtonST m_btnOk;
	CWinXPButtonST m_btnCancel;
	CString m_strValueName;
	CSkinComboBox m_comboValueType;
	CNewLabel m_labelInfo;
	CString m_strValue;
	CString m_strValueTipInfo;
	int     m_nValueType ;

public:
	void UpdataAllControl() ;
private:
	void InitAllControl() ;
	void InitBtnControl() ;
	void InitComboControl() ;
	void InitLabelControl() ;

public:
	CGobalViarentDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGobalViarentDlg();

// 对话框数据
	enum { IDD = IDD_GOBALVIARENT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnEditChange(UINT uEdit) ;
	afx_msg void OnCbnSelendokComboViarenttype();
};
