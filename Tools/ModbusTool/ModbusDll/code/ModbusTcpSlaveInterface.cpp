#include "StdAfx.h"
#include "ModbusTcpSlaveInterface.h"

CModbusTcpSlaveInterface::CModbusTcpSlaveInterface(void)
{
	::InitializeCriticalSection(&m_Critical);
	m_pModbusTcpSlaveBase = NULL ;
	m_bInitOk = false ;
	m_dllModbusTcpSlaveIm.DllCreateInterface((int)E_TOOL_MODBUS_TCPSLAVE,(void **)&m_pModbusTcpSlaveBase) ;
	if (m_pModbusTcpSlaveBase)
		m_bInitOk = true ;
}

CModbusTcpSlaveInterface::~CModbusTcpSlaveInterface(void)
{
	::DeleteCriticalSection(&m_Critical) ;
}

MODBUS_CODE CModbusTcpSlaveInterface:: Modbus_Init(string strInitInfo)
{
	try
	{
		OutputDebugString(_T("Function(TcpSlaveModbus_Init) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_MODBUS_NG ;

		OutputDebugString(_T("Function(TcpSlaveModbus_Init) End")) ;

		return m_pModbusTcpSlaveBase->Modbus_Init(strInitInfo) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(TcpSlaveModbus_Init) Throw")) ;

		return E_MODBUS_THROW ;
	}
}

MODBUS_CODE CModbusTcpSlaveInterface:: Modbus_Release()
{
	try
	{
		OutputDebugString(_T("Function(TcpSlaveModbus_Release) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_MODBUS_NG ;

		if (m_pModbusTcpSlaveBase)
		{
			delete m_pModbusTcpSlaveBase ;
			m_pModbusTcpSlaveBase = NULL;
		}
		::DeleteCriticalSection(&m_Critical);

		OutputDebugString(_T("Function(TcpSlaveModbus_Release) End")) ;

		return E_MODBUS_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(TcpSlaveModbus_Release) Throw")) ;

		return E_MODBUS_THROW ;
	}
}

MODBUS_CODE CModbusTcpSlaveInterface:: Modbus_Close()
{
	try
	{
		OutputDebugString(_T("Function(TcpSlaveModbus_Close) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_MODBUS_NG ;

		OutputDebugString(_T("Function(TcpSlaveModbus_Close) End")) ;

		return m_pModbusTcpSlaveBase->Modbus_Close() ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(TcpSlaveModbus_Close) Throw")) ;

		return E_MODBUS_THROW ;
	}
}

MODBUS_CODE CModbusTcpSlaveInterface:: Modbus_ReadRegisters(const unsigned int uStartAddress,const unsigned int uReadNum,vector<short> &vecReadValue)
{
	try
	{
		OutputDebugString(_T("Function(TcpSlaveModbus_ReadRegisters) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_MODBUS_NG ;

		OutputDebugString(_T("Function(TcpSlaveModbus_ReadRegisters) End")) ;

		return m_pModbusTcpSlaveBase->Modbus_ReadRegisters(uStartAddress,uReadNum,vecReadValue) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(TcpSlaveModbus_ReadRegisters) Throw")) ;

		return E_MODBUS_THROW ;
	}
}

MODBUS_CODE CModbusTcpSlaveInterface:: Modbus_WriteRegisters(const unsigned int uStartAddress,vector<short> vecWriteValue)
{
	try
	{
		OutputDebugString(_T("Function(TcpSlaveModbus_WriteRegisters) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_MODBUS_NG ;

		OutputDebugString(_T("Function(TcpSlaveModbus_WriteRegisters) End")) ;

		return m_pModbusTcpSlaveBase->Modbus_WriteRegisters(uStartAddress,vecWriteValue) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(TcpSlaveModbus_WriteRegisters) Throw")) ;

		return E_MODBUS_THROW ;
	}
}

MODBUS_CODE CModbusTcpSlaveInterface:: Modbus_ReadRegisters(const unsigned int uStartAddress,double &dbReadValue)
{
	try
	{
		OutputDebugString(_T("Function(TcpSlaveModbus_ReadRegisters) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_MODBUS_NG ;

		OutputDebugString(_T("Function(TcpSlaveModbus_ReadRegisters) End")) ;

		return m_pModbusTcpSlaveBase->Modbus_ReadRegisters(uStartAddress,dbReadValue) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(TcpSlaveModbus_ReadRegisters) Throw")) ;

		return E_MODBUS_THROW ;
	}
}

MODBUS_CODE CModbusTcpSlaveInterface:: Modbus_WriteRegisters(const unsigned int uStartAddress,double dbWriteValue)
{
	try
	{
		OutputDebugString(_T("Function(TcpSlaveModbus_WriteRegisters) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_MODBUS_NG ;

		OutputDebugString(_T("Function(TcpSlaveModbus_WriteRegisters) End")) ;

		return m_pModbusTcpSlaveBase->Modbus_WriteRegisters(uStartAddress,dbWriteValue) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(TcpSlaveModbus_WriteRegisters) Throw")) ;

		return E_MODBUS_THROW ;
	}
}