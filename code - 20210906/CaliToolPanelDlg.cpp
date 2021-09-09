// CaliToolPanelDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VisionProject.h"
#include "CaliToolPanelDlg.h"
#include "afxdialogex.h"
#include "VisionProjectDlg.h"

// CCaliToolPanelDlg �Ի���
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(CCaliToolPanelDlg, CPropertyPage)

CCaliToolPanelDlg::CCaliToolPanelDlg()
	: CPropertyPage(CCaliToolPanelDlg::IDD)
{
}

CCaliToolPanelDlg::~CCaliToolPanelDlg()
{
}

void CCaliToolPanelDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_NINECALI, m_btnNineCali);
	DDX_Control(pDX, IDC_BTN_NINECALIREALLY, m_btnNineCaliReally);
}

BEGIN_MESSAGE_MAP(CCaliToolPanelDlg, CPropertyPage)
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_NINECALI, IDC_BTN_NINECALIREALLY, OnButtonClicked)
END_MESSAGE_MAP()

BEGIN_EASYSIZE_MAP(CCaliToolPanelDlg)

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
	EASYSIZE(IDC_BTN_NINECALI,ES_BORDER,ES_BORDER,IDC_BTN_NINECALIREALLY,ES_KEEPSIZE,0)
	EASYSIZE(IDC_BTN_NINECALIREALLY,IDC_BTN_NINECALI,ES_BORDER,ES_KEEPSIZE,ES_KEEPSIZE,0)
END_EASYSIZE_MAP

// CCaliToolPanelDlg ��Ϣ�������

BOOL CCaliToolPanelDlg::OnInitDialog()
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

BOOL CCaliToolPanelDlg::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
	// TODO: �ڴ����ר�ô����/����û���

	return CPropertyPage::Create(lpszTemplateName, pParentWnd);
}

HBRUSH CCaliToolPanelDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return m_brushBk;
}

void CCaliToolPanelDlg::OnSize(UINT nType, int cx, int cy)
{
	CPropertyPage::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	UPDATE_EASYSIZE;
}

void CCaliToolPanelDlg::InitAllControl()
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

void CCaliToolPanelDlg::InitBtnControl()
{
	try
	{
		m_btnNineCali.SetIcon(IDI_ICON_NINECALI) ;
		m_btnNineCali.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnNineCali.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnNineCali.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnNineCali.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnNineCali.SetRounded(TRUE) ;

		m_btnNineCaliReally.SetIcon(IDI_ICON_NINECALIREALLY) ;
		m_btnNineCaliReally.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnNineCaliReally.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnNineCaliReally.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnNineCaliReally.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnNineCaliReally.SetRounded(TRUE) ;
	}
	catch (...)
	{
	}
}

void CCaliToolPanelDlg::OnButtonClicked(UINT uBtnId)
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
		case IDC_BTN_NINECALI:
			{
				strName.Format(_T("(ID%d)9��궨"),pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ListWorkFlow.AddString(strName,pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_NINECALI));
				//����9��궨����

				break;
			}
		case IDC_BTN_NINECALIREALLY:
			{
				strName.Format(_T("(ID%d)9��ʵʱ�궨") ,pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ListWorkFlow.AddString(strName,pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_NINECALIREALLY));
				//����9��ʵʱ�궨����

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