// Vision2DPanelDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VisionProject.h"
#include "Vision2DPanelDlg.h"
#include "afxdialogex.h"
#include "VisionProjectDlg.h"

// CVision2DPanelDlg �Ի���
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
// CVision2DPanelDlg ��Ϣ�������

BOOL CVision2DPanelDlg::OnInitDialog()
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

BOOL CVision2DPanelDlg::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
	// TODO: �ڴ����ר�ô����/����û���

	return CPropertyPage::Create(lpszTemplateName, pParentWnd);
}

HBRUSH CVision2DPanelDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return m_brushBk;
}

void CVision2DPanelDlg::OnSize(UINT nType, int cx, int cy)
{
	CPropertyPage::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	UPDATE_EASYSIZE;
}

void CVision2DPanelDlg::InitAllControl()
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
				//������׼��״ģ�幤��(����shapeModelTooldll)
				CFlowNode *pFlowNode = new CFlowNode() ;
				pFlowNode->eFlowNodeType = E_TOOL_2DVISION_SHAPEMODEL ;
				pFlowNode->nFlowNodeID = pCurWorkFlowDlg->m_ManageFlowNode.GetFlowNodeListSize() ;
				pFlowNode->mgrDllVisionBaseIm.DllCreateInterface((int)E_TOOL_2DVISION_SHAPEMODEL,(void **)&pFlowNode->pVisionBase) ;

				if (NULL == pFlowNode->pVisionBase)
				{
					AfxMessageBox(_T("��׼ģ�幤��Dll����ʧ��")) ;
					DELETE_POINT(pFlowNode) ;
					return ;
				}

				//�����ļ���
				strName.Format(_T("(ID%d)��׼��״ģ��"),pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
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
				pCurWorkFlowDlg->m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_SHAPEMODEL));

				//��ӵ�����
				pCurWorkFlowDlg->m_ManageFlowNode.AddTail(pFlowNode) ;
				break;
			}
		case IDC_BTN_SCALESHAPEMODEL:
			{
				strName.Format(_T("(ID%d)������״ģ��") ,pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ListWorkFlow.AddString(strName,pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_SCALESHAPEMODEL));
				//����������״ģ�幤��

				break;
			}
		case IDC_BTN_NCCMODEL:
			{
				strName.Format(_T("(ID%d)NCCģ��"),pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ListWorkFlow.AddString(strName,pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_NCCMODEL));
				//����NCCģ�幤��

				break;
			}
		case IDC_BTN_CONTOURMODEL:
			{
				strName.Format(_T("(ID%d)��׼����ģ��"),pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ListWorkFlow.AddString(strName,pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_CONTOURMODEL));
				//������׼����ģ�幤��

				break;
			}
		case IDC_BTN_SCALECONTOURMODEL:
			{
				strName.Format(_T("(ID%d)��������ģ��"),pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ListWorkFlow.AddString(strName,pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_SCALECONTOURMODEL));
				//������������ģ�幤��

				break;
			}
		case IDC_BTN_FITLINE:
			{
				//�������߹���(����fitLineTooldll)
				CFlowNode *pFlowNode = new CFlowNode() ;
				pFlowNode->eFlowNodeType = E_TOOL_2DVISION_FITLINE ;
				pFlowNode->nFlowNodeID = pCurWorkFlowDlg->m_ManageFlowNode.GetFlowNodeListSize() ;
				pFlowNode->mgrDllVisionBaseIm.DllCreateInterface((int)E_TOOL_2DVISION_FITLINE,(void **)&pFlowNode->pVisionBase) ;

				if (NULL == pFlowNode->pVisionBase)
				{
					AfxMessageBox(_T("���߹���Dll����ʧ��")) ;
					DELETE_POINT(pFlowNode) ;
					return ;
				}

				//�����ļ���
				strName.Format(_T("(ID%d)����"),pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
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
				pCurWorkFlowDlg->m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_FITLINE));
				//��ӵ�����
				pCurWorkFlowDlg->m_ManageFlowNode.AddTail(pFlowNode) ;

				break;
			}
		case IDC_BTN_FITCIRCLE:
			{
				strName.Format(_T("(ID%d)��Բ"),pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ListWorkFlow.AddString(strName,pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_FITCIRCLE));
				//������Բ����

				break;
			}
		case IDC_BTN_FITARC:
			{
				strName.Format(_T("(ID%d)�һ�"),pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ListWorkFlow.AddString(strName,pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_FITARC));
				//�����һ�����

				break;
			}
		case IDC_BTN_BLOB:
			{
				strName.Format(_T("(ID%d)Blob��ȡ"),pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ListWorkFlow.AddString(strName,pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_BLOB));
				//����Blob��ȡ����

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