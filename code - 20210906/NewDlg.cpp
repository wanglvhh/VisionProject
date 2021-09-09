// NewDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VisionProject.h"
#include "NewDlg.h"
#include "afxdialogex.h"

// CNewDlg �Ի���
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(CNewDlg, CDialogEx)

CNewDlg::CNewDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNewDlg::IDD, pParent)
	, m_strInfo(_T(""))
{
}

CNewDlg::~CNewDlg()
{
}

void CNewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_INFO, m_strInfo);
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
}

BEGIN_MESSAGE_MAP(CNewDlg, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_INFO, &CNewDlg::OnEnChangeEditInfo)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

// CNewDlg ��Ϣ�������

BOOL CNewDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_brushBk.CreateSolidBrush(SYSTEM_BK_COLOR);
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GetDlgItem(IDC_STATIC_INFO)->SetWindowText(m_strStaticInfo) ;
	UpdateData(false) ;

	InitAllControl() ;

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CNewDlg::OnEnChangeEditInfo()
{
	UpdateData(TRUE) ;
}

HBRUSH CNewDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return m_brushBk;
}

void CNewDlg::InitAllControl()
{
	try
	{
		//��ʼ��button�ؼ�
		InitBtnControl()  ;
	}
	catch (...)
	{
	}
}

void CNewDlg::InitBtnControl()
{
	try
	{
		m_btnOk.SetIcon(IDI_ICON_OK) ;
		m_btnOk.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnOk.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnOk.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnOk.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnOk.SetRounded(TRUE) ;

		m_btnCancel.SetIcon(IDI_ICON_CANCEL) ;
		m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnCancel.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnCancel.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnCancel.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnCancel.SetRounded(TRUE) ;
	}
	catch (...)
	{
	}
}