#pragma once
#include "ModuleDevelopH.h"
#include "ModbusData.h"

class CMgrDllModbusTcpMasterIm : public CMgrDllDelegate
{
public:
#ifdef _DEBUG
	CMgrDllModbusTcpMasterIm(LPCTSTR lpcszDllPathFullName=_T("ModbusTcpMasterD.dll"))
		: CMgrDllDelegate(lpcszDllPathFullName)
	{
	}
#else
	CMgrDllModbusTcpMasterIm(LPCTSTR lpcszDllPathFullName=_T("ModbusTcpMaster.dll"))
		: CMgrDllDelegate(lpcszDllPathFullName)
	{
	}
#endif
	virtual ~CMgrDllModbusTcpMasterIm(){
	}
};

class CModbusTcpMasterBase
{
public:
	virtual MODBUS_CODE Modbus_Init(string strInitInfo) = 0 ;

	virtual MODBUS_CODE Modbus_Close() = 0 ;

	virtual MODBUS_CODE Modbus_ReadRegisters(const unsigned int uStartAddress,const unsigned int uReadNum,vector<short> &vecReadValue) = 0 ;

	virtual MODBUS_CODE Modbus_WriteRegisters(const unsigned int uStartAddress,vector<short> vecWriteValue) = 0 ;

	virtual MODBUS_CODE Modbus_ReadRegisters(const unsigned int uStartAddress,double &dbReadValue) = 0 ;

	virtual MODBUS_CODE Modbus_WriteRegisters(const unsigned int uStartAddress,double dbWriteValue) = 0 ;
};