#pragma once
// CVision2DLogicPanelDlg 对话框

class CVision2DLogicPanelDlg : public CPropertyPage
{
	DECLARE_DYNAMIC(CVision2DLogicPanelDlg)
	DECLARE_EASYSIZE
public:
	CBrush m_brushBk ;
	CWinXPButtonST m_btnDistancePP;
	CWinXPButtonST m_btnDistancePL;
	CWinXPButtonST m_btnProjectPL;
	CWinXPButtonST m_btnIntersectionLL;
	CWinXPButtonST m_btnAngleLL;

private:
	void InitAllControl() ;
	void InitBtnControl() ;
public:
	CVision2DLogicPanelDlg();
	virtual ~CVision2DLogicPanelDlg();

// 对话框数据
	enum { IDD = IDD_VISION2DLOGIC_PANEL_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//双击获取工具ID
	afx_msg void OnButtonClicked(UINT uBtnId) ;
};
