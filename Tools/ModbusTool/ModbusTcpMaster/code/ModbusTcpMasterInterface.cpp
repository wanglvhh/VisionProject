#include "StdAfx.h"
#include "ModbusTcpMasterInterface.h"

CModbusTcpMasterInterface::CModbusTcpMasterInterface(void)
{
	InitializeCriticalSection(&m_csModbusTcpMaster);
	m_bInitOk = false ;
}

CModbusTcpMasterInterface::~CModbusTcpMasterInterface(void)
{
	m_bInitOk = false ;
}

MODBUS_CODE CModbusTcpMasterInterface:: Modbus_Init(string strInitInfo)
{
	USES_CONVERSION ;
	m_bInitOk = false ;
	//strInitInfo:Format->127.0.0.1,502,strSlaveId
	try
	{
		OutputDebugString(_T("Function(TcpMasterModbus_Init) Start")) ;

		CString strInit(strInitInfo.c_str()),strIpAddress(_T("")), strPort(_T("")) ,strSlaveId(_T(""))  ;
		if (strInit.IsEmpty())
		{
			OutputDebugString(_T("Error:TcpMasterModbus_Init strInitInfo is Empty.")) ;
			return E_MODBUS_NG ;
		}

		int nFind = strInit.Find(',') ;
		if (nFind < 0)
		{
			OutputDebugString(_T("Error:TcpMasterModbus_Init strInitInfo Format is Error.")) ;
			return E_MODBUS_NG ;
		}
		strIpAddress = strInit.Mid(0,nFind) ;
		strInit = strInit.Mid(nFind + 1,strInit.GetLength() - nFind + 1) ;

		nFind = strInit.Find(',') ;
		if (nFind < 0)
		{
			OutputDebugString(_T("Error:TcpMasterModbus_Init strInitInfo Format is Error.")) ;
			return E_MODBUS_NG ;
		}
		strPort = strInit.Mid(0,nFind) ;
		strInit = strInit.Mid(nFind + 1,strInit.GetLength() - nFind + 1) ;

		nFind = strInit.Find(',') ;
		if (nFind >= 0)
		{
			OutputDebugString(_T("Error:TcpMasterModbus_Init strInitInfo Format is Error.")) ;
			return E_MODBUS_NG ;
		}
		strSlaveId = strInit ;
		m_uSlaveID = _wtoi(strSlaveId) ;

		//创建一个TCP类型容器
		m_pCtx = modbus_new_tcp(W2A(strIpAddress), _wtoi(strPort));
		if (m_pCtx == NULL)
		{
			modbus_free(m_pCtx);
			OutputDebugString(_T("Error:TcpMasterModbus_Init modbus_new_tcp Failed.")) ;
			return E_MODBUS_NG;
		}

		//设置debug模式
		modbus_set_debug(m_pCtx, true);

		//设置从机地址
		modbus_set_slave(m_pCtx, m_uSlaveID);

		if (modbus_connect(m_pCtx) == -1)
		{
			modbus_free(m_pCtx);
			OutputDebugString(_T("Error:TcpMasterModbus_Init modbus_connect Failed.")) ;
			return E_MODBUS_NG;
		}

		m_bInitOk = true ;

		OutputDebugString(_T("Function(TcpMasterModbus_Init) End")) ;

		return E_MODBUS_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(TcpMasterModbus_Init) Throw")) ;
		return E_MODBUS_THROW ;
	}
}

MODBUS_CODE CModbusTcpMasterInterface:: Modbus_Close()
{
	try
	{
		OutputDebugString(_T("Function(TcpMasterModbus_Close) Start")) ;

		if (m_bInitOk)
		{
			if (m_pCtx)
			{
				modbus_close(m_pCtx);
				modbus_free(m_pCtx);
			}
		}

		DeleteCriticalSection(&m_csModbusTcpMaster) ;

		OutputDebugString(_T("Function(TcpMasterModbus_Close) End")) ;

		return E_MODBUS_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(TcpMasterModbus_Close) Throw")) ;
		return E_MODBUS_THROW ;
	}
}

MODBUS_CODE CModbusTcpMasterInterface:: Modbus_ReadRegisters(const unsigned int uStartAddress,const unsigned int uReadNum,vector<short> &vecReadValue)
{
	try
	{
		OutputDebugString(_T("Function(TcpMasterModbus_ReadRegisters) Start")) ;

		if (!m_bInitOk)
		{
			OutputDebugString(_T("Error:TcpMasterModbus_ReadRegisters failed.")) ;
			return E_MODBUS_NG ;
		}

		uint16_t*  pTabRpRegisters = (uint16_t *)malloc(uReadNum*sizeof(uint16_t)) ;
		memset(pTabRpRegisters, 0, uReadNum*sizeof(uint16_t));

		//读取多个寄存器
		int nRc = modbus_read_registers(m_pCtx, uStartAddress, uReadNum, pTabRpRegisters);
		if (nRc != uReadNum)
		{
			OutputDebugString(_T("Error: TcpMasterModbus_ReadRegisters return ReadNum,is not equal input readNum "));
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

		OutputDebugString(_T("Function(TcpMasterModbus_ReadRegisters) End")) ;

		return E_MODBUS_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(TcpMasterModbus_ReadRegisters) Throw")) ;
		return E_MODBUS_THROW ;
	}
}

MODBUS_CODE CModbusTcpMasterInterface:: Modbus_WriteRegisters(const unsigned int uStartAddress,vector<short> vecWriteValue)
{
	try
	{
		OutputDebugString(_T("Function(TcpMasterModbus_WriteRegisters) Start")) ;

		if (!m_bInitOk)
		{
			OutputDebugString(_T("Error:TcpMasterModbus_WriteRegisters failed.")) ;
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
			OutputDebugString(_T("Error: TcpMasterModbus_WriteRegisters return WriteNum,is not equal vecWriteValue size "));
			free(pTabRqRegisters);
			return E_MODBUS_NG ;
		}

		free(pTabRqRegisters);

		OutputDebugString(_T("Function(TcpMasterModbus_WriteRegisters) End")) ;

		return E_MODBUS_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(TcpMasterModbus_WriteRegisters) Throw")) ;
		return E_MODBUS_THROW ;
	}
}

MODBUS_CODE CModbusTcpMasterInterface:: Modbus_ReadRegisters(const unsigned int uStartAddress,double &dbReadValue)
{
	try
	{
		OutputDebugString(_T("Function(TcpMasterModbus_ReadRegisters) Start")) ;

		if (!m_bInitOk)
		{
			OutputDebugString(_T("Error:TcpMasterModbus_ReadRegisters failed.")) ;
			return E_MODBUS_NG ;
		}

		uint16_t* pTabRqRegisters = (uint16_t *)malloc(2 * sizeof(uint16_t)) ;
		memset(pTabRqRegisters, 0, 2 * sizeof(uint16_t));

		int nRc = modbus_read_registers(m_pCtx, uStartAddress, 2, pTabRqRegisters);
		if (2 != nRc)
		{
			free(pTabRqRegisters);
			OutputDebugString(_T("Error: TcpMasterModbus_ReadRegisters return ReadNum,is not equal 2 "));
			return E_MODBUS_NG ;
		}

		dbReadValue = MAKELONG(pTabRqRegisters[0], pTabRqRegisters[1]) / 10000.0;
		free(pTabRqRegisters);

		OutputDebugString(_T("Function(TcpMasterModbus_ReadRegisters) End")) ;

		return E_MODBUS_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(TcpMasterModbus_ReadRegisters) Throw")) ;
		return E_MODBUS_THROW ;
	}
}

MODBUS_CODE CModbusTcpMasterInterface:: Modbus_WriteRegisters(const unsigned int uStartAddress,double dbWriteValue)
{
	try
	{
		OutputDebugString(_T("Function(TcpMasterModbus_WriteRegisters) Start")) ;

		if (!m_bInitOk)
		{
			OutputDebugString(_T("Error:TcpMasterModbus_WriteRegisters failed.")) ;
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
			OutputDebugString(_T("Error: TcpMasterModbus_WriteRegisters return WriteNum,is not equal 2 "));
			return E_MODBUS_NG ;
		}

		free(pTabRqRegisters);

		OutputDebugString(_T("Function(TcpMasterModbus_WriteRegisters) End")) ;

		return E_MODBUS_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(TcpMasterModbus_WriteRegisters) Throw")) ;
		return E_MODBUS_THROW ;
	}
}