// Vision2DPanelDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "VisionProject.h"
#include "Vision2DPanelDlg.h"
#include "afxdialogex.h"
#include "VisionProjectDlg.h"

// CVision2DPanelDlg 对话框
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(CVision2DPanelDlg, CPropertyPage)

CVision2DPanelDlg::CVision2DPanelDlg()
	: CPropertyPage(CVision2DPanelDlg::IDD)
{
}

CVision2DPanelDlg::~CVision2DPanelDlg()
{
}

void CVision2DPanelDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_SHAPEMODEL, m_btnShapeModel);
	DDX_Control(pDX, IDC_BTN_SCALESHAPEMODEL, m_btnScaleShapeModel);
	DDX_Control(pDX, IDC_BTN_NCCMODEL, m_btnNccModel);
	DDX_Control(pDX, IDC_BTN_CONTOURMODEL, m_btnContourModel);
	DDX_Control(pDX, IDC_BTN_SCALECONTOURMODEL, m_btnScaleContourModel);
	DDX_Control(pDX, IDC_BTN_FITLINE, m_btnFitLine);
	DDX_Control(pDX, IDC_BTN_FITCIRCLE, m_btnFitCircle);
	DDX_Control(pDX, IDC_BTN_FITARC, m_btnFitArc);
	DDX_Control(pDX, IDC_BTN_BLOB, m_btnBlob);
}

BEGIN_MESSAGE_MAP(CVision2DPanelDlg, CPropertyPage)
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_SHAPEMODEL, IDC_BTN_BLOB, OnButtonClicked)
END_MESSAGE_MAP()

BEGIN_EASYSIZE_MAP(CVision2DPanelDlg)

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
	EASYSIZE(IDC_BTN_SHAPEMODEL,ES_BORDER,ES_BORDER,IDC_BTN_SCALESHAPEMODEL,ES_KEEPSIZE,0)
	EASYSIZE(IDC_BTN_SCALESHAPEMODEL,IDC_BTN_SHAPEMODEL,ES_BORDER,IDC_BTN_NCCMODEL,ES_KEEPSIZE,0)
	EASYSIZE(IDC_BTN_NCCMODEL,IDC_BTN_SCALESHAPEMODEL,ES_BORDER,ES_KEEPSIZE,ES_KEEPSIZE,0)
	EASYSIZE(IDC_BTN_CONTOURMODEL,ES_BORDER,IDC_BTN_SHAPEMODEL,IDC_BTN_SCALECONTOURMODEL,ES_KEEPSIZE,0)
	EASYSIZE(IDC_BTN_SCALECONTOURMODEL,IDC_BTN_CONTOURMODEL,IDC_BTN_SCALECONTOURMODEL,ES_KEEPSIZE,ES_KEEPSIZE,0)
	EASYSIZE(IDC_BTN_FITLINE,ES_BORDER,IDC_BTN_CONTOURMODEL,IDC_BTN_FITCIRCLE,ES_KEEPSIZE,0)
	EASYSIZE(IDC_BTN_FITCIRCLE,IDC_BTN_FITLINE,IDC_BTN_SCALECONTOURMODEL,IDC_BTN_FITARC,ES_KEEPSIZE,0)
	EASYSIZE(IDC_BTN_FITARC,IDC_BTN_FITCIRCLE,IDC_BTN_NCCMODEL,ES_KEEPSIZE,ES_KEEPSIZE,0)
	EASYSIZE(IDC_BTN_BLOB,ES_BORDER,IDC_BTN_FITLINE,ES_KEEPSIZE,ES_KEEPSIZE,0)
	/*EASYSIZE(IDC_BTN_NINECALI,ES_BORDER,ES_BORDER,IDC_BTN_NINECALIREALLY,ES_KEEPSIZE,0)
	EASYSIZE(IDC_BTN_NINECALIREALLY,IDC_BTN_NINECALI,ES_BORDER,ES_KEEPSIZE,ES_KEEPSIZE,0)*/
END_EASYSIZE_MAP
// CVision2DPanelDlg 消息处理程序

BOOL CVision2DPanelDlg::OnInitDialog()
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

BOOL CVision2DPanelDlg::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CPropertyPage::Create(lpszTemplateName, pParentWnd);
}

HBRUSH CVision2DPanelDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return m_brushBk;
}

void CVision2DPanelDlg::OnSize(UINT nType, int cx, int cy)
{
	CPropertyPage::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	UPDATE_EASYSIZE;
}

void CVision2DPanelDlg::InitAllControl()
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

void CVision2DPanelDlg::InitBtnControl()
{
	try
	{
		//2D button
		m_btnShapeModel.SetIcon(IDI_ICON_SHAPEMODEL) ;
		m_btnShapeModel.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnShapeModel.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnShapeModel.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnShapeModel.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnShapeModel.SetRounded(TRUE) ;

		m_btnScaleShapeModel.SetIcon(IDI_ICON_SCALESHAPEMODEL) ;
		m_btnScaleShapeModel.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnScaleShapeModel.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnScaleShapeModel.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnScaleShapeModel.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnScaleShapeModel.SetRounded(TRUE) ;

		m_btnNccModel.SetIcon(IDI_ICON_NCCMODEL) ;
		m_btnNccModel.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnNccModel.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnNccModel.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnNccModel.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnNccModel.SetRounded(TRUE) ;

		m_btnContourModel.SetIcon(IDI_ICON_CONTOURMODEL) ;
		m_btnContourModel.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnContourModel.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnContourModel.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnContourModel.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnContourModel.SetRounded(TRUE) ;

		m_btnScaleContourModel.SetIcon(IDI_ICON_SCALECONTOURMODEL) ;
		m_btnScaleContourModel.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnScaleContourModel.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnScaleContourModel.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnScaleContourModel.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnScaleContourModel.SetRounded(TRUE) ;

		m_btnFitLine.SetIcon(IDI_ICON_FITLINE) ;
		m_btnFitLine.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnFitLine.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnFitLine.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnFitLine.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnFitLine.SetRounded(TRUE) ;

		m_btnFitCircle.SetIcon(IDI_ICON_FITCIRCLE) ;
		m_btnFitCircle.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnFitCircle.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnFitCircle.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnFitCircle.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnFitCircle.SetRounded(TRUE) ;

		m_btnFitArc.SetIcon(IDI_ICON_FITARC) ;
		m_btnFitArc.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnFitArc.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnFitArc.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnFitArc.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnFitArc.SetRounded(TRUE) ;

		m_btnBlob.SetIcon(IDI_ICON_BLOB) ;
		m_btnBlob.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnBlob.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnBlob.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnBlob.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnBlob.SetRounded(TRUE) ;
	}
	catch (...)
	{
	}
}

void CVision2DPanelDlg::OnButtonClicked(UINT uBtnId)
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
		case IDC_BTN_SHAPEMODEL:
			{
				//创建标准形状模板工具(加载shapeModelTooldll)
				CFlowNode *pFlowNode = new CFlowNode() ;
				pFlowNode->eFlowNodeType = E_TOOL_2DVISION_SHAPEMODEL ;
				pFlowNode->nFlowNodeID = pCurWorkFlowDlg->m_ManageFlowNode.GetFlowNodeListSize() ;
				pFlowNode->mgrDllVisionBaseIm.DllCreateInterface((int)E_TOOL_2DVISION_SHAPEMODEL,(void **)&pFlowNode->pVisionBase) ;

				if (NULL == pFlowNode->pVisionBase)
				{
					AfxMessageBox(_T("标准模板工具Dll加载失败")) ;
					DELETE_POINT(pFlowNode) ;
					return ;
				}

				//创建文件夹
				strName.Format(_T("(ID%d)标准形状模板"),pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
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

				//更新列表
				pCurWorkFlowDlg->m_ListWorkFlow.AddString(strName,pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_SHAPEMODEL));

				//添加到链表
				pCurWorkFlowDlg->m_ManageFlowNode.AddTail(pFlowNode) ;
				break;
			}
		case IDC_BTN_SCALESHAPEMODEL:
			{
				strName.Format(_T("(ID%d)缩放形状模板") ,pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ListWorkFlow.AddString(strName,pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_SCALESHAPEMODEL));
				//创建缩放形状模板工具

				break;
			}
		case IDC_BTN_NCCMODEL:
			{
				strName.Format(_T("(ID%d)NCC模板"),pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ListWorkFlow.AddString(strName,pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_NCCMODEL));
				//创建NCC模板工具

				break;
			}
		case IDC_BTN_CONTOURMODEL:
			{
				strName.Format(_T("(ID%d)标准轮廓模板"),pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ListWorkFlow.AddString(strName,pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_CONTOURMODEL));
				//创建标准轮廓模板工具

				break;
			}
		case IDC_BTN_SCALECONTOURMODEL:
			{
				strName.Format(_T("(ID%d)缩放轮廓模板"),pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ListWorkFlow.AddString(strName,pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_SCALECONTOURMODEL));
				//创建缩放轮廓模板工具

				break;
			}
		case IDC_BTN_FITLINE:
			{
				//创建找线工具(加载fitLineTooldll)
				CFlowNode *pFlowNode = new CFlowNode() ;
				pFlowNode->eFlowNodeType = E_TOOL_2DVISION_FITLINE ;
				pFlowNode->nFlowNodeID = pCurWorkFlowDlg->m_ManageFlowNode.GetFlowNodeListSize() ;
				pFlowNode->mgrDllVisionBaseIm.DllCreateInterface((int)E_TOOL_2DVISION_FITLINE,(void **)&pFlowNode->pVisionBase) ;

				if (NULL == pFlowNode->pVisionBase)
				{
					AfxMessageBox(_T("找线工具Dll加载失败")) ;
					DELETE_POINT(pFlowNode) ;
					return ;
				}

				//创建文件夹
				strName.Format(_T("(ID%d)找线"),pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
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

				//更新列表
				pCurWorkFlowDlg->m_ListWorkFlow.AddString(strName,pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_FITLINE));
				//添加到链表
				pCurWorkFlowDlg->m_ManageFlowNode.AddTail(pFlowNode) ;

				break;
			}
		case IDC_BTN_FITCIRCLE:
			{
				strName.Format(_T("(ID%d)找圆"),pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ListWorkFlow.AddString(strName,pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_FITCIRCLE));
				//创建找圆工具

				break;
			}
		case IDC_BTN_FITARC:
			{
				strName.Format(_T("(ID%d)找弧"),pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ListWorkFlow.AddString(strName,pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_FITARC));
				//创建找弧工具

				break;
			}
		case IDC_BTN_BLOB:
			{
				strName.Format(_T("(ID%d)Blob提取"),pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ListWorkFlow.AddString(strName,pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_BLOB));
				//创建Blob提取工具

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