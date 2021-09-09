// Vision2DLogicPanelDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "VisionProject.h"
#include "Vision2DLogicPanelDlg.h"
#include "afxdialogex.h"
#include "VisionProjectDlg.h"

// CVision2DLogicPanelDlg 对话框
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(CVision2DLogicPanelDlg, CPropertyPage)

CVision2DLogicPanelDlg::CVision2DLogicPanelDlg()
	: CPropertyPage(CVision2DLogicPanelDlg::IDD)
{
}

CVision2DLogicPanelDlg::~CVision2DLogicPanelDlg()
{
}

void CVision2DLogicPanelDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_DISTANCEPP, m_btnDistancePP);
	DDX_Control(pDX, IDC_BTN_DISTACNEPL, m_btnDistancePL);
	DDX_Control(pDX, IDC_BTN_PROJECTPL, m_btnProjectPL);
	DDX_Control(pDX, IDC_BTN_INTERSECTIONLL, m_btnIntersectionLL);
	DDX_Control(pDX, IDC_BTN_ANGLELL, m_btnAngleLL);
}

BEGIN_MESSAGE_MAP(CVision2DLogicPanelDlg, CPropertyPage)
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_DISTANCEPP, IDC_BTN_PROJECTPL, OnButtonClicked)
END_MESSAGE_MAP()

BEGIN_EASYSIZE_MAP(CVision2DLogicPanelDlg)

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
	EASYSIZE(IDC_BTN_DISTANCEPP,ES_BORDER,ES_BORDER,IDC_BTN_DISTACNEPL,ES_KEEPSIZE,0)
	EASYSIZE(IDC_BTN_DISTACNEPL,IDC_BTN_DISTANCEPP,ES_BORDER,ES_KEEPSIZE,ES_KEEPSIZE,0)
	EASYSIZE(IDC_BTN_PROJECTPL,ES_BORDER,IDC_BTN_DISTACNEPL,ES_KEEPSIZE,ES_KEEPSIZE,0)
	EASYSIZE(IDC_BTN_INTERSECTIONLL,ES_BORDER,IDC_BTN_PROJECTPL,ES_KEEPSIZE,ES_KEEPSIZE,0)
	EASYSIZE(IDC_BTN_ANGLELL,IDC_BTN_INTERSECTIONLL,IDC_BTN_DISTACNEPL,ES_KEEPSIZE,ES_KEEPSIZE,0)
	/*EASYSIZE(IDC_BTN_NINECALI,ES_BORDER,ES_BORDER,IDC_BTN_NINECALIREALLY,ES_KEEPSIZE,0)
	EASYSIZE(IDC_BTN_NINECALIREALLY,IDC_BTN_NINECALI,ES_BORDER,ES_KEEPSIZE,ES_KEEPSIZE,0)*/
END_EASYSIZE_MAP
// CVision2DLogicPanelDlg 消息处理程序

BOOL CVision2DLogicPanelDlg::OnInitDialog()
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

BOOL CVision2DLogicPanelDlg::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CPropertyPage::Create(lpszTemplateName, pParentWnd);
}

HBRUSH CVision2DLogicPanelDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return m_brushBk;
}

void CVision2DLogicPanelDlg::OnSize(UINT nType, int cx, int cy)
{
	CPropertyPage::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	UPDATE_EASYSIZE;
}

void CVision2DLogicPanelDlg::InitAllControl()
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

void CVision2DLogicPanelDlg::InitBtnControl()
{
	try
	{
		//2D Logic button
		m_btnDistancePP.SetIcon(IDI_ICON_LOGIC) ;
		m_btnDistancePP.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnDistancePP.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnDistancePP.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnDistancePP.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnDistancePP.SetRounded(TRUE) ;

		m_btnDistancePL.SetIcon(IDI_ICON_LOGIC) ;
		m_btnDistancePL.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnDistancePL.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnDistancePL.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnDistancePL.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnDistancePL.SetRounded(TRUE) ;

		m_btnProjectPL.SetIcon(IDI_ICON_LOGIC) ;
		m_btnProjectPL.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnProjectPL.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnProjectPL.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnProjectPL.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnProjectPL.SetRounded(TRUE) ;

		m_btnIntersectionLL.SetIcon(IDI_ICON_LOGIC) ;
		m_btnIntersectionLL.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnIntersectionLL.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnIntersectionLL.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnIntersectionLL.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnIntersectionLL.SetRounded(TRUE) ;

		m_btnAngleLL.SetIcon(IDI_ICON_LOGIC) ;
		m_btnAngleLL.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnAngleLL.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnAngleLL.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnAngleLL.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnAngleLL.SetRounded(TRUE) ;
	}
	catch (...)
	{
	}
}

void CVision2DLogicPanelDlg::OnButtonClicked(UINT uBtnId)
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		if (!pDlg->m_bWorkFlowAddTool)
			return ;

		CString strName(_T("")) ;
		int nCurWorkFlowDlg = pDlg->m_tabWorkFlowDlg.GetCurSel() ;
		CWorkFlowDlg *pCurWorkFlowDlg = pDlg->m_projectData.m_mgWorkFlowDlg.GetWorkFlowDlgById(nCurWorkFlowDlg)->pWorkFlowDlg ;

		switch (uBtnId)
		{
		case IDC_BTN_DISTANCEPP:
			{
				strName.Format(_T("(ID%d)点到点距离"),pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ListWorkFlow.AddString(strName,pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_LOGIC));
				//创建点到点距离工具

				break;
			}
		case IDC_BTN_DISTACNEPL:
			{
				strName.Format(_T("(ID%d)点到线距离") ,pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ListWorkFlow.AddString(strName,pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_LOGIC));
				//创建点到线距离工具

				break;
			}
		case IDC_BTN_PROJECTPL:
			{
				strName.Format(_T("(ID%d)点投影到线"),pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ListWorkFlow.AddString(strName,pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_LOGIC));
				//创建点投影到线工具

				break;
			}
		case IDC_BTN_INTERSECTIONLL:
			{
				strName.Format(_T("(ID%d)线线相交"),pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ListWorkFlow.AddString(strName,pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_LOGIC));
				//创建线线相交工具

				break;
			}
		case IDC_BTN_ANGLELL:
			{
				strName.Format(_T("(ID%d)线线夹角"),pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ListWorkFlow.AddString(strName,pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_LOGIC));
				//创建线线夹角工具

				break;
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