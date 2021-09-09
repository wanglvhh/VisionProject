#pragma once

// CManageViarentDlg 对话框

class CManageViarentDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CManageViarentDlg)
public:
	CListCtrlCl m_listLuaGobalViarent;
	CWinXPButtonST m_btnAdd;
	CWinXPButtonST m_btnEdit;
	CWinXPButtonST m_btnDel;
	CWinXPButtonST m_btnSave;
	CWinXPButtonST m_btnCancel;

	enum LISTLUAGOBALVIARENT
	{
		E_LUAGOBALVIARENT_ID = 0,
		E_LUAGOBALVIARENT_NAME,
		E_LUAGOBALVIARENT_TYPE,
		E_LUAGOBALVIARENT_VALUE,
		E_LUAGOBALVIARENT_TIPINFO,
	};
private:
	void InitAllControl() ;
	void InitBtnControl() ;
	void InitListControl() ;

public:
	void UpdataListControl() ;

public:
	CManageViarentDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CManageViarentDlg();

// 对话框数据
	enum { IDD = IDD_MANAGEVIARENT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnEdit();
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnNMDblclkListLuagobalviarent(NMHDR *pNMHDR, LRESULT *pResult);
};
