#pragma once
#include "VisionData.h"

#include <iostream>

#define enum_to_string(x) #x

inline VISION_DATATYPE GetVisionDataType(CString strDataTypeName)
{
	try
	{
		if (_T("起点") == strDataTypeName || _T("终点") == strDataTypeName)
		{
			return E_VDATA_2DPOINT ;
		}
		else if (_T("线信息") == strDataTypeName)
		{
			return E_VDATA_LINE ;
		}
		else if (_T("横方向夹角") == strDataTypeName || _T("纵方向夹角") == strDataTypeName)
		{
			return E_VDATA_DOUBLE ;
		}
		else if (_T("模板位置") == strDataTypeName)
		{
			return E_VDATA_POS ;
		}
		else if (_T("查找位置") == strDataTypeName)
		{
			return E_VDATA_POSVEC ;
		}
		else if (_T("防射矩阵") == strDataTypeName)
		{
			return E_VDATA_MATRIX ;
		}
		else if (_T("") == strDataTypeName)
		{
		}
		else if (_T("") == strDataTypeName)
		{
		}
		else if (_T("") == strDataTypeName)
		{
		}
		else if (_T("") == strDataTypeName)
		{
		}

		return E_VDATA_NONE ;
	}
	catch (...)
	{
		return E_VDATA_NONE ;
	}
}

inline bool ProVisionFun(VISION_CODE eVisionCode,VISION_TOOLTYPE eVisionType,CString strFun)
{
	try
	{
		if (E_VCODE_OK != eVisionCode)
		{
			CString strText,strTmp ;
			string strVisionType ;
		    strVisionType = enum_to_string(eVisionType) ;
			strTmp.Format(_T(" Fun Return = %d"),(int)eVisionCode) ;
			strText = strVisionType.c_str();
			strText += strFun + strTmp ;

			OutputDebugString(strText) ;
			return false ;
		}

		return true ;
	}
	catch (...)
	{
		return false ;
	} 
}