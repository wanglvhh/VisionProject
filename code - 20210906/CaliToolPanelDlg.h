#pragma once
// CCaliToolPanelDlg 对话框

class CCaliToolPanelDlg : public CPropertyPage
{
	DECLARE_DYNAMIC(CCaliToolPanelDlg)
	DECLARE_EASYSIZE
public:
	CBrush m_brushBk ;
	CWinXPButtonST m_btnNineCali;
	CWinXPButtonST m_btnNineCaliReally;

private:
	void InitAllControl() ;
	void InitBtnControl() ;
public:
	CCaliToolPanelDlg();
	virtual ~CCaliToolPanelDlg();

// 对话框数据
	enum { IDD = IDD_CALIBRATION_PANEL_DIALOG };

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
