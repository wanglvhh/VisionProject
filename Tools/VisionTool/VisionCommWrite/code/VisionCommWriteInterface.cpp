#include "StdAfx.h"
#include "VisionCommWriteInterface.h"
#include "MainDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CVisionCommWriteInterface::CVisionCommWriteInterface(void)
{
	m_pCommunicationNode = NULL ;
	m_strSendData = _T("") ;
	m_strCommInfo = _T("") ;
	m_pCommunicationNode = NULL ;
}

CVisionCommWriteInterface::~CVisionCommWriteInterface(void)
{
}

VISION_CODE CVisionCommWriteInterface::Vision_Init()
{
	try
	{
		OutputDebugString(_T("Function(CommunicationWrite_Init) Start")) ;

		if (NULL == m_pCommunicationNode)
		{
			OutputDebugString(_T("Function(CommunicationWrite_Init) Camera Point is Empty")) ;
			return E_VCODE_NG ;
		}

		OutputDebugString(_T("Function(CommunicationWrite_Init) End")) ;
		return E_VCODE_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(CommunicationWrite_Init) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionCommWriteInterface::Vision_Release()
{
	try
	{
		OutputDebugString(_T("Function(CommunicationWrite_Release) Start")) ;

		//通信指针不能在这里进行释放

		OutputDebugString(_T("Function(CommunicationWrite_Release) End")) ;
		return E_VCODE_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(CommunicationWrite_Release) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionCommWriteInterface::Vision_SetLanguage(int nLanguage)
{
	try
	{
		OutputDebugString(_T("Function(CommunicationWrite_SetLanguage) Start")) ;

		OutputDebugString(_T("Function(CommunicationWrite_SetLanguage) End")) ;
		return E_VCODE_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(CommunicationWrite_SetLanguage) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionCommWriteInterface::Vision_LoadConfigure(const char* pLoadPath)
{
	try
	{
		OutputDebugString(_T("Function(CommunicationWrite_LoadConfigure) Start")) ;

		if (NULL == pLoadPath)
		{
			OutputDebugString(_T("Function(CommunicationWrite_SetConfigurePath) pLoadPath is Empty")) ;
			return E_VCODE_NG ;
		}
		CString strLoadPath(pLoadPath)  ;
		if (!vFileIsExist(strLoadPath))
		{
			OutputDebugString(_T("Function(CommunicationWrite_SetConfigurePath) pLoadFile is not Exist")) ;
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

			if (0 != (HTuple(hReadTuple[0])!=HTuple("VisionSystemCommunicationWrite")))
			{
				OutputDebugString(_T("Function(CommunicationWrite_SetConfigurePath) Load Configure is Error")) ;
				return E_VCODE_NG;
			}

			m_strSendData = hReadTuple[1].S() ;
		}
		catch (...)
		{
			OutputDebugString(_T("Function(CommunicationWrite_SetConfigurePath) Load Configure is Error")) ;
			CloseFile(hFileHandle) ;
			return E_VCODE_NG;
		}

		m_strSavePath = strLoadPath ;

		OutputDebugString(_T("Function(CommunicationWrite_LoadConfigure) End")) ;
		return E_VCODE_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(CommunicationWrite_LoadConfigure) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionCommWriteInterface::Vision_SetConfigurePath(const char* pSavePath)
{
	try
	{
		OutputDebugString(_T("Function(CommunicationWrite_SetConfigurePath) Start")) ;

		if (NULL == pSavePath)
		{
			OutputDebugString(_T("Function(CommunicationWrite_SetConfigurePath) pSavePath is Empty")) ;
			return E_VCODE_NG ;
		}

		m_strSavePath = pSavePath ;

		OutputDebugString(_T("Function(CommunicationWrite_SetConfigurePath) End")) ;
		return E_VCODE_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(CommunicationWrite_SetConfigurePath) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionCommWriteInterface::Vision_ShowDialog()
{
	try
	{
		OutputDebugString(_T("Function(CommunicationWrite_ShowDialog) Start")) ;

		//必须添加AFX_MANAGE_STATE(AfxGetStaticModuleState()) 不然对话框不显示
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		CMainDlg mainDlg;
		mainDlg.m_strSavePath = m_strSavePath ;
		mainDlg.m_strCommInfo = m_strCommInfo ;
		mainDlg.m_pCommunicationNode = m_pCommunicationNode ;
		mainDlg.m_para1Dlg.m_strSendData = m_strSendData ;
		if (IDOK == mainDlg.DoModal())
		{
			m_strSendData = mainDlg.m_para1Dlg.m_strSendData ;
		}

		OutputDebugString(_T("Function(CommunicationWrite_ShowDialog) End")) ;
		return E_VCODE_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(CommunicationWrite_ShowDialog) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionCommWriteInterface::Vision_Run(HTuple hWindowID)
{
	USES_CONVERSION ;
	try
	{
		OutputDebugString(_T("Function(CommunicationWrite_Run) Start")) ;

		if (NULL == m_pCommunicationNode)
		{
			OutputDebugString(_T("Function(CommunicationWrite_Run) Comm Point is Empty")) ;
			return E_VCODE_NG ;
		}

		m_pCommunicationNode->pCommunicationBase->Comm_SendData(W2A(m_strSendData)) ;

		OutputDebugString(_T("Function(CommunicationWrite_Run) End")) ;
		return E_VCODE_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(CommunicationWrite_Run) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionCommWriteInterface::Vision_Input(vector<any> vecInput)
{
	USES_CONVERSION ;
	try
	{
		OutputDebugString(_T("Function(CommunicationWrite_Input) Start")) ;

		int nInputPara = vecInput.size() ;
		if (nInputPara != 2)
		{
			OutputDebugString(_T("Function(CommunicationWrite_Input) Input Params size error")) ;
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
			OutputDebugString(_T("Function(CommunicationWrite_Input) Input Params[0] type error")) ;
			return E_VCODE_NG ;
		}

		aValue = vecInput[1] ;
		if (aValue.type() == typeid(CCommunicationNode *))
		{
			m_pCommunicationNode = any_cast<CCommunicationNode *>(aValue);
		}
		else
		{
			OutputDebugString(_T("Function(CommunicationWrite_Input) Input Params[1] type error")) ;
			return E_VCODE_NG ;
		}

		OutputDebugString(_T("Function(CommunicationWrite_Input) End")) ;
		return E_VCODE_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(CommunicationWrite_Input) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionCommWriteInterface::Vision_Output(vector<any> &vecOutput)
{
	USES_CONVERSION ;
	try
	{
		OutputDebugString(_T("Function(CommunicationWrite_Output) Start")) ;

		vecOutput.clear() ;
		/*if (m_strReadData.IsEmpty())
		{
		OutputDebugString(_T("Function(CommunicationWrite_Output) Comm output data is empty")) ;
		return E_VCODE_NG ;
		}

		VString strOutData ;
		strOutData.vStr = W2A(m_strReadData) ;
		vecOutput.push_back(strOutData) ;*/

		OutputDebugString(_T("Function(CommunicationWrite_Output) End")) ;
		return E_VCODE_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(CommunicationWrite_Output) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionCommWriteInterface::Vision_GetDisFeature(vector<any> &vecDisplayFeature)
{
	try
	{
		OutputDebugString(_T("Function(CommunicationWrite_GetDisFeature) Start")) ;

		OutputDebugString(_T("Function(CommunicationWrite_GetDisFeature) End")) ;
		return E_VCODE_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(CommunicationWrite_GetDisFeature) Throw")) ;
		return E_VCODE_THROW ;
	}
}