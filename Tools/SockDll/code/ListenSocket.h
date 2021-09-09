#if !defined(AFX_LISTENSOCKET_H__E43FC361_CA65_11D6_AAAF_00E04C3AA9CB__INCLUDED_)
#define AFX_LISTENSOCKET_H__E43FC361_CA65_11D6_AAAF_00E04C3AA9CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListenSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CListenSocket command target

class CListenSocket : public CAsyncSocket
{
// Attributes
public:
	int m_nID;//标示本SOCKET's_ID

// Operations
public:
	CListenSocket(CAsyncSocket* pSockParent);
	virtual ~CListenSocket();

// Overrides
public:
	DWORD GetPeerIP();//获取对应SOCKET's_IP
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListenSocket)
	public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CListenSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	CAsyncSocket* m_pSockParent;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTENSOCKET_H__E43FC361_CA65_11D6_AAAF_00E04C3AA9CB__INCLUDED_)
