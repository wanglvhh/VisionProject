#pragma once

/*********************************************************************************************************************************************************************
//                                                                          WorkFlowNode(工作流程工具节点)                                                                            //
//                                                                                |																					//
//                                                                                |																					//
//                                               -----------------------------------------------------------------------------										//
//                                               |                                                                            |										//
//                                               |                                                                            |										//
//                                       ParentToolTreeControl(父节点工具树)                                           TreeControl(当前工具节点参数树)			    //
//                                  -----------------------------                                                             |										//
//                                 |                             |                                              			  |										//
//                                 |							 |					         			                 TreeNode(当前工具节点)						//
//                (工具节点1) ParentTreeNode1  .....    ParentTreeNoden(工具节点n)                                            |										//
//                                 |                             |                                                            |										//
//                                 |                             |                                                  -----------------------							//
//                        ---------------------          --------------------                                      |                      |  						//
//                        |                    |         |                   |                                     |                      | 						//
//                        |                    |         |                   |                    (输入参数节点) NodeIn1      ......    NodeInn	                	//
//      (输出参数节点) NodeOut11  ......   NodeOut1n   NodeOutn1   ......   NodeOutnn                               |												//
//                        |     													         				        |												//
//                        |     													         		 -------------------------------								//
//              -----------------------     										         		 |              |               | 								//
//              |                      |											         		 |              |               | 								//
//              |               	   |                                                      VISION_DATATYPE   VisionDataBase   NodeLogIn							//
//  （输出参数）VISION_DATATYPE  VisionDataBase                ......                                                                |								//
//                             														         										 |								//
//                             														         	      ------------------------------------------------------		//
//  																				         		  |                            |                        | 		//
//																					         		  |                            |                        | 		//
//                                                                                          nParentTreeNodeID       nParentTreeNodeOutID   strParentTreeNodeOutName	//
//																					         																		//
//																																									//
//																																									//
*********************************************************************************************************************************************************************/

//工具与工具节点参数关联:树形数据结构
struct NodeLogIn
{
public:
	int nParentTreeNodeID ;
	int nParentTreeNodeOutID ;
	string strParentTreeNodeOutName;

	NodeLogIn()
	{
		nParentTreeNodeID           = -1 ;
		nParentTreeNodeOutID        = -1 ;
		strParentTreeNodeOutName    = "" ;
	}

	~NodeLogIn()
	{
		nParentTreeNodeID           = -1 ;
		nParentTreeNodeOutID        = -1 ;
		strParentTreeNodeOutName    = "" ;
	}
	NodeLogIn ( const NodeLogIn& src )
	{
		USES_CONVERSION ;
		nParentTreeNodeID           = src.nParentTreeNodeID ;
		nParentTreeNodeOutID        = src.nParentTreeNodeOutID ;
		strParentTreeNodeOutName    = src.strParentTreeNodeOutName ;
	}

	NodeLogIn& operator= ( const NodeLogIn& src )
	{
		if ( &src == this )
			return *this ;

		USES_CONVERSION ;
		nParentTreeNodeID           = src.nParentTreeNodeID ;
		nParentTreeNodeOutID        = src.nParentTreeNodeOutID ;
		strParentTreeNodeOutName    = src.strParentTreeNodeOutName ;

		return *this ;
	}
};

class CNodeIn:public CObject
{
public:
	CNodeIn()
	{
		eNodeInType = E_VDATA_NONE ;
	}

	~CNodeIn()
	{
		eNodeInType = E_VDATA_NONE ;
	}

	CNodeIn ( const CNodeIn& src )
	{
		eNodeInType = src.eNodeInType ;
		NodeInLog = src.NodeInLog ;
	}

	CNodeIn& operator= ( const CNodeIn& src )
	{
		if ( &src == this )
			return *this ;

		eNodeInType = src.eNodeInType ;
		NodeInLog = src.NodeInLog ;

		return *this ;
	}

public:
	//参数类型
	VISION_DATATYPE     eNodeInType ;
	//参数变量
	//VisionDataBase*     pNodeInData ;
	//参数追溯
	NodeLogIn           NodeInLog ;
};

typedef CTypedPtrList<CObList, CNodeIn *> NodeInList ;

class CNodeOut:public CObject
{
public:
	CNodeOut()
	{
		eNodeOutType = E_VDATA_NONE ;
		//pNodeOutData = NULL ;
	}
	~CNodeOut()
	{
		eNodeOutType = E_VDATA_NONE ;
		//DELETE_POINT(pNodeOutData) ;
	}

public:
	//参数类型
	VISION_DATATYPE     eNodeOutType ;
	//参数变量
	//VisionDataBase*     pNodeOutData ;
};

typedef CTypedPtrList<CObList, CNodeOut *> NodeOutList ;

typedef CTypedPtrList<CObList,NodeOutList *> ParentTreeNodeList ;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Flow节点元素
class CFlowNode:public CObject
{
public:
	CFlowNode()
	{
		nFlowNodeID = -1 ;
		eFlowNodeType = E_TOOL_NONE ;
		pVisionBase = NULL ;
	}

	~CFlowNode()
	{
		nFlowNodeID = -1 ;
		eFlowNodeType = E_TOOL_NONE ;
		DELETE_POINT(pVisionBase) ;
	}

	CFlowNode & operator=(const CFlowNode &src)
	{
		if ( this == &src )
			return *this;

		return *this;
	}

public:
	int                      nFlowNodeID ;
	VISION_TOOLTYPE          eFlowNodeType ;
	CVisionBase*             pVisionBase ;
	CMgrDllVisionBaseIm      mgrDllVisionBaseIm ;
	NodeInList               treeNode ;
};

//对外接口FlowNode数据链表
typedef CTypedPtrList<CObList, CFlowNode *> FlowNodeList;

//管理FlowNode
class CManageFlowNode
{
public:
	CManageFlowNode()
	{
		flowNodeList.RemoveAll() ;
	}

	~CManageFlowNode()
	{
		flowNodeList.RemoveAll() ;
	}

	int GetFlowNodeListSize()
	{
		return (int)flowNodeList.GetSize() ;
	}

	void AddTail(CFlowNode *pNewFlowNode)
	{
		if (pNewFlowNode)
		{
			flowNodeList.AddTail(pNewFlowNode) ;
		}
	}

	void RemoveAtById(int nFlowNodeID)
	{
		if (GetFlowNodeListSize() <= 0)
		{
			return  ;
		}

		POSITION prev;
		POSITION pos = flowNodeList.GetHeadPosition() ;
		while(pos)
		{
			prev = pos ;
			CFlowNode *pFlowNode = flowNodeList.GetNext(pos) ;
			if (nFlowNodeID == pFlowNode->nFlowNodeID)
			{
				flowNodeList.RemoveAt(prev) ;
				pFlowNode->pVisionBase->Vision_Release() ;
				DELETE_POINT(pFlowNode) ;

				break;
			}
		}
	}

	void RemoveAll()
	{
		flowNodeList.RemoveAll() ;
	}

	void ReSortById()
	{
		if (GetFlowNodeListSize() <= 0)
		{
			return  ;
		}

		int nIndex = 0 ;
		POSITION pos = flowNodeList.GetHeadPosition() ;
		while(pos)
		{
			CFlowNode *pFlowNode = flowNodeList.GetNext(pos) ;
			pFlowNode->nFlowNodeID = nIndex++ ;
		}
	}

	CFlowNode* GetFlowNodeById(int nFlowNodeID)
	{
		if (GetFlowNodeListSize() <= 0)
		{
			return NULL ;
		}

		POSITION pos = flowNodeList.GetHeadPosition() ;
		while(pos)
		{
			CFlowNode *pFlowNode = flowNodeList.GetNext(pos) ;
			if (nFlowNodeID == pFlowNode->nFlowNodeID)
			{
				return pFlowNode ;
				//break;
			}
		}

		return NULL ;
	}
public:
	FlowNodeList flowNodeList ;
};
