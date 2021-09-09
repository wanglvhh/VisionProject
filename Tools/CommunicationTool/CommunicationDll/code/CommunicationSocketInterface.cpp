#include "StdAfx.h"
#include "CommunicationSocketInterface.h"

CCommunicationSocketInterface::CCommunicationSocketInterface(void)
{
	::InitializeCriticalSection(&m_Critical);
	m_pCommSocketBase = NULL ;
	m_bInitOk = false ;
	m_dllCommSocketIm.DllCreateInterface((int)E_TOOL_COMMUNICATION_TCPIP,(void **)&m_pCommSocketBase) ;
	if (m_pCommSocketBase)
		m_bInitOk = true ;
}

CCommunicationSocketInterface::~CCommunicationSocketInterface(void)
{
	::DeleteCriticalSection(&m_Critical);
	/*if (m_pCommSocketBase)
	{
		delete m_pCommSocketBase ;
		m_pCommSocketBase = NULL ;
	}*/
}

COMM_CODE CCommunicationSocketInterface:: Comm_Init(string strInitInfo)
{
	try
	{
		OutputDebugString(_T("Function(SocketComm_Init) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_COMM_NG ;

		OutputDebugString(_T("Function(SocketComm_Init) End")) ;

		return m_pCommSocketBase->Comm_Init(strInitInfo) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(SocketComm_Init) Throw")) ;

		return E_COMM_THROW ;
	}
}

COMM_CODE CCommunicationSocketInterface:: Comm_Release()
{
	try
	{
		OutputDebugString(_T("Function(SocketComm_Release) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_COMM_NG ;

		if (m_pCommSocketBase)
		{
			delete m_pCommSocketBase ;
			m_pCommSocketBase = NULL;
		}

		::DeleteCriticalSection(&m_Critical);

		OutputDebugString(_T("Function(SocketComm_Release) End")) ;

		return E_COMM_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(SocketComm_Release) Throw")) ;

		return E_COMM_THROW ;
	}
}

COMM_CODE CCommunicationSocketInterface:: Comm_Close()
{
	try
	{
		OutputDebugString(_T("Function(SocketComm_Close) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_COMM_NG ;

		OutputDebugString(_T("Function(SocketComm_Close) End")) ;

		return m_pCommSocketBase->Comm_Close() ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(SocketComm_Close) Throw")) ;

		return E_COMM_THROW ;
	}
}

COMM_CODE CCommunicationSocketInterface:: Comm_ClearData()
{
	try
	{
		OutputDebugString(_T("Function(SocketComm_ClearData) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_COMM_NG ;

		OutputDebugString(_T("Function(SocketComm_ClearData) End")) ;

		return m_pCommSocketBase->Comm_ClearData() ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(SocketComm_ClearData) Throw")) ;

		return E_COMM_THROW ;
	}
}

COMM_CODE CCommunicationSocketInterface:: Comm_RevData(string &strRevData)
{
	try
	{
		OutputDebugString(_T("Function(SocketComm_RevData) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_COMM_NG ;

		OutputDebugString(_T("Function(SocketComm_RevData) End")) ;

		return m_pCommSocketBase->Comm_RevData(strRevData) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(SocketComm_RevData) Throw")) ;

		return E_COMM_THROW ;
	}
}

COMM_CODE CCommunicationSocketInterface:: Comm_SendData(string strSendData)
{
	try
	{
		OutputDebugString(_T("Function(SocketComm_SendData) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_COMM_NG ;

		OutputDebugString(_T("Function(SocketComm_SendData) End")) ;

		return m_pCommSocketBase->Comm_SendData(strSendData) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(SocketComm_SendData) Throw")) ;

		return E_COMM_THROW ;
	}
}