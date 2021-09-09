#pragma once
#include "Halconcamerabase.h"

#define ASSERT_CAMERA_CONNECT(bConnect)		{if(!bConnect){return E_CAMERA_NG ;}}

class CHalconCameraInterface :
	public CHalconCameraBase
{
public:
	CHalconCameraInterface(void);
	~CHalconCameraInterface(void);

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

	virtual CAMERA_CODE Camera_GetRangeGain(long &lMinGain,long &lMaxGain) ;

	//相机抓取线程
	static unsigned int WINAPI CamGrabbingThread(LPVOID lparam) ;

private:
	CameraCallbackFunc    m_pCallbackFunc ;
	void*                 m_pOwner ;
	int                   m_nImageWidth ;
	int                   m_nImageHeight ;
	//相机句柄
	HTuple                m_hCamHandle ;
	//相机连接状态
	bool                  m_bConnect ;
	//相机采集状态
	bool                  m_bGrabbing ;
	//相机驱动方式
	CAMERA_CONNECTTYPE    m_eCameraConnectType ;
	//相机颜色空间
	CAMERA_COLORTYPE      m_eCameraColorType ;
	//关闭采图线程事件
	HANDLE                m_eCameraCloseThread ;
	//相机连续采集事件
	HANDLE                m_eCameraContinueThread ;
	//线程ID
	unsigned int          m_dwCameraId ;
	//临界区保护
	CRITICAL_SECTION      m_csCamera ;
};
