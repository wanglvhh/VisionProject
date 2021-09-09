#pragma once
#include "Visionbase.h"
#include "VisionCommWriteBase.h"
#include "vCriticalSection.h"

class CVisionCommWriteInterface :
	public CVisionBase
{
public:
	CVisionCommWriteInterface(void);
	~CVisionCommWriteInterface(void);

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
	CVisionCommWriteBase*       m_pVisionCommWriteBase ;
	CMgrDllVisionCommWriteIm    m_dllVisionCommWriteIm ;
	bool                        m_bInitOk ;
	CRITICAL_SECTION            m_Critical;
};
