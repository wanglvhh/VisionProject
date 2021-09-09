// ManageCommunicationDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "VisionProject.h"
#include "ManageCommunicationDlg.h"
#include "afxdialogex.h"
#include "TypeCommDlg.h"
#include "VisionProjectDlg.h"
#include "AddComm232Dlg.h"
#include "AddCommTcpDlg.h"

// CManageCommunicationDlg 对话框

IMPLEMENT_DYNAMIC(CManageCommunicationDlg, CDialogEx)

CManageCommunicationDlg::CManageCommunicationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CManageCommunicationDlg::IDD, pParent)
	, m_strSendData(_T(""))
{
	InitializeCriticalSection(&m_csComm);
}

CManageCommunicationDlg::~CManageCommunicationDlg()
{
	//删除临界区
	DeleteCriticalSection(&m_csComm) ;
}

void CManageCommunicationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_ADD, m_btnAdd);
	DDX_Control(pDX, IDC_BTN_EDIT, m_btnEdit);
	DDX_Control(pDX, IDC_BTN_DEL, m_btnDel);
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_LIST_COMM, m_listComm);
	DDX_Control(pDX, IDC_RICHEDIT21, m_ctlSysTipsDisplay1);
	DDX_Control(pDX, IDC_BTN_SEND, m_btnSend);
	DDX_Control(pDX, IDC_BTN_CLEAR, m_btnClear);
	DDX_Control(pDX, IDC_COMBO_COMMLIST, m_comboCommList);
	DDX_Control(pDX, IDC_BTN_READ, m_btnRead);
	DDX_Text(pDX, IDC_EDIT_SENDDATA, m_strSendData);
	DDX_Control(pDX, IDC_BTN_RECONNECT, m_btnReConnect);
}

BEGIN_MESSAGE_MAP(CManageCommunicationDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_ADD, &CManageCommunicationDlg::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_EDIT, &CManageCommunicationDlg::OnBnClickedBtnEdit)
	ON_BN_CLICKED(IDC_BTN_DEL, &CManageCommunicationDlg::OnBnClickedBtnDel)
	ON_BN_CLICKED(IDOK, &CManageCommunicationDlg::OnBnClickedOk)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_COMM, &CManageCommunicationDlg::OnNMDblclkListComm)
	ON_BN_CLICKED(IDC_BTN_SEND, &CManageCommunicationDlg::OnBnClickedBtnSend)
	ON_BN_CLICKED(IDC_BTN_READ, &CManageCommunicationDlg::OnBnClickedBtnRead)
	ON_BN_CLICKED(IDC_BTN_CLEAR, &CManageCommunicationDlg::OnBnClickedBtnClear)
	ON_BN_CLICKED(IDC_BTN_RECONNECT, &CManageCommunicationDlg::OnBnClickedBtnReconnect)
END_MESSAGE_MAP()

// CManageCommunicationDlg 消息处理程序

BOOL CManageCommunicationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitAllControl() ;

	UpdataAllControl() ;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CManageCommunicationDlg::InitAllControl()
{
	try
	{
		//初始化BtnControl
		InitBtnControl() ;
		//初始化ListControl
		InitListControl() ;
		//初始化ComboControl
		InitComboControl() ;
		//初始化RichEdit
		InitRichEdit() ;
	}
	catch (...)
	{
	}
}

void CManageCommunicationDlg::InitBtnControl()
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

		m_btnReConnect.SetIcon(IDI_ICON_CONNECT) ;
		m_btnReConnect.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnReConnect.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnReConnect.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnReConnect.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnReConnect.SetRounded(TRUE) ;

		m_btnOk.SetIcon(IDI_ICON_SAVE) ;
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

		m_btnSend.SetIcon(IDI_ICON_SEND) ;
		m_btnSend.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnSend.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnSend.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnSend.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnSend.SetRounded(TRUE) ;

		m_btnRead.SetIcon(IDI_ICON_READ) ;
		m_btnRead.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnRead.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnRead.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnRead.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnRead.SetRounded(TRUE) ;

		m_btnClear.SetIcon(IDI_ICON_CLEAR) ;
		m_btnClear.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnClear.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnClear.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnClear.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnClear.SetRounded(TRUE) ;
	}
	catch (...)
	{
	}
}

void CManageCommunicationDlg::InitListControl()
{
	try
	{
		////设置列背景颜色
		m_listComm.SetColColor(E_COMM_ID,SYSTEM_BK_COLOR) ;
		m_listComm.SetColColor(E_COMM_NAME,SYSTEM_BK_COLOR) ;
		m_listComm.SetColColor(E_COMM_TYPE,SYSTEM_BK_COLOR) ;
		m_listComm.SetColColor(E_COMM_VALUE,SYSTEM_BK_COLOR) ;
		////设置背景颜色
		m_listComm.SetBkColor(SYSTEM_BK_COLOR) ;
		////设置行高
		m_listComm.SetRowHeight(25) ;
		////设置头部高度
		m_listComm.SetHeaderHeight(1.5) ;
		////设置头部字体高度,和宽度,0表示缺省，自适应
		m_listComm.SetHeaderFontHW(16,0);
		////设置头部字体颜色
		m_listComm.SetHeaderTextColor(RGB(255,200,100));
		////设置文本颜色
		m_listComm.SetTextColor(SYSTEM_BLACK);
		////设置头部背景色
		m_listComm.SetHeaderBKColor(245,245,245,8);
		////设置字体高度，和宽度,0表示缺省宽度
		m_listComm.SetFontHW(15,0);
		////设置列文本颜色
		m_listComm.SetColTextColor((int)E_COMM_ID,SYSTEM_BLUE);
		m_listComm.SetColTextColor((int)E_COMM_NAME,SYSTEM_BLUE);
		m_listComm.SetColTextColor((int)E_COMM_TYPE,SYSTEM_RED);
		////设置单元格字体颜色
		////m_listCamera.SetItemTextColor(3,1,RGB(255,0,0));

		CRect rect ;
		m_listComm.GetClientRect(&rect) ;
		m_listComm.InsertColumn((int)E_COMM_ID,_T("通信ID"),LVCFMT_CENTER,(int)(rect.Width()*0.1)) ;
		m_listComm.InsertColumn((int)E_COMM_NAME,_T("通信名称"),LVCFMT_CENTER,(int)(rect.Width()*0.3)) ;
		m_listComm.InsertColumn((int)E_COMM_TYPE,_T("通信类型"),LVCFMT_CENTER,(int)(rect.Width()*0.3)) ;
		m_listComm.InsertColumn((int)E_COMM_VALUE,_T("通信信息"),LVCFMT_CENTER,(int)(rect.Width()*0.3)) ;

		SetWindowLong(m_listComm.m_hWnd ,GWL_EXSTYLE,WS_EX_CLIENTEDGE);
		////设置扩展风格为网格
		m_listComm.SetExtendedStyle(LVS_EX_GRIDLINES);
	}
	catch (...)
	{
	}
}

void CManageCommunicationDlg::InitRichEdit()
{
	try
	{
		m_ctlSysTipsDisplay1.SetBackgroundColor(FALSE, SYSTEM_WHITE);
	}
	catch (...)
	{
	}
}

void CManageCommunicationDlg::InitComboControl()
{
	try
	{
		m_comboCommList.SnShowImage(_T(".\\res\\bmp\\drop_down.bmp"), 3, 2, SKIN_STATUS_NOR, FALSE);
		m_comboCommList.SnShowImage(_T(".\\res\\bmp\\drop_down.bmp"), 3, 3, SKIN_STATUS_HOT, FALSE);
	}
	catch (...)
	{
	}
}

void CManageCommunicationDlg::UpdataAllControl()
{
	try
	{
		UpdataListControl() ;

		UpdataComboControl() ;
	}
	catch (...)
	{
	}
}

void CManageCommunicationDlg::UpdataListControl()
{
	USES_CONVERSION ;
	UpdateData(TRUE) ;
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		m_listComm.DeleteAllItems() ;

		for (int i = 0 ;i < pDlg->m_projectData.m_mgCommunication.GetCommNodeListSize();i++)
		{
			CCommunicationNode *pCommNode = pDlg->m_projectData.m_mgCommunication.GetCommNodeById(i) ;
			if (NULL == pCommNode)
				continue;

			CString strInfo(_T("")) ;
			strInfo.Format(_T("%d"),pCommNode->nCommId) ;
			m_listComm.InsertItem(i,strInfo) ;

			strInfo = pCommNode->strCommName.c_str() ;
			m_listComm.SetItemText(i,1,strInfo) ;

			if (0 == pCommNode->nCommType)
			{
				strInfo = _T("Comm232") ;
				m_listComm.SetItemText(i,2,strInfo) ;
			}
			else if (1 == pCommNode->nCommType)
			{
				strInfo = _T("CommTcp") ;
				m_listComm.SetItemText(i,2,strInfo) ;
			}
			strInfo = pDlg->m_projectData.m_mgCommunication.GetCommInfo(pCommNode).c_str() ;
			m_listComm.SetItemText(i,3,strInfo) ;
		}
	}
	catch (...)
	{
	}
}

void CManageCommunicationDlg::UpdataComboControl()
{
	USES_CONVERSION ;
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		m_comboCommList.ResetContent() ;
		int nCommSize = pDlg->m_projectData.m_mgCommunication.GetCommNodeListSize() ;
		for (int i = 0 ;i < pDlg->m_projectData.m_mgCommunication.GetCommNodeListSize();i++)
		{
			CCommunicationNode *pCommNode = pDlg->m_projectData.m_mgCommunication.GetCommNodeById(i) ;
			CString strCommName( pCommNode->strCommName.c_str() ) ;
			m_comboCommList.AddString(strCommName) ;
		}
		if (nCommSize >= 0) m_comboCommList.SetCurSel(0) ;
	}
	catch (...)
	{
	}
}

void CManageCommunicationDlg::SetSysTipsInfo(CString strInfo, COLORREF crColor)
{
	try
	{
		CHARFORMAT cf;
		memset(&cf, 0, sizeof(CHARFORMAT));

		m_ctlSysTipsDisplay1.GetSelectionCharFormat(cf);
		cf.dwMask = CFM_COLOR | CFM_SIZE;
		cf.yHeight = 218;
		cf.cbSize = 1000;
		cf.crTextColor = crColor;
		cf.dwEffects = 0;
		m_ctlSysTipsDisplay1.SetSelectionCharFormat(cf);

		CString strLine = _T(""), strEdit = _T("");

		m_ctlSysTipsDisplay1.GetWindowText(strEdit);
		m_ctlSysTipsDisplay1.SetSel(-1, -1);
		strLine.Format(_T("%s\r\n"), strInfo);
		m_ctlSysTipsDisplay1.ReplaceSel(strLine);

		HWND  hWnd = (HWND)m_ctlSysTipsDisplay1;
		int line = ::SendMessage(hWnd, EM_GETFIRSTVISIBLELINE, 0, 0);
		int linecount = ::SendMessage(hWnd, EM_GETLINECOUNT, 0, 0);

		::SendMessage(hWnd, EM_LINESCROLL, 0, (linecount - line - 2));

		//Cancel select all text in richedit control
		m_ctlSysTipsDisplay1.SetOptions(ECOOP_OR, ECO_SAVESEL);
	}
	catch (...)
	{
	}
}

void CManageCommunicationDlg::OnBnClickedBtnAdd()
{
	USES_CONVERSION ;
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		CTypeCommDlg typeCommDlg ;
		CCommunicationNode *pCommNode = new CCommunicationNode() ;
		pCommNode->nCommId = pDlg->m_projectData.m_mgCommunication.GetCommNodeListSize() ;
		if (IDOK == typeCommDlg.DoModal())
		{
			pCommNode->nCommType = typeCommDlg.m_nCommType ;
			if (typeCommDlg.m_strCommName.IsEmpty())
			{
				DELETE_POINT(pCommNode) ;
				AfxMessageBox(_T("请输入通信名")) ;
				return ;
			}
			if (!pDlg->m_projectData.m_mgCommunication.CheckCommName(typeCommDlg.m_strCommName))
			{
				DELETE_POINT(pCommNode) ;
				AfxMessageBox(_T("通信名重复")) ;
				return ;
			}
			pCommNode->strCommName = W2A(typeCommDlg.m_strCommName) ;

			COMM_CODE commCode = E_COMM_NG ;
			if (0 == typeCommDlg.m_nCommType)
			{
				//串口通信
				CAddComm232Dlg addComm232Dlg ;
				if (IDOK != addComm232Dlg.DoModal())
				{
					DELETE_POINT(pCommNode) ;
					return ;
				}
				pCommNode->aCommValue = addComm232Dlg.m_comm232Node ;
				pCommNode->mgrDllCommuncitionBaseIm.DllCreateInterface((long)E_TOOL_COMMUNICATION_COMM232,(void **)&pCommNode->pCommunicationBase) ;
				if (NULL == pCommNode->pCommunicationBase)
				{
					DELETE_POINT(pCommNode) ;
					AfxMessageBox(_T("加载Comm232Dll失败")) ;
					return ;
				}

				string strComm232Info = pDlg->m_projectData.m_mgCommunication.GetCommInfo(pCommNode).c_str() ;
				commCode = pCommNode->pCommunicationBase->Comm_Init(strComm232Info) ;
				if (E_COMM_OK != commCode)
					AfxMessageBox(_T("Comm232 Init Fail")) ;
			}
			else if (1 == typeCommDlg.m_nCommType)
			{
				//网络通信
				 CAddCommTcpDlg addCommTcpDlg ;
				 if (IDOK != addCommTcpDlg.DoModal())
				 {
					 DELETE_POINT(pCommNode) ;
					 return ;
				 }
				 pCommNode->aCommValue = addCommTcpDlg.m_commSocketNode ;
				 pCommNode->mgrDllCommuncitionBaseIm.DllCreateInterface((long)E_TOOL_COMMUNICATION_TCPIP,(void **)&pCommNode->pCommunicationBase) ;
				 if (NULL == pCommNode->pCommunicationBase)
				 {
					 DELETE_POINT(pCommNode) ;
					 AfxMessageBox(_T("加载CommSocketDll失败")) ;
					 return ;
				 }

				 string strCommSocketInfo = pDlg->m_projectData.m_mgCommunication.GetCommInfo(pCommNode).c_str() ;
				 commCode = pCommNode->pCommunicationBase->Comm_Init(strCommSocketInfo) ;
				 if (E_COMM_OK != commCode)
					 AfxMessageBox(_T("CommSocket Init Fail")) ;
			}

			pDlg->m_projectData.m_mgCommunication.AddTail(pCommNode) ;

			UpdataAllControl() ;
		}
		else
		{
			DELETE_POINT(pCommNode) ;
		}
	}
	catch (...)
	{
	}
}

void CManageCommunicationDlg::OnBnClickedBtnEdit()
{
	USES_CONVERSION ;
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		int nCurSel = m_listComm.GetSelectionMark() ;
		if (nCurSel < 0)
		{
			AfxMessageBox(_T("请选中编辑")) ;
			return ;
		}

		COMM_CODE commCode = E_COMM_NG ;
		CCommunicationNode *pCommNode = pDlg->m_projectData.m_mgCommunication.GetCommNodeById(nCurSel) ;
		if (0 == pCommNode->nCommType)
		{
			//串口通信
			CAddComm232Dlg addComm232Dlg ;
			addComm232Dlg.m_comm232Node = any_cast<COMM232NODE>(pCommNode->aCommValue) ;
			if (IDOK != addComm232Dlg.DoModal()) return ;
			pCommNode->aCommValue = addComm232Dlg.m_comm232Node ;

			pCommNode->pCommunicationBase->Comm_Close() ;
			string strComm232Info = pDlg->m_projectData.m_mgCommunication.GetCommInfo(pCommNode).c_str() ;
			commCode = pCommNode->pCommunicationBase->Comm_Init(strComm232Info) ;
			if (E_COMM_OK != commCode)
				AfxMessageBox(_T("Comm232 Init Fail")) ;
		}
		else if (1 == pCommNode->nCommType)
		{
			//网络通信
			CAddCommTcpDlg addCommTcpDlg ;
			addCommTcpDlg.m_commSocketNode = any_cast<COMMSOCKETNODE>(pCommNode->aCommValue) ;
			if (IDOK != addCommTcpDlg.DoModal()) return ;
			pCommNode->aCommValue = addCommTcpDlg.m_commSocketNode ;

			pCommNode->pCommunicationBase->Comm_Close() ;
			string strCommSocketInfo = pDlg->m_projectData.m_mgCommunication.GetCommInfo(pCommNode).c_str() ;
			commCode = pCommNode->pCommunicationBase->Comm_Init(strCommSocketInfo) ;
			if (E_COMM_OK != commCode)
				AfxMessageBox(_T("CommSocket Init Fail")) ;
		}

		UpdataAllControl() ;
	}
	catch (...)
	{
	}
}

void CManageCommunicationDlg::OnBnClickedBtnDel()
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		int nCurSel = m_listComm.GetSelectionMark() ;
		if (nCurSel < 0)
		{
			AfxMessageBox(_T("请选中删除")) ;
			return ;
		}

		CCommunicationNode *pCommNode = pDlg->m_projectData.m_mgCommunication.GetCommNodeById(nCurSel) ;
		pCommNode->pCommunicationBase->Comm_Close() ;
		pCommNode->pCommunicationBase->Comm_Release() ;

		pDlg->m_projectData.m_mgCommunication.RemoveAtById(nCurSel) ;
		pDlg->m_projectData.m_mgCommunication.ReSortId() ;

		UpdataAllControl() ;
	}
	catch (...)
	{
	}
}

void CManageCommunicationDlg::OnBnClickedOk()
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		pDlg->m_projectData.SaveCommunicationConfig() ;

		AfxMessageBox(_T("保存成功")) ;
	}
	catch (...)
	{
	}
	CDialogEx::OnOK();
}

void CManageCommunicationDlg::OnNMDblclkListComm(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	OnBnClickedBtnEdit() ;

	*pResult = 0;
}

void CManageCommunicationDlg::OnBnClickedBtnSend()
{
	USES_CONVERSION ;
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		UpdateData(TRUE) ;

		int nCurSel = m_comboCommList.GetCurSel() ;
		if (nCurSel < 0) return ;

		CCommunicationNode *pCommNode = pDlg->m_projectData.m_mgCommunication.GetCommNodeById(nCurSel) ;
		if (NULL == pCommNode) return ;

		EnterCriticalSection(&m_csComm) ;
		pCommNode->pCommunicationBase->Comm_SendData(W2A(m_strSendData)) ;
		LeaveCriticalSection(&m_csComm) ;
	}
	catch (...)
	{
	}
}

void CManageCommunicationDlg::OnBnClickedBtnRead()
{
	USES_CONVERSION ;
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		int nCurSel = m_comboCommList.GetCurSel() ;
		if (nCurSel < 0) return ;

		CCommunicationNode *pCommNode = pDlg->m_projectData.m_mgCommunication.GetCommNodeById(nCurSel) ;
		if (NULL == pCommNode) return ;

		CString strInfo(_T("")) ;
		string strRecData("") ;

		EnterCriticalSection(&m_csComm) ;
		pCommNode->pCommunicationBase->Comm_RevData(strRecData) ;
		LeaveCriticalSection(&m_csComm) ;
		pCommNode->pCommunicationBase->Comm_ClearData() ;

		strInfo = strRecData.c_str() ;
		if (strInfo.IsEmpty()) return ;
		SetSysTipsInfo(strInfo,SYSTEM_BLUE) ;
	}
	catch (...)
	{
	}
}

void CManageCommunicationDlg::OnBnClickedBtnClear()
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		m_ctlSysTipsDisplay1.SetWindowText(_T("")) ;
	}
	catch (...)
	{
	}
}

void CManageCommunicationDlg::OnBnClickedBtnReconnect()
{
	USES_CONVERSION ;
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		int nCurSel = m_listComm.GetSelectionMark() ;
		if (nCurSel < 0) return ;

		CCommunicationNode *pCommNode = pDlg->m_projectData.m_mgCommunication.GetCommNodeById(nCurSel) ;
		if (NULL == pCommNode) return ;

		pCommNode->pCommunicationBase->Comm_Close() ;
		if (0 == pCommNode->nCommType)
		{
			//串口通信
			string strComm232Info = pDlg->m_projectData.m_mgCommunication.GetCommInfo(pCommNode).c_str() ;
			if(E_COMM_OK == pCommNode->pCommunicationBase->Comm_Init(strComm232Info) )
			{
				AfxMessageBox(_T("串口通信重连成功")) ;
			}
			else
			{
				AfxMessageBox(_T("串口通信重连失败")) ;
			}
		}
		else if (1 == pCommNode->nCommType)
		{
			//网络通信
			string strCommTcpInfo = pDlg->m_projectData.m_mgCommunication.GetCommInfo(pCommNode).c_str() ;
			if(E_COMM_OK == pCommNode->pCommunicationBase->Comm_Init(strCommTcpInfo) )
			{
				AfxMessageBox(_T("网络通信重连成功")) ;
			}
			else
			{
				AfxMessageBox(_T("网络通信重连失败")) ;
			}
		}
	}
	catch (...)
	{
	}
}