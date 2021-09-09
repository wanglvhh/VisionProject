#include "StdAfx.h"
#include "ModbusRtuSlaveInterface.h"

CModbusRtuSlaveInterface::CModbusRtuSlaveInterface(void)
{
	InitializeCriticalSection(&m_csModbusRtuSlave);
	m_eSlaveThread= CreateEventW(NULL, TRUE, FALSE, NULL);
	ResetEvent(m_eSlaveThread);
	m_eCloseThread = CreateEventW(NULL, TRUE, FALSE, NULL);
	ResetEvent(m_eCloseThread);
	m_bInitOk = false ;
}

CModbusRtuSlaveInterface::~CModbusRtuSlaveInterface(void)
{
	m_bInitOk = false ;
}

MODBUS_CODE CModbusRtuSlaveInterface:: Modbus_Init(string strInitInfo)
{
	USES_CONVERSION ;
	m_bInitOk = false ;
	//strInitInfo:Format->COM2,19200,N,8,1,strSlaveId
	try
	{
		OutputDebugString(_T("Function(RtuSlaveModbus_Init) Start")) ;

		CString strInit(strInitInfo.c_str()),strPortName(_T("")),\
			strBaudRate(_T("")),strParity(_T("")),strDataBits(_T("")),strStop(_T("")),strSlaveId(_T(""))  ;
		if (strInit.IsEmpty())
		{
			OutputDebugString(_T("Error:RtuSlaveModbus_Init strInitInfo is Empty.")) ;
			return E_MODBUS_NG ;
		}

		int nFind = strInit.Find(',') ;
		if (nFind < 0)
		{
			OutputDebugString(_T("Error:RtuSlaveModbus_Init strInitInfo Format is Error.")) ;
			return E_MODBUS_NG ;
		}
		strPortName = strInit.Mid(0,nFind) ;
		strInit = strInit.Mid(nFind + 1,strInit.GetLength() - nFind + 1) ;

		nFind = strInit.Find(',') ;
		if (nFind < 0)
		{
			OutputDebugString(_T("Error:RtuSlaveModbus_Init strInitInfo Format is Error.")) ;
			return E_MODBUS_NG ;
		}
		strBaudRate = strInit.Mid(0,nFind) ;
		strInit = strInit.Mid(nFind + 1,strInit.GetLength() - nFind + 1) ;

		nFind = strInit.Find(',') ;
		if (nFind < 0)
		{
			OutputDebugString(_T("Error:RtuSlaveModbus_Init strInitInfo Format is Error.")) ;
			return E_MODBUS_NG ;
		}
		strParity = strInit.Mid(0,nFind) ;
		strInit = strInit.Mid(nFind + 1,strInit.GetLength() - nFind + 1) ;

		nFind = strInit.Find(',') ;
		if (nFind < 0)
		{
			OutputDebugString(_T("Error:RtuSlaveModbus_Init strInitInfo Format is Error.")) ;
			return E_MODBUS_NG ;
		}
		strDataBits = strInit.Mid(0,nFind) ;
		strInit = strInit.Mid(nFind + 1,strInit.GetLength() - nFind + 1) ;

		nFind = strInit.Find(',') ;
		if (nFind < 0)
		{
			OutputDebugString(_T("Error:RtuSlaveModbus_Init strInitInfo Format is Error.")) ;
			return E_MODBUS_NG ;
		}
		strStop = strInit.Mid(0,nFind) ;
		strInit = strInit.Mid(nFind + 1,strInit.GetLength() - nFind + 1) ;

		nFind = strInit.Find(',') ;
		if (nFind >= 0)
		{
			OutputDebugString(_T("Error:RtuSlaveModbus_Init strInitInfo Format is Error.")) ;
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
			OutputDebugString(_T("Error:RtuSlaveModbus_Init modbus_new_rtu Failed.")) ;
			return E_MODBUS_NG ;
		}

		//设置从站地址
		modbus_set_slave(m_pCtx, m_uSlaveID);

		//设置debug模式
		modbus_set_debug(m_pCtx, true);

		//RTU模式下打开串口
		if (modbus_connect(m_pCtx) == -1)
		{
			CString strInfo(L"");
			strInfo.Format(L"Error:RtuSlaveModbus_Init Connection failed :%s\n", modbus_strerror(errno));
			OutputDebugString(strInfo);
			modbus_free(m_pCtx);
			return E_MODBUS_NG;
		}

		//申请4块内存区用以存放寄存器数据,这里各申请500个寄存器地址
		m_pMapping = modbus_mapping_new(500, 500, 500, 500);
		if (m_pMapping == NULL)
		{
			modbus_free(m_pCtx);
			OutputDebugString(_T("Error:RtuSlaveModbus_Init modbus_mapping_new Failed.")) ;
			return E_MODBUS_NG;
		}

		_beginthreadex(NULL, 0, SlaveThread, this, 0, &m_dwSlaveId);

		ResetEvent(m_eCloseThread) ;

		SetEvent(m_eSlaveThread);

		m_bInitOk = true ;

		OutputDebugString(_T("Function(RtuSlaveModbus_Init) End")) ;

		return E_MODBUS_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(RtuSlaveModbus_Init) Throw")) ;
		return E_MODBUS_THROW ;
	}
}

MODBUS_CODE CModbusRtuSlaveInterface:: Modbus_Close()
{
	try
	{
		OutputDebugString(_T("Function(RtuSlaveModbus_Close) Start")) ;

		DeleteCriticalSection(&m_csModbusRtuSlave) ;

		ResetEvent(m_eSlaveThread) ;
		SetEvent(m_eCloseThread);
		Sleep(1000);

		if (m_bInitOk)
		{
			if (m_pCtx)
			{
				modbus_mapping_free(m_pMapping);
				modbus_close(m_pCtx);
				modbus_free(m_pCtx);

				m_pCtx = NULL ;
			}
		}

		OutputDebugString(_T("Function(RtuSlaveModbus_Close) End")) ;

		return E_MODBUS_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(RtuSlaveModbus_Close) Throw")) ;
		return E_MODBUS_THROW ;
	}
}

MODBUS_CODE CModbusRtuSlaveInterface:: Modbus_ReadRegisters(const unsigned int uStartAddress,const unsigned int uReadNum,vector<short> &vecReadValue)
{
	try
	{
		OutputDebugString(_T("Function(RtuSlaveModbus_ReadRegisters) Start")) ;

		if (!m_bInitOk)
		{
			OutputDebugString(_T("Error:RtuSlaveModbus_ReadRegisters failed.")) ;
			return E_MODBUS_NG ;
		}

		if (uReadNum > MODBUS_TCP_MAX_ADU_LENGTH)
		{
			OutputDebugString(_T("Error:RtuSlaveModbus_ReadRegisters uReadNum over the limit.")) ;
			return E_MODBUS_NG ;
		}

		uint8_t query[MODBUS_TCP_MAX_ADU_LENGTH];
		int nRc = modbus_receive(m_pCtx, query);
		/*if (nRc < 0)
		{
		OutputDebugString(_T("Error:RtuSlaveModbus_ReadRegisters modbus_receive failed.")) ;
		return E_MODBUS_NG ;
		}*/

		modbus_reply(m_pCtx, query, nRc, m_pMapping);
		for (int i = 0; i < uReadNum;i++)
		{
			uint16_t  uiTmp = m_pMapping->tab_registers[i];
			int16_t  iPlcValue;
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

		OutputDebugString(_T("Function(RtuSlaveModbus_ReadRegisters) End")) ;

		return E_MODBUS_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(RtuSlaveModbus_ReadRegisters) Throw")) ;
		return E_MODBUS_THROW ;
	}
}

MODBUS_CODE CModbusRtuSlaveInterface:: Modbus_WriteRegisters(const unsigned int uStartAddress,vector<short> vecWriteValue)
{
	try
	{
		OutputDebugString(_T("Function(RtuSlaveModbus_WriteRegisters) Start")) ;

		if (!m_bInitOk)
		{
			OutputDebugString(_T("Error:RtuSlaveModbus_WriteRegisters failed.")) ;
			return E_MODBUS_NG ;
		}

		unsigned int uWriteNum = vecWriteValue.size() ;
		if (uWriteNum > MODBUS_TCP_MAX_ADU_LENGTH)
		{
			OutputDebugString(_T("Error:RtuSlaveModbus_WriteRegisters vecWriteValue over the limit.")) ;
			return E_MODBUS_NG ;
		}

		uint8_t query[MODBUS_TCP_MAX_ADU_LENGTH];
		int nRc = modbus_receive(m_pCtx, query);
		for (int i = 0 ;i < uWriteNum ;i++)
		{
			m_pMapping->tab_registers[i] = (uint16_t)vecWriteValue[i] ;
		}

		if (nRc < 0)
		{
			OutputDebugString(_T("Error:RtuSlaveModbus_WriteRegisters modbus_receive failed.")) ;
			return E_MODBUS_NG ;
		}

		OutputDebugString(_T("Function(RtuSlaveModbus_WriteRegisters) End")) ;

		return E_MODBUS_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(RtuSlaveModbus_WriteRegisters) Throw")) ;
		return E_MODBUS_THROW ;
	}
}

MODBUS_CODE CModbusRtuSlaveInterface:: Modbus_ReadRegisters(const unsigned int uStartAddress,double &dbReadValue)
{
	try
	{
		OutputDebugString(_T("Function(RtuSlaveModbus_ReadRegisters) Start")) ;

		if (!m_bInitOk)
		{
			OutputDebugString(_T("Error:RtuSlaveModbus_ReadRegisters failed.")) ;
			return E_MODBUS_NG ;
		}

		uint8_t query[MODBUS_TCP_MAX_ADU_LENGTH];
		int nRc = modbus_receive(m_pCtx, query);

		int nData = MAKELONG(m_pMapping->tab_registers[0], m_pMapping->tab_registers[1]);
		dbReadValue = nData / 10000.0;

		/*if (nRc < 0)
		{
			OutputDebugString(_T("Error:RtuSlaveModbus_ReadRegisters modbus_receive failed.")) ;
			return E_MODBUS_NG ;
		}*/

		modbus_reply(m_pCtx, query, nRc, m_pMapping);

		OutputDebugString(_T("Function(RtuSlaveModbus_ReadRegisters) End")) ;

		return E_MODBUS_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(RtuSlaveModbus_ReadRegisters) Throw")) ;
		return E_MODBUS_THROW ;
	}
}

MODBUS_CODE CModbusRtuSlaveInterface:: Modbus_WriteRegisters(const unsigned int uStartAddress,double dbWriteValue)
{
	try
	{
		OutputDebugString(_T("Function(RtuSlaveModbus_WriteRegisters) Start")) ;

		if (!m_bInitOk)
		{
			OutputDebugString(_T("Error:RtuSlaveModbus_WriteRegisters failed.")) ;
			return E_MODBUS_NG ;
		}

		int nData = (int)(dbWriteValue * 10000.0);
		short int nLow = LOWORD(nData);
		short int nHigh = HIWORD(nData);

		uint8_t query[MODBUS_TCP_MAX_ADU_LENGTH];
		int nRc = modbus_receive(m_pCtx, query);
		m_pMapping->tab_registers[0] = (uint16_t)nLow;
		m_pMapping->tab_registers[1] = (uint16_t)nHigh;
		if (nRc < 0)
		{
			OutputDebugString(_T("Error:RtuSlaveModbus_WriteRegisters modbus_receive failed.")) ;
			return E_MODBUS_NG ;
		}

		modbus_reply(m_pCtx, query, nRc, m_pMapping);

		OutputDebugString(_T("Function(RtuSlaveModbus_WriteRegisters) End")) ;

		return E_MODBUS_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(RtuSlaveModbus_WriteRegisters) Throw")) ;
		return E_MODBUS_THROW ;
	}
}

unsigned int WINAPI CModbusRtuSlaveInterface::SlaveThread(LPVOID lparam)
{
	try
	{
		CModbusRtuSlaveInterface *pDlg = (CModbusRtuSlaveInterface*)lparam;

		HANDLE  eventHandle[2];
		eventHandle[0] = (*pDlg).m_eCloseThread;
		eventHandle[1] = (*pDlg).m_eSlaveThread;

		while (WAIT_OBJECT_0 != WaitForSingleObject(pDlg->m_eCloseThread, 0))
		{
			//退出程序直接退出线程
			WaitForMultipleObjects(2, eventHandle, FALSE, INFINITE);
			if (WAIT_OBJECT_0 == WaitForSingleObject(pDlg->m_eCloseThread, 0))
			{
				return 0;
			}

			Sleep(100);

			uint8_t query[MODBUS_TCP_MAX_ADU_LENGTH];
			int nRc = modbus_receive(pDlg->m_pCtx, query);
			if (nRc >= 0)
			{
				modbus_reply(pDlg->m_pCtx, query, nRc, pDlg->m_pMapping);
			}
		}
		return 0;
	}
	catch (...)
	{
		return -1;
	}
}