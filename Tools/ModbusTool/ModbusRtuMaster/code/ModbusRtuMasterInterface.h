#pragma once
#include "modbus.h"
#include "ModbusData.h"
#include "Modbusrtumasterbase.h"

class CModbusRtuMasterInterface :
	public CModbusRtuMasterBase
{
public:
	CModbusRtuMasterInterface(void);
	~CModbusRtuMasterInterface(void);

	virtual MODBUS_CODE Modbus_Init(string strInitInfo) ;

	virtual MODBUS_CODE Modbus_Close() ;

	virtual MODBUS_CODE Modbus_ReadRegisters(const unsigned int uStartAddress,const unsigned int uReadNum,vector<short> &vecReadValue) ;

	virtual MODBUS_CODE Modbus_WriteRegisters(const unsigned int uStartAddress,vector<short> vecWriteValue) ;

	virtual MODBUS_CODE Modbus_ReadRegisters(const unsigned int uStartAddress,double &dbReadValue) ;

	virtual MODBUS_CODE Modbus_WriteRegisters(const unsigned int uStartAddress,double dbWriteValue) ;

private:
	CRITICAL_SECTION          m_csModbusRtuMaster ;
	bool                      m_bInitOk ;
	modbus_t*                 m_pCtx;
	unsigned int              m_uSlaveID ;
};
