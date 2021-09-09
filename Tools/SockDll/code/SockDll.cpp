// SockDll.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "SockDll.h"
#include "mainSocket.h"

#ifndef SOCKDLL_EXPORT
	#define SOCKDLL_EXPORT
	#include "SockDllDefine.h"
#endif


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CSockDllApp

BEGIN_MESSAGE_MAP(CSockDllApp, CWinApp)
	//{{AFX_MSG_MAP(CSockDllApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSockDllApp construction

CSockDllApp::CSockDllApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSockDllApp object

CSockDllApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSockDllApp initialization

BOOL CSockDllApp::InitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	if ( !::AfxSocketInit() )
	{//初始化SOCKET
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}
	::g_pISockDllold=new ISockDllold();
	Trace(_T("SockDll.dll::Load SockDll.dll!"));
	return CWinApp::InitInstance();
}

int CSockDllApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	if( ::g_pISockDllold )
	{
		::g_pISockDllold->Delete();
		::g_pISockDllold=NULL;
	}
	::AfxSocketTerm();
	Trace(_T("SockDll.dll::Unload SockDll.dll!"));
	return CWinApp::ExitInstance();
}

LRESULT ISockDllold::NotifyParent(SOCK_PARA &SockPara,BOOL bySend)
{
	LRESULT ret(0);
	if( m_listForSockets.IsEmpty() ) return ret;
	LIST_NODE* pNode=NULL;
	m_listForSockets.MoveToFirst();
	BOOL bFound(FALSE);
	while( m_listForSockets.GetNext(&pNode) )
	{
		if( pNode->_pSock->m_para._nID==SockPara._wpara._hiPara )
		{
			bFound=TRUE;
			break;
		}
	}
	if( bFound )
	{
		if( bySend )
		{
			ret=::SendMessage(pNode->_pSock->m_para._hWnd,WM_SOCKETS,
					SockPara.GetWpara(),SockPara.GetLpara());
		}
		else
		{
			ret=::PostMessage(pNode->_pSock->m_para._hWnd,WM_SOCKETS,
					SockPara.GetWpara(),SockPara.GetLpara());
		}
	}
	return ret;
}

/////////////////////////////////////////////////////////////////////
//
//				输入、输出接口
//
////////////////////////////////////////////////////////////////////
/////////////////////


//初始化扩展SOCK
SOCKDLL_API BOOL __stdcall InitSockEx(HWND hWnd,BOOL bServer,int& nMainSocketID,
							LPCTSTR lpsIP,UINT nPort,BOOL bEnableMultiSameClients)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	return ::g_pISockDllold->InitSock(hWnd,bServer,nMainSocketID,lpsIP,nPort,bEnableMultiSameClients);
}

//扩展读数据函数
SOCKDLL_API BOOL __stdcall ReadDataEx(LPTSTR lpsData,DWORD dwBuffLen,int nMainSocketID,
									  DWORD* pdwReaded,int nListenSocketID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	return ::g_pISockDllold->ReadData(lpsData,dwBuffLen,nMainSocketID,pdwReaded,nListenSocketID);
}

//扩展读数据函数
SOCKDLL_API BOOL __stdcall SendDataEx(LPCTSTR lpsData,DWORD dwToSend,int nMainSocketID,
									  DWORD* pdwSended,int nListenSocketID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	return ::g_pISockDllold->SendData(lpsData,dwToSend,nMainSocketID,pdwSended,nListenSocketID);
}

//扩展读数据函数
SOCKDLL_API BOOL __stdcall CloseSockEx(int nMainSocketID,int nListenSocketID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	return ::g_pISockDllold->CloseSock(nMainSocketID,nListenSocketID);
}

SOCKDLL_API BOOL __stdcall GetAssociatsSocketIP(int nMainSocketID,int nListenSocketID,DWORD *pdwMainSocketIP,DWORD *pdwListenSocketIP)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	DWORD dwMainSocketIP(0),dwListenSocketIP(0);
	BOOL bret=::g_pISockDllold->GetSocketIP(nMainSocketID,nListenSocketID,dwMainSocketIP,dwListenSocketIP);
	if( pdwMainSocketIP ) *pdwMainSocketIP=dwMainSocketIP;
	if( pdwListenSocketIP ) *pdwListenSocketIP=dwListenSocketIP;
	return bret;
}
