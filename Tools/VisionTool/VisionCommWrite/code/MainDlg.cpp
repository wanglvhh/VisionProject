// MainDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "VisionCommWrite.h"
#include "MainDlg.h"
#include "afxdialogex.h"

// CMainDlg 对话框

IMPLEMENT_DYNAMIC(CMainDlg, CDialogEx)

CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMainDlg::IDD, pParent)
{
	m_strCommInfo = _T("") ;
}

CMainDlg::~CMainDlg()
{
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
	USES_CONVERSION ;
	try
	{
		ASSERT_POINT(m_pCommunicationNode) ;

		m_pCommunicationNode->pCommunicationBase->Comm_SendData(W2A(m_para1Dlg.m_strSendData)) ;
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

			if (0 != (HTuple(hReadTuple[0])!=HTuple("VisionSystemCommunicationWrite")))
			{
				AfxMessageBox(_T("加载配置文件格式错误")) ;
				return ;
			}

			m_para1Dlg.m_strSendData = hReadTuple[1].S() ;
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
		hSaveTuple[0] = "VisionSystemCommunicationWrite" ;
		hSaveTuple[1] = W2A(m_para1Dlg.m_strSendData) ;

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