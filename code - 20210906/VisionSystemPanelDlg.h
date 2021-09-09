#pragma once // CVisionSystemPanelDlg �Ի���

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

// �Ի�������
	enum { IDD = IDD_VISIONSYSTEM_PANEL_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//˫����ȡ����ID
	afx_msg void OnButtonClicked(UINT uBtnId) ;
};
