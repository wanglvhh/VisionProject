// ManageModbusDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "VisionProject.h"
#include "ManageModbusDlg.h"
#include "afxdialogex.h"
#include "VisionProjectDlg.h"
#include "TypeModbusDlg.h"
#include "AddRtuMasterDlg.h"
#include "AddRtuSlaveDlg.h"
#include "AddTcpMasterDlg.h"
#include "AddTcpSlaveDlg.h"
#include "NewDlg.h"

// CManageModbusDlg 对话框

IMPLEMENT_DYNAMIC(CManageModbusDlg, CDialogEx)

CManageModbusDlg::CManageModbusDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CManageModbusDlg::IDD, pParent)
	, m_uPlcStartAddress(0)
	, m_uReadNum(0)
	, m_dbReadValue(0)
{
	InitializeCriticalSection(&m_csModbus);
	m_vecWrite.clear() ;
}

CManageModbusDlg::~CManageModbusDlg()
{
	//删除临界区
	DeleteCriticalSection(&m_csModbus) ;
	m_vecWrite.clear() ;
}

void CManageModbusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_ADD, m_btnAdd);
	DDX_Control(pDX, IDC_BTN_EDIT, m_btnEdit);
	DDX_Control(pDX, IDC_BTN_DEL, m_btnDel);
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_LIST_MODBUS, m_listModbus);
	DDX_Control(pDX, IDC_BTN_RECONNECT, m_btnReConnect);
	DDX_Control(pDX, IDC_COMBO_MODBUSLIST, m_comboModbusList);
	DDX_Control(pDX, IDC_BTN_READ1, m_btnRead1);
	DDX_Control(pDX, IDC_BTN_ADD1, m_btnAdd1);
	DDX_Control(pDX, IDC_BTN_EDIT1, m_btnEdit1);
	DDX_Control(pDX, IDC_BTN_DEL1, m_btnDel1);
	DDX_Control(pDX, IDC_BTN_WRITE1, m_btnWrite1);
	DDX_Control(pDX, IDC_BTN_READ2, m_btnRead2);
	DDX_Control(pDX, IDC_BTN_WRITE2, m_btnWrite2);
	DDX_Text(pDX, IDC_EDIT_PLCSTART_ADDRESS, m_uPlcStartAddress);
	DDX_Text(pDX, IDC_EDIT_NUM, m_uReadNum);
	DDX_Control(pDX, IDC_LIST_READ, m_listRead);
	DDX_Text(pDX, IDC_EDIT_READDOUBLEVALUE, m_dbReadValue);
	DDX_Control(pDX, IDC_RICHEDIT21, m_ctlSysTipsDisplay1);
}

BEGIN_MESSAGE_MAP(CManageModbusDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_ADD, &CManageModbusDlg::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_EDIT, &CManageModbusDlg::OnBnClickedBtnEdit)
	ON_BN_CLICKED(IDC_BTN_DEL, &CManageModbusDlg::OnBnClickedBtnDel)
	ON_BN_CLICKED(IDOK, &CManageModbusDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_RECONNECT, &CManageModbusDlg::OnBnClickedBtnReconnect)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_MODBUS, &CManageModbusDlg::OnNMDblclkListModbus)
	ON_EN_CHANGE(IDC_EDIT_PLCSTART_ADDRESS, &CManageModbusDlg::OnEnChangeEditPlcstartAddress)
	ON_EN_CHANGE(IDC_EDIT_NUM, &CManageModbusDlg::OnEnChangeEditNum)
	ON_EN_CHANGE(IDC_EDIT_READDOUBLEVALUE, &CManageModbusDlg::OnEnChangeEditReaddoublevalue)
	ON_BN_CLICKED(IDC_BTN_READ1, &CManageModbusDlg::OnBnClickedBtnRead1)
	ON_BN_CLICKED(IDC_BTN_READ2, &CManageModbusDlg::OnBnClickedBtnRead2)
	ON_BN_CLICKED(IDC_BTN_ADD1, &CManageModbusDlg::OnBnClickedBtnAdd1)
	ON_BN_CLICKED(IDC_BTN_EDIT1, &CManageModbusDlg::OnBnClickedBtnEdit1)
	ON_BN_CLICKED(IDC_BTN_DEL1, &CManageModbusDlg::OnBnClickedBtnDel1)
	ON_BN_CLICKED(IDC_BTN_WRITE1, &CManageModbusDlg::OnBnClickedBtnWrite1)
	ON_BN_CLICKED(IDC_BTN_WRITE2, &CManageModbusDlg::OnBnClickedBtnWrite2)
END_MESSAGE_MAP()

// CManageModbusDlg 消息处理程序

BOOL CManageModbusDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitAllControl() ;

	UpdataAllControl() ;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CManageModbusDlg::InitAllControl()
{
	try
	{
		//初始化BtnControl
		InitBtnControl() ;
		//初始化ListControl
		InitListControl() ;
		//初始化ListControl2
		InitListControl2() ;
		//初始化ComboControl
		InitComboControl() ;
		//初始化RichEdit
		InitRichEdit() ;
	}
	catch (...)
	{
	}
}

void CManageModbusDlg::InitBtnControl()
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

		m_btnRead1.SetIcon(IDI_ICON_READ2) ;
		m_btnRead1.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnRead1.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnRead1.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnRead1.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnRead1.SetRounded(TRUE) ;

		m_btnRead2.SetIcon(IDI_ICON_READ2) ;
		m_btnRead2.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnRead2.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnRead2.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnRead2.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnRead2.SetRounded(TRUE) ;

		m_btnAdd1.SetIcon(IDI_ICON_ADD2) ;
		m_btnAdd1.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnAdd1.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnAdd1.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnAdd1.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnAdd1.SetRounded(TRUE) ;

		m_btnEdit1.SetIcon(IDI_ICON_EDIT2) ;
		m_btnEdit1.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnEdit1.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnEdit1.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnEdit1.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnEdit1.SetRounded(TRUE) ;

		m_btnDel1.SetIcon(IDI_ICON_DELFLOW2) ;
		m_btnDel1.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnDel1.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnDel1.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnDel1.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnDel1.SetRounded(TRUE) ;

		m_btnWrite1.SetIcon(IDI_ICON_WRITE2) ;
		m_btnWrite1.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnWrite1.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnWrite1.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnWrite1.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnWrite1.SetRounded(TRUE) ;

		m_btnWrite2.SetIcon(IDI_ICON_WRITE2) ;
		m_btnWrite2.SetAlign(CButtonST::ST_ALIGN_VERT);
		m_btnWrite2.SetColor(CButtonST::BTNST_COLOR_FG_IN, BTNST_COLOR_FG_IN_COLOR);
		m_btnWrite2.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BTNST_COLOR_FG_OUT_COLOR);
		m_btnWrite2.SetColor(CButtonST::BTNST_COLOR_BK_OUT, SYSTEM_BK_COLOR);
		m_btnWrite2.SetRounded(TRUE) ;
	}
	catch (...)
	{
	}
}

void CManageModbusDlg::InitListControl()
{
	try
	{
		////设置列背景颜色
		m_listModbus.SetColColor(E_MODBUS_ID,SYSTEM_BK_COLOR) ;
		m_listModbus.SetColColor(E_MODBUS_NAME,SYSTEM_BK_COLOR) ;
		m_listModbus.SetColColor(E_MODBUS_TYPE,SYSTEM_BK_COLOR) ;
		m_listModbus.SetColColor(E_MODBUS_VALUE,SYSTEM_BK_COLOR) ;
		////设置背景颜色
		m_listModbus.SetBkColor(SYSTEM_BK_COLOR) ;
		////设置行高
		m_listModbus.SetRowHeight(25) ;
		////设置头部高度
		m_listModbus.SetHeaderHeight(1.5) ;
		////设置头部字体高度,和宽度,0表示缺省，自适应
		m_listModbus.SetHeaderFontHW(16,0);
		////设置头部字体颜色
		m_listModbus.SetHeaderTextColor(RGB(255,200,100));
		////设置文本颜色
		m_listModbus.SetTextColor(SYSTEM_BLACK);
		////设置头部背景色
		m_listModbus.SetHeaderBKColor(245,245,245,8);
		////设置字体高度，和宽度,0表示缺省宽度
		m_listModbus.SetFontHW(15,0);
		////设置列文本颜色
		m_listModbus.SetColTextColor((int)E_MODBUS_ID,SYSTEM_BLUE);
		m_listModbus.SetColTextColor((int)E_MODBUS_NAME,SYSTEM_BLUE);
		m_listModbus.SetColTextColor((int)E_MODBUS_TYPE,SYSTEM_RED);
		////设置单元格字体颜色
		////m_listCamera.SetItemTextColor(3,1,RGB(255,0,0));

		CRect rect ;
		m_listModbus.GetClientRect(&rect) ;
		m_listModbus.InsertColumn((int)E_MODBUS_ID,_T("ModbusID"),LVCFMT_CENTER,(int)(rect.Width()*0.15)) ;
		m_listModbus.InsertColumn((int)E_MODBUS_NAME,_T("Modbus名称"),LVCFMT_CENTER,(int)(rect.Width()*0.3)) ;
		m_listModbus.InsertColumn((int)E_MODBUS_TYPE,_T("Modbus类型"),LVCFMT_CENTER,(int)(rect.Width()*0.2)) ;
		m_listModbus.InsertColumn((int)E_MODBUS_VALUE,_T("Modbus信息"),LVCFMT_CENTER,(int)(rect.Width()*0.35)) ;

		SetWindowLong(m_listModbus.m_hWnd ,GWL_EXSTYLE,WS_EX_CLIENTEDGE);
		////设置扩展风格为网格
		m_listModbus.SetExtendedStyle(LVS_EX_GRIDLINES);
	}
	catch (...)
	{
	}
}

void CManageModbusDlg::InitListControl2()
{
	try
	{
		////设置列背景颜色
		m_listRead.SetColColor(E_READ_ID,SYSTEM_BK_COLOR) ;
		m_listRead.SetColColor(E_READ_VALUE,SYSTEM_BK_COLOR) ;
		////设置背景颜色
		m_listRead.SetBkColor(SYSTEM_BK_COLOR) ;
		////设置行高
		m_listRead.SetRowHeight(16) ;
		////设置头部高度
		m_listRead.SetHeaderHeight(1.0) ;
		////设置头部字体高度,和宽度,0表示缺省，自适应
		m_listRead.SetHeaderFontHW(16,0);
		////设置头部字体颜色
		m_listRead.SetHeaderTextColor(RGB(255,200,100));
		////设置文本颜色
		m_listRead.SetTextColor(SYSTEM_BLACK);
		////设置头部背景色
		m_listRead.SetHeaderBKColor(245,245,245,8);
		////设置字体高度，和宽度,0表示缺省宽度
		m_listRead.SetFontHW(15,0);
		////设置列文本颜色
		m_listRead.SetColTextColor((int)E_READ_ID,SYSTEM_BLUE);
		m_listRead.SetColTextColor((int)E_READ_VALUE,SYSTEM_RED);
		////设置单元格字体颜色
		////m_listCamera.SetItemTextColor(3,1,RGB(255,0,0));

		CRect rect ;
		m_listRead.GetClientRect(&rect) ;
		m_listRead.InsertColumn((int)E_READ_ID,_T("ID"),LVCFMT_CENTER,(int)(rect.Width()*0.2)) ;
		m_listRead.InsertColumn((int)E_READ_VALUE,_T("读取值"),LVCFMT_CENTER,(int)(rect.Width()*0.8)) ;

		SetWindowLong(m_listRead.m_hWnd ,GWL_EXSTYLE,WS_EX_CLIENTEDGE);
		////设置扩展风格为网格
		m_listRead.SetExtendedStyle(LVS_EX_GRIDLINES);
	}
	catch (...)
	{
	}
}

void CManageModbusDlg::InitRichEdit()
{
	try
	{
		m_ctlSysTipsDisplay1.SetBackgroundColor(FALSE, SYSTEM_WHITE);
	}
	catch (...)
	{
	}
}

void CManageModbusDlg::InitComboControl()
{
	try
	{
		m_comboModbusList.SnShowImage(_T(".\\res\\bmp\\drop_down.bmp"), 3, 2, SKIN_STATUS_NOR, FALSE);
		m_comboModbusList.SnShowImage(_T(".\\res\\bmp\\drop_down.bmp"), 3, 3, SKIN_STATUS_HOT, FALSE);
	}
	catch (...)
	{
	}
}

void CManageModbusDlg::UpdataAllControl()
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

void CManageModbusDlg::UpdataListControl()
{
	USES_CONVERSION ;
	UpdateData(TRUE) ;
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		m_listModbus.DeleteAllItems() ;

		for (int i = 0 ;i < pDlg->m_projectData.m_mgModbus.GetModbusNodeListSize();i++)
		{
			CModbusNode *pModbusNode = pDlg->m_projectData.m_mgModbus.GetModbusNodeById(i) ;
			if (NULL == pModbusNode)
				continue;

			CString strInfo(_T("")) ;
			strInfo.Format(_T("%d"),pModbusNode->nModbusID) ;
			m_listModbus.InsertItem(i,strInfo) ;

			strInfo = pModbusNode->strModbusName.c_str() ;
			m_listModbus.SetItemText(i,1,strInfo) ;

			if (0 == pModbusNode->nModbusType)
			{
				//RtuMaster
				strInfo = _T("RtuMaster") ;
				m_listModbus.SetItemText(i,2,strInfo) ;
			}
			else if (1 == pModbusNode->nModbusType)
			{
				//RtuSlave
				strInfo = _T("RtuSlave") ;
				m_listModbus.SetItemText(i,2,strInfo) ;
			}
			else if (2 == pModbusNode->nModbusType)
			{
				//TcpMaster
				strInfo = _T("TcpMaster") ;
				m_listModbus.SetItemText(i,2,strInfo) ;
			}
			else if (3 == pModbusNode->nModbusType)
			{
				//TcpSlave
				strInfo = _T("TcpSlave") ;
				m_listModbus.SetItemText(i,2,strInfo) ;
			}
			strInfo = pDlg->m_projectData.m_mgModbus.GetModbusInfo(pModbusNode).c_str() ;
			m_listModbus.SetItemText(i,3,strInfo) ;
		}
	}
	catch (...)
	{
	}
}

void CManageModbusDlg::UpdataListControl2()
{
	USES_CONVERSION ;
	UpdateData(TRUE) ;
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		m_listRead.DeleteAllItems() ;

		for (int i = 0 ;i < m_vecWrite.size();i++)
		{
			CString strInfo(_T("")) ;
			strInfo.Format(_T("%d"),i) ;
			m_listRead.InsertItem(i,strInfo) ;

			strInfo.Format(_T("%d"),m_vecWrite[i]) ;
			m_listRead.SetItemText(i,1,strInfo) ;
		}
	}
	catch (...)
	{
	}
}

void CManageModbusDlg::UpdataComboControl()
{
	USES_CONVERSION ;
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		m_comboModbusList.ResetContent() ;
		int nModbusSize = pDlg->m_projectData.m_mgModbus.GetModbusNodeListSize() ;
		for (int i = 0 ;i < pDlg->m_projectData.m_mgModbus.GetModbusNodeListSize();i++)
		{
			CModbusNode *pModbusNode = pDlg->m_projectData.m_mgModbus.GetModbusNodeById(i) ;
			CString strModbusName( pModbusNode->strModbusName.c_str() ) ;
			m_comboModbusList.AddString(strModbusName) ;
		}
		if (nModbusSize >= 0) m_comboModbusList.SetCurSel(0) ;
	}
	catch (...)
	{
	}
}

void CManageModbusDlg::SetSysTipsInfo(CString strInfo, COLORREF crColor)
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

void CManageModbusDlg::OnBnClickedBtnAdd()
{
	USES_CONVERSION ;
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		CTypeModbusDlg typeModbusDlg ;
		CModbusNode*   pModbusNode = new CModbusNode() ;
		pModbusNode->nModbusID = pDlg->m_projectData.m_mgModbus.GetModbusNodeListSize() ;
		if (IDOK == typeModbusDlg.DoModal())
		{
			pModbusNode->nModbusType = typeModbusDlg.m_nModbusType ;
			if (typeModbusDlg.m_strModbusName.IsEmpty())
			{
				DELETE_POINT(pModbusNode) ;
				AfxMessageBox(_T("请输入通信名")) ;
				return ;
			}
			if (!pDlg->m_projectData.m_mgModbus.CheckModbusName(typeModbusDlg.m_strModbusName))
			{
				DELETE_POINT(pModbusNode) ;
				AfxMessageBox(_T("通信名重复")) ;
				return ;
			}
			pModbusNode->strModbusName = W2A(typeModbusDlg.m_strModbusName) ;

			MODBUS_CODE modbusCode = E_MODBUS_NG ;
			if (0 == typeModbusDlg.m_nModbusType)
			{
				//RtuMaster
				CAddRtuMasterDlg addRtuMasterDlg ;
				if (IDOK != addRtuMasterDlg.DoModal())
				{
					DELETE_POINT(pModbusNode) ;
					return ;
				}

				pModbusNode->aModbusValue = addRtuMasterDlg.m_rtuMasterNode ;
				pModbusNode->mgrDllModbusBaseDllIm.DllCreateInterface((long)E_TOOL_MODBUS_RTUMASTER,(void **)&pModbusNode->pModbusBase) ;
				if (NULL == pModbusNode->pModbusBase)
				{
					DELETE_POINT(pModbusNode) ;
					AfxMessageBox(_T("加载ModbusRtuMaster失败")) ;
					return ;
				}
			}
			else if (1 == typeModbusDlg.m_nModbusType)
			{
				//RtuSlave
				CAddRtuSlaveDlg addRtuSlaveDlg ;
				if (IDOK != addRtuSlaveDlg.DoModal())
				{
					DELETE_POINT(pModbusNode) ;
					return ;
				}

				pModbusNode->aModbusValue = addRtuSlaveDlg.m_rtuSlaveNode ;
				pModbusNode->mgrDllModbusBaseDllIm.DllCreateInterface((long)E_TOOL_MODBUS_RTUSLAVE,(void **)&pModbusNode->pModbusBase) ;
				if (NULL == pModbusNode->pModbusBase)
				{
					AfxMessageBox(_T("加载ModbusRtuSlave失败")) ;
					DELETE_POINT(pModbusNode) ;
					return ;
				}
			}
			else if (2 == typeModbusDlg.m_nModbusType)
			{
				//TcpMaster
				CAddTcpMasterDlg addTcpMasterDlg ;
				if (IDOK != addTcpMasterDlg.DoModal())
				{
					DELETE_POINT(pModbusNode) ;
					return ;
				}

				pModbusNode->aModbusValue = addTcpMasterDlg.m_tcpMasterNode ;
				pModbusNode->mgrDllModbusBaseDllIm.DllCreateInterface((long)E_TOOL_MODBUS_TCPMASTER,(void **)&pModbusNode->pModbusBase) ;
				if (NULL == pModbusNode->pModbusBase)
				{
					AfxMessageBox(_T("加载ModbusTcpMaster失败")) ;
					DELETE_POINT(pModbusNode) ;
					return ;
				}
			}
			else if (3 == typeModbusDlg.m_nModbusType)
			{
				//TcpSlave
				CAddTcpSlaveDlg addTcpSlaveDlg ;
				if (IDOK != addTcpSlaveDlg.DoModal())
				{
					DELETE_POINT(pModbusNode) ;
					return ;
				}

				pModbusNode->aModbusValue = addTcpSlaveDlg.m_tcpSlaveNode ;
				pModbusNode->mgrDllModbusBaseDllIm.DllCreateInterface((long)E_TOOL_MODBUS_TCPSLAVE,(void **)&pModbusNode->pModbusBase) ;
				if (NULL == pModbusNode->pModbusBase)
				{
					AfxMessageBox(_T("加载ModbusTcpSlave失败")) ;
					DELETE_POINT(pModbusNode) ;
					return ;
				}
			}

			string strModbusInfo =  pDlg->m_projectData.m_mgModbus.GetModbusInfo(pModbusNode).c_str() ;
			modbusCode = pModbusNode->pModbusBase->Modbus_Init(strModbusInfo) ;
			if (E_MODBUS_OK != modbusCode)
				AfxMessageBox(_T("Modbus_Init Fail")) ;

			pDlg->m_projectData.m_mgModbus.AddTail(pModbusNode) ;

			UpdataAllControl() ;
		}
		else
		{
			DELETE_POINT(pModbusNode) ;
		}
	}
	catch (...)
	{
	}
}

void CManageModbusDlg::OnBnClickedBtnEdit()
{
	USES_CONVERSION ;
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		int nCurSel = m_listModbus.GetSelectionMark() ;
		if (nCurSel < 0)
		{
			AfxMessageBox(_T("请选中编辑")) ;
			return ;
		}

		MODBUS_CODE modbusCode = E_MODBUS_NG ;
		CModbusNode *pModbusNode = pDlg->m_projectData.m_mgModbus.GetModbusNodeById(nCurSel) ;
		if (0 == pModbusNode->nModbusType)
		{
			//RtuMaster
			CAddRtuMasterDlg addRtuMasterDlg ;
			addRtuMasterDlg.m_rtuMasterNode = any_cast<RTUMASTERNODE>(pModbusNode->aModbusValue) ;
			if (IDOK != addRtuMasterDlg.DoModal()) return ;
			pModbusNode->aModbusValue = addRtuMasterDlg.m_rtuMasterNode ;

			pModbusNode->pModbusBase->Modbus_Close() ;
			string strRtuMasterInfo = pDlg->m_projectData.m_mgModbus.GetModbusInfo(pModbusNode).c_str() ;
			modbusCode = pModbusNode->pModbusBase->Modbus_Init(strRtuMasterInfo) ;
			if (E_COMM_OK != modbusCode)
				AfxMessageBox(_T("RtuMaster Init Fail")) ;
		}
		else if (1 == pModbusNode->nModbusType)
		{
			//RtuSlave
			CAddRtuSlaveDlg addRtuSlaveDlg ;
			addRtuSlaveDlg.m_rtuSlaveNode = any_cast<RTUSLAVENODE>(pModbusNode->aModbusValue) ;
			if (IDOK != addRtuSlaveDlg.DoModal()) return ;
			pModbusNode->aModbusValue = addRtuSlaveDlg.m_rtuSlaveNode ;

			pModbusNode->pModbusBase->Modbus_Close() ;
			string strRtuSlaveInfo = pDlg->m_projectData.m_mgModbus.GetModbusInfo(pModbusNode).c_str() ;
			modbusCode = pModbusNode->pModbusBase->Modbus_Init(strRtuSlaveInfo) ;
			if (E_COMM_OK != modbusCode)
				AfxMessageBox(_T("RtuSlave Init Fail")) ;
		}
		else if (2 == pModbusNode->nModbusType)
		{
			//TcpMaster
			CAddTcpMasterDlg addTcpMasterDlg ;
			addTcpMasterDlg.m_tcpMasterNode = any_cast<TCPMASTERNODE>(pModbusNode->aModbusValue) ;
			if (IDOK != addTcpMasterDlg.DoModal()) return ;
			pModbusNode->aModbusValue = addTcpMasterDlg.m_tcpMasterNode ;

			pModbusNode->pModbusBase->Modbus_Close() ;
			string strTcpMasterInfo = pDlg->m_projectData.m_mgModbus.GetModbusInfo(pModbusNode).c_str() ;
			modbusCode = pModbusNode->pModbusBase->Modbus_Init(strTcpMasterInfo) ;
			if (E_COMM_OK != modbusCode)
				AfxMessageBox(_T("TcpMaster Init Fail")) ;
		}
		else if (3 == pModbusNode->nModbusType)
		{
			//TcpSlave
			CAddTcpSlaveDlg addTcpSlaveDlg ;
			addTcpSlaveDlg.m_tcpSlaveNode = any_cast<TCPSLAVENODE>(pModbusNode->aModbusValue) ;
			if (IDOK != addTcpSlaveDlg.DoModal()) return ;
			pModbusNode->aModbusValue = addTcpSlaveDlg.m_tcpSlaveNode ;

			pModbusNode->pModbusBase->Modbus_Close() ;
			string strTcpSlaveInfo = pDlg->m_projectData.m_mgModbus.GetModbusInfo(pModbusNode).c_str() ;
			modbusCode = pModbusNode->pModbusBase->Modbus_Init(strTcpSlaveInfo) ;
			if (E_COMM_OK != modbusCode)
				AfxMessageBox(_T("TcpSlave Init Fail")) ;
		}

		UpdataAllControl() ;
	}
	catch (...)
	{
	}
}

void CManageModbusDlg::OnBnClickedBtnDel()
{
	USES_CONVERSION ;
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		int nCurSel = m_listModbus.GetSelectionMark() ;
		if (nCurSel < 0)
		{
			AfxMessageBox(_T("请选中删除")) ;
			return ;
		}

		CModbusNode *pModbusNode = pDlg->m_projectData.m_mgModbus.GetModbusNodeById(nCurSel) ;
		pModbusNode->pModbusBase->Modbus_Close() ;
		pModbusNode->pModbusBase->Modbus_Release() ;

		pDlg->m_projectData.m_mgModbus.RemoveAtById(nCurSel) ;
		pDlg->m_projectData.m_mgModbus.ReSortId() ;

		UpdataAllControl() ;
	}
	catch (...)
	{
	}
}

void CManageModbusDlg::OnBnClickedBtnReconnect()
{
	USES_CONVERSION ;
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		int nCurSel = m_listModbus.GetSelectionMark() ;
		if (nCurSel < 0) return ;

		CModbusNode *pModbusNode = pDlg->m_projectData.m_mgModbus.GetModbusNodeById(nCurSel) ;
		if (NULL == pModbusNode) return ;

		pModbusNode->pModbusBase->Modbus_Close() ;
		if (0 == pModbusNode->nModbusType)
		{
			//RtuMaster
			string strRtuMasterInfo = pDlg->m_projectData.m_mgModbus.GetModbusInfo(pModbusNode).c_str() ;
			if(E_COMM_OK == pModbusNode->pModbusBase->Modbus_Init(strRtuMasterInfo) )
			{
				AfxMessageBox(_T("RtuMaster重连成功")) ;
			}
			else
			{
				AfxMessageBox(_T("RtuMaster重连失败")) ;
			}
		}
		else if (1 == pModbusNode->nModbusType)
		{
			//RtuSlave
			string strRtuSlaveInfo = pDlg->m_projectData.m_mgModbus.GetModbusInfo(pModbusNode).c_str() ;
			if(E_COMM_OK == pModbusNode->pModbusBase->Modbus_Init(strRtuSlaveInfo) )
			{
				AfxMessageBox(_T("RtuSlave重连成功")) ;
			}
			else
			{
				AfxMessageBox(_T("RtuSlave重连失败")) ;
			}
		}
		else if (2 == pModbusNode->nModbusType)
		{
			//TcpMaster
			string strTcpMasterInfo = pDlg->m_projectData.m_mgModbus.GetModbusInfo(pModbusNode).c_str() ;
			if(E_COMM_OK == pModbusNode->pModbusBase->Modbus_Init(strTcpMasterInfo) )
			{
				AfxMessageBox(_T("TcpMaster重连成功")) ;
			}
			else
			{
				AfxMessageBox(_T("TcpMaster重连失败")) ;
			}
		}
		else if (3 == pModbusNode->nModbusType)
		{
			//TcpSlave
			string strTcpSlaveInfo = pDlg->m_projectData.m_mgModbus.GetModbusInfo(pModbusNode).c_str() ;
			if(E_COMM_OK == pModbusNode->pModbusBase->Modbus_Init(strTcpSlaveInfo) )
			{
				AfxMessageBox(_T("TcpSlave重连成功")) ;
			}
			else
			{
				AfxMessageBox(_T("TcpSlave重连失败")) ;
			}
		}
	}
	catch (...)
	{
	}
}

void CManageModbusDlg::OnBnClickedOk()
{
	USES_CONVERSION ;
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		pDlg->m_projectData.SaveModbusConfig() ;

		AfxMessageBox(_T("保存成功")) ;
	}
	catch (...)
	{
	}
	CDialogEx::OnOK();
}

void CManageModbusDlg::OnNMDblclkListModbus(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	OnBnClickedBtnEdit() ;

	*pResult = 0;
}

void CManageModbusDlg::OnEnChangeEditPlcstartAddress()
{
	UpdateData(TRUE) ;
}

void CManageModbusDlg::OnEnChangeEditNum()
{
	UpdateData(TRUE) ;
}

void CManageModbusDlg::OnEnChangeEditReaddoublevalue()
{
	UpdateData(TRUE) ;
}

void CManageModbusDlg::OnBnClickedBtnRead1()
{
	USES_CONVERSION ;
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		UpdateData(TRUE) ;

		int nCurSel = m_comboModbusList.GetCurSel() ;
		if (nCurSel < 0) return ;

		CModbusNode *pModbusNode = pDlg->m_projectData.m_mgModbus.GetModbusNodeById(nCurSel) ;
		if (NULL == pModbusNode) return ;

		vector<short> vecReadValue ;
		vecReadValue.clear() ;

		EnterCriticalSection(&m_csModbus) ;
		pModbusNode->pModbusBase->Modbus_ReadRegisters(m_uPlcStartAddress,m_uReadNum,vecReadValue) ;
		LeaveCriticalSection(&m_csModbus) ;

		for (int i = 0 ;i < vecReadValue.size();i++)
		{
			CString strInfo(_T("")) ;
			strInfo.Format(_T("Addr = %d , Val = %d(0x%X)"), m_uPlcStartAddress + i, vecReadValue[i], vecReadValue[i]);
			SetSysTipsInfo(strInfo, SYSTEM_BLUE);
		}
	}
	catch (...)
	{
	}
}

void CManageModbusDlg::OnBnClickedBtnRead2()
{
	USES_CONVERSION ;
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		UpdateData(TRUE) ;

		int nCurSel = m_comboModbusList.GetCurSel() ;
		if (nCurSel < 0) return ;

		CModbusNode *pModbusNode = pDlg->m_projectData.m_mgModbus.GetModbusNodeById(nCurSel) ;
		if (NULL == pModbusNode) return ;

		CString strInfo(_T("")) ;
		double dbReadValue = 0.0 ;

		EnterCriticalSection(&m_csModbus) ;
		pModbusNode->pModbusBase->Modbus_ReadRegisters(m_uPlcStartAddress,dbReadValue) ;
		LeaveCriticalSection(&m_csModbus) ;

		strInfo.Format(_T("Val = %.4f"), dbReadValue);
		SetSysTipsInfo(strInfo, SYSTEM_BLUE);
	}
	catch (...)
	{
	}
}

void CManageModbusDlg::OnBnClickedBtnAdd1()
{
	try
	{
		CNewDlg newDlg ;
		newDlg.m_strStaticInfo = _T("写入数据") ;
		if (IDOK != newDlg.DoModal()) return ;

		m_vecWrite.push_back(_wtoi(newDlg.m_strInfo)) ;

		UpdataListControl2() ;
	}
	catch (...)
	{
	}
}

void CManageModbusDlg::OnBnClickedBtnEdit1()
{
	try
	{
		int nCurSel = m_listRead.GetSelectionMark() ;
		if (nCurSel < 0)
		{
			AfxMessageBox(_T("请选中编辑")) ;
			return ;
		}

		CNewDlg newDlg ;
		newDlg.m_strStaticInfo = _T("写入数据") ;
		newDlg.m_strInfo.Format(_T("%d"),m_vecWrite[nCurSel]) ;
		if (IDOK != newDlg.DoModal()) return ;

		m_vecWrite[nCurSel] = _wtoi(newDlg.m_strInfo) ;

		UpdataListControl2() ;
	}
	catch (...)
	{
	}
}

void CManageModbusDlg::OnBnClickedBtnDel1()
{
	try
	{
		int nCurSel = m_listRead.GetSelectionMark() ;
		if (nCurSel < 0)
		{
			AfxMessageBox(_T("请选中删除")) ;
			return ;
		}

		m_vecWrite.erase(std::begin(m_vecWrite) + nCurSel) ;

		UpdataListControl2() ;
	}
	catch (...)
	{
	}
}

void CManageModbusDlg::OnBnClickedBtnWrite1()
{
	USES_CONVERSION ;
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		UpdateData(TRUE) ;

		if (m_vecWrite.size() <= 0)
		{
			AfxMessageBox(_T("列表为空,不能写入")) ;
			return ;
		}

		int nCurSel = m_comboModbusList.GetCurSel() ;
		if (nCurSel < 0) return ;

		CModbusNode *pModbusNode = pDlg->m_projectData.m_mgModbus.GetModbusNodeById(nCurSel) ;
		if (NULL == pModbusNode) return ;

		EnterCriticalSection(&m_csModbus) ;
		pModbusNode->pModbusBase->Modbus_WriteRegisters(m_uPlcStartAddress,m_vecWrite) ;
		LeaveCriticalSection(&m_csModbus) ;
	}
	catch (...)
	{
	}
}

void CManageModbusDlg::OnBnClickedBtnWrite2()
{
	USES_CONVERSION ;
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		UpdateData(TRUE) ;

		int nCurSel = m_comboModbusList.GetCurSel() ;
		if (nCurSel < 0) return ;

		CModbusNode *pModbusNode = pDlg->m_projectData.m_mgModbus.GetModbusNodeById(nCurSel) ;
		if (NULL == pModbusNode) return ;

		EnterCriticalSection(&m_csModbus) ;
		pModbusNode->pModbusBase->Modbus_WriteRegisters(m_uPlcStartAddress,m_dbReadValue) ;
		LeaveCriticalSection(&m_csModbus) ;
	}
	catch (...)
	{
	}
}