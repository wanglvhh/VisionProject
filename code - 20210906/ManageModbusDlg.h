#pragma once
#include "afxcmn.h"
// CManageModbusDlg 对话框

class CManageModbusDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CManageModbusDlg)
public:
	CWinXPButtonST m_btnAdd;
	CWinXPButtonST m_btnEdit;
	CWinXPButtonST m_btnDel;
	CWinXPButtonST m_btnOk;
	CWinXPButtonST m_btnCancel;
	CWinXPButtonST m_btnReConnect;
	CSkinComboBox  m_comboModbusList;
	CWinXPButtonST m_btnRead1;
	CWinXPButtonST m_btnAdd1;
	CWinXPButtonST m_btnEdit1;
	CWinXPButtonST m_btnDel1;
	CWinXPButtonST m_btnWrite1;
	CWinXPButtonST m_btnRead2;
	CWinXPButtonST m_btnWrite2;
	CListCtrlCl    m_listModbus;
	CListCtrlCl    m_listRead;
	UINT           m_uPlcStartAddress;
	UINT           m_uReadNum;
	double         m_dbReadValue;
	CRichEditCtrl  m_ctlSysTipsDisplay1;

	CRITICAL_SECTION m_csModbus ;

	vector<short>  m_vecWrite ;

	enum LISTMODBUS
	{
		E_MODBUS_ID = 0,
		E_MODBUS_NAME,
		E_MODBUS_TYPE,
		E_MODBUS_VALUE,
	};

	enum LISTREAD
	{
		E_READ_ID = 0,
		E_READ_VALUE,
	};

private:
	void InitAllControl() ;
	void InitBtnControl() ;
	void InitListControl() ;
	void InitListControl2() ;
	void InitComboControl() ;
	void InitRichEdit() ;
	void SetSysTipsInfo(CString strInfo, COLORREF crColor) ;
public:
	void UpdataAllControl() ;
	void UpdataListControl() ;
	void UpdataListControl2() ;
	void UpdataComboControl() ;
public:
	CManageModbusDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CManageModbusDlg();

// 对话框数据
	enum { IDD = IDD_MANAGE_MODBUS_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnEdit();
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnBnClickedBtnReconnect();
	afx_msg void OnBnClickedOk();
	afx_msg void OnNMDblclkListModbus(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeEditPlcstartAddress();
	afx_msg void OnEnChangeEditNum();
	afx_msg void OnEnChangeEditReaddoublevalue();
	afx_msg void OnBnClickedBtnRead1();
	afx_msg void OnBnClickedBtnRead2();
	afx_msg void OnBnClickedBtnAdd1();
	afx_msg void OnBnClickedBtnEdit1();
	afx_msg void OnBnClickedBtnDel1();
	afx_msg void OnBnClickedBtnWrite1();
	afx_msg void OnBnClickedBtnWrite2();
};
