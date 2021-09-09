#if !defined(AFX_MAINSOCKET_H__E43FC360_CA65_11D6_AAAF_00E04C3AA9CB__INCLUDED_)
#define AFX_MAINSOCKET_H__E43FC360_CA65_11D6_AAAF_00E04C3AA9CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainSocket.h : header file
//

#include "ListenSocket.h"
/////////////////////////////////////////////////////////////////////////////
// CMainSocket command target
typedef struct PARA
{
	BOOL _bServer;//表明服务器OR客户端
	DWORD _nServerPort;//标示服务功能端口号
	int _nID;//主SOCKET's_ID
	DWORD _nIP;//标示主SOCKET's_IP地址(服务器版,可不要)
	HWND _hWnd;//标示与主SOCKET关联的窗口句柄
	PARA(){::ZeroMemory((void*) this,sizeof(this));}
}PARA;

class CMainSocket : public CAsyncSocket
{
// Attributes
public:
	PARA m_para;//由外部传入,并初始化
	static DWORD IPStrToInt(CString strIP);
// Operations
public:
	CMainSocket();
	virtual ~CMainSocket();

// Overrides
public:
	void SetPara(const PARA& para);
	BOOL GetListenSocketIP(int nListenSocketID,DWORD& dwRetIP);//获取指定ListenSocket's_IP
	BOOL Inital(const PARA& para,const BOOL& bEnableMultiSameClients=FALSE);
	BOOL ReadData(LPTSTR lpsData,DWORD dwBuffLen,DWORD& dwReaded,int nListenSocketID=0);
	BOOL SendData(LPCTSTR lpsData,DWORD dwToSend,DWORD& dwSended,int nListenSocketID=0);
	void CloseSock(const int nListenSocketID);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainSocket)
	public:
	virtual void OnAccept(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CMainSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
private:
	int CreateNewListenID();
	void DeleteListenSock(const int nListenSocketID);
	void AcceptNewClient(CListenSocket *pListenSocket);
	////////////////
	HANDLE m_hWatchEvent;//监视OnConnect函数的调用(仅对客户端有意义)
	CPtrList m_listSock;//代理SOCKET
	BOOL m_bCreate;//标示本SOCKET是否已初始化
	BOOL m_bEnableMultiSameClients;//是否允许同一客户机作为多个客户端连到同一服务器
};

/***************************************************\
		每一个LIST_NODE节点标示一个独立的功能项
	要么作为服务器，要么作为客户端
\***************************************************/
typedef struct LIST_NODE{
public:
	CMainSocket* _pSock;//主代理SOCKET

	///////////////
	LIST_NODE();
	~LIST_NODE();
	void Initialize(CMainSocket* pSock);
} LIST_NODE;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINSOCKET_H__E43FC360_CA65_11D6_AAAF_00E04C3AA9CB__INCLUDED_)
