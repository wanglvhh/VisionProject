#include "StdAfx.h"
#include "VisionFitLineInterface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CVisionFitLineInterface::CVisionFitLineInterface(void)
{
	::InitializeCriticalSection(&m_Critical);
	m_pVisionFitLineBase = NULL ;
	m_bInitOk = false ;
	m_dllVisionFitLineIm.DllCreateInterface((int)E_TOOL_2DVISION_FITLINE,(void **)&m_pVisionFitLineBase) ;
	if (m_pVisionFitLineBase)
		m_bInitOk = true ;
}

CVisionFitLineInterface::~CVisionFitLineInterface(void)
{
	::DeleteCriticalSection(&m_Critical);
}

VISION_CODE CVisionFitLineInterface:: Vision_Init()
{
	try
	{
		OutputDebugString(_T("Function(FitLineVision_Init) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_VCODE_NG ;

		OutputDebugString(_T("Function(FitLineVision_Init) End")) ;

		return m_pVisionFitLineBase->Vision_Init() ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(FitLineVision_Init) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionFitLineInterface:: Vision_Release()
{
	try
	{
		OutputDebugString(_T("Function(FitLineVision_Release) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_VCODE_NG ;

		OutputDebugString(_T("Function(FitLineVision_Release) End")) ;

		return m_pVisionFitLineBase->Vision_Release() ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(FitLineVision_Release) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionFitLineInterface:: Vision_SetLanguage(int nLanguage)
{
	try
	{
		OutputDebugString(_T("Function(FitLineVision_SetLanguage) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_VCODE_NG ;

		OutputDebugString(_T("Function(FitLineVision_SetLanguage) End")) ;

		return m_pVisionFitLineBase->Vision_SetLanguage(nLanguage) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(FitLineVision_SetLanguage) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionFitLineInterface:: Vision_LoadConfigure(const char* pLoadPath)
{
	try
	{
		OutputDebugString(_T("Function(FitLineVision_LoadConfigure) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_VCODE_NG ;

		OutputDebugString(_T("Function(FitLineVision_LoadConfigure) End")) ;

		return m_pVisionFitLineBase->Vision_LoadConfigure(pLoadPath) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(FitLineVision_LoadConfigure) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionFitLineInterface:: Vision_SetConfigurePath(const char* pSavePath)
{
	try
	{
		OutputDebugString(_T("Function(FitLineVision_SetConfigurePath) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_VCODE_NG ;

		OutputDebugString(_T("Function(FitLineVision_SetConfigurePath) End")) ;

		return m_pVisionFitLineBase->Vision_SetConfigurePath(pSavePath) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(FitLineVision_SetConfigurePath) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionFitLineInterface:: Vision_ShowDialog()
{
	try
	{
		OutputDebugString(_T("Function(FitLineVision_ShowDialog) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_VCODE_NG ;

		OutputDebugString(_T("Function(FitLineVision_ShowDialog) End")) ;

		return m_pVisionFitLineBase->Vision_ShowDialog() ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(FitLineVision_ShowDialog) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionFitLineInterface:: Vision_Run(HTuple hWindowID)
{
	try
	{
		OutputDebugString(_T("Function(FitLineVision_Run) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_VCODE_NG ;

		OutputDebugString(_T("Function(FitLineVision_Run) End")) ;

		return m_pVisionFitLineBase->Vision_Run(hWindowID) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(FitLineVision_Run) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionFitLineInterface:: Vision_Input(vector<any> vecInput)
{
	try
	{
		OutputDebugString(_T("Function(FitLineVision_Input) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_VCODE_NG ;

		OutputDebugString(_T("Function(FitLineVision_Input) End")) ;

		return m_pVisionFitLineBase->Vision_Input(vecInput) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(FitLineVision_Input) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionFitLineInterface:: Vision_Output(vector<any> &vecOutput)
{
	try
	{
		OutputDebugString(_T("Function(FitLineVision_Output) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_VCODE_NG ;

		OutputDebugString(_T("Function(FitLineVision_Output) End")) ;

		return m_pVisionFitLineBase->Vision_Output(vecOutput) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(FitLineVision_Output) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionFitLineInterface:: Vision_GetDisFeature(vector<any> &vecDisplayFeature)
{
	try
	{
		OutputDebugString(_T("Function(FitLineVision_GetDisFeature) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_VCODE_NG ;

		OutputDebugString(_T("Function(FitLineVision_GetDisFeature) End")) ;

		return m_pVisionFitLineBase->Vision_GetDisFeature(vecDisplayFeature) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(FitLineVision_GetDisFeature) Throw")) ;
		return E_VCODE_THROW ;
	}
}