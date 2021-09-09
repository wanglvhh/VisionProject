#pragma once

// CSplashWindowDlg 对话框

class CSplashWindowDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSplashWindowDlg)

private:
	CBitmapCtrl	m_BitmapCtrl;
	CFont		m_Font;

	CRect		m_rtWnd;
	int			m_nFonHeight;
public:
	void	LoadBitmap(UINT nID);
	void	ShowTip(LPCTSTR lpszTip);
public:
	CSplashWindowDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSplashWindowDlg();

// 对话框数据
	enum { IDD = IDD_SPLASH_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
