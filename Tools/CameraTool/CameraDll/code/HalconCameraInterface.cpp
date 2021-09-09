#include "StdAfx.h"
#include "HalconCameraInterface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CHalconCameraInterface::CHalconCameraInterface(void)
{
	::InitializeCriticalSection(&m_Critical);
	m_pHalconCameraBase = NULL ;
	m_bInitOk = false ;
	m_dllHalconCameraIm.DllCreateInterface((int)E_TOOL_CAMERA_HALCON,(void **)&m_pHalconCameraBase) ;
	if (m_pHalconCameraBase)
		m_bInitOk = true ;
}

CHalconCameraInterface::~CHalconCameraInterface(void)
{
	::DeleteCriticalSection(&m_Critical);
}

CAMERA_CODE CHalconCameraInterface:: Camera_Init(string strCamSn,CAMERA_CONNECTTYPE eCameraConnectType,\
	CAMERA_COLORTYPE eCameraColorType)
{
	try
	{
		OutputDebugString(_T("Function(HalconCamera_Init) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_CAMERA_NG ;

		OutputDebugString(_T("Function(HalconCamera_Init) End")) ;

		return m_pHalconCameraBase->Camera_Init(strCamSn,eCameraConnectType,eCameraColorType) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(HalconCamera_Init) Throw")) ;

		return E_CAMERA_THROW ;
	}
}

CAMERA_CODE CHalconCameraInterface:: Camera_Close()
{
	try
	{
		OutputDebugString(_T("Function(HalconCamera_Close) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_CAMERA_NG ;

		OutputDebugString(_T("Function(HalconCamera_Close) End")) ;

		return m_pHalconCameraBase->Camera_Close() ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(HalconCamera_Close) Throw")) ;

		return E_CAMERA_THROW ;
	}
}

CAMERA_CODE CHalconCameraInterface:: Camera_SetOwner(void *pOwner,CameraCallbackFunc pFun)
{
	try
	{
		OutputDebugString(_T("Function(HalconCamera_SetOwner) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_CAMERA_NG ;

		OutputDebugString(_T("Function(HalconCamera_SetOwner) End")) ;

		return m_pHalconCameraBase->Camera_SetOwner(pOwner,pFun) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(HalconCamera_SetOwner) Throw")) ;

		return E_CAMERA_THROW ;
	}
}

CAMERA_CODE CHalconCameraInterface:: Camera_GetImageSize(int &nImageWidth,int &nImageHeight)
{
	try
	{
		OutputDebugString(_T("Function(HalconCamera_GetImageSize) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_CAMERA_NG ;

		OutputDebugString(_T("Function(HalconCamera_GetImageSize) End")) ;

		return m_pHalconCameraBase->Camera_GetImageSize(nImageWidth,nImageHeight) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(HalconCamera_GetImageSize) Throw")) ;

		return E_CAMERA_THROW ;
	}
}

CAMERA_CODE CHalconCameraInterface:: Camera_StartGrab()
{
	try
	{
		OutputDebugString(_T("Function(HalconCamera_StartGrab) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_CAMERA_NG ;

		OutputDebugString(_T("Function(HalconCamera_StartGrab) End")) ;

		return m_pHalconCameraBase->Camera_StartGrab() ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(HalconCamera_StartGrab) Throw")) ;

		return E_CAMERA_THROW ;
	}
}

CAMERA_CODE CHalconCameraInterface:: Camera_StopGrab()
{
	try
	{
		OutputDebugString(_T("Function(HalconCamera_StopGrab) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_CAMERA_NG ;

		OutputDebugString(_T("Function(HalconCamera_StopGrab) End")) ;

		return m_pHalconCameraBase->Camera_StopGrab() ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(HalconCamera_StopGrab) Throw")) ;

		return E_CAMERA_THROW ;
	}
}

CAMERA_CODE CHalconCameraInterface:: Camera_GrabOne(HObject *hImage)
{
	try
	{
		OutputDebugString(_T("Function(HalconCamera_GrabOne) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_CAMERA_NG ;

		OutputDebugString(_T("Function(HalconCamera_GrabOne) End")) ;

		return m_pHalconCameraBase->Camera_GrabOne(hImage) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(HalconCamera_GrabOne) Throw")) ;

		return E_CAMERA_THROW ;
	}
}

CAMERA_CODE CHalconCameraInterface:: Camera_SetTriggerMode(CAMERA_TRIGGER_MODE triggerMode)
{
	try
	{
		OutputDebugString(_T("Function(HalconCamera_SetTriggerMode) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_CAMERA_NG ;

		OutputDebugString(_T("Function(HalconCamera_SetTriggerMode) End")) ;

		return m_pHalconCameraBase->Camera_SetTriggerMode(triggerMode) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(HalconCamera_SetTriggerMode) Throw")) ;

		return E_CAMERA_THROW ;
	}
}

CAMERA_CODE CHalconCameraInterface:: Camera_GetTriggerMode(CAMERA_TRIGGER_MODE &triggerMode)
{
	try
	{
		OutputDebugString(_T("Function(HalconCamera_GetTriggerMode) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_CAMERA_NG ;

		OutputDebugString(_T("Function(HalconCamera_GetTriggerMode) End")) ;

		return m_pHalconCameraBase->Camera_GetTriggerMode(triggerMode) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(HalconCamera_GetTriggerMode) Throw")) ;

		return E_CAMERA_THROW ;
	}
}

CAMERA_CODE CHalconCameraInterface:: Camera_SetExposureTime(long lExposureTime)
{
	try
	{
		OutputDebugString(_T("Function(HalconCamera_SetExposureTime) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_CAMERA_NG ;

		OutputDebugString(_T("Function(HalconCamera_SetExposureTime) End")) ;

		return m_pHalconCameraBase->Camera_SetExposureTime(lExposureTime) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(HalconCamera_SetExposureTime) Throw")) ;

		return E_CAMERA_THROW ;
	}
}

CAMERA_CODE CHalconCameraInterface:: Camera_GetExposureTime(long &lExposureTime)
{
	try
	{
		OutputDebugString(_T("Function(HalconCamera_GetExposureTime) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_CAMERA_NG ;

		OutputDebugString(_T("Function(HalconCamera_GetExposureTime) End")) ;

		return m_pHalconCameraBase->Camera_GetExposureTime(lExposureTime) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(HalconCamera_GetExposureTime) Throw")) ;

		return E_CAMERA_THROW ;
	}
}

CAMERA_CODE CHalconCameraInterface:: Camera_SetGain(long lGain)
{
	try
	{
		OutputDebugString(_T("Function(HalconCamera_SetGain) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_CAMERA_NG ;

		OutputDebugString(_T("Function(HalconCamera_SetGain) End")) ;

		return m_pHalconCameraBase->Camera_SetGain(lGain) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(HalconCamera_SetGain) Throw")) ;

		return E_CAMERA_THROW ;
	}
}

CAMERA_CODE CHalconCameraInterface:: Camera_GetGain(long &lGain)
{
	try
	{
		OutputDebugString(_T("Function(HalconCamera_GetGain) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_CAMERA_NG ;

		OutputDebugString(_T("Function(HalconCamera_GetGain) End")) ;

		return m_pHalconCameraBase->Camera_GetGain(lGain) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(HalconCamera_GetGain) Throw")) ;

		return E_CAMERA_THROW ;
	}
}

CAMERA_CODE CHalconCameraInterface:: Camera_GetRangeExposureTime(long &lMinExposureTime,long &lMaxExposureTime)
{
	try
	{
		OutputDebugString(_T("Function(HalconCamera_GetRangeExposureTime) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_CAMERA_NG ;

		OutputDebugString(_T("Function(HalconCamera_GetRangeExposureTime) End")) ;

		return m_pHalconCameraBase->Camera_GetRangeExposureTime(lMinExposureTime,lMaxExposureTime) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(HalconCamera_GetRangeExposureTime) Throw")) ;

		return E_CAMERA_THROW ;
	}
}

CAMERA_CODE CHalconCameraInterface:: Camera_GetRangeGain(long &lMinGain,long &lMaxGain)
{
	try
	{
		OutputDebugString(_T("Function(HalconCamera_GetRangeGain) Start")) ;

		vCriticalSection myCritSection(&m_Critical);
		if(!m_bInitOk) return E_CAMERA_NG ;

		OutputDebugString(_T("Function(HalconCamera_GetRangeGain) End")) ;

		return m_pHalconCameraBase->Camera_GetRangeGain(lMinGain,lMaxGain) ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(HalconCamera_GetRangeGain) Throw")) ;

		return E_CAMERA_THROW ;
	}
}