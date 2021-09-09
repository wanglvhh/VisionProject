#pragma once
#include "Modbusbase.h"
#include "ModbusTcpMasterBase.h"
#include "vCriticalSection.h"

class CModbusTcpMasterInterface :
	public CModbusBase
{
public:
	CModbusTcpMasterInterface(void);
	~CModbusTcpMasterInterface(void);

	virtual MODBUS_CODE Modbus_Init(string strInitInfo)  ;

	virtual MODBUS_CODE Modbus_Release()  ;

	virtual MODBUS_CODE Modbus_Close()  ;

	virtual MODBUS_CODE Modbus_ReadRegisters(const unsigned int uStartAddress,const unsigned int uReadNum,vector<short> &vecReadValue)  ;

	virtual MODBUS_CODE Modbus_WriteRegisters(const unsigned int uStartAddress,vector<short> vecWriteValue)  ;

	virtual MODBUS_CODE Modbus_ReadRegisters(const unsigned int uStartAddress,double &dbReadValue)  ;

	virtual MODBUS_CODE Modbus_WriteRegisters(const unsigned int uStartAddress,double dbWriteValue)  ;

private:
	CModbusTcpMasterBase*        m_pModbusTcpMasterBase ;
	CMgrDllModbusTcpMasterIm     m_dllModbusTcpMasterIm ;
	bool                         m_bInitOk ;
	CRITICAL_SECTION             m_Critical ;
};
