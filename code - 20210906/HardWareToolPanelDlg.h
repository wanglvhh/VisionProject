#pragma once
// CHardWareToolPanelDlg �Ի���

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

// �Ի�������
	enum { IDD = IDD_HARDWARE_PANEL_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//������������ȡ����ID
	afx_msg void OnButtonClicked(UINT uBtnId) ;
};
