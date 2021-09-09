// MainSocket.cpp : implementation file
//

#include "stdafx.h"
#include "SockDll.h"
#include "MainSocket.h"
#include "SockDllDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainSocket

CMainSocket::CMainSocket()
{
	m_bCreate=FALSE;
	m_bEnableMultiSameClients=FALSE;
	::ZeroMemory((void*) &m_para,sizeof(PARA));
	m_para._bServer=TRUE;
	m_listSock.RemoveAll();
	m_hWatchEvent=NULL;
}

CMainSocket::~CMainSocket()
{
	DeleteListenSock(0);//ɾ�����д���SOCK
	if( m_hWatchEvent!=NULL ){
		::CloseHandle(m_hWatchEvent);
		m_hWatchEvent=NULL;
	}
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CMainSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CMainSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CMainSocket member functions

BOOL CMainSocket::Inital(const PARA &para,const BOOL &bEnableMultiSameClients)
{
	if(m_bCreate)
	{
		CloseSock(0);
	}
	m_bEnableMultiSameClients=bEnableMultiSameClients;
	::CopyMemory((void*) &m_para,(void*) &para,sizeof(PARA));
	if( m_para._bServer )
	{//��������SOCKET
		if( Create(m_para._nServerPort) )
		{
			if( Listen() )
				m_bCreate=TRUE;
			else
			{
				Close();
				CString strDebug;
				strDebug.Format(_T("SockDll.dll::CMainSocket::Inital(Server)_FAILED!: GetLastError()=%ld\n"),GetLastError());
				::OutputDebugString(strDebug);
			}
		}
		else
		{
			CString strDebug;
			strDebug.Format(_T("SockDll.dll::CMainSocket::Inital(Server)_FAILED!: GetLastError()=%ld\n"),GetLastError());
			::OutputDebugString(strDebug);
		}
	}
	else
	{//�ͻ���SOCKET
		if( Create() )
		{//�ͻ���m_bCreate�ڱ�������OnConnect�������趨
			CString lpsIP(_T(""));
			lpsIP.Format(_T("%d.%d.%d.%d"),(BYTE) ((m_para._nIP>>24)&0x0FF),
				(BYTE) ((m_para._nIP>>16)&0x0FF),(BYTE) ((m_para._nIP>>8)&0x0FF),
				(BYTE) ((m_para._nIP>>0)&0x0FF));
			if( !Connect((LPCTSTR) lpsIP,(UINT) m_para._nServerPort) )
			{
				int nResult=GetLastError();
				if( nResult!=WSAEWOULDBLOCK )
				{
					Close();
					CString strDebug;
					strDebug.Format(_T("SockDll.dll::CMainSocket::Inital(Client): GetLastError()=%ld\n"),nResult);
					::OutputDebugString(strDebug);
				}
				else
				{//�ȴ�OnConnect��������
					MSG msg;
					if( m_hWatchEvent==NULL ) VERIFY( (m_hWatchEvent=::CreateEvent(NULL,TRUE,FALSE,NULL))!=NULL );
					else ::ResetEvent(m_hWatchEvent);
					while( ::WaitForSingleObject(m_hWatchEvent,0)!=WAIT_OBJECT_0 )
					{
						while( ::PeekMessage(&msg,NULL,0,0,PM_REMOVE) )
						{
							::TranslateMessage(&msg);
							::DispatchMessage(&msg);
						}
					}
					::CloseHandle(m_hWatchEvent);
					m_hWatchEvent=NULL;
				}
			}
			else
			{
				m_bCreate=TRUE;
			}
		}
	}

	return m_bCreate;
}

//�ر�ָ������SOCK����رտͻ���
void CMainSocket::CloseSock(const int nListenSocketID)
{
	if(!m_bCreate) return;
	if( m_para._bServer )
	{//��������
		DeleteListenSock(nListenSocketID);
		if( nListenSocketID==0 ){ Close();m_bCreate=FALSE; }
	}
	else
	{//�ͻ��˰�
		Close();
		m_bCreate = FALSE;
	}
}

//nListenSocketIDΪ��ʱ�ر����еĴ���
void CMainSocket::DeleteListenSock(const int nListenSocketID)
{
	if( !m_para._bServer ) return;

	CListenSocket* pListenSocket=NULL;
	POSITION pos, posPrev;
	pos = posPrev = m_listSock.GetHeadPosition();
	while(pos)
	{
		pListenSocket = (CListenSocket*)m_listSock.GetNext(pos);
		ASSERT(pListenSocket);

		if(nListenSocketID==0)
		{//ɾ�����д���
			delete pListenSocket;
			continue;
		}
		if( nListenSocketID==pListenSocket->m_nID )	
		{//ɾ��ָ������
			delete pListenSocket;
			m_listSock.RemoveAt(posPrev);
			break;
		}
		posPrev = pos;
	}

	if( nListenSocketID==0 )
		m_listSock.RemoveAll();
}

BOOL CMainSocket::SendData(LPCTSTR lpsData,DWORD dwToSend,
						   DWORD& dwSended,int nListenSocketID)
{
	dwSended=0;
	if(!m_bCreate) return FALSE;
	if( dwToSend>SOCKET_BUFSIZE ) dwToSend=SOCKET_BUFSIZE;
	if( dwToSend<=0 ) return TRUE;
	if( m_para._bServer )
	{//�������˷���
		CListenSocket* pListenSock;
		POSITION pos = m_listSock.GetHeadPosition();
		while(pos)
		{
			pListenSock = (CListenSocket *) m_listSock.GetNext(pos);
			ASSERT(pListenSock);
			if( pListenSock->m_nID==nListenSocketID )
				if( (dwSended=pListenSock->Send(lpsData,dwToSend))==SOCKET_ERROR )
					return FALSE;
				else
				{
					return TRUE;
				}
		}
	}
	else 
	{//�ͻ��˷���
		if( (dwSended=Send(lpsData,dwToSend))==SOCKET_ERROR ) 
			return FALSE;
		else
		{
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CMainSocket::ReadData(LPTSTR lpsData,DWORD dwBuffLen,
						   DWORD& dwReaded,int nListenSocketID)
{
	dwReaded=0;
	if( !m_bCreate || dwBuffLen<=0 ) return FALSE;
	if( dwBuffLen>SOCKET_BUFSIZE ) dwBuffLen=SOCKET_BUFSIZE;
	if( m_para._bServer)
	{//�������˶�ȡ
		CListenSocket* pListenSock=NULL;
		POSITION pos=m_listSock.GetHeadPosition();
		while( pos )
		{
			pListenSock = (CListenSocket *) m_listSock.GetNext(pos);
			ASSERT(pListenSock);
			if( pListenSock->m_nID==nListenSocketID )
			{
				if( (dwReaded=pListenSock->Receive(lpsData,dwBuffLen-1))==SOCKET_ERROR )
				{
					return FALSE;
				}
				else
				{
					lpsData[dwBuffLen-1]=0;
					lpsData[dwReaded]=0;
					return TRUE;
				}
			}
		}
	}
	else
	{//�ͻ��˶�ȡ
		if( (dwReaded=Receive(lpsData,dwBuffLen-1))==SOCKET_ERROR )
		{
			return FALSE;
		}
		else
		{
			lpsData[dwBuffLen-1]=0;
			lpsData[dwReaded]=0;
			return TRUE;
		}
	}
	/////////
	return FALSE;
}

//////////////////////////////////////////////////////////////
//���������ò���

//Windows�ڲ���Ϣ�����յ��ͻ��˵���������
void CMainSocket::OnAccept(int nErrorCode) 
{
	if(nErrorCode) return;
	CListenSocket* pSockListen = new CListenSocket(this);

	if( Accept(*pSockListen) )
		AcceptNewClient(pSockListen);
	else
		delete pSockListen;
	
	CAsyncSocket::OnAccept(nErrorCode);
}

//�µĿͻ������������ж�IP���Ϸ������
void CMainSocket::AcceptNewClient(CListenSocket *pListenSocket)
{
	if( !pListenSocket ) return;
	
	//����ͬһ���ͻ����Ĳ�ͬʵ��
	if( !m_bEnableMultiSameClients )
	{//�ж��Ƿ�����ͬ��IP����
		CListenSocket *pExistSocket=NULL;
		POSITION pos = m_listSock.GetHeadPosition();
		while( pos )
		{
			pExistSocket = (CListenSocket*) m_listSock.GetNext(pos);
			if( pExistSocket )
				if( pExistSocket->GetPeerIP()==pListenSocket->GetPeerIP() )
				{
					delete pListenSocket;
					return;
				}
		}
	}

	pListenSocket->m_nID=CreateNewListenID();
	m_listSock.AddTail(pListenSocket);
	SOCK_PARA sockpara;
	sockpara.SetPara(m_para._nID,(WORD) IDWM_SOCKET_ACCEPT,(WORD) 0,(WORD) pListenSocket->m_nID);
	::g_pISockDllold->NotifyParent(sockpara);//֪ͨ������
}

//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//�ͻ��˵��ò���

void CMainSocket::OnReceive(int nErrorCode) 
{
	if( m_para._bServer ) return;
	SOCK_PARA sockpara;
	sockpara.SetPara(m_para._nID,(WORD) IDWM_SOCKET_RECEIVE,(WORD) 0,(WORD) 0);
	::g_pISockDllold->NotifyParent(sockpara);//֪ͨ������
	
	CAsyncSocket::OnReceive(nErrorCode);
}

void CMainSocket::OnClose(int nErrorCode) 
{
	SOCK_PARA sockpara;
	sockpara.SetPara(m_para._nID,(WORD) IDWM_SOCKET_CLOSE,(WORD) 0,(WORD) 0);
	::g_pISockDllold->NotifyParent(sockpara);//֪ͨ������
	
	CAsyncSocket::OnClose(nErrorCode);
}

//////////////////////////////////////////////////////////////

DWORD CMainSocket::IPStrToInt(CString strIP)
{
#ifdef _UNICODE
	USES_CONVERSION;
	DWORD dwIP = inet_addr(W2A(strIP));
#else
	DWORD dwIP=::inet_addr((char*) (LPCTSTR) strIP);
#endif
	
	DWORD dwRet=::ntohl(dwIP);
	return dwRet;
}

LIST_NODE::LIST_NODE()
{
	Trace(_T("SockDll.dll::LIST_NODE::LIST_NODE()!"));
	::ZeroMemory((void*) this,sizeof(LIST_NODE));
}

LIST_NODE::~LIST_NODE()
{
	Trace(_T("SockDll.dll::LIST_NODE::~LIST_NODE()!"));
	if( _pSock )
		delete _pSock;
}

void LIST_NODE::Initialize(CMainSocket *pSock)
{
	ASSERT( pSock!=NULL );

	_pSock=pSock;
}

//����һ�µ�ListenSocket's_ID
int CMainSocket::CreateNewListenID()
{
	ASSERT( m_para._bServer==TRUE );
	
	int nRetID(1);
	while( TRUE )
	{
		CListenSocket *pSocket=NULL;
		POSITION pos = m_listSock.GetHeadPosition();
		BOOL bExist(FALSE);
		while(pos)
		{
			pSocket = (CListenSocket*) m_listSock.GetNext(pos);
			if(pSocket)
			{
				if( pSocket->m_nID==nRetID )
				{
					bExist=TRUE;
					break;
				}
			}
		}
		if( !bExist ) break;
		else nRetID++;
	}
	return nRetID;
}

BOOL CMainSocket::GetListenSocketIP(int nListenSocketID, DWORD &dwRetIP)
{
	dwRetIP=0;
	if( nListenSocketID<=0 || m_para._bServer==FALSE ||
		m_listSock.IsEmpty() )
		return FALSE;
	POSITION pos=m_listSock.GetHeadPosition();
	CListenSocket* pSocket=NULL;
	BOOL bFound(FALSE);
	while( pos )
	{
		pSocket=(CListenSocket*) m_listSock.GetNext(pos);
		if( pSocket->m_nID==nListenSocketID )
		{//matched
			dwRetIP=pSocket->GetPeerIP();
			bFound=TRUE;
			break;
		}
	}
	return bFound;
}

//��������
void CMainSocket::SetPara(const PARA &para)
{
	::CopyMemory((void*) &m_para,(void*) &para,sizeof(PARA));
}

void CMainSocket::OnConnect(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	CAsyncSocket::OnConnect(nErrorCode);
	if( nErrorCode==0 ) m_bCreate=TRUE;
	else {
		m_bCreate=FALSE;
		Close();
		CString strDebug;
		strDebug.Format(_T("SockDll.dll::CMainSocket::Inital(OnConnect(Client)): GetLastError()=%ld\n"),nErrorCode);
		::OutputDebugString(strDebug);
	}
	if( m_hWatchEvent!=NULL ) ::SetEvent(m_hWatchEvent);
}
