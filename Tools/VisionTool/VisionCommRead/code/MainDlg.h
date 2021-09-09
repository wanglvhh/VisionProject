#pragma once
#include "resource.h"
#include "afxcmn.h"
#include "Para1Dlg.h"
#include "ManageCommunication.h"
// CMainDlg �Ի���

class CMainDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMainDlg)
public:
	CTabCtrl             m_tabPara;
	CWinXPButtonST       m_btnRun;
	CWinXPButtonST       m_btnRunCycle;
	CWinXPButtonST       m_btnLoad;
	CWinXPButtonST       m_btnSave;
	CWinXPButtonST       m_btnClose;
	CLabelEx             m_labelInfo;

	CCommunicationNode*  m_pCommunicationNode ;
	CString              m_strCommInfo ;
	CString              m_strSavePath ;
	CPara1Dlg            m_para1Dlg ;
private:
	//�ر��߳��¼�
	HANDLE               m_eCommCloseThread ;
	//����߳��¼�
	HANDLE               m_eCommContinueThread ;
	//�߳�ID
	unsigned int         m_dwCommId ;
	//�ٽ�������
	CRITICAL_SECTION     m_csComm ;
public:
	void BtnRun() ;
	void BtnRunCycle() ;
	void BtnLoad() ;
	void BtnSave() ;
	void BtnClose() ;
	//ͨ���߳�
	static unsigned int WINAPI CommunicationThread(LPVOID lparam) ;
private:
	void InitAllControl() ;
	void InitBtnControl() ;
	void InitLabelControl() ;
	void InitTabControl() ;
	void UpdateAllControl() ;
public:
	CMainDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMainDlg();

// �Ի�������
	enum { IDD = IDD_MAIN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonClicked(UINT uBtnId) ;
};
