#pragma once
#include "VisionShapeModelBase.h"

class CVisionShapeModelInterface :
	public CVisionShapeModelBase
{
public:
	CVisionShapeModelInterface(void);
	~CVisionShapeModelInterface(void);

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
	HObject    hInputImage ;
	HObject    hTrainImage ;
	HTuple     hFixtureHom2d ;
};
