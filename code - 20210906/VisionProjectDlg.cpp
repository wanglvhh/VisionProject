// VisionProjectDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "VisionProject.h"
#include "VisionProjectDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CVisionProjectDlg 对话框

CVisionProjectDlg::CVisionProjectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CVisionProjectDlg::IDD, pParent)
	,m_bWorkFlowAddTool(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pSheetPanel = NULL;
}

void CVisionProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_CYCLERUN, m_btnCycleRun);
	DDX_Control(pDX, IDC_BTN_STOP, m_btnStop);
	DDX_Control(pDX, IDC_BTN_CAMERA, m_btnCamera);
	DDX_Control(pDX, IDC_BTN_LED, m_btnLed);
	DDX_Control(pDX, IDC_BTN_MESSAGE, m_btnMessage);
	DDX_Control(pDX, IDC_BTN_MOBUS, m_btnMobus);
	DDX_Control(pDX, IDC_BTN_NEWVIEW, m_btnNewView);
	DDX_Control(pDX, IDC_BTN_VIEWCONNECT, m_btnViewConnect);
	DDX_Control(pDX, IDC_BTN_DELVIEW, m_btnDelView);
	DDX_Control(pDX, IDC_BTN_NEWFLOW, m_btnNewFlow);
	DDX_Control(pDX, IDC_BTN_DELFLOW, m_btnDelFlow);
	DDX_Control(pDX, IDC_BTN_TSTFLOW, m_btnTstFlow);
	DDX_Control(pDX, IDC_BTN_MANAGEUSER, m_btnManageUser);
	DDX_Control(pDX, IDC_BTN_LOGINUSER, m_btnLoginUser);
	DDX_Control(pDX, IDC_BTN_LICENSE, m_btnLicense);
	DDX_Control(pDX, IDC_BTN_SYSTEMSET, m_btnSystemSet);
	DDX_Control(pDX, IDC_BTN_UI, m_btnUi);
	DDX_Control(pDX, IDC_BTN_LUAGOBALVIARENT, m_btnLuaGobalVar);
	DDX_Control(pDX, IDC_BTN_PROJECT, m_btnProject);
	DDX_Control(pDX, IDC_TAB_VIEW, m_tabView);
	DDX_Control(pDX, IDC_TAB_WORKFLOWDLG, m_tabWorkFlowDlg);
}

BEGIN_MESSAGE_MAP(CVisionProjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_WORKFLOWDLG, &CVisionProjectDlg::OnTcnSelchangeTabWorkflowdlg)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_CYCLERUN, IDC_BTN_PROJECT, OnButtonClicked)
	ON_WM_SIZING()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

// CVisionProjectDlg 消息处理程序
BEGIN_EASYSIZE_MAP(CVisionProjectDlg)

	/*
	left、top、right、bottom分别指的是该控件左、上、右、下方的控件的ID，也可以为以下特殊值：
	ES_BORDER：保持与边框距离不变
	ES_KEEPSIZE：保持大小不变
	所放位置：
	left -- 表示和right指定的控件右对齐
	right -- 表示和left指定的控件左对齐
	top -- 表示和bottom指定的控件上对齐
	bottom -- 表示和top指定的控件下对齐
	options可指定为0，也可指定为以下值：
	ES_HCENTER：保持宽度不变，水平位置在left和right指定的控件正中间
	ES_VCENTER：保持高度不变，垂直位置在left和right指定的控件正中间
	*/
	/*
	EASYSIZE(IDOK,ES_BORDER,ES_BORDER,ES_BORDER,ES_BORDER,0)
	表示缩放后，值为IDOK的控件，距离边界上下左右位置保持不变，水平和垂直方向尺寸拉伸；

	EASYSIZE(IDOK,ES_BORDER,ES_BORDER,ES_BORDER,ES_BORDER,ES_HCENTER)
	表示缩放后，值为IDOK的控件，距离边界上下位置保持不变，垂直方向尺寸拉伸，水平居中；

	EASYSIZE(IDOK,ES_BORDER,ES_BORDER,ES_BORDER,ES_BORDER,ES_HCENTER| ES_HCENTER)
	表示缩放后，值为IDOK的控件，在对话框内垂直居中，水平居中；

	EASYSIZE(IDOK,ES_BORDER,ES_KEEPSIZE,ES_KEEPSIZE,ES_BORDER,0)
	表示缩放后，值为IDOK的控件，距离边界左、下方位置保持不变，同时保持控件尺寸；

	EASYSIZE(IDOK,ES_BORDER,ES_KEEPSIZE, ES_BORDER,ES_BORDER,0)
	表示缩放后，值为IDOK的控件，距离边界左、右、下方位置保持不变，水平方向尺寸拉伸，垂直方向尺寸不变；

	EASYSIZE(IDOK,ES_BORDER,ES_BORDER,IDCANCEL,ES_BORDER,0)
	表示缩放后，值为IDOK的控件，距离边界上下左位置保持不变，距离ID值为IDCANCEL的右方位置距离保持不变，水平和垂直方向尺寸拉伸；
	（当使用指定控件作为定位参数时候，确保指定控件的EASYSIZE在该宏前面）
	*/
	EASYSIZE(IDC_STATIC_MENU,ES_BORDER,ES_BORDER,ES_BORDER,IDC_TAB_VIEW,0)
	EASYSIZE(IDC_BTN_CYCLERUN,ES_BORDER,ES_KEEPSIZE,ES_KEEPSIZE,IDC_STATIC_MENU,0)
	EASYSIZE(IDC_BTN_STOP,IDC_BTN_CYCLERUN,ES_KEEPSIZE,ES_KEEPSIZE,IDC_STATIC_MENU,0)
	EASYSIZE(IDC_BTN_PROJECT,IDC_BTN_STOP,ES_KEEPSIZE,ES_KEEPSIZE,IDC_STATIC_MENU,0)
	EASYSIZE(IDC_BTN_CAMERA,IDC_BTN_PROJECT,ES_KEEPSIZE,ES_KEEPSIZE,IDC_STATIC_MENU,0)
	EASYSIZE(IDC_BTN_LED,IDC_BTN_CAMERA,ES_KEEPSIZE,ES_KEEPSIZE,IDC_STATIC_MENU,0)
	EASYSIZE(IDC_BTN_MESSAGE,IDC_BTN_LED,ES_KEEPSIZE,ES_KEEPSIZE,IDC_STATIC_MENU,0)
	EASYSIZE(IDC_BTN_NEWVIEW,IDC_BTN_MESSAGE,ES_KEEPSIZE,ES_KEEPSIZE,IDC_STATIC_MENU,0)
	EASYSIZE(IDC_BTN_VIEWCONNECT,IDC_BTN_NEWVIEW,ES_KEEPSIZE,ES_KEEPSIZE,IDC_STATIC_MENU,0)
	EASYSIZE(IDC_BTN_DELVIEW,IDC_BTN_VIEWCONNECT,ES_KEEPSIZE,ES_KEEPSIZE,IDC_STATIC_MENU,0)
	EASYSIZE(IDC_BTN_LUAGOBALVIARENT,IDC_BTN_DELVIEW,ES_KEEPSIZE,ES_KEEPSIZE,IDC_STATIC_MENU,0)
	EASYSIZE(IDC_BTN_MANAGEUSER,IDC_BTN_DELVIEW,ES_KEEPSIZE,ES_KEEPSIZE,IDC_STATIC_MENU,0)
	EASYSIZE(IDC_BTN_LOGINUSER,IDC_BTN_MANAGEUSER,ES_KEEPSIZE,ES_KEEPSIZE,IDC_STATIC_MENU,0)
	EASYSIZE(IDC_BTN_LICENSE,IDC_BTN_LOGINUSER,ES_KEEPSIZE,ES_KEEPSIZE,IDC_STATIC_MENU,0)
	EASYSIZE(IDC_BTN_SYSTEMSET,IDC_BTN_LICENSE,ES_KEEPSIZE,ES_KEEPSIZE,IDC_STATIC_MENU,0)
	EASYSIZE(IDC_TAB_VIEW,ES_BORDER,IDC_STATIC_MENU,ES_BORDER,ES_BORDER,0)
	EASYSIZE(IDC_LIST_INFO,ES_BORDER,IDC_TAB_VIEW,ES_BORDER,ES_BORDER,0)
	EASYSIZE(IDC_TAB_FLOW,IDC_TAB_VIEW,ES_BORDER,ES_BORDER,ES_BORDER,0)
	EASYSIZE(IDC_STATIC_FLOW,IDC_TAB_VIEW,ES_BORDER,ES_BORDER,IDC_TAB_FLOW,0)
	EASYSIZE(IDC_STATIC_TOOL,IDC_TAB_FLOW,ES_BORDER,ES_BORDER,ES_BORDER,0)
	EASYSIZE(IDC_BTN_NEWFLOW,IDC_STATIC_FLOW,IDC_STATIC_FLOW,IDC_STATIC_FLOW,IDC_STATIC_FLOW,0)
	EASYSIZE(IDC_BTN_DELFLOW,IDC_STATIC_FLOW,IDC_STATIC_FLOW,IDC_STATIC_FLOW,IDC_STATIC_FLOW,0)
	EASYSIZE(IDC_BTN_TSTFLOW,IDC_STATIC_FLOW,IDC_STATIC_FLOW,IDC_STATIC_FLOW,IDC_STATIC_FLOW,0)
END_EASYSIZE_MAP

BOOL CVisionProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
/*
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
*/
	// TODO: 在此添加额外的初始化代码
	SPLASH_START(m_pSplashWindowDlg,_T("开始初始化系统")) ;

	INIT_EASYSIZE;
	//窗体最大化
	//ShowWindow(SW_MAXIMIZE);
	//初始化控件
	SPLASH_STEP(m_pSplashWindowDlg,_T("初始化控件")) ;
	InitAllControl() ;
	//加载数据
	SPLASH_STEP(m_pSplashWindowDlg,_T("加载数据")) ;
	LoadProjectData() ;
	//更新控件
	SPLASH_STEP(m_pSplashWindowDlg,_T("更新控件")) ;
	UpdateAllControl() ;
	//注册脚本
	SPLASH_STEP(m_pSplashWindowDlg,_T("注册脚本")) ;
	g_VisionGlobal.InitScript() ;

	SPLASH_END(m_pSplashWindowDlg,_T("结束初始化系统")) ;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CVisionProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CVisionProjectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CVisionProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CVisionProjectDlg::InitAllControl()
{
	try
	{
		//初始化button控件
		InitBtnControl()  ;

		//初始化工具页控件
		InitToolPanelControl() ;
	}
	catch (...)
	{
	}
}

void CVisionProjectDlg::LoadProjectData()
{
	try
	{
		SPLASH_STEP(m_pSplashWindowDlg,_T("加载设备数据")) ;
		m_projectData.LoadDeviceData() ;

		SPLASH_STEP(m_pSplashWindowDlg,_T("加载工程数据")) ;
		m_projectData.LoadProjectData() ;
	}
	catch (...)
	{
	}
}

void CVisionProjectDlg::InitBtnControl()
{
	try
	{
		m_btnCycleRun.SetIcon(IDI_ICON_CYCLERUN) ;
		m_btnCycleRun.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnCycleRun.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnCycleRun.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnCycleRun.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnCycleRun.SetRounded(TRUE) ;

		m_btnStop.SetIcon(IDI_ICON_STOPRUN) ;
		m_btnStop.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnStop.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnStop.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnStop.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnStop.SetRounded(TRUE) ;

		m_btnProject.SetIcon(IDI_ICON_PROJECT) ;
		m_btnProject.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnProject.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnProject.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnProject.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnProject.SetRounded(TRUE) ;

		m_btnCamera.SetIcon(IDI_ICON_CAMERA) ;
		m_btnCamera.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnCamera.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnCamera.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnCamera.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnCamera.SetRounded(TRUE) ;

		m_btnLed.SetIcon(IDI_ICON_LED) ;
		m_btnLed.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnLed.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnLed.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnLed.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnLed.SetRounded(TRUE) ;

		m_btnMessage.SetIcon(IDI_ICON_MESSAGE) ;
		m_btnMessage.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnMessage.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnMessage.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnMessage.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnMessage.SetRounded(TRUE) ;

		m_btnMobus.SetIcon(IDI_ICON_MODBUS) ;
		m_btnMobus.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnMobus.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnMobus.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnMobus.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnMobus.SetRounded(TRUE) ;

		m_btnNewView.SetIcon(IDI_ICON_NEWVIEW) ;
		m_btnNewView.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnNewView.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnNewView.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnNewView.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnNewView.SetRounded(TRUE) ;

		m_btnViewConnect.SetIcon(IDI_ICON_VIEWCONNECT) ;
		m_btnViewConnect.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnViewConnect.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnViewConnect.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnViewConnect.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnViewConnect.SetRounded(TRUE) ;

		m_btnDelView.SetIcon(IDI_ICON_DELVIEW) ;
		m_btnDelView.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnDelView.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnDelView.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnDelView.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnDelView.SetRounded(TRUE) ;

		m_btnLuaGobalVar.SetIcon(IDI_ICON_LUAGOBALVARIENT) ;
		m_btnLuaGobalVar.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnLuaGobalVar.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnLuaGobalVar.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnLuaGobalVar.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnLuaGobalVar.SetRounded(TRUE) ;

		m_btnNewFlow.SetIcon(IDI_ICON_NEWFLOW) ;
		m_btnNewFlow.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnNewFlow.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnNewFlow.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnNewFlow.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnNewFlow.SetRounded(TRUE) ;

		m_btnDelFlow.SetIcon(IDI_ICON_DELFLOW) ;
		m_btnDelFlow.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnDelFlow.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnDelFlow.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnDelFlow.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnDelFlow.SetRounded(TRUE) ;

		m_btnTstFlow.SetIcon(IDI_ICON_TSTFLOW) ;
		m_btnTstFlow.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnTstFlow.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnTstFlow.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnTstFlow.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnTstFlow.SetRounded(TRUE) ;

		m_btnManageUser.SetIcon(IDI_ICON_MANAGEUSER) ;
		m_btnManageUser.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnManageUser.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnManageUser.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnManageUser.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnManageUser.SetRounded(TRUE) ;

		m_btnLoginUser.SetIcon(IDI_ICON_LOGINUSER) ;
		m_btnLoginUser.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnLoginUser.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnLoginUser.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnLoginUser.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnLoginUser.SetRounded(TRUE) ;

		m_btnLicense.SetIcon(IDI_ICON_LICENSE) ;
		m_btnLicense.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnLicense.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnLicense.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnLicense.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnLicense.SetRounded(TRUE) ;

		m_btnSystemSet.SetIcon(IDI_ICON_SYSTEMSET) ;
		m_btnSystemSet.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnSystemSet.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnSystemSet.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnSystemSet.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnSystemSet.SetRounded(TRUE) ;

		m_btnUi.SetIcon(IDI_ICON_UI) ;
		m_btnUi.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnUi.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnUi.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnUi.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnUi.SetRounded(TRUE) ;
	}
	catch (...)
	{
	}
}

void CVisionProjectDlg::InitToolPanelControl()
{
	try
	{
		m_pSheetPanel = new CPropertySheet() ;

		m_HardWareToolPanelDlg.m_psp.dwFlags |= PSP_USETITLE ;
		m_HardWareToolPanelDlg.m_psp.pszTitle = _T("视觉硬件") ;
		m_pSheetPanel->AddPage(&m_HardWareToolPanelDlg) ;

		m_CaliToolPanelDlg.m_psp.dwFlags |= PSP_USETITLE ;
		m_CaliToolPanelDlg.m_psp.pszTitle = _T("视觉标定") ;
		m_pSheetPanel->AddPage(&m_CaliToolPanelDlg) ;

		m_Vision2DPanelDlg.m_psp.dwFlags |= PSP_USETITLE ;
		m_Vision2DPanelDlg.m_psp.pszTitle = _T("2D视觉") ;
		m_pSheetPanel->AddPage(&m_Vision2DPanelDlg) ;

		m_Vision2DLogicPanelDlg.m_psp.dwFlags |= PSP_USETITLE ;
		m_Vision2DLogicPanelDlg.m_psp.pszTitle = _T("2D视觉逻辑") ;
		m_pSheetPanel->AddPage(&m_Vision2DLogicPanelDlg) ;

		m_VisionSystemPanelDlg.m_psp.dwFlags |= PSP_USETITLE ;
		m_VisionSystemPanelDlg.m_psp.pszTitle = _T("系统") ;
		m_pSheetPanel->AddPage(&m_VisionSystemPanelDlg) ;

		m_pSheetPanel->Create(this, WS_CHILD | WS_VISIBLE/*|WS_TABSTOP*/, WS_EX_CONTROLPARENT);
		m_pSheetPanel->SetActivePage(0);
		m_pSheetPanel->ShowWindow(SW_SHOW);

		RECT rc;
		GetDlgItem(IDC_STATIC_TOOL)->GetWindowRect(&rc);
		ScreenToClient(&rc) ;
		int width = rc.right - rc.left;
		int height = rc.bottom - rc.top;

		CRect rect ;
		GetDlgItem(IDC_STATIC_TOOL)->GetClientRect(&rect);
		m_pSheetPanel->GetTabControl()->MoveWindow(&rect);
		m_pSheetPanel->MoveWindow(rc.left,rc.top,  width, height) ;
		m_HardWareToolPanelDlg.MoveWindow(rect.left,rect.top+20,  width, height) ;
	}
	catch (...)
	{
	}
}

void CVisionProjectDlg::UpdateAllControl()
{
	try
	{
		UpdateImageViewTabControl()  ;

		UpdateWorkFlowTabControl() ;
	}
	catch (...)
	{
	}
}

void CVisionProjectDlg::UpdateImageViewTabControl()
{
	try
	{
		m_tabView.DeleteAllItems() ;

		int nImageViewCount = m_projectData.m_mgImageViewDlg.GetImageViewDlgListSize() ;
		if (nImageViewCount < 0)
			return ;

		for (int i = 0 ;i < nImageViewCount ;i++)
		{
			CInterfaceImageViewDlg *pInterfaceImageViewDlg = m_projectData.m_mgImageViewDlg.GetImageViewDlgById(i) ;
			//插入tab标签
			m_tabView.InsertItem(i,pInterfaceImageViewDlg->strImageViewDlgName) ;
			if (NULL == pInterfaceImageViewDlg->pImageViewDlg)
			{
				pInterfaceImageViewDlg->pImageViewDlg          = new CImageViewDlg ;
				pInterfaceImageViewDlg->pImageViewDlg->Create(IDD_IMAGEVIEW_DIALOG,&m_tabView) ;
			}
			else
			{
				HalconCpp::CloseWindow(pInterfaceImageViewDlg->pImageViewDlg->m_lWindowID) ;
			}

			//设定在Tab内显示范围
			CRect rc;
			m_tabView.GetClientRect(rc);
			rc.top += 20;
			rc.bottom -= 0;
			rc.left += 0;
			rc.right -= 0;
			pInterfaceImageViewDlg->pImageViewDlg->MoveWindow(&rc) ;
			pInterfaceImageViewDlg->pImageViewDlg->InitViewControl() ;
		}

		//对话框显示
		SetActiveImageViewDlg(0) ;
	}
	catch (...)
	{
	}
}

void CVisionProjectDlg::UpdateWorkFlowTabControl()
{
	try
	{
		m_tabWorkFlowDlg.DeleteAllItems() ;

		int nWorkFlowCount = m_projectData.m_mgWorkFlowDlg.GetWorkFlowDlgListSize() ;
		if (nWorkFlowCount <= 0)
			return ;

		for (int i = 0 ;i < nWorkFlowCount ;i++)
		{
			CInterfaceWorkFlowDlg *pInterfaceWorkFlowDlg = m_projectData.m_mgWorkFlowDlg.GetWorkFlowDlgById(i) ;
			//插入标签
			m_tabWorkFlowDlg.InsertItem(i,pInterfaceWorkFlowDlg->strWorkFlowDlgName) ;
			//pInterfaceWorkFlowDlg->pWorkFlowDlg          = new CWorkFlowDlg() ;
			pInterfaceWorkFlowDlg->pWorkFlowDlg->Create(IDD_WROKFLOW_DIALOG,&m_tabWorkFlowDlg) ;
			//设定在Tab内显示范围
			CRect rc;
			m_tabWorkFlowDlg.GetClientRect(rc);
			rc.top += 20;
			rc.bottom -= 0;
			rc.left += 0;
			rc.right -= 0;
			pInterfaceWorkFlowDlg->pWorkFlowDlg->MoveWindow(&rc) ;
			pInterfaceWorkFlowDlg->pWorkFlowDlg->UpdateList() ;
		}

		SetActiveWorkFlowDlg(0) ;
	}
	catch (...)
	{
	}
}

void CVisionProjectDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	UPDATE_EASYSIZE;

	if (m_pSheetPanel != NULL)
	{
		RECT rc;
		GetDlgItem(IDC_STATIC_TOOL)->GetWindowRect(&rc);
		ScreenToClient(&rc) ;
		int width = rc.right - rc.left;
		int height = rc.bottom - rc.top;

		CRect rect ;
		GetDlgItem(IDC_STATIC_TOOL)->GetClientRect(&rect);
		rect.top -= 0 ;
		rect.left -= 0 ;
		rect.bottom -= 0 ;
		rect.right -= 0 ;
		m_pSheetPanel->GetTabControl()->MoveWindow(&rect);
		m_pSheetPanel->MoveWindow(rc.left,rc.top,  width, height) ;
		int nPageID = m_pSheetPanel->GetActiveIndex() ;
		if (E_PANEL_HARDWARE == nPageID)
		{
			m_pSheetPanel->SetActivePage(E_PANEL_HARDWARE);
			m_pSheetPanel->ShowWindow(SW_SHOW);
			m_HardWareToolPanelDlg.MoveWindow(rect.left,rect.top+20,  width, height) ;
		}
		else if (E_PANEL_CALI == nPageID)
		{
			m_pSheetPanel->SetActivePage(E_PANEL_CALI);
			m_pSheetPanel->ShowWindow(SW_SHOW);
			m_CaliToolPanelDlg.MoveWindow(rect.left,rect.top+20,  width, height) ;
		}
		else if (E_PANEL_2DVISION == nPageID)
		{
			m_pSheetPanel->SetActivePage(E_PANEL_2DVISION);
			m_pSheetPanel->ShowWindow(SW_SHOW);
			m_Vision2DPanelDlg.MoveWindow(rect.left,rect.top+20,  width, height) ;
		}
		else if (E_PANEL_2DVISIONLOGIC == nPageID)
		{
			m_pSheetPanel->SetActivePage(E_PANEL_2DVISIONLOGIC);
			m_pSheetPanel->ShowWindow(SW_SHOW);
			m_Vision2DLogicPanelDlg.MoveWindow(rect.left,rect.top+20,  width, height) ;
		}
		else if (E_PANEL_VISIONSYSTEM == nPageID)
		{
			m_pSheetPanel->SetActivePage(E_PANEL_VISIONSYSTEM);
			m_pSheetPanel->ShowWindow(SW_SHOW);
			m_VisionSystemPanelDlg.MoveWindow(rect.left,rect.top+20,  width, height) ;
		}

		InvalidateRect((CRect)rc);
	}

	if (m_projectData.m_mgImageViewDlg.GetImageViewDlgListSize() <= 0)
		return ;

	if (NULL == m_tabView)
		return ;

	int nCurSelTab = m_tabView.GetCurSel() ;
	//m_tabView.DeleteAllItems() ;

	HideAllImageViewDlg() ;

	for (int i = 0 ;i < m_projectData.m_mgImageViewDlg.GetImageViewDlgListSize();i++)
	{
		CInterfaceImageViewDlg *pImageView = m_projectData.m_mgImageViewDlg.GetImageViewDlgById(i) ;
		//m_tabView.InsertItem(i,pImageView->strImageViewDlgName) ;
		CRect rc ;
		m_tabView.GetClientRect(&rc) ;
		if (rc.IsRectEmpty()) continue;
		rc.top += 20;
		rc.bottom -= 0;
		rc.left += 0;
		rc.right -= 0;
		pImageView->pImageViewDlg->MoveWindow(&rc) ;
		HalconCpp::CloseWindow(pImageView->pImageViewDlg->m_lWindowID) ;
		pImageView->pImageViewDlg->InitViewControl() ;

		InvalidateRect((CRect)rc);
	}

	SetActiveImageViewDlg(nCurSelTab) ;
	m_tabView.SetCurSel(nCurSelTab) ;
}

void CVisionProjectDlg::OnSizing(UINT fwSide, LPRECT pRect)
{
	CDialogEx::OnSizing(fwSide, pRect);

	// TODO: 在此处添加消息处理程序代码
	EASYSIZE_MINSIZE(400, 300, fwSide, pRect);
}

void CVisionProjectDlg::SetActiveWorkFlowDlg(int nWorkFlowDlgID)
{
	try
	{
		if (nWorkFlowDlgID < 0)
		{
			return ;
		}

		for (int i = 0 ;i < m_projectData.m_mgWorkFlowDlg.GetWorkFlowDlgListSize();i++)
		{
			if (nWorkFlowDlgID == m_projectData.m_mgWorkFlowDlg.GetWorkFlowDlgById(i)->nWorkFlowDlgID)
			{
				m_tabWorkFlowDlg.SetCurSel(nWorkFlowDlgID) ;
				m_projectData.m_mgWorkFlowDlg.GetWorkFlowDlgById(i)->pWorkFlowDlg->ShowWindow(SW_SHOW) ;
				m_projectData.m_mgWorkFlowDlg.GetWorkFlowDlgById(i)->pWorkFlowDlg->SetFocus() ;
			}
			else
			{
				m_projectData.m_mgWorkFlowDlg.GetWorkFlowDlgById(i)->pWorkFlowDlg->ShowWindow(SW_HIDE) ;
			}
		}
	}
	catch (...)
	{
	}
}

void CVisionProjectDlg::SetActiveImageViewDlg(int nImageViewDlgID)
{
	try
	{
		if (nImageViewDlgID < 0)
		{
			return ;
		}

		for (int i = 0 ;i < m_projectData.m_mgImageViewDlg.GetImageViewDlgListSize();i++)
		{
			if (nImageViewDlgID == m_projectData.m_mgImageViewDlg.GetImageViewDlgById(i)->nImageViewDlgID)
			{
				m_tabView.SetCurSel(nImageViewDlgID) ;
				m_projectData.m_mgImageViewDlg.GetImageViewDlgById(i)->pImageViewDlg->ShowWindow(SW_SHOW) ;
				m_projectData.m_mgImageViewDlg.GetImageViewDlgById(i)->pImageViewDlg->SetFocus() ;
			}
			else
			{
				m_projectData.m_mgImageViewDlg.GetImageViewDlgById(i)->pImageViewDlg->ShowWindow(SW_HIDE) ;
			}
		}
	}
	catch (...)
	{
	}
}

void CVisionProjectDlg::HideAllImageViewDlg()
{
	try
	{
		for (int i = 0 ;i < m_projectData.m_mgImageViewDlg.GetImageViewDlgListSize();i++)
		{
			CInterfaceImageViewDlg *pImageView = m_projectData.m_mgImageViewDlg.GetImageViewDlgById(i) ;
			pImageView->pImageViewDlg->ShowWindow(SW_HIDE) ;
			/*HalconCpp::CloseWindow(pImageView->pImageViewDlg->m_lWindowID) ;
			pImageView->pImageViewDlg->DestroyWindow() ;*/
		}
	}
	catch (...)
	{
	}
}

void CVisionProjectDlg::OnTcnSelchangeTabWorkflowdlg(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	SetActiveWorkFlowDlg(m_tabWorkFlowDlg.GetCurSel()) ;
	*pResult = 0;
}

void CVisionProjectDlg::OnButtonClicked(UINT uBtnId)
{
	try
	{
		switch(uBtnId)
		{
		case IDC_BTN_CYCLERUN:
			{
				Systst2() ;
				////获取当前WorkFlowDlg ;
				//CInterfaceWorkFlowDlg *pCurWorkFlowDlg = m_projectData.m_mgWorkFlowDlg.GetWorkFlowDlgById(0) ;

				////获取当前选中工具ID
				//int nCurSelListBox = pCurWorkFlowDlg->pWorkFlowDlg->m_ListWorkFlow.GetCurSel() ;
				//if (nCurSelListBox < 0)
				//	return ;

				////获取当前选中工具
				//CFlowNode *pNode = pCurWorkFlowDlg->pWorkFlowDlg->m_ManageFlowNode.GetFlowNodeById(nCurSelListBox) ;
				//if (NULL == pNode)
				//	return ;
				////执行
				//if (ProVisionFun(pNode->pVisionBase->Vision_Run(),pNode->eFlowNodeType,_T("Vision_Run")))
				//{
				//	//获取结果
				//	vector<any> vecOutput ;
				//	vecOutput.clear() ;
				//	if(ProVisionFun(pNode->pVisionBase->Vision_Output(vecOutput),pNode->eFlowNodeType,_T("Vision_Output")))
				//	{
				//		//保存结果
				//		HObject hImage ;
				//		VImage image ;
				//		any aValue = vecOutput[0] ;
				//		try
				//		{
				//			if (aValue.type() == typeid(VImage))
				//			{
				//				image = any_cast<VImage>(aValue);
				//				WriteImage(image.vImage,"bmp",0,"D:\\run.bmp") ;
				//			}
				//		}
				//		catch (...)
				//		{
				//		}
				//	}
				//}

				//AfxMessageBox(_T("IDC_BTN_CYCLERUN")) ;
				break;
			}
		case IDC_BTN_STOP:
			{
				AfxMessageBox(_T("IDC_BTN_STOP")) ;
				break;
			}
		case IDC_BTN_PROJECT:
			{
				BtnManageProject() ;
				break;
			}
			/*case IDC_BTN_SAVE:
			{
			AfxMessageBox(_T("IDC_BTN_SAVE")) ;
			break;
			}*/
		case IDC_BTN_CAMERA:
			{
				//相机管理
				BtnManageCamera() ;
				break;
			}
		case IDC_BTN_LED:
			{
				AfxMessageBox(_T("IDC_BTN_LED")) ;
				break;
			}
		case IDC_BTN_MESSAGE:
			{
				BtnManageMessage() ;
				break;
			}
		case IDC_BTN_MOBUS:
			{
				BtnManageModbus() ;
				break;
			}
		case IDC_BTN_NEWVIEW:
			{
				BtnNewView() ;
				break;
			}
		case IDC_BTN_VIEWCONNECT:
			{
				BtnViewConnect() ;
				break;
			}
		case IDC_BTN_DELVIEW:
			{
				BtnDelView() ;
				break;
			}
		case IDC_BTN_LUAGOBALVIARENT:
			{
				BtnLuaGobalViarent() ;
				break;
			}
		case IDC_BTN_MANAGEUSER:
			{
				AfxMessageBox(_T("IDC_BTN_MANAGEUSER")) ;
				break;
			}
		case IDC_BTN_LOGINUSER:
			{
				AfxMessageBox(_T("IDC_BTN_LOGINUSER")) ;
				break;
			}
		case IDC_BTN_LICENSE:
			{
				AfxMessageBox(_T("IDC_BTN_LICENSE")) ;
				break;
			}
		case IDC_BTN_SYSTEMSET:
			{
				AfxMessageBox(_T("IDC_BTN_SYSTEMSET")) ;
				break;
			}
		case IDC_BTN_UI:
			{
				AfxMessageBox(_T("IDC_BTN_UI")) ;
				break;
			}
		case IDC_BTN_NEWFLOW:
			{
				//新建流程
				BtnNewflow() ;
				break;
			}
		case IDC_BTN_DELFLOW:
			{
				AfxMessageBox(_T("IDC_BTN_DELFLOW")) ;
				break;
			}
		case IDC_BTN_TSTFLOW:
			{
				AfxMessageBox(_T("IDC_BTN_TSTFLOW")) ;
				break;
			}
		default:
			break;
		}
	}
	catch (...)
	{
	}
}

void CVisionProjectDlg::BtnNewflow()
{
	// 新建工作流程页
	try
	{
		CNewDlg newDlg ;
		newDlg.m_strStaticInfo = _T("流程名") ;
		if (IDOK != newDlg.DoModal())
			return ;
		if (newDlg.m_strInfo.IsEmpty())
		{
			AfxMessageBox(_T("请输入流程名")) ;
			return ;
		}

		//判断流程名称是否唯一
		if (!CheckWorkFlowName(m_projectData.m_mgWorkFlowDlg,newDlg.m_strInfo))
		{
			AfxMessageBox(_T("输入流程名重复，请重新输入")) ;
			return ;
		}

		//插入tab标签
		m_tabWorkFlowDlg.InsertItem(m_projectData.m_mgWorkFlowDlg.GetWorkFlowDlgListSize(),newDlg.m_strInfo) ;

		//新建WorkFlowDlg
		CInterfaceWorkFlowDlg *pInterfaceWorkFlowDlg = new CInterfaceWorkFlowDlg();
		pInterfaceWorkFlowDlg->nWorkFlowDlgID        = m_projectData.m_mgWorkFlowDlg.GetWorkFlowDlgListSize() ;
		pInterfaceWorkFlowDlg->strWorkFlowDlgName    = newDlg.m_strInfo ;
		pInterfaceWorkFlowDlg->pWorkFlowDlg          = new CWorkFlowDlg ;
		pInterfaceWorkFlowDlg->pWorkFlowDlg->m_strWorkFlowDlgName = newDlg.m_strInfo ;
		pInterfaceWorkFlowDlg->pWorkFlowDlg->Create(IDD_WROKFLOW_DIALOG,&m_tabWorkFlowDlg) ;

		//设定在Tab内显示范围
		CRect rc;
		m_tabWorkFlowDlg.GetClientRect(rc);
		rc.top += 20;
		rc.bottom -= 0;
		rc.left += 0;
		rc.right -= 0;
		pInterfaceWorkFlowDlg->pWorkFlowDlg->MoveWindow(&rc) ;
		/*CRect rc ;
		m_tabWorkFlowDlg.GetWindowRect(&rc) ;
		ScreenToClient(&rc);
		pInterfaceWorkFlowDlg->pWorkFlowDlg->MoveWindow(&rc) ; */
		m_projectData.m_mgWorkFlowDlg.AddTail(pInterfaceWorkFlowDlg) ;
		//对话框显示
		SetActiveWorkFlowDlg(m_projectData.m_mgWorkFlowDlg.GetWorkFlowDlgListSize()-1) ;

		//创建路径
		CString strFolder(_T("")) ;
		strFolder = g_sysIni.m_strProjectPath + _T("\\") + newDlg.m_strInfo ;
		if (!vPathIsExist(strFolder))
		{
			CreateDirectory ( strFolder, NULL );
		}
		else
		{
#ifdef _UNICODE

			USES_CONVERSION;
			DeleteFolder ( T2A(strFolder) ) ;
#else

			DeleteFolder ( ( LPSTR ) ( LPCSTR )strFolder ) ;
#endif
			CreateDirectory ( strFolder, NULL );
		}
	}
	catch (...)
	{
	}
}

void CVisionProjectDlg::BtnManageCamera()
{
	try
	{
		CManageCameraDlg manageCameraDlg ;
		if (IDOK == manageCameraDlg.DoModal())
		{
		}
	}
	catch (...)
	{
	}
}

void CVisionProjectDlg::BtnNewView()
{
	//新建视图
	try
	{
		CNewDlg newDlg ;
		newDlg.m_strStaticInfo = _T("视图名") ;
		if (IDOK != newDlg.DoModal())
			return ;
		if (newDlg.m_strInfo.IsEmpty())
		{
			AfxMessageBox(_T("请输入视图名")) ;
			return ;
		}

		//判断视图名称是否唯一
		if (!CheckImageViewName(m_projectData.m_mgImageViewDlg,newDlg.m_strInfo))
		{
			AfxMessageBox(_T("输入视图名重复，请重新输入")) ;
			return ;
		}

		//插入tab标签
		m_tabView.InsertItem(m_projectData.m_mgImageViewDlg.GetImageViewDlgListSize(),newDlg.m_strInfo) ;

		//新建imageViewDlg
		CInterfaceImageViewDlg *pInterfaceImageViewDlg = new CInterfaceImageViewDlg();
		pInterfaceImageViewDlg->nImageViewDlgID        = m_projectData.m_mgImageViewDlg.GetImageViewDlgListSize() ;
		pInterfaceImageViewDlg->strImageViewDlgName    = newDlg.m_strInfo ;
		pInterfaceImageViewDlg->pImageViewDlg          = new CImageViewDlg ;
		pInterfaceImageViewDlg->pImageViewDlg->Create(IDD_IMAGEVIEW_DIALOG,&m_tabView) ;

		//设定在Tab内显示范围
		CRect rc;
		m_tabView.GetClientRect(rc);
		rc.top += 20;
		rc.bottom -= 0;
		rc.left += 0;
		rc.right -= 0;
		pInterfaceImageViewDlg->pImageViewDlg->MoveWindow(&rc) ;
		m_projectData.m_mgImageViewDlg.AddTail(pInterfaceImageViewDlg) ;

		pInterfaceImageViewDlg->pImageViewDlg->InitViewControl() ;
		//对话框显示
		SetActiveImageViewDlg(m_projectData.m_mgImageViewDlg.GetImageViewDlgListSize()-1) ;
	}
	catch (...)
	{
	}
}

void CVisionProjectDlg::BtnViewConnect()
{
	try
	{
		CViewConnectDlg viewConnectDlg ;
		if (IDOK == viewConnectDlg.DoModal())
		{
			m_projectData.m_mgImageViewDlg.GetImageViewDlgById(m_tabView.GetCurSel())->strConnectWorkFlowName = viewConnectDlg.m_strWorkFlowName ;
		}
	}
	catch (...)
	{
	}
}

void CVisionProjectDlg::BtnDelView()
{
	try
	{
		if (IDOK != AfxMessageBox(_T("是否删除视图?"),MB_OKCANCEL))
			return ;

		int nSelView = m_tabView.GetCurSel() ;
		if (nSelView < 0)
		{
			AfxMessageBox(_T("请选中删除视图")) ;
			return ;
		}

		m_projectData.m_mgImageViewDlg.RemoveAtById(nSelView) ;
		m_projectData.m_mgImageViewDlg.ReSortById() ;

		UpdateImageViewTabControl() ;
	}
	catch (...)
	{
	}
}

void CVisionProjectDlg::BtnManageProject()
{
	try
	{
		CManageProjectDlg projectDlg ;
		projectDlg.DoModal() ;
	}
	catch (...)
	{
	}
}

void CVisionProjectDlg::BtnLuaGobalViarent()
{
	try
	{
		CManageViarentDlg manageViarentDlg ;
		manageViarentDlg.DoModal() ;
	}
	catch (...)
	{
	}
}

void CVisionProjectDlg::BtnManageMessage()
{
	try
	{
		CManageCommunicationDlg manageCommDlg ;
		manageCommDlg.DoModal() ;
	}
	catch (...)
	{
	}
}

void  CVisionProjectDlg::BtnManageModbus()
{
	try
	{
		CManageModbusDlg manageModbusDlg ;
		manageModbusDlg.DoModal() ;
	}
	catch (...)
	{
	}
}

void CVisionProjectDlg::OnClose()
{
	try
	{
		if (IDOK != AfxMessageBox(_T("是否退出系统?"),MB_OKCANCEL))
			return ;

		m_projectData.SaveProjectData() ;
		m_projectData.ReleaseProjectData() ;
		m_projectData.ReleaseDeviceData() ;
	}
	catch (...)
	{
	}

	CDialogEx::OnClose();
}

void CVisionProjectDlg::Systst()
{
	try
	{
		//g_VisionGlobal.LoadScript("D:\\GobalViarent.lua") ;
		g_VisionGlobal.LoadScript("E:\\Project\\2020\\10\\VisionProject\\bin\\Project\\P1\\WorkFlow.lua") ;
	}
	catch (...)
	{
	}
}

void  CVisionProjectDlg::Systst2()
{
	USES_CONVERSION ;
	try
	{
		////获取当前WorkFlowDlg ;
		CInterfaceWorkFlowDlg *pCurWorkFlowDlg = m_projectData.m_mgWorkFlowDlg.GetWorkFlowDlgById(0) ;

		//获取当前选中工具ID
		int nCurSelListBox = pCurWorkFlowDlg->pWorkFlowDlg->m_ListWorkFlow.GetCurSel() ;
		if (nCurSelListBox < 0)
			return ;

		//获取当前选中工具
		CFlowNode *pNode = pCurWorkFlowDlg->pWorkFlowDlg->m_ManageFlowNode.GetFlowNodeById(nCurSelListBox) ;
		if (NULL == pNode)
			return ;

		//获取输入参数
		vector<any> vecInput ;
		if (!m_projectData.GetInputPara(pNode,vecInput))
		{
			AfxMessageBox(_T("获取输入参数失败")) ;
			return ;
		}
		//输入参数
		if (ProVisionFun(pNode->pVisionBase->Vision_Input(vecInput),pNode->eFlowNodeType,_T("Vision_Input")))
		{
			//初始化
			if(ProVisionFun(pNode->pVisionBase->Vision_Init(),pNode->eFlowNodeType,_T("Vision_Init")))
			{
				CString strConfigPath(_T("")) ;
				if (!m_projectData.GetConfigPath(pCurWorkFlowDlg->pWorkFlowDlg->m_strWorkFlowDlgName,pNode,strConfigPath))
				{
					AfxMessageBox(_T("获取参数路径失败")) ;
					return ;
				}

				//加载配置文件
				if(!ProVisionFun(pNode->pVisionBase->Vision_LoadConfigure(W2A(strConfigPath)),pNode->eFlowNodeType,_T("Vision_LoadConfigure")) )
				{
					//工具加载配置文件失败 重新设置配置路径
					ProVisionFun(pNode->pVisionBase->Vision_SetConfigurePath(W2A(strConfigPath)),pNode->eFlowNodeType,_T("Vision_SetConfigurePath")) ;
				}

				//执行
				if (ProVisionFun(pNode->pVisionBase->Vision_Run(),pNode->eFlowNodeType,_T("Vision_Run")))
				{
					//获取结果
					vector<any> vecOutput ;
					vecOutput.clear() ;
					if(ProVisionFun(pNode->pVisionBase->Vision_Output(vecOutput),pNode->eFlowNodeType,_T("Vision_Output")))
					{
						if (vecOutput.size() <= 0) return ;

						//显示结果
						VString vStroutput ;
						any aValue = vecOutput[0] ;
						try
						{
							if (aValue.type() == typeid(VString))
							{
								vStroutput = any_cast<VString>(aValue);
								CString strInfo(vStroutput.vStr.c_str())  ;
								AfxMessageBox(strInfo) ;
							}
						}
						catch (...)
						{
						}
					}
				}
			}
		}
	}
	catch (...)
	{
	}
}