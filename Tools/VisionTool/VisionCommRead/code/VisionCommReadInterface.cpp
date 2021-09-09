#include "StdAfx.h"
#include "VisionCommReadInterface.h"
#include "MainDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CVisionCommReadInterface::CVisionCommReadInterface(void)
{
	m_pCommunicationNode = NULL ;
	m_dbWaitTime = 0.0 ;
	m_strReadData = _T("") ;
	m_strCommInfo = _T("") ;
	m_pCommunicationNode = NULL ;
}

CVisionCommReadInterface::~CVisionCommReadInterface(void)
{
}

VISION_CODE CVisionCommReadInterface::Vision_Init()
{
	try
	{
		OutputDebugString(_T("Function(CommunicationRead_Init) Start")) ;

		if (NULL == m_pCommunicationNode)
		{
			OutputDebugString(_T("Function(CommunicationRead_Init) Camera Point is Empty")) ;
			return E_VCODE_NG ;
		}

		OutputDebugString(_T("Function(CommunicationRead_Init) End")) ;
		return E_VCODE_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(CommunicationRead_Init) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionCommReadInterface::Vision_Release()
{
	try
	{
		OutputDebugString(_T("Function(CommunicationRead_Release) Start")) ;

		//通信指针不能在这里进行释放

		OutputDebugString(_T("Function(CommunicationRead_Release) End")) ;
		return E_VCODE_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(CommunicationRead_Release) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionCommReadInterface::Vision_SetLanguage(int nLanguage)
{
	try
	{
		OutputDebugString(_T("Function(CommunicationRead_SetLanguage) Start")) ;

		OutputDebugString(_T("Function(CommunicationRead_SetLanguage) End")) ;
		return E_VCODE_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(CommunicationRead_SetLanguage) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionCommReadInterface::Vision_LoadConfigure(const char* pLoadPath)
{
	try
	{
		OutputDebugString(_T("Function(CommunicationRead_LoadConfigure) Start")) ;

		if (NULL == pLoadPath)
		{
			OutputDebugString(_T("Function(CommunicationRead_SetConfigurePath) pLoadPath is Empty")) ;
			return E_VCODE_NG ;
		}
		CString strLoadPath(pLoadPath)  ;
		if (!vFileIsExist(strLoadPath))
		{
			OutputDebugString(_T("Function(CommunicationRead_SetConfigurePath) pLoadFile is not Exist")) ;
			return E_VCODE_NG ;
		}

		//开始反序列化
		HTuple hFileHandle,hSerializedItemHandle ;
		try
		{
			HTuple hReadTuple ;
			OpenFile(pLoadPath,"input_binary",&hFileHandle) ;
			FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
			DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
			CloseFile(hFileHandle) ;

			if (0 != (HTuple(hReadTuple[0])!=HTuple("VisionSystemCommunicationRead")))
			{
				OutputDebugString(_T("Function(CommunicationRead_SetConfigurePath) Load Configure is Error")) ;
				return E_VCODE_NG;
			}

			m_dbWaitTime = hReadTuple[1].D() ;
		}
		catch (...)
		{
			OutputDebugString(_T("Function(CommunicationRead_SetConfigurePath) Load Configure is Error")) ;
			CloseFile(hFileHandle) ;
			return E_VCODE_NG;
		}

		m_strSavePath = strLoadPath ;

		OutputDebugString(_T("Function(CommunicationRead_LoadConfigure) End")) ;
		return E_VCODE_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(CommunicationRead_LoadConfigure) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionCommReadInterface::Vision_SetConfigurePath(const char* pSavePath)
{
	try
	{
		OutputDebugString(_T("Function(CommunicationRead_SetConfigurePath) Start")) ;

		if (NULL == pSavePath)
		{
			OutputDebugString(_T("Function(CommunicationRead_SetConfigurePath) pSavePath is Empty")) ;
			return E_VCODE_NG ;
		}

		m_strSavePath = pSavePath ;

		OutputDebugString(_T("Function(CommunicationRead_SetConfigurePath) End")) ;
		return E_VCODE_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(CommunicationRead_SetConfigurePath) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionCommReadInterface::Vision_ShowDialog()
{
	try
	{
		OutputDebugString(_T("Function(CommunicationRead_ShowDialog) Start")) ;

		//必须添加AFX_MANAGE_STATE(AfxGetStaticModuleState()) 不然对话框不显示
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		CMainDlg mainDlg;
		mainDlg.m_strSavePath = m_strSavePath ;
		mainDlg.m_strCommInfo = m_strCommInfo ;
		mainDlg.m_pCommunicationNode = m_pCommunicationNode ;
		mainDlg.m_para1Dlg.m_dbWaitTime = m_dbWaitTime ;
		if (IDOK == mainDlg.DoModal())
		{
			m_dbWaitTime = mainDlg.m_para1Dlg.m_dbWaitTime ;
		}

		OutputDebugString(_T("Function(CommunicationRead_ShowDialog) End")) ;
		return E_VCODE_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(CommunicationRead_ShowDialog) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionCommReadInterface::Vision_Run(HTuple hWindowID)
{
	try
	{
		OutputDebugString(_T("Function(CommunicationRead_Run) Start")) ;

		if (NULL == m_pCommunicationNode)
		{
			OutputDebugString(_T("Function(CommunicationRead_Run) Comm Point is Empty")) ;
			return E_VCODE_NG ;
		}

		m_strReadData = _T("") ;

		DWORD dwWaitTime = m_dbWaitTime * 1000.0 ;
		string strRecData("") ;
		bool bRecieveRet = false ;
		DWORD dwStartTime, dwEndTime ;
		DWORD dwSpend = 0;
		dwStartTime = ::GetTickCount() ;

		while (1)
		{
			if (E_COMM_OK != m_pCommunicationNode->pCommunicationBase->Comm_RevData(strRecData))
			{
				OutputDebugString(_T("Function(CommunicationRead_Run) Comm RevData Err")) ;
				break ;
			}
			if (strRecData.length() > 0)
			{
				bRecieveRet = true ;
				break;
			}

			dwEndTime = GetTickCount() ;
			dwSpend = dwEndTime - dwStartTime ;
			if (dwSpend >= dwWaitTime)
			{
				bRecieveRet = false ;
				break ;
			}

			Sleep ( 10 );
			::DoEvent();
		}

		if (!bRecieveRet)
		{
			OutputDebugString(_T("Function(CommunicationRead_Run) Comm RevData is Empty in the limit time")) ;
			return E_VCODE_NG ;
		}

		m_strReadData = strRecData.c_str() ;

		OutputDebugString(_T("Function(CommunicationRead_Run) End")) ;
		return E_VCODE_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(CommunicationRead_Run) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionCommReadInterface::Vision_Input(vector<any> vecInput)
{
	USES_CONVERSION ;
	try
	{
		OutputDebugString(_T("Function(CommunicationRead_Input) Start")) ;

		int nInputPara = vecInput.size() ;
		if (nInputPara != 2)
		{
			OutputDebugString(_T("Function(CommunicationRead_Input) Input Params size error")) ;
			return E_VCODE_NG ;
		}

		any aValue =  vecInput[0] ;
		if (aValue.type() == typeid(VString))
		{
			string strValue = any_cast<VString>(aValue).vStr ;
			m_strCommInfo = strValue.c_str() ;
		}
		else
		{
			OutputDebugString(_T("Function(CommunicationRead_Input) Input Params[0] type error")) ;
			return E_VCODE_NG ;
		}

		aValue = vecInput[1] ;
		if (aValue.type() == typeid(CCommunicationNode *))
		{
			m_pCommunicationNode = any_cast<CCommunicationNode *>(aValue);
		}
		else
		{
			OutputDebugString(_T("Function(CommunicationRead_Input) Input Params[1] type error")) ;
			return E_VCODE_NG ;
		}

		OutputDebugString(_T("Function(CommunicationRead_Input) End")) ;
		return E_VCODE_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(CommunicationRead_Input) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionCommReadInterface::Vision_Output(vector<any> &vecOutput)
{
	USES_CONVERSION ;
	try
	{
		OutputDebugString(_T("Function(CommunicationRead_Output) Start")) ;

		vecOutput.clear() ;
		if (m_strReadData.IsEmpty())
		{
			OutputDebugString(_T("Function(CommunicationRead_Output) Comm output data is empty")) ;
			return E_VCODE_NG ;
		}

		VString strOutData ;
		strOutData.vStr = W2A(m_strReadData) ;
		vecOutput.push_back(strOutData) ;

		OutputDebugString(_T("Function(CommunicationRead_Output) End")) ;
		return E_VCODE_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(CommunicationRead_Output) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionCommReadInterface::Vision_GetDisFeature(vector<any> &vecDisplayFeature)
{
	try
	{
		OutputDebugString(_T("Function(CommunicationRead_GetDisFeature) Start")) ;

		OutputDebugString(_T("Function(CommunicationRead_GetDisFeature) End")) ;
		return E_VCODE_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(CommunicationRead_GetDisFeature) Throw")) ;
		return E_VCODE_THROW ;
	}
}