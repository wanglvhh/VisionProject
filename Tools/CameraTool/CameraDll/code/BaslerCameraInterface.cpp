#include "StdAfx.h"
#include "BaslerCameraInterface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CBaslerCameraInterface::CBaslerCameraInterface(void)
{
	::InitializeCriticalSection(&m_Critical);
	m_pBaslerCameraBase = NULL ;
	m_bInitOk = false ;
	m_dllBaslerCameraIm.DllCreateInterface((int)E_TOOL_CAMERA_BASLER,(void **)&m_pBaslerCameraBase) ;
	if (m_pBaslerCameraBase)
		m_bInitOk = true ;
}

CBaslerCameraInterface::~CBaslerCameraInterface(void)
{
	::DeleteCriticalSection(&m_Critical);
}

CAMERA_CODE CBaslerCameraInterface:: Camera_Init(string strCamSn,CAMERA_CONNECTTYPE eCameraConnectType,\
	CAMERA_COLORTYPE eCameraColorType)
{
	try
	{
		OutputDebugString(_T("Function(BaserCamera_Init) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_CAMERA_NG ;

		OutputDebugString(_T("Function(BaserCamera_Init) End")) ;

		return m_pBaslerCameraBase->Camera_Init(strCamSn,eCameraConnectType,eCameraColorType) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(BaserCamera_Init) Throw")) ;

		return E_CAMERA_THROW ;
	}
}

CAMERA_CODE CBaslerCameraInterface:: Camera_Close()
{
	try
	{
		OutputDebugString(_T("Function(BaserCamera_Close) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_CAMERA_NG ;

		OutputDebugString(_T("Function(BaserCamera_Close) End")) ;

		return m_pBaslerCameraBase->Camera_Close() ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(BaserCamera_Close) Throw")) ;

		return E_CAMERA_THROW ;
	}
}

CAMERA_CODE CBaslerCameraInterface:: Camera_SetOwner(void *pOwner,CameraCallbackFunc pFun)
{
	try
	{
		OutputDebugString(_T("Function(BaserCamera_SetOwner) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_CAMERA_NG ;

		OutputDebugString(_T("Function(BaserCamera_SetOwner) End")) ;

		return m_pBaslerCameraBase->Camera_SetOwner(pOwner,pFun) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(BaserCamera_SetOwner) Throw")) ;

		return E_CAMERA_THROW ;
	}
}

CAMERA_CODE CBaslerCameraInterface:: Camera_GetImageSize(int &nImageWidth,int &nImageHeight)
{
	try
	{
		OutputDebugString(_T("Function(BaserCamera_GetImageSize) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_CAMERA_NG ;

		OutputDebugString(_T("Function(BaserCamera_GetImageSize) End")) ;

		return m_pBaslerCameraBase->Camera_GetImageSize(nImageWidth,nImageHeight) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(BaserCamera_GetImageSize) Throw")) ;

		return E_CAMERA_THROW ;
	}
}

CAMERA_CODE CBaslerCameraInterface:: Camera_StartGrab()
{
	try
	{
		OutputDebugString(_T("Function(BaserCamera_StartGrab) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_CAMERA_NG ;

		OutputDebugString(_T("Function(BaserCamera_StartGrab) End")) ;

		return m_pBaslerCameraBase->Camera_StartGrab() ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(BaserCamera_StartGrab) Throw")) ;

		return E_CAMERA_THROW ;
	}
}

CAMERA_CODE CBaslerCameraInterface:: Camera_StopGrab()
{
	try
	{
		OutputDebugString(_T("Function(BaserCamera_StopGrab) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_CAMERA_NG ;

		OutputDebugString(_T("Function(BaserCamera_StopGrab) End")) ;

		return m_pBaslerCameraBase->Camera_StopGrab() ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(BaserCamera_StopGrab) Throw")) ;

		return E_CAMERA_THROW ;
	}
}

CAMERA_CODE CBaslerCameraInterface:: Camera_GrabOne(HObject *hImage)
{
	try
	{
		OutputDebugString(_T("Function(BaserCamera_GrabOne) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_CAMERA_NG ;

		OutputDebugString(_T("Function(BaserCamera_GrabOne) End")) ;

		return m_pBaslerCameraBase->Camera_GrabOne(hImage) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(BaserCamera_GrabOne) Throw")) ;

		return E_CAMERA_THROW ;
	}
}

CAMERA_CODE CBaslerCameraInterface:: Camera_SetTriggerMode(CAMERA_TRIGGER_MODE triggerMode)
{
	try
	{
		OutputDebugString(_T("Function(BaserCamera_SetTriggerMode) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_CAMERA_NG ;

		OutputDebugString(_T("Function(BaserCamera_SetTriggerMode) End")) ;

		return m_pBaslerCameraBase->Camera_SetTriggerMode(triggerMode) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(BaserCamera_SetTriggerMode) Throw")) ;

		return E_CAMERA_THROW ;
	}
}

CAMERA_CODE CBaslerCameraInterface:: Camera_GetTriggerMode(CAMERA_TRIGGER_MODE &triggerMode)
{
	try
	{
		OutputDebugString(_T("Function(BaserCamera_GetTriggerMode) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_CAMERA_NG ;

		OutputDebugString(_T("Function(BaserCamera_GetTriggerMode) End")) ;

		return m_pBaslerCameraBase->Camera_GetTriggerMode(triggerMode) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(BaserCamera_GetTriggerMode) Throw")) ;

		return E_CAMERA_THROW ;
	}
}

CAMERA_CODE CBaslerCameraInterface:: Camera_SetExposureTime(long lExposureTime)
{
	try
	{
		OutputDebugString(_T("Function(BaserCamera_SetExposureTime) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_CAMERA_NG ;

		OutputDebugString(_T("Function(BaserCamera_SetExposureTime) End")) ;

		return m_pBaslerCameraBase->Camera_SetExposureTime(lExposureTime) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(BaserCamera_SetExposureTime) Throw")) ;

		return E_CAMERA_THROW ;
	}
}

CAMERA_CODE CBaslerCameraInterface:: Camera_GetExposureTime(long &lExposureTime)
{
	try
	{
		OutputDebugString(_T("Function(BaserCamera_GetExposureTime) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_CAMERA_NG ;

		OutputDebugString(_T("Function(BaserCamera_GetExposureTime) End")) ;

		return m_pBaslerCameraBase->Camera_GetExposureTime(lExposureTime) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(BaserCamera_GetExposureTime) Throw")) ;

		return E_CAMERA_THROW ;
	}
}

CAMERA_CODE CBaslerCameraInterface:: Camera_SetGain(long lGain)
{
	try
	{
		OutputDebugString(_T("Function(BaserCamera_SetGain) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_CAMERA_NG ;

		OutputDebugString(_T("Function(BaserCamera_SetGain) End")) ;

		return m_pBaslerCameraBase->Camera_SetGain(lGain) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(BaserCamera_SetGain) Throw")) ;

		return E_CAMERA_THROW ;
	}
}

CAMERA_CODE CBaslerCameraInterface:: Camera_GetGain(long &lGain)
{
	try
	{
		OutputDebugString(_T("Function(BaserCamera_GetGain) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_CAMERA_NG ;

		OutputDebugString(_T("Function(BaserCamera_GetGain) End")) ;

		return m_pBaslerCameraBase->Camera_GetGain(lGain) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(BaserCamera_GetGain) Throw")) ;

		return E_CAMERA_THROW ;
	}
}

CAMERA_CODE CBaslerCameraInterface:: Camera_GetRangeExposureTime(long &lMinExposureTime,long &lMaxExposureTime)
{
	try
	{
		OutputDebugString(_T("Function(BaserCamera_GetRangeExposureTime) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_CAMERA_NG ;

		OutputDebugString(_T("Function(BaserCamera_GetRangeExposureTime) End")) ;

		return m_pBaslerCameraBase->Camera_GetRangeExposureTime(lMinExposureTime,lMaxExposureTime) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(BaserCamera_GetRangeExposureTime) Throw")) ;

		return E_CAMERA_THROW ;
	}
}

CAMERA_CODE CBaslerCameraInterface:: Camera_GetRangeGain(long &lMinGain,long &lMaxGain)
{
	try
	{
		OutputDebugString(_T("Function(BaserCamera_GetRangeGain) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_CAMERA_NG ;

		OutputDebugString(_T("Function(BaserCamera_GetRangeGain) End")) ;

		return m_pBaslerCameraBase->Camera_GetRangeGain(lMinGain,lMaxGain) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(BaserCamera_GetRangeGain) Throw")) ;

		return E_CAMERA_THROW ;
	}
}