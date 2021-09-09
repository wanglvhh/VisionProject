#pragma once
#include "modbus.h"
#include "ModbusData.h"
#include "Modbustcpmasterbase.h"

class CModbusTcpMasterInterface :
	public CModbusTcpMasterBase
{
public:
	CModbusTcpMasterInterface(void);
	~CModbusTcpMasterInterface(void);

	virtual MODBUS_CODE Modbus_Init(string strInitInfo) ;

	virtual MODBUS_CODE Modbus_Close() ;

	virtual MODBUS_CODE Modbus_ReadRegisters(const unsigned int uStartAddress,const unsigned int uReadNum,vector<short> &vecReadValue) ;

	virtual MODBUS_CODE Modbus_WriteRegisters(const unsigned int uStartAddress,vector<short> vecWriteValue) ;

	virtual MODBUS_CODE Modbus_ReadRegisters(const unsigned int uStartAddress,double &dbReadValue) ;

	virtual MODBUS_CODE Modbus_WriteRegisters(const unsigned int uStartAddress,double dbWriteValue) ;

private:
	CRITICAL_SECTION          m_csModbusTcpMaster ;
	bool                      m_bInitOk ;
	modbus_t*                 m_pCtx;
	unsigned int              m_uSlaveID ;
};
