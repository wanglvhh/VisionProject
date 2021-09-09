// VisionProjectDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VisionProject.h"
#include "VisionProjectDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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

// CVisionProjectDlg �Ի���

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

// CVisionProjectDlg ��Ϣ�������
BEGIN_EASYSIZE_MAP(CVisionProjectDlg)

	/*
	left��top��right��bottom�ֱ�ָ���Ǹÿؼ����ϡ��ҡ��·��Ŀؼ���ID��Ҳ����Ϊ��������ֵ��
	ES_BORDER��������߿���벻��
	ES_KEEPSIZE�����ִ�С����
	����λ�ã�
	left -- ��ʾ��rightָ���Ŀؼ��Ҷ���
	right -- ��ʾ��leftָ���Ŀؼ������
	top -- ��ʾ��bottomָ���Ŀؼ��϶���
	bottom -- ��ʾ��topָ���Ŀؼ��¶���
	options��ָ��Ϊ0��Ҳ��ָ��Ϊ����ֵ��
	ES_HCENTER�����ֿ�Ȳ��䣬ˮƽλ����left��rightָ���Ŀؼ����м�
	ES_VCENTER�����ָ߶Ȳ��䣬��ֱλ����left��rightָ���Ŀؼ����м�
	*/
	/*
	EASYSIZE(IDOK,ES_BORDER,ES_BORDER,ES_BORDER,ES_BORDER,0)
	��ʾ���ź�ֵΪIDOK�Ŀؼ�������߽���������λ�ñ��ֲ��䣬ˮƽ�ʹ�ֱ����ߴ����죻

	EASYSIZE(IDOK,ES_BORDER,ES_BORDER,ES_BORDER,ES_BORDER,ES_HCENTER)
	��ʾ���ź�ֵΪIDOK�Ŀؼ�������߽�����λ�ñ��ֲ��䣬��ֱ����ߴ����죬ˮƽ���У�

	EASYSIZE(IDOK,ES_BORDER,ES_BORDER,ES_BORDER,ES_BORDER,ES_HCENTER| ES_HCENTER)
	��ʾ���ź�ֵΪIDOK�Ŀؼ����ڶԻ����ڴ�ֱ���У�ˮƽ���У�

	EASYSIZE(IDOK,ES_BORDER,ES_KEEPSIZE,ES_KEEPSIZE,ES_BORDER,0)
	��ʾ���ź�ֵΪIDOK�Ŀؼ�������߽����·�λ�ñ��ֲ��䣬ͬʱ���ֿؼ��ߴ磻

	EASYSIZE(IDOK,ES_BORDER,ES_KEEPSIZE, ES_BORDER,ES_BORDER,0)
	��ʾ���ź�ֵΪIDOK�Ŀؼ�������߽����ҡ��·�λ�ñ��ֲ��䣬ˮƽ����ߴ����죬��ֱ����ߴ粻�䣻

	EASYSIZE(IDOK,ES_BORDER,ES_BORDER,IDCANCEL,ES_BORDER,0)
	��ʾ���ź�ֵΪIDOK�Ŀؼ�������߽�������λ�ñ��ֲ��䣬����IDֵΪIDCANCEL���ҷ�λ�þ��뱣�ֲ��䣬ˮƽ�ʹ�ֱ����ߴ����죻
	����ʹ��ָ���ؼ���Ϊ��λ����ʱ��ȷ��ָ���ؼ���EASYSIZE�ڸú�ǰ�棩
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

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
/*
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
*/
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	SPLASH_START(m_pSplashWindowDlg,_T("��ʼ��ʼ��ϵͳ")) ;

	INIT_EASYSIZE;
	//�������
	//ShowWindow(SW_MAXIMIZE);
	//��ʼ���ؼ�
	SPLASH_STEP(m_pSplashWindowDlg,_T("��ʼ���ؼ�")) ;
	InitAllControl() ;
	//��������
	SPLASH_STEP(m_pSplashWindowDlg,_T("��������")) ;
	LoadProjectData() ;
	//���¿ؼ�
	SPLASH_STEP(m_pSplashWindowDlg,_T("���¿ؼ�")) ;
	UpdateAllControl() ;
	//ע��ű�
	SPLASH_STEP(m_pSplashWindowDlg,_T("ע��ű�")) ;
	g_VisionGlobal.InitScript() ;

	SPLASH_END(m_pSplashWindowDlg,_T("������ʼ��ϵͳ")) ;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CVisionProjectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CVisionProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CVisionProjectDlg::InitAllControl()
{
	try
	{
		//��ʼ��button�ؼ�
		InitBtnControl()  ;

		//��ʼ������ҳ�ؼ�
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
		SPLASH_STEP(m_pSplashWindowDlg,_T("�����豸����")) ;
		m_projectData.LoadDeviceData() ;

		SPLASH_STEP(m_pSplashWindowDlg,_T("���ع�������")) ;
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
		m_HardWareToolPanelDlg.m_psp.pszTitle = _T("�Ӿ�Ӳ��") ;
		m_pSheetPanel->AddPage(&m_HardWareToolPanelDlg) ;

		m_CaliToolPanelDlg.m_psp.dwFlags |= PSP_USETITLE ;
		m_CaliToolPanelDlg.m_psp.pszTitle = _T("�Ӿ��궨") ;
		m_pSheetPanel->AddPage(&m_CaliToolPanelDlg) ;

		m_Vision2DPanelDlg.m_psp.dwFlags |= PSP_USETITLE ;
		m_Vision2DPanelDlg.m_psp.pszTitle = _T("2D�Ӿ�") ;
		m_pSheetPanel->AddPage(&m_Vision2DPanelDlg) ;

		m_Vision2DLogicPanelDlg.m_psp.dwFlags |= PSP_USETITLE ;
		m_Vision2DLogicPanelDlg.m_psp.pszTitle = _T("2D�Ӿ��߼�") ;
		m_pSheetPanel->AddPage(&m_Vision2DLogicPanelDlg) ;

		m_VisionSystemPanelDlg.m_psp.dwFlags |= PSP_USETITLE ;
		m_VisionSystemPanelDlg.m_psp.pszTitle = _T("ϵͳ") ;
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
			//����tab��ǩ
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

			//�趨��Tab����ʾ��Χ
			CRect rc;
			m_tabView.GetClientRect(rc);
			rc.top += 20;
			rc.bottom -= 0;
			rc.left += 0;
			rc.right -= 0;
			pInterfaceImageViewDlg->pImageViewDlg->MoveWindow(&rc) ;
			pInterfaceImageViewDlg->pImageViewDlg->InitViewControl() ;
		}

		//�Ի�����ʾ
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
			//�����ǩ
			m_tabWorkFlowDlg.InsertItem(i,pInterfaceWorkFlowDlg->strWorkFlowDlgName) ;
			//pInterfaceWorkFlowDlg->pWorkFlowDlg          = new CWorkFlowDlg() ;
			pInterfaceWorkFlowDlg->pWorkFlowDlg->Create(IDD_WROKFLOW_DIALOG,&m_tabWorkFlowDlg) ;
			//�趨��Tab����ʾ��Χ
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

	// TODO: �ڴ˴������Ϣ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
				////��ȡ��ǰWorkFlowDlg ;
				//CInterfaceWorkFlowDlg *pCurWorkFlowDlg = m_projectData.m_mgWorkFlowDlg.GetWorkFlowDlgById(0) ;

				////��ȡ��ǰѡ�й���ID
				//int nCurSelListBox = pCurWorkFlowDlg->pWorkFlowDlg->m_ListWorkFlow.GetCurSel() ;
				//if (nCurSelListBox < 0)
				//	return ;

				////��ȡ��ǰѡ�й���
				//CFlowNode *pNode = pCurWorkFlowDlg->pWorkFlowDlg->m_ManageFlowNode.GetFlowNodeById(nCurSelListBox) ;
				//if (NULL == pNode)
				//	return ;
				////ִ��
				//if (ProVisionFun(pNode->pVisionBase->Vision_Run(),pNode->eFlowNodeType,_T("Vision_Run")))
				//{
				//	//��ȡ���
				//	vector<any> vecOutput ;
				//	vecOutput.clear() ;
				//	if(ProVisionFun(pNode->pVisionBase->Vision_Output(vecOutput),pNode->eFlowNodeType,_T("Vision_Output")))
				//	{
				//		//������
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
				//�������
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
				//�½�����
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
	// �½���������ҳ
	try
	{
		CNewDlg newDlg ;
		newDlg.m_strStaticInfo = _T("������") ;
		if (IDOK != newDlg.DoModal())
			return ;
		if (newDlg.m_strInfo.IsEmpty())
		{
			AfxMessageBox(_T("������������")) ;
			return ;
		}

		//�ж����������Ƿ�Ψһ
		if (!CheckWorkFlowName(m_projectData.m_mgWorkFlowDlg,newDlg.m_strInfo))
		{
			AfxMessageBox(_T("�����������ظ�������������")) ;
			return ;
		}

		//����tab��ǩ
		m_tabWorkFlowDlg.InsertItem(m_projectData.m_mgWorkFlowDlg.GetWorkFlowDlgListSize(),newDlg.m_strInfo) ;

		//�½�WorkFlowDlg
		CInterfaceWorkFlowDlg *pInterfaceWorkFlowDlg = new CInterfaceWorkFlowDlg();
		pInterfaceWorkFlowDlg->nWorkFlowDlgID        = m_projectData.m_mgWorkFlowDlg.GetWorkFlowDlgListSize() ;
		pInterfaceWorkFlowDlg->strWorkFlowDlgName    = newDlg.m_strInfo ;
		pInterfaceWorkFlowDlg->pWorkFlowDlg          = new CWorkFlowDlg ;
		pInterfaceWorkFlowDlg->pWorkFlowDlg->m_strWorkFlowDlgName = newDlg.m_strInfo ;
		pInterfaceWorkFlowDlg->pWorkFlowDlg->Create(IDD_WROKFLOW_DIALOG,&m_tabWorkFlowDlg) ;

		//�趨��Tab����ʾ��Χ
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
		//�Ի�����ʾ
		SetActiveWorkFlowDlg(m_projectData.m_mgWorkFlowDlg.GetWorkFlowDlgListSize()-1) ;

		//����·��
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
	//�½���ͼ
	try
	{
		CNewDlg newDlg ;
		newDlg.m_strStaticInfo = _T("��ͼ��") ;
		if (IDOK != newDlg.DoModal())
			return ;
		if (newDlg.m_strInfo.IsEmpty())
		{
			AfxMessageBox(_T("��������ͼ��")) ;
			return ;
		}

		//�ж���ͼ�����Ƿ�Ψһ
		if (!CheckImageViewName(m_projectData.m_mgImageViewDlg,newDlg.m_strInfo))
		{
			AfxMessageBox(_T("������ͼ���ظ�������������")) ;
			return ;
		}

		//����tab��ǩ
		m_tabView.InsertItem(m_projectData.m_mgImageViewDlg.GetImageViewDlgListSize(),newDlg.m_strInfo) ;

		//�½�imageViewDlg
		CInterfaceImageViewDlg *pInterfaceImageViewDlg = new CInterfaceImageViewDlg();
		pInterfaceImageViewDlg->nImageViewDlgID        = m_projectData.m_mgImageViewDlg.GetImageViewDlgListSize() ;
		pInterfaceImageViewDlg->strImageViewDlgName    = newDlg.m_strInfo ;
		pInterfaceImageViewDlg->pImageViewDlg          = new CImageViewDlg ;
		pInterfaceImageViewDlg->pImageViewDlg->Create(IDD_IMAGEVIEW_DIALOG,&m_tabView) ;

		//�趨��Tab����ʾ��Χ
		CRect rc;
		m_tabView.GetClientRect(rc);
		rc.top += 20;
		rc.bottom -= 0;
		rc.left += 0;
		rc.right -= 0;
		pInterfaceImageViewDlg->pImageViewDlg->MoveWindow(&rc) ;
		m_projectData.m_mgImageViewDlg.AddTail(pInterfaceImageViewDlg) ;

		pInterfaceImageViewDlg->pImageViewDlg->InitViewControl() ;
		//�Ի�����ʾ
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
		if (IDOK != AfxMessageBox(_T("�Ƿ�ɾ����ͼ?"),MB_OKCANCEL))
			return ;

		int nSelView = m_tabView.GetCurSel() ;
		if (nSelView < 0)
		{
			AfxMessageBox(_T("��ѡ��ɾ����ͼ")) ;
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
		if (IDOK != AfxMessageBox(_T("�Ƿ��˳�ϵͳ?"),MB_OKCANCEL))
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
		////��ȡ��ǰWorkFlowDlg ;
		CInterfaceWorkFlowDlg *pCurWorkFlowDlg = m_projectData.m_mgWorkFlowDlg.GetWorkFlowDlgById(0) ;

		//��ȡ��ǰѡ�й���ID
		int nCurSelListBox = pCurWorkFlowDlg->pWorkFlowDlg->m_ListWorkFlow.GetCurSel() ;
		if (nCurSelListBox < 0)
			return ;

		//��ȡ��ǰѡ�й���
		CFlowNode *pNode = pCurWorkFlowDlg->pWorkFlowDlg->m_ManageFlowNode.GetFlowNodeById(nCurSelListBox) ;
		if (NULL == pNode)
			return ;

		//��ȡ�������
		vector<any> vecInput ;
		if (!m_projectData.GetInputPara(pNode,vecInput))
		{
			AfxMessageBox(_T("��ȡ�������ʧ��")) ;
			return ;
		}
		//�������
		if (ProVisionFun(pNode->pVisionBase->Vision_Input(vecInput),pNode->eFlowNodeType,_T("Vision_Input")))
		{
			//��ʼ��
			if(ProVisionFun(pNode->pVisionBase->Vision_Init(),pNode->eFlowNodeType,_T("Vision_Init")))
			{
				CString strConfigPath(_T("")) ;
				if (!m_projectData.GetConfigPath(pCurWorkFlowDlg->pWorkFlowDlg->m_strWorkFlowDlgName,pNode,strConfigPath))
				{
					AfxMessageBox(_T("��ȡ����·��ʧ��")) ;
					return ;
				}

				//���������ļ�
				if(!ProVisionFun(pNode->pVisionBase->Vision_LoadConfigure(W2A(strConfigPath)),pNode->eFlowNodeType,_T("Vision_LoadConfigure")) )
				{
					//���߼��������ļ�ʧ�� ������������·��
					ProVisionFun(pNode->pVisionBase->Vision_SetConfigurePath(W2A(strConfigPath)),pNode->eFlowNodeType,_T("Vision_SetConfigurePath")) ;
				}

				//ִ��
				if (ProVisionFun(pNode->pVisionBase->Vision_Run(),pNode->eFlowNodeType,_T("Vision_Run")))
				{
					//��ȡ���
					vector<any> vecOutput ;
					vecOutput.clear() ;
					if(ProVisionFun(pNode->pVisionBase->Vision_Output(vecOutput),pNode->eFlowNodeType,_T("Vision_Output")))
					{
						if (vecOutput.size() <= 0) return ;

						//��ʾ���
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