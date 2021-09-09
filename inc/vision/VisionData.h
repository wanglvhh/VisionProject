#pragma once

#include <string.h>
using namespace std ;

#include "halconcpp.h"
using namespace HalconCpp;
#include <vector>
using namespace std ;

#include "ToolType.h"

#pragma region CAMERA

typedef void (*CameraCallbackFunc)(void* pOwner,HObject *hImage/*unsigned char* pBuffer*/);

enum CAMERA_CODE
{
	E_CAMERA_THROW = -1,
	E_CAMERA_OK,
	E_CAMERA_NG,
};

enum CAMERA_TRIGGER_SOURCE
{
	E_TRIGGER_SOFTWARE = 0,
	E_TRIGGER_LINE1,
};

enum CAMERA_TRIGGER_ACTIVE
{
	E_TRIGGER_RISING_EDGE = 0,
	E_TRIGGER_FALLING_EDGE,
};

enum CAMERA_ACQUISITION_MODE
{
	E_ACQ_CONTINUOUS = 0,
	E_ACQ_SINGLEFRAME,
};

enum CAMERA_CONNECTTYPE
{
	E_CAMERA_GIGE = 0,
	E_CAMERA_USB,
	E_CAMERA_FIREWARE,
	E_CAMERA_CAMERALINK,
	E_CAMERA_1394,
};

enum CAMERA_COLORTYPE
{
	E_CAMERA_MONO8 = 0,
	E_CAMERA_BGR8,
};

enum CAMERA_ROTATE
{
	E_CAMERA_ROTATE_0 = 0,
	E_CAMERA_ROTATE_90,
	E_CAMERA_ROTATE_180,
	E_CAMERA_ROTATE_270,
};

enum CAMERA_MIRROR
{
	E_CAMERA_MIRROR_NONE = 0,
	E_CAMERA_MIRROR_ROW ,
	E_CAMERA_MIRROR_COLUMN ,
	E_CAMERA_MIRROR_DIAGONAL ,
};

struct CAMERA_TRIGGER_PARA
{
public:
	CAMERA_TRIGGER_PARA()
	{
		eTriggerSource      = E_TRIGGER_SOFTWARE ;
		eTriggerActive      = E_TRIGGER_RISING_EDGE ;
		eAcquisitionMode    = E_ACQ_CONTINUOUS ;
		lTriggerDelayTime   = 0 ;
	}

	~CAMERA_TRIGGER_PARA()
	{
		eTriggerSource      = E_TRIGGER_SOFTWARE ;
		eTriggerActive      = E_TRIGGER_RISING_EDGE ;
		eAcquisitionMode    = E_ACQ_CONTINUOUS ;
		lTriggerDelayTime   = 0 ;
	}
public:
	CAMERA_TRIGGER_SOURCE    eTriggerSource ;
	CAMERA_TRIGGER_ACTIVE    eTriggerActive ;
	CAMERA_ACQUISITION_MODE  eAcquisitionMode ;
	long                     lTriggerDelayTime ;
};

struct CAMERA_TRIGGER_MODE
{
public:
	CAMERA_TRIGGER_MODE()
	{
		bTriggerMode = false ;
	}

	~CAMERA_TRIGGER_MODE()
	{
		bTriggerMode = false ;
	}
public:
	bool                   bTriggerMode ;
	CAMERA_TRIGGER_PARA    triggerPara ;
};

#pragma endregion CAMERA

#pragma  region VISION

struct VInt
{
public:
	int vInteger ;

	VInt()
	{
		vInteger = 0;
	}

	~VInt()
	{
		vInteger = 0 ;
	}
};

struct VDouble
{
public:
	double vDouble ;

	VDouble()
	{
		vDouble = 0.0 ;
	}

	~VDouble()
	{
		vDouble = 0.0 ;
	}
};

struct VString
{
public:
	string vStr ;

	VString()
	{
		vStr = "" ;
	}

	~VString()
	{
		vStr = "" ;
	}
};

struct VImage
{
public:
	HObject vImage ;

	VImage()
	{
		GenEmptyObj(&vImage) ;
	}

	~VImage()
	{
		if (vImage.Key() != NULL)
		{
			vImage.Clear() ;
		}
	}
};

struct VRegion
{
public:
	HObject vRegion ;

	VRegion()
	{
		GenEmptyObj(&vRegion) ;
	}

	~VRegion()
	{
		if (vRegion.Key() != NULL)
		{
			vRegion.Clear() ;
		}
	}
};

struct VContour
{
public:
	HObject vContour ;

	VContour()
	{
		GenEmptyObj(&vContour) ;
	}

	~VContour()
	{
		if (vContour.Key() != NULL)
		{
			vContour.Clear() ;
		}
	}
};

struct VMatrix
{
public:
	HTuple vHtuple ;

	VMatrix()
	{
		vHtuple = HTuple() ;
	}

	~VMatrix()
	{
		vHtuple.Clear() ;
	}
};

struct V2DPoint
{
public:
	double dbX ;
	double dbY ;

	V2DPoint()
	{
		dbX = dbY = 0.0 ;
	}

	~V2DPoint()
	{
		dbX = dbY = 0.0 ;
	}
};

struct V2DPointVec
{
public:
	vector<V2DPoint> vec2DPoint ;

	V2DPointVec()
	{
		vec2DPoint.clear() ;
	}

	~V2DPointVec()
	{
		vec2DPoint.clear() ;
	}
};

struct V3DPoint
{
public:
	double dbX ;
	double dbY ;
	double dbZ ;

	V3DPoint()
	{
		dbX = dbY = dbZ = 0.0 ;
	}

	~V3DPoint()
	{
		dbX = dbY = dbZ = 0.0 ;
	}
};

struct V3DPointVec
{
public:
	vector<V3DPoint> vec3DPoint ;

	V3DPointVec()
	{
		vec3DPoint.clear() ;
	}

	~V3DPointVec()
	{
		vec3DPoint.clear() ;
	}
};

struct VLine
{
public:
	V2DPoint p1 ;
	V2DPoint p2 ;

	double AngleLineToX()
	{
		HTuple hNewStartX,hNewStartY,hNewEndX,hNewEndY,hPhi,hAngle ;
		if (p1.dbX > p2.dbX)
		{
			hNewStartX = p2.dbX ;
			hNewStartX = p2.dbY ;
			hNewEndX   = p1.dbX ;
			hNewEndY   = p1.dbY ;
		}
		else
		{
			hNewStartX = p1.dbX ;
			hNewStartX = p1.dbY ;
			hNewEndX   = p2.dbX ;
			hNewEndY   = p2.dbY ;
		}
		AngleLl(hNewStartX,hNewStartY,hNewEndX,hNewEndY,hNewStartX,hNewStartY,9999,hNewStartY,&hPhi) ;
        TupleDeg(hPhi,&hAngle) ;

		return hAngle[0].D() ;
	}

	double AngleLineToY()
	{
		HTuple hNewStartX,hNewStartY,hNewEndX,hNewEndY,hPhi,hAngle ;
		if (p1.dbY < p2.dbY)
		{
			hNewStartX = p2.dbX ;
			hNewStartX = p2.dbY ;
			hNewEndX   = p1.dbX ;
			hNewEndY   = p1.dbY ;
		}
		else
		{
			hNewStartX = p1.dbX ;
			hNewStartX = p1.dbY ;
			hNewEndX   = p2.dbX ;
			hNewEndY   = p2.dbY ;
		}

		AngleLl(hNewStartX,hNewStartY,hNewEndX,hNewEndY,hNewStartX,hNewStartY,hNewEndX,-9999,&hPhi) ;
		TupleDeg(hPhi,&hAngle) ;

		return hAngle[0].D() ;
	}
};

struct VCircle
{
public:
	double dbCircleX ;
	double dbCircleY ;
	double dbRadius ;

	VCircle()
	{
		dbCircleX = dbCircleY = dbRadius = 0.0 ;
	}

	~VCircle()
	{
		dbCircleX = dbCircleY = dbRadius = 0.0 ;
	}
};

struct VArc
{
public:
	double dbArcX ;
	double dbArcY ;
	double dbRadius ;
	double dbStartAngle ;
	double dbExternAngle ;

	VArc()
	{
		dbArcX = dbArcY = dbRadius = 0.0 ;
		dbStartAngle = dbExternAngle = 0.0 ;
	}

	~VArc()
	{
		dbArcX = dbArcY = dbRadius = 0.0 ;
		dbStartAngle = dbExternAngle = 0.0 ;
	}
};

struct VPos
{
public:
	double dbX ;
	double dbY ;
	double dbU ;

	VPos()
	{
		dbX = dbY = dbU = 0.0 ;
	}

	~VPos()
	{
		dbX = dbY = dbU = 0.0 ;
	}
};

struct VPosVec
{
public:
	vector<VPos> vecVPos ;

	VPosVec()
	{
		vecVPos.clear() ;
	}

	~VPosVec()
	{
		vecVPos.clear() ;
	}
};

struct VFont
{
public:
	int       nDisplayRow ;
	int       nDisplayCol ;
	int       nFontSize ;
	string    strInfo ;

	VFont()
	{
		nDisplayRow = 10 ;
		nDisplayCol = 10 ;
		nFontSize = 10 ;
		strInfo = "" ;
	}

	~VFont()
	{
		nDisplayRow = 10 ;
		nDisplayCol = 10 ;
		nFontSize = 10 ;
		strInfo = "" ;
	}
};

#pragma endregion VISION
