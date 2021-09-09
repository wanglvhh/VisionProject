// MainDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Vision2DCamera.h"
#include "MainDlg.h"
#include "afxdialogex.h"

// CMainDlg �Ի���
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(CMainDlg, CDialogEx)

CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMainDlg::IDD, pParent)
{
}

CMainDlg::~CMainDlg()
{
	HalconCpp::CloseWindow(m_lWindowID) ;
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CAMERALIST, m_comboCameraList);
	DDX_Control(pDX, IDC_STATIC_VIEW, m_ctlImageView);
	DDX_Control(pDX, IDC_TAB_PARA, m_tabPara);
	DDX_Control(pDX, IDC_BTN_RUN, m_btnRun);
	DDX_Control(pDX, IDC_BTN_RUNCYCLE, m_btnRunCycle);
	DDX_Control(pDX, IDC_BTN_LOAD, m_btnLoad);
	DDX_Control(pDX, IDC_BTN_SAVE, m_btnSave);
	DDX_Control(pDX, IDC_BTN_CLOSE, m_btnClose);
	DDX_Control(pDX, IDC_STATIC_ROW, m_labelRow);
	DDX_Control(pDX, IDC_STATIC_COL, m_labelCol);
	DDX_Control(pDX, IDC_STATIC_GRAY, m_labelGray);
	DDX_Control(pDX, IDC_STATIC_INFO, m_labelInfo);
}

BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_RUN, IDC_BTN_CLOSE, OnButtonClicked)
END_MESSAGE_MAP()

// CMainDlg ��Ϣ�������

BOOL CMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitAllControl() ;

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CMainDlg::InitAllControl()
{
	try
	{
		//��ʼ��BtnControl
		InitBtnControl() ;
		//��ʼ��ComboControl
		InitComboControl() ;
		//��ʼ��ViewControl
		InitViewControl() ;
		//��ʼ��NewlabelControl
		InitLabelControl() ;
		//��ʼ��TabControl
		InitTabControl() ;

		//����AllControl
		m_para1Dlg.UpdateAllControl() ;
	}
	catch (...)
	{
	}
}

void CMainDlg::InitBtnControl()
{
	try
	{
		m_btnRun.SetIcon(IDI_ICON_TSTRUN) ;
		m_btnRun.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnRun.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnRun.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnRun.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnRun.SetRounded(TRUE) ;

		m_btnRunCycle.SetIcon(IDI_ICON_CYCLE) ;
		m_btnRunCycle.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnRunCycle.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnRunCycle.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnRunCycle.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnRunCycle.SetRounded(TRUE) ;

		m_btnLoad.SetIcon(IDI_ICON_LOAD) ;
		m_btnLoad.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnLoad.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnLoad.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnLoad.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnLoad.SetRounded(TRUE) ;

		m_btnSave.SetIcon(IDI_ICON_SAVE) ;
		m_btnSave.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnSave.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnSave.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnSave.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnSave.SetRounded(TRUE) ;

		m_btnClose.SetIcon(IDI_ICON_EXIT) ;
		m_btnClose.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnClose.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnClose.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnClose.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnClose.SetRounded(TRUE) ;
	}
	catch (...)
	{
	}
}

void CMainDlg::InitComboControl()
{
	try
	{
		m_comboCameraList.SnShowImage(_T(".\\res\\bmp\\drop_down.bmp"), 3, 2, SKIN_STATUS_NOR, FALSE);
		m_comboCameraList.SnShowImage(_T(".\\res\\bmp\\drop_down.bmp"), 3, 3, SKIN_STATUS_HOT, FALSE);

		m_comboCameraList.AddString(m_strCameraInfo) ;
		m_comboCameraList.SetCurSel(0) ;
	}
	catch (...)
	{
	}
}

void CMainDlg::InitViewControl()
{
	try
	{
		long lWindowID=0;
		CRect Rect;
		int nCtrlWidth,nCtrlHeight ;

		m_ctlImageView.GetClientRect(Rect);
		nCtrlWidth =Rect.Width();
		nCtrlHeight=Rect.Height();
		m_dbRatioWh = (double)nCtrlWidth/(double)nCtrlHeight ;
		lWindowID = (long)m_ctlImageView.GetSafeHwnd();
		InitStaticView(lWindowID,E_CAMERA_ROTATE_0,nCtrlWidth,nCtrlHeight,m_pCameraNode->nImageWidth,m_pCameraNode->nImageHeight,m_dbRatioWh,&m_lWindowID) ;

		//�󶨻ص���ʾ����
		ASSERT_POINT(m_pCameraNode) ;
		m_pCameraNode->pCameraBase->Camera_SetOwner(this,CallDispImage) ;
	}
	catch (...)
	{
	}
}

void CMainDlg::InitLabelControl()
{
	try
	{
		CNewLabel *pCtrl[]={ &m_labelRow, &m_labelCol,&m_labelGray, &m_labelInfo };
		for (int i = 0 ;i < ARRSIZE(pCtrl);i++)
		{
			pCtrl[i]->SetFontBold(TRUE);
			//pCtrl[i]->SetFontName(_T("΢���ź�"));
			pCtrl[i]->SetFontSize(10);
			pCtrl[i]->SetTextColor(SYSTEM_GREEN);
			pCtrl[i]->SetBorder(TRUE);
			pCtrl[i]->SetBkColor(SYSTEM_BLACK);
			pCtrl[i]->SetAlignment(CNewLabel::HORZ_CENTER|CNewLabel::VERT_CENTER) ;
		}
	}
	catch (...)
	{
	}
}

void CMainDlg::InitTabControl()
{
	try
	{
		m_tabPara.InsertItem(0,_T("�������")) ;

		CRect rc ;
		m_tabPara.GetClientRect(&rc) ;

		m_pCameraNode->pCameraBase->Camera_GetRangeExposureTime(m_para1Dlg.m_lMinExposureTime,m_para1Dlg.m_lMaxExposureTime);
		m_pCameraNode->pCameraBase->Camera_GetRangeGain(m_para1Dlg.m_lMinGain,m_para1Dlg.m_lMaxGain);
		m_para1Dlg.Create(CPara1Dlg::IDD,&m_tabPara) ;
		m_para1Dlg.SetWindowPos(NULL,0,20,rc.right,rc.bottom,SWP_SHOWWINDOW) ;
		m_para1Dlg.ShowWindow(SW_SHOW) ;
	}
	catch (...)
	{
	}
}

void CMainDlg::CallDispImage(void *pOwner,HObject *hImage)
{
	try
	{
		CMainDlg *pDlg = (CMainDlg*)pOwner ;

		if (hImage->IsInitialized())
		{
			HTuple hImageWidth,hImageHeight ;
			GetImageSize(*hImage,&hImageWidth,&hImageHeight) ;
			//��ʾͼƬ
			int nImageWidth,nImageHeight ;
			switch((CAMERA_ROTATE)pDlg->m_pCameraNode->eCameraRotateType)
			{
			case E_CAMERA_ROTATE_0:
				{
					nImageWidth = hImageWidth ;
					nImageHeight = hImageHeight ;
					break ;
				}
			case E_CAMERA_ROTATE_90:
				{
					nImageWidth = hImageHeight ;
					nImageHeight = hImageWidth ;
					break ;
				}
			case E_CAMERA_ROTATE_180:
				{
					nImageWidth = hImageWidth ;
					nImageHeight = hImageHeight ;
					break ;
				}
			case E_CAMERA_ROTATE_270:
				{
					nImageWidth = hImageHeight ;
					nImageHeight = hImageWidth ;
					break ;
				}
			default:
				break;
			}
			DispImageToView(pDlg->m_lWindowID,*hImage,(CAMERA_ROTATE)pDlg->m_pCameraNode->eCameraRotateType,(CAMERA_MIRROR)pDlg->m_pCameraNode->eCameraMirrorType,\
				nImageWidth,nImageHeight,pDlg->m_dbRatioWh) ;
		}

		OutputDebugString(_T("")) ;
	}
	catch (...)
	{
	}
}

void CMainDlg::OnButtonClicked(UINT uBtnId)
{
	try
	{
		switch(uBtnId)
		{
		case IDC_BTN_RUN:
			{
				BtnRun() ;
				break;
			}
		case IDC_BTN_RUNCYCLE:
			{
				BtnRunCycle() ;
				break;
			}
		case IDC_BTN_LOAD:
			{
				BtnLoad() ;
				break;
			}
		case IDC_BTN_SAVE:
			{
				BtnSave() ;
				break;
			}
		case IDC_BTN_CLOSE:
			{
				BtnClose() ;
				break;
			}
		default:
			break;
		}
	}
	catch (...)
	{
	}
}

void CMainDlg::BtnRun()
{
	try
	{
		ASSERT_POINT(m_pCameraNode) ;

		HObject hImage ;
		if (E_CAMERA_OK == m_pCameraNode->pCameraBase->Camera_GrabOne(&hImage))
		{
			DispImageToView(m_lWindowID,hImage,m_pCameraNode->eCameraRotateType,m_pCameraNode->eCameraMirrorType,\
				m_pCameraNode->nImageWidth,m_pCameraNode->nImageHeight,m_dbRatioWh) ;
		}
		hImage.Clear() ;
	}
	catch (...)
	{
	}
}

void CMainDlg::BtnRunCycle()
{
	try
	{
		ASSERT_POINT(m_pCameraNode) ;

		CString strGrabRet(_T("")) ;
		GetDlgItem(IDC_BTN_RUNCYCLE)->GetWindowText(strGrabRet) ;
		if ( _T("�Զ�") == strGrabRet)
		{
			//���������ɼ�
			m_pCameraNode->pCameraBase->Camera_StartGrab() ;
			GetDlgItem(IDC_BTN_RUNCYCLE)->SetWindowText(_T("ֹͣ")) ;

			//���е��Ųɼ�����ӡ�ɾ����ȷ�����˳���ť����
			GetDlgItem(IDC_BTN_RUN)->EnableWindow(FALSE) ;
			GetDlgItem(IDC_BTN_LOAD)->EnableWindow(FALSE) ;
			GetDlgItem(IDC_BTN_SAVE)->EnableWindow(FALSE) ;
			GetDlgItem(IDC_BTN_CLOSE)->EnableWindow(FALSE) ;

			//���������ع������
			m_para1Dlg.GetDlgItem(IDC_SLIDER_EXPOSURETIME)->EnableWindow(TRUE) ;
			m_para1Dlg.GetDlgItem(IDC_SLIDER_GAIN)->EnableWindow(TRUE) ;

			//������ɫ
			m_para1Dlg.m_sliderExposureTime._SetThumbColor(SYSTEM_GREEN);
			m_para1Dlg.m_sliderGain._SetThumbColor(SYSTEM_GREEN);
		}
		else if (_T("ֹͣ") == strGrabRet)
		{
			//ֹͣ�����ɼ�
			m_pCameraNode->pCameraBase->Camera_StopGrab() ;
			GetDlgItem(IDC_BTN_RUNCYCLE)->SetWindowText(_T("�Զ�")) ;

			//���е��Ųɼ�����ӡ�ɾ����ȷ�����˳���ť����
			GetDlgItem(IDC_BTN_RUN)->EnableWindow(TRUE) ;
			GetDlgItem(IDC_BTN_LOAD)->EnableWindow(TRUE) ;
			GetDlgItem(IDC_BTN_SAVE)->EnableWindow(TRUE) ;
			GetDlgItem(IDC_BTN_CLOSE)->EnableWindow(TRUE) ;

			//�ر������ع������
			m_para1Dlg.GetDlgItem(IDC_SLIDER_EXPOSURETIME)->EnableWindow(FALSE) ;
			m_para1Dlg.GetDlgItem(IDC_SLIDER_GAIN)->EnableWindow(FALSE) ;

			//������ɫ
			m_para1Dlg.m_sliderExposureTime._SetThumbColor(SYSTEM_RED);
			m_para1Dlg.m_sliderGain._SetThumbColor(SYSTEM_RED);
		}
	}
	catch (...)
	{
	}
}

void CMainDlg::BtnLoad()
{
	USES_CONVERSION ;
	try
	{
		CString strLoadPath(_T("")) ;
		char  strFileName[1024];
		CFileDialog FileDlg(TRUE, _T("*.vDat"), NULL, 0, _T("All Files (*.vDat)|*.vDat||"));
		if(FileDlg.DoModal()==IDOK)
		{
			strLoadPath = FileDlg.GetPathName();
		}
		else
		{
			return ;
		}

		//��ʼ�����л�
		HTuple hFileHandle,hSerializedItemHandle ;
		try
		{
			HTuple hReadTuple ;
			OpenFile(W2A(strLoadPath),"input_binary",&hFileHandle) ;
			FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
			DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
			CloseFile(hFileHandle) ;

			if (0 != (HTuple(hReadTuple[0])!=HTuple("Vision2DCamera")))
			{
				AfxMessageBox(_T("���������ļ���ʽ����")) ;
				return ;
			}

			m_para1Dlg.m_lExposureTime = hReadTuple[1].L() ;
			m_para1Dlg.m_lGain = hReadTuple[2].L() ;
			m_para1Dlg.UpdateAllControl() ;
		}
		catch (...)
		{
			AfxMessageBox(_T("���������ļ���ʽ����")) ;
			CloseFile(hFileHandle) ;
			return ;
		}
	}
	catch (...)
	{
	}
}

void CMainDlg::BtnSave()
{
	USES_CONVERSION ;
	try
	{
		if (m_strSavePath.IsEmpty())
			return  ;

		if (IDOK != AfxMessageBox(_T("���������ļ�?"),MB_OKCANCEL))
			return ;

		HTuple hSaveTuple;
		hSaveTuple[0] = "Vision2DCamera" ;
		hSaveTuple[1] = m_para1Dlg.m_sliderExposureTime.GetPos() ;
		hSaveTuple[2] = m_para1Dlg.m_sliderGain.GetPos() ;

		//��ʼ���л�
		HTuple hFileHandle,hSerializedItemHandle ;
		OpenFile(W2A(m_strSavePath),"output_binary",&hFileHandle) ;
		SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
		FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;
		CloseFile(hFileHandle) ;

		AfxMessageBox(_T("����Ok")) ;

		CDialogEx::OnOK() ;
	}
	catch (...)
	{
	}
}

void CMainDlg::BtnClose()
{
	try
	{
		CDialogEx::OnCancel() ;
	}
	catch (...)
	{
	}
}