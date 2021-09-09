#include "StdAfx.h"
#include "VisionCommWriteInterface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CVisionCommWriteInterface::CVisionCommWriteInterface(void)
{
	::InitializeCriticalSection(&m_Critical);
	m_pVisionCommWriteBase = NULL ;
	m_bInitOk = false ;
	m_dllVisionCommWriteIm.DllCreateInterface((int)E_TOOL_VISIONSYSTEM_COMMWRITE,(void **)&m_pVisionCommWriteBase) ;
	if (m_pVisionCommWriteBase)
		m_bInitOk = true ;
}

CVisionCommWriteInterface::~CVisionCommWriteInterface(void)
{
	::DeleteCriticalSection(&m_Critical);
}

VISION_CODE CVisionCommWriteInterface:: Vision_Init()
{
	try
	{
		OutputDebugString(_T("Function(CommWriteVision_Init) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_VCODE_NG ;

		OutputDebugString(_T("Function(CommWriteVision_Init) End")) ;

		return m_pVisionCommWriteBase->Vision_Init() ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(CommWriteVision_Init) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionCommWriteInterface:: Vision_Release()
{
	try
	{
		OutputDebugString(_T("Function(CommWriteVision_Release) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_VCODE_NG ;

		OutputDebugString(_T("Function(CommWriteVision_Release) End")) ;

		return m_pVisionCommWriteBase->Vision_Release() ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(CommWriteVision_Release) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionCommWriteInterface:: Vision_SetLanguage(int nLanguage)
{
	try
	{
		OutputDebugString(_T("Function(CommWriteVision_SetLanguage) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_VCODE_NG ;

		OutputDebugString(_T("Function(CommWriteVision_SetLanguage) End")) ;

		return m_pVisionCommWriteBase->Vision_SetLanguage(nLanguage) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(CommWriteVision_SetLanguage) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionCommWriteInterface:: Vision_LoadConfigure(const char* pLoadPath)
{
	try
	{
		OutputDebugString(_T("Function(CommWriteVision_LoadConfigure) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_VCODE_NG ;

		OutputDebugString(_T("Function(CommWriteVision_LoadConfigure) End")) ;

		return m_pVisionCommWriteBase->Vision_LoadConfigure(pLoadPath) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(CommWriteVision_LoadConfigure) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionCommWriteInterface:: Vision_SetConfigurePath(const char* pSavePath)
{
	try
	{
		OutputDebugString(_T("Function(CommWriteVision_SetConfigurePath) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_VCODE_NG ;

		OutputDebugString(_T("Function(CommWriteVision_SetConfigurePath) End")) ;

		return m_pVisionCommWriteBase->Vision_SetConfigurePath(pSavePath) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(CommWriteVision_SetConfigurePath) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionCommWriteInterface:: Vision_ShowDialog()
{
	try
	{
		OutputDebugString(_T("Function(CommWriteVision_ShowDialog) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_VCODE_NG ;

		OutputDebugString(_T("Function(CommWriteVision_ShowDialog) End")) ;

		return m_pVisionCommWriteBase->Vision_ShowDialog() ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(CommWriteVision_ShowDialog) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionCommWriteInterface:: Vision_Run(HTuple hWindowID)
{
	try
	{
		OutputDebugString(_T("Function(CommWriteVision_Run) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_VCODE_NG ;

		OutputDebugString(_T("Function(CommWriteVision_Run) End")) ;

		return m_pVisionCommWriteBase->Vision_Run(hWindowID) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(CommWriteVision_Run) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionCommWriteInterface:: Vision_Input(vector<any> vecInput)
{
	try
	{
		OutputDebugString(_T("Function(CommWriteVision_Input) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_VCODE_NG ;

		OutputDebugString(_T("Function(CommWriteVision_Input) End")) ;

		return m_pVisionCommWriteBase->Vision_Input(vecInput) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(CommWriteVision_Input) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionCommWriteInterface:: Vision_Output(vector<any> &vecOutput)
{
	try
	{
		OutputDebugString(_T("Function(CommWriteVision_Output) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_VCODE_NG ;

		OutputDebugString(_T("Function(CommWriteVision_Output) End")) ;

		return m_pVisionCommWriteBase->Vision_Output(vecOutput) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(CommWriteVision_Output) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionCommWriteInterface:: Vision_GetDisFeature(vector<any> &vecDisplayFeature)
{
	try
	{
		OutputDebugString(_T("Function(CommWriteVision_GetDisFeature) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_VCODE_NG ;

		OutputDebugString(_T("Function(CommWriteVision_GetDisFeature) End")) ;

		return m_pVisionCommWriteBase->Vision_GetDisFeature(vecDisplayFeature) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(CommWriteVision_GetDisFeature) Throw")) ;
		return E_VCODE_THROW ;
	}
}