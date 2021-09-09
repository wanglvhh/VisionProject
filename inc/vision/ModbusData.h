#pragma once
#include <iostream>

#include <string.h>
using namespace std ;

#include <vector>
using namespace std ;

#pragma region MODBUS

enum MODBUS_TOOLTYPE
{
	E_TOOL_MODBUS_RTUMASTER = 310,
	E_TOOL_MODBUS_RTUSLAVE,
	E_TOOL_MODBUS_TCPMASTER,
	E_TOOL_MODBUS_TCPSLAVE,
};

enum MODBUS_CODE
{
	E_MODBUS_THROW = -1,
	E_MODBUS_OK,
	E_MODBUS_NG,
};

#pragma endregion MODBUS