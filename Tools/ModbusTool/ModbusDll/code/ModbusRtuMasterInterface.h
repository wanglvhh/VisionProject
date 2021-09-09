#pragma once
#include "Modbusbase.h"
#include "ModbusRtuMasterBase.h"
#include "vCriticalSection.h"

class CModbusRtuMasterInterface :
	public CModbusBase
{
public:
	CModbusRtuMasterInterface(void);
	~CModbusRtuMasterInterface(void);

	virtual MODBUS_CODE Modbus_Init(string strInitInfo)  ;

	virtual MODBUS_CODE Modbus_Release() ;

	virtual MODBUS_CODE Modbus_Close()  ;

	virtual MODBUS_CODE Modbus_ReadRegisters(const unsigned int uStartAddress,const unsigned int uReadNum,vector<short> &vecReadValue)  ;

	virtual MODBUS_CODE Modbus_WriteRegisters(const unsigned int uStartAddress,vector<short> vecWriteValue)  ;

	virtual MODBUS_CODE Modbus_ReadRegisters(const unsigned int uStartAddress,double &dbReadValue)  ;

	virtual MODBUS_CODE Modbus_WriteRegisters(const unsigned int uStartAddress,double dbWriteValue)  ;

private:
	CModbusRtuMasterBase*        m_pModbusRtuMasterBase ;
	CMgrDllModbusRtuMasterIm     m_dllModbusRtuMasterIm ;
	bool                         m_bInitOk ;
	CRITICAL_SECTION             m_Critical ;
};
