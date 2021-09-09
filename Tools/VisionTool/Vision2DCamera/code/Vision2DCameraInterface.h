#pragma once
#include "Vision2dcamerabase.h"

class CVision2DCameraInterface :
	public CVision2DCameraBase
{
public:
	CVision2DCameraInterface(void);
	~CVision2DCameraInterface(void);

	virtual VISION_CODE Vision_Init() ;

	virtual VISION_CODE Vision_Release()  ;

	virtual VISION_CODE Vision_SetLanguage(int nLanguage = 804) ;

	virtual VISION_CODE Vision_LoadConfigure(const char* pLoadPath)  ;

	virtual VISION_CODE Vision_SetConfigurePath(const char* pSavePath)  ;

	virtual VISION_CODE Vision_ShowDialog()  ;

	virtual VISION_CODE Vision_Run(HTuple hWindowID = HTuple())  ;

	virtual VISION_CODE Vision_Input(vector<any> vecInput)  ;

	virtual VISION_CODE Vision_Output(vector<any> &vecOutput)  ;

	virtual VISION_CODE Vision_GetDisFeature(vector<any> &vecDisplayFeature)  ;

private:
	CString           m_strCameraInfo ;
	CString           m_strSavePath ;
	long              m_lExposureTime ;
	long              m_lGain ;
	CCameraNode*      m_pCameraNode ;
	HObject           m_hImage ;
};
