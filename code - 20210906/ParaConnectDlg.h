#pragma once
#include "MyTreeListCtrl.h"
// CParaConnectDlg 对话框

class CParaConnectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CParaConnectDlg)
public:
	CWinXPButtonST m_btnOk;
	CWinXPButtonST m_btnCancel;
	CImageList  m_ImageList;
	// 当前节点所有父节点输出树
	CMyTreeListCtrl m_ctrlTreeParentList;
	// 当前节点输入树
	CMyTreeListCtrl m_ctrlTreeList;
	//当前工具节点
	CFlowNode*     m_pFlowNode ;

private:
	void InitAllControl() ;
	void InitBtnControl() ;
public:
	void InitTreeList() ;
	void InitParentTreeControl() ;
	void InitTreeControl() ;
	void SearchParentTool(int nStartFlowNodeId,int nEndFlowNodeId,int nSearchRange,VISION_TOOLTYPE eSearchType[]) ;
	bool CheckParentNode(CFlowNode *pParentFlowNode,CFlowNode *pFlowNode,CNodeIn *pNodeIn) ;
	bool CheckInputData(int nParentTreeNodeID,int nParentTreeNodeOutID,VISION_DATATYPE eNodeInType) ;
	bool CheckImageData() ;
	bool CheckMatrixData(int nParentTreeNodeID,int nParentTreeNodeOutID) ;
	void SortInputData() ;
public:
	CParaConnectDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CParaConnectDlg();

// 对话框数据
	enum { IDD = IDD_PARACONNECT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnUpdataChildTreeList(WPARAM wParam, LPARAM lParam) ;
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnDelInputpara();
};
