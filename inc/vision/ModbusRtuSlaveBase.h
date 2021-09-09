#pragma once
#include "ModuleDevelopH.h"
#include "ModbusData.h"

class CMgrDllModbusRtuSlaveIm : public CMgrDllDelegate
{
public:
#ifdef _DEBUG
	CMgrDllModbusRtuSlaveIm(LPCTSTR lpcszDllPathFullName=_T("ModbusRtuSlaveD.dll"))
		: CMgrDllDelegate(lpcszDllPathFullName)
	{
	}
#else
	CMgrDllModbusRtuSlaveIm(LPCTSTR lpcszDllPathFullName=_T("ModbusRtuSlave.dll"))
		: CMgrDllDelegate(lpcszDllPathFullName)
	{
	}
#endif
	virtual ~CMgrDllModbusRtuSlaveIm(){
	}
};

class CModbusRtuSlaveBase
{
public:
	virtual MODBUS_CODE Modbus_Init(string strInitInfo) = 0 ;

	virtual MODBUS_CODE Modbus_Close() = 0 ;

	virtual MODBUS_CODE Modbus_ReadRegisters(const unsigned int uStartAddress,const unsigned int uReadNum,vector<short> &vecReadValue) = 0 ;

	virtual MODBUS_CODE Modbus_WriteRegisters(const unsigned int uStartAddress,vector<short> vecWriteValue) = 0 ;

	virtual MODBUS_CODE Modbus_ReadRegisters(const unsigned int uStartAddress,double &dbReadValue) = 0 ;

	virtual MODBUS_CODE Modbus_WriteRegisters(const unsigned int uStartAddress,double dbWriteValue) = 0 ;
};