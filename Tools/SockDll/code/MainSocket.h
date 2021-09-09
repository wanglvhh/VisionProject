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
	BOOL _bServer;//����������OR�ͻ���
	DWORD _nServerPort;//��ʾ�����ܶ˿ں�
	int _nID;//��SOCKET's_ID
	DWORD _nIP;//��ʾ��SOCKET's_IP��ַ(��������,�ɲ�Ҫ)
	HWND _hWnd;//��ʾ����SOCKET�����Ĵ��ھ��
	PARA(){::ZeroMemory((void*) this,sizeof(this));}
}PARA;

class CMainSocket : public CAsyncSocket
{
// Attributes
public:
	PARA m_para;//���ⲿ����,����ʼ��
	static DWORD IPStrToInt(CString strIP);
// Operations
public:
	CMainSocket();
	virtual ~CMainSocket();

// Overrides
public:
	void SetPara(const PARA& para);
	BOOL GetListenSocketIP(int nListenSocketID,DWORD& dwRetIP);//��ȡָ��ListenSocket's_IP
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
	HANDLE m_hWatchEvent;//����OnConnect�����ĵ���(���Կͻ���������)
	CPtrList m_listSock;//����SOCKET
	BOOL m_bCreate;//��ʾ��SOCKET�Ƿ��ѳ�ʼ��
	BOOL m_bEnableMultiSameClients;//�Ƿ�����ͬһ�ͻ�����Ϊ����ͻ�������ͬһ������
};

/***************************************************\
		ÿһ��LIST_NODE�ڵ��ʾһ�������Ĺ�����
	Ҫô��Ϊ��������Ҫô��Ϊ�ͻ���
\***************************************************/
typedef struct LIST_NODE{
public:
	CMainSocket* _pSock;//������SOCKET

	///////////////
	LIST_NODE();
	~LIST_NODE();
	void Initialize(CMainSocket* pSock);
} LIST_NODE;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINSOCKET_H__E43FC360_CA65_11D6_AAAF_00E04C3AA9CB__INCLUDED_)
