// VisionSystemPanelDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VisionProject.h"
#include "VisionSystemPanelDlg.h"
#include "afxdialogex.h"
#include "VisionProjectDlg.h"

// CVisionSystemPanelDlg �Ի���
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

// CVisionSystemPanelDlg ��Ϣ�������

BEGIN_EASYSIZE_MAP(CVisionSystemPanelDlg)

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
	EASYSIZE(IDC_BTN_LUASCRIPT,ES_BORDER,ES_BORDER,ES_KEEPSIZE,ES_KEEPSIZE,0)
END_EASYSIZE_MAP

BOOL CVisionSystemPanelDlg::OnInitDialog()
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

BOOL CVisionSystemPanelDlg::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
	// TODO: �ڴ����ר�ô����/����û���

	return CPropertyPage::Create(lpszTemplateName, pParentWnd);
}

HBRUSH CVisionSystemPanelDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return m_brushBk;
}

void CVisionSystemPanelDlg::OnSize(UINT nType, int cx, int cy)
{
	CPropertyPage::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	UPDATE_EASYSIZE;
}

void CVisionSystemPanelDlg::InitAllControl()
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
				strName.Format(_T("(ID%d)Lua�ű�"),pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ListWorkFlow.AddString(strName,pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
				pCurWorkFlowDlg->m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_LUAGOBALVARIENT));
				//����Lua�ű�����

				break;
			}
		case IDC_BTN_COMMRECV:
			{
				//����ͨ�Ž��չ���
				CFlowNode *pFlowNode = new CFlowNode() ;
				pFlowNode->eFlowNodeType = E_TOOL_VISIONSYSTEM_COMMREAD ;
				pFlowNode->nFlowNodeID = pCurWorkFlowDlg->m_ListWorkFlow.GetCount() ;
				pFlowNode->mgrDllVisionBaseIm.DllCreateInterface(E_TOOL_VISIONSYSTEM_COMMREAD,(void **)&pFlowNode->pVisionBase) ;
				if (NULL == pFlowNode->pVisionBase)
				{
					AfxMessageBox(_T("ͨ�Ž��չ���Dll����ʧ��")) ;
					DELETE_POINT(pFlowNode) ;
					return ;
				}

				//�����ļ���
				strName.Format(_T("(ID%d)ͨ�Ž���"),pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
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

				//��ӵ�����
				pCurWorkFlowDlg->m_ManageFlowNode.AddTail(pFlowNode) ;

				break ;
			}
		case IDC_BTN_COMMSEND:
			{
				//����ͨ�ŷ��͹���
				CFlowNode *pFlowNode = new CFlowNode() ;
				pFlowNode->eFlowNodeType = E_TOOL_VISIONSYSTEM_COMMWRITE ;
				pFlowNode->nFlowNodeID = pCurWorkFlowDlg->m_ListWorkFlow.GetCount() ;
				pFlowNode->mgrDllVisionBaseIm.DllCreateInterface(E_TOOL_VISIONSYSTEM_COMMWRITE,(void **)&pFlowNode->pVisionBase) ;
				if (NULL == pFlowNode->pVisionBase)
				{
					AfxMessageBox(_T("ͨ�ŷ��͹���Dll����ʧ��")) ;
					DELETE_POINT(pFlowNode) ;
					return ;
				}

				//�����ļ���
				strName.Format(_T("(ID%d)ͨ�ŷ���"),pCurWorkFlowDlg->m_ListWorkFlow.GetCount()) ;
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

				//��ӵ�����
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