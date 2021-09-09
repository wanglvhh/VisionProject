// WorkFlowDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VisionProject.h"
#include "WorkFlowDlg.h"
#include "afxdialogex.h"
#include "VisionProjectDlg.h"
#include "ParaConnectDlg.h"
#include "CameraConnectDlg.h"
#include "CommConnectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// CWorkFlowDlg �Ի���

IMPLEMENT_DYNAMIC(CWorkFlowDlg, CDialogEx)

CWorkFlowDlg::CWorkFlowDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWorkFlowDlg::IDD, pParent)
{
	m_strWorkFlowDlgName = _T("") ;
}

CWorkFlowDlg::~CWorkFlowDlg()
{
}

void CWorkFlowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_WORKFLOW, m_ListWorkFlow);
}

BEGIN_MESSAGE_MAP(CWorkFlowDlg, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_TOOL_ADD, &CWorkFlowDlg::OnToolAdd)
	ON_COMMAND(ID_TOOL_DEL, &CWorkFlowDlg::OnToolDel)
	ON_COMMAND(ID_TOOL_MOVEUP, &CWorkFlowDlg::OnToolMoveup)
	ON_COMMAND(ID_TOOL_MOVEDOWN, &CWorkFlowDlg::OnToolMovedown)
	ON_COMMAND(ID_PARACONNECT, &CWorkFlowDlg::OnParaconnect)
	ON_LBN_DBLCLK(IDC_LIST_WORKFLOW, &CWorkFlowDlg::OnLbnDblclkListWorkflow)
	ON_COMMAND(ID_ADD_SCRIPT, &CWorkFlowDlg::OnAddScript)
	ON_COMMAND(ID_EDIT_SCRIPT, &CWorkFlowDlg::OnEditScript)
END_MESSAGE_MAP()

// CWorkFlowDlg ��Ϣ�������

BEGIN_EASYSIZE_MAP(CWorkFlowDlg)
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
	EASYSIZE(IDC_LIST_WORKFLOW,ES_BORDER,ES_BORDER,ES_BORDER,ES_BORDER,0)
END_EASYSIZE_MAP

BOOL CWorkFlowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	INIT_EASYSIZE;

	InitImageList() ;

	m_brushBk.CreateSolidBrush(SYSTEM_BK_COLOR);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

HBRUSH CWorkFlowDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if(nCtlColor == CTLCOLOR_LISTBOX ||nCtlColor == CTLCOLOR_EDIT)
	{
		//pDC->SetBkColor(SYSTEM_WHITE) ;
		pDC->SetTextColor(SYSTEM_BLUE);//����ɫ
	}

	/*switch(pWnd->GetDlgCtrlID())
	{
	case IDC_LIST_WORKFLOW:
		{
			pDC->SetTextColor(SYSTEM_BLUE) ;
			pDC->SetBkColor(SYSTEM_BK_COLOR) ;
			return (HBRUSH)m_brushBk ;
		}
	default:
		break;
	}*/

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return m_brushBk;
}

void CWorkFlowDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	UPDATE_EASYSIZE;
}

void CWorkFlowDlg::InitImageList()
{
	try
	{
		BOOL	bRetValue = FALSE;
		HICON	hIcon = NULL;

		// Create image list
		bRetValue = m_ImageList.Create(32, 32, ILC_COLOR32 | ILC_MASK, 1, 1);
		ASSERT(bRetValue == TRUE);

		m_ListWorkFlow.SetImageList(&m_ImageList) ;
		m_ListWorkFlow.MoveTop(1) ;
	}
	catch (...)
	{
	}
}

void CWorkFlowDlg::ReplaceImageList(CFlowNode *pSourceFlowNode,CFlowNode *pDstFlowNode)
{
	try
	{
		if (NULL == pSourceFlowNode || NULL == pDstFlowNode) return ;

		HICON hSourceFlowNodeICO,hDisFlowNodeICO ;

		switch((int)pSourceFlowNode->eFlowNodeType)
		{
		case (int)E_TOOL_2DVISION_CAMERA:
			{
				hSourceFlowNodeICO = AfxGetApp()->LoadIcon(IDI_ICON_CAMERA);
				break;
			}
		case (int)E_TOOL_2DVISION_SHAPEMODEL:
			{
				hSourceFlowNodeICO = AfxGetApp()->LoadIcon(IDI_ICON_SHAPEMODEL);
				break;
			}
		case (int)E_TOOL_2DVISION_FITLINE:
			{
				hSourceFlowNodeICO = AfxGetApp()->LoadIcon(IDI_ICON_FITLINE);
				break;
			}
		case (int)E_TOOL_VISIONSYSTEM_COMMREAD:
			{
				hSourceFlowNodeICO = AfxGetApp()->LoadIcon(IDI_ICON_READ);
				break;
			}
		case (int)E_TOOL_VISIONSYSTEM_COMMWRITE:
			{
				hSourceFlowNodeICO = AfxGetApp()->LoadIcon(IDI_ICON_SEND);
				break;
			}
		default:
			break ;
		}

		switch((int)pDstFlowNode->eFlowNodeType)
		{
		case (int)E_TOOL_2DVISION_CAMERA:
			{
				hDisFlowNodeICO = AfxGetApp()->LoadIcon(IDI_ICON_CAMERA);
				break;
			}
		case (int)E_TOOL_2DVISION_SHAPEMODEL:
			{
				hDisFlowNodeICO = AfxGetApp()->LoadIcon(IDI_ICON_SHAPEMODEL);
				break;
			}
		case (int)E_TOOL_2DVISION_FITLINE:
			{
				hDisFlowNodeICO = AfxGetApp()->LoadIcon(IDI_ICON_FITLINE);
				break;
			}
		case (int)E_TOOL_VISIONSYSTEM_COMMREAD:
			{
				hDisFlowNodeICO = AfxGetApp()->LoadIcon(IDI_ICON_READ);
				break;
			}
		case (int)E_TOOL_VISIONSYSTEM_COMMWRITE:
			{
				hDisFlowNodeICO = AfxGetApp()->LoadIcon(IDI_ICON_SEND);
				break;
			}
		default:
			break ;
		}

		m_ImageList.Replace(pSourceFlowNode->nFlowNodeID,hDisFlowNodeICO) ;
		m_ImageList.Replace(pDstFlowNode->nFlowNodeID,hSourceFlowNodeICO) ;
	}
	catch (...)
	{
	}
}

void CWorkFlowDlg::UpdateList()
{
	try
	{
		m_ListWorkFlow.ResetContent() ;

		for (int i = 0 ;i < m_ManageFlowNode.GetFlowNodeListSize();i++)
		{
			CFlowNode *pFlowNode = m_ManageFlowNode.GetFlowNodeById(i) ;
			CString strName(_T("")) ;
			switch((int)pFlowNode->eFlowNodeType)
			{
			case (int)E_TOOL_2DVISION_CAMERA:
				{
					strName.Format(_T("(ID%d)2D���"),i) ;

					if (NULL == pFlowNode->pVisionBase)
					{
						pFlowNode->mgrDllVisionBaseIm.DllCreateInterface(E_TOOL_2DVISION_CAMERA,(void **)&pFlowNode->pVisionBase) ;
						if (NULL == pFlowNode->pVisionBase)continue;
						//�����б�
						m_ListWorkFlow.AddString(strName,i) ;
						m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_CAMERA));
					}

					break;
				}
			case (int)E_TOOL_2DVISION_SHAPEMODEL:
				{
					strName.Format(_T("(ID%d)��׼��״ģ��"),i) ;

					if (NULL == pFlowNode->pVisionBase)
					{
						pFlowNode->mgrDllVisionBaseIm.DllCreateInterface((int)E_TOOL_2DVISION_SHAPEMODEL,(void **)&pFlowNode->pVisionBase) ;
						if (NULL == pFlowNode->pVisionBase)continue;
						//�����б�
						m_ListWorkFlow.AddString(strName,i) ;
						m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_SHAPEMODEL));
					}

					break;
				}
			case (int)E_TOOL_2DVISION_FITLINE:
				{
					strName.Format(_T("(ID%d)����"),i) ;

					if (NULL == pFlowNode->pVisionBase)
					{
						pFlowNode->mgrDllVisionBaseIm.DllCreateInterface((int)E_TOOL_2DVISION_FITLINE,(void **)&pFlowNode->pVisionBase) ;
						if (NULL == pFlowNode->pVisionBase)continue;
						//�����б�
						m_ListWorkFlow.AddString(strName,i) ;
						m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_FITLINE));
					}

					break ;
				}
			case (int)E_TOOL_VISIONSYSTEM_COMMREAD:
				{
					strName.Format(_T("(ID%d)ͨ�Ž���"),i) ;

					if (NULL == pFlowNode->pVisionBase)
					{
						pFlowNode->mgrDllVisionBaseIm.DllCreateInterface((int)E_TOOL_VISIONSYSTEM_COMMREAD,(void **)&pFlowNode->pVisionBase) ;
						if (NULL == pFlowNode->pVisionBase)continue;
						//�����б�
						m_ListWorkFlow.AddString(strName,i) ;
						m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_READ));
					}

					break ;
				}
			case (int)E_TOOL_VISIONSYSTEM_COMMWRITE:
				{
					strName.Format(_T("(ID%d)ͨ�ŷ���"),i) ;

					if (NULL == pFlowNode->pVisionBase)
					{
						pFlowNode->mgrDllVisionBaseIm.DllCreateInterface((int)E_TOOL_VISIONSYSTEM_COMMWRITE,(void **)&pFlowNode->pVisionBase) ;
						if (NULL == pFlowNode->pVisionBase)continue;
						//�����б�
						m_ListWorkFlow.AddString(strName,i) ;
						m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_SEND));
					}

					break ;
				}
			default:
				break;
			}

			//��ȡInput

			//��ʼ��
		}
	}
	catch (...)
	{
	}
}

void CWorkFlowDlg::ReUpdateList(int nStartPos)
{
	try
	{
		for (int i = nStartPos ;i < m_ManageFlowNode.GetFlowNodeListSize();i++)
		{
			CFlowNode *pFlowNode = m_ManageFlowNode.GetFlowNodeById(i) ;
			CString strName(_T("")) ;

			GetFlowNodeName(pFlowNode,strName) ;

			if (NULL != pFlowNode->pVisionBase)
			{
				//�����б�
				m_ListWorkFlow.ReplaceString(i,strName,i) ;
			}
		}
	}
	catch (...)
	{
	}
}

void CWorkFlowDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	try
	{
		/*CRect rect;
		m_ListWorkFlow.GetClientRect( &rect );
		ScreenToClient(&rect) ;
		if (point.x> rect.right || point.x<rect.left ||
			point.y<rect.top ||point.y > rect.bottom )
			return ;*/

		CMenu menu,*pSubMenu;
		menu.LoadMenu(IDR_MENU_WORKFLOW);
		pSubMenu = menu.GetSubMenu(0);
		pSubMenu->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
	}
	catch (...)
	{
	}
}

bool CWorkFlowDlg::GetCameraList(CStringArray &arrayCameraInfo)
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		arrayCameraInfo.RemoveAll() ;

		int nCameraCount = pDlg->m_projectData.m_mgCamera.GetCameraNodeListSize() ;
		if (nCameraCount <= 0)
			return false ;

		for (int i = 0 ;i < nCameraCount ;i++)
		{
			CCameraNode *pCameraNode = pDlg->m_projectData.m_mgCamera.GetCameraNodeById(i) ;
			if (NULL == pCameraNode)
				continue;

			CString strCameraInfo(_T("")),strTmp(_T("")) ;
			strTmp.Format(_T("ID%d:"),pCameraNode->nCameraId) ;
			strCameraInfo += strTmp ;

			strTmp = pCameraNode->strCameraSn.c_str() ;
			strCameraInfo += strTmp + _T("|��������������|");

			strTmp = pCameraNode->strCameraTipInfo.c_str() ;
			strCameraInfo += strTmp ;

			arrayCameraInfo.Add(strCameraInfo) ;
		}

		return true ;
	}
	catch (...)
	{
		return false ;
	}
}

bool CWorkFlowDlg::GetCommList(CStringArray &arrayCommInfo)
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		arrayCommInfo.RemoveAll() ;

		int nCommCount = pDlg->m_projectData.m_mgCommunication.GetCommNodeListSize() ;
		if (nCommCount <= 0)
			return false ;

		for (int i = 0 ;i < nCommCount ;i++)
		{
			CCommunicationNode *pCommNode = pDlg->m_projectData.m_mgCommunication.GetCommNodeById(i) ;
			if (NULL == pCommNode)
				continue;

			CString strCommInfo(_T("")),strTmp(_T("")) ;
			strTmp.Format(_T("ID%d:"),pCommNode->nCommId) ;
			strCommInfo += strTmp ;

			strTmp = pCommNode->strCommName.c_str() ;
			strCommInfo += strTmp + _T("|��������������|");

			strTmp = pDlg->m_projectData.m_mgCommunication.GetCommInfo(pCommNode).c_str();
			strCommInfo += strTmp ;

			arrayCommInfo.Add(strCommInfo) ;
		}

		return true ;
	}
	catch (...)
	{
		return false ;
	}
}

bool CWorkFlowDlg::GetFlowNodeName(CFlowNode *pFlowNode,CString &strName)
{
	try
	{
		if (NULL == pFlowNode) return false ;

		strName = _T("") ;
		switch((int)pFlowNode->eFlowNodeType)
		{
		case (int)E_TOOL_2DVISION_CAMERA:
			{
				strName.Format(_T("(ID%d)2D���"),pFlowNode->nFlowNodeID) ;

				break;
			}
		case (int)E_TOOL_2DVISION_SHAPEMODEL:
			{
				strName.Format(_T("(ID%d)��׼��״ģ��"),pFlowNode->nFlowNodeID) ;

				break;
			}
		case (int)E_TOOL_2DVISION_FITLINE:
			{
				strName.Format(_T("(ID%d)����"),pFlowNode->nFlowNodeID) ;

				break ;
			}
		case (int)E_TOOL_VISIONSYSTEM_COMMREAD:
			{
				strName.Format(_T("(ID%d)ͨ�Ž���"),pFlowNode->nFlowNodeID) ;

				break ;
			}
		case (int)E_TOOL_VISIONSYSTEM_COMMWRITE:
			{
				strName.Format(_T("(ID%d)ͨ�ŷ���"),pFlowNode->nFlowNodeID) ;

				break ;
			}
		default:
			break;
		}
	}
	catch (...)
	{
		return false ;
	}
	return true ;
}

void CWorkFlowDlg::OnToolAdd()
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		pDlg->m_bWorkFlowAddTool = true ;
	}
	catch (...)
	{
	}
}

void CWorkFlowDlg::OnToolDel()
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		if (IDOK != AfxMessageBox(_T("�Ƿ�ɾ������?"),MB_OKCANCEL))
			return ;

		int nSelWorkFlow = m_ListWorkFlow.GetCurSel() ;
		if (nSelWorkFlow < 0)
		{
			AfxMessageBox(_T("��ѡ��ɾ������")) ;
			return ;
		}

		int nCurWorkFlowDlg = pDlg->m_tabWorkFlowDlg.GetCurSel() ;
		CInterfaceWorkFlowDlg *pInterfaceWorkFlowDlg = pDlg->m_projectData.m_mgWorkFlowDlg.GetWorkFlowDlgById(nCurWorkFlowDlg) ;
		CString strParentName(_T("")) ;
		strParentName = pInterfaceWorkFlowDlg->strWorkFlowDlgName ;

		CFlowNode *pFlowNode = m_ManageFlowNode.GetFlowNodeById(nSelWorkFlow) ;
		CString strFolderName(_T("")) ;
		GetFlowNodeName(pFlowNode,strFolderName) ;

		CString strDelPath = g_sysIni.m_strProjectPath + _T("\\") + strParentName + _T("\\") + strFolderName ;
		if (vPathIsExist(strDelPath))
		{
			USES_CONVERSION;
			DeleteFolder(W2A(strDelPath)) ;
		}

		m_ManageFlowNode.RemoveAtById(nSelWorkFlow) ;
		m_ManageFlowNode.ReSortById() ;
		m_ImageList.Remove(nSelWorkFlow) ;
		m_ListWorkFlow.DeleteString(nSelWorkFlow) ;

		ReUpdateList(nSelWorkFlow) ;

		ResetAllTreeNode() ;
	}
	catch (...)
	{
	}
}

void CWorkFlowDlg::OnToolMoveup()
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		if (IDOK != AfxMessageBox(_T("�Ƿ񹤾�����?"),MB_OKCANCEL))
			return ;

		int nSelWorkFlow = m_ListWorkFlow.GetCurSel() ;
		if (nSelWorkFlow < 0)
		{
			AfxMessageBox(_T("��ѡ�й�������")) ;
			return ;
		}

		CManageFlowNode manageCpyFlowNode ;
		CFlowNode *pPreFlowNode = m_ManageFlowNode.GetFlowNodeById(nSelWorkFlow - 1) ;
		CFlowNode *pFlowNode = m_ManageFlowNode.GetFlowNodeById(nSelWorkFlow) ;
		for (int i = 0 ;i < m_ManageFlowNode.GetFlowNodeListSize();i++)
		{
			manageCpyFlowNode.AddTail(m_ManageFlowNode.GetFlowNodeById(i)) ;
		}
		m_ManageFlowNode.RemoveAll() ;

		CString strName(_T("")) ;
		ReplaceImageList(pPreFlowNode,pFlowNode) ;
		for (int i = 0 ;i < manageCpyFlowNode.GetFlowNodeListSize();i++)
		{
			if (i == (nSelWorkFlow - 1))
			{
				pFlowNode->nFlowNodeID = i;
				m_ManageFlowNode.AddTail(pFlowNode) ;
				GetFlowNodeName(pFlowNode,strName) ;
				m_ListWorkFlow.ReplaceString(i,strName,i) ;
			}
			else if (i == nSelWorkFlow)
			{
				pPreFlowNode->nFlowNodeID = i ;
				m_ManageFlowNode.AddTail(pPreFlowNode) ;
				GetFlowNodeName(pPreFlowNode,strName) ;
				m_ListWorkFlow.ReplaceString(i,strName,i) ;
			}
			else
			    m_ManageFlowNode.AddTail(manageCpyFlowNode.GetFlowNodeById(i)) ;
		}

		ResetAllTreeNode() ;
	}
	catch (...)
	{
	}
}

void CWorkFlowDlg::OnToolMovedown()
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		if (IDOK != AfxMessageBox(_T("�Ƿ񹤾�����?"),MB_OKCANCEL))
			return ;

		int nSelWorkFlow = m_ListWorkFlow.GetCurSel() ;
		if (nSelWorkFlow < 0)
		{
			AfxMessageBox(_T("��ѡ�й�������")) ;
			return ;
		}

		CManageFlowNode manageCpyFlowNode ;
		CFlowNode *pFlowNode = m_ManageFlowNode.GetFlowNodeById(nSelWorkFlow) ;
		CFlowNode *pNextFlowNode = m_ManageFlowNode.GetFlowNodeById(nSelWorkFlow + 1) ;
		for (int i = 0 ;i < m_ManageFlowNode.GetFlowNodeListSize();i++)
		{
			manageCpyFlowNode.AddTail(m_ManageFlowNode.GetFlowNodeById(i)) ;
		}
		m_ManageFlowNode.RemoveAll() ;

		CString strName(_T("")) ;
		ReplaceImageList(pFlowNode,pNextFlowNode) ;
		for (int i = 0 ;i < manageCpyFlowNode.GetFlowNodeListSize();i++)
		{
			if (i == (nSelWorkFlow))
			{
				pNextFlowNode->nFlowNodeID = i ;
				m_ManageFlowNode.AddTail(pNextFlowNode) ;
				GetFlowNodeName(pNextFlowNode,strName) ;
				m_ListWorkFlow.ReplaceString(i,strName,i) ;
			}
			else if (i == nSelWorkFlow + 1)
			{
				pFlowNode->nFlowNodeID = i ;
				m_ManageFlowNode.AddTail(pFlowNode) ;
				GetFlowNodeName(pFlowNode,strName) ;
				m_ListWorkFlow.ReplaceString(i,strName,i) ;
			}
			else
				m_ManageFlowNode.AddTail(manageCpyFlowNode.GetFlowNodeById(i)) ;
		}

		ResetAllTreeNode() ;
	}
	catch (...)
	{
	}
}

void CWorkFlowDlg::OnParaconnect()
{
	USES_CONVERSION ;
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		//��ȡ��ǰѡ�й���ID
		int nCurSelListBox = m_ListWorkFlow.GetCurSel() ;
		if (nCurSelListBox < 0)
			return ;

		//��ȡ��ǰѡ�й���
		CFlowNode *pNode = m_ManageFlowNode.GetFlowNodeById(nCurSelListBox) ;
		if (NULL == pNode)
			return ;

		if (E_TOOL_2DVISION_CAMERA == pNode->eFlowNodeType)
		{
			CStringArray arrayCameraInfo ;
			if (!GetCameraList(arrayCameraInfo))
			{
				AfxMessageBox(_T("û��������Ӳ��")) ;
				return ;
			}

			CCameraConnectDlg cameraConnectDlg ;
			cameraConnectDlg.m_arrayCameraInfo.Copy(arrayCameraInfo) ;
			if (IDOK == cameraConnectDlg.DoModal())
			{
				VString strCameraInfo  ;
				strCameraInfo.vStr = W2A(cameraConnectDlg.m_strSelCameraInfo) ;

				//��¼treenode
				int nNodeInCount = (int)pNode->treeNode.GetSize() ;
				CNodeIn *pNodeIn ;
				if (nNodeInCount <= 0)
				{
					pNodeIn = new CNodeIn() ;
					pNodeIn->eNodeInType = E_VDATA_CAMERA ;
					pNodeIn->NodeInLog.nParentTreeNodeID = -1 ;
					pNodeIn->NodeInLog.nParentTreeNodeOutID = -1 ;
					pNodeIn->NodeInLog.strParentTreeNodeOutName = strCameraInfo.vStr ;
					pNode->treeNode.AddTail(pNodeIn) ;
				}
				else
				{
					pNodeIn = pNode->treeNode.GetAt(pNode->treeNode.FindIndex(0)) ;
					pNodeIn->eNodeInType = E_VDATA_CAMERA ;
					pNodeIn->NodeInLog.nParentTreeNodeID = -1 ;
					pNodeIn->NodeInLog.nParentTreeNodeOutID = -1 ;
					pNodeIn->NodeInLog.strParentTreeNodeOutName = strCameraInfo.vStr ;
				}
			}
		}
		else if (E_TOOL_2DVISION_LED == pNode->eFlowNodeType)
		{
		}
		else if (E_TOOL_VISIONSYSTEM_COMMREAD == pNode->eFlowNodeType \
			|| E_TOOL_VISIONSYSTEM_COMMWRITE == pNode->eFlowNodeType)
		{
			CStringArray arrayCommInfo ;
			if (!GetCommList(arrayCommInfo))
			{
				AfxMessageBox(_T("û�����ͨ��")) ;
				return ;
			}

			CCommConnectDlg commConnectDlg ;
			commConnectDlg.m_arrayCommInfo.Copy(arrayCommInfo) ;
			if (IDOK == commConnectDlg.DoModal())
			{
				VString strCommInfo  ;
				strCommInfo.vStr = W2A(commConnectDlg.m_strSelCommInfo) ;

				//��¼treenode
				int nNodeInCount = (int)pNode->treeNode.GetSize() ;
				CNodeIn *pNodeIn ;
				if (nNodeInCount <= 0)
				{
					pNodeIn = new CNodeIn() ;
					pNodeIn->eNodeInType = E_VDATA_COMMUNICATION ;
					pNodeIn->NodeInLog.nParentTreeNodeID = -1 ;
					pNodeIn->NodeInLog.nParentTreeNodeOutID = -1 ;
					pNodeIn->NodeInLog.strParentTreeNodeOutName = strCommInfo.vStr ;
					pNode->treeNode.AddTail(pNodeIn) ;
				}
				else
				{
					pNodeIn = pNode->treeNode.GetAt(pNode->treeNode.FindIndex(0)) ;
					pNodeIn->eNodeInType = E_VDATA_COMMUNICATION ;
					pNodeIn->NodeInLog.nParentTreeNodeID = -1 ;
					pNodeIn->NodeInLog.nParentTreeNodeOutID = -1 ;
					pNodeIn->NodeInLog.strParentTreeNodeOutName = strCommInfo.vStr ;
				}
			}
		}
		else
		{
			//��������
			CParaConnectDlg paraConnectDlg ;
			paraConnectDlg.m_pFlowNode = pNode ;
			//paraConnectDlg.UpdateInputData(m_ManageFlowNode,pNode) ;
			if (IDOK == paraConnectDlg.DoModal())
			{
			}
		}

		////Ӳ�����������Ӳ��
		//if (E_TOOL_2DVISION_CAMERA == pNode->eFlowNodeType || E_TOOL_2DVISION_LED == pNode->eFlowNodeType)
		//	return ;

		////��������
		//CParaConnectDlg paraConnectDlg ;
		//paraConnectDlg.m_pFlowNode = pNode ;
		//if (IDOK == paraConnectDlg.DoModal())
		//{
		//
		//}
		OutputDebugString(_T("")) ;
	}
	catch (...)
	{
	}
}

void CWorkFlowDlg::OnLbnDblclkListWorkflow()
{
	USES_CONVERSION ;
	// ˫���༭����
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		//��ȡ��ǰѡ�й���ID
		int nCurSelListBox = m_ListWorkFlow.GetCurSel() ;
		if (nCurSelListBox < 0)
			return ;

		//��ȡ��ǰWorkFlowDlg
		CInterfaceWorkFlowDlg *pInterfaceWorkFlowDlg = pDlg->m_projectData.m_mgWorkFlowDlg.GetWorkFlowDlgById(pDlg->m_tabWorkFlowDlg.GetCurSel()) ;
		if (NULL == pInterfaceWorkFlowDlg)
			return ;

		//��ȡ��ǰѡ�й���
		CFlowNode *pNode = m_ManageFlowNode.GetFlowNodeById(nCurSelListBox) ;
		if (NULL == pNode)
			return ;

		vector<any> vecInput ;
		if (!pDlg->m_projectData.GetInputPara(pNode,vecInput))
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
				if (!pDlg->m_projectData.GetConfigPath(m_strWorkFlowDlgName/*pInterfaceWorkFlowDlg*/,pNode,strConfigPath))
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

				//��ʾ�Ի���
				ProVisionFun(pNode->pVisionBase->Vision_ShowDialog(),pNode->eFlowNodeType,_T("Vision_ShowDialog")) ;

				return ;
			}
			else
			{
				AfxMessageBox(_T("��ʼ��ʧ��")) ;
			}
		}
		else
		{
			AfxMessageBox(_T("��������쳣")) ;
		}
	}
	catch (...)
	{
	}
}

void CWorkFlowDlg::ResetAllTreeNode()
{
	try
	{
		for (int i = 0 ;i < m_ManageFlowNode.GetFlowNodeListSize();i++)
		{
			CFlowNode *pFlowNode = m_ManageFlowNode.GetFlowNodeById(i) ;

			while(pFlowNode->treeNode.GetSize() > 0)
			{
				CNodeIn *pNodeIn = pFlowNode->treeNode.GetAt(pFlowNode->treeNode.FindIndex(0)) ;
				DELETE_POINT(pNodeIn) ;
				pFlowNode->treeNode.RemoveAt(pFlowNode->treeNode.FindIndex(0)) ;
			}
			/*for (int j = 0 ;j < pFlowNode->treeNode.GetSize();j++)
			{
				CNodeIn *pNodeIn = pFlowNode->treeNode.GetAt(pFlowNode->treeNode.FindIndex(j)) ;
				DELETE_POINT(pNodeIn) ;
				pFlowNode->treeNode
			}*/
		}
	}
	catch (...)
	{
	}
}

void CWorkFlowDlg::OnAddScript()
{
	USES_CONVERSION ;
	// ˫���༭����
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		CStdioFile f;
		CString strPath ;
		strPath = g_sysIni.m_strProjectPath+_T("\\WorkFlow.lua") ;
		if (vFileIsExist(strPath)) return ;

		char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
		setlocale( LC_CTYPE, ("chs")) ;
		if(!f.Open(strPath,CFile::modeRead|CFile::modeWrite))
		{
			if(!f.Open(strPath,CFile::modeCreate|CFile::modeWrite))
			{
				setlocale( LC_CTYPE, old_locale );
				free( old_locale );//��ԭ�����趨
				return ;
			}
		}
		f.SeekToEnd();
		f.Close();
		setlocale( LC_CTYPE, old_locale );
		free( old_locale );//��ԭ�����趨
	}
	catch( CFileException* e )
	{
		e;
	}
}

void CWorkFlowDlg::OnEditScript()
{
	USES_CONVERSION ;
	try
	{
		CString strPath ;
		strPath = g_sysIni.m_strProjectPath+_T("\\WorkFlow.lua") ;
		ShellExecute(NULL,_T("open"),strPath,NULL,NULL, SW_SHOWNORMAL);
	}
	catch (...)
	{
	}
}