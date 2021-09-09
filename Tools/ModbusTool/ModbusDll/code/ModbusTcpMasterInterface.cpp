#include "StdAfx.h"
#include "ModbusTcpMasterInterface.h"

CModbusTcpMasterInterface::CModbusTcpMasterInterface(void)
{
	::InitializeCriticalSection(&m_Critical);
	m_pModbusTcpMasterBase = NULL ;
	m_bInitOk = false ;
	m_dllModbusTcpMasterIm.DllCreateInterface((int)E_TOOL_MODBUS_TCPMASTER,(void **)&m_pModbusTcpMasterBase) ;
	if (m_pModbusTcpMasterBase)
		m_bInitOk = true ;
}

CModbusTcpMasterInterface::~CModbusTcpMasterInterface(void)
{
	::DeleteCriticalSection(&m_Critical) ;
}

MODBUS_CODE CModbusTcpMasterInterface:: Modbus_Init(string strInitInfo)
{
	try
	{
		OutputDebugString(_T("Function(TcpMasterModbus_Init) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_MODBUS_NG ;

		OutputDebugString(_T("Function(TcpMasterModbus_Init) End")) ;

		return m_pModbusTcpMasterBase->Modbus_Init(strInitInfo) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(TcpMasterModbus_Init) Throw")) ;

		return E_MODBUS_THROW ;
	}
}

MODBUS_CODE CModbusTcpMasterInterface:: Modbus_Release()
{
	try
	{
		OutputDebugString(_T("Function(TcpMasterModbus_Release) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_MODBUS_NG ;

		if (m_pModbusTcpMasterBase)
		{
			delete m_pModbusTcpMasterBase ;
			m_pModbusTcpMasterBase = NULL;
		}
		::DeleteCriticalSection(&m_Critical);

		OutputDebugString(_T("Function(TcpMasterModbus_Release) End")) ;

		return E_MODBUS_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(TcpMasterModbus_Release) Throw")) ;

		return E_MODBUS_THROW ;
	}
}

MODBUS_CODE CModbusTcpMasterInterface:: Modbus_Close()
{
	try
	{
		OutputDebugString(_T("Function(TcpMasterModbus_Close) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_MODBUS_NG ;

		OutputDebugString(_T("Function(TcpMasterModbus_Close) End")) ;

		return m_pModbusTcpMasterBase->Modbus_Close() ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(TcpMasterModbus_Close) Throw")) ;

		return E_MODBUS_THROW ;
	}
}

MODBUS_CODE CModbusTcpMasterInterface:: Modbus_ReadRegisters(const unsigned int uStartAddress,const unsigned int uReadNum,vector<short> &vecReadValue)
{
	try
	{
		OutputDebugString(_T("Function(TcpMasterModbus_ReadRegisters) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_MODBUS_NG ;

		OutputDebugString(_T("Function(TcpMasterModbus_ReadRegisters) End")) ;

		return m_pModbusTcpMasterBase->Modbus_ReadRegisters(uStartAddress,uReadNum,vecReadValue) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(TcpMasterModbus_ReadRegisters) Throw")) ;

		return E_MODBUS_THROW ;
	}
}

MODBUS_CODE CModbusTcpMasterInterface:: Modbus_WriteRegisters(const unsigned int uStartAddress,vector<short> vecWriteValue)
{
	try
	{
		OutputDebugString(_T("Function(TcpMasterModbus_WriteRegisters) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_MODBUS_NG ;

		OutputDebugString(_T("Function(TcpMasterModbus_WriteRegisters) End")) ;

		return m_pModbusTcpMasterBase->Modbus_WriteRegisters(uStartAddress,vecWriteValue) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(TcpMasterModbus_WriteRegisters) Throw")) ;

		return E_MODBUS_THROW ;
	}
}

MODBUS_CODE CModbusTcpMasterInterface:: Modbus_ReadRegisters(const unsigned int uStartAddress,double &dbReadValue)
{
	try
	{
		OutputDebugString(_T("Function(TcpMasterModbus_ReadRegisters) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_MODBUS_NG ;

		OutputDebugString(_T("Function(TcpMasterModbus_ReadRegisters) End")) ;

		return m_pModbusTcpMasterBase->Modbus_ReadRegisters(uStartAddress,dbReadValue) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(TcpMasterModbus_ReadRegisters) Throw")) ;

		return E_MODBUS_THROW ;
	}
}

MODBUS_CODE CModbusTcpMasterInterface:: Modbus_WriteRegisters(const unsigned int uStartAddress,double dbWriteValue)
{
	try
	{
		OutputDebugString(_T("Function(TcpMasterModbus_WriteRegisters) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_MODBUS_NG ;

		OutputDebugString(_T("Function(TcpMasterModbus_WriteRegisters) End")) ;

		return m_pModbusTcpMasterBase->Modbus_WriteRegisters(uStartAddress,dbWriteValue) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(TcpMasterModbus_WriteRegisters) Throw")) ;

		return E_MODBUS_THROW ;
	}
}