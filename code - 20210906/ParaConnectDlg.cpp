// ParaConnectDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "VisionProject.h"
#include "ParaConnectDlg.h"
#include "afxdialogex.h"
#include "VisionProjectDlg.h"

// CParaConnectDlg 对话框
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(CParaConnectDlg, CDialogEx)

CParaConnectDlg::CParaConnectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CParaConnectDlg::IDD, pParent)
{
	m_pFlowNode = NULL ;
}

CParaConnectDlg::~CParaConnectDlg()
{
}

void CParaConnectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREELIST_PARNETNODE_OUT, m_ctrlTreeParentList);
	DDX_Control(pDX, IDC_TREELIST_CHILDNODE_IN, m_ctrlTreeList);
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
}

BEGIN_MESSAGE_MAP(CParaConnectDlg, CDialogEx)
	ON_MESSAGE(WM_TREELIST_UPDATA, &CParaConnectDlg::OnUpdataChildTreeList)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_DEL_INPUTPARA, &CParaConnectDlg::OnDelInputpara)
END_MESSAGE_MAP()

// CParaConnectDlg 消息处理程序

BOOL CParaConnectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitAllControl() ;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CParaConnectDlg::InitAllControl()
{
	try
	{
		//初始化button控件
		InitBtnControl()  ;

		//初始化TreeList
		InitTreeList() ;
	}
	catch (...)
	{
	}
}

void CParaConnectDlg::InitBtnControl()
{
	try
	{
		m_btnOk.SetIcon(IDI_ICON_OK) ;
		m_btnOk.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnOk.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnOk.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnOk.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnOk.SetRounded(TRUE) ;

		m_btnCancel.SetIcon(IDI_ICON_CANCEL) ;
		m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnCancel.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnCancel.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnCancel.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnCancel.SetRounded(TRUE) ;
	}
	catch (...)
	{
	}
}

void CParaConnectDlg::InitTreeList()
{
	try
	{
		m_ImageList.Create( IDB_BITMAP_TREE, 16, 4, 0xFF00FF );

		m_ctrlTreeParentList.SetStyle( TLC_DOUBLECOLOR | TLC_BKGNDCOLOR| TLC_SHOWSELALWAYS | TLC_MULTIPLESELECT | TLC_SHOWSELACTIVE | TLC_HEADER | TLC_HGRID | TLC_VGRID );
		m_ctrlTreeParentList.SetStyle( m_ctrlTreeParentList.GetStyle() | TLC_TREELINE |  TLC_BUTTON | TLC_CHECKBOX | TLC_LOCKBOX | TLC_IMAGE | TLC_DRAG );

		m_ctrlTreeList.SetStyle( TLC_DOUBLECOLOR | TLC_BKGNDCOLOR| TLC_SHOWSELALWAYS | TLC_MULTIPLESELECT | TLC_SHOWSELACTIVE | TLC_HEADER | TLC_HGRID | TLC_VGRID );
		m_ctrlTreeList.SetStyle( m_ctrlTreeList.GetStyle() | TLC_TREELINE |  TLC_BUTTON | TLC_CHECKBOX | TLC_LOCKBOX | TLC_IMAGE | TLC_DRAG );

		m_ctrlTreeParentList.SetStyle
			( 0
			| TLC_TREELIST           // TreeList or List
			//    | TLC_BKGNDIMAGE       // image background
			//    | TLC_BKGNDCOLOR       // colored background ( not client area )
			//    | TLC_DOUBLECOLOR      // double color background

			| TLC_MULTIPLESELECT     // single or multiple select
			| TLC_SHOWSELACTIVE      // show active column of selected item
			| TLC_SHOWSELALWAYS      // show selected item always
			| TLC_SHOWSELFULLROWS    // show selected item in fullrow mode

			| TLC_HEADER             // show header
			| TLC_HGRID              // show horizonal grid lines
			| TLC_VGRID              // show vertical grid lines
			| TLC_TGRID              // show tree horizonal grid lines ( when HGRID & VGRID )
			| TLC_HGRID_EXT          // show extention horizonal grid lines
			| TLC_VGRID_EXT          // show extention vertical grid lines
			| TLC_HGRID_FULL         // show full horizonal grid lines
			//    | TLC_READONLY         // read only

			| TLC_TREELINE           // show tree line
			| TLC_ROOTLINE           // show root line
			| TLC_BUTTON             // show expand/collapse button [+]
			| TLC_CHECKBOX           // show check box
			| TLC_LOCKBOX            // show lock box
			| TLC_IMAGE              // show image
			| TLC_HOTTRACK           // show hover text

			| TLC_DRAG               // drag support
			| TLC_DROP               // drop support
			//    | TLC_DROPTHIS         // drop self support
			//    | TLC_DROPROOT         // drop on root support

			| TLC_HEADDRAGDROP       // head drag drop
			| TLC_HEADFULLDRAG       // head funn drag
			//    | TLC_NOAUTOCHECK      // do NOT auto set checkbox of parent & child
			//    | TLC_NOAUTOLOCK       // do NOT auto set lockbox of parent & child
			);

		m_ctrlTreeList.SetStyle
			( 0
			| TLC_TREELIST           // TreeList or List
			//    | TLC_BKGNDIMAGE       // image background
			//    | TLC_BKGNDCOLOR       // colored background ( not client area )
			//    | TLC_DOUBLECOLOR      // double color background

			| TLC_MULTIPLESELECT     // single or multiple select
			| TLC_SHOWSELACTIVE      // show active column of selected item
			| TLC_SHOWSELALWAYS      // show selected item always
			| TLC_SHOWSELFULLROWS    // show selected item in fullrow mode

			| TLC_HEADER             // show header
			//    | TLC_HGRID            // show horizonal grid lines
			//    | TLC_VGRID            // show vertical grid lines
			//    | TLC_TGRID            // show tree horizonal grid lines ( when HGRID & VGRID )
			| TLC_HGRID_EXT          // show extention horizonal grid lines
			| TLC_VGRID_EXT          // show extention vertical grid lines
			| TLC_HGRID_FULL         // show full horizonal grid lines
			//    | TLC_READONLY         // read only

			| TLC_TREELINE           // show tree line
			| TLC_ROOTLINE           // show root line
			| TLC_BUTTON             // show expand/collapse button [+]
			| TLC_CHECKBOX           // show check box
			| TLC_LOCKBOX            // show lock box
			| TLC_IMAGE              // show image
			| TLC_HOTTRACK           // show hover text

			//    | TLC_DRAG             // drag support
			| TLC_DROP               // drop support
			| TLC_DROPTHIS           // drop self support
			//    | TLC_DROPROOT         // drop on root support

			| TLC_HEADDRAGDROP       // head drag drop
			| TLC_HEADFULLDRAG       // head funn drag
			///    | TLC_NOAUTOCHECK     // do NOT auto set checkbox of parent & child
			//    | TLC_NOAUTOLOCK       // do NOT auto set lockbox of parent & child
			);

		m_ctrlTreeParentList.SetImageList(&m_ImageList);
		m_ctrlTreeList.SetImageList(&m_ImageList);

		m_ctrlTreeParentList.InsertColumn(_T("父节节点工具名"),   TLF_DEFAULT_LEFT   | TLF_CAPTION_IMAGE );
		m_ctrlTreeParentList.SetColumnModify( 0, TLM_STATIC );

		m_ctrlTreeList.InsertColumn(_T("当前节点工具名"),   TLF_DEFAULT_LEFT   | TLF_CAPTION_IMAGE );
		m_ctrlTreeList.SetColumnModify( 0, TLM_STATIC );

		m_ctrlTreeParentList.SetColumnWidth( 0, 378 );
		m_ctrlTreeList.SetColumnWidth( 0, 378 );

		m_ctrlTreeParentList.Refresh(FALSE);
		InitParentTreeControl() ;
		m_ctrlTreeParentList.Refresh(TRUE);

		m_ctrlTreeList.Refresh(FALSE);
		InitTreeControl() ;
		m_ctrlTreeList.Refresh(FALSE);

		m_ctrlTreeParentList.m_hParentHwnd = this->GetSafeHwnd() ;
		m_ctrlTreeList.m_hParentHwnd = this->GetSafeHwnd() ;
	}
	catch (...)
	{
	}
}

void CParaConnectDlg::InitParentTreeControl()
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		//当前工具节点为所有节点父节点
		if (0 == m_pFlowNode->nFlowNodeID)
			return ;

		switch((int)m_pFlowNode->eFlowNodeType)
		{
		case (int)E_TOOL_2DVISION_CAMERA:
			{
				break;
			}
		case (int)E_TOOL_2DVISION_SHAPEMODEL:
			{
				//初始化查找相机工具、图像工具、所有模板工具
				VISION_TOOLTYPE eSearchType[] = {E_TOOL_2DVISION_CAMERA,E_TOOL_2DVISION_SHAPEMODEL,E_TOOL_2DVISION_SCALESHAPEMODEL\
				                                ,E_TOOL_2DVISION_NCCMODEL,E_TOOL_2DVISION_CONTOURMODEL,E_TOOL_2DVISION_SCALECONTOURMODEL} ;

				//查找符合条件的父节点并初始化ParentTreeControl
				SearchParentTool(0,m_pFlowNode->nFlowNodeID-1,ARRAYSIZE(eSearchType),eSearchType) ;

				break;
			}
		case (int)E_TOOL_2DVISION_FITLINE:
			{
				//初始化查找相机工具、图像工具、所有模板工具
				VISION_TOOLTYPE eSearchType[] = {E_TOOL_2DVISION_CAMERA,E_TOOL_2DVISION_SHAPEMODEL,E_TOOL_2DVISION_SCALESHAPEMODEL\
					,E_TOOL_2DVISION_NCCMODEL,E_TOOL_2DVISION_CONTOURMODEL,E_TOOL_2DVISION_SCALECONTOURMODEL} ;

				//查找符合条件的父节点并初始化ParentTreeControl
				SearchParentTool(0,m_pFlowNode->nFlowNodeID-1,ARRAYSIZE(eSearchType),eSearchType) ;

				break;
			}
		default:
			break;
		}
	}
	catch (...)
	{
	}
}

void CParaConnectDlg::SearchParentTool(int nStartFlowNodeId,int nEndFlowNodeId,int nSearchRange,VISION_TOOLTYPE eSearchType[])
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		//m_ctrlTreeParentList.m_parentTreeNodeList.RemoveAll() ;

		CInterfaceWorkFlowDlg *pCurInterfaceWorkFlowDlg = pDlg->m_projectData.m_mgWorkFlowDlg.GetWorkFlowDlgById(pDlg->m_tabWorkFlowDlg.GetCurSel()) ;
		CWorkFlowDlg          *pCurWorkFlowDlg          = pCurInterfaceWorkFlowDlg->pWorkFlowDlg ;

		for (int nFlowNodeId = nStartFlowNodeId ;nFlowNodeId <= nEndFlowNodeId ;nFlowNodeId++)
		{
			CFlowNode *pFlowNode = pCurWorkFlowDlg->m_ManageFlowNode.GetFlowNodeById(nFlowNodeId);

			for (int i = 0 ;i < nSearchRange ; i++)
			{
				if (pFlowNode->eFlowNodeType != eSearchType[i])
					continue;

				CString strInfo(_T("")) ;
				switch((int)pFlowNode->eFlowNodeType)
				{
				case (int)E_TOOL_2DVISION_CAMERA:
					{
						CTreeListItem *pItem ;
						strInfo.Format(_T("(ID%d)2D相机"),nFlowNodeId) ;
						pItem = m_ctrlTreeParentList.InsertItem(strInfo) ;
						m_ctrlTreeParentList.SetItemImage( pItem, 0, 1, 2, 3 );
						m_ctrlTreeParentList.SetItemState( pItem, 0, TLIS_SHOWCHECKBOX | TLIS_SHOWLOCKBOX );
						m_ctrlTreeParentList.SetItemState( pItem, TLIS_EXPANDED );

						CTreeListItem *pItem2 ;
						strInfo.Format(_T("输出变量:(ID%d)图像"),0) ;
						pItem2 = m_ctrlTreeParentList.InsertItem( strInfo, pItem);
						m_ctrlTreeParentList.SetItemImage( pItem2, 8, 9, 10, 11 );
						m_ctrlTreeParentList.SetItemState( pItem2, 0, TLIS_SHOWCHECKBOX | TLIS_SHOWLOCKBOX );

						break;
					}
				case (int)E_TOOL_2DVISION_SHAPEMODEL:
					{
						CTreeListItem *pItem ;
						strInfo.Format(_T("(ID%d)标准形状模板"),nFlowNodeId) ;
						pItem = m_ctrlTreeParentList.InsertItem(strInfo) ;
						m_ctrlTreeParentList.SetItemImage( pItem, 0, 1, 2, 3 );
						m_ctrlTreeParentList.SetItemState( pItem, 0, TLIS_SHOWCHECKBOX | TLIS_SHOWLOCKBOX );
						m_ctrlTreeParentList.SetItemState( pItem, TLIS_EXPANDED );

						CTreeListItem *pItem2 ;
						strInfo.Format(_T("输出变量:(ID%d)模板位置"),0) ;
						pItem2 = m_ctrlTreeParentList.InsertItem( strInfo, pItem);
						m_ctrlTreeParentList.SetItemImage( pItem2, 8, 9, 10, 11 );
						m_ctrlTreeParentList.SetItemState( pItem2, 0, TLIS_SHOWCHECKBOX | TLIS_SHOWLOCKBOX );

						strInfo.Format(_T("输出变量:(ID%d)查找位置"),1) ;
						pItem2 = m_ctrlTreeParentList.InsertItem( strInfo, pItem);
						m_ctrlTreeParentList.SetItemImage( pItem2, 8, 9, 10, 11 );
						m_ctrlTreeParentList.SetItemState( pItem2, 0, TLIS_SHOWCHECKBOX | TLIS_SHOWLOCKBOX );

						strInfo.Format(_T("输出变量:(ID%d)防射矩阵"),2) ;
						pItem2 = m_ctrlTreeParentList.InsertItem( strInfo, pItem);
						m_ctrlTreeParentList.SetItemImage( pItem2, 8, 9, 10, 11 );
						m_ctrlTreeParentList.SetItemState( pItem2, 0, TLIS_SHOWCHECKBOX | TLIS_SHOWLOCKBOX );

						break;
					}
				case (int)E_TOOL_2DVISION_FITLINE:
					{
						CTreeListItem *pItem ;
						strInfo.Format(_T("(ID%d)找线"),nFlowNodeId) ;
						pItem = m_ctrlTreeParentList.InsertItem(strInfo) ;
						m_ctrlTreeParentList.SetItemImage( pItem, 0, 1, 2, 3 );
						m_ctrlTreeParentList.SetItemState( pItem, 0, TLIS_SHOWCHECKBOX | TLIS_SHOWLOCKBOX );
						m_ctrlTreeParentList.SetItemState( pItem, TLIS_EXPANDED );

						CTreeListItem *pItem2 ;

						strInfo.Format(_T("输出变量:(ID%d)起点"),0) ;
						pItem2 = m_ctrlTreeParentList.InsertItem( strInfo, pItem);
						m_ctrlTreeParentList.SetItemImage( pItem2, 8, 9, 10, 11 );
						m_ctrlTreeParentList.SetItemState( pItem2, 0, TLIS_SHOWCHECKBOX | TLIS_SHOWLOCKBOX );

						strInfo.Format(_T("输出变量:(ID%d)终点"),1) ;
						pItem2 = m_ctrlTreeParentList.InsertItem( strInfo, pItem);
						m_ctrlTreeParentList.SetItemImage( pItem2, 8, 9, 10, 11 );
						m_ctrlTreeParentList.SetItemState( pItem2, 0, TLIS_SHOWCHECKBOX | TLIS_SHOWLOCKBOX );

						strInfo.Format(_T("输出变量:(ID%d)线信息"),2) ;
						pItem2 = m_ctrlTreeParentList.InsertItem( strInfo, pItem);
						m_ctrlTreeParentList.SetItemImage( pItem2, 8, 9, 10, 11 );
						m_ctrlTreeParentList.SetItemState( pItem2, 0, TLIS_SHOWCHECKBOX | TLIS_SHOWLOCKBOX );

						strInfo.Format(_T("输出变量:(ID%d)横方向夹角"),3) ;
						pItem2 = m_ctrlTreeParentList.InsertItem( strInfo, pItem);
						m_ctrlTreeParentList.SetItemImage( pItem2, 8, 9, 10, 11 );
						m_ctrlTreeParentList.SetItemState( pItem2, 0, TLIS_SHOWCHECKBOX | TLIS_SHOWLOCKBOX );

						strInfo.Format(_T("输出变量:(ID%d)纵方向夹角"),4) ;
						pItem2 = m_ctrlTreeParentList.InsertItem( strInfo, pItem);
						m_ctrlTreeParentList.SetItemImage( pItem2, 8, 9, 10, 11 );
						m_ctrlTreeParentList.SetItemState( pItem2, 0, TLIS_SHOWCHECKBOX | TLIS_SHOWLOCKBOX );

						break;
					}
				default:
					break;
				}
			}
		}

		return ;
	}
	catch (...)
	{
	}
}

void CParaConnectDlg::InitTreeControl()
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		CString strInfo(_T("")) ;

		switch((int)m_pFlowNode->eFlowNodeType)
		{
		case (int)E_TOOL_2DVISION_CAMERA:
			{
				break;
			}
		case (int)E_TOOL_2DVISION_SHAPEMODEL:
			{
				strInfo.Format(_T("(ID%d)标准形状模板"),m_pFlowNode->nFlowNodeID) ;
				break;
			}
		case (int)E_TOOL_2DVISION_FITLINE:
			{
				strInfo.Format(_T("(ID%d)找线"),m_pFlowNode->nFlowNodeID) ;
				break;
			}
		default:
			break;
		}

		CTreeListItem *pItem ;
		pItem = m_ctrlTreeList.InsertItem(strInfo) ;
		m_ctrlTreeList.SetItemImage( pItem, 0, 1, 2, 3 );
		m_ctrlTreeList.SetItemState( pItem, 0, TLIS_SHOWCHECKBOX | TLIS_SHOWLOCKBOX );
		m_ctrlTreeList.SetItemState( pItem, TLIS_EXPANDED );

		for (int i = 0 ;i < m_pFlowNode->treeNode.GetCount();i++)
		{
			CNodeIn *pNodeIn = m_pFlowNode->treeNode.GetAt(m_pFlowNode->treeNode.FindIndex(i)) ;
			CTreeListItem *pItem2 ;
			strInfo = pNodeIn->NodeInLog.strParentTreeNodeOutName.c_str() ;
			pItem2 = m_ctrlTreeList.InsertItem( strInfo, pItem);
			m_ctrlTreeList.SetItemImage( pItem2, 8, 9, 10, 11 );
			m_ctrlTreeList.SetItemState( pItem2, 0, TLIS_SHOWCHECKBOX | TLIS_SHOWLOCKBOX );
		}
	}
	catch (...)
	{
	}
}

LRESULT CParaConnectDlg::OnUpdataChildTreeList(WPARAM wParam, LPARAM lParam)
{
	USES_CONVERSION;
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	CInterfaceWorkFlowDlg *pCurInterfaceWorkFlowDlg = pDlg->m_projectData.m_mgWorkFlowDlg.GetWorkFlowDlgById(pDlg->m_tabWorkFlowDlg.GetCurSel()) ;
	CWorkFlowDlg          *pCurWorkFlowDlg          = pCurInterfaceWorkFlowDlg->pWorkFlowDlg ;
	try
	{
		CString strMessage = (LPCTSTR)(LPCSTR)lParam ;
		int nFlagPosition = strMessage.Find('D') ;
		CString strParentTreeNodeID = strMessage.Mid(nFlagPosition+1,1) ;
		nFlagPosition = strMessage.ReverseFind('D') ;
		CString strParentTreeNodeOutID = strMessage.Mid(nFlagPosition+1,1) ;
		nFlagPosition= strMessage.ReverseFind(')') ;
		CString strNodeOutType = strMessage.Mid(nFlagPosition+1,strMessage.GetLength()-nFlagPosition-1) ;

		//输入判断定参数类型是否满足,图像源是否唯一，输入是否重复
		if (!CheckInputData(_wtoi(strParentTreeNodeID),_wtoi(strParentTreeNodeOutID),GetVisionDataType(strNodeOutType)))
			return 0L ;

		CTreeListItem *pItem,*pItem2;
		pItem = m_ctrlTreeList.GetRootItem() ;
		pItem2 = m_ctrlTreeList.InsertItem( strMessage, pItem);
		m_ctrlTreeList.SetItemImage( pItem2, 8, 9, 10, 11 );
		m_ctrlTreeList.SetItemState( pItem2, 0, TLIS_SHOWCHECKBOX | TLIS_SHOWLOCKBOX );

		CNodeIn *pNodeIn = new CNodeIn() ;
		pNodeIn->NodeInLog.strParentTreeNodeOutName = W2A(strMessage) ;
		pNodeIn->NodeInLog.nParentTreeNodeID        = _wtoi(strParentTreeNodeID) ;
		pNodeIn->NodeInLog.nParentTreeNodeOutID     = _wtoi(strParentTreeNodeOutID) ;
		pNodeIn->eNodeInType                        = GetVisionDataType(strNodeOutType) ;
		m_pFlowNode->treeNode.AddTail(pNodeIn) ;

		//输入参数排序
		SortInputData() ;

		return 1L ;
	}
	catch (...)
	{
		return -1L ;
	}
}

bool CParaConnectDlg::CheckParentNode(CFlowNode *pParentFlowNode,CFlowNode *pFlowNode,CNodeIn *pNodeIn)
{
	try
	{
		if (NULL == pParentFlowNode || NULL == pFlowNode || NULL == pNodeIn)
			return false ;

		//判断父节点类型是否正确
		switch((int)pParentFlowNode->eFlowNodeType)
		{
		case (int)E_TOOL_2DVISION_CAMERA:
			{
				if (E_VDATA_IMAGE != pNodeIn->eNodeInType)
					return false ;

				break;
			}
		case (int)E_TOOL_2DVISION_SHAPEMODEL:
			{
				if (E_VDATA_MATRIX != pNodeIn->eNodeInType)
					return false ;

				break ;
			}
		case (int)E_TOOL_2DVISION_FITLINE:
			{
				if (E_VDATA_IMAGE != pNodeIn->eNodeInType || E_VDATA_MATRIX != pNodeIn->eNodeInType)
					return false ;

				break ;
			}
		default:
			break;
		}

		//判断ID
		if (pParentFlowNode->nFlowNodeID >= pFlowNode->nFlowNodeID)
			return false ;
	}
	catch (...)
	{
		return false ;
	}
	return true ;
}

void CParaConnectDlg::SortInputData()
{
	try
	{
		NodeInList sortTreeNode ;
		sortTreeNode.RemoveAll() ;

		//拷贝链表
		for (int i = 0 ;i < m_pFlowNode->treeNode.GetSize();i++)
		{
			CNodeIn *pNodeIn = m_pFlowNode->treeNode.GetAt(m_pFlowNode->treeNode.FindIndex(i)) ;
			sortTreeNode.AddTail(pNodeIn) ;
		}
		//清空原始链表
		m_pFlowNode->treeNode.RemoveAll() ;

		//排序
		//优先级:图像--》矩阵--》坐标...
		VISION_DATATYPE eVisionDataType[] = {E_VDATA_IMAGE,E_VDATA_MATRIX,E_VDATA_POS} ;
		for (int i = 0 ;i < ARRAYSIZE(eVisionDataType);i++)
		{
			for (int j = 0 ;j < sortTreeNode.GetSize();j++)
			{
				CNodeIn *pNodeIn = sortTreeNode.GetAt(sortTreeNode.FindIndex(j)) ;
				if (eVisionDataType[i] == pNodeIn->eNodeInType)
				{
					m_pFlowNode->treeNode.AddTail(pNodeIn) ;
				}
			}
		}

		sortTreeNode.RemoveAll() ;

		//删除树节点及原有指针
		m_ctrlTreeList.DeleteAllItems() ;
		//重新初始化树
		InitTreeControl() ;
	}
	catch (...)
	{
	}
}

bool CParaConnectDlg::CheckImageData()
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		int nNodeInCount = (int)m_pFlowNode->treeNode.GetSize() ;
		if (nNodeInCount <= 0)
			return true ;

		for (int i = 0 ;i < nNodeInCount ;i++)
		{
			CNodeIn *pNodeIn = m_pFlowNode->treeNode.GetAt(m_pFlowNode->treeNode.FindIndex(i)) ;
			if (E_VDATA_IMAGE == pNodeIn->eNodeInType)
				return false ;
		}
	}
	catch (...)
	{
		return false ;
	}
	return true ;
}

bool CParaConnectDlg::CheckMatrixData(int nParentTreeNodeID,int nParentTreeNodeOutID)
{
	try
	{
		if (nParentTreeNodeOutID != 2)
			return false ;

		int nNodeInCount = (int)m_pFlowNode->treeNode.GetSize() ;
		if (nNodeInCount <= 0)
			return true ;

		for (int i = 0 ;i < nNodeInCount ;i++)
		{
			CNodeIn *pNodeIn = m_pFlowNode->treeNode.GetAt(m_pFlowNode->treeNode.FindIndex(i)) ;
			if (nParentTreeNodeID == pNodeIn->NodeInLog.nParentTreeNodeID &&\
				nParentTreeNodeOutID == pNodeIn->NodeInLog.nParentTreeNodeOutID)
				return false ;
		}
	}
	catch (...)
	{
		return false ;
	}
	return true ;
}

bool CParaConnectDlg::CheckInputData(int nParentTreeNodeID,int nParentTreeNodeOutID,VISION_DATATYPE eNodeInType)
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		VISION_TOOLTYPE eCurNodeInType = m_pFlowNode->eFlowNodeType ;

		CFlowNode *pFlowParentNode = pDlg->m_projectData.m_mgWorkFlowDlg.GetWorkFlowDlgById(pDlg->m_tabWorkFlowDlg.GetCurSel())\
			->pWorkFlowDlg->m_ManageFlowNode.GetFlowNodeById(nParentTreeNodeID) ;

		//判断参数类型是否满足条件
		switch((int)eCurNodeInType)
		{
		case (int)E_TOOL_2DVISION_CAMERA:
			{
				break;
			}
		case (int)E_TOOL_2DVISION_SHAPEMODEL:
			{
				//只允许图像或者模板矩阵输入

				if (E_VDATA_IMAGE == eNodeInType )
				{
					//检查图像源是否唯一
					if (!CheckImageData())
						return false ;
				}
				else if (E_VDATA_MATRIX == eNodeInType)
				{
					//检查数据是否唯一
					if (!CheckMatrixData(nParentTreeNodeID,nParentTreeNodeOutID))
						return false ;
				}
				else return false ;

				break;
			}
		case (int)E_TOOL_2DVISION_FITLINE:
			{
				//只允许图像或者模板矩阵输入
				if (E_VDATA_IMAGE == eNodeInType )
				{
					//检查图像源是否唯一
					if (!CheckImageData())
						return false ;
				}
				else if (E_VDATA_MATRIX == eNodeInType)
				{
					//检查数据是否唯一
					if (!CheckMatrixData(nParentTreeNodeID,nParentTreeNodeOutID))
						return false ;
				}
				else return false ;

				break;
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

void CParaConnectDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	try
	{
		CRect rect;
		GetDlgItem(IDC_TREELIST_CHILDNODE_IN)->GetWindowRect( &rect );
		if (point.x> rect.right || point.x<rect.left ||
			point.y<rect.top ||point.y > rect.bottom )
			return ;

		CMenu menu,*pSubMenu;
		menu.LoadMenu(IDR_MENU_PARACONNECT);
		pSubMenu = menu.GetSubMenu(0);
		pSubMenu->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
	}
	catch (...)
	{
	}
}

void CParaConnectDlg::OnDelInputpara()
{
	USES_CONVERSION;
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();

	try
	{
		int nSel = m_ctrlTreeList.GetSelectionMark() ;
		if (nSel < 0)
		{
			AfxMessageBox(_T("请选中删除")) ;
			return ;
		}

		//删除树节点
		CTreeListItem *pDelItem;
		pDelItem = m_ctrlTreeList.GetSelectedItem();
		if (NULL != pDelItem)
		{
			m_ctrlTreeList.DeleteItem(pDelItem) ;
		}

		int nNodeCount = (int)m_pFlowNode->treeNode.GetSize() ;
		if (nNodeCount <= 0)
			return ;

		CNodeIn *pDelNodeIn = m_pFlowNode->treeNode.GetAt(m_pFlowNode->treeNode.FindIndex(nSel-1)) ;
		DELETE_POINT(pDelNodeIn) ;

		m_pFlowNode->treeNode.RemoveAt(m_pFlowNode->treeNode.FindIndex(nSel-1)) ;
	}
	catch (...)
	{
	}
}