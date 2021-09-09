#pragma once
#include<winsock2.h>
#include "Communicationsocketbase.h"

class CCommunicationSocketInterface :
	public CCommunicationSocketBase
{
public:
	CCommunicationSocketInterface(void);
	~CCommunicationSocketInterface(void);

	enum SOCKET_TYPE
	{
		E_SOCKET_SERVER = 0,
		E_SOCKET_CLIENT,
	};

	virtual COMM_CODE Comm_Init(string strInitInfo);

	virtual COMM_CODE Comm_Close() ;

	virtual COMM_CODE Comm_ClearData() ;

	virtual COMM_CODE Comm_RevData(string &strRevData)  ;

	virtual COMM_CODE Comm_SendData(string strSendData)  ;

	COMM_CODE InitServer(CString strIpAddress,CString strPort,CString strType) ;

	COMM_CODE InitClient(CString strIpAddress,CString strPort,CString strType) ;

	static unsigned int WINAPI CommListenThread(LPVOID lparam) ;
private:
	CRITICAL_SECTION          m_csCommSocket ;
	string                    m_strData ;
	bool                      m_bSocketOpen ;
	bool                      m_bClientConnectStatus ;
	int                       m_nSocketType ;
	SOCKET                    m_serverSocket ;
	SOCKET                    m_clientSocket;
	HANDLE                    m_eCommCloseThread ;
	unsigned int              m_dwCommThreadId ;
};
