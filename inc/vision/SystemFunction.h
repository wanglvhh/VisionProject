#pragma once
#include "VisionData.h"

#include <iostream>

#define enum_to_string(x) #x

inline VISION_DATATYPE GetVisionDataType(CString strDataTypeName)
{
	try
	{
		if (_T("���") == strDataTypeName || _T("�յ�") == strDataTypeName)
		{
			return E_VDATA_2DPOINT ;
		}
		else if (_T("����Ϣ") == strDataTypeName)
		{
			return E_VDATA_LINE ;
		}
		else if (_T("�᷽��н�") == strDataTypeName || _T("�ݷ���н�") == strDataTypeName)
		{
			return E_VDATA_DOUBLE ;
		}
		else if (_T("ģ��λ��") == strDataTypeName)
		{
			return E_VDATA_POS ;
		}
		else if (_T("����λ��") == strDataTypeName)
		{
			return E_VDATA_POSVEC ;
		}
		else if (_T("�������") == strDataTypeName)
		{
			return E_VDATA_MATRIX ;
		}
		else if (_T("ͼ��") == strDataTypeName)
		{
			return E_VDATA_IMAGE ;
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
