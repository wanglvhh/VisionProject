// ISockDllold.cpp: implementation of the ISockDllold class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SockDll.h"
#include "MainSocket.h"
#include "ISockDllold.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ISockDllold* g_pISockDllold=NULL;//全局对象

ISockDllold::ISockDllold()
{
	m_listForSockets.Clear();
}

ISockDllold::~ISockDllold()
{
	m_listForSockets.Clear();
}

void ISockDllold::Delete()
{
	delete this;
}

int ISockDllold::CreateNewMainSocketID()
{
	if( m_listForSockets.IsEmpty() )
		return 1;
	else
	{
		LIST_NODE* pNode=NULL;
		int i=1;
		while( TRUE )
		{
			m_listForSockets.MoveToFirst();
			BOOL bExist=FALSE;
			while( m_listForSockets.GetNext(&pNode) )
			{
				if( pNode->_pSock->m_para._nID==i )
				{
					bExist=TRUE;
					break;
				}
			}
			if( !bExist ) break;
			else i++;
		}
		return i;
	}
}

BOOL ISockDllold::SearchedNode(int nMainSocketID,void** ppret,DWORD &dwPos)
{
	*ppret=0;dwPos=0;
	BOOL bSearched(FALSE);
	LIST_NODE* pNode=NULL;
	DWORD dwToget(0);
	m_listForSockets.MoveToFirst();
	while( m_listForSockets.GetNext(&pNode,&dwToget) )
	{
		if( pNode->_pSock->m_para._nID==nMainSocketID )
		{
			bSearched=TRUE;
			*ppret=(void*) pNode;
			dwPos=dwToget;
			break;
		}
	}
	return bSearched;
}
////////////////////////////////
//创建SOCKET
BOOL ISockDllold::InitSock(HWND hWnd,BOOL bServer,int& nMainSocketID,
							 LPCTSTR lpsIP,UINT nPort,BOOL bEnableMultiSameClients)
{	
	if(!::IsWindow(hWnd)) return FALSE;

	LIST_NODE* pNode=new LIST_NODE;
	if( pNode==NULL ) return FALSE;
	CMainSocket* pSock=new CMainSocket();
	if( pSock==NULL )
	{
		delete pNode;
		return FALSE;
	}
	pNode->Initialize(pSock);
	if( !m_listForSockets.InsertBeforeHead(pNode) )
	{//添加到链表头
		delete pNode;
		return FALSE;
	}
	PARA para;
	para._bServer=bServer;
	para._hWnd=hWnd;
	nMainSocketID=para._nID=CreateNewMainSocketID();
	para._nIP=CMainSocket::IPStrToInt(CString(lpsIP));
	para._nServerPort=nPort;
	if( !pNode->_pSock->Inital(para,bEnableMultiSameClients) )
	{
		m_listForSockets.RemoveHead(TRUE);
		return FALSE;
	}

	return TRUE;
}

//发送数据
BOOL ISockDllold::SendData(LPCTSTR lpsData,DWORD dwToSend,
							 int nMainSocketID,DWORD* pdwSended,int nListenSocketID)
{
	if( pdwSended ) *pdwSended=0;
	LIST_NODE* pNode=NULL;
	DWORD dwSended=0;
	DWORD dwPos(0);
	if( SearchedNode(nMainSocketID,(void**) &pNode,dwPos) )
	{
		if( !pNode->_pSock->SendData(lpsData,dwToSend,dwSended,nListenSocketID) )
			return FALSE;
		if( pdwSended ) *pdwSended=dwSended;
	}
	else
	{
		Trace(_T("SockDll.dll::ISockDllold::SendData(): SOCKET_ID is Invalid!"));
	}
	return TRUE;
}

//接收数据(最多收取dwBuffLen-1个字符)
BOOL ISockDllold::ReadData(LPTSTR lpsData,DWORD dwBuffLen,
							 int nMainSocketID,DWORD* pdwReaded,int nListenSocketID)
{
	if( pdwReaded ) *pdwReaded=0;
	LIST_NODE* pNode=NULL;
	DWORD dwReaded=0;
	DWORD dwPos(0);
	if( SearchedNode(nMainSocketID,(void**) &pNode,dwPos) )
	{
		if( !pNode->_pSock->ReadData(lpsData,dwBuffLen,dwReaded,nListenSocketID) )
			return FALSE;
		if( pdwReaded ) *pdwReaded=dwReaded;
	}
	else
	{
		Trace(_T("SockDll.dll::ISockDllold::ReadData(): SOCKET_ID is Invalid!"));
	}
	return TRUE;
}

//关闭SOCKET,if(nMainSocketID==0)则关闭所有主SOCKETS;
//else(若nListenSocketID==0,则关闭指定主SOCKET;else则关闭指定主SOCKET's_listenSocket)
BOOL ISockDllold::CloseSock(int nMainSocketID,int nListenSocketID)
{
	LIST_NODE* pNode=NULL;
	if( m_listForSockets.IsEmpty() ) return TRUE;
	if( nMainSocketID==0 )
	{//清除所有的主SOCKETS
		m_listForSockets.Clear();
		return TRUE;
	}

	DWORD dwPos(0);
	if( SearchedNode(nMainSocketID,(void**) &pNode,dwPos) )
	{
		pNode->_pSock->CloseSock(nListenSocketID);
		//整理链表
		if( (pNode->_pSock->m_para._bServer && nListenSocketID==0) || 
			!pNode->_pSock->m_para._bServer )
		{//清除主SOCKET
			m_listForSockets.RemoveAt(dwPos,TRUE);
		}
	}
	else
	{
		Trace(_T("SockDll.dll::ISockDllold::CloseSock(): SOCKET_ID is Invalid!"));
	}
	return TRUE;
}

BOOL ISockDllold::GetSocketIP(int nMainSocketID,int nListenSocketID,DWORD &dwMainSocketIP, DWORD &dwListenSocketIP)
{
	BOOL bret(FALSE);
	if( nMainSocketID==0 || m_listForSockets.IsEmpty() )
		return bret;
	LIST_NODE* pNode=NULL;
	BOOL bMatched=FALSE;
	m_listForSockets.MoveToFirst();
	while( m_listForSockets.GetNext(&pNode) )
	{
		if( pNode->_pSock->m_para._nID==nMainSocketID )
		{
			bMatched=TRUE;
			break;
		}
	}
	if( !bMatched ) return bret;
	if( pNode->_pSock->m_para._bServer )
	{//server
		dwMainSocketIP=pNode->_pSock->m_para._nIP;
		bret=pNode->_pSock->GetListenSocketIP(nListenSocketID,dwListenSocketIP);
	}
	else
	{
		dwListenSocketIP=0;
		dwMainSocketIP=pNode->_pSock->m_para._nIP;
		bret=TRUE;
	}
	//////////////////
	return bret;
}
