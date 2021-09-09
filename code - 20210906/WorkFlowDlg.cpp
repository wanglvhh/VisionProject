// WorkFlowDlg.cpp : 实现文件
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
// CWorkFlowDlg 对话框

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

// CWorkFlowDlg 消息处理程序

BEGIN_EASYSIZE_MAP(CWorkFlowDlg)
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
	EASYSIZE(IDC_LIST_WORKFLOW,ES_BORDER,ES_BORDER,ES_BORDER,ES_BORDER,0)
END_EASYSIZE_MAP

BOOL CWorkFlowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	INIT_EASYSIZE;

	InitImageList() ;

	m_brushBk.CreateSolidBrush(SYSTEM_BK_COLOR);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

HBRUSH CWorkFlowDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if(nCtlColor == CTLCOLOR_LISTBOX ||nCtlColor == CTLCOLOR_EDIT)
	{
		//pDC->SetBkColor(SYSTEM_WHITE) ;
		pDC->SetTextColor(SYSTEM_BLUE);//字体色
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

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return m_brushBk;
}

void CWorkFlowDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
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
					strName.Format(_T("(ID%d)2D相机"),i) ;

					if (NULL == pFlowNode->pVisionBase)
					{
						pFlowNode->mgrDllVisionBaseIm.DllCreateInterface(E_TOOL_2DVISION_CAMERA,(void **)&pFlowNode->pVisionBase) ;
						if (NULL == pFlowNode->pVisionBase)continue;
						//更新列表
						m_ListWorkFlow.AddString(strName,i) ;
						m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_CAMERA));
					}

					break;
				}
			case (int)E_TOOL_2DVISION_SHAPEMODEL:
				{
					strName.Format(_T("(ID%d)标准形状模板"),i) ;

					if (NULL == pFlowNode->pVisionBase)
					{
						pFlowNode->mgrDllVisionBaseIm.DllCreateInterface((int)E_TOOL_2DVISION_SHAPEMODEL,(void **)&pFlowNode->pVisionBase) ;
						if (NULL == pFlowNode->pVisionBase)continue;
						//更新列表
						m_ListWorkFlow.AddString(strName,i) ;
						m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_SHAPEMODEL));
					}

					break;
				}
			case (int)E_TOOL_2DVISION_FITLINE:
				{
					strName.Format(_T("(ID%d)找线"),i) ;

					if (NULL == pFlowNode->pVisionBase)
					{
						pFlowNode->mgrDllVisionBaseIm.DllCreateInterface((int)E_TOOL_2DVISION_FITLINE,(void **)&pFlowNode->pVisionBase) ;
						if (NULL == pFlowNode->pVisionBase)continue;
						//更新列表
						m_ListWorkFlow.AddString(strName,i) ;
						m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_FITLINE));
					}

					break ;
				}
			case (int)E_TOOL_VISIONSYSTEM_COMMREAD:
				{
					strName.Format(_T("(ID%d)通信接收"),i) ;

					if (NULL == pFlowNode->pVisionBase)
					{
						pFlowNode->mgrDllVisionBaseIm.DllCreateInterface((int)E_TOOL_VISIONSYSTEM_COMMREAD,(void **)&pFlowNode->pVisionBase) ;
						if (NULL == pFlowNode->pVisionBase)continue;
						//更新列表
						m_ListWorkFlow.AddString(strName,i) ;
						m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_READ));
					}

					break ;
				}
			case (int)E_TOOL_VISIONSYSTEM_COMMWRITE:
				{
					strName.Format(_T("(ID%d)通信发送"),i) ;

					if (NULL == pFlowNode->pVisionBase)
					{
						pFlowNode->mgrDllVisionBaseIm.DllCreateInterface((int)E_TOOL_VISIONSYSTEM_COMMWRITE,(void **)&pFlowNode->pVisionBase) ;
						if (NULL == pFlowNode->pVisionBase)continue;
						//更新列表
						m_ListWorkFlow.AddString(strName,i) ;
						m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_SEND));
					}

					break ;
				}
			default:
				break;
			}

			//获取Input

			//初始化
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
				//更新列表
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
			strCameraInfo += strTmp + _T("|······→|");

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
			strCommInfo += strTmp + _T("|······→|");

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
				strName.Format(_T("(ID%d)2D相机"),pFlowNode->nFlowNodeID) ;

				break;
			}
		case (int)E_TOOL_2DVISION_SHAPEMODEL:
			{
				strName.Format(_T("(ID%d)标准形状模板"),pFlowNode->nFlowNodeID) ;

				break;
			}
		case (int)E_TOOL_2DVISION_FITLINE:
			{
				strName.Format(_T("(ID%d)找线"),pFlowNode->nFlowNodeID) ;

				break ;
			}
		case (int)E_TOOL_VISIONSYSTEM_COMMREAD:
			{
				strName.Format(_T("(ID%d)通信接收"),pFlowNode->nFlowNodeID) ;

				break ;
			}
		case (int)E_TOOL_VISIONSYSTEM_COMMWRITE:
			{
				strName.Format(_T("(ID%d)通信发送"),pFlowNode->nFlowNodeID) ;

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
		if (IDOK != AfxMessageBox(_T("是否删除工具?"),MB_OKCANCEL))
			return ;

		int nSelWorkFlow = m_ListWorkFlow.GetCurSel() ;
		if (nSelWorkFlow < 0)
		{
			AfxMessageBox(_T("请选中删除工具")) ;
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
		if (IDOK != AfxMessageBox(_T("是否工具上移?"),MB_OKCANCEL))
			return ;

		int nSelWorkFlow = m_ListWorkFlow.GetCurSel() ;
		if (nSelWorkFlow < 0)
		{
			AfxMessageBox(_T("请选中工具上移")) ;
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
		if (IDOK != AfxMessageBox(_T("是否工具下移?"),MB_OKCANCEL))
			return ;

		int nSelWorkFlow = m_ListWorkFlow.GetCurSel() ;
		if (nSelWorkFlow < 0)
		{
			AfxMessageBox(_T("请选中工具下移")) ;
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
		//获取当前选中工具ID
		int nCurSelListBox = m_ListWorkFlow.GetCurSel() ;
		if (nCurSelListBox < 0)
			return ;

		//获取当前选中工具
		CFlowNode *pNode = m_ManageFlowNode.GetFlowNodeById(nCurSelListBox) ;
		if (NULL == pNode)
			return ;

		if (E_TOOL_2DVISION_CAMERA == pNode->eFlowNodeType)
		{
			CStringArray arrayCameraInfo ;
			if (!GetCameraList(arrayCameraInfo))
			{
				AfxMessageBox(_T("没有添加相机硬件")) ;
				return ;
			}

			CCameraConnectDlg cameraConnectDlg ;
			cameraConnectDlg.m_arrayCameraInfo.Copy(arrayCameraInfo) ;
			if (IDOK == cameraConnectDlg.DoModal())
			{
				VString strCameraInfo  ;
				strCameraInfo.vStr = W2A(cameraConnectDlg.m_strSelCameraInfo) ;

				//记录treenode
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
				AfxMessageBox(_T("没有添加通信")) ;
				return ;
			}

			CCommConnectDlg commConnectDlg ;
			commConnectDlg.m_arrayCommInfo.Copy(arrayCommInfo) ;
			if (IDOK == commConnectDlg.DoModal())
			{
				VString strCommInfo  ;
				strCommInfo.vStr = W2A(commConnectDlg.m_strSelCommInfo) ;

				//记录treenode
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
			//参数关联
			CParaConnectDlg paraConnectDlg ;
			paraConnectDlg.m_pFlowNode = pNode ;
			//paraConnectDlg.UpdateInputData(m_ManageFlowNode,pNode) ;
			if (IDOK == paraConnectDlg.DoModal())
			{
			}
		}

		////硬件工具需关联硬件
		//if (E_TOOL_2DVISION_CAMERA == pNode->eFlowNodeType || E_TOOL_2DVISION_LED == pNode->eFlowNodeType)
		//	return ;

		////参数关联
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
	// 双击编辑工具
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		//获取当前选中工具ID
		int nCurSelListBox = m_ListWorkFlow.GetCurSel() ;
		if (nCurSelListBox < 0)
			return ;

		//获取当前WorkFlowDlg
		CInterfaceWorkFlowDlg *pInterfaceWorkFlowDlg = pDlg->m_projectData.m_mgWorkFlowDlg.GetWorkFlowDlgById(pDlg->m_tabWorkFlowDlg.GetCurSel()) ;
		if (NULL == pInterfaceWorkFlowDlg)
			return ;

		//获取当前选中工具
		CFlowNode *pNode = m_ManageFlowNode.GetFlowNodeById(nCurSelListBox) ;
		if (NULL == pNode)
			return ;

		vector<any> vecInput ;
		if (!pDlg->m_projectData.GetInputPara(pNode,vecInput))
		{
			AfxMessageBox(_T("获取输入参数失败")) ;
			return ;
		}

		//输入参数
		if (ProVisionFun(pNode->pVisionBase->Vision_Input(vecInput),pNode->eFlowNodeType,_T("Vision_Input")))
		{
			//初始化
			if(ProVisionFun(pNode->pVisionBase->Vision_Init(),pNode->eFlowNodeType,_T("Vision_Init")))
			{
				CString strConfigPath(_T("")) ;
				if (!pDlg->m_projectData.GetConfigPath(m_strWorkFlowDlgName/*pInterfaceWorkFlowDlg*/,pNode,strConfigPath))
				{
					AfxMessageBox(_T("获取参数路径失败")) ;
					return ;
				}

				//加载配置文件
				if(!ProVisionFun(pNode->pVisionBase->Vision_LoadConfigure(W2A(strConfigPath)),pNode->eFlowNodeType,_T("Vision_LoadConfigure")) )
				{
					//工具加载配置文件失败 重新设置配置路径
					ProVisionFun(pNode->pVisionBase->Vision_SetConfigurePath(W2A(strConfigPath)),pNode->eFlowNodeType,_T("Vision_SetConfigurePath")) ;
				}

				//显示对话框
				ProVisionFun(pNode->pVisionBase->Vision_ShowDialog(),pNode->eFlowNodeType,_T("Vision_ShowDialog")) ;

				return ;
			}
			else
			{
				AfxMessageBox(_T("初始化失败")) ;
			}
		}
		else
		{
			AfxMessageBox(_T("输入参数异常")) ;
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
	// 双击编辑工具
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
				free( old_locale );//还原区域设定
				return ;
			}
		}
		f.SeekToEnd();
		f.Close();
		setlocale( LC_CTYPE, old_locale );
		free( old_locale );//还原区域设定
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