// Vision2DLogicPanelDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VisionProject.h"
#include "Vision2DLogicPanelDlg.h"
#include "afxdialogex.h"
#include "VisionProjectDlg.h"

// CVision2DLogicPanelDlg �Ի���
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
	EASYSIZE(IDC_BTN_DISTANCEPP,ES_BORDER,ES_BORDER,IDC_BTN_DISTACNEPL,ES_KEEPSIZE,0)
	EASYSIZE(IDC_BTN_DISTACNEPL,IDC_BTN_DISTANCEPP,ES_BORDER,ES_KEEPSIZE,ES_KEEPSIZE,0)
	EASYSIZE(IDC_BTN_PROJECTPL,ES_BORDER,IDC_BTN_DISTACNEPL,ES_KEEPSIZE,ES_KEEPSIZE,0)
	EASYSIZE(IDC_BTN_INTERSECTIONLL,ES_BORDER,IDC_BTN_PROJECTPL,ES_KEEPSIZE,ES_KEEPSIZE,0)
	EASYSIZE(IDC_BTN_ANGLELL,IDC_BTN_INTERSECTIONLL,IDC_BTN_DISTACNEPL,ES_KEEPSIZE,ES_KEEPSIZE,0)
	/*EASYSIZE(IDC_BTN_NINECALI,ES_BORDER,ES_BORDER,IDC_BTN_NINECALIREALLY,ES_KEEPSIZE,0)
	EASYSIZE(IDC_BTN_NINECALIREALLY,IDC_BTN_NINECALI,ES_BORDER,ES_KEEPSIZE,ES_KEEPSIZE,0)*/
END_EASYSIZE_MAP
// CVision2DLogicPanelDlg ��Ϣ�������

BOOL CVision2DLogicPanelDlg::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	INIT_EASYSIZE;

	m_brushBk.CreateSolidBrush(SYSTEM_BK_COLOR);

	ModifyStyle(0, WS_SIZEBOX);

	InitAllControl() ;

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

BOOL CVision2DLogicPanelDlg::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
	// TODO: �ڴ����ר�ô����/����û���

	return CPropertyPage::Create(lpszTemplateName, pParentWnd);
}

HBRUSH CVision2DLogicPanelDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return m_brushBk;
}

void CVision2DLogicPanelDlg::OnSize(UINT nType, int cx, int cy)
{
	CPropertyPage::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	UPDATE_EASYSIZE;
}

void CVision2DLogicPanelDlg::InitAllControl()
{
	try
	{
		//��ʼ��button�ؼ�
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
				strName.Format(_T("(ID%d)�㵽�����"),pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ListWorkFlow.AddString(strName,pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_LOGIC));
				//�����㵽����빤��

				break;
			}
		case IDC_BTN_DISTACNEPL:
			{
				strName.Format(_T("(ID%d)�㵽�߾���") ,pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ListWorkFlow.AddString(strName,pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_LOGIC));
				//�����㵽�߾��빤��

				break;
			}
		case IDC_BTN_PROJECTPL:
			{
				strName.Format(_T("(ID%d)��ͶӰ����"),pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ListWorkFlow.AddString(strName,pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_LOGIC));
				//������ͶӰ���߹���

				break;
			}
		case IDC_BTN_INTERSECTIONLL:
			{
				strName.Format(_T("(ID%d)�����ཻ"),pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ListWorkFlow.AddString(strName,pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_LOGIC));
				//���������ཻ����

				break;
			}
		case IDC_BTN_ANGLELL:
			{
				strName.Format(_T("(ID%d)���߼н�"),pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ListWorkFlow.AddString(strName,pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_LOGIC));
				//�������߼нǹ���

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