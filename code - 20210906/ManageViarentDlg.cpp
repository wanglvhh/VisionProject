// ManageViarentDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VisionProject.h"
#include "ManageViarentDlg.h"
#include "afxdialogex.h"
#include "GobalViarentDlg.h"
#include "VisionProjectDlg.h"

// CManageViarentDlg �Ի���

IMPLEMENT_DYNAMIC(CManageViarentDlg, CDialogEx)

CManageViarentDlg::CManageViarentDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CManageViarentDlg::IDD, pParent)
{
}

CManageViarentDlg::~CManageViarentDlg()
{
}

void CManageViarentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_LUAGOBALVIARENT, m_listLuaGobalViarent);
	DDX_Control(pDX, IDC_BTN_ADD, m_btnAdd);
	DDX_Control(pDX, IDC_BTN_EDIT, m_btnEdit);
	DDX_Control(pDX, IDC_BTN_DEL, m_btnDel);
	DDX_Control(pDX, IDOK, m_btnSave);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
}

BEGIN_MESSAGE_MAP(CManageViarentDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_ADD, &CManageViarentDlg::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_EDIT, &CManageViarentDlg::OnBnClickedBtnEdit)
	ON_BN_CLICKED(IDC_BTN_DEL, &CManageViarentDlg::OnBnClickedBtnDel)
	ON_BN_CLICKED(IDOK, &CManageViarentDlg::OnBnClickedOk)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_LUAGOBALVIARENT, &CManageViarentDlg::OnNMDblclkListLuagobalviarent)
END_MESSAGE_MAP()

// CManageViarentDlg ��Ϣ�������

BOOL CManageViarentDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitAllControl() ;

	UpdataListControl() ;

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CManageViarentDlg::InitAllControl()
{
	try
	{
		//��ʼ��BtnControl
		InitBtnControl() ;
		//��ʼ��ListControl
		InitListControl() ;
	}
	catch (...)
	{
	}
}

void CManageViarentDlg::InitBtnControl()
{
	try
	{
		m_btnAdd.SetIcon(IDI_ICON_ADD) ;
		m_btnAdd.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnAdd.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnAdd.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnAdd.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnAdd.SetRounded(TRUE) ;

		m_btnEdit.SetIcon(IDI_ICON_EDIT) ;
		m_btnEdit.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnEdit.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnEdit.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnEdit.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnEdit.SetRounded(TRUE) ;

		m_btnDel.SetIcon(IDI_ICON_SUB) ;
		m_btnDel.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnDel.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnDel.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnDel.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnDel.SetRounded(TRUE) ;

		m_btnSave.SetIcon(IDI_ICON_SAVE) ;
		m_btnSave.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnSave.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnSave.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnSave.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnSave.SetRounded(TRUE) ;

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

void CManageViarentDlg::InitListControl()
{
	try
	{
		////�����б�����ɫ
		m_listLuaGobalViarent.SetColColor(E_LUAGOBALVIARENT_ID,SYSTEM_BK_COLOR) ;
		m_listLuaGobalViarent.SetColColor(E_LUAGOBALVIARENT_NAME,SYSTEM_BK_COLOR) ;
		m_listLuaGobalViarent.SetColColor(E_LUAGOBALVIARENT_TYPE,SYSTEM_BK_COLOR) ;
		m_listLuaGobalViarent.SetColColor(E_LUAGOBALVIARENT_VALUE,SYSTEM_BK_COLOR) ;
		m_listLuaGobalViarent.SetColColor(E_LUAGOBALVIARENT_TIPINFO,SYSTEM_BK_COLOR) ;
		////���ñ�����ɫ
		m_listLuaGobalViarent.SetBkColor(SYSTEM_BK_COLOR) ;
		////�����и�
		m_listLuaGobalViarent.SetRowHeight(25) ;
		////����ͷ���߶�
		m_listLuaGobalViarent.SetHeaderHeight(1.5) ;
		////����ͷ������߶�,�Ϳ��,0��ʾȱʡ������Ӧ
		m_listLuaGobalViarent.SetHeaderFontHW(16,0);
		////����ͷ��������ɫ
		m_listLuaGobalViarent.SetHeaderTextColor(RGB(255,200,100));
		////�����ı���ɫ
		m_listLuaGobalViarent.SetTextColor(SYSTEM_BLACK);
		////����ͷ������ɫ
		m_listLuaGobalViarent.SetHeaderBKColor(245,245,245,8);
		////��������߶ȣ��Ϳ��,0��ʾȱʡ���
		m_listLuaGobalViarent.SetFontHW(15,0);
		////�������ı���ɫ
		m_listLuaGobalViarent.SetColTextColor((int)E_LUAGOBALVIARENT_ID,SYSTEM_BLUE);
		m_listLuaGobalViarent.SetColTextColor((int)E_LUAGOBALVIARENT_NAME,SYSTEM_BLUE);
		m_listLuaGobalViarent.SetColTextColor((int)E_LUAGOBALVIARENT_TYPE,SYSTEM_RED);
		////���õ�Ԫ��������ɫ
		////m_listCamera.SetItemTextColor(3,1,RGB(255,0,0));

		CRect rect ;
		m_listLuaGobalViarent.GetClientRect(&rect) ;
		m_listLuaGobalViarent.InsertColumn((int)E_LUAGOBALVIARENT_ID,_T("ID"),LVCFMT_CENTER,(int)(rect.Width()*0.1)) ;
		m_listLuaGobalViarent.InsertColumn((int)E_LUAGOBALVIARENT_NAME,_T("��������"),LVCFMT_CENTER,(int)(rect.Width()*0.2)) ;
		m_listLuaGobalViarent.InsertColumn((int)E_LUAGOBALVIARENT_TYPE,_T("��������"),LVCFMT_CENTER,(int)(rect.Width()*0.2)) ;
		m_listLuaGobalViarent.InsertColumn((int)E_LUAGOBALVIARENT_VALUE,_T("����ֵ"),LVCFMT_CENTER,(int)(rect.Width()*0.2)) ;
		m_listLuaGobalViarent.InsertColumn((int)E_LUAGOBALVIARENT_TIPINFO,_T("��ʾ��Ϣ"),LVCFMT_CENTER,(int)(rect.Width()*0.3)) ;

		SetWindowLong(m_listLuaGobalViarent.m_hWnd ,GWL_EXSTYLE,WS_EX_CLIENTEDGE);
		////������չ���Ϊ����
		m_listLuaGobalViarent.SetExtendedStyle(LVS_EX_GRIDLINES);
	}
	catch (...)
	{
	}
}

void CManageViarentDlg::UpdataListControl()
{
	USES_CONVERSION ;
	UpdateData(TRUE) ;
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		m_listLuaGobalViarent.DeleteAllItems() ;

		for (int i = 0 ;i < pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentListSize();i++)
		{
			CGOBALVIARENT *pGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentById(i) ;
			if (NULL == pGobalViarent)
				continue;

			CString strInfo(_T("")) ;
			strInfo.Format(_T("%d"),pGobalViarent->nViarentID) ;
			m_listLuaGobalViarent.InsertItem(i,strInfo) ;

			m_listLuaGobalViarent.SetItemText(i,1,pGobalViarent->strViarentName) ;

			switch(pGobalViarent->nViarentType)
			{
			case 0:
				{
					strInfo = _T("int") ;
					break ;
				}
			case 1:
				{
					strInfo = _T("double") ;
					break ;
				}
			case 2:
				{
					strInfo = _T("string") ;
					break ;
				}
			case 3:
				{
					strInfo = _T("bool") ;
					break ;
				}
			case 4:
				{
					strInfo = _T("matrix") ;
					break ;
				}
			case 5:
				{
					strInfo = _T("2dpos") ;
					break ;
				}
			case 6:
				{
					strInfo = _T("3dpos") ;
					break ;
				}
			default:
				break;
			}
			m_listLuaGobalViarent.SetItemText(i,2,strInfo) ;
			m_listLuaGobalViarent.SetItemText(i,3,pGobalViarent->strViarentValue) ;
			m_listLuaGobalViarent.SetItemText(i,4,pGobalViarent->strViarentTipInfo) ;
		}
	}
	catch (...)
	{
	}
}

void CManageViarentDlg::OnBnClickedBtnAdd()
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		CGobalViarentDlg gobalViarentDlg ;
		CGOBALVIARENT *pGobalViarent = new CGOBALVIARENT() ;
		pGobalViarent->nViarentID = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentListSize() ;
		if( IDOK == gobalViarentDlg.DoModal())
		{
			pGobalViarent->strViarentName = gobalViarentDlg.m_strValueName ;
			if (pGobalViarent->strViarentName.IsEmpty())
			{
				DELETE_POINT(pGobalViarent) ;
				AfxMessageBox(_T("�����������")) ;
				return ;
			}
			if (!pDlg->m_projectData.m_mgGobalViarent.CheckViarentName(pGobalViarent->strViarentName))
			{
				DELETE_POINT(pGobalViarent) ;
				AfxMessageBox(_T("�������ظ�")) ;
				return ;
			}

			if(!pDlg->m_projectData.m_mgGobalViarent.CheckViarentFormat(gobalViarentDlg.m_nValueType,gobalViarentDlg.m_strValue))
			{
				pGobalViarent->nViarentType = gobalViarentDlg.m_nValueType ;
				pGobalViarent->strViarentValue = _T("") ;
				pGobalViarent->strViarentTipInfo = gobalViarentDlg.m_strValueTipInfo ;
			}
			else
			{
				pGobalViarent->nViarentType = gobalViarentDlg.m_nValueType ;
				pGobalViarent->strViarentValue = gobalViarentDlg.m_strValue ;
				pGobalViarent->strViarentTipInfo = gobalViarentDlg.m_strValueTipInfo ;
			}

			if (!pDlg->m_projectData.m_mgGobalViarent.GetViarentValue(pGobalViarent->nViarentType,\
				pGobalViarent->strViarentValue,pGobalViarent->aViarentValue))
			{
				DELETE_POINT(pGobalViarent) ;
				return ;
			}

			pDlg->m_projectData.m_mgGobalViarent.AddTail(pGobalViarent) ;

			UpdataListControl() ;
		}
		else
		{
			DELETE_POINT(pGobalViarent) ;
		}
	}
	catch (...)
	{
	}
}

void CManageViarentDlg::OnBnClickedBtnEdit()
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		int nCurSel = m_listLuaGobalViarent.GetSelectionMark() ;
		if (nCurSel < 0)
		{
			AfxMessageBox(_T("��ѡ�б༭")) ;
			return ;
		}

		CGobalViarentDlg gobalViarentDlg ;
		CGOBALVIARENT *pGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentById(nCurSel) ;
		gobalViarentDlg.m_strValueName = pGobalViarent->strViarentName ;
		gobalViarentDlg.m_nValueType = pGobalViarent->nViarentType ;
		gobalViarentDlg.m_strValue = pGobalViarent->strViarentValue ;
		gobalViarentDlg.m_strValueTipInfo = pGobalViarent->strViarentTipInfo ;
		if (IDOK == gobalViarentDlg.DoModal())
		{
			if (gobalViarentDlg.m_strValueName.IsEmpty()) return ;

			if (!pDlg->m_projectData.m_mgGobalViarent.CheckViarentName(gobalViarentDlg.m_strValueName))
			{
				if(!pDlg->m_projectData.m_mgGobalViarent.CheckViarentFormat(gobalViarentDlg.m_nValueType,gobalViarentDlg.m_strValue))
				{
					pGobalViarent->nViarentType = gobalViarentDlg.m_nValueType ;
					pGobalViarent->strViarentValue = _T("") ;
					pGobalViarent->strViarentTipInfo = gobalViarentDlg.m_strValueTipInfo ;
				}
				else
				{
					pGobalViarent->nViarentType = gobalViarentDlg.m_nValueType ;
					pGobalViarent->strViarentValue = gobalViarentDlg.m_strValue ;
					pGobalViarent->strViarentTipInfo = gobalViarentDlg.m_strValueTipInfo ;
				}

				if (!pDlg->m_projectData.m_mgGobalViarent.GetViarentValue(pGobalViarent->nViarentType,\
					pGobalViarent->strViarentValue,pGobalViarent->aViarentValue))
				{
					return ;
				}
				UpdataListControl() ;
				return ;
			}

			pGobalViarent->strViarentName = gobalViarentDlg.m_strValueName ;
			if(!pDlg->m_projectData.m_mgGobalViarent.CheckViarentFormat(gobalViarentDlg.m_nValueType,gobalViarentDlg.m_strValue))
			{
				pGobalViarent->nViarentType = gobalViarentDlg.m_nValueType ;
				pGobalViarent->strViarentValue = _T("") ;
				pGobalViarent->strViarentTipInfo = gobalViarentDlg.m_strValueTipInfo ;
			}
			else
			{
				pGobalViarent->nViarentType = gobalViarentDlg.m_nValueType ;
				pGobalViarent->strViarentValue = gobalViarentDlg.m_strValue ;
				pGobalViarent->strViarentTipInfo = gobalViarentDlg.m_strValueTipInfo ;
			}

			if (!pDlg->m_projectData.m_mgGobalViarent.GetViarentValue(pGobalViarent->nViarentType,\
				pGobalViarent->strViarentValue,pGobalViarent->aViarentValue))
			{
				return ;
			}

			UpdataListControl() ;
		}
	}
	catch (...)
	{
	}
}

void CManageViarentDlg::OnBnClickedBtnDel()
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		int nCurSel = m_listLuaGobalViarent.GetSelectionMark() ;
		if (nCurSel < 0)
		{
			AfxMessageBox(_T("��ѡ��ɾ��")) ;
			return ;
		}

		pDlg->m_projectData.m_mgGobalViarent.RemoveAtById(nCurSel) ;
		pDlg->m_projectData.m_mgGobalViarent.ReSortId() ;

		UpdataListControl() ;
	}
	catch (...)
	{
	}
}

void CManageViarentDlg::OnBnClickedOk()
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		pDlg->m_projectData.SaveGobalViarentConfig() ;

		AfxMessageBox(_T("����ɹ�")) ;
	}
	catch (...)
	{
	}
	CDialogEx::OnOK();
}

void CManageViarentDlg::OnNMDblclkListLuagobalviarent(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	OnBnClickedBtnEdit() ;
	*pResult = 0;
}