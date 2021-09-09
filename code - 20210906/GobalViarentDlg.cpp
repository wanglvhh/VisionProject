// GobalViarentDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "VisionProject.h"
#include "GobalViarentDlg.h"
#include "afxdialogex.h"
#include "VisionProjectDlg.h"

// CGobalViarentDlg 对话框

IMPLEMENT_DYNAMIC(CGobalViarentDlg, CDialogEx)

CGobalViarentDlg::CGobalViarentDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGobalViarentDlg::IDD, pParent)
	, m_strValueName(_T(""))
	, m_strValue(_T(""))
	, m_strValueTipInfo(_T(""))
	, m_nValueType(0)
{
}

CGobalViarentDlg::~CGobalViarentDlg()
{
}

void CGobalViarentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Text(pDX, IDC_EDIT_VIARENTNAME, m_strValueName);
	DDX_Control(pDX, IDC_COMBO_VIARENTTYPE, m_comboValueType);
	DDX_Text(pDX, IDC_EDIT_VIARENTVALUE, m_strValue);
	DDX_Text(pDX, IDC_EDIT_VIARENTTIPINFO, m_strValueTipInfo);
	DDX_Control(pDX, IDC_STATIC_INFO, m_labelInfo);
}

BEGIN_MESSAGE_MAP(CGobalViarentDlg, CDialogEx)
	ON_CONTROL_RANGE(EN_CHANGE, IDC_EDIT_VIARENTNAME, IDC_EDIT_VIARENTTIPINFO, OnEditChange)
	ON_CBN_SELENDOK(IDC_COMBO_VIARENTTYPE, &CGobalViarentDlg::OnCbnSelendokComboViarenttype)
END_MESSAGE_MAP()

// CGobalViarentDlg 消息处理程序

BOOL CGobalViarentDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitAllControl() ;

	UpdataAllControl() ;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CGobalViarentDlg::InitAllControl()
{
	try
	{
		//初始化BtnControl
		InitBtnControl() ;
		//初始化ComboControl
		InitComboControl() ;
		//初始化Label
		InitLabelControl() ;
	}
	catch (...)
	{
	}
}

void CGobalViarentDlg::InitBtnControl()
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

void CGobalViarentDlg::InitComboControl()
{
	try
	{
		m_comboValueType.SnShowImage(_T(".\\res\\bmp\\drop_down.bmp"), 3, 2, SKIN_STATUS_NOR, FALSE);
		m_comboValueType.SnShowImage(_T(".\\res\\bmp\\drop_down.bmp"), 3, 3, SKIN_STATUS_HOT, FALSE);

	    m_comboValueType.SetCurSel(0) ;
	}
	catch (...)
	{
	}
}

void CGobalViarentDlg::InitLabelControl()
{
	try
	{
		m_labelInfo.SetFontBold(TRUE);
		m_labelInfo.SetFontSize(12);
		m_labelInfo.SetTextColor(SYSTEM_RED);
		m_labelInfo.SetBorder(TRUE);
		m_labelInfo.SetBkColor(SYSTEM_BLACK);
		m_labelInfo.SetAlignment(CNewLabel::HORZ_CENTER|CNewLabel::VERT_CENTER) ;
	}
	catch (...)
	{
	}
}

void CGobalViarentDlg::UpdataAllControl()
{
	try
	{
		m_comboValueType.SetCurSel(m_nValueType) ;

		UpdateData(false) ;
	}
	catch (...)
	{
	}
}

void CGobalViarentDlg::OnEditChange(UINT uEdit)
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		UpdateData(TRUE) ;

		//0.98,0.123,12.310,0.1234,-0.14789,0.123s6
		switch(m_nValueType)
		{
		case 0:
			{
				if(!pDlg->m_projectData.m_mgGobalViarent.CheckViarentFormat(m_nValueType,m_strValue))
				{
					m_labelInfo.SetTextColor(SYSTEM_RED);
					m_labelInfo.SetText(_T("Format:nValue")) ;
					return ;
				}
				m_labelInfo.SetTextColor(SYSTEM_GREEN);
				m_labelInfo.SetText(_T("Format:nValue")) ;
				break;
			}
		case 1:
			{
				if(!pDlg->m_projectData.m_mgGobalViarent.CheckViarentFormat(m_nValueType,m_strValue))
				{
					m_labelInfo.SetTextColor(SYSTEM_RED);
					m_labelInfo.SetText(_T("Format:dbValue")) ;
					return ;
				}
				m_labelInfo.SetTextColor(SYSTEM_GREEN);
				m_labelInfo.SetText(_T("Format:dbValue")) ;
				break;
			}
		case 2:
			{
				if(!pDlg->m_projectData.m_mgGobalViarent.CheckViarentFormat(m_nValueType,m_strValue))
				{
					m_labelInfo.SetTextColor(SYSTEM_RED);
					m_labelInfo.SetText(_T("Format:strValue")) ;
					return ;
				}
				m_labelInfo.SetTextColor(SYSTEM_GREEN);
				m_labelInfo.SetText(_T("Format:strValue")) ;
				break;
			}
		case 3:
			{
				if(!pDlg->m_projectData.m_mgGobalViarent.CheckViarentFormat(m_nValueType,m_strValue))
				{
					m_labelInfo.SetTextColor(SYSTEM_RED);
					m_labelInfo.SetText(_T("Format:bValue")) ;
					return ;
				}
				m_labelInfo.SetTextColor(SYSTEM_GREEN);
				m_labelInfo.SetText(_T("Format:bValue")) ;
				break;
			}
		case 4 :
			{
				if(!pDlg->m_projectData.m_mgGobalViarent.CheckViarentFormat(m_nValueType,m_strValue))
				{
					m_labelInfo.SetTextColor(SYSTEM_RED);
					m_labelInfo.SetText(_T("Format:dbValue1,dbValue2,dbValue3,dbValue4,dbValue5,dbValue6")) ;
					return ;
				}
				m_labelInfo.SetTextColor(SYSTEM_GREEN);
				m_labelInfo.SetText(_T("Format:dbValue1,dbValue2,dbValue3,dbValue4,dbValue5,dbValue6")) ;
				break;
			}
		case 5 :
			{
				if(!pDlg->m_projectData.m_mgGobalViarent.CheckViarentFormat(m_nValueType,m_strValue))
				{
					m_labelInfo.SetTextColor(SYSTEM_RED);
					m_labelInfo.SetText(_T("Format:dbValue1,dbValue2")) ;
					return ;
				}
				m_labelInfo.SetTextColor(SYSTEM_GREEN);
				m_labelInfo.SetText(_T("Format:dbValue1,dbValue2")) ;
				break;
			}
		case 6 :
			{
				if(!pDlg->m_projectData.m_mgGobalViarent.CheckViarentFormat(m_nValueType,m_strValue))
				{
					m_labelInfo.SetTextColor(SYSTEM_RED);
					m_labelInfo.SetText(_T("Format:dbValue1,dbValue2,dbValue3")) ;
					return ;
				}
				m_labelInfo.SetTextColor(SYSTEM_GREEN);
				m_labelInfo.SetText(_T("Format:dbValue1,dbValue2,dbValue3")) ;
				break;
			}
		}
	}
	catch (...)
	{
	}
}

void CGobalViarentDlg::OnCbnSelendokComboViarenttype()
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();

	try
	{
		UpdateData(TRUE) ;

		m_nValueType = m_comboValueType.GetCurSel() ;

		switch(m_nValueType)
		{
		case 0:
			{
				if(!pDlg->m_projectData.m_mgGobalViarent.CheckViarentFormat(m_nValueType,m_strValue))
				{
					m_labelInfo.SetTextColor(SYSTEM_RED);
					m_labelInfo.SetText(_T("Format:nValue")) ;
					return ;
				}
				m_labelInfo.SetTextColor(SYSTEM_GREEN);
				m_labelInfo.SetText(_T("Format:nValue")) ;
				break;
			}
		case 1:
			{
				if(!pDlg->m_projectData.m_mgGobalViarent.CheckViarentFormat(m_nValueType,m_strValue))
				{
					m_labelInfo.SetTextColor(SYSTEM_RED);
					m_labelInfo.SetText(_T("Format:dbValue")) ;
					return ;
				}
				m_labelInfo.SetTextColor(SYSTEM_GREEN);
				m_labelInfo.SetText(_T("Format:dbValue")) ;
				break;
			}
		case 2:
			{
				if(!pDlg->m_projectData.m_mgGobalViarent.CheckViarentFormat(m_nValueType,m_strValue))
				{
					m_labelInfo.SetTextColor(SYSTEM_RED);
					m_labelInfo.SetText(_T("Format:strValue")) ;
					return ;
				}
				m_labelInfo.SetTextColor(SYSTEM_GREEN);
				m_labelInfo.SetText(_T("Format:strValue")) ;
				break;
			}
		case 3:
			{
				if(!pDlg->m_projectData.m_mgGobalViarent.CheckViarentFormat(m_nValueType,m_strValue))
				{
					m_labelInfo.SetTextColor(SYSTEM_RED);
					m_labelInfo.SetText(_T("Format:bValue")) ;
					return ;
				}
				m_labelInfo.SetTextColor(SYSTEM_GREEN);
				m_labelInfo.SetText(_T("Format:bValue")) ;
				break;
			}
		case 4 :
			{
				if(!pDlg->m_projectData.m_mgGobalViarent.CheckViarentFormat(m_nValueType,m_strValue))
				{
					m_labelInfo.SetTextColor(SYSTEM_RED);
					m_labelInfo.SetText(_T("Format:dbValue1,dbValue2,dbValue3,dbValue4,dbValue5,dbValue6")) ;
					return ;
				}
				m_labelInfo.SetTextColor(SYSTEM_GREEN);
				m_labelInfo.SetText(_T("Format:dbValue1,dbValue2,dbValue3,dbValue4,dbValue5,dbValue6")) ;
				break;
			}
		case 5 :
			{
				if(!pDlg->m_projectData.m_mgGobalViarent.CheckViarentFormat(m_nValueType,m_strValue))
				{
					m_labelInfo.SetTextColor(SYSTEM_RED);
					m_labelInfo.SetText(_T("Format:dbValue1,dbValue2")) ;
					return ;
				}
				m_labelInfo.SetTextColor(SYSTEM_GREEN);
				m_labelInfo.SetText(_T("Format:dbValue1,dbValue2")) ;
				break;
			}
		case 6 :
			{
				if(!pDlg->m_projectData.m_mgGobalViarent.CheckViarentFormat(m_nValueType,m_strValue))
				{
					m_labelInfo.SetTextColor(SYSTEM_RED);
					m_labelInfo.SetText(_T("Format:dbValue1,dbValue2,dbValue3")) ;
					return ;
				}
				m_labelInfo.SetTextColor(SYSTEM_GREEN);
				m_labelInfo.SetText(_T("Format:dbValue1,dbValue2,dbValue3")) ;
				break;
			}
		}
	}
	catch (...)
	{
	}
}