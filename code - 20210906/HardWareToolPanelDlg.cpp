// HardWareToolPanelDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VisionProject.h"
#include "HardWareToolPanelDlg.h"
#include "afxdialogex.h"
#include "VisionProjectDlg.h"

// CHardWareToolPanelDlg �Ի���
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(CHardWareToolPanelDlg, CPropertyPage)

CHardWareToolPanelDlg::CHardWareToolPanelDlg()
	: CPropertyPage(CHardWareToolPanelDlg::IDD)
{
}

CHardWareToolPanelDlg::~CHardWareToolPanelDlg()
{
}

void CHardWareToolPanelDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_2DCAMERA, m_btn2DCamera);
	DDX_Control(pDX, IDC_BTN_2DLED, m_btnLed);
	/*DDX_Control(pDX, IDC_BTN_LOTSLED, m_btnLotsLed);
	DDX_Control(pDX, IDC_BTN_CSTLED, m_btnCstLed);*/
}

BEGIN_MESSAGE_MAP(CHardWareToolPanelDlg, CPropertyPage)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_2DCAMERA, IDC_BTN_2DLED, OnButtonClicked)
END_MESSAGE_MAP()

BEGIN_EASYSIZE_MAP(CHardWareToolPanelDlg)

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
	EASYSIZE(IDC_BTN_HALCONCAMERA,ES_BORDER,ES_BORDER,ES_KEEPSIZE,ES_KEEPSIZE,0)
	/*EASYSIZE(IDC_BTN_NINECALI,ES_BORDER,ES_BORDER,IDC_BTN_NINECALIREALLY,ES_KEEPSIZE,0)
	EASYSIZE(IDC_BTN_NINECALIREALLY,IDC_BTN_NINECALI,ES_BORDER,ES_KEEPSIZE,ES_KEEPSIZE,0)*/
END_EASYSIZE_MAP

// CHardWareToolPanelDlg ��Ϣ�������

BOOL CHardWareToolPanelDlg::OnInitDialog()
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

BOOL CHardWareToolPanelDlg::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
	// TODO: �ڴ����ר�ô����/����û���

	return CPropertyPage::Create(lpszTemplateName, pParentWnd);
}

void CHardWareToolPanelDlg::OnSize(UINT nType, int cx, int cy)
{
	CPropertyPage::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	UPDATE_EASYSIZE;
}

void CHardWareToolPanelDlg::InitAllControl()
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

void CHardWareToolPanelDlg::InitBtnControl()
{
	try
	{
		//���button
		m_btn2DCamera.SetIcon(IDI_ICON_CAMERA) ;
		m_btn2DCamera.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btn2DCamera.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btn2DCamera.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btn2DCamera.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btn2DCamera.SetRounded(TRUE) ;

		//��Դbutton
		m_btnLed.SetIcon(IDI_ICON_LED) ;
		m_btnLed.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnLed.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnLed.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnLed.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnLed.SetRounded(TRUE) ;

		/*m_btnLotsLed.SetIcon(IDI_ICON_LOTSLED) ;
		m_btnLotsLed.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnLotsLed.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnLotsLed.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnLotsLed.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnLotsLed.SetRounded(TRUE) ;

		m_btnCstLed.SetIcon(IDI_ICON_CSTLED) ;
		m_btnCstLed.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnCstLed.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnCstLed.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnCstLed.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnCstLed.SetRounded(TRUE) ;*/
	}
	catch (...)
	{
	}
}

HBRUSH CHardWareToolPanelDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return m_brushBk/*hbr*/;
}

void CHardWareToolPanelDlg::OnButtonClicked(UINT uBtnId)
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
		case IDC_BTN_2DCAMERA:
			{
				//�����������
				CFlowNode *pFlowNode = new CFlowNode() ;
				pFlowNode->eFlowNodeType = E_TOOL_2DVISION_CAMERA ;
				pFlowNode->nFlowNodeID = pCurWorkFlowDlg->m_ListWorkFlow.GetCount() ;
				pFlowNode->mgrDllVisionBaseIm.DllCreateInterface(E_TOOL_2DVISION_CAMERA,(void **)&pFlowNode->pVisionBase) ;
				if (NULL == pFlowNode->pVisionBase)
				{
					AfxMessageBox(_T("�������Dll����ʧ��")) ;
					DELETE_POINT(pFlowNode) ;
					return ;
				}

				//�����ļ���
				strName.Format(_T("(ID%d)2D���"),pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
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

				//�����б�
				pCurWorkFlowDlg->m_ListWorkFlow.AddString(strName,pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_CAMERA));

				//��ӵ�����
				pCurWorkFlowDlg->m_ManageFlowNode.AddTail(pFlowNode) ;

				break;
			}
		case IDC_BTN_2DLED:
			{
				strName.Format(_T("(ID%d)��Դ") ,pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ListWorkFlow.AddString(strName,pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_LED));
				//������Դ����

				break;
			}
		//case IDC_BTN_LOTSLED:
		//	{
		//		strName.Format(_T("(ID%d)Lots��Դ"),pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
		//		pCurWorkFlowDlg->m_ListWorkFlow.AddString(strName,pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
		//		pCurWorkFlowDlg->m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_LOTSLED));
		//		//����Lots��Դ����

		//		break;
		//	}
		//case IDC_BTN_CSTLED:
		//	{
		//		strName.Format(_T("(ID%d)Cst��Դ"),pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
		//		pCurWorkFlowDlg->m_ListWorkFlow.AddString(strName,pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
		//		pCurWorkFlowDlg->m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_CSTLED));
		//		//����Cst��Դ����

		//		break;
		//	}
		default:
			break;
		}

		pDlg->m_bWorkFlowAddTool = false ;
	}
	catch (...)
	{
	}
}