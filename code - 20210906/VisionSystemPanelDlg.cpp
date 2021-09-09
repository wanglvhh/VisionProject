// VisionSystemPanelDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "VisionProject.h"
#include "VisionSystemPanelDlg.h"
#include "afxdialogex.h"
#include "VisionProjectDlg.h"

// CVisionSystemPanelDlg 对话框
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(CVisionSystemPanelDlg, CPropertyPage)

CVisionSystemPanelDlg::CVisionSystemPanelDlg()
	: CPropertyPage(CVisionSystemPanelDlg::IDD)
{
}

CVisionSystemPanelDlg::~CVisionSystemPanelDlg()
{
}

void CVisionSystemPanelDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_LUASCRIPT, m_btnLuaScript);
	DDX_Control(pDX, IDC_BTN_COMMRECV, m_btnCommRecv);
	DDX_Control(pDX, IDC_BTN_COMMSEND, m_btnCommSend);
	DDX_Control(pDX, IDC_BTN_MODBUSRECV, m_btnModbusRecv);
	DDX_Control(pDX, IDC_BTN_MODBUSSEND, m_btnModbusSend);
}

BEGIN_MESSAGE_MAP(CVisionSystemPanelDlg, CPropertyPage)
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_LUASCRIPT, IDC_BTN_COMMSEND, OnButtonClicked)
END_MESSAGE_MAP()

// CVisionSystemPanelDlg 消息处理程序

BEGIN_EASYSIZE_MAP(CVisionSystemPanelDlg)

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
	EASYSIZE(IDC_BTN_LUASCRIPT,ES_BORDER,ES_BORDER,ES_KEEPSIZE,ES_KEEPSIZE,0)
END_EASYSIZE_MAP

BOOL CVisionSystemPanelDlg::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化
	INIT_EASYSIZE;

	m_brushBk.CreateSolidBrush(SYSTEM_BK_COLOR);

	ModifyStyle(0, WS_SIZEBOX);

	InitAllControl() ;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

BOOL CVisionSystemPanelDlg::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CPropertyPage::Create(lpszTemplateName, pParentWnd);
}

HBRUSH CVisionSystemPanelDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return m_brushBk;
}

void CVisionSystemPanelDlg::OnSize(UINT nType, int cx, int cy)
{
	CPropertyPage::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	UPDATE_EASYSIZE;
}

void CVisionSystemPanelDlg::InitAllControl()
{
	try
	{
		//初始化button控件
		InitBtnControl()  ;
	}
	catch (...)
	{
	}
}

void CVisionSystemPanelDlg::InitBtnControl()
{
	try
	{
		//LuaScript button
		m_btnLuaScript.SetIcon(IDI_ICON_LUAGOBALVARIENT) ;
		m_btnLuaScript.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnLuaScript.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnLuaScript.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnLuaScript.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnLuaScript.SetRounded(TRUE) ;

		//CommRecv button
		m_btnCommRecv.SetIcon(IDI_ICON_READ) ;
		m_btnCommRecv.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnCommRecv.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnCommRecv.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnCommRecv.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnCommRecv.SetRounded(TRUE) ;

		//CommSend button
		m_btnCommSend.SetIcon(IDI_ICON_SEND) ;
		m_btnCommSend.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnCommSend.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnCommSend.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnCommSend.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnCommSend.SetRounded(TRUE) ;

		//ModbusRecv button
		m_btnModbusRecv.SetIcon(IDI_ICON_MODBUS) ;
		m_btnModbusRecv.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnModbusRecv.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnModbusRecv.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnModbusRecv.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnModbusRecv.SetRounded(TRUE) ;

		//ModbusSend button
		m_btnModbusSend.SetIcon(IDI_ICON_MODBUS) ;
		m_btnModbusSend.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnModbusSend.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnModbusSend.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnModbusSend.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnModbusSend.SetRounded(TRUE) ;
	}
	catch (...)
	{
	}
}

void CVisionSystemPanelDlg::OnButtonClicked(UINT uBtnId)
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		if (!pDlg->m_bWorkFlowAddTool)
			return ;

		CString strName(_T("")),strFolder(_T("")) ;
		int nCurWorkFlowDlg = pDlg->m_tabWorkFlowDlg.GetCurSel() ;
		CInterfaceWorkFlowDlg *pCurInterfaceWorkFlowDlg = pDlg->m_projectData.m_mgWorkFlowDlg.GetWorkFlowDlgById(nCurWorkFlowDlg) ;
		CWorkFlowDlg *pCurWorkFlowDlg = pCurInterfaceWorkFlowDlg->pWorkFlowDlg ;

		switch (uBtnId)
		{
		case IDC_BTN_LUASCRIPT:
			{
				strName.Format(_T("(ID%d)Lua脚本"),pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ListWorkFlow.AddString(strName,pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_LUAGOBALVARIENT));
				//创建Lua脚本工具

				break;
			}
		case IDC_BTN_COMMRECV:
			{
				//创建通信接收工具
				CFlowNode *pFlowNode = new CFlowNode() ;
				pFlowNode->eFlowNodeType = E_TOOL_VISIONSYSTEM_COMMREAD ;
				pFlowNode->nFlowNodeID = pCurWorkFlowDlg->m_ListWorkFlow.GetCount() ;
				pFlowNode->mgrDllVisionBaseIm.DllCreateInterface(E_TOOL_VISIONSYSTEM_COMMREAD,(void **)&pFlowNode->pVisionBase) ;
				if (NULL == pFlowNode->pVisionBase)
				{
					AfxMessageBox(_T("通信接收工具Dll加载失败")) ;
					DELETE_POINT(pFlowNode) ;
					return ;
				}

				//创建文件夹
				strName.Format(_T("(ID%d)通信接收"),pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				strFolder = g_sysIni.m_strProjectPath + _T("\\") + pCurInterfaceWorkFlowDlg->strWorkFlowDlgName + _T("\\") + strName ;
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

				pCurWorkFlowDlg->m_ListWorkFlow.AddString(strName,pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_READ));

				//添加到链表
				pCurWorkFlowDlg->m_ManageFlowNode.AddTail(pFlowNode) ;

				break ;
			}
		case IDC_BTN_COMMSEND:
			{
				//创建通信发送工具
				CFlowNode *pFlowNode = new CFlowNode() ;
				pFlowNode->eFlowNodeType = E_TOOL_VISIONSYSTEM_COMMWRITE ;
				pFlowNode->nFlowNodeID = pCurWorkFlowDlg->m_ListWorkFlow.GetCount() ;
				pFlowNode->mgrDllVisionBaseIm.DllCreateInterface(E_TOOL_VISIONSYSTEM_COMMWRITE,(void **)&pFlowNode->pVisionBase) ;
				if (NULL == pFlowNode->pVisionBase)
				{
					AfxMessageBox(_T("通信发送工具Dll加载失败")) ;
					DELETE_POINT(pFlowNode) ;
					return ;
				}

				//创建文件夹
				strName.Format(_T("(ID%d)通信发送"),pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				strFolder = g_sysIni.m_strProjectPath + _T("\\") + pCurInterfaceWorkFlowDlg->strWorkFlowDlgName + _T("\\") + strName ;
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

				pCurWorkFlowDlg->m_ListWorkFlow.AddString(strName,pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_SEND));

				//添加到链表
				pCurWorkFlowDlg->m_ManageFlowNode.AddTail(pFlowNode) ;

				break ;
			}
		default:
			break;
		}

		pDlg->m_bWorkFlowAddTool = false ;
	}
	catch (...)
	{
	}
}