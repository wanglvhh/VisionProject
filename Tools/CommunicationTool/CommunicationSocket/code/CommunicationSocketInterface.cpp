#include "StdAfx.h"
#include "CommunicationSocketInterface.h"

#pragma comment(lib,"Ws2_32.lib")

CCommunicationSocketInterface::CCommunicationSocketInterface(void)
{
	m_strData = "" ;
	m_bSocketOpen = false ;
	m_bClientConnectStatus = false ;
	m_nSocketType = -1 ;
	m_eCommCloseThread = CreateEventW(NULL,TRUE,FALSE,NULL);
	ResetEvent(m_eCommCloseThread);
}

CCommunicationSocketInterface::~CCommunicationSocketInterface(void)
{
	m_strData = "" ;
	m_bSocketOpen = false ;
	m_nSocketType = -1 ;
}

COMM_CODE CCommunicationSocketInterface::Comm_Init(string strInitInfo)
{
	m_bSocketOpen = false ;
	//strInitInfo:Format->192.168.0.1,9006,1(0`1:0:服务器，1:客户端)
	try
	{
		OutputDebugString(_T("Function(SocketComm_Init) Start")) ;

		InitializeCriticalSection(&m_csCommSocket);

		CString strInit(strInitInfo.c_str()) ,strIpAddress(_T("")),\
			strPort(_T("")),strType(_T("")) ;
		if (strInit.IsEmpty())
		{
			OutputDebugString(_T("Error:SocketComm_Init strInitInfo is Empty.")) ;
			return E_COMM_NG ;
		}
		int nFind = strInit.Find(',') ;
		if (nFind < 0)
		{
			OutputDebugString(_T("Error:SocketComm_Init strInitInfo Format is Error.")) ;
			return E_COMM_NG ;
		}
		strIpAddress = strInit.Mid(0,nFind) ;
		strInit = strInit.Mid(nFind+1,strInit.GetLength() - nFind + 1) ;

		nFind = strInit.Find(',') ;
		if (nFind < 0)
		{
			OutputDebugString(_T("Error:SocketComm_Init strInitInfo Format is Error.")) ;
			return E_COMM_NG ;
		}
		strPort = strInit.Mid(0,nFind) ;
		strInit = strInit.Mid(nFind+1,strInit.GetLength() - nFind + 1) ;

		nFind = strInit.Find(',') ;
		if (nFind >= 0)
		{
			OutputDebugString(_T("Error:SocketComm_Init strInitInfo Format is Error.")) ;
			return E_COMM_NG ;
		}
		strType = strInit ;

		if (_T("Serve") == strType) m_nSocketType = 0 ;
		else if (_T("Client") == strType) m_nSocketType = 1;

		if (m_nSocketType == 0 || m_nSocketType == 1);
		else
		{
			OutputDebugString(_T("Error:SocketComm_Init strInitInfo SocketType is Error.")) ;
			return E_COMM_NG ;
		}

		COMM_CODE eCommCode = E_COMM_THROW ;
		if (E_SOCKET_SERVER == m_nSocketType)
		{
			eCommCode = InitServer(strIpAddress,strPort,strType) ;
		}
		else if (E_SOCKET_CLIENT == m_nSocketType)
		{
			eCommCode = InitClient(strIpAddress,strPort,strType) ;
		}

		OutputDebugString(_T("Function(SocketComm_Init) End")) ;

		return eCommCode ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(SocketComm_Init) Throw")) ;
		return E_COMM_THROW ;
	}
}

COMM_CODE CCommunicationSocketInterface::Comm_Close()
{
	try
	{
		OutputDebugString(_T("Function(SocketComm_Close) Start")) ;

		//关闭线程
		SetEvent(m_eCommCloseThread) ;
		Sleep(100) ;

		//删除临界区
		DeleteCriticalSection(&m_csCommSocket) ;

		//4.关闭监听套接字
		if (m_bSocketOpen)
		{
			if (E_SOCKET_SERVER == m_nSocketType)
			{
				closesocket(m_serverSocket);
				if (m_bClientConnectStatus)
				{
					closesocket(m_clientSocket);
				}
			}
			else if (E_SOCKET_CLIENT == m_nSocketType)
			{
				closesocket(m_clientSocket);
			}
		}

		//清理winsock2的环境
		WSACleanup();

		OutputDebugString(_T("Function(SocketComm_Close) End")) ;

		return E_COMM_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(SocketComm_Close) Throw")) ;
		return E_COMM_THROW ;
	}
}

COMM_CODE CCommunicationSocketInterface::Comm_ClearData()
{
	try
	{
		OutputDebugString(_T("Function(SocketComm_ClearData) Start")) ;

		EnterCriticalSection(&m_csCommSocket) ;

		m_strData = "" ;

		LeaveCriticalSection(&m_csCommSocket) ;

		OutputDebugString(_T("Function(SocketComm_ClearData) End")) ;

		return E_COMM_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(SocketComm_ClearData) Throw")) ;
		return E_COMM_THROW ;
	}
}

COMM_CODE CCommunicationSocketInterface::Comm_RevData(string &strRevData)
{
	USES_CONVERSION ;
	try
	{
		OutputDebugString(_T("Function(SocketComm_RevData) Start")) ;

		if (E_SOCKET_SERVER == m_nSocketType)
		{
			if (!m_bClientConnectStatus) return E_COMM_NG ;
			//接收客户端信息
			char revdata[1024];
			int num = recv(m_clientSocket, revdata, 1024, 0);
			if (num <= 0)
			{
				if (num == 0)
				{
					//客户端断开
					m_bClientConnectStatus = false ;
				}
				strRevData = "" ;
				return E_COMM_NG ;
			}
			EnterCriticalSection(&m_csCommSocket) ;
			revdata[num] = '\0';
			strRevData = revdata ;
			LeaveCriticalSection(&m_csCommSocket) ;
		}
		else if (E_SOCKET_CLIENT == m_nSocketType)
		{
			//接收服务端信息
			char revdata[1024];
			EnterCriticalSection(&m_csCommSocket) ;
			int num = recv(m_clientSocket, revdata, 1024, 0);
			if (num <= 0)
			{
				strRevData = "" ;
				return E_COMM_NG ;
			}
			revdata[num] = '\0';
			strRevData = revdata ;
			LeaveCriticalSection(&m_csCommSocket) ;
		}

		OutputDebugString(_T("Function(SocketComm_RevData) End")) ;

		return E_COMM_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(SocketComm_RevData) Throw")) ;
		return E_COMM_THROW ;
	}
}

COMM_CODE CCommunicationSocketInterface::Comm_SendData(string strSendData)
{
	try
	{
		OutputDebugString(_T("Function(SocketComm_SendData) Start")) ;

		const char * sendData;
		sendData = strSendData.c_str();

		if (E_SOCKET_SERVER == m_nSocketType)
		{
			send(m_clientSocket, sendData, strlen(sendData), 0);
		}
		else if (E_SOCKET_CLIENT == m_nSocketType)
		{
			send(m_clientSocket, sendData, strlen(sendData), 0);
		}

		OutputDebugString(_T("Function(SocketComm_SendData) End")) ;

		return E_COMM_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(SocketComm_SendData) Throw")) ;
		return E_COMM_THROW ;
	}
}

COMM_CODE CCommunicationSocketInterface::InitServer(CString strIpAddress,CString strPort,CString strType)
{
	USES_CONVERSION ;
	try
	{
		OutputDebugString(_T("Function(SocketComm_InitServer) Start")) ;

		//初始化DLL
		WORD sockVersion = MAKEWORD(2, 2);
		WSADATA wsdata;
		if (WSAStartup(sockVersion, &wsdata) == INVALID_SOCKET)
		{
			OutputDebugString(_T("Error:SocketComm_InitServer WSAStartup error ") + GetLastError()) ;
			return E_COMM_NG;
		}

		//1.创建监听套接字
		m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (m_serverSocket == INVALID_SOCKET)
		{
			OutputDebugString(_T("Error:SocketComm_InitServer socket error ") + GetLastError()) ;
			return E_COMM_NG;
		}

		//2.绑定到ip与端口
		sockaddr_in  addr;
		addr.sin_family = AF_INET;
		addr.sin_addr.S_un.S_addr = INADDR_ANY;
		addr.sin_port = htons(_wtoi(strPort));
		if (bind(m_serverSocket, (SOCKADDR*)&addr, sizeof(sockaddr_in)) == SOCKET_ERROR)
		{
			OutputDebugString(_T("Error:SocketComm_InitServer bind error ") + GetLastError()) ;
			return E_COMM_NG;
		}

		//3.监听套接字
		if (listen(m_serverSocket, SOMAXCONN) == INVALID_SOCKET)
		{
			OutputDebugString(_T("Error:SocketComm_InitServer listen error ") + GetLastError()) ;
			return E_COMM_NG;
		}

		m_bSocketOpen = true ;
		//开启线程
		_beginthreadex(NULL,0,CommListenThread,this,0,&m_dwCommThreadId) ;

		OutputDebugString(_T("Function(SocketComm_InitServer) End")) ;

		return E_COMM_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(SocketComm_InitServer) Throw")) ;
		return E_COMM_THROW ;
	}
}

COMM_CODE CCommunicationSocketInterface::InitClient(CString strIpAddress,CString strPort,CString strType)
{
	USES_CONVERSION ;
	try
	{
		OutputDebugString(_T("Function(SocketComm_InitClient) Start")) ;

		WORD sockVersion = MAKEWORD(2, 2);
		//加载winsock2的环境
		WSADATA data;
		if (WSAStartup(MAKEWORD(2, 2), &data) != 0)
		{
			OutputDebugString(_T("Error:SocketComm_InitClient WSAStartup error ") + GetLastError()) ;
			return E_COMM_NG;
		}

		//1.创建流式套接字
		m_clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (m_clientSocket == INVALID_SOCKET)
		{
			OutputDebugString(_T("Error:SocketComm_InitClient Socket error ") + GetLastError()) ;
			return E_COMM_NG;
		}

		//2.连接服务器
		sockaddr_in  addr;
		addr.sin_family = AF_INET;
		addr.sin_addr.S_un.S_addr = inet_addr(W2A(strIpAddress));
		addr.sin_port = htons(_wtoi(strPort));

		if (connect(m_clientSocket, (SOCKADDR*)&addr, sizeof(sockaddr_in)) == SOCKET_ERROR)
		{
			OutputDebugString(_T("Error:SocketComm_InitClient Connect error ") + GetLastError()) ;
			return E_COMM_NG;
		}
		u_long ul = 1;
		// 使socket工作在异步模式
		ioctlsocket(m_clientSocket, FIONBIO, (u_long*)&ul);

		m_bSocketOpen = true ;
		OutputDebugString(_T("Function(SocketComm_InitClient) End")) ;

		return E_COMM_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(SocketComm_InitClient) Throw")) ;
		return E_COMM_THROW ;
	}
}

unsigned int WINAPI CCommunicationSocketInterface::CommListenThread(LPVOID lparam)
{
	try
	{
		CCommunicationSocketInterface *pCommListen = (CCommunicationSocketInterface*)lparam;

		HANDLE  eventHandle;
		eventHandle =(*pCommListen).m_eCommCloseThread;

		sockaddr_in client_sin;
		char msg[100];//存储传送的消息
		//int flag = 0;//是否已经连接上
		int len = sizeof(client_sin);
		pCommListen->m_bClientConnectStatus = false ;
		OutputDebugString(_T("Function(CommListen_Thread) Start")) ;

		while(WAIT_OBJECT_0 != WaitForSingleObject(pCommListen->m_eCommCloseThread,0))
		{
			//等待连接
			if (!pCommListen->m_bClientConnectStatus)
				pCommListen->m_clientSocket = accept(pCommListen->m_serverSocket, (sockaddr*)&client_sin, &len);
			if (pCommListen->m_clientSocket == INVALID_SOCKET){
				pCommListen->m_bClientConnectStatus = false ;
				continue;
			}
			else
			{
				u_long ul = 1;
				// 使socket工作在异步模式
				ioctlsocket(pCommListen->m_clientSocket, FIONBIO, (u_long*)&ul);
			}

		    //setsockopt(pCommListen->m_clientSocket,SOL_SOCKET,SO_KEEPALIVE,(const char*)&pCommListen->m_bClientConnectStatus,sizeof(BOOL));
			pCommListen->m_bClientConnectStatus = true ;

			/*int num = recv(pCommListen->m_clientSocket, msg, 1024, 0);
			if (num > 0)
			{
			msg[num] = '\0';
			EnterCriticalSection(&pCommListen->m_csCommSocket) ;
			pCommListen->m_strData = msg ;
			LeaveCriticalSection(&pCommListen->m_csCommSocket) ;
			}*/
		}

		OutputDebugString(_T("Function(CommListen_Thread) End")) ;

		return 0 ;
	}
	catch (...)
	{
		OutputDebugString(_T("Error:CommListen_Thread Throw")) ;
		return -1 ;
	}
}