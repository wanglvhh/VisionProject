// AddCameraDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "VisionProject.h"
#include "AddCameraDlg.h"
#include "afxdialogex.h"

// CAddCameraDlg 对话框
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(CAddCameraDlg, CDialogEx)

CAddCameraDlg::CAddCameraDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAddCameraDlg::IDD, pParent)
	, m_strCameraSn(_T(""))
	, m_strCameraTipInfo(_T(""))
{
	m_pCameraNode = NULL ;
}

CAddCameraDlg::~CAddCameraDlg()
{
}

void CAddCameraDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Text(pDX, IDC_EDIT_CAMERA_SN, m_strCameraSn);
	DDX_Text(pDX, IDC_EDIT_CAMERA_TIPINFO, m_strCameraTipInfo);
	DDX_Control(pDX, IDC_COMBO_CAMERA_COMPANY, m_comboCameraCompany);
	DDX_Control(pDX, IDC_COMBO_CAMERA_CONNECT, m_comboCameraConnect);
	DDX_Control(pDX, IDC_COMBO_CAMERA_COLORSPACE, m_comboCameraColorSpace);
}

BEGIN_MESSAGE_MAP(CAddCameraDlg, CDialogEx)
	ON_CONTROL_RANGE(EN_CHANGE, IDC_EDIT_CAMERA_SN, IDC_EDIT_CAMERA_TIPINFO, OnEditChange)
	ON_CONTROL_RANGE(CBN_SELENDOK, IDC_COMBO_CAMERA_COMPANY, IDC_COMBO_CAMERA_CONNECT, OnCbnSelOk)
	ON_CONTROL_RANGE(BN_CLICKED, IDOK, IDCANCEL, OnButtonClicked)
END_MESSAGE_MAP()

// CAddCameraDlg 消息处理程序

BOOL CAddCameraDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitAllControl() ;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CAddCameraDlg::InitAllControl()
{
	try
	{
		//初始化BtnControl
		InitBtnControl() ;
		//初始化ComboControl
		InitComboControl() ;
		//初始化EditControl
		InitEditControl() ;
	}
	catch (...)
	{
	}
}

void CAddCameraDlg::InitBtnControl()
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

void CAddCameraDlg::InitComboControl()
{
	try
	{
		m_comboCameraCompany.SetCurSel((int)E_TOOL_CAMERA_HALCON-1) ;
		m_comboCameraCompany.SnShowImage(_T(".\\res\\bmp\\drop_down.bmp"), 3, 2, SKIN_STATUS_NOR, FALSE);
		m_comboCameraCompany.SnShowImage(_T(".\\res\\bmp\\drop_down.bmp"), 3, 3, SKIN_STATUS_HOT, FALSE);

		m_comboCameraConnect.SetCurSel((int)E_CAMERA_GIGE) ;
		m_comboCameraConnect.SnShowImage(_T(".\\res\\bmp\\drop_down.bmp"), 3, 2, SKIN_STATUS_NOR, FALSE);
		m_comboCameraConnect.SnShowImage(_T(".\\res\\bmp\\drop_down.bmp"), 3, 3, SKIN_STATUS_HOT, FALSE);

		m_comboCameraColorSpace.SetCurSel((int)E_CAMERA_MONO8) ;
		m_comboCameraColorSpace.SnShowImage(_T(".\\res\\bmp\\drop_down.bmp"), 3, 2, SKIN_STATUS_NOR, FALSE);
		m_comboCameraColorSpace.SnShowImage(_T(".\\res\\bmp\\drop_down.bmp"), 3, 3, SKIN_STATUS_HOT, FALSE);
	}
	catch (...)
	{
	}
}

void CAddCameraDlg::InitEditControl()
{
	try
	{
		m_strCameraSn = m_pCameraNode->strCameraSn.c_str() ;
		m_strCameraTipInfo = m_pCameraNode->strCameraTipInfo.c_str() ;

		UpdateData(FALSE) ;
	}
	catch (...)
	{
	}
}

void CAddCameraDlg::OnEditChange(UINT uEditId)
{
	UpdateData(TRUE) ;
	USES_CONVERSION ;
	try
	{
		switch (uEditId)
		{
		case IDC_EDIT_CAMERA_SN:
			{
				m_pCameraNode->strCameraSn = W2A(m_strCameraSn) ;
				break;
			}
		case IDC_EDIT_CAMERA_TIPINFO:
			{
				m_pCameraNode->strCameraTipInfo = W2A(m_strCameraTipInfo) ;
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

void CAddCameraDlg::OnCbnSelOk(UINT uComboId)
{
	UpdateData(TRUE) ;
	try
	{
		switch (uComboId)
		{
		case IDC_COMBO_CAMERA_COMPANY:
			{
				m_pCameraNode->eCameraType = (VISION_TOOLTYPE)(m_comboCameraCompany.GetCurSel() + 1) ;
				break;
			}
		case IDC_COMBO_CAMERA_CONNECT:
			{
				m_pCameraNode->eCameraConnectType = (CAMERA_CONNECTTYPE)m_comboCameraConnect.GetCurSel() ;
				break;
			}
		case IDC_COMBO_CAMERA_COLORSPACE:
			{
				m_pCameraNode->eCameraColorType = (CAMERA_COLORTYPE)m_comboCameraColorSpace.GetCurSel() ;
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

void CAddCameraDlg::OnButtonClicked(UINT uBtnId)
{
	USES_CONVERSION ;
	UpdateData(TRUE) ;
	try
	{
		switch (uBtnId)
		{
		case IDOK:
			{
				m_pCameraNode->strCameraSn          = W2A(m_strCameraSn) ;
				m_pCameraNode->strCameraTipInfo     = W2A(m_strCameraTipInfo) ;
				m_pCameraNode->eCameraType          = (VISION_TOOLTYPE)(m_comboCameraCompany.GetCurSel() + 1) ;
				m_pCameraNode->eCameraConnectType   = (CAMERA_CONNECTTYPE)m_comboCameraConnect.GetCurSel() ;
				m_pCameraNode->eCameraColorType     = (CAMERA_COLORTYPE)m_comboCameraColorSpace.GetCurSel() ;

				CDialogEx::OnOK() ;

				break;
			}
		case IDCANCEL:
			{
				CDialogEx::OnCancel() ;

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