#include "StdAfx.h"
#include "HalconCameraInterface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CHalconCameraInterface::CHalconCameraInterface(void)
{
	InitializeCriticalSection(&m_csCamera);
	m_bConnect = false ;
	m_bGrabbing = false ;
	m_eCameraConnectType = E_CAMERA_GIGE ;
	m_eCameraColorType = E_CAMERA_MONO8 ;
	m_eCameraCloseThread = CreateEventW(NULL,TRUE,FALSE,NULL);
	ResetEvent(m_eCameraCloseThread);
	m_eCameraContinueThread = CreateEventW(NULL,TRUE,FALSE,NULL);
	ResetEvent(m_eCameraContinueThread);
}

CHalconCameraInterface::~CHalconCameraInterface(void)
{
	if (m_bGrabbing)
	{
		//关闭线程
		EnterCriticalSection(&m_csCamera) ;
		ResetEvent(m_eCameraContinueThread) ;
		LeaveCriticalSection(&m_csCamera) ;
		Sleep(100) ;

		EnterCriticalSection(&m_csCamera) ;
		SetEvent(m_eCameraCloseThread) ;
		LeaveCriticalSection(&m_csCamera) ;
		Sleep(100) ;

		m_bGrabbing = false ;
	}

	if (m_bConnect)
	{
		CloseFramegrabber(m_hCamHandle) ;
	}
	//删除临界区
	DeleteCriticalSection(&m_csCamera) ;
}

CAMERA_CODE CHalconCameraInterface:: Camera_Init(string strCamSn,CAMERA_CONNECTTYPE eCameraConnectType,\
	CAMERA_COLORTYPE eCameraColorType)
{
	USES_CONVERSION ;
	try
	{
		OutputDebugString(_T("Function(HalconCamera_Init) Start")) ;

		CString strConnectType(_T("")),strColorType(_T("")),strDeviceName(strCamSn.c_str()) ;

		//相机Sn判断
		if ("" == strCamSn.c_str())
		{
			OutputDebugString(_T("Error:Halcon Camera Sn is Empty.")) ;
			return E_CAMERA_NG ;
		}

		//相机驱动方式判断
		if (E_CAMERA_GIGE == eCameraConnectType )
		{
			strConnectType = _T("GigEVision2") ;
		}
		else if (E_CAMERA_USB == eCameraConnectType)
		{
			strConnectType = _T("USB3Vision") ;
		}
		else
		{
			OutputDebugString(_T("Error:Halcon Camera cannot support this connection type.")) ;
			return E_CAMERA_NG ;
		}

		//相机颜色空间判断
		if (E_CAMERA_MONO8 == eCameraColorType )
		{
			strColorType = _T("gray") ;
		}
		else if (E_CAMERA_BGR8 == eCameraColorType)
		{
			strColorType = _T("rgb") ;
		}
		else
		{
			OutputDebugString(_T("Error:Halcon Camera cannot support this color space.")) ;
			return E_CAMERA_NG ;
		}

		OpenFramegrabber(W2A(strConnectType), 0, 0, 0, 0, 0, 0, "progressive", -1, W2A(strColorType),
			-1, "false", "default", W2A(strDeviceName), 0, -1, &m_hCamHandle);
		SetFramegrabberParam(m_hCamHandle, "TriggerMode", "Off");
		SetFramegrabberParam(m_hCamHandle, "GainAuto", "Off");
		//SetFramegrabberParam(m_hCamHandle, "GainSelector", "All");
		SetFramegrabberParam(m_hCamHandle, "ExposureAuto", "Off");

		m_bConnect = true ;

		OutputDebugString(_T("Function(HalconCamera_Init) End")) ;

		return E_CAMERA_OK ;
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

		if (m_bGrabbing)
		{
			//关闭线程
			EnterCriticalSection(&m_csCamera) ;
			ResetEvent(m_eCameraContinueThread) ;
			LeaveCriticalSection(&m_csCamera) ;
			Sleep(100) ;

			EnterCriticalSection(&m_csCamera) ;
			SetEvent(m_eCameraCloseThread) ;
			LeaveCriticalSection(&m_csCamera) ;
			Sleep(100) ;

			m_bGrabbing = false ;
		}

		if (m_bConnect)
		{
			CloseFramegrabber(m_hCamHandle) ;
		}
		//删除临界区
		DeleteCriticalSection(&m_csCamera) ;

		OutputDebugString(_T("Function(HalconCamera_Close) End")) ;

		return E_CAMERA_OK ;
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

		m_pOwner = pOwner ;
		m_pCallbackFunc = pFun ;

		OutputDebugString(_T("Function(HalconCamera_SetOwner) End")) ;

		return E_CAMERA_OK ;
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

		ASSERT_CAMERA_CONNECT(m_bConnect) ;

		HTuple hImageWidth,hImageHeight ;
		GetFramegrabberParam(m_hCamHandle,"Width",&hImageWidth) ;
		GetFramegrabberParam(m_hCamHandle,"Height",&hImageHeight) ;
		m_nImageWidth = nImageWidth = hImageWidth ;
		m_nImageHeight = nImageHeight = hImageHeight ;

		OutputDebugString(_T("Function(HalconCamera_GetImageSize) End")) ;

		return E_CAMERA_OK ;
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

		ASSERT_CAMERA_CONNECT(m_bConnect) ;

		if (!m_bGrabbing)
		{
			//所有事件复位
			ResetEvent(m_eCameraCloseThread);
			ResetEvent(m_eCameraContinueThread);
			//开启线程
			_beginthreadex(NULL,0,CamGrabbingThread,this,0,&m_dwCameraId) ;

			//开启采集事件
			Sleep(100) ;

			EnterCriticalSection(&m_csCamera) ;
			SetEvent(m_eCameraContinueThread) ;
			LeaveCriticalSection(&m_csCamera) ;

			m_bGrabbing = true ;
		}

		OutputDebugString(_T("Function(HalconCamera_StartGrab) End")) ;

		return E_CAMERA_OK ;
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

		ASSERT_CAMERA_CONNECT(m_bConnect) ;

		if (m_bGrabbing)
		{
			//关闭线程
			/*EnterCriticalSection(&m_csCamera) ;
			ResetEvent(m_eCameraContinueThread) ;
			LeaveCriticalSection(&m_csCamera) ;
			Sleep(100) ;*/

			EnterCriticalSection(&m_csCamera) ;
			SetEvent(m_eCameraCloseThread) ;
			LeaveCriticalSection(&m_csCamera) ;
			Sleep(100) ;

			m_bGrabbing = false ;
		}

		OutputDebugString(_T("Function(HalconCamera_StopGrab) End")) ;

		return E_CAMERA_OK ;
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

		ASSERT_CAMERA_CONNECT(m_bConnect) ;

		bool bGrabRet = false ;
		GenEmptyObj(hImage) ;
		for (int i = 0 ;i < 3 ;i++)
		{
			GrabImage(hImage,m_hCamHandle) ;
			if (hImage->IsInitialized())
			{
				bGrabRet = true ;
				break ;
			}
			continue;
		}

		if (!bGrabRet)
		{
			OutputDebugString(_T("Error:Halcon Camera grab one image Failed.")) ;
			return E_CAMERA_NG ;
		}

		OutputDebugString(_T("Function(HalconCamera_GrabOne) End")) ;

		return E_CAMERA_OK ;
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

		ASSERT_CAMERA_CONNECT(m_bConnect) ;

		//触发模式开关
		if (triggerMode.bTriggerMode)
		{
			SetFramegrabberParam(m_hCamHandle, "TriggerMode", "On");
		}
		else
		{
			SetFramegrabberParam(m_hCamHandle, "TriggerMode", "Off");

			OutputDebugString(_T("Function(HalconCamera_SetTriggerMode) End")) ;
			return E_CAMERA_OK ;
		}

		//触发源:E_TRIGGER_SOFTWARE-软件触发\E_TRIGGER_LINE1-硬件触发
		if (E_TRIGGER_SOFTWARE == triggerMode.triggerPara.eTriggerSource)
		{
			SetFramegrabberParam(m_hCamHandle,"TriggerSource","Software") ;
		}
		else if(E_TRIGGER_LINE1 == triggerMode.triggerPara.eTriggerSource)
		{
			SetFramegrabberParam(m_hCamHandle,"TriggerSource","Line1") ;
		}

		//触发信号沿:E_TRIGGER_RISING_EDGE-上升沿\E_TRIGGER_FALLING_EDGE-下降沿
		if (E_TRIGGER_RISING_EDGE == triggerMode.triggerPara.eTriggerActive)
		{
			SetFramegrabberParam(m_hCamHandle,"TriggerActivation","RisingEdge") ;
		}
		else if (E_TRIGGER_FALLING_EDGE == triggerMode.triggerPara.eTriggerActive)
		{
			SetFramegrabberParam(m_hCamHandle,"TriggerActivation","FallingEdge") ;
		}

		//采集模式:E_ACQ_CONTINUOUS-连续采集\E_ACQ_SINGLEFRAME-单帧采集
		if (E_ACQ_CONTINUOUS == triggerMode.triggerPara.eAcquisitionMode)
		{
			SetFramegrabberParam(m_hCamHandle,"AcquisitionMode","Continuous") ;
		}
		else if (E_ACQ_SINGLEFRAME == triggerMode.triggerPara.eAcquisitionMode)
		{
			SetFramegrabberParam(m_hCamHandle,"AcquisitionMode","SingleFrame") ;
		}

		//设置采集超时
		SetFramegrabberParam(m_hCamHandle,"grab_timeout",triggerMode.triggerPara.lTriggerDelayTime) ;

		OutputDebugString(_T("Function(HalconCamera_SetTriggerMode) End")) ;

		return E_CAMERA_OK ;
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

		ASSERT_CAMERA_CONNECT(m_bConnect) ;

		HTuple hTriggerPara ;

		//获取触发模式开关
		GetFramegrabberParam(m_hCamHandle,"TriggerMode",&hTriggerPara) ;
		if ("On" == hTriggerPara)
		{
			triggerMode.bTriggerMode = true ;
		}
		else if ("Off" == hTriggerPara)
		{
			triggerMode.bTriggerMode = false ;
		}

		//获取触发源
		GetFramegrabberParam(m_hCamHandle,"TriggerSource",&hTriggerPara) ;
		if ("Software" == hTriggerPara)
		{
			triggerMode.triggerPara.eTriggerSource = E_TRIGGER_SOFTWARE ;
		}
		else if ("Line1" == hTriggerPara)
		{
			triggerMode.triggerPara.eTriggerSource = E_TRIGGER_LINE1 ;
		}

		//获取触发信号沿
		GetFramegrabberParam(m_hCamHandle,"TriggerActivation",&hTriggerPara) ;
		if ("RisingEdge" == hTriggerPara)
		{
			triggerMode.triggerPara.eTriggerActive = E_TRIGGER_RISING_EDGE ;
		}
		else if ("FallingEdge" == hTriggerPara)
		{
			triggerMode.triggerPara.eTriggerActive = E_TRIGGER_FALLING_EDGE ;
		}

		//获取采集模式
		GetFramegrabberParam(m_hCamHandle,"AcquisitionMode",&hTriggerPara) ;
		if ("Continuous" == hTriggerPara)
		{
			triggerMode.triggerPara.eAcquisitionMode = E_ACQ_CONTINUOUS ;
		}
		else if ("SingleFrame" == hTriggerPara)
		{
			triggerMode.triggerPara.eAcquisitionMode = E_ACQ_SINGLEFRAME ;
		}

		GetFramegrabberParam(m_hCamHandle,"grab_timeout",&hTriggerPara) ;
		triggerMode.triggerPara.lTriggerDelayTime = (long)(int)hTriggerPara ;

		OutputDebugString(_T("Function(HalconCamera_GetTriggerMode) End")) ;

		return E_CAMERA_OK ;
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

		ASSERT_CAMERA_CONNECT(m_bConnect) ;

		long lMinValue,lMaxValue ;
		Camera_GetRangeExposureTime(lMinValue,lMaxValue) ;

		//超出设定范围
		if (lExposureTime < lMinValue || lExposureTime > lMaxValue)
		{
			OutputDebugString(_T("Error:Halcon Camera SetExposureTime Over the limit")) ;
			return E_CAMERA_NG ;
		}

		SetFramegrabberParam(m_hCamHandle,"ExposureTimeAbs",lExposureTime) ;
		SetFramegrabberParam(m_hCamHandle,"ExposureTimeRaw",lExposureTime) ;

		OutputDebugString(_T("Function(HalconCamera_SetExposureTime) End")) ;

		return E_CAMERA_OK ;
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

		ASSERT_CAMERA_CONNECT(m_bConnect) ;

		HTuple hCameraPara ;
		double dbExposureTime ;
		GetFramegrabberParam(m_hCamHandle,"ExposureTimeAbs",&hCameraPara) ;
		dbExposureTime = hCameraPara[0].D() ;
		lExposureTime = (long)dbExposureTime ;

		OutputDebugString(_T("Function(HalconCamera_GetExposureTime) End")) ;

		return E_CAMERA_OK ;
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

		ASSERT_CAMERA_CONNECT(m_bConnect) ;

		long lMinValue,lMaxValue ;
		Camera_GetRangeGain(lMinValue,lMaxValue) ;

		//超出设定范围
		if (lGain < lMinValue || lGain > lMaxValue)
		{
			OutputDebugString(_T("Error:Halcon Camera SetGain Over the limit")) ;
			return E_CAMERA_NG ;
		}

		SetFramegrabberParam(m_hCamHandle,"GainRaw",lGain) ;

		OutputDebugString(_T("Function(HalconCamera_SetGain) End")) ;

		return E_CAMERA_OK ;
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

		ASSERT_CAMERA_CONNECT(m_bConnect) ;

		HTuple hCameraPara ;
		double dbGain ;
		GetFramegrabberParam(m_hCamHandle,"GainRaw",&hCameraPara) ;
		dbGain = hCameraPara[0].D() ;
		lGain = (long)dbGain ;

		OutputDebugString(_T("Function(HalconCamera_GetGain) End")) ;

		return E_CAMERA_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(HalconCamera_GetGain) Throw")) ;

		return E_CAMERA_THROW ;
	}
}

CAMERA_CODE CHalconCameraInterface::Camera_GetRangeExposureTime(long &lMinExposureTime,long &lMaxExposureTime)
{
	try
	{
		OutputDebugString(_T("Function(HalconCamera_GetRangeExposureTime) Start")) ;

		ASSERT_CAMERA_CONNECT(m_bConnect) ;

		HTuple hCameraPara ;
		double dbMinExposureTime,dbMaxExposureTime ;
		GetFramegrabberParam(m_hCamHandle,"AutoExposureTimeAbsLowerLimit",&hCameraPara) ;
		dbMinExposureTime = hCameraPara[0].D() ;
		lMinExposureTime = (long)dbMinExposureTime ;

		GetFramegrabberParam(m_hCamHandle,"AutoExposureTimeAbsUpperLimit",&hCameraPara) ;
		dbMaxExposureTime = hCameraPara[0].D() ;
		lMaxExposureTime = (long)dbMaxExposureTime ;

		OutputDebugString(_T("Function(HalconCamera_GetRangeExposureTime) End")) ;

		return E_CAMERA_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(HalconCamera_GetRangeExposureTime) Throw")) ;

		return E_CAMERA_THROW ;
	}
}

CAMERA_CODE CHalconCameraInterface::Camera_GetRangeGain(long &lMinGain,long &lMaxGain)
{
	try
	{
		OutputDebugString(_T("Function(HalconCamera_GetRangeGain) Start")) ;

		ASSERT_CAMERA_CONNECT(m_bConnect) ;

		HTuple hCameraPara ;
		double dbMinGain,dbMaxGain ;
		GetFramegrabberParam(m_hCamHandle,"AutoGainRawLowerLimit",&hCameraPara) ;
		dbMinGain = hCameraPara[0].D() ;
		lMinGain = (long)dbMinGain ;

		GetFramegrabberParam(m_hCamHandle,"AutoGainRawUpperLimit",&hCameraPara) ;
		dbMaxGain = hCameraPara[0].D() ;
		lMaxGain = (int)dbMaxGain ;

		OutputDebugString(_T("Function(HalconCamera_GetRangeGain) End")) ;

		return E_CAMERA_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(HalconCamera_GetRangeGain) Throw")) ;

		return E_CAMERA_THROW ;
	}
}

unsigned int WINAPI CHalconCameraInterface::CamGrabbingThread(LPVOID lparam)

{
	try
	{
		CHalconCameraInterface *pCamera = (CHalconCameraInterface*)lparam;

		HObject hImage ;
		HANDLE  eventHandle[2];

		eventHandle[0] =(*pCamera).m_eCameraCloseThread;
		eventHandle[1] =(*pCamera).m_eCameraContinueThread;

		OutputDebugString(_T("Function(HalconCamera_Thread) Start")) ;

		while(WAIT_OBJECT_0 != WaitForSingleObject(pCamera->m_eCameraCloseThread,0))
		{
			//退出程序直接退出线程
			WaitForMultipleObjects(2,eventHandle,FALSE,INFINITE);
			if(WAIT_OBJECT_0==WaitForSingleObject(pCamera->m_eCameraCloseThread,0))
			{
				OutputDebugString(_T("Function(HalconCamera_Thread) End")) ;
				return 0;
			}

			Sleep(10) ;

			bool bGrabRet = false ;
			GenEmptyObj(&hImage) ;
			for (int i = 0 ;i < 3 ;i++)
			{
				GrabImage(&hImage,pCamera->m_hCamHandle) ;
				if (hImage.IsInitialized())
				{
					bGrabRet = true ;
					break ;
				}
				continue;
			}

			if (!bGrabRet)
			{
				OutputDebugString(_T("Error:Halcon Camera grabbing image Failed.")) ;
				continue;
			}

			pCamera->m_pCallbackFunc(pCamera->m_pOwner,&hImage) ;

			OutputDebugString(_T("Function(HalconCamera_Thread) Grab Image")) ;
		}

		OutputDebugString(_T("Function(HalconCamera_Thread) End")) ;

		return 0 ;
	}
	catch (...)
	{
		return -1 ;
	}
}