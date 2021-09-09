#pragma once
#include "Modbusbase.h"
#include "ModbusRtuSlaveBase.h"
#include "vCriticalSection.h"

class CModbusRtuSlaveInterface :
	public CModbusBase
{
public:
	CModbusRtuSlaveInterface(void);
	~CModbusRtuSlaveInterface(void);

	virtual MODBUS_CODE Modbus_Init(string strInitInfo)  ;

	virtual MODBUS_CODE Modbus_Release()  ;

	virtual MODBUS_CODE Modbus_Close()  ;

	virtual MODBUS_CODE Modbus_ReadRegisters(const unsigned int uStartAddress,const unsigned int uReadNum,vector<short> &vecReadValue)  ;

	virtual MODBUS_CODE Modbus_WriteRegisters(const unsigned int uStartAddress,vector<short> vecWriteValue)  ;

	virtual MODBUS_CODE Modbus_ReadRegisters(const unsigned int uStartAddress,double &dbReadValue)  ;

	virtual MODBUS_CODE Modbus_WriteRegisters(const unsigned int uStartAddress,double dbWriteValue)  ;

private:
	CModbusRtuSlaveBase*         m_pModbusRtuSlaveBase ;
	CMgrDllModbusRtuSlaveIm      m_dllModbusRtuSlaveIm ;
	bool                         m_bInitOk ;
	CRITICAL_SECTION             m_Critical ;
};
