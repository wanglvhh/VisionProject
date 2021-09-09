#pragma once
#include "ModuleDevelopH.h"
#include "VisionData.h"
#include "HardWareData.h"
#include <boost/any.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/make_shared.hpp>
using namespace boost;

class CMgrDllVisionShapeModelIm : public CMgrDllDelegate
{
public:
#ifdef _DEBUG
	CMgrDllVisionShapeModelIm(LPCTSTR lpcszDllPathFullName=_T("VisionShapeModelD.dll"))
		: CMgrDllDelegate(lpcszDllPathFullName)
	{
	}
#else
	CMgrDllVisionShapeModelIm(LPCTSTR lpcszDllPathFullName=_T("VisionShapeModel.dll"))
		: CMgrDllDelegate(lpcszDllPathFullName)
	{
	}
#endif
	virtual ~CMgrDllVisionShapeModelIm(){
	}
};

class CVisionShapeModelBase
{
public:
	virtual VISION_CODE Vision_Init() = 0 ;

	virtual VISION_CODE Vision_Release() = 0 ;

	virtual VISION_CODE Vision_SetLanguage(int nLanguage = 804) = 0 ;

	virtual VISION_CODE Vision_LoadConfigure(const char* pLoadPath) = 0 ;

	virtual VISION_CODE Vision_SetConfigurePath(const char* pSavePath) = 0 ;

	virtual VISION_CODE Vision_ShowDialog() = 0 ;

	virtual VISION_CODE Vision_Run(HTuple hWindowID = HTuple()) = 0 ;

	virtual VISION_CODE Vision_Input(vector<any> vecInput) = 0 ;

	virtual VISION_CODE Vision_Output(vector<any> &vecOutput) = 0 ;

	virtual VISION_CODE Vision_GetDisFeature(vector<any> &vecDisplayFeature) = 0 ;
};