#include "StdAfx.h"
#include "Communication232Interface.h"

CCommunication232Interface::CCommunication232Interface(void)
{
	m_strData = "" ;
	m_bSerialOpen = false ;
}

CCommunication232Interface::~CCommunication232Interface(void)
{
	m_strData = "" ;
	m_bSerialOpen = false ;
}

COMM_CODE CCommunication232Interface::Comm_Init(string strInitInfo)
{
	USES_CONVERSION ;
	m_bSerialOpen = false ;
	//strInitInfo:Format->COM9,19200,0,8,0
	try
	{
		OutputDebugString(_T("Function(232Comm_Init) Start")) ;

		InitializeCriticalSection(&m_csComm232);

		CString strInit(strInitInfo.c_str()),strPortName(_T("")),\
			strBaudRate(_T("")),strParity(_T("")),strDataBits(_T("")),strStop(_T(""))  ;
		if (strInit.IsEmpty())
		{
			OutputDebugString(_T("Error:232Comm_Init strInitInfo is Empty.")) ;
			return E_COMM_NG ;
		}

		int nFind = strInit.Find(',') ;
		if (nFind < 0)
		{
			OutputDebugString(_T("Error:232Comm_Init strInitInfo Format is Error.")) ;
			return E_COMM_NG ;
		}
		strPortName = strInit.Mid(0,nFind) ;
		strInit = strInit.Mid(nFind + 1,strInit.GetLength() - nFind - 1) ;

		nFind = strInit.Find(',') ;
		if (nFind < 0)
		{
			OutputDebugString(_T("Error:232Comm_Init strInitInfo Format is Error.")) ;
			return E_COMM_NG ;
		}
		strBaudRate = strInit.Mid(0,nFind) ;
		strInit = strInit.Mid(nFind + 1,strInit.GetLength() - nFind - 1) ;

		nFind = strInit.Find(',') ;
		if (nFind < 0)
		{
			OutputDebugString(_T("Error:232Comm_Init strInitInfo Format is Error.")) ;
			return E_COMM_NG ;
		}
		strParity = strInit.Mid(0,nFind) ;
		strInit = strInit.Mid(nFind + 1,strInit.GetLength() - nFind - 1) ;

		nFind = strInit.Find(',') ;
		if (nFind < 0)
		{
			OutputDebugString(_T("Error:232Comm_Init strInitInfo Format is Error.")) ;
			return E_COMM_NG ;
		}
		strDataBits = strInit.Mid(0,nFind) ;
		strInit = strInit.Mid(nFind + 1,strInit.GetLength() - nFind - 1) ;

		nFind = strInit.Find(',') ;
		if (nFind >= 0)
		{
			OutputDebugString(_T("Error:232Comm_Init strInitInfo Format is Error.")) ;
			return E_COMM_NG ;
		}
		strStop = strInit ;

		//初始化serialPort
		m_serialPort.init(W2A(strPortName), _wtoi(strBaudRate), itas109::Parity(_wtoi(strParity)), itas109::DataBits(_wtoi(strDataBits)), itas109::StopBits(_wtoi(strStop)));
		if (m_serialPort.open())
		{
			m_bSerialOpen = true ;
		}
		else
		{
			m_bSerialOpen = false ;
			OutputDebugString(_T("Error:232Comm_Init connected Error.")) ;
			return E_COMM_NG ;
		}

		OutputDebugString(_T("Function(232Comm_Init) End")) ;

		return E_COMM_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(232Comm_Init) Throw")) ;
		return E_COMM_THROW ;
	}
}

COMM_CODE CCommunication232Interface::Comm_Close()
{
	try
	{
		OutputDebugString(_T("Function(232Comm_Close) Start")) ;

		if (m_bSerialOpen)
		{
			m_serialPort.close() ;
			m_bSerialOpen = false ;
		}

		DeleteCriticalSection(&m_csComm232) ;

		OutputDebugString(_T("Function(232Comm_Close) End")) ;

		return E_COMM_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(232Comm_Close) Throw")) ;
		return E_COMM_THROW ;
	}
}

COMM_CODE CCommunication232Interface::Comm_ClearData()
{
	try
	{
		OutputDebugString(_T("Function(232Comm_ClearData) Start")) ;

		EnterCriticalSection(&m_csComm232) ;

		m_strData = "" ;

		LeaveCriticalSection(&m_csComm232) ;

		OutputDebugString(_T("Function(232Comm_ClearData) End")) ;

		return E_COMM_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(232Comm_ClearData) Throw")) ;
		return E_COMM_THROW ;
	}
}

COMM_CODE CCommunication232Interface::Comm_RevData(string &strRevData)
{
	USES_CONVERSION ;
	try
	{
		OutputDebugString(_T("Function(232Comm_RevData) Start")) ;

		if (!m_bSerialOpen)
		{
			OutputDebugString(_T("Error:232Comm_SendData Port not Open")) ;
			return E_COMM_NG ;
		}

		char * str = NULL;
		str = new char[1024];
		int iRet = m_serialPort.readAllData(str);

		if (iRet > 0)
		{
			str[iRet] = '\0';
			CString str1((char*)str);
			strRevData = W2A(str1) ;
		}

		LeaveCriticalSection(&m_csComm232) ;

		OutputDebugString(_T("Function(232Comm_RevData) End")) ;

		return E_COMM_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(232Comm_RevData) Throw")) ;
		return E_COMM_THROW ;
	}
}

COMM_CODE CCommunication232Interface::Comm_SendData(string strSendData)
{
	USES_CONVERSION ;
	try
	{
		OutputDebugString(_T("Function(232Comm_SendData) Start")) ;

		if (!m_bSerialOpen)
		{
			OutputDebugString(_T("Error:232Comm_SendData Port not Open")) ;
			return E_COMM_NG ;
		}

		size_t len = 0;
		char* m_str = NULL;
#ifdef UNICODE
		// 兼容中文
		CStringA strA(strSendData.c_str());
		len = strA.GetLength();
		m_str = strA.GetBuffer();
#else
		len = strSendData.c_str().GetLength();
		m_str = strSendData.c_str().GetBuffer(0);
#endif

		m_serialPort.writeData(m_str, len);

		OutputDebugString(_T("Function(232Comm_SendData) End")) ;

		return E_COMM_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(232Comm_SendData) Throw")) ;
		return E_COMM_THROW ;
	}
}