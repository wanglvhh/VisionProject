// MainDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "VisionCommRead.h"
#include "MainDlg.h"
#include "afxdialogex.h"

// CMainDlg 对话框

IMPLEMENT_DYNAMIC(CMainDlg, CDialogEx)

CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMainDlg::IDD, pParent)
{
	InitializeCriticalSection(&m_csComm);
	m_strCommInfo = _T("") ;
	m_eCommCloseThread = CreateEventW(NULL,TRUE,FALSE,NULL);
	ResetEvent(m_eCommCloseThread);
	m_eCommContinueThread = CreateEventW(NULL,TRUE,FALSE,NULL);
	ResetEvent(m_eCommContinueThread);
}

CMainDlg::~CMainDlg()
{
	//删除临界区
	DeleteCriticalSection(&m_csComm) ;
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_PARA, m_tabPara);
	DDX_Control(pDX, IDC_BTN_RUN, m_btnRun);
	DDX_Control(pDX, IDC_BTN_RUNCYCLE, m_btnRunCycle);
	DDX_Control(pDX, IDC_BTN_LOAD, m_btnLoad);
	DDX_Control(pDX, IDC_BTN_SAVE, m_btnSave);
	DDX_Control(pDX, IDC_BTN_CLOSE, m_btnClose);
	DDX_Control(pDX, IDC_STATIC_INFO, m_labelInfo);
}

BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_RUN, IDC_BTN_CLOSE, OnButtonClicked)
END_MESSAGE_MAP()

// CMainDlg 消息处理程序

BOOL CMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitAllControl() ;

	UpdateAllControl() ;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CMainDlg::InitAllControl()
{
	try
	{
		//初始化BtnControl
		InitBtnControl() ;
		//初始化TabControl
		InitTabControl() ;
		//初始化Label
		InitLabelControl() ;

		//更新AllControl
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

void CMainDlg::InitLabelControl()
{
	try
	{
		m_labelInfo.SetAlignTextCM();
		m_labelInfo.SetColorBkg(255,0,0,0);
		m_labelInfo.SetColorBorder(255,0,0,0);
		m_labelInfo.SetColorText(255,RGB(0,255,0)) ;
	}
	catch (...)
	{
	}
}

void CMainDlg::InitTabControl()
{
	try
	{
		m_tabPara.InsertItem(0,_T("通信参数")) ;

		CRect rc ;
		m_tabPara.GetClientRect(&rc) ;

		m_para1Dlg.Create(CPara1Dlg::IDD,&m_tabPara) ;
		m_para1Dlg.SetWindowPos(NULL,0,20,rc.right,rc.bottom,SWP_SHOWWINDOW) ;
		m_para1Dlg.ShowWindow(SW_SHOW) ;
	}
	catch (...)
	{
	}
}

void CMainDlg::UpdateAllControl()
{
	try
	{
		UpdateData(TRUE) ;

		m_labelInfo.SetText(m_strCommInfo) ;

		UpdateData(FALSE) ;
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
		ASSERT_POINT(m_pCommunicationNode) ;

		string strRev("") ;
		if(E_COMM_OK != m_pCommunicationNode->pCommunicationBase->Comm_RevData(strRev))
			return ;

		CString strInfo(strRev.c_str()) ;
		m_para1Dlg.SetSysTipsInfo(strInfo,SYSTEM_BLUE) ;
	}
	catch (...)
	{
	}
}

void CMainDlg::BtnRunCycle()
{
	try
	{
		ASSERT_POINT(m_pCommunicationNode) ;

		CString strCommRet(_T("")) ;
		GetDlgItem(IDC_BTN_RUNCYCLE)->GetWindowText(strCommRet) ;
		if ( _T("自动") == strCommRet)
		{
			//开启连续获取
			//所有事件复位
			ResetEvent(m_eCommCloseThread);
			ResetEvent(m_eCommContinueThread);
			//开启线程
			_beginthreadex(NULL,0,CommunicationThread,this,0,&m_dwCommId) ;
			//开启采集事件
			Sleep(100) ;

			EnterCriticalSection(&m_csComm) ;
			SetEvent(m_eCommContinueThread) ;
			LeaveCriticalSection(&m_csComm) ;
			GetDlgItem(IDC_BTN_RUNCYCLE)->SetWindowText(_T("停止")) ;

			//所有 按钮禁用
			GetDlgItem(IDC_BTN_RUN)->EnableWindow(FALSE) ;
			GetDlgItem(IDC_BTN_LOAD)->EnableWindow(FALSE) ;
			GetDlgItem(IDC_BTN_SAVE)->EnableWindow(FALSE) ;
			GetDlgItem(IDC_BTN_CLOSE)->EnableWindow(FALSE) ;
		}
		else if (_T("停止") == strCommRet)
		{
			//停止连续获取
			EnterCriticalSection(&m_csComm) ;
			SetEvent(m_eCommCloseThread) ;
			LeaveCriticalSection(&m_csComm) ;
			Sleep(100) ;

			GetDlgItem(IDC_BTN_RUNCYCLE)->SetWindowText(_T("自动")) ;

			//所有按钮启用
			GetDlgItem(IDC_BTN_RUN)->EnableWindow(TRUE) ;
			GetDlgItem(IDC_BTN_LOAD)->EnableWindow(TRUE) ;
			GetDlgItem(IDC_BTN_SAVE)->EnableWindow(TRUE) ;
			GetDlgItem(IDC_BTN_CLOSE)->EnableWindow(TRUE) ;
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

		//开始反序列化
		HTuple hFileHandle,hSerializedItemHandle ;
		try
		{
			HTuple hReadTuple ;
			OpenFile(W2A(strLoadPath),"input_binary",&hFileHandle) ;
			FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
			DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
			CloseFile(hFileHandle) ;

			if (0 != (HTuple(hReadTuple[0])!=HTuple("VisionSystemCommunicationRead")))
			{
				AfxMessageBox(_T("加载配置文件格式错误")) ;
				return ;
			}

			m_para1Dlg.m_dbWaitTime = hReadTuple[1].D() ;
			m_para1Dlg.UpdateAllControl() ;
		}
		catch (...)
		{
			AfxMessageBox(_T("加载配置文件格式错误")) ;
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

		if (IDOK != AfxMessageBox(_T("保存配置文件?"),MB_OKCANCEL))
			return ;

		HTuple hSaveTuple;
		hSaveTuple[0] = "VisionSystemCommunicationRead" ;
		hSaveTuple[1] = m_para1Dlg.m_dbWaitTime ;

		//开始序列化
		HTuple hFileHandle,hSerializedItemHandle ;
		OpenFile(W2A(m_strSavePath),"output_binary",&hFileHandle) ;
		SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
		FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;
		CloseFile(hFileHandle) ;

		AfxMessageBox(_T("保存Ok")) ;

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

unsigned int WINAPI CMainDlg::CommunicationThread(LPVOID lparam)

{
	try
	{
		CMainDlg *pComm = (CMainDlg*)lparam;

		HObject hImage ;
		HANDLE  eventHandle[2];

		eventHandle[0] =(*pComm).m_eCommCloseThread;
		eventHandle[1] =(*pComm).m_eCommContinueThread;

		OutputDebugString(_T("Function(CommRead_Thread) Start")) ;

		while(WAIT_OBJECT_0 != WaitForSingleObject(pComm->m_eCommCloseThread,0))
		{
			//退出程序直接退出线程
			WaitForMultipleObjects(2,eventHandle,FALSE,INFINITE);
			if(WAIT_OBJECT_0==WaitForSingleObject(pComm->m_eCommCloseThread,0))
			{
				OutputDebugString(_T("Function(CommRead_Thread) End")) ;
				return 0;
			}

			Sleep(10) ;

			CString strReadData(_T("")) ;

			DWORD dwWaitTime = pComm->m_para1Dlg.m_dbWaitTime * 1000.0 ;
			string strRecData("") ;
			bool bRecieveRet = false ;
			DWORD dwStartTime, dwEndTime ;
			DWORD dwSpend = 0;
			dwStartTime = ::GetTickCount() ;

			while (1)
			{
				if (E_COMM_OK != pComm->m_pCommunicationNode->pCommunicationBase->Comm_RevData(strRecData))
				{
					OutputDebugString(_T("Function(CommRead_Thread) Comm RevData Err")) ;
					break ;
				}
				if (strRecData.length() > 0)
				{
					bRecieveRet = true ;
					break ;
				}

				dwEndTime = GetTickCount() ;
				dwSpend = dwEndTime - dwStartTime ;
				if (dwSpend >= dwWaitTime)
				{
					bRecieveRet = false ;
					break ;
				}

				Sleep ( 10 ) ;
				::DoEvent() ;
			}

			if (!bRecieveRet)
			{
				OutputDebugString(_T("Function(CommunicationRead_Run) Comm RevData is Empty in the limit time")) ;
				continue ;
			}

			strReadData = strRecData.c_str() ;

			pComm->m_para1Dlg.SetSysTipsInfo(strReadData,SYSTEM_BLUE) ;

			OutputDebugString(_T("Function(CommRead_Thread) Read Data")) ;
		}

		OutputDebugString(_T("Function(CommRead_Thread) End")) ;

		return 0 ;
	}
	catch (...)
	{
		return -1 ;
	}
}