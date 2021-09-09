#include "StdAfx.h"
#include "BaslerCameraInterface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CBaslerCameraInterface::CBaslerCameraInterface(void)
{
}

CBaslerCameraInterface::~CBaslerCameraInterface(void)
{
}

CAMERA_CODE CBaslerCameraInterface:: Camera_Init(string strCamSn,CAMERA_CONNECTTYPE eCameraConnectType,\
	CAMERA_COLORTYPE eCameraColorType)
{
	try
	{
		OutputDebugString(_T("Function(BaslerCamera_Init) Start")) ;

		OutputDebugString(_T("Function(BaslerCamera_Init) End")) ;

		return E_CAMERA_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(BaslerCamera_Init) Throw")) ;

		return E_CAMERA_THROW ;
	}
}

CAMERA_CODE CBaslerCameraInterface:: Camera_Close()
{
	try
	{
		OutputDebugString(_T("Function(BaslerCamera_Close) Start")) ;

		OutputDebugString(_T("Function(BaslerCamera_Close) End")) ;

		return E_CAMERA_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(BaslerCamera_Close) Throw")) ;

		return E_CAMERA_THROW ;
	}
}

CAMERA_CODE CBaslerCameraInterface:: Camera_SetOwner(void *pOwner,CameraCallbackFunc pFun)
{
	try
	{
		OutputDebugString(_T("Function(BaslerCamera_SetOwner) Start")) ;

		OutputDebugString(_T("Function(BaslerCamera_SetOwner) End")) ;

		return E_CAMERA_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(BaslerCamera_SetOwner) Throw")) ;

		return E_CAMERA_THROW ;
	}
}

CAMERA_CODE CBaslerCameraInterface:: Camera_GetImageSize(int &nImageWidth,int &nImageHeight)
{
	try
	{
		OutputDebugString(_T("Function(BaslerCamera_GetImageSize) Start")) ;

		OutputDebugString(_T("Function(BaslerCamera_GetImageSize) End")) ;

		return E_CAMERA_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(BaslerCamera_GetImageSize) Throw")) ;

		return E_CAMERA_THROW ;
	}
}

CAMERA_CODE CBaslerCameraInterface:: Camera_StartGrab()
{
	try
	{
		OutputDebugString(_T("Function(BaslerCamera_StartGrab) Start")) ;

		OutputDebugString(_T("Function(BaslerCamera_StartGrab) End")) ;

		return E_CAMERA_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(BaslerCamera_StartGrab) Throw")) ;

		return E_CAMERA_THROW ;
	}
}

CAMERA_CODE CBaslerCameraInterface:: Camera_StopGrab()
{
	try
	{
		OutputDebugString(_T("Function(BaslerCamera_StopGrab) Start")) ;

		OutputDebugString(_T("Function(BaslerCamera_StopGrab) End")) ;

		return E_CAMERA_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(BaslerCamera_StopGrab) Throw")) ;

		return E_CAMERA_THROW ;
	}
}

CAMERA_CODE CBaslerCameraInterface:: Camera_GrabOne(HObject *hImage)
{
	try
	{
		OutputDebugString(_T("Function(BaslerCamera_GrabOne) Start")) ;

		OutputDebugString(_T("Function(BaslerCamera_GrabOne) End")) ;

		return E_CAMERA_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(BaslerCamera_GrabOne) Throw")) ;

		return E_CAMERA_THROW ;
	}
}

CAMERA_CODE CBaslerCameraInterface:: Camera_SetTriggerMode(CAMERA_TRIGGER_MODE triggerMode)
{
	try
	{
		OutputDebugString(_T("Function(BaslerCamera_SetTriggerMode) Start")) ;

		OutputDebugString(_T("Function(BaslerCamera_SetTriggerMode) End")) ;

		return E_CAMERA_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(BaslerCamera_SetTriggerMode) Throw")) ;

		return E_CAMERA_THROW ;
	}
}

CAMERA_CODE CBaslerCameraInterface:: Camera_GetTriggerMode(CAMERA_TRIGGER_MODE &triggerMode)
{
	try
	{
		OutputDebugString(_T("Function(BaslerCamera_GetTriggerMode) Start")) ;

		OutputDebugString(_T("Function(BaslerCamera_GetTriggerMode) End")) ;

		return E_CAMERA_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(BaslerCamera_GetTriggerMode) Throw")) ;

		return E_CAMERA_THROW ;
	}
}

CAMERA_CODE CBaslerCameraInterface:: Camera_SetExposureTime(long lExposureTime)
{
	try
	{
		OutputDebugString(_T("Function(BaslerCamera_SetExposureTime) Start")) ;

		OutputDebugString(_T("Function(BaslerCamera_SetExposureTime) End")) ;

		return E_CAMERA_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(BaslerCamera_SetExposureTime) Throw")) ;

		return E_CAMERA_THROW ;
	}
}

CAMERA_CODE CBaslerCameraInterface:: Camera_GetExposureTime(long &lExposureTime)
{
	try
	{
		OutputDebugString(_T("Function(BaslerCamera_GetExposureTime) Start")) ;

		OutputDebugString(_T("Function(BaslerCamera_GetExposureTime) End")) ;

		return E_CAMERA_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(BaslerCamera_GetExposureTime) Throw")) ;

		return E_CAMERA_THROW ;
	}
}

CAMERA_CODE CBaslerCameraInterface:: Camera_SetGain(long lGain)
{
	try
	{
		OutputDebugString(_T("Function(BaslerCamera_SetGain) Start")) ;

		OutputDebugString(_T("Function(BaslerCamera_SetGain) End")) ;

		return E_CAMERA_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(BaslerCamera_SetGain) Throw")) ;

		return E_CAMERA_THROW ;
	}
}

CAMERA_CODE CBaslerCameraInterface:: Camera_GetGain(long &lGain)
{
	try
	{
		OutputDebugString(_T("Function(BaslerCamera_GetGain) Start")) ;

		OutputDebugString(_T("Function(BaslerCamera_GetGain) End")) ;

		return E_CAMERA_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(BaslerCamera_GetGain) Throw")) ;

		return E_CAMERA_THROW ;
	}
}

CAMERA_CODE CBaslerCameraInterface:: Camera_GetRangeExposureTime(long &lMinExposureTime,long &lMaxExposureTime)
{
	try
	{
		OutputDebugString(_T("Function(BaslerCamera_GetRangeExposureTime) Start")) ;

		OutputDebugString(_T("Function(BaslerCamera_GetRangeExposureTime) End")) ;

		return E_CAMERA_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(BaslerCamera_GetRangeExposureTime) Throw")) ;

		return E_CAMERA_THROW ;
	}
}

CAMERA_CODE CBaslerCameraInterface:: Camera_GetRangeGain(long &lMinGain,long &lMaxGain)
{
	try
	{
		OutputDebugString(_T("Function(BaslerCamera_GetRangeGain) Start")) ;

		OutputDebugString(_T("Function(BaslerCamera_GetRangeGain) End")) ;

		return E_CAMERA_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(BaslerCamera_GetRangeGain) Throw")) ;

		return E_CAMERA_THROW ;
	}
}