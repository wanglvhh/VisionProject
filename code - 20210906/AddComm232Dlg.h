#pragma once
#include "afxcmn.h"

// CAddComm232Dlg 对话框

class CAddComm232Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddComm232Dlg)
public:
	CWinXPButtonST m_btnOk;
	CWinXPButtonST m_btnCancel ;
	CSkinComboBox  m_comboPort ;
	CSkinComboBox  m_comboBaudRate ;
	CSkinComboBox  m_comboParity ;
	CSkinComboBox  m_comboBitsize ;
	CSkinComboBox  m_comboStopBits ;
	COMM232NODE    m_comm232Node ;
private:
	void InitAllControl() ;
	void InitBtnControl() ;
	void InitComboControl() ;
	void UpdateAllControl() ;
public:
	CAddComm232Dlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAddComm232Dlg();

// 对话框数据
	enum { IDD = IDD_ADD_COMM232_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
