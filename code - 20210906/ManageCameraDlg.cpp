// ManageCameraDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "VisionProject.h"
#include "ManageCameraDlg.h"
#include "afxdialogex.h"
#include "AddCameraDlg.h"
#include "VisionProjectDlg.h"

// CManageCameraDlg 对话框
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(CManageCameraDlg, CDialogEx)

CManageCameraDlg::CManageCameraDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CManageCameraDlg::IDD, pParent)
	//, m_nTriggerMode(0)
	, m_nMirrorMode(0)
	, m_nRotateMode(0)
	, m_bTriggerMode(FALSE)
{
}

CManageCameraDlg::~CManageCameraDlg()
{
}

void CManageCameraDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_VIEW, m_ctlImageView);
	DDX_Control(pDX, IDC_BTN_ADD, m_btnAddCamera);
	DDX_Control(pDX, IDC_BTN_DEL, m_btnDelCamera);
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_LIST_CAMERA, m_listCamera);
	//DDX_Radio(pDX, IDC_RADIO_SOFTTRIGGER, m_nTriggerMode);
	DDX_Radio(pDX, IDC_RADIO_MIRROR_NONE, m_nMirrorMode);
	DDX_Radio(pDX, IDC_RADIO_ROTATE_NONE, m_nRotateMode);
	DDX_Control(pDX, IDC_SLIDER_EXPOSURETIME, m_sliderExposureTime);
	DDX_Control(pDX, IDC_SLIDER_GAIN, m_sliderGain);
	DDX_Check(pDX, IDC_CHECK_TRIGGERMODE, m_bTriggerMode);
	DDX_Control(pDX, IDC_COMBO_CAMERALIST, m_comboCameraList);
	DDX_Control(pDX, IDC_BTN_GRABONE, m_btnGrabOne);
	DDX_Control(pDX, IDC_BTN_GRABBING, m_btnGrabbing);
	DDX_Control(pDX, IDC_BTN_TRIGGERMODE, m_btnTriggerMode);
}

BEGIN_MESSAGE_MAP(CManageCameraDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_ADD, &CManageCameraDlg::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DEL, &CManageCameraDlg::OnBnClickedBtnDel)
	ON_BN_CLICKED(IDC_BTN_GRABONE, &CManageCameraDlg::OnBnClickedBtnGrabone)
	ON_BN_CLICKED(IDC_BTN_GRABBING, &CManageCameraDlg::OnBnClickedBtnGrabbing)
	ON_CBN_SELENDOK(IDC_COMBO_CAMERALIST, &CManageCameraDlg::OnCbnSelendokComboCameralist)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO_MIRROR_NONE, IDC_RADIO_ROTATE_270, OnRadioClicked)
	ON_BN_CLICKED(IDOK, &CManageCameraDlg::OnBnClickedOk)
END_MESSAGE_MAP()

// CManageCameraDlg 消息处理程序

BOOL CManageCameraDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitAllControl() ;

	UpdataAllControl() ;

	UpdataCamera() ;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CManageCameraDlg::InitAllControl()
{
	try
	{
		//初始化BtnControl
		InitBtnControl() ;
		//初始化ListControl
		InitListControl() ;
		//初始化ViewControl
		InitViewControl() ;
		//初始化ComboControl
		InitComboControl() ;
		//初始化SliderControl
		InitSliderControl() ;
	}
	catch (...)
	{
	}
}

void CManageCameraDlg::InitBtnControl()
{
	try
	{
		m_btnAddCamera.SetIcon(IDI_ICON_ADD) ;
		m_btnAddCamera.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnAddCamera.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnAddCamera.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnAddCamera.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnAddCamera.SetRounded(TRUE) ;

		m_btnDelCamera.SetIcon(IDI_ICON_SUB) ;
		m_btnDelCamera.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnDelCamera.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnDelCamera.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnDelCamera.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnDelCamera.SetRounded(TRUE) ;

		m_btnGrabOne.SetIcon(IDI_ICON_CAMERA) ;
		m_btnGrabOne.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnGrabOne.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnGrabOne.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnGrabOne.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnGrabOne.SetRounded(TRUE) ;

		m_btnGrabbing.SetIcon(IDI_ICON_VIDEO) ;
		m_btnGrabbing.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnGrabbing.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnGrabbing.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnGrabbing.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnGrabbing.SetRounded(TRUE) ;

		m_btnTriggerMode.SetIcon(IDI_ICON_CAMERASET) ;
		m_btnTriggerMode.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnTriggerMode.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnTriggerMode.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnTriggerMode.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnTriggerMode.SetRounded(TRUE) ;

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

void CManageCameraDlg::InitListControl()
{
	try
	{
		//设置列背景颜色
		m_listCamera.SetColColor(E_CAMERA_ID,SYSTEM_BK_COLOR) ;
		m_listCamera.SetColColor(E_CAMERA_SN,SYSTEM_BK_COLOR) ;
		m_listCamera.SetColColor(E_CAMERA_TIPINFO,SYSTEM_BK_COLOR) ;
		m_listCamera.SetColColor(E_CAMERA_COMPANY,SYSTEM_BK_COLOR) ;
		m_listCamera.SetColColor(E_CAMERA_CONNECT,SYSTEM_BK_COLOR) ;
		m_listCamera.SetColColor(E_CAMERA_COLORSPACE,SYSTEM_BK_COLOR) ;
		//设置背景颜色
		m_listCamera.SetBkColor(SYSTEM_BK_COLOR) ;
		//设置行高
		m_listCamera.SetRowHeight(25) ;
		//设置头部高度
		m_listCamera.SetHeaderHeight(1.5) ;
		//设置头部字体高度,和宽度,0表示缺省，自适应
		m_listCamera.SetHeaderFontHW(16,0);
		//设置头部字体颜色
		m_listCamera.SetHeaderTextColor(RGB(255,200,100));
		//设置文本颜色
		m_listCamera.SetTextColor(SYSTEM_BLACK);
		//设置头部背景色
		m_listCamera.SetHeaderBKColor(245,245,245,8);
		//设置字体高度，和宽度,0表示缺省宽度
		m_listCamera.SetFontHW(15,0);
		//设置列文本颜色
		m_listCamera.SetColTextColor((int)E_CAMERA_ID,SYSTEM_BLUE);
		m_listCamera.SetColTextColor((int)E_CAMERA_SN,SYSTEM_RED);
		//设置单元格字体颜色
		//m_listCamera.SetItemTextColor(3,1,RGB(255,0,0));

		CRect rect ;
		m_listCamera.GetClientRect(&rect) ;
		m_listCamera.InsertColumn((int)E_CAMERA_ID,_T("ID"),LVCFMT_CENTER,(int)(rect.Width()*0.1)) ;
		m_listCamera.InsertColumn((int)E_CAMERA_SN,_T("相机SN号"),LVCFMT_CENTER,(int)(rect.Width()*0.25)) ;
		m_listCamera.InsertColumn((int)E_CAMERA_TIPINFO,_T("相机提示信息"),LVCFMT_CENTER,(int)(rect.Width()*0.2)) ;
		m_listCamera.InsertColumn((int)E_CAMERA_COMPANY,_T("相机品牌"),LVCFMT_CENTER,(int)(rect.Width()*0.15)) ;
		m_listCamera.InsertColumn((int)E_CAMERA_CONNECT,_T("连接方式"),LVCFMT_CENTER,(int)(rect.Width()*0.15)) ;
		m_listCamera.InsertColumn((int)E_CAMERA_COLORSPACE,_T("色彩空间"),LVCFMT_CENTER,(int)(rect.Width()*0.15)) ;

		SetWindowLong(m_listCamera.m_hWnd ,GWL_EXSTYLE,WS_EX_CLIENTEDGE);
		//设置扩展风格为网格
		m_listCamera.SetExtendedStyle(LVS_EX_GRIDLINES);
	}
	catch (...)
	{
	}
}

void CManageCameraDlg::InitViewControl()
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
		InitStaticView(lWindowID,E_CAMERA_ROTATE_0,nCtrlWidth,nCtrlHeight,1200,900,m_dbRatioWh,&m_lWindowID) ;
	}
	catch (...)
	{
	}
}

void CManageCameraDlg::InitComboControl()
{
	try
	{
		m_comboCameraList.SnShowImage(_T(".\\res\\bmp\\drop_down.bmp"), 3, 2, SKIN_STATUS_NOR, FALSE);
		m_comboCameraList.SnShowImage(_T(".\\res\\bmp\\drop_down.bmp"), 3, 3, SKIN_STATUS_HOT, FALSE);
	}
	catch (...)
	{
	}
}

void CManageCameraDlg::InitSliderControl()
{
	try
	{
		m_sliderExposureTime.SetRange(0,999999) ;
		m_sliderExposureTime.SetTicFreq(10) ;
		m_sliderExposureTime.SetPageSize(1000);
		m_sliderExposureTime._IsEnabled()?m_sliderExposureTime._EnableBorders(FALSE):m_sliderExposureTime._EnableBorders(TRUE);
		//设置颜色
		m_sliderExposureTime._SetBkColor(SYSTEM_BK_COLOR);
		m_sliderExposureTime._SetThumbColor(SYSTEM_RED);
		m_sliderExposureTime._SetChColor(SYSTEM_BLUE);

		m_sliderGain.SetRange(0,100) ;
		m_sliderGain.SetTicFreq(10) ;
		m_sliderGain.SetPageSize(1);
		m_sliderGain._IsEnabled()?m_sliderGain._EnableBorders(FALSE):m_sliderGain._EnableBorders(TRUE);
		//设置颜色
		m_sliderGain._SetBkColor(SYSTEM_BK_COLOR);
		m_sliderGain._SetThumbColor(SYSTEM_RED);
		m_sliderGain._SetChColor(SYSTEM_BLUE);
	}
	catch (...)
	{
	}
}

void CManageCameraDlg::UpdataAllControl()
{
	try
	{
		//更新ListControl
		UpdataListControl() ;
		//更新ComboControl
		UpdataComboControl() ;
		//更新SliderControl
		UpdataSliderControl() ;
	}
	catch (...)
	{
	}
}

BOOL CManageCameraDlg::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	int nCameraCount = pDlg->m_projectData.m_mgCamera.GetCameraNodeListSize() ;
	if (nCameraCount <= 0)
		return CDialog::OnNotify(wParam, lParam, pResult) ;

	int nCurCameraId = m_comboCameraList.GetCurSel() ;
	CCameraNode *pCameraNode = pDlg->m_projectData.m_mgCamera.GetCameraNodeById(nCurCameraId) ;
	if (NULL == pCameraNode)
		return CDialog::OnNotify(wParam, lParam, pResult) ;

	CString lpszValue;
	NMHDR *pParam = reinterpret_cast<NMHDR*>(lParam);

	if(pParam->hwndFrom == m_sliderExposureTime.m_hWnd)
	{
		int nValue = m_sliderExposureTime.GetPos();

		//设置曝光
		if (E_CAMERA_OK != pCameraNode->pCameraBase->Camera_SetExposureTime((long)nValue))
			return CDialog::OnNotify(wParam, lParam, pResult) ;

		m_sliderExposureTime.SetPos(nValue);
		lpszValue.Format(_T("%d"),nValue);
		GetDlgItem(IDC_EDIT_EXPOSURETIME)->SetWindowText(lpszValue);

		pCameraNode->lExposureTime = nValue ;
	}
	if(pParam->hwndFrom == m_sliderGain.m_hWnd)
	{
		int nValue = m_sliderGain.GetPos();

		//设置增益
		if (E_CAMERA_OK != pCameraNode->pCameraBase->Camera_SetGain((long)nValue))
			return CDialog::OnNotify(wParam, lParam, pResult) ;

		m_sliderGain.SetPos(nValue);
		lpszValue.Format(_T("%d"),nValue);
		GetDlgItem(IDC_EDIT_GAIN)->SetWindowText(lpszValue);

		pCameraNode->lGain = nValue ;
	}

	return CDialog::OnNotify(wParam, lParam, pResult);
}

void CManageCameraDlg::UpdataListControl()
{
	USES_CONVERSION ;
	UpdateData(TRUE) ;
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		m_listCamera.DeleteAllItems() ;

	    for (int i = 0 ;i < pDlg->m_projectData.m_mgCamera.GetCameraNodeListSize() ;i++)
	    {
			CCameraNode* pCameraNode = pDlg->m_projectData.m_mgCamera.GetCameraNodeById(i) ;
			if (NULL == pCameraNode)
				continue;

			CString strInfo(_T("")) ;

			strInfo.Format(_T("%d"),pCameraNode->nCameraId) ;
			m_listCamera.InsertItem(i/*m_listCamera.GetSelectedCount()*/,strInfo) ;

			strInfo = pCameraNode->strCameraSn.c_str() ;
			m_listCamera.SetItemText(i/*m_listCamera.GetSelectedCount()*/,(int)E_CAMERA_SN,strInfo) ;

			strInfo = pCameraNode->strCameraTipInfo.c_str() ;
			m_listCamera.SetItemText(i/*m_listCamera.GetSelectedCount()*/,(int)E_CAMERA_TIPINFO,strInfo) ;

			switch(pCameraNode->eCameraType)
			{
			case E_TOOL_CAMERA_HALCON:
				{
					strInfo = _T("Halcon") ;
					break;
				}
			case E_TOOL_CAMERA_BASLER:
				{
					strInfo = _T("Basler") ;
					break;
				}
			default:
				break;
			}
			m_listCamera.SetItemText(i/*m_listCamera.GetSelectedCount()*/,(int)E_CAMERA_COMPANY,strInfo) ;

			switch(pCameraNode->eCameraConnectType)
			{
			case E_CAMERA_GIGE:
				{
					strInfo = _T("Gige") ;
					break;
				}
			case E_CAMERA_USB:
				{
					strInfo = _T("Usb") ;
					break;
				}
			case E_CAMERA_FIREWARE:
				{
					strInfo = _T("FireWare") ;
					break;
				}
			case E_CAMERA_CAMERALINK:
				{
					strInfo = _T("CameraLink") ;
					break;
				}
			case E_CAMERA_1394:
				{
					strInfo = _T("1394") ;
					break;
				}
			default:
				break;
			}
			m_listCamera.SetItemText(i/*m_listCamera.GetSelectedCount()*/,(int)E_CAMERA_CONNECT,strInfo) ;

			switch(pCameraNode->eCameraColorType)
			{
			case E_CAMERA_MONO8:
				{
					strInfo = _T("gray") ;
					break;
				}
			case E_CAMERA_BGR8:
				{
					strInfo = _T("rgb") ;
					break;
				}
			default:
				break;
			}
			m_listCamera.SetItemText(i/*m_listCamera.GetSelectedCount()*/,(int)E_CAMERA_COLORSPACE,strInfo) ;
	    }
	}
	catch (...)
	{
	}
}

void CManageCameraDlg::UpdataComboControl()
{
	USES_CONVERSION ;
	UpdateData(TRUE) ;
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		m_comboCameraList.Clear() ;

		int nCameraCount = pDlg->m_projectData.m_mgCamera.GetCameraNodeListSize();
		if (nCameraCount <= 0)
			return ;

		for (int i = 0 ;i < nCameraCount;i++)
		{
			CCameraNode *pCameraNode = pDlg->m_projectData.m_mgCamera.GetCameraNodeById(i) ;
			if (NULL == pCameraNode) continue;
			//添加相机信息到ComboControl
			CString strCamInfo(_T("")) ;
			strCamInfo += pCameraNode->strCameraSn.c_str();
			strCamInfo += _T("|······→|") ;
			strCamInfo += pCameraNode->strCameraTipInfo.c_str() ;
			m_comboCameraList.AddString(strCamInfo) ;
		}
		m_comboCameraList.SetCurSel(0) ;
	}
	catch (...)
	{
	}
}

void CManageCameraDlg::UpdataSliderControl()
{
	USES_CONVERSION ;
	UpdateData(TRUE) ;
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		int nCameraCount = pDlg->m_projectData.m_mgCamera.GetCameraNodeListSize();
		if (nCameraCount <= 0)
			return ;

		int nCameraId = m_comboCameraList.GetCurSel() ;
		CString strValue(_T("")) ;
		CCameraNode *pCameraNode = pDlg->m_projectData.m_mgCamera.GetCameraNodeById(nCameraId) ;
		ASSERT_POINT(pCameraNode) ;

		ReSetSliderControl(pCameraNode) ;
		//重置图像显示区
		ReSetPart(m_lWindowID,pCameraNode->eCameraRotateType,pCameraNode->nImageWidth,pCameraNode->nImageHeight,m_dbRatioWh) ;
		m_sliderExposureTime.SetPos(pCameraNode->lExposureTime);
		strValue.Format(_T("%d"),pCameraNode->lExposureTime);
		GetDlgItem(IDC_EDIT_EXPOSURETIME)->SetWindowText(strValue);
		m_sliderGain.SetPos(pCameraNode->lGain);
		strValue.Format(_T("%d"),pCameraNode->lGain);
		GetDlgItem(IDC_EDIT_GAIN)->SetWindowText(strValue);
	}
	catch (...)
	{
	}
}

void CManageCameraDlg::UpdataCamera()
{
	UpdateData(TRUE) ;
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		int nCameraCount = pDlg->m_projectData.m_mgCamera.GetCameraNodeListSize();
		if (nCameraCount <= 0)
			return ;

		int nCameraId = m_comboCameraList.GetCurSel() ;
		CCameraNode *pCameraNode = pDlg->m_projectData.m_mgCamera.GetCameraNodeById(nCameraId) ;
		ASSERT_POINT(pCameraNode) ;
		pCameraNode->pCameraBase->Camera_SetOwner(this,CallDispImage) ;
	}
	catch (...)
	{
	}
}

void CManageCameraDlg::ReSortCameraId()
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		int nCameraId = 0 ;
		POSITION pos = pDlg->m_projectData.m_mgCamera.cameraNodeList.GetHeadPosition() ;
		while(pos)
		{
			CCameraNode *pCameraNode = pDlg->m_projectData.m_mgCamera.cameraNodeList.GetNext(pos) ;
			pCameraNode->nCameraId = nCameraId++ ;
		}
	}
	catch (...)
	{
	}
}

void CManageCameraDlg::CallDispImage(void *pOwner,HObject *hImage)
{
	try
	{
		CManageCameraDlg *pDlg = (CManageCameraDlg*)pOwner ;

		if (hImage->IsInitialized())
		{
			HTuple hImageWidth,hImageHeight ;
			GetImageSize(*hImage,&hImageWidth,&hImageHeight) ;
			//显示图片
			int nImageWidth,nImageHeight ;
			switch((CAMERA_ROTATE)pDlg->m_nRotateMode)
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
			DispImageToView(pDlg->m_lWindowID,*hImage,(CAMERA_ROTATE)pDlg->m_nRotateMode,(CAMERA_MIRROR)pDlg->m_nMirrorMode,\
				nImageWidth,nImageHeight,pDlg->m_dbRatioWh) ;
		}

		OutputDebugString(_T("")) ;
	}
	catch (...)
	{
	}
}

CAMERA_CODE CManageCameraDlg::ReSetSliderControl(CCameraNode* pCameraNode)
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		if (NULL == pCameraNode)
		{
			return E_CAMERA_NG ;
		}

		long lMinExposureTime,lMaxExposureTime,lMinGain,lMaxGain ;
		if (E_CAMERA_OK != pCameraNode->pCameraBase->Camera_GetRangeExposureTime(lMinExposureTime,lMaxExposureTime) ||
			E_CAMERA_OK != pCameraNode->pCameraBase->Camera_GetRangeGain(lMinGain,lMaxGain))
		{
			//AfxMessageBox(_T("获取相机曝光范围或者增益范围失败")) ;
			return E_CAMERA_NG;
		}

		//设置SliderControl 范围
		m_sliderExposureTime.SetRange(lMinExposureTime,lMaxExposureTime) ;
		m_sliderGain.SetRange(lMinGain,lMaxGain) ;

		return E_CAMERA_OK ;
	}
	catch (...)
	{
		return E_CAMERA_THROW ;
	}
}

void CManageCameraDlg::OnBnClickedBtnAdd()
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		CAddCameraDlg addCameraDlg ;
		CCameraNode*  pCameraNode = new CCameraNode() ;
		pCameraNode->nCameraId = pDlg->m_projectData.m_mgCamera.GetCameraNodeListSize() ;
		addCameraDlg.m_pCameraNode = pCameraNode ;
		if (NULL == pCameraNode)
			return ;

		if (IDOK == addCameraDlg.DoModal())
		{
			//加载相机Dll
			switch((int)pCameraNode->eCameraType)
			{
			case E_TOOL_CAMERA_HALCON:
				{
					pCameraNode->mgrDllCameraBaseIm.DllCreateInterface((long)E_TOOL_CAMERA_HALCON,(void **)&pCameraNode->pCameraBase) ;
					break;
				}
			case E_TOOL_CAMERA_BASLER:
				{
					pCameraNode->mgrDllCameraBaseIm.DllCreateInterface((long)E_TOOL_CAMERA_BASLER,(void **)&pCameraNode->pCameraBase) ;
					break;
				}

			default:
				break;
			}

			if (NULL == pCameraNode->pCameraBase)
			{
				AfxMessageBox(_T("加载相机DLL失败")) ;
				DELETE_POINT(pCameraNode) ;
				return ;
			}

			//初始化相机
			if (E_CAMERA_OK != pCameraNode->pCameraBase->Camera_Init(pCameraNode->strCameraSn,pCameraNode->eCameraConnectType,pCameraNode->eCameraColorType))
			{
				AfxMessageBox(_T("相机初始化失败")) ;
				DELETE_POINT(pCameraNode) ;
				return ;
			}

			//获取图像尺寸
			if (E_CAMERA_OK != pCameraNode->pCameraBase->Camera_GetImageSize(pCameraNode->nSourceImageWidth,pCameraNode->nSourceImageHeight))
			{
				AfxMessageBox(_T("相机获取图像尺寸失败")) ;
				DELETE_POINT(pCameraNode) ;
				return ;
			}
			else
			{
				pCameraNode->nImageWidth = pCameraNode->nSourceImageWidth ;
				pCameraNode->nImageHeight = pCameraNode->nSourceImageHeight ;
			}

			//设置触发模式
			if (E_CAMERA_OK != pCameraNode->pCameraBase->Camera_SetTriggerMode(pCameraNode->triggerMode))
			{
				AfxMessageBox(_T("相机设置触发模式失败")) ;
				DELETE_POINT(pCameraNode) ;
				return ;
			}

			//设置SliderControl
			if (E_CAMERA_OK != ReSetSliderControl(pCameraNode) )
			{
				AfxMessageBox(_T("相机获取曝光范围或增益范围失败")) ;
				DELETE_POINT(pCameraNode) ;
				return ;
			}

			//注册回调函数
			if (E_CAMERA_OK != pCameraNode->pCameraBase->Camera_SetOwner(this,CallDispImage))
			{
				AfxMessageBox(_T("相机注册回调失败")) ;
				DELETE_POINT(pCameraNode) ;
				return ;
			}

			//添加相机到链表
			pDlg->m_projectData.m_mgCamera.AddTail(pCameraNode) ;

			//更新列表
			UpdataListControl() ;

			//添加相机信息到ComboControl
			CString strCamInfo(_T("")) ;
			strCamInfo += pCameraNode->strCameraSn.c_str();
			strCamInfo += _T("|······→|") ;
			strCamInfo += pCameraNode->strCameraTipInfo.c_str() ;
			m_comboCameraList.AddString(strCamInfo) ;
			m_comboCameraList.SetCurSel(pCameraNode->nCameraId) ;

			//重置图像显示区
			ReSetPart(m_lWindowID,pCameraNode->eCameraRotateType,pCameraNode->nImageWidth,pCameraNode->nImageHeight,m_dbRatioWh) ;

			//AfxMessageBox(_T("添加成功")) ;
		}
		else
		{
			DELETE_POINT(pCameraNode) ;
		}
	}
	catch (...)
	{
	}
}

void CManageCameraDlg::OnBnClickedBtnDel()
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		int nCurSelCamera = m_listCamera.GetSelectionMark() ;
		if (nCurSelCamera < 0)
		{
			AfxMessageBox(_T("请选中删除相机")) ;
			return ;
		}

		//关闭相机
		pDlg->m_projectData.m_mgCamera.GetCameraNodeById(nCurSelCamera)->pCameraBase->Camera_Close() ;
		//删除相机
		pDlg->m_projectData.m_mgCamera.RemoveAtById(nCurSelCamera) ;

		//重新排序相机ID
		ReSortCameraId() ;

		//更新相机列表
		UpdataListControl() ;
	}
	catch (...)
	{
	}
}

void CManageCameraDlg::OnBnClickedBtnGrabone()
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		int nCameraCount = pDlg->m_projectData.m_mgCamera.GetCameraNodeListSize() ;
		if (nCameraCount <= 0)
			return ;

		int nCurCameraId = m_comboCameraList.GetCurSel() ;
		CCameraNode *pCameraNode = pDlg->m_projectData.m_mgCamera.GetCameraNodeById(nCurCameraId) ;
		if (NULL == pCameraNode)
			return ;
		HObject hImage ;
		if (E_CAMERA_OK == pCameraNode->pCameraBase->Camera_GrabOne(&hImage))
		{
			DispImageToView(m_lWindowID,hImage,pCameraNode->eCameraRotateType,pCameraNode->eCameraMirrorType,\
				pCameraNode->nImageWidth,pCameraNode->nImageHeight,m_dbRatioWh) ;
		}
	}
	catch (...)
	{
	}
}

void CManageCameraDlg::OnBnClickedBtnGrabbing()
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		int nCameraCount = pDlg->m_projectData.m_mgCamera.GetCameraNodeListSize() ;
		if (nCameraCount <= 0)
			return ;

		int nCurCameraId = m_comboCameraList.GetCurSel() ;
		CCameraNode *pCameraNode = pDlg->m_projectData.m_mgCamera.GetCameraNodeById(nCurCameraId) ;
		if (NULL == pCameraNode)
			return ;
		CString strGrabRet(_T("")) ;
		GetDlgItem(IDC_BTN_GRABBING)->GetWindowText(strGrabRet) ;
		if ( _T("连续采集") == strGrabRet)
		{
			//开启连续采集
			pCameraNode->pCameraBase->Camera_StartGrab() ;
			GetDlgItem(IDC_BTN_GRABBING)->SetWindowText(_T("停止采集")) ;

			//所有单张采集、添加、删除、确定、退出按钮禁用
			GetDlgItem(IDC_BTN_GRABONE)->EnableWindow(FALSE) ;
			GetDlgItem(IDC_BTN_ADD)->EnableWindow(FALSE) ;
			GetDlgItem(IDC_BTN_DEL)->EnableWindow(FALSE) ;
			GetDlgItem(IDOK)->EnableWindow(FALSE) ;
			GetDlgItem(IDCANCEL)->EnableWindow(FALSE) ;
			GetDlgItem(IDC_RADIO_ROTATE_NONE)->EnableWindow(FALSE) ;
			GetDlgItem(IDC_RADIO_ROTATE_90)->EnableWindow(FALSE) ;
			GetDlgItem(IDC_RADIO_ROTATE_180)->EnableWindow(FALSE) ;
			GetDlgItem(IDC_RADIO_ROTATE_270)->EnableWindow(FALSE) ;
			GetDlgItem(IDC_RADIO_MIRROR_NONE)->EnableWindow(FALSE) ;
			GetDlgItem(IDC_RADIO_MIRROR_ROW)->EnableWindow(FALSE) ;
			GetDlgItem(IDC_RADIO_MIRROR_COLUMN)->EnableWindow(FALSE) ;
			GetDlgItem(IDC_RADIO_MIRROR_DIAGONAL)->EnableWindow(FALSE) ;

			//开启设置曝光和增益
			GetDlgItem(IDC_SLIDER_EXPOSURETIME)->EnableWindow(TRUE) ;
			GetDlgItem(IDC_SLIDER_GAIN)->EnableWindow(TRUE) ;

			//设置颜色
			m_sliderExposureTime._SetThumbColor(SYSTEM_GREEN);
			m_sliderGain._SetThumbColor(SYSTEM_GREEN);
		}
		else if (_T("停止采集") == strGrabRet)
		{
			//停止连续采集
			pCameraNode->pCameraBase->Camera_StopGrab() ;
			GetDlgItem(IDC_BTN_GRABBING)->SetWindowText(_T("连续采集")) ;

			//所有单张采集、添加、删除、确定、退出按钮启用
			GetDlgItem(IDC_BTN_GRABONE)->EnableWindow(TRUE) ;
			GetDlgItem(IDC_BTN_ADD)->EnableWindow(TRUE) ;
			GetDlgItem(IDC_BTN_DEL)->EnableWindow(TRUE) ;
			GetDlgItem(IDOK)->EnableWindow(TRUE) ;
			GetDlgItem(IDCANCEL)->EnableWindow(TRUE) ;
			GetDlgItem(IDC_RADIO_ROTATE_NONE)->EnableWindow(TRUE) ;
			GetDlgItem(IDC_RADIO_ROTATE_90)->EnableWindow(TRUE) ;
			GetDlgItem(IDC_RADIO_ROTATE_180)->EnableWindow(TRUE) ;
			GetDlgItem(IDC_RADIO_ROTATE_270)->EnableWindow(TRUE) ;
			GetDlgItem(IDC_RADIO_MIRROR_NONE)->EnableWindow(TRUE) ;
			GetDlgItem(IDC_RADIO_MIRROR_ROW)->EnableWindow(TRUE) ;
			GetDlgItem(IDC_RADIO_MIRROR_COLUMN)->EnableWindow(TRUE) ;
			GetDlgItem(IDC_RADIO_MIRROR_DIAGONAL)->EnableWindow(TRUE) ;

			//关闭设置曝光和增益
			GetDlgItem(IDC_SLIDER_EXPOSURETIME)->EnableWindow(FALSE) ;
			GetDlgItem(IDC_SLIDER_GAIN)->EnableWindow(FALSE) ;

			//设置颜色
			m_sliderExposureTime._SetThumbColor(SYSTEM_RED);
			m_sliderGain._SetThumbColor(SYSTEM_RED);
		}
	}
	catch (...)
	{
	}
}

void CManageCameraDlg::OnCbnSelendokComboCameralist()
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		//切换相机
		int nCameraCount = pDlg->m_projectData.m_mgCamera.GetCameraNodeListSize() ;
		if (nCameraCount <= 0)
			return ;

		int nCurCameraId = m_comboCameraList.GetCurSel() ;
		CCameraNode *pCameraNode = pDlg->m_projectData.m_mgCamera.GetCameraNodeById(nCurCameraId) ;
		if (NULL == pCameraNode)
			return ;

		//设置触发模式
		if (E_CAMERA_OK != pCameraNode->pCameraBase->Camera_SetTriggerMode(pCameraNode->triggerMode))
		{
			AfxMessageBox(_T("相机设置触发模式失败")) ;
			DELETE_POINT(pCameraNode) ;
			return ;
		}

		//设置SliderControl
		if (E_CAMERA_OK != ReSetSliderControl(pCameraNode) )
		{
			AfxMessageBox(_T("相机获取曝光范围或增益范围失败")) ;
			DELETE_POINT(pCameraNode) ;
			return ;
		}

		//重置图像显示区
		ReSetPart(m_lWindowID,pCameraNode->eCameraRotateType,pCameraNode->nImageWidth,pCameraNode->nImageHeight,m_dbRatioWh) ;
	}
	catch (...)
	{
	}
}

void CManageCameraDlg::OnRadioClicked(UINT uRadioId)
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();

	try
	{
		int nCameraCount = pDlg->m_projectData.m_mgCamera.GetCameraNodeListSize() ;
		if (nCameraCount <= 0)
			return ;

		int nCurCameraId = m_comboCameraList.GetCurSel() ;
		CCameraNode *pCameraNode = pDlg->m_projectData.m_mgCamera.GetCameraNodeById(nCurCameraId) ;
		if (NULL == pCameraNode)
			return ;

		switch(uRadioId)
		{
		case IDC_RADIO_ROTATE_NONE:
			{
				m_nRotateMode = (int)E_CAMERA_ROTATE_0 ;
				//不旋转
				pCameraNode->eCameraRotateType = E_CAMERA_ROTATE_0 ;
				pCameraNode->nImageWidth = pCameraNode->nSourceImageWidth ;
				pCameraNode->nImageHeight = pCameraNode->nSourceImageHeight ;

				ReSetPart(m_lWindowID,(CAMERA_ROTATE)m_nRotateMode,pCameraNode->nImageWidth,pCameraNode->nImageHeight,m_dbRatioWh) ;

				ClearWindow(m_lWindowID) ;
				DispCrossLineInWindow(m_lWindowID,(CAMERA_ROTATE)m_nRotateMode,pCameraNode->nImageWidth,pCameraNode->nImageHeight,m_dbRatioWh) ;

				break;
			}
		case IDC_RADIO_ROTATE_90:
			{
				m_nRotateMode = (int)E_CAMERA_ROTATE_90 ;
				//旋转90
				pCameraNode->eCameraRotateType = E_CAMERA_ROTATE_90 ;
				pCameraNode->nImageWidth = pCameraNode->nSourceImageHeight ;
				pCameraNode->nImageHeight = pCameraNode->nSourceImageWidth ;

				ReSetPart(m_lWindowID,(CAMERA_ROTATE)m_nRotateMode,pCameraNode->nImageWidth,pCameraNode->nImageHeight,m_dbRatioWh) ;

				ClearWindow(m_lWindowID) ;
				DispCrossLineInWindow(m_lWindowID,(CAMERA_ROTATE)m_nRotateMode,pCameraNode->nImageWidth,pCameraNode->nImageHeight,m_dbRatioWh) ;

				break;
			}
		case IDC_RADIO_ROTATE_180:
			{
				m_nRotateMode = (int)E_CAMERA_ROTATE_180 ;
				//旋转180
				pCameraNode->eCameraRotateType = E_CAMERA_ROTATE_180 ;
				pCameraNode->nImageWidth = pCameraNode->nSourceImageWidth ;
				pCameraNode->nImageHeight = pCameraNode->nSourceImageHeight ;

				ReSetPart(m_lWindowID,(CAMERA_ROTATE)m_nRotateMode,pCameraNode->nImageWidth,pCameraNode->nImageHeight,m_dbRatioWh) ;

				ClearWindow(m_lWindowID) ;
				DispCrossLineInWindow(m_lWindowID,(CAMERA_ROTATE)m_nRotateMode,pCameraNode->nImageWidth,pCameraNode->nImageHeight,m_dbRatioWh) ;

				break;
			}
		case IDC_RADIO_ROTATE_270:
			{
				m_nRotateMode = (int)E_CAMERA_ROTATE_270 ;
				//旋转270
				pCameraNode->eCameraRotateType = E_CAMERA_ROTATE_270 ;
				pCameraNode->nImageWidth = pCameraNode->nSourceImageHeight ;
				pCameraNode->nImageHeight = pCameraNode->nSourceImageWidth ;

				ReSetPart(m_lWindowID,(CAMERA_ROTATE)m_nRotateMode,pCameraNode->nImageWidth,pCameraNode->nImageHeight,m_dbRatioWh) ;

				ClearWindow(m_lWindowID) ;
				DispCrossLineInWindow(m_lWindowID,(CAMERA_ROTATE)m_nRotateMode,pCameraNode->nImageWidth,pCameraNode->nImageHeight,m_dbRatioWh) ;

				break;
			}
		case IDC_RADIO_MIRROR_NONE:
			{
				m_nMirrorMode = (int)E_CAMERA_MIRROR_NONE ;
				//不镜像
				pCameraNode->eCameraMirrorType = E_CAMERA_MIRROR_NONE ;

				ClearWindow(m_lWindowID) ;
				DispCrossLineInWindow(m_lWindowID,(CAMERA_ROTATE)m_nRotateMode,pCameraNode->nImageWidth,pCameraNode->nImageHeight,m_dbRatioWh) ;

				break;
			}
		case IDC_RADIO_MIRROR_ROW:
			{
				m_nMirrorMode = (int)E_CAMERA_MIRROR_ROW ;
				//行镜像
				pCameraNode->eCameraMirrorType = E_CAMERA_MIRROR_ROW ;

				ClearWindow(m_lWindowID) ;
				DispCrossLineInWindow(m_lWindowID,(CAMERA_ROTATE)m_nRotateMode,pCameraNode->nImageWidth,pCameraNode->nImageHeight,m_dbRatioWh) ;

				break;
			}
		case IDC_RADIO_MIRROR_COLUMN:
			{
				m_nMirrorMode = (int)E_CAMERA_MIRROR_COLUMN ;
				//列镜像
				pCameraNode->eCameraMirrorType = E_CAMERA_MIRROR_COLUMN ;

				ClearWindow(m_lWindowID) ;
				DispCrossLineInWindow(m_lWindowID,(CAMERA_ROTATE)m_nRotateMode,pCameraNode->nImageWidth,pCameraNode->nImageHeight,m_dbRatioWh) ;

				break;
			}
		case IDC_RADIO_MIRROR_DIAGONAL:
			{
				m_nMirrorMode = (int)E_CAMERA_MIRROR_DIAGONAL ;
				//对角线镜像
				pCameraNode->eCameraMirrorType = E_CAMERA_MIRROR_DIAGONAL ;

				ClearWindow(m_lWindowID) ;
				DispCrossLineInWindow(m_lWindowID,(CAMERA_ROTATE)m_nRotateMode,pCameraNode->nImageWidth,pCameraNode->nImageHeight,m_dbRatioWh) ;

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

void CManageCameraDlg::OnBnClickedOk()
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();

	try
	{
		/*if (IDOK != AfxMessageBox(_T("保存配置文件?"),MB_OKCANCEL))
		return ;*/

		//保存相机配置
		pDlg->m_projectData.SaveCameraConfig() ;

		AfxMessageBox(_T("保存OK")) ;
	}
	catch (...)
	{
	}

	CDialogEx::OnOK();
}