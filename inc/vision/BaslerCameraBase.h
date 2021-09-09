#pragma once
#include "ModuleDevelopH.h"
#include "VisionData.h"

class CMgrDllBaserCameraIm : public CMgrDllDelegate
{
public:
#ifdef _DEBUG
	CMgrDllBaserCameraIm(LPCTSTR lpcszDllPathFullName=_T("BaslerCameraD.dll"))
		: CMgrDllDelegate(lpcszDllPathFullName)
	{
	}
#else
	CMgrDllBaserCameraIm(LPCTSTR lpcszDllPathFullName=_T("BaslerCamera.dll"))
		: CMgrDllDelegate(lpcszDllPathFullName)
	{
	}
#endif
	virtual ~CMgrDllBaserCameraIm(){
	}
};

class CBaslerCameraBase
{
public:
	virtual CAMERA_CODE Camera_Init(string strCamSn,CAMERA_CONNECTTYPE eCameraConnectType = E_CAMERA_GIGE,\
		CAMERA_COLORTYPE eCameraColorType = E_CAMERA_MONO8) = 0 ;

	virtual CAMERA_CODE Camera_Close() = 0 ;

	virtual CAMERA_CODE Camera_SetOwner(void *pOwner,CameraCallbackFunc pFun) = 0 ;

	virtual CAMERA_CODE Camera_GetImageSize(int &nImageWidth,int &nImageHeight) = 0 ;

	virtual CAMERA_CODE Camera_StartGrab() = 0 ;

	virtual CAMERA_CODE Camera_StopGrab() = 0 ;

	virtual CAMERA_CODE Camera_GrabOne(HObject *hImage) = 0 ;

	virtual CAMERA_CODE Camera_SetTriggerMode(CAMERA_TRIGGER_MODE triggerMode) = 0 ;

	virtual CAMERA_CODE Camera_GetTriggerMode(CAMERA_TRIGGER_MODE &triggerMode) = 0 ;

	virtual CAMERA_CODE Camera_SetExposureTime(long lExposureTime) = 0 ;

	virtual CAMERA_CODE Camera_GetExposureTime(long &lExposureTime) = 0 ;

	virtual CAMERA_CODE Camera_SetGain(long lGain) = 0 ;

	virtual CAMERA_CODE Camera_GetGain(long &lGain) = 0 ;

	virtual CAMERA_CODE Camera_GetRangeExposureTime(long &lMinExposureTime,long &lMaxExposureTime) = 0 ;

	virtual CAMERA_CODE Camera_GetRangeGain(long &lMinGain,long &lMaxGain) = 0 ;
};