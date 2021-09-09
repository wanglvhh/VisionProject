// ManageProjectDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "VisionProject.h"
#include "ManageProjectDlg.h"
#include "afxdialogex.h"
#include "VisionProjectDlg.h"

// CManageProjectDlg 对话框
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(CManageProjectDlg, CDialogEx)

CManageProjectDlg::CManageProjectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CManageProjectDlg::IDD, pParent)
{
}

CManageProjectDlg::~CManageProjectDlg()
{
}

void CManageProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_ADD, m_btnAdd);
	DDX_Control(pDX, IDC_BTN_DEL, m_btnDel);
	DDX_Control(pDX, IDC_BTN_LOAD, m_btnLoad);
	DDX_Control(pDX, IDC_BTN_SAVE, m_btnSave);
	DDX_Control(pDX, IDC_BTN_EXIT, m_btnExit);
	DDX_Control(pDX, IDC_STATIC_INFO, m_labelInfo);
	DDX_Control(pDX, IDC_LIST_PROJECT, m_listProject);
}

BEGIN_MESSAGE_MAP(CManageProjectDlg, CDialogEx)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_EXIT,IDC_BTN_LOAD,  OnButtonClicked)
END_MESSAGE_MAP()

// CManageProjectDlg 消息处理程序

BOOL CManageProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitAllControl() ;

	UpdateControl() ;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CManageProjectDlg::InitAllControl()
{
	try
	{
		InitBtnControl() ;

		InitListControl() ;

		InitLabelControl() ;
	}
	catch (...)
	{
	}
}

void CManageProjectDlg::InitBtnControl()
{
	try
	{
		m_btnAdd.SetIcon(IDI_ICON_ADD) ;
		m_btnAdd.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnAdd.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnAdd.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnAdd.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnAdd.SetRounded(TRUE) ;

		m_btnDel.SetIcon(IDI_ICON_SUB) ;
		m_btnDel.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnDel.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnDel.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnDel.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnDel.SetRounded(TRUE) ;

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

		m_btnExit.SetIcon(IDI_ICON_CANCEL) ;
		m_btnExit.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnExit.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnExit.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnExit.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnExit.SetRounded(TRUE) ;
	}
	catch (...)
	{
	}
}

void CManageProjectDlg::InitListControl()
{
	try
	{
		InitImageList() ;
	}
	catch (...)
	{
	}
}

void CManageProjectDlg::InitLabelControl()
{
	try
	{
		CNewLabel *pCtrl[]={ &m_labelInfo };
		for (int i = 0 ;i < ARRSIZE(pCtrl);i++)
		{
			pCtrl[i]->SetFontBold(TRUE);
			//pCtrl[i]->SetFontName(_T("微软雅黑"));
			pCtrl[i]->SetFontSize(30);
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

void CManageProjectDlg::InitImageList()
{
	try
	{
		BOOL	bRetValue = FALSE;
		HICON	hIcon = NULL;

		// Create image list
		bRetValue = m_ImageList.Create(32, 32, ILC_COLOR32 | ILC_MASK, 1, 1);
		ASSERT(bRetValue == TRUE);

		m_listProject.SetImageList(&m_ImageList) ;;
		m_listProject.MoveTop(1) ;
	}
	catch (...)
	{
	}
}

void CManageProjectDlg::OnButtonClicked(UINT uBtnId)
{
	try
	{
		switch(uBtnId)
		{
		case IDC_BTN_ADD:
			{
				BtnAddProject() ;
				break;
			}
		case IDC_BTN_DEL:
			{
				BtnDelProject() ;
				break;
			}
		case IDC_BTN_LOAD:
			{
				BtnLoadProject() ;
				break;
			}
		case IDC_BTN_SAVE:
			{
				BtnSaveProject() ;
				break;
			}
		case IDC_BTN_EXIT:
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

void CManageProjectDlg::UpdateControl()
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		m_listProject.ResetContent() ;

		int nProjectCount = (int)pDlg->m_projectData.m_mgProject.GetSize() ;
		if (nProjectCount <= 0)
			return ;

		for (int i = 0 ;i < nProjectCount ;i++)
		{
			m_listProject.AddString(pDlg->m_projectData.m_mgProject.GetAt(i),i) ;
			m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_PROJECT));
		}

		CString strCurProject(_T("")) ;
		int nFind = g_sysIni.m_strProjectPath.ReverseFind('\\') ;
		strCurProject = g_sysIni.m_strProjectPath.Mid(nFind + 1,g_sysIni.m_strProjectPath.GetLength() - nFind - 1) ;
		m_labelInfo.SetText(strCurProject) ;
	}
	catch (...)
	{
	}
}

void CManageProjectDlg::BtnAddProject()
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		CNewDlg newDlg ;
		newDlg.m_strStaticInfo = _T("工程名") ;
		if (IDOK != newDlg.DoModal())
			return ;
		if (newDlg.m_strInfo.IsEmpty())
		{
			AfxMessageBox(_T("请输入工程名")) ;
			return ;
		}
		//判断工程名是否唯一
		if (!CheckProjectName(pDlg->m_projectData.m_mgProject,newDlg.m_strInfo))
		{
			AfxMessageBox(_T("输入工程名重复，请重新输入")) ;
			return ;
		}

		//新建工程文件夹
		CString strFolder = pDlg->m_projectData.m_strRoot + _T("Project\\") + newDlg.m_strInfo ;
		if (!vPathIsExist(strFolder))
		{
			CreateDirectory ( strFolder, NULL );
		}
		else
		{
#ifdef _UNICODE

			USES_CONVERSION;
			DeleteFolder ( T2A(strFolder) ) ;
#else

			DeleteFolder ( ( LPSTR ) ( LPCSTR )strFolder ) ;
#endif
			CreateDirectory ( strFolder, NULL );
		}

		m_listProject.AddString(newDlg.m_strInfo,m_listProject.GetCount()) ;
		m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_PROJECT));

		pDlg->m_projectData.m_mgProject.Add(newDlg.m_strInfo) ;
		pDlg->m_projectData.SaveProjectName() ;
	}
	catch (...)
	{
	}
}

void CManageProjectDlg::BtnDelProject()
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		int nSelProject = m_listProject.GetCurSel() ;
		if (nSelProject < 0)
		{
			AfxMessageBox(_T("请选中删除")) ;
			return ;
		}

		CString strDelProject = pDlg->m_projectData.m_strRoot + _T("Project\\") + \
			pDlg->m_projectData.m_mgProject.GetAt(nSelProject) ;
		if (vPathIsExist(strDelProject))
		{
			USES_CONVERSION;
			DeleteFolder(W2A(strDelProject)) ;
		}

		if (strDelProject == g_sysIni.m_strProjectPath)
		{
			g_sysIni.m_strProjectPath = _T("") ;
			g_sysIni.WritePara() ;

			m_labelInfo.SetText(g_sysIni.m_strProjectPath) ;
		}

		m_listProject.DeleteString(nSelProject) ;
		pDlg->m_projectData.m_mgProject.RemoveAt(nSelProject) ;

		//释放资源
		pDlg->m_projectData.ReleaseProjectData() ;
	}
	catch (...)
	{
	}
}

void CManageProjectDlg::BtnLoadProject()
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		int nSelProject = m_listProject.GetCurSel() ;
		if (nSelProject < 0)
		{
			AfxMessageBox(_T("请选中设定")) ;
			return ;
		}

		CString strSetPath = pDlg->m_projectData.m_strRoot + _T("Project\\") + \
			pDlg->m_projectData.m_mgProject.GetAt(nSelProject) ;

		g_sysIni.m_strProjectPath = strSetPath ;
		g_sysIni.WritePara() ;

		pDlg->m_projectData.ReleaseProjectData() ;
		pDlg->m_projectData.LoadProjectData() ;
		pDlg->UpdateAllControl() ;
		m_labelInfo.SetText(pDlg->m_projectData.m_mgProject.GetAt(nSelProject)) ;

		AfxMessageBox(_T("设置Ok")) ;
	}
	catch (...)
	{
	}
}

void CManageProjectDlg::BtnSaveProject()
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		if (IDOK != AfxMessageBox(_T("保存配置文件?"),MB_OKCANCEL))
			return ;

		pDlg->m_projectData.SaveProjectData() ;

		AfxMessageBox(_T("保存Ok")) ;
	}
	catch (...)
	{
	}
}