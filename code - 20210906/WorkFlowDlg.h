#pragma once

// CWorkFlowDlg 对话框
class CInterfaceWorkFlowDlg;
class CWorkFlowDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CWorkFlowDlg)
	DECLARE_EASYSIZE
public:
	CBrush             m_brushBk ;
	CImageList         m_ImageList ;
	CListBoxST         m_ListWorkFlow;
	CManageFlowNode    m_ManageFlowNode ;
	CString            m_strWorkFlowDlgName ;
private:
public:
	void InitImageList() ;
	void ReplaceImageList(CFlowNode *pSourceFlowNode,CFlowNode *pDstFlowNode) ;
	void UpdateList() ;
	void ReUpdateList(int nStartPos) ;
	void ResetAllTreeNode() ;
	bool GetCameraList(CStringArray &arrayCameraInfo) ;
	bool GetCommList(CStringArray &arrayCommInfo) ;
	bool GetFlowNodeName(CFlowNode *pFlowNode,CString &strName) ;

public:
	CWorkFlowDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWorkFlowDlg();

// 对话框数据
	enum { IDD = IDD_WROKFLOW_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnToolAdd();
	afx_msg void OnToolDel();
	afx_msg void OnToolMoveup();
	afx_msg void OnToolMovedown();
	afx_msg void OnParaconnect();
	afx_msg void OnLbnDblclkListWorkflow();
	afx_msg void OnAddScript();
	afx_msg void OnEditScript();
};

//WorkFlowDlg对话框元素
class CInterfaceWorkFlowDlg:public CObject
{
public:
	CInterfaceWorkFlowDlg()
	{
		strWorkFlowDlgName   = _T("") ;
		nWorkFlowDlgID       = -1 ;
		pWorkFlowDlg         = NULL ;
	}

	virtual ~CInterfaceWorkFlowDlg()
	{
		strWorkFlowDlgName   = _T("") ;
		nWorkFlowDlgID       = -1 ;
		DELETE_POINT(pWorkFlowDlg) ;
	}

	CInterfaceWorkFlowDlg & operator=(const CInterfaceWorkFlowDlg &src)
	{
		if ( this == &src )
			return *this;

		pWorkFlowDlg        = src.pWorkFlowDlg ;
		strWorkFlowDlgName  = src.strWorkFlowDlgName ;
		nWorkFlowDlgID      = src.nWorkFlowDlgID ;

		return *this;
	}

public:
	CWorkFlowDlg*   pWorkFlowDlg ;
	CString         strWorkFlowDlgName ;
	int             nWorkFlowDlgID ;
};

//对外接口WorkFlowDlg数据链表
typedef CTypedPtrList<CObList, CInterfaceWorkFlowDlg *> InterfaceWorkFlowDlgList;

//管理WorkFlowDlg
class CManageWorkFlowDlg
{
public:
	CManageWorkFlowDlg()
	{
		workFlowDlgList.RemoveAll() ;
	}

	~CManageWorkFlowDlg()
	{
		workFlowDlgList.RemoveAll() ;
	}

	int GetWorkFlowDlgListSize()
	{
		return (int)workFlowDlgList.GetSize() ;
	}

	void AddTail(CInterfaceWorkFlowDlg *pNewWorkFlowDlg)
	{
		workFlowDlgList.AddTail(pNewWorkFlowDlg) ;
	}

	void RemoveAtByName(CString strWorkFlowDlgName)
	{
		if (GetWorkFlowDlgListSize() <= 0)
		{
			return  ;
		}

		POSITION prev;
		POSITION pos = workFlowDlgList.GetHeadPosition() ;
		while(pos)
		{
			prev = pos ;
			CInterfaceWorkFlowDlg *pWorkFlowDlg = workFlowDlgList.GetNext(pos) ;
			if (strWorkFlowDlgName == pWorkFlowDlg->strWorkFlowDlgName)
			{
				workFlowDlgList.RemoveAt(prev) ;
				DELETE_POINT(pWorkFlowDlg) ;

				break;
			}
		}
	}

	void RemoveAtById(int nWorkFlowDlgID)
	{
		if (GetWorkFlowDlgListSize() <= 0)
		{
			return  ;
		}

		POSITION prev;
		POSITION pos = workFlowDlgList.GetHeadPosition() ;
		while(pos)
		{
			prev = pos ;
			CInterfaceWorkFlowDlg *pWorkFlowDlg = workFlowDlgList.GetNext(pos) ;
			if (nWorkFlowDlgID == pWorkFlowDlg->nWorkFlowDlgID)
			{
				workFlowDlgList.RemoveAt(prev) ;
				DELETE_POINT(pWorkFlowDlg) ;

				break;
			}
		}
	}

	void RemoveAll()
	{
		workFlowDlgList.RemoveAll() ;
	}

	CInterfaceWorkFlowDlg* GetWorkFlowDlgByName(CString strWorkFlowDlgName)
	{
		if (GetWorkFlowDlgListSize() <= 0)
		{
			return NULL ;
		}

		POSITION pos = workFlowDlgList.GetHeadPosition() ;
		while(pos)
		{
			CInterfaceWorkFlowDlg *pWorkFlowDlg = workFlowDlgList.GetNext(pos) ;
			if (strWorkFlowDlgName == pWorkFlowDlg->strWorkFlowDlgName)
			{
				return pWorkFlowDlg ;
				//break;
			}
		}

		return NULL ;
	}

	CInterfaceWorkFlowDlg* GetWorkFlowDlgById(int nWorkFlowDlgID)
	{
		if (GetWorkFlowDlgListSize() <= 0)
		{
			return NULL ;
		}

		POSITION pos = workFlowDlgList.GetHeadPosition() ;
		while(pos)
		{
			CInterfaceWorkFlowDlg *pWorkFlowDlg = workFlowDlgList.GetNext(pos) ;
			if (nWorkFlowDlgID == pWorkFlowDlg->nWorkFlowDlgID)
			{
				return pWorkFlowDlg ;
			}
		}

		return NULL ;
	}

public:
	InterfaceWorkFlowDlgList workFlowDlgList ;
};