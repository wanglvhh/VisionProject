#include "StdAfx.h"
#include "ModbusRtuSlaveInterface.h"

CModbusRtuSlaveInterface::CModbusRtuSlaveInterface(void)
{
	::InitializeCriticalSection(&m_Critical);
	m_pModbusRtuSlaveBase = NULL ;
	m_bInitOk = false ;
	m_dllModbusRtuSlaveIm.DllCreateInterface((int)E_TOOL_MODBUS_RTUSLAVE,(void **)&m_pModbusRtuSlaveBase) ;
	if (m_pModbusRtuSlaveBase)
		m_bInitOk = true ;
}

CModbusRtuSlaveInterface::~CModbusRtuSlaveInterface(void)
{
	::DeleteCriticalSection(&m_Critical) ;
}

MODBUS_CODE CModbusRtuSlaveInterface:: Modbus_Init(string strInitInfo)
{
	try
	{
		OutputDebugString(_T("Function(RtuSlaveModbus_Init) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_MODBUS_NG ;

		OutputDebugString(_T("Function(RtuSlaveModbus_Init) End")) ;

		return m_pModbusRtuSlaveBase->Modbus_Init(strInitInfo) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(RtuSlaveModbus_Init) Throw")) ;

		return E_MODBUS_THROW ;
	}
}

MODBUS_CODE CModbusRtuSlaveInterface:: Modbus_Release()
{
	try
	{
		OutputDebugString(_T("Function(RtuSlaveModbus_Release) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_MODBUS_NG ;

		if (m_pModbusRtuSlaveBase)
		{
			delete m_pModbusRtuSlaveBase ;
			m_pModbusRtuSlaveBase = NULL;
		}
		::DeleteCriticalSection(&m_Critical);

		OutputDebugString(_T("Function(RtuSlaveModbus_Release) End")) ;

		return E_MODBUS_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(RtuSlaveModbus_Release) Throw")) ;

		return E_MODBUS_THROW ;
	}
}

MODBUS_CODE CModbusRtuSlaveInterface:: Modbus_Close()
{
	try
	{
		OutputDebugString(_T("Function(RtuSlaveModbus_Close) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_MODBUS_NG ;

		OutputDebugString(_T("Function(RtuSlaveModbus_Close) End")) ;

		return m_pModbusRtuSlaveBase->Modbus_Close() ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(RtuSlaveModbus_Close) Throw")) ;

		return E_MODBUS_THROW ;
	}
}

MODBUS_CODE CModbusRtuSlaveInterface:: Modbus_ReadRegisters(const unsigned int uStartAddress,const unsigned int uReadNum,vector<short> &vecReadValue)
{
	try
	{
		OutputDebugString(_T("Function(RtuSlaveModbus_ReadRegisters) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_MODBUS_NG ;

		OutputDebugString(_T("Function(RtuSlaveModbus_ReadRegisters) End")) ;

		return m_pModbusRtuSlaveBase->Modbus_ReadRegisters(uStartAddress,uReadNum,vecReadValue) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(RtuSlaveModbus_ReadRegisters) Throw")) ;

		return E_MODBUS_THROW ;
	}
}

MODBUS_CODE CModbusRtuSlaveInterface:: Modbus_WriteRegisters(const unsigned int uStartAddress,vector<short> vecWriteValue)
{
	try
	{
		OutputDebugString(_T("Function(RtuSlaveModbus_WriteRegisters) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_MODBUS_NG ;

		OutputDebugString(_T("Function(RtuSlaveModbus_WriteRegisters) End")) ;

		return m_pModbusRtuSlaveBase->Modbus_WriteRegisters(uStartAddress,vecWriteValue) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(RtuSlaveModbus_WriteRegisters) Throw")) ;

		return E_MODBUS_THROW ;
	}
}

MODBUS_CODE CModbusRtuSlaveInterface:: Modbus_ReadRegisters(const unsigned int uStartAddress,double &dbReadValue)
{
	try
	{
		OutputDebugString(_T("Function(RtuSlaveModbus_ReadRegisters) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_MODBUS_NG ;

		OutputDebugString(_T("Function(RtuSlaveModbus_ReadRegisters) End")) ;

		return m_pModbusRtuSlaveBase->Modbus_ReadRegisters(uStartAddress,dbReadValue) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(RtuSlaveModbus_ReadRegisters) Throw")) ;

		return E_MODBUS_THROW ;
	}
}

MODBUS_CODE CModbusRtuSlaveInterface:: Modbus_WriteRegisters(const unsigned int uStartAddress,double dbWriteValue)
{
	try
	{
		OutputDebugString(_T("Function(RtuSlaveModbus_WriteRegisters) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_MODBUS_NG ;

		OutputDebugString(_T("Function(RtuSlaveModbus_WriteRegisters) End")) ;

		return m_pModbusRtuSlaveBase->Modbus_WriteRegisters(uStartAddress,dbWriteValue) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(RtuSlaveModbus_WriteRegisters) Throw")) ;

		return E_MODBUS_THROW ;
	}
}