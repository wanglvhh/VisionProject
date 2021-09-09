#include "StdAfx.h"
#include "VisionFitLineInterface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CVisionFitLineInterface::CVisionFitLineInterface(void)
{
}

CVisionFitLineInterface::~CVisionFitLineInterface(void)
{
}

VISION_CODE CVisionFitLineInterface::Vision_Init()
{
	try
	{
		OutputDebugString(_T("Function(FitLine_Init) Start")) ;

		OutputDebugString(_T("Function(FitLine_Init) End")) ;
		return E_VCODE_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(FitLine_Init) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionFitLineInterface::Vision_Release()
{
	try
	{
		OutputDebugString(_T("Function(FitLine_Release) Start")) ;

		OutputDebugString(_T("Function(FitLine_Release) End")) ;
		return E_VCODE_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(FitLine_Release) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionFitLineInterface::Vision_SetLanguage(int nLanguage)
{
	try
	{
		OutputDebugString(_T("Function(FitLine_SetLanguage) Start")) ;

		OutputDebugString(_T("Function(FitLine_SetLanguage) End")) ;
		return E_VCODE_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(FitLine_SetLanguage) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionFitLineInterface::Vision_LoadConfigure(const char* pLoadPath)
{
	try
	{
		OutputDebugString(_T("Function(FitLine_LoadConfigure) Start")) ;

		OutputDebugString(_T("Function(FitLine_LoadConfigure) End")) ;
		return E_VCODE_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(FitLine_LoadConfigure) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionFitLineInterface::Vision_SetConfigurePath(const char* pSavePath)
{
	try
	{
		OutputDebugString(_T("Function(FitLine_SetConfigurePath) Start")) ;

		OutputDebugString(_T("Function(FitLine_SetConfigurePath) End")) ;
		return E_VCODE_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(FitLine_SetConfigurePath) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionFitLineInterface::Vision_ShowDialog()
{
	try
	{
		OutputDebugString(_T("Function(FitLine_ShowDialog) Start")) ;

		OutputDebugString(_T("Function(FitLine_ShowDialog) End")) ;
		return E_VCODE_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(FitLine_ShowDialog) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionFitLineInterface::Vision_Run(HTuple hWindowID)
{
	try
	{
		OutputDebugString(_T("Function(FitLine_Run) Start")) ;

		OutputDebugString(_T("Function(FitLine_Run) End")) ;
		return E_VCODE_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(FitLine_Run) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionFitLineInterface::Vision_Input(vector<any> vecInput)
{
	try
	{
		OutputDebugString(_T("Function(FitLine_Input) Start")) ;

		OutputDebugString(_T("Function(FitLine_Input) End")) ;
		return E_VCODE_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(FitLine_Input) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionFitLineInterface::Vision_Output(vector<any> &vecOutput)
{
	try
	{
		OutputDebugString(_T("Function(FitLine_Output) Start")) ;

		OutputDebugString(_T("Function(FitLine_Output) End")) ;
		return E_VCODE_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(FitLine_Output) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionFitLineInterface::Vision_GetDisFeature(vector<any> &vecDisplayFeature)
{
	try
	{
		OutputDebugString(_T("Function(FitLine_GetDisFeature) Start")) ;

		OutputDebugString(_T("Function(FitLine_GetDisFeature) End")) ;
		return E_VCODE_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(FitLine_GetDisFeature) Throw")) ;
		return E_VCODE_THROW ;
	}
}