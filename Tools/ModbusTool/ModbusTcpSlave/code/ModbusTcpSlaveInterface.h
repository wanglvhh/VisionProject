#pragma once
#include "modbus.h"
#include "ModbusData.h"
#include "Modbustcpslavebase.h"

class CModbusTcpSlaveInterface :
	public CModbusTcpSlaveBase
{
public:
	CModbusTcpSlaveInterface(void);
	~CModbusTcpSlaveInterface(void);

	virtual MODBUS_CODE Modbus_Init(string strInitInfo) ;

	virtual MODBUS_CODE Modbus_Close() ;

	virtual MODBUS_CODE Modbus_ReadRegisters(const unsigned int uStartAddress,const unsigned int uReadNum,vector<short> &vecReadValue) ;

	virtual MODBUS_CODE Modbus_WriteRegisters(const unsigned int uStartAddress,vector<short> vecWriteValue) ;

	virtual MODBUS_CODE Modbus_ReadRegisters(const unsigned int uStartAddress,double &dbReadValue) ;

	virtual MODBUS_CODE Modbus_WriteRegisters(const unsigned int uStartAddress,double dbWriteValue) ;

private:
	static unsigned int WINAPI  SlaveThread(LPVOID lparam);
private:
	CRITICAL_SECTION          m_csModbusTcpSlave ;
	bool                      m_bInitOk ;
	modbus_t*                 m_pCtx;
	modbus_mapping_t*         m_pMapping;
	unsigned int              m_uSlaveID ;
	int                       m_nServer_socket;
	unsigned int              m_dwSlaveId;
	HANDLE                    m_eSlaveThread;
	HANDLE                    m_eCloseThread;
};
