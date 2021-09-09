#include "StdAfx.h"
#include "VisionShapeModelInterface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CVisionShapeModelInterface::CVisionShapeModelInterface(void)
{
}

CVisionShapeModelInterface::~CVisionShapeModelInterface(void)
{
}

VISION_CODE CVisionShapeModelInterface::Vision_Init()
{
	try
	{
		OutputDebugString(_T("Function(ShapeModel_Init) Start")) ;

		OutputDebugString(_T("Function(ShapeModel_Init) End")) ;
		return E_VCODE_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(ShapeModel_Init) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionShapeModelInterface::Vision_Release()
{
	try
	{
		OutputDebugString(_T("Function(ShapeModel_Release) Start")) ;

		OutputDebugString(_T("Function(ShapeModel_Release) End")) ;
		return E_VCODE_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(ShapeModel_Release) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionShapeModelInterface::Vision_SetLanguage(int nLanguage)
{
	try
	{
		OutputDebugString(_T("Function(ShapeModel_SetLanguage) Start")) ;

		OutputDebugString(_T("Function(ShapeModel_SetLanguage) End")) ;
		return E_VCODE_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(ShapeModel_SetLanguage) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionShapeModelInterface::Vision_LoadConfigure(const char* pLoadPath)
{
	try
	{
		OutputDebugString(_T("Function(ShapeModel_LoadConfigure) Start")) ;

		OutputDebugString(_T("Function(ShapeModel_LoadConfigure) End")) ;
		return E_VCODE_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(ShapeModel_LoadConfigure) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionShapeModelInterface::Vision_SetConfigurePath(const char* pSavePath)
{
	try
	{
		OutputDebugString(_T("Function(ShapeModel_SetConfigurePath) Start")) ;

		OutputDebugString(_T("Function(ShapeModel_SetConfigurePath) End")) ;
		return E_VCODE_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(ShapeModel_SetConfigurePath) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionShapeModelInterface::Vision_ShowDialog()
{
	try
	{
		OutputDebugString(_T("Function(ShapeModel_ShowDialog) Start")) ;

		OutputDebugString(_T("Function(ShapeModel_ShowDialog) End")) ;
		return E_VCODE_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(ShapeModel_ShowDialog) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionShapeModelInterface::Vision_Run(HTuple hWindowID)
{
	try
	{
		OutputDebugString(_T("Function(ShapeModel_Run) Start")) ;

		OutputDebugString(_T("Function(ShapeModel_Run) End")) ;
		return E_VCODE_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(ShapeModel_Run) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionShapeModelInterface::Vision_Input(vector<any> vecInput)
{
	try
	{
		OutputDebugString(_T("Function(ShapeModel_Input) Start")) ;

		OutputDebugString(_T("Function(ShapeModel_Input) End")) ;
		return E_VCODE_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(ShapeModel_Input) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionShapeModelInterface::Vision_Output(vector<any> &vecOutput)
{
	try
	{
		OutputDebugString(_T("Function(ShapeModel_Output) Start")) ;

		OutputDebugString(_T("Function(ShapeModel_Output) End")) ;
		return E_VCODE_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(ShapeModel_Output) Throw")) ;
		return E_VCODE_THROW ;
	}
}

VISION_CODE CVisionShapeModelInterface::Vision_GetDisFeature(vector<any> &vecDisplayFeature)
{
	try
	{
		OutputDebugString(_T("Function(ShapeModel_GetDisFeature) Start")) ;

		OutputDebugString(_T("Function(ShapeModel_GetDisFeature) End")) ;
		return E_VCODE_OK ;
	}
	catch (...)
	{
		OutputDebugString(_T("Function(ShapeModel_GetDisFeature) Throw")) ;
		return E_VCODE_THROW ;
	}
}