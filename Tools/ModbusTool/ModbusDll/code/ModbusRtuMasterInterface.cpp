#include "StdAfx.h"
#include "ModbusRtuMasterInterface.h"

CModbusRtuMasterInterface::CModbusRtuMasterInterface(void)
{
	::InitializeCriticalSection(&m_Critical);
	m_pModbusRtuMasterBase = NULL ;
	m_bInitOk = false ;
	m_dllModbusRtuMasterIm.DllCreateInterface((int)E_TOOL_MODBUS_RTUMASTER,(void **)&m_pModbusRtuMasterBase) ;
	if (m_pModbusRtuMasterBase)
		m_bInitOk = true ;
}

CModbusRtuMasterInterface::~CModbusRtuMasterInterface(void)
{
	::DeleteCriticalSection(&m_Critical) ;
}

MODBUS_CODE CModbusRtuMasterInterface:: Modbus_Init(string strInitInfo)
{
	try
	{
		OutputDebugString(_T("Function(RtuMasterModbus_Init) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_MODBUS_NG ;

		OutputDebugString(_T("Function(RtuMasterModbus_Init) End")) ;

		return m_pModbusRtuMasterBase->Modbus_Init(strInitInfo) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(RtuMasterModbus_Init) Throw")) ;

		return E_MODBUS_THROW ;
	}
}

MODBUS_CODE CModbusRtuMasterInterface:: Modbus_Release()
{
	try
	{
		OutputDebugString(_T("Function(RtuMasterModbus_Release) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_MODBUS_NG ;

		if (m_pModbusRtuMasterBase)
		{
			delete m_pModbusRtuMasterBase ;
			m_pModbusRtuMasterBase = NULL;
		}
		::DeleteCriticalSection(&m_Critical);

		OutputDebugString(_T("Function(RtuMasterModbus_Release) End")) ;

		return E_MODBUS_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(RtuMasterModbus_Release) Throw")) ;

		return E_MODBUS_THROW ;
	}
}

MODBUS_CODE CModbusRtuMasterInterface:: Modbus_Close()
{
	try
	{
		OutputDebugString(_T("Function(RtuMasterModbus_Close) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_MODBUS_NG ;

		OutputDebugString(_T("Function(RtuMasterModbus_Close) End")) ;

		return m_pModbusRtuMasterBase->Modbus_Close() ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(RtuMasterModbus_Close) Throw")) ;

		return E_MODBUS_THROW ;
	}
}

MODBUS_CODE CModbusRtuMasterInterface:: Modbus_ReadRegisters(const unsigned int uStartAddress,const unsigned int uReadNum,vector<short> &vecReadValue)
{
	try
	{
		OutputDebugString(_T("Function(RtuMasterModbus_ReadRegisters) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_MODBUS_NG ;

		OutputDebugString(_T("Function(RtuMasterModbus_ReadRegisters) End")) ;

		return m_pModbusRtuMasterBase->Modbus_ReadRegisters(uStartAddress,uReadNum,vecReadValue) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(RtuMasterModbus_ReadRegisters) Throw")) ;

		return E_MODBUS_THROW ;
	}
}

MODBUS_CODE CModbusRtuMasterInterface:: Modbus_WriteRegisters(const unsigned int uStartAddress,vector<short> vecWriteValue)
{
	try
	{
		OutputDebugString(_T("Function(RtuMasterModbus_WriteRegisters) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_MODBUS_NG ;

		OutputDebugString(_T("Function(RtuMasterModbus_WriteRegisters) End")) ;

		return m_pModbusRtuMasterBase->Modbus_WriteRegisters(uStartAddress,vecWriteValue) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(RtuMasterModbus_WriteRegisters) Throw")) ;

		return E_MODBUS_THROW ;
	}
}

MODBUS_CODE CModbusRtuMasterInterface:: Modbus_ReadRegisters(const unsigned int uStartAddress,double &dbReadValue)
{
	try
	{
		OutputDebugString(_T("Function(RtuMasterModbus_ReadRegisters) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_MODBUS_NG ;

		OutputDebugString(_T("Function(RtuMasterModbus_ReadRegisters) End")) ;

		return m_pModbusRtuMasterBase->Modbus_ReadRegisters(uStartAddress,dbReadValue) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(RtuMasterModbus_ReadRegisters) Throw")) ;

		return E_MODBUS_THROW ;
	}
}

MODBUS_CODE CModbusRtuMasterInterface:: Modbus_WriteRegisters(const unsigned int uStartAddress,double dbWriteValue)
{
	try
	{
		OutputDebugString(_T("Function(RtuMasterModbus_WriteRegisters) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_MODBUS_NG ;

		OutputDebugString(_T("Function(RtuMasterModbus_WriteRegisters) End")) ;

		return m_pModbusRtuMasterBase->Modbus_WriteRegisters(uStartAddress,dbWriteValue) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(RtuMasterModbus_WriteRegisters) Throw")) ;

		return E_MODBUS_THROW ;
	}
}