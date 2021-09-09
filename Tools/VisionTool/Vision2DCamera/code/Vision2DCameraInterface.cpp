#include "StdAfx.h"
#include "Vision2DCameraInterface.h"
#include "MainDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CVision2DCameraInterface::CVision2DCameraInterface(void)
{
	m_pCameraNode = NULL ;
}

CVision2DCameraInterface::~CVision2DCameraInterface(void)
{
}

VISION_CODE CVision2DCameraInterface::Vision_Init()
{
	try
	{
		OutputDebugString(_T("Function(2DCamera_Init) Start")) ;

		if (NULL == m_pCameraNode)
		{
			OutputDebugString(_T("Function(2DCamera_Init) Camera Point is Empty")) ;
			return E_VCODE_NG ;
		}

		GenEmptyObj(&m_hImage) ;

		m_pCameraNode->pCameraBase->Camera_GetExposureTime(m_lExposureTime) ;
		m_pCameraNode->pCameraBase->Camera_GetGain(m_lGain) ;

		OutputDebugString(_T("Function(2DCamera_Init) End")) ;
		return E_VCODE_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(2DCamera_Init) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVision2DCameraInterface::Vision_Release()
{
	try
	{
		OutputDebugString(_T("Function(2DCamera_Release) Start")) ;

		//设备指针不能在这里进行释放

		OutputDebugString(_T("Function(2DCamera_Release) End")) ;
		return E_VCODE_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(2DCamera_Release) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVision2DCameraInterface::Vision_SetLanguage(int nLanguage)
{
	try
	{
		OutputDebugString(_T("Function(2DCamera_SetLanguage) Start")) ;

		OutputDebugString(_T("Function(2DCamera_SetLanguage) End")) ;
		return E_VCODE_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(2DCamera_SetLanguage) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVision2DCameraInterface::Vision_LoadConfigure(const char* pLoadPath)
{
	try
	{
		OutputDebugString(_T("Function(2DCamera_LoadConfigure) Start")) ;

		if (NULL == pLoadPath)
		{
			OutputDebugString(_T("Function(2DCamera_SetConfigurePath) pLoadPath is Empty")) ;
			return E_VCODE_NG ;
		}
		CString strLoadPath(pLoadPath)  ;
		if (!vFileIsExist(strLoadPath))
		{
			OutputDebugString(_T("Function(2DCamera_SetConfigurePath) pLoadFile is not Exist")) ;
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

			if (0 != (HTuple(hReadTuple[0])!=HTuple("Vision2DCamera")))
			{
				OutputDebugString(_T("Function(2DCamera_SetConfigurePath) Load Configure is Error")) ;
				return E_VCODE_NG;
			}

			m_lExposureTime = hReadTuple[1].L() ;
			m_lGain = hReadTuple[2].L() ;
		}
		catch (...)
		{
			OutputDebugString(_T("Function(2DCamera_SetConfigurePath) Load Configure is Error")) ;
			CloseFile(hFileHandle) ;
			return E_VCODE_NG;
		}

		m_strSavePath = strLoadPath ;

		OutputDebugString(_T("Function(2DCamera_LoadConfigure) End")) ;
		return E_VCODE_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(2DCamera_LoadConfigure) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVision2DCameraInterface::Vision_SetConfigurePath(const char* pSavePath)
{
	try
	{
		OutputDebugString(_T("Function(2DCamera_SetConfigurePath) Start")) ;

		if (NULL == pSavePath)
		{
			OutputDebugString(_T("Function(2DCamera_SetConfigurePath) pSavePath is Empty")) ;
			return E_VCODE_NG ;
		}

		m_strSavePath = pSavePath ;

		OutputDebugString(_T("Function(2DCamera_SetConfigurePath) End")) ;
		return E_VCODE_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(2DCamera_SetConfigurePath) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVision2DCameraInterface::Vision_ShowDialog()
{
	try
	{
		OutputDebugString(_T("Function(2DCamera_ShowDialog) Start")) ;

		//必须添加AFX_MANAGE_STATE(AfxGetStaticModuleState()) 不然对话框不显示
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		CMainDlg mainDlg;
		mainDlg.m_strCameraInfo = m_strCameraInfo ;
		mainDlg.m_strSavePath = m_strSavePath ;
		mainDlg.m_pCameraNode = m_pCameraNode ;
		mainDlg.m_para1Dlg.m_lExposureTime = m_lExposureTime ;
		mainDlg.m_para1Dlg.m_lGain = m_lGain ;
		if (IDOK == mainDlg.DoModal())
		{
		}

		OutputDebugString(_T("Function(2DCamera_ShowDialog) End")) ;
		return E_VCODE_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(2DCamera_ShowDialog) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVision2DCameraInterface::Vision_Run(HTuple hWindowID)
{
	try
	{
		OutputDebugString(_T("Function(2DCamera_Run) Start")) ;

		if (NULL == m_pCameraNode)
		{
			OutputDebugString(_T("Function(2DCamera_Run) Camera Point is Empty")) ;
			return E_VCODE_NG ;
		}

		GenEmptyObj(&m_hImage) ;
		if (E_CAMERA_OK != m_pCameraNode->pCameraBase->Camera_GrabOne(&m_hImage))
		{
			OutputDebugString(_T("Function(2DCamera_Run) Camera GrabOne Fail")) ;
			return E_VCODE_NG ;
		}

		OutputDebugString(_T("Function(2DCamera_Run) End")) ;
		return E_VCODE_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(2DCamera_Run) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVision2DCameraInterface::Vision_Input(vector<any> vecInput)
{
	USES_CONVERSION ;
	try
	{
		OutputDebugString(_T("Function(2DCamera_Input) Start")) ;

		int nInputPara = vecInput.size() ;
		if (nInputPara != 4)
		{
			OutputDebugString(_T("Function(2DCamera_Input) Input Params size error")) ;
			return E_VCODE_NG ;
		}

		any aValue =  vecInput[0] ;
		if (aValue.type() == typeid(VString))
		{
			string strValue = any_cast<VString>(aValue).vStr ;
			m_strCameraInfo = strValue.c_str() ;
		}
		else
		{
			OutputDebugString(_T("Function(2DCamera_Input) Input Params[0] type error")) ;
			return E_VCODE_NG ;
		}

		aValue = vecInput[1] ;
		if (aValue.type() == typeid(long))
		{
			m_lExposureTime = any_cast<long>(aValue);
			/*CString strInfo ;
			strInfo.Format(_T("%d"),m_lExposureTime) ;
			OutputDebugString(strInfo) ;
			OutputDebugString(_T("Function(2DCamera_Input) End")) ;*/
		}
		else
		{
			OutputDebugString(_T("Function(2DCamera_Input) Input Params[1] type error")) ;
			return E_VCODE_NG ;
		}

		aValue = vecInput[2] ;
		if (aValue.type() == typeid(long))
		{
			m_lGain = any_cast<long>(aValue);
			/*CString strInfo ;
			strInfo.Format(_T("%d"),m_lGain) ;
			OutputDebugString(strInfo) ;
			OutputDebugString(_T("Function(2DCamera_Input) End")) ;*/
		}
		else
		{
			OutputDebugString(_T("Function(2DCamera_Input) Input Params[2] type error")) ;
			return E_VCODE_NG ;
		}

		aValue = vecInput[3] ;
		if (aValue.type() == typeid(CCameraNode*))
		{
			m_pCameraNode = any_cast<CCameraNode*>(aValue);
			OutputDebugString(_T("Function(2DCamera_Input) End")) ;
		}
		else
		{
			OutputDebugString(_T("Function(2DCamera_Input) Input Params[3] type error")) ;
			return E_VCODE_NG ;
		}

		/*HObject hImage ;
		static int nId = 0 ;
		CString strInfo(_T("")) ;
		strInfo.Format(_T("D:\\boost%d.bmp"),nId++) ;
		m_pCameraNode->pCameraBase->Camera_GrabOne(&hImage) ;
		WriteImage(hImage,"bmp",0,W2A(strInfo)) ;*/

		OutputDebugString(_T("Function(2DCamera_Input) End")) ;
		return E_VCODE_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(2DCamera_Input) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVision2DCameraInterface::Vision_Output(vector<any> &vecOutput)
{
	try
	{
		OutputDebugString(_T("Function(2DCamera_Output) Start")) ;

		vecOutput.clear() ;
		if (!m_hImage.IsInitialized())
		{
			OutputDebugString(_T("Function(2DCamera_Output) Image is not Init")) ;
			return E_VCODE_NG ;
		}

		VImage image ;
		image.vImage = m_hImage ;
		vecOutput.push_back(image) ;

		OutputDebugString(_T("Function(2DCamera_Output) End")) ;
		return E_VCODE_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(2DCamera_Output) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVision2DCameraInterface::Vision_GetDisFeature(vector<any> &vecDisplayFeature)
{
	try
	{
		OutputDebugString(_T("Function(2DCamera_GetDisFeature) Start")) ;

		OutputDebugString(_T("Function(2DCamera_GetDisFeature) End")) ;
		return E_VCODE_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(2DCamera_GetDisFeature) Throw")) ;
		return E_VCODE_THROW ;
	}
}