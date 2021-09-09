#pragma once
// CManageProjectDlg �Ի���
#include "NewDlg.h"

class CManageProjectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CManageProjectDlg)
public:
	CBrush             m_brushBk ;
	CImageList         m_ImageList ;
	CListBoxST         m_listProject;
	CWinXPButtonST     m_btnAdd;
	CWinXPButtonST     m_btnDel;
	CWinXPButtonST     m_btnLoad;
	CWinXPButtonST     m_btnSave;
	CWinXPButtonST     m_btnExit;
	CNewLabel          m_labelInfo;

private:
	void InitAllControl() ;
	void InitBtnControl() ;
	void InitListControl() ;
	void InitLabelControl() ;
	void InitImageList() ;
public:
	void UpdateControl() ;
	void BtnAddProject() ;
	void BtnDelProject() ;
	void BtnLoadProject() ;
	void BtnSaveProject() ;
public:
	CManageProjectDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CManageProjectDlg();

// �Ի�������
	enum { IDD = IDD_MANAGE_PROJECT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonClicked(UINT uBtnId) ;
};
