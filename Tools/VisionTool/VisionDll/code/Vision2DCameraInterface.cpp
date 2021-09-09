#include "StdAfx.h"
#include "Vision2DCameraInterface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CVision2DCameraInterface::CVision2DCameraInterface(void)
{
	::InitializeCriticalSection(&m_Critical);
	m_pVision2DCameraBase = NULL ;
	m_bInitOk = false ;
	m_dllVision2DCameraIm.DllCreateInterface((int)E_TOOL_2DVISION_CAMERA,(void **)&m_pVision2DCameraBase) ;
	if (m_pVision2DCameraBase)
		m_bInitOk = true ;
}

CVision2DCameraInterface::~CVision2DCameraInterface(void)
{
	::DeleteCriticalSection(&m_Critical);
}

VISION_CODE CVision2DCameraInterface:: Vision_Init()
{
	try
	{
		OutputDebugString(_T("Function(2DCameraVision_Init) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_VCODE_NG ;

		OutputDebugString(_T("Function(2DCameraVision_Init) End")) ;

		return m_pVision2DCameraBase->Vision_Init() ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(2DCameraVision_Init) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVision2DCameraInterface:: Vision_Release()
{
	try
	{
		OutputDebugString(_T("Function(2DCameraVision_Release) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_VCODE_NG ;

		OutputDebugString(_T("Function(2DCameraVision_Release) End")) ;

		return m_pVision2DCameraBase->Vision_Release() ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(2DCameraVision_Release) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVision2DCameraInterface:: Vision_SetLanguage(int nLanguage)
{
	try
	{
		OutputDebugString(_T("Function(2DCameraVision_SetLanguage) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_VCODE_NG ;

		OutputDebugString(_T("Function(2DCameraVision_SetLanguage) End")) ;

		return m_pVision2DCameraBase->Vision_SetLanguage(nLanguage) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(2DCameraVision_SetLanguage) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVision2DCameraInterface:: Vision_LoadConfigure(const char* pLoadPath)
{
	try
	{
		OutputDebugString(_T("Function(2DCameraVision_LoadConfigure) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_VCODE_NG ;

		OutputDebugString(_T("Function(2DCameraVision_LoadConfigure) End")) ;

		return m_pVision2DCameraBase->Vision_LoadConfigure(pLoadPath) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(2DCameraVision_LoadConfigure) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVision2DCameraInterface:: Vision_SetConfigurePath(const char* pSavePath)
{
	try
	{
		OutputDebugString(_T("Function(2DCameraVision_SetConfigurePath) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_VCODE_NG ;

		OutputDebugString(_T("Function(2DCameraVision_SetConfigurePath) End")) ;

		return m_pVision2DCameraBase->Vision_SetConfigurePath(pSavePath) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(2DCameraVision_SetConfigurePath) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVision2DCameraInterface:: Vision_ShowDialog()
{
	try
	{
		OutputDebugString(_T("Function(2DCameraVision_ShowDialog) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_VCODE_NG ;

		OutputDebugString(_T("Function(2DCameraVision_ShowDialog) End")) ;

		return m_pVision2DCameraBase->Vision_ShowDialog() ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(2DCameraVision_ShowDialog) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVision2DCameraInterface:: Vision_Run(HTuple hWindowID)
{
	try
	{
		OutputDebugString(_T("Function(2DCameraVision_Run) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_VCODE_NG ;

		OutputDebugString(_T("Function(2DCameraVision_Run) End")) ;

		return m_pVision2DCameraBase->Vision_Run(hWindowID) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(2DCameraVision_Run) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVision2DCameraInterface:: Vision_Input(vector<any> vecInput)
{
	try
	{
		OutputDebugString(_T("Function(2DCameraVision_Input) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_VCODE_NG ;

		OutputDebugString(_T("Function(2DCameraVision_Input) End")) ;

		return m_pVision2DCameraBase->Vision_Input(vecInput) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(2DCameraVision_Input) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVision2DCameraInterface:: Vision_Output(vector<any> &vecOutput)
{
	try
	{
		OutputDebugString(_T("Function(2DCameraVision_Output) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_VCODE_NG ;

		OutputDebugString(_T("Function(2DCameraVision_Output) End")) ;

		return m_pVision2DCameraBase->Vision_Output(vecOutput) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(2DCameraVision_Output) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVision2DCameraInterface:: Vision_GetDisFeature(vector<any> &vecDisplayFeature)
{
	try
	{
		OutputDebugString(_T("Function(2DCameraVision_GetDisFeature) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_VCODE_NG ;

		OutputDebugString(_T("Function(2DCameraVision_GetDisFeature) End")) ;

		return m_pVision2DCameraBase->Vision_GetDisFeature(vecDisplayFeature) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(2DCameraVision_GetDisFeature) Throw")) ;
		return E_VCODE_THROW ;
	}
}