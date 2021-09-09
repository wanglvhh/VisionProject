#pragma once
#include "ModuleDevelopH.h"
#include "ModbusData.h"

class CMgrDllModbusTcpSlaveIm : public CMgrDllDelegate
{
public:
#ifdef _DEBUG
	CMgrDllModbusTcpSlaveIm(LPCTSTR lpcszDllPathFullName=_T("ModbusTcpSlaveD.dll"))
		: CMgrDllDelegate(lpcszDllPathFullName)
	{
	}
#else
	CMgrDllModbusTcpSlaveIm(LPCTSTR lpcszDllPathFullName=_T("ModbusTcpSlave.dll"))
		: CMgrDllDelegate(lpcszDllPathFullName)
	{
	}
#endif
	virtual ~CMgrDllModbusTcpSlaveIm(){
	}
};

class CModbusTcpSlaveBase
{
public:
	virtual MODBUS_CODE Modbus_Init(string strInitInfo) = 0 ;

	virtual MODBUS_CODE Modbus_Close() = 0 ;

	virtual MODBUS_CODE Modbus_ReadRegisters(const unsigned int uStartAddress,const unsigned int uReadNum,vector<short> &vecReadValue) = 0 ;

	virtual MODBUS_CODE Modbus_WriteRegisters(const unsigned int uStartAddress,vector<short> vecWriteValue) = 0 ;

	virtual MODBUS_CODE Modbus_ReadRegisters(const unsigned int uStartAddress,double &dbReadValue) = 0 ;

	virtual MODBUS_CODE Modbus_WriteRegisters(const unsigned int uStartAddress,double dbWriteValue) = 0 ;
};