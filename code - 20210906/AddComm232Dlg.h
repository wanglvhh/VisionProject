#pragma once
#include "afxcmn.h"

// CAddComm232Dlg �Ի���

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
	CAddComm232Dlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAddComm232Dlg();

// �Ի�������
	enum { IDD = IDD_ADD_COMM232_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
