#pragma once
// CHardWareToolPanelDlg 对话框

class CHardWareToolPanelDlg : public CPropertyPage
{
	DECLARE_DYNAMIC(CHardWareToolPanelDlg)
	DECLARE_EASYSIZE
public:
	CBrush m_brushBk ;
	CWinXPButtonST m_btn2DCamera;
	CWinXPButtonST m_btnLed;
	/*CWinXPButtonST m_btnLotsLed;
	CWinXPButtonST m_btnCstLed;*/

private:
	void InitAllControl() ;
	void InitBtnControl() ;
public:
	CHardWareToolPanelDlg();
	virtual ~CHardWareToolPanelDlg();

// 对话框数据
	enum { IDD = IDD_HARDWARE_PANEL_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//鼠标左键单击获取工具ID
	afx_msg void OnButtonClicked(UINT uBtnId) ;
};
