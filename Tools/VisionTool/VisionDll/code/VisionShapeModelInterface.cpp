#include "StdAfx.h"
#include "VisionShapeModelInterface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CVisionShapeModelInterface::CVisionShapeModelInterface(void)
{
	::InitializeCriticalSection(&m_Critical);
	m_pVisionShapeModelBase = NULL ;
	m_bInitOk = false ;
	m_dllVisionShapeModelIm.DllCreateInterface((int)E_TOOL_2DVISION_SHAPEMODEL,(void **)&m_pVisionShapeModelBase) ;
	if (m_pVisionShapeModelBase)
		m_bInitOk = true ;
}

CVisionShapeModelInterface::~CVisionShapeModelInterface(void)
{
	::DeleteCriticalSection(&m_Critical);
}

VISION_CODE CVisionShapeModelInterface:: Vision_Init()
{
	try
	{
		OutputDebugString(_T("Function(ShapeModelVision_Init) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_VCODE_NG ;

		OutputDebugString(_T("Function(ShapeModelVision_Init) End")) ;

		return m_pVisionShapeModelBase->Vision_Init() ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(ShapeModelVision_Init) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionShapeModelInterface:: Vision_Release()
{
	try
	{
		OutputDebugString(_T("Function(ShapeModelVision_Release) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_VCODE_NG ;

		OutputDebugString(_T("Function(ShapeModelVision_Release) End")) ;

		return m_pVisionShapeModelBase->Vision_Release() ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(ShapeModelVision_Release) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionShapeModelInterface:: Vision_SetLanguage(int nLanguage)
{
	try
	{
		OutputDebugString(_T("Function(ShapeModelVision_SetLanguage) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_VCODE_NG ;

		OutputDebugString(_T("Function(ShapeModelVision_SetLanguage) End")) ;

		return m_pVisionShapeModelBase->Vision_SetLanguage(nLanguage) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(ShapeModelVision_SetLanguage) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionShapeModelInterface:: Vision_LoadConfigure(const char* pLoadPath)
{
	try
	{
		OutputDebugString(_T("Function(ShapeModelVision_LoadConfigure) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_VCODE_NG ;

		OutputDebugString(_T("Function(ShapeModelVision_LoadConfigure) End")) ;

		return m_pVisionShapeModelBase->Vision_LoadConfigure(pLoadPath) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(ShapeModelVision_LoadConfigure) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionShapeModelInterface:: Vision_SetConfigurePath(const char* pSavePath)
{
	try
	{
		OutputDebugString(_T("Function(ShapeModelVision_SetConfigurePath) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_VCODE_NG ;

		OutputDebugString(_T("Function(ShapeModelVision_SetConfigurePath) End")) ;

		return m_pVisionShapeModelBase->Vision_SetConfigurePath(pSavePath) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(ShapeModelVision_SetConfigurePath) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionShapeModelInterface:: Vision_ShowDialog()
{
	try
	{
		OutputDebugString(_T("Function(ShapeModelVision_ShowDialog) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_VCODE_NG ;

		OutputDebugString(_T("Function(ShapeModelVision_ShowDialog) End")) ;

		return m_pVisionShapeModelBase->Vision_ShowDialog() ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(ShapeModelVision_ShowDialog) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionShapeModelInterface:: Vision_Run(HTuple hWindowID)
{
	try
	{
		OutputDebugString(_T("Function(ShapeModelVision_Run) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_VCODE_NG ;

		OutputDebugString(_T("Function(ShapeModelVision_Run) End")) ;

		return m_pVisionShapeModelBase->Vision_Run(hWindowID) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(ShapeModelVision_Run) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionShapeModelInterface:: Vision_Input(vector<any> vecInput)
{
	try
	{
		OutputDebugString(_T("Function(ShapeModelVision_Input) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_VCODE_NG ;

		OutputDebugString(_T("Function(ShapeModelVision_Input) End")) ;

		return m_pVisionShapeModelBase->Vision_Input(vecInput) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(ShapeModelVision_Input) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionShapeModelInterface:: Vision_Output(vector<any> &vecOutput)
{
	try
	{
		OutputDebugString(_T("Function(ShapeModelVision_Output) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_VCODE_NG ;

		OutputDebugString(_T("Function(ShapeModelVision_Output) End")) ;

		return m_pVisionShapeModelBase->Vision_Output(vecOutput) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(ShapeModelVision_Output) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionShapeModelInterface:: Vision_GetDisFeature(vector<any> &vecDisplayFeature)
{
	try
	{
		OutputDebugString(_T("Function(ShapeModelVision_GetDisFeature) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_VCODE_NG ;

		OutputDebugString(_T("Function(ShapeModelVision_GetDisFeature) End")) ;

		return m_pVisionShapeModelBase->Vision_GetDisFeature(vecDisplayFeature) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(ShapeModelVision_GetDisFeature) Throw")) ;
		return E_VCODE_THROW ;
	}
}