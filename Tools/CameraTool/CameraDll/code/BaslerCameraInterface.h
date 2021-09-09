#pragma once
#include "Camerabase.h"
#include "BaslerCameraBase.h"
#include "vCriticalSection.h"

class CBaslerCameraInterface :
	public CCameraBase
{
public:
	CBaslerCameraInterface(void);
	~CBaslerCameraInterface(void);

	virtual CAMERA_CODE Camera_Init(string strCamSn,CAMERA_CONNECTTYPE eCameraConnectType = E_CAMERA_GIGE,\
		CAMERA_COLORTYPE eCameraColorType = E_CAMERA_MONO8)  ;

	virtual CAMERA_CODE Camera_Close() ;

	virtual CAMERA_CODE Camera_SetOwner(void *pOwner,CameraCallbackFunc pFun)  ;

	virtual CAMERA_CODE Camera_GetImageSize(int &nImageWidth,int &nImageHeight)  ;

	virtual CAMERA_CODE Camera_StartGrab()  ;

	virtual CAMERA_CODE Camera_StopGrab()  ;

	virtual CAMERA_CODE Camera_GrabOne(HObject *hImage)  ;

	virtual CAMERA_CODE Camera_SetTriggerMode(CAMERA_TRIGGER_MODE triggerMode)  ;

	virtual CAMERA_CODE Camera_GetTriggerMode(CAMERA_TRIGGER_MODE &triggerMode)  ;

	virtual CAMERA_CODE Camera_SetExposureTime(long lExposureTime)  ;

	virtual CAMERA_CODE Camera_GetExposureTime(long &lExposureTime)  ;

	virtual CAMERA_CODE Camera_SetGain(long lGain)  ;

	virtual CAMERA_CODE Camera_GetGain(long &lGain)  ;

	virtual CAMERA_CODE Camera_GetRangeExposureTime(long &lMinExposureTime,long &lMaxExposureTime) ;

	virtual CAMERA_CODE Camera_GetRangeGain(long &lMinGain,long &lMaxGain)  ;

private:
	CBaslerCameraBase*         m_pBaslerCameraBase ;
	CMgrDllBaserCameraIm       m_dllBaslerCameraIm ;
	bool                       m_bInitOk ;
	CRITICAL_SECTION           m_Critical;
};
