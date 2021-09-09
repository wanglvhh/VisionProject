#pragma once
#include "modbus.h"
#include "ModbusData.h"
#include "Modbusrtuslavebase.h"

class CModbusRtuSlaveInterface :
	public CModbusRtuSlaveBase
{
public:
	CModbusRtuSlaveInterface(void);
	~CModbusRtuSlaveInterface(void);

	virtual MODBUS_CODE Modbus_Init(string strInitInfo) ;

	virtual MODBUS_CODE Modbus_Close() ;

	virtual MODBUS_CODE Modbus_ReadRegisters(const unsigned int uStartAddress,const unsigned int uReadNum,vector<short> &vecReadValue) ;

	virtual MODBUS_CODE Modbus_WriteRegisters(const unsigned int uStartAddress,vector<short> vecWriteValue) ;

	virtual MODBUS_CODE Modbus_ReadRegisters(const unsigned int uStartAddress,double &dbReadValue) ;

	virtual MODBUS_CODE Modbus_WriteRegisters(const unsigned int uStartAddress,double dbWriteValue) ;

private:
	static unsigned int WINAPI  SlaveThread(LPVOID lparam);
private:
	CRITICAL_SECTION          m_csModbusRtuSlave ;
	bool                      m_bInitOk ;
	modbus_t*                 m_pCtx;
	modbus_mapping_t*         m_pMapping;
	UINT                      m_uSlaveID;
	unsigned int              m_dwSlaveId;
	HANDLE                    m_eSlaveThread;
	HANDLE                    m_eCloseThread;
};
