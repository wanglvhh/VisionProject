#pragma once
#include "Modbusbase.h"
#include "ModbusTcpSlaveBase.h"
#include "vCriticalSection.h"

class CModbusTcpSlaveInterface :
	public CModbusBase
{
public:
	CModbusTcpSlaveInterface(void);
	~CModbusTcpSlaveInterface(void);

	virtual MODBUS_CODE Modbus_Init(string strInitInfo)  ;

	virtual MODBUS_CODE Modbus_Release()  ;

	virtual MODBUS_CODE Modbus_Close()  ;

	virtual MODBUS_CODE Modbus_ReadRegisters(const unsigned int uStartAddress,const unsigned int uReadNum,vector<short> &vecReadValue)  ;

	virtual MODBUS_CODE Modbus_WriteRegisters(const unsigned int uStartAddress,vector<short> vecWriteValue)  ;

	virtual MODBUS_CODE Modbus_ReadRegisters(const unsigned int uStartAddress,double &dbReadValue)  ;

	virtual MODBUS_CODE Modbus_WriteRegisters(const unsigned int uStartAddress,double dbWriteValue)  ;

private:
	CModbusTcpSlaveBase*         m_pModbusTcpSlaveBase ;
	CMgrDllModbusTcpSlaveIm      m_dllModbusTcpSlaveIm ;
	bool                         m_bInitOk ;
	CRITICAL_SECTION             m_Critical ;
};
