#pragma once
#include "VisionData.h"
#include "CameraBase.h"

//����ڵ�Ԫ��
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
		strCameraTipInfo = "�������" ;
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
	//���ID
	int                    nCameraId ;
	//���Sn��
	string                 strCameraSn ;
	//�����ʾ��Ϣ
	string                 strCameraTipInfo ;
	//�������
	VISION_TOOLTYPE        eCameraType ;
	//���ʵ��
	CCameraBase*           pCameraBase ;
	//���DLl����
	CMgrDllCameraBaseIm    mgrDllCameraBaseIm ;
	//������ӷ�ʽ
	CAMERA_CONNECTTYPE     eCameraConnectType ;
	//����ɼ�ͼ��ʽ(��ɫ���߲�ɫ)
	CAMERA_COLORTYPE       eCameraColorType ;
	//���ͼ����תģʽ
	CAMERA_ROTATE          eCameraRotateType ;
	//���ͼ����ģʽ
	CAMERA_MIRROR          eCameraMirrorType ;
	//����ģʽ
	CAMERA_TRIGGER_MODE    triggerMode ;
	//CAMERA_TRIGGERMODE     eCameraTriggerMode ;
	//ͼ��
	HObject                hImage ;
	//Դͼ���
	int                    nSourceImageWidth ;
	//Դͼ���
	int                    nSourceImageHeight ;
	//ͼ���
	int                    nImageWidth ;
	//ͼ���
	int                    nImageHeight ;
	//����ع�
	long                   lExposureTime ;
	//�������
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
//	//���ʵ��
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