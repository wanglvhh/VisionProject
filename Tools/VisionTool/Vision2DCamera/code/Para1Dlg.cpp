// Para1Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Vision2DCamera.h"
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
{
	m_lExposureTime = 0 ;
	m_lGain = 0 ;
}

CPara1Dlg::~CPara1Dlg()
{
}

void CPara1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_EXPOSURETIME, m_sliderExposureTime);
	DDX_Control(pDX, IDC_SLIDER_GAIN, m_sliderGain);
}

BEGIN_MESSAGE_MAP(CPara1Dlg, CDialogEx)
	ON_WM_CTLCOLOR()
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
		//��ʼ��SliderControl
		InitSliderControl() ;
	}
	catch (...)
	{
	}
}

void CPara1Dlg::InitSliderControl()
{
	try
	{
		m_sliderExposureTime.SetRange(m_lMinExposureTime,m_lMaxExposureTime) ;
		m_sliderExposureTime.SetTicFreq(10) ;
		m_sliderExposureTime.SetPageSize(1000);
		m_sliderExposureTime._IsEnabled()?m_sliderExposureTime._EnableBorders(FALSE):m_sliderExposureTime._EnableBorders(TRUE);
		//������ɫ
		m_sliderExposureTime._SetBkColor(SYSTEM_BK_COLOR);
		m_sliderExposureTime._SetThumbColor(SYSTEM_RED);
		m_sliderExposureTime._SetChColor(SYSTEM_BLUE);

		m_sliderGain.SetRange(m_lMinGain,m_lMaxGain) ;
		m_sliderGain.SetTicFreq(10) ;
		m_sliderGain.SetPageSize(1);
		m_sliderGain._IsEnabled()?m_sliderGain._EnableBorders(FALSE):m_sliderGain._EnableBorders(TRUE);
		//������ɫ
		m_sliderGain._SetBkColor(SYSTEM_BK_COLOR);
		m_sliderGain._SetThumbColor(SYSTEM_RED);
		m_sliderGain._SetChColor(SYSTEM_BLUE);
	}
	catch (...)
	{
	}
}

BOOL CPara1Dlg::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	//ʹ��AfxGetMainWnd()����MainDlg��� һ������Ƴ�Ӧ�ó������� �Ҳ������屨��
	//CMainDlg *pDlg = (CMainDlg *)AfxGetMainWnd();
	CMainDlg *pDlg = (CMainDlg *)FindWindow(NULL, _T("�������")) ;
	/*if (NULL == pDlg)
	{
	}*/
	try
	{
		CString lpszValue;
		NMHDR *pParam = reinterpret_cast<NMHDR*>(lParam);
		if(pParam->hwndFrom == m_sliderExposureTime.m_hWnd)
		{
			m_lExposureTime = m_sliderExposureTime.GetPos();
			if (m_lExposureTime < 0)
				return CDialog::OnNotify(wParam, lParam, pResult) ;

			//�����ع�
			if (E_CAMERA_OK != pDlg->m_pCameraNode->pCameraBase->Camera_SetExposureTime((long)m_lExposureTime))
				return CDialog::OnNotify(wParam, lParam, pResult) ;

			m_sliderExposureTime.SetPos(m_lExposureTime);
			lpszValue.Format(_T("%d"),m_lExposureTime);
			GetDlgItem(IDC_EDIT_EXPOSURETIME)->SetWindowText(lpszValue);
		}
		if(pParam->hwndFrom == m_sliderGain.m_hWnd)
		{
			m_lGain = m_sliderGain.GetPos();
			if (m_lGain < 0)
				return CDialog::OnNotify(wParam, lParam, pResult) ;

			//��������
			if (E_CAMERA_OK != pDlg->m_pCameraNode->pCameraBase->Camera_SetGain((long)m_lGain))
				return CDialog::OnNotify(wParam, lParam, pResult) ;

			m_sliderGain.SetPos(m_lGain);
			lpszValue.Format(_T("%d"),m_lGain);
			GetDlgItem(IDC_EDIT_GAIN)->SetWindowText(lpszValue);
		}
	}
	catch (...)
	{
	}
	return CDialog::OnNotify(wParam, lParam, pResult);
}

void CPara1Dlg::UpdateAllControl()
{
	CMainDlg *pDlg = (CMainDlg *)FindWindow(NULL, _T("�������")) ;
	try
	{
		CString lpszValue;
		//�����ع�
		if (E_CAMERA_OK != pDlg->m_pCameraNode->pCameraBase->Camera_SetExposureTime((long)m_lExposureTime))
		{
			AfxMessageBox(_T("�����ع�ʧ��")) ;
			return  ;
		}

		m_sliderExposureTime.SetPos(m_lExposureTime);
		lpszValue.Format(_T("%d"),m_lExposureTime);
		GetDlgItem(IDC_EDIT_EXPOSURETIME)->SetWindowText(lpszValue);

		//��������
		if (E_CAMERA_OK != pDlg->m_pCameraNode->pCameraBase->Camera_SetGain((long)m_lGain))
		{
			AfxMessageBox(_T("��������ʧ��")) ;
			return  ;
		}

		m_sliderGain.SetPos(m_lGain);
		lpszValue.Format(_T("%d"),m_lGain);
		GetDlgItem(IDC_EDIT_GAIN)->SetWindowText(lpszValue);
	}
	catch (...)
	{
	}
}