#pragma once
#include "afxcmn.h"

// CAddRtuMasterDlg 对话框

class CAddRtuMasterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddRtuMasterDlg)
public:
	CWinXPButtonST m_btnOk;
	CWinXPButtonST m_btnCancel;
	CSkinComboBox m_comboPort;
	CSkinComboBox m_comboBaudRate;
	CSkinComboBox m_comboParity;
	CSkinComboBox m_comboBitsize;
	CSkinComboBox m_comboStopBits;
	UINT          m_uSlaveID;

	RTUMASTERNODE m_rtuMasterNode ;

private:
	void InitAllControl() ;
	void InitBtnControl() ;
	void InitComboControl() ;
	void UpdateAllControl() ;
public:
	CAddRtuMasterDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAddRtuMasterDlg();

// 对话框数据
	enum { IDD = IDD_ADD_MODBUS_RTUMASTER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
