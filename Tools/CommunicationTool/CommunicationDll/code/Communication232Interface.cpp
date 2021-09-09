#include "StdAfx.h"
#include "Communication232Interface.h"

CCommunication232Interface::CCommunication232Interface(void)
{
	::InitializeCriticalSection(&m_Critical);
	m_pComm232Base = NULL ;
	m_bInitOk = false ;
	m_dllComm232Im.DllCreateInterface((int)E_TOOL_COMMUNICATION_COMM232,(void **)&m_pComm232Base) ;
	if (m_pComm232Base)
		m_bInitOk = true ;
}

CCommunication232Interface::~CCommunication232Interface(void)
{
	::DeleteCriticalSection(&m_Critical);
}

COMM_CODE CCommunication232Interface:: Comm_Init(string strInitInfo)
{
	try
	{
		OutputDebugString(_T("Function(232Comm_Init) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_COMM_NG ;

		OutputDebugString(_T("Function(232Comm_Init) End")) ;

		return m_pComm232Base->Comm_Init(strInitInfo) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(232Comm_Init) Throw")) ;

		return E_COMM_THROW ;
	}
}

COMM_CODE CCommunication232Interface:: Comm_Release()
{
	try
	{
		OutputDebugString(_T("Function(232Comm_Release) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_COMM_NG ;

		if (m_pComm232Base)
		{
			delete m_pComm232Base ;
			m_pComm232Base = NULL;
		}
		::DeleteCriticalSection(&m_Critical);

		OutputDebugString(_T("Function(232Comm_Release) End")) ;

		return E_COMM_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(232Comm_Release) Throw")) ;

		return E_COMM_THROW ;
	}
}

COMM_CODE CCommunication232Interface:: Comm_Close()
{
	try
	{
		OutputDebugString(_T("Function(232Comm_Close) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_COMM_NG ;

		OutputDebugString(_T("Function(232Comm_Close) End")) ;

		return m_pComm232Base->Comm_Close() ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(232Comm_Close) Throw")) ;

		return E_COMM_THROW ;
	}
}

COMM_CODE CCommunication232Interface:: Comm_ClearData()
{
	try
	{
		OutputDebugString(_T("Function(232Comm_ClearData) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_COMM_NG ;

		OutputDebugString(_T("Function(232Comm_ClearData) End")) ;

		return m_pComm232Base->Comm_ClearData() ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(232Comm_ClearData) Throw")) ;

		return E_COMM_THROW ;
	}
}

COMM_CODE CCommunication232Interface:: Comm_RevData(string &strRevData)
{
	try
	{
		OutputDebugString(_T("Function(232Comm_RevData) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_COMM_NG ;

		OutputDebugString(_T("Function(232Comm_RevData) End")) ;

		return m_pComm232Base->Comm_RevData(strRevData) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(232Comm_RevData) Throw")) ;

		return E_COMM_THROW ;
	}
}

COMM_CODE CCommunication232Interface:: Comm_SendData(string strSendData)
{
	try
	{
		OutputDebugString(_T("Function(232Comm_SendData) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_COMM_NG ;

		OutputDebugString(_T("Function(232Comm_SendData) End")) ;

		return m_pComm232Base->Comm_SendData(strSendData) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(232Comm_SendData) Throw")) ;

		return E_COMM_THROW ;
	}
}