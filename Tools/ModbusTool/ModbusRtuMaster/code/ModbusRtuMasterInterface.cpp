#include "StdAfx.h"
#include "ModbusRtuMasterInterface.h"

CModbusRtuMasterInterface::CModbusRtuMasterInterface(void)
{
	InitializeCriticalSection(&m_csModbusRtuMaster);
	m_bInitOk = false ;
}

CModbusRtuMasterInterface::~CModbusRtuMasterInterface(void)
{
	m_bInitOk = false ;
}

MODBUS_CODE CModbusRtuMasterInterface:: Modbus_Init(string strInitInfo)
{
	USES_CONVERSION ;
	m_bInitOk = false ;
	//strInitInfo:Format->COM1,19200,N,8,1,strSlaveId
	try
	{
		OutputDebugString(_T("Function(RtuMasterModbus_Init) Start")) ;

		CString strInit(strInitInfo.c_str()),strPortName(_T("")),\
			strBaudRate(_T("")),strParity(_T("")),strDataBits(_T("")),strStop(_T("")),strSlaveId(_T(""))  ;
		if (strInit.IsEmpty())
		{
			OutputDebugString(_T("Error:RtuMasterModbus_Init strInitInfo is Empty.")) ;
			return E_MODBUS_NG ;
		}

		int nFind = strInit.Find(',') ;
		if (nFind < 0)
		{
			OutputDebugString(_T("Error:RtuMasterModbus_Init strInitInfo Format is Error.")) ;
			return E_MODBUS_NG ;
		}
		strPortName = strInit.Mid(0,nFind) ;
		strInit = strInit.Mid(nFind + 1,strInit.GetLength() - nFind + 1) ;

		nFind = strInit.Find(',') ;
		if (nFind < 0)
		{
			OutputDebugString(_T("Error:RtuMasterModbus_Init strInitInfo Format is Error.")) ;
			return E_MODBUS_NG ;
		}
		strBaudRate = strInit.Mid(0,nFind) ;
		strInit = strInit.Mid(nFind + 1,strInit.GetLength() - nFind + 1) ;

		nFind = strInit.Find(',') ;
		if (nFind < 0)
		{
			OutputDebugString(_T("Error:RtuMasterModbus_Init strInitInfo Format is Error.")) ;
			return E_MODBUS_NG ;
		}
		strParity = strInit.Mid(0,nFind) ;
		strInit = strInit.Mid(nFind + 1,strInit.GetLength() - nFind + 1) ;

		nFind = strInit.Find(',') ;
		if (nFind < 0)
		{
			OutputDebugString(_T("Error:RtuMasterModbus_Init strInitInfo Format is Error.")) ;
			return E_MODBUS_NG ;
		}
		strDataBits = strInit.Mid(0,nFind) ;
		strInit = strInit.Mid(nFind + 1,strInit.GetLength() - nFind + 1) ;

		nFind = strInit.Find(',') ;
		if (nFind < 0)
		{
			OutputDebugString(_T("Error:RtuMasterModbus_Init strInitInfo Format is Error.")) ;
			return E_MODBUS_NG ;
		}
		strStop = strInit.Mid(0,nFind) ;
		strInit = strInit.Mid(nFind + 1,strInit.GetLength() - nFind + 1) ;

		nFind = strInit.Find(',') ;
		if (nFind >= 0)
		{
			OutputDebugString(_T("Error:RtuMasterModbus_Init strInitInfo Format is Error.")) ;
			return E_MODBUS_NG ;
		}
		strSlaveId = strInit ;
		m_uSlaveID = _wtoi(strSlaveId) ;

		char chParity ;
		if (_T("0") == strParity)
		{
			chParity = 'N' ;
		}
		else if (_T("1") == strParity)
		{
			chParity = 'O' ;
		}
		else if (_T("1") == strParity)
		{
			chParity = 'E' ;
		}

		int nStop = -1 ;
		if (_T("0") == strStop)
		{
			nStop = 1 ;
		}
		else if (_T("1") == strStop)
		{
			nStop = 2 ;
		}

		//创建一个RTU类型的容器
		m_pCtx = modbus_new_rtu(W2A(strPortName), _wtoi(strBaudRate), chParity, _wtoi(strDataBits),nStop);
		if (NULL == m_pCtx)
		{
			OutputDebugString(_T("Error:RtuMasterModbus_Init modbus_new_rtu Failed.")) ;
			return E_MODBUS_NG ;
		}

		//设置debug模式
		modbus_set_debug(m_pCtx, true);

		//RTU模式下打开串口
		if (modbus_connect(m_pCtx) == -1)
		{
			CString strInfo(L"");
			strInfo.Format(L"Error:RtuMasterModbus_Init Connection failed :%s\n", modbus_strerror(errno));
			OutputDebugString(strInfo);
			modbus_free(m_pCtx);
			return E_MODBUS_NG;
		}

		//设置从站地址
		modbus_set_slave(m_pCtx, m_uSlaveID);

		m_bInitOk = true ;

		OutputDebugString(_T("Function(RtuMasterModbus_Init) End")) ;

		return E_MODBUS_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(RtuMasterModbus_Init) Throw")) ;
		return E_MODBUS_THROW ;
	}
}

MODBUS_CODE CModbusRtuMasterInterface:: Modbus_Close()
{
	try
	{
		OutputDebugString(_T("Function(RtuMasterModbus_Close) Start")) ;

		if (m_bInitOk)
		{
			if (m_pCtx)
			{
				modbus_close(m_pCtx);
				modbus_free(m_pCtx);

				m_pCtx = NULL ;
			}
		}

		DeleteCriticalSection(&m_csModbusRtuMaster) ;

		OutputDebugString(_T("Function(RtuMasterModbus_Close) End")) ;

		return E_MODBUS_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(RtuMasterModbus_Close) Throw")) ;
		return E_MODBUS_THROW ;
	}
}

MODBUS_CODE CModbusRtuMasterInterface:: Modbus_ReadRegisters(const unsigned int uStartAddress,const unsigned int uReadNum,vector<short> &vecReadValue)
{
	try
	{
		OutputDebugString(_T("Function(RtuMasterModbus_ReadRegisters) Start")) ;

		if (!m_bInitOk)
		{
			OutputDebugString(_T("Error:RtuMasterModbus_ReadRegisters failed.")) ;
			return E_MODBUS_NG ;
		}

		uint16_t*  pTabRpRegisters = (uint16_t *)malloc(uReadNum*sizeof(uint16_t)) ;
		memset(pTabRpRegisters, 0, uReadNum*sizeof(uint16_t));

		//读取多个寄存器
		int nRc = modbus_read_registers(m_pCtx, uStartAddress, uReadNum, pTabRpRegisters);
		if (nRc != uReadNum)
		{
			OutputDebugString(_T("Error: RtuMasterModbus_ReadRegisters return ReadNum,is not equal input readNum "));
			free(pTabRpRegisters);
			return E_MODBUS_NG ;
		}

		for (int i = 0; i < uReadNum; i++)
		{
			uint16_t  uiTmp = pTabRpRegisters[i];
			int16_t  iPlcValue ;
			if (uiTmp & 0x8000)
			{
				iPlcValue = ~uiTmp + 1;
				iPlcValue = -iPlcValue;
			}
			else
			{
				iPlcValue = uiTmp;
			}

			vecReadValue.push_back(iPlcValue) ;
		}

		free(pTabRpRegisters);

		OutputDebugString(_T("Function(RtuMasterModbus_ReadRegisters) End")) ;

		return E_MODBUS_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(RtuMasterModbus_ReadRegisters) Throw")) ;
		return E_MODBUS_THROW ;
	}
}

MODBUS_CODE CModbusRtuMasterInterface:: Modbus_WriteRegisters(const unsigned int uStartAddress,vector<short> vecWriteValue)
{
	try
	{
		OutputDebugString(_T("Function(RtuMasterModbus_WriteRegisters) Start")) ;

		if (!m_bInitOk)
		{
			OutputDebugString(_T("Error:RtuMasterModbus_WriteRegisters failed.")) ;
			return E_MODBUS_NG ;
		}

		unsigned int uWriteNum = vecWriteValue.size() ;
		uint16_t* pTabRqRegisters = (uint16_t *)malloc(uWriteNum*sizeof(uint16_t));
		memset(pTabRqRegisters, 0, uWriteNum*sizeof(uint16_t));

		for (int i = 0 ;i < uWriteNum ;i++)
		{
			pTabRqRegisters[i] = vecWriteValue[i] ;
		}

		int nRc = modbus_write_registers(m_pCtx, uStartAddress, uWriteNum, pTabRqRegisters);
		if (uWriteNum != nRc)
		{
			OutputDebugString(_T("Error: RtuMasterModbus_WriteRegisters return WriteNum,is not equal vecWriteValue size "));
			free(pTabRqRegisters);
			return E_MODBUS_NG ;
		}

		free(pTabRqRegisters);

		OutputDebugString(_T("Function(RtuMasterModbus_WriteRegisters) End")) ;

		return E_MODBUS_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(RtuMasterModbus_WriteRegisters) Throw")) ;
		return E_MODBUS_THROW ;
	}
}

MODBUS_CODE CModbusRtuMasterInterface:: Modbus_ReadRegisters(const unsigned int uStartAddress,double &dbReadValue)
{
	try
	{
		OutputDebugString(_T("Function(RtuMasterModbus_ReadRegisters) Start")) ;

		if (!m_bInitOk)
		{
			OutputDebugString(_T("Error:RtuMasterModbus_ReadRegisters failed.")) ;
			return E_MODBUS_NG ;
		}

		uint16_t* pTabRqRegisters = (uint16_t *)malloc(2 * sizeof(uint16_t)) ;
		memset(pTabRqRegisters, 0, 2 * sizeof(uint16_t));

		int nRc = modbus_read_registers(m_pCtx, uStartAddress, 2, pTabRqRegisters);
		if (2 != nRc)
		{
			free(pTabRqRegisters);
			OutputDebugString(_T("Error: RtuMasterModbus_ReadRegisters return ReadNum,is not equal 2 "));
			return E_MODBUS_NG ;
		}

		dbReadValue = MAKELONG(pTabRqRegisters[0], pTabRqRegisters[1]) / 10000.0;
		free(pTabRqRegisters);

		OutputDebugString(_T("Function(RtuMasterModbus_ReadRegisters) End")) ;

		return E_MODBUS_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(RtuMasterModbus_ReadRegisters) Throw")) ;
		return E_MODBUS_THROW ;
	}
}

MODBUS_CODE CModbusRtuMasterInterface:: Modbus_WriteRegisters(const unsigned int uStartAddress,double dbWriteValue)
{
	try
	{
		OutputDebugString(_T("Function(RtuMasterModbus_WriteRegisters) Start")) ;

		if (!m_bInitOk)
		{
			OutputDebugString(_T("Error:RtuMasterModbus_WriteRegisters failed.")) ;
			return E_MODBUS_NG ;
		}

		uint16_t* pTabRqRegisters = (uint16_t *)malloc(2 * sizeof(uint16_t)) ;
		memset(pTabRqRegisters, 0, 2 * sizeof(uint16_t));

		int nData = (int)(dbWriteValue * 10000.0);
		short int nLow = LOWORD(nData);
		short int nHigh = HIWORD(nData);

		pTabRqRegisters[0] = (uint16_t)nLow;
		pTabRqRegisters[1] = (uint16_t)nHigh;

		int nRc = modbus_write_registers(m_pCtx, uStartAddress, 2, pTabRqRegisters);
		if (2 != nRc)
		{
			free(pTabRqRegisters);
			OutputDebugString(_T("Error: RtuMasterModbus_WriteRegisters return WriteNum,is not equal 2 "));
			return E_MODBUS_NG ;
		}

		free(pTabRqRegisters);

		OutputDebugString(_T("Function(RtuMasterModbus_WriteRegisters) End")) ;

		return E_MODBUS_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(RtuMasterModbus_WriteRegisters) Throw")) ;
		return E_MODBUS_THROW ;
	}
}