#pragma once
#include "resource.h"
#include "afxcmn.h"
#include "Para1Dlg.h"
// CMainDlg 对话框

class CMainDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMainDlg)
public:
	CSkinComboBox            m_comboCameraList;
	CMyStatic                m_ctlImageView;
	CTabCtrl                 m_tabPara;
	CWinXPButtonST           m_btnRun;
	CWinXPButtonST           m_btnRunCycle;
	CWinXPButtonST           m_btnLoad;
	CWinXPButtonST           m_btnSave;
	CWinXPButtonST           m_btnClose;
	CNewLabel                m_labelRow;
	CNewLabel                m_labelCol;
	CNewLabel                m_labelGray;
	CNewLabel                m_labelInfo;

	CCameraNode*             m_pCameraNode ;
	CString                  m_strCameraInfo ;
	CString                  m_strSavePath ;

	HTuple                   m_lWindowID ;
	HObject                  m_hImage ;

	bool                     m_bDraw;
	HTuple                   m_hRowB ;
	HTuple                   m_hColB ;
	HTuple                   m_hRowE ;
	HTuple                   m_hColE;
	BOOL                     m_bScale ;
	BOOL                     m_bMoveImg ;
	bool                     m_bMoveState;
	double                   m_dbRatioWh ;

	CPara1Dlg                m_para1Dlg ;
public:
	static void CallDispImage(void *pOwner,HObject *hImage) ;
	void BtnRun() ;
	void BtnRunCycle() ;
	void BtnLoad() ;
	void BtnSave() ;
	void BtnClose() ;
private:
	void InitAllControl() ;
	void InitBtnControl() ;
	void InitComboControl() ;
	void InitViewControl() ;
	void InitLabelControl() ;
	void InitTabControl() ;
public:
	CMainDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMainDlg();

// 对话框数据
	enum { IDD = IDD_MAIN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonClicked(UINT uBtnId) ;
};
