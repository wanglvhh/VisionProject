// Para1Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VisionCommWrite.h"
#include "Para1Dlg.h"
#include "afxdialogex.h"
#include "MainDlg.h"

// CPara1Dlg �Ի���
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(CPara1Dlg, CDialogEx)

CPara1Dlg::CPara1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPara1Dlg::IDD, pParent)
	, m_strSendData(_T(""))
{
}

CPara1Dlg::~CPara1Dlg()
{
}

void CPara1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SENDDATA, m_strSendData);
}

BEGIN_MESSAGE_MAP(CPara1Dlg, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_EN_CHANGE(IDC_EDIT_SENDDATA, &CPara1Dlg::OnEnChangeEditSenddata)
END_MESSAGE_MAP()

// CPara1Dlg ��Ϣ�������

BOOL CPara1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_brush.CreateSolidBrush(SYSTEM_BK_COLOR) ;

	InitAllControl() ;

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

HBRUSH CPara1Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return m_brush;
}

void CPara1Dlg::InitAllControl()
{
	try
	{
		return ;
	}
	catch (...)
	{
	}
}

void CPara1Dlg::UpdateAllControl()
{
	CMainDlg *pDlg = (CMainDlg *)FindWindow(NULL, _T("ͨ��д��")) ;
	try
	{
		UpdateData(FALSE) ;
	}
	catch (...)
	{
	}
}

void CPara1Dlg::OnEnChangeEditSenddata()
{
	UpdateData(TRUE) ;
}