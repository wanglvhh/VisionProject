#pragma once
#include "VisionData.h"
#include "CameraBase.h"

//相机节点元素
class CCameraNode:public CObject
{
public:
	CCameraNode()
	{
		nCameraId = -1 ;
		nSourceImageWidth = nSourceImageHeight = -1 ;
		lExposureTime = lGain = 0 ;
		nImageWidth = nImageHeight = -1 ;
		strCameraSn = "0030533004ff_Basler_acA244020gm" ;
		strCameraTipInfo = "引导相机" ;
		eCameraType = E_TOOL_NONE ;
		pCameraBase = NULL ;
		eCameraConnectType = E_CAMERA_GIGE ;
		eCameraColorType = E_CAMERA_MONO8 ;
		eCameraRotateType = E_CAMERA_ROTATE_0 ;
		eCameraMirrorType = E_CAMERA_MIRROR_NONE ;
		//eCameraTriggerMode = E_CAMERA_SOFTTRIGGER ;
		GenEmptyObj(&hImage) ;
	}

	~CCameraNode()
	{
		nCameraId = -1 ;
		nSourceImageWidth = nSourceImageHeight = -1 ;
		lExposureTime = lGain = 0 ;
		nImageWidth = nImageHeight = -1 ;
		strCameraSn = strCameraTipInfo = "" ;
		eCameraType = E_TOOL_NONE ;
		//DELETE_POINT(pCameraBase) ;
		eCameraConnectType = E_CAMERA_GIGE ;
		eCameraColorType = E_CAMERA_MONO8 ;
		eCameraRotateType = E_CAMERA_ROTATE_0 ;
		eCameraMirrorType = E_CAMERA_MIRROR_NONE ;
		//eCameraTriggerMode = E_CAMERA_SOFTTRIGGER ;
		hImage.Clear() ;
		if (pCameraBase)
		{
			delete pCameraBase ;
			pCameraBase = NULL ;
		}
	}

public:
	//相机ID
	int                    nCameraId ;
	//相机Sn号
	string                 strCameraSn ;
	//相机提示信息
	string                 strCameraTipInfo ;
	//相机类型
	VISION_TOOLTYPE        eCameraType ;
	//相机实例
	CCameraBase*           pCameraBase ;
	//相机DLl加载
	CMgrDllCameraBaseIm    mgrDllCameraBaseIm ;
	//相机连接方式
	CAMERA_CONNECTTYPE     eCameraConnectType ;
	//相机采集图像方式(灰色或者彩色)
	CAMERA_COLORTYPE       eCameraColorType ;
	//相机图像旋转模式
	CAMERA_ROTATE          eCameraRotateType ;
	//相机图像镜像模式
	CAMERA_MIRROR          eCameraMirrorType ;
	//触发模式
	CAMERA_TRIGGER_MODE    triggerMode ;
	//CAMERA_TRIGGERMODE     eCameraTriggerMode ;
	//图像
	HObject                hImage ;
	//源图像宽
	int                    nSourceImageWidth ;
	//源图像高
	int                    nSourceImageHeight ;
	//图像宽
	int                    nImageWidth ;
	//图像高
	int                    nImageHeight ;
	//相机曝光
	long                   lExposureTime ;
	//相机增益
	long                   lGain ;
};

typedef CTypedPtrList<CObList, CCameraNode *> CameraNodeList ;

class CManageCamera
{
public:
	CManageCamera()
	{
		cameraNodeList.RemoveAll() ;
	}

	~CManageCamera()
	{
		cameraNodeList.RemoveAll() ;
	}

	int GetCameraNodeListSize()
	{
		return (int)cameraNodeList.GetSize() ;
	}

	void AddTail(CCameraNode *pNewCameraNode)
	{
		if (pNewCameraNode)
		{
			cameraNodeList.AddTail(pNewCameraNode) ;
		}
	}

	void RemoveAtById(int nCameraNodeID)
	{
		if (GetCameraNodeListSize() <= 0)
		{
			return  ;
		}

		POSITION prev;
		POSITION pos = cameraNodeList.GetHeadPosition() ;
		while(pos)
		{
			prev = pos ;
			CCameraNode *pCameraNode = cameraNodeList.GetNext(pos) ;
			if (nCameraNodeID == pCameraNode->nCameraId)
			{
				cameraNodeList.RemoveAt(prev) ;
				//DELETE_POINT(pCameraNode) ;
				//pCameraNode->mgrDllCameraBaseIm.ReleaseLib() ;
				if (pCameraNode)
				{
					delete pCameraNode ;
					pCameraNode = NULL ;
				}

				break;
			}
		}
	}

	void RemoveAll()
	{
		cameraNodeList.RemoveAll() ;
	}

	CCameraNode* GetCameraNodeById(int nCameraNodeID)
	{
		if (GetCameraNodeListSize() <= 0)
		{
			return NULL ;
		}

		POSITION pos = cameraNodeList.GetHeadPosition() ;
		while(pos)
		{
			CCameraNode *pCameraNode = cameraNodeList.GetNext(pos) ;
			if (nCameraNodeID == pCameraNode->nCameraId)
			{
				return pCameraNode ;
				//break;
			}
		}

		return NULL ;
	}

	CCameraNode* GetCameraNodeBySn(string strCameraNodeSn)
	{
		if (GetCameraNodeListSize() <= 0)
		{
			return NULL ;
		}

		POSITION pos = cameraNodeList.GetHeadPosition() ;
		while(pos)
		{
			CCameraNode *pCameraNode = cameraNodeList.GetNext(pos) ;
			if (strCameraNodeSn.c_str() == pCameraNode->strCameraSn.c_str())
			{
				return pCameraNode ;
				//break;
			}
		}

		return NULL ;
	}

public:
	CameraNodeList cameraNodeList ;
};

//struct VCamera
//{
//public:
//	CCameraNode *pCamera ;
//};

//struct VisionDataBase
//{
//public:
//	VISION_DATATYPE     eVisionDataType ;
//	HTuple              hValue ;
//	HObject             hObj ;
//	CCameraNode*        pCameraNode ;
//};

//struct VCAMERA/*:public VisionDataBase*/
//{
//public:
//	//相机实例
//	CCameraBase  *pCameraBase ;
//	long         lExposureTime ;
//	long         lGain ;
//
//	VCAMERA()
//	{
//		pCameraBase = NULL ;
//		lExposureTime = 1000 ;
//		lGain = 0 ;
//	}
//
//	~VCAMERA()
//	{
//		/*if (pCameraBase)
//		{
//			delete pCameraBase ;
//			pCameraBase = NULL ;
//		}*/
//		lExposureTime = 1000 ;
//		lGain = 0 ;
//	}
//	/*
//	virtual VISION_DATATYPE type() override
//	{
//	return E_VDATA_CAMERA;
//	}*/
//};