#pragma once // CVisionSystemPanelDlg 对话框

class CVisionSystemPanelDlg : public CPropertyPage
{
	DECLARE_DYNAMIC(CVisionSystemPanelDlg)
	DECLARE_EASYSIZE
public:
	CBrush m_brushBk ;
	CWinXPButtonST m_btnLuaScript;
	CWinXPButtonST m_btnCommRecv;
	CWinXPButtonST m_btnCommSend;
	CWinXPButtonST m_btnModbusRecv;
	CWinXPButtonST m_btnModbusSend;

private:
	void InitAllControl() ;
	void InitBtnControl() ;
public:
	CVisionSystemPanelDlg();
	virtual ~CVisionSystemPanelDlg();

// 对话框数据
	enum { IDD = IDD_VISIONSYSTEM_PANEL_DIALOG };

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
