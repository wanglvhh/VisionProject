#pragma once
#include "ModuleDevelopH.h"
#include "ModbusData.h"

class CMgrDllModbusBaseDllIm : public CMgrDllDelegate
{
public:
#ifdef _DEBUG
	CMgrDllModbusBaseDllIm(LPCTSTR lpcszDllPathFullName=_T("ModbusDllD.dll"))
		: CMgrDllDelegate(lpcszDllPathFullName)
	{
	}
#else
	CMgrDllModbusBaseDllIm(LPCTSTR lpcszDllPathFullName=_T("ModbusDll.dll"))
		: CMgrDllDelegate(lpcszDllPathFullName)
	{
	}
#endif
	virtual ~CMgrDllModbusBaseDllIm(){
	}
};

class CModbusBase
{
public:
	virtual MODBUS_CODE Modbus_Init(string strInitInfo) = 0 ;

	virtual MODBUS_CODE Modbus_Release() = 0 ;

	virtual MODBUS_CODE Modbus_Close() = 0 ;

	virtual MODBUS_CODE Modbus_ReadRegisters(const unsigned int uStartAddress,const unsigned int uReadNum,vector<short> &vecReadValue) = 0 ;

	virtual MODBUS_CODE Modbus_WriteRegisters(const unsigned int uStartAddress,vector<short> vecWriteValue) = 0 ;

	virtual MODBUS_CODE Modbus_ReadRegisters(const unsigned int uStartAddress,double &dbReadValue) = 0 ;

	virtual MODBUS_CODE Modbus_WriteRegisters(const unsigned int uStartAddress,double dbWriteValue) = 0 ;
};