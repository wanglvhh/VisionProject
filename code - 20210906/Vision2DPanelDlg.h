#pragma once
// CVision2DPanelDlg 对话框

class CVision2DPanelDlg : public CPropertyPage
{
	DECLARE_DYNAMIC(CVision2DPanelDlg)
	DECLARE_EASYSIZE
public:
	CBrush m_brushBk ;
	CWinXPButtonST m_btnShapeModel;
	CWinXPButtonST m_btnScaleShapeModel;
	CWinXPButtonST m_btnNccModel;
	CWinXPButtonST m_btnContourModel;
	CWinXPButtonST m_btnScaleContourModel;
	CWinXPButtonST m_btnFitLine;
	CWinXPButtonST m_btnFitCircle;
	CWinXPButtonST m_btnFitArc;
	CWinXPButtonST m_btnBlob;

private:
	void InitAllControl() ;
	void InitBtnControl() ;
public:
	CVision2DPanelDlg();
	virtual ~CVision2DPanelDlg();

// 对话框数据
	enum { IDD = IDD_VISION2D_PANEL_DIALOG };

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
