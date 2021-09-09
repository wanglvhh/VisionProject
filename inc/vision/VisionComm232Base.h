#pragma once
#include "ModuleDevelopH.h"
#include "VisionData.h"
#include "HardWareData.h"
#include <boost/any.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/make_shared.hpp>
using namespace boost;

class CMgrDllVisionComm232Im : public CMgrDllDelegate
{
public:
#ifdef _DEBUG
	CMgrDllVisionComm232Im(LPCTSTR lpcszDllPathFullName=_T("VisionComm232D.dll"))
		: CMgrDllDelegate(lpcszDllPathFullName)
	{
	}
#else
	CMgrDllVisionComm232Im(LPCTSTR lpcszDllPathFullName=_T("VisionComm232.dll"))
		: CMgrDllDelegate(lpcszDllPathFullName)
	{
	}
#endif
	virtual ~CMgrDllVisionComm232Im(){
	}
};

class CVisionComm232Base
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