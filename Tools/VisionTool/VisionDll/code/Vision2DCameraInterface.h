#pragma once
#include "Visionbase.h"
#include "Vision2DCameraBase.h"
#include "vCriticalSection.h"

class CVision2DCameraInterface :
	public CVisionBase
{
public:
	CVision2DCameraInterface(void);
	~CVision2DCameraInterface(void);

	virtual VISION_CODE Vision_Init()  ;

	virtual VISION_CODE Vision_Release()  ;

	virtual VISION_CODE Vision_SetLanguage(int nLanguage = 804)  ;

	virtual VISION_CODE Vision_LoadConfigure(const char* pLoadPath)  ;

	virtual VISION_CODE Vision_SetConfigurePath(const char* pSavePath)  ;

	virtual VISION_CODE Vision_ShowDialog()  ;

	virtual VISION_CODE Vision_Run(HTuple hWindowID = HTuple())  ;

	virtual VISION_CODE Vision_Input(vector<any> vecInput)  ;

	virtual VISION_CODE Vision_Output(vector<any> &vecOutput)  ;

	virtual VISION_CODE Vision_GetDisFeature(vector<any> &vecDisplayFeature)  ;

private:
	CVision2DCameraBase*        m_pVision2DCameraBase ;
	CMgrDllVision2DCameraIm     m_dllVision2DCameraIm ;
	bool                        m_bInitOk ;
	CRITICAL_SECTION            m_Critical;
};
