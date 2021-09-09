// VisionProjectDlg.h : 头文件
//
#include "HardWareToolPanelDlg.h"
#include "CaliToolPanelDlg.h"
#include "Vision2DPanelDlg.h"
#include "Vision2DLogicPanelDlg.h"
#include "VisionSystemPanelDlg.h"
#include "NewDlg.h"
#include "WorkFlowDlg.h"
#include "ManageCameraDlg.h"
#include "ImageViewDlg.h"
#include "ManageProjectDlg.h"
#include "SplashWindowDlg.h"
#include "ViewConnectDlg.h"
#include "ManageViarentDlg.h"
#include "ManageCommunicationDlg.h"
#include "ManageModbusDlg.h"

#pragma once

#define SPLASH_START(pDlg,strTip){pDlg = new CSplashWindowDlg; pDlg->Create ( IDD_SPLASH_DIALOG, this ); pDlg->CenterWindow(); pDlg->ShowTip ( strTip); pDlg->ShowWindow ( SW_SHOW ); Delay(1000) ;}
#define SPLASH_STEP(pDlg,strTip){pDlg->ShowTip ( strTip);Delay(500) ;}
#define SPLASH_END(pDlg,strTip){pDlg->ShowTip ( strTip);Delay(1000) ; pDlg->ShowWindow ( SW_HIDE ); delete pDlg; pDlg = NULL;}
// CVisionProjectDlg 对话框
class CVisionProjectDlg : public CDialogEx
{
	DECLARE_EASYSIZE
public:
	enum TOOLPANEL
	{
		E_PANEL_HARDWARE = 0 ,
		E_PANEL_CALI,
		E_PANEL_2DVISION,
		E_PANEL_2DVISIONLOGIC,
		E_PANEL_VISIONSYSTEM,
	};
	CWinXPButtonST            m_btnCycleRun;
	CWinXPButtonST            m_btnStop;
	CWinXPButtonST            m_btnCamera;
	CWinXPButtonST            m_btnLed;
	CWinXPButtonST            m_btnMessage;
	CWinXPButtonST            m_btnMobus;
	CWinXPButtonST            m_btnNewView;
	CWinXPButtonST            m_btnViewConnect;
	CWinXPButtonST            m_btnDelView;
	CWinXPButtonST            m_btnNewFlow;
	CWinXPButtonST            m_btnDelFlow;
	CWinXPButtonST            m_btnTstFlow;
	CWinXPButtonST            m_btnManageUser;
	CWinXPButtonST            m_btnLoginUser;
	CWinXPButtonST            m_btnLicense;
	CWinXPButtonST            m_btnUi;
	CWinXPButtonST            m_btnSystemSet;
	CWinXPButtonST            m_btnLuaGobalVar;
	CWinXPButtonST            m_btnProject;
	CTabCtrl                  m_tabView ;
	CTabCtrl                  m_tabWorkFlowDlg ;

	//工程数据
	CProjectData              m_projectData ;
	//添加工具标志 add true or false
	bool                      m_bWorkFlowAddTool ;

	//开机启动对话框
	CSplashWindowDlg*         m_pSplashWindowDlg ;
	CPropertySheet*           m_pSheetPanel;
	CHardWareToolPanelDlg     m_HardWareToolPanelDlg ;
	CCaliToolPanelDlg         m_CaliToolPanelDlg ;
	CVision2DPanelDlg         m_Vision2DPanelDlg ;
	CVision2DLogicPanelDlg    m_Vision2DLogicPanelDlg ;
	CVisionSystemPanelDlg     m_VisionSystemPanelDlg ;

private:
	void InitAllControl() ;
	void InitBtnControl() ;
	void InitToolPanelControl() ;
public:
	void LoadProjectData() ;
	void SetActiveWorkFlowDlg(int nWorkFlowDlgID) ;
	void SetActiveImageViewDlg(int nImageViewDlgID) ;
	void UpdateAllControl() ;
	void UpdateImageViewTabControl() ;
	void UpdateWorkFlowTabControl() ;
	void HideAllImageViewDlg() ;
	void BtnNewflow() ;
	void BtnManageCamera() ;
	void BtnNewView() ;
	void BtnViewConnect() ;
	void BtnDelView() ;
	void BtnManageProject() ;
	void BtnLuaGobalViarent() ;
	void BtnManageMessage() ;
	void BtnManageModbus() ;
	void Systst() ;
	void Systst2() ;
// 构造
public:
	CVisionProjectDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_VISIONPROJECT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnTcnSelchangeTabWorkflowdlg(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnButtonClicked(UINT uBtnId) ;
	afx_msg void OnClose();
};
