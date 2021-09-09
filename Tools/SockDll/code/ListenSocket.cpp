// ListenSocket.cpp : implementation file
//

#include "stdafx.h"
#include "SockDll.h"
#include "ListenSocket.h"
#include "SockDllDefine.h"
#include "MainSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListenSocket

CListenSocket::CListenSocket(CAsyncSocket* pSockParent)
{
	ASSERT( pSockParent!=NULL );
	m_pSockParent=pSockParent;
	m_nID=0;
}

CListenSocket::~CListenSocket()
{
}

// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CListenSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CListenSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CListenSocket member functions

DWORD CListenSocket::GetPeerIP()
{
	CString strIP(_T(""));		
	DWORD nIP(0);
	UINT nPort(0);
	GetPeerName(strIP,nPort);
	nIP=CMainSocket::IPStrToInt(strIP);
	return nIP;
}

void CListenSocket::OnReceive(int nErrorCode) 
{
	ASSERT( m_pSockParent!=NULL );
	SOCK_PARA sockpara;
	CMainSocket* psock=static_cast<CMainSocket*>(m_pSockParent);
	sockpara.SetPara(psock->m_para._nID,(WORD) IDWM_SOCKET_RECEIVE,(WORD) 0,(WORD) m_nID);
	::g_pISockDllold->NotifyParent(sockpara);
	
	CAsyncSocket::OnReceive(nErrorCode);
}

void CListenSocket::OnClose(int nErrorCode) 
{
	ASSERT( m_pSockParent!=NULL );
	SOCK_PARA sockpara;
	CMainSocket* psock=static_cast<CMainSocket*>(m_pSockParent);
	sockpara.SetPara(psock->m_para._nID,(WORD) IDWM_SOCKET_CLOSE,(WORD) 0,(WORD) m_nID);
	::g_pISockDllold->NotifyParent(sockpara);
	
	CAsyncSocket::OnClose(nErrorCode);
}
