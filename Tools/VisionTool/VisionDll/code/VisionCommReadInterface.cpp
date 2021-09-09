#include "StdAfx.h"
#include "VisionCommReadInterface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CVisionCommReadInterface::CVisionCommReadInterface(void)
{
	::InitializeCriticalSection(&m_Critical);
	m_pVisionCommReadBase = NULL ;
	m_bInitOk = false ;
	m_dllVisionCommReadIm.DllCreateInterface((int)E_TOOL_VISIONSYSTEM_COMMREAD,(void **)&m_pVisionCommReadBase) ;
	if (m_pVisionCommReadBase)
		m_bInitOk = true ;
}

CVisionCommReadInterface::~CVisionCommReadInterface(void)
{
	::DeleteCriticalSection(&m_Critical);
}

VISION_CODE CVisionCommReadInterface:: Vision_Init()
{
	try
	{
		OutputDebugString(_T("Function(CommReadVision_Init) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_VCODE_NG ;

		OutputDebugString(_T("Function(CommReadVision_Init) End")) ;

		return m_pVisionCommReadBase->Vision_Init() ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(CommReadVision_Init) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionCommReadInterface:: Vision_Release()
{
	try
	{
		OutputDebugString(_T("Function(CommReadVision_Release) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_VCODE_NG ;

		OutputDebugString(_T("Function(CommReadVision_Release) End")) ;

		return m_pVisionCommReadBase->Vision_Release() ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(CommReadVision_Release) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionCommReadInterface:: Vision_SetLanguage(int nLanguage)
{
	try
	{
		OutputDebugString(_T("Function(CommReadVision_SetLanguage) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_VCODE_NG ;

		OutputDebugString(_T("Function(CommReadVision_SetLanguage) End")) ;

		return m_pVisionCommReadBase->Vision_SetLanguage(nLanguage) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(CommReadVision_SetLanguage) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionCommReadInterface:: Vision_LoadConfigure(const char* pLoadPath)
{
	try
	{
		OutputDebugString(_T("Function(CommReadVision_LoadConfigure) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_VCODE_NG ;

		OutputDebugString(_T("Function(CommReadVision_LoadConfigure) End")) ;

		return m_pVisionCommReadBase->Vision_LoadConfigure(pLoadPath) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(CommReadVision_LoadConfigure) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionCommReadInterface:: Vision_SetConfigurePath(const char* pSavePath)
{
	try
	{
		OutputDebugString(_T("Function(CommReadVision_SetConfigurePath) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_VCODE_NG ;

		OutputDebugString(_T("Function(CommReadVision_SetConfigurePath) End")) ;

		return m_pVisionCommReadBase->Vision_SetConfigurePath(pSavePath) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(CommReadVision_SetConfigurePath) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionCommReadInterface:: Vision_ShowDialog()
{
	try
	{
		OutputDebugString(_T("Function(CommReadVision_ShowDialog) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_VCODE_NG ;

		OutputDebugString(_T("Function(CommReadVision_ShowDialog) End")) ;

		return m_pVisionCommReadBase->Vision_ShowDialog() ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(CommReadVision_ShowDialog) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionCommReadInterface:: Vision_Run(HTuple hWindowID)
{
	try
	{
		OutputDebugString(_T("Function(CommReadVision_Run) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_VCODE_NG ;

		OutputDebugString(_T("Function(CommReadVision_Run) End")) ;

		return m_pVisionCommReadBase->Vision_Run(hWindowID) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(CommReadVision_Run) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionCommReadInterface:: Vision_Input(vector<any> vecInput)
{
	try
	{
		OutputDebugString(_T("Function(CommReadVision_Input) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_VCODE_NG ;

		OutputDebugString(_T("Function(CommReadVision_Input) End")) ;

		return m_pVisionCommReadBase->Vision_Input(vecInput) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(CommReadVision_Input) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionCommReadInterface:: Vision_Output(vector<any> &vecOutput)
{
	try
	{
		OutputDebugString(_T("Function(CommReadVision_Output) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_VCODE_NG ;

		OutputDebugString(_T("Function(CommReadVision_Output) End")) ;

		return m_pVisionCommReadBase->Vision_Output(vecOutput) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(CommReadVision_Output) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionCommReadInterface:: Vision_GetDisFeature(vector<any> &vecDisplayFeature)
{
	try
	{
		OutputDebugString(_T("Function(CommReadVision_GetDisFeature) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_VCODE_NG ;

		OutputDebugString(_T("Function(CommReadVision_GetDisFeature) End")) ;

		return m_pVisionCommReadBase->Vision_GetDisFeature(vecDisplayFeature) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(CommReadVision_GetDisFeature) Throw")) ;
		return E_VCODE_THROW ;
	}
}