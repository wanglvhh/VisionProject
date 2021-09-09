#pragma once
#include "MyTreeListCtrl.h"
// CParaConnectDlg �Ի���

class CParaConnectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CParaConnectDlg)
public:
	CWinXPButtonST m_btnOk;
	CWinXPButtonST m_btnCancel;
	CImageList  m_ImageList;
	// ��ǰ�ڵ����и��ڵ������
	CMyTreeListCtrl m_ctrlTreeParentList;
	// ��ǰ�ڵ�������
	CMyTreeListCtrl m_ctrlTreeList;
	//��ǰ���߽ڵ�
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
	CParaConnectDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CParaConnectDlg();

// �Ի�������
	enum { IDD = IDD_PARACONNECT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnUpdataChildTreeList(WPARAM wParam, LPARAM lParam) ;
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnDelInputpara();
};
