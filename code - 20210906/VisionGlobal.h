#pragma once

#include <iostream>
using namespace std;

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include <boost/any.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/make_shared.hpp>
using namespace boost;

#include <luabind/luabind.hpp>
#include <luabind/lua_include.hpp>
#include <luabind/detail/convert_to_lua.hpp>
using namespace luabind;

static const char* const ERROR_ARGUMENT_COUNT = "参数数目错误！";
static const char* const ERROR_ARGUMENT_TYPE = "参数类型错误！";

class CGOBALVIARENT;

class CManageGobalViarent ;

class VisionGlobal
{
public:
	VisionGlobal(void);
	~VisionGlobal(void);

	//初始化Lua
	bool InitScript() ;
	//注册函数
	bool RegisterAll() ;
	//加载脚本
	bool LoadScript(const char* pScriptPath) ;
	//卸载Lua
	void CloseScript() ;
	//发生错误，报告错误
	static void ScriptErrorMsg(lua_State* L, const char* const pszErrorInfo) ;
	//检测函数调用参数个数是否正常
	static void ScriptCheckParamCount(lua_State* L, int paramCount) ;
public:
	/////////////////////////////////////系统接口///////////////////////////////////////////////////
	static int VpScript_MessageBox(lua_State* L) ;
	////////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////全局变量接口///////////////////////////////////////////////
#pragma region GobalViarentInterface
	static int VpScript_GetIntGobalViarentById(lua_State* L) ;
	static int VpScript_SetIntGobalViarentById(lua_State* L) ;
	static int VpScript_GetIntGobalViarentByName(lua_State* L) ;
	static int VpScript_SetIntGobalViarentByName(lua_State* L) ;
	static int VpScript_GetDoubleGobalViarentById(lua_State* L) ;
	static int VpScript_SetDoubleGobalViarentById(lua_State* L) ;
	static int VpScript_GetDoubleGobalViarentByName(lua_State* L) ;
	static int VpScript_SetDoubleGobalViarentByName(lua_State* L) ;
	static int VpScript_GetStringGobalViarentById(lua_State* L) ;
	static int VpScript_SetStringGobalViarentById(lua_State* L) ;
	static int VpScript_GetStringGobalViarentByName(lua_State* L) ;
	static int VpScript_SetStringGobalViarentByName(lua_State* L) ;
	static int VpScript_GetBoolGobalViarentById(lua_State* L) ;
	static int VpScript_SetBoolGobalViarentById(lua_State* L) ;
	static int VpScript_GetBoolGobalViarentByName(lua_State* L) ;
	static int VpScript_SetBoolGobalViarentByName(lua_State* L) ;
	static int VpScript_GetMatrixGobalViarentById(lua_State* L) ;
	static int VpScript_SetMatrixGobalViarentById(lua_State* L) ;
	static int VpScript_GetMatrixGobalViarentByName(lua_State* L) ;
	static int VpScript_SetMatrixGobalViarentByName(lua_State* L) ;
	static int VpScript_Get2DPosGobalViarentById(lua_State* L) ;
	static int VpScript_Set2DPosGobalViarentById(lua_State* L) ;
	static int VpScript_Get2DPosGobalViarentByName(lua_State* L) ;
	static int VpScript_Set2DPosGobalViarentByName(lua_State* L) ;
	static int VpScript_Get3DPosGobalViarentById(lua_State* L) ;
	static int VpScript_Set3DPosGobalViarentById(lua_State* L) ;
	static int VpScript_Get3DPosGobalViarentByName(lua_State* L) ;
	static int VpScript_Set3DPosGobalViarentByName(lua_State* L) ;
#pragma endregion GobalViarentInterface
	////////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////通信接口///////////////////////////////////////////////////
#pragma  region Comm
	static int VpScript_ReadDataByCommId(lua_State* L) ;
	static int VpScript_SendDataByCommId(lua_State* L) ;
	static int VpScript_ReadDataByCommName(lua_State* L) ;
	static int VpScript_SendDataByCommName(lua_State* L) ;
#pragma  endregion Comm
	////////////////////////////////////////////////////////////////////////////////////////////////

public:
	//lua脚本
	lua_State *m_pLua ;
	//lua脚本初始化状态
	static bool m_bInitStatus ;
	//当前应用程序路径
	CString m_strCurrentPath ;
};
extern VisionGlobal g_VisionGlobal ;

class CGOBALVIARENT:public CObject
{
public:
	CGOBALVIARENT()
	{
		nViarentID = -1 ;
		nViarentType = -1 ;
		strViarentName = _T("") ;
		strViarentValue = _T("") ;
		strViarentTipInfo = _T("") ;
	}

	~CGOBALVIARENT()
	{
		nViarentID = -1 ;
		nViarentType = -1 ;
		strViarentName = _T("") ;
		strViarentValue = _T("") ;
		strViarentTipInfo = _T("") ;
	}

public:
	int           nViarentID ;
	int           nViarentType ;
	CString       strViarentName ;
	CString       strViarentValue ;
	CString       strViarentTipInfo ;
	any           aViarentValue ;
};

//对外接口ImageViewDlg数据链表
typedef CTypedPtrList<CObList, CGOBALVIARENT *> GobalViarentList;

class CManageGobalViarent
{
public:
	CManageGobalViarent()
	{
	}

	~CManageGobalViarent()
	{
	}

	int GetGobalViarentListSize()
	{
		return (int)gobalViarentList.GetSize() ;
	}

	void AddTail(CGOBALVIARENT *pNewGobalViarent)
	{
		gobalViarentList.AddTail(pNewGobalViarent) ;
	}

	void RemoveAtByName(CString strViarentName)
	{
		if (GetGobalViarentListSize() <= 0)
		{
			return  ;
		}

		POSITION prev;
		POSITION pos = gobalViarentList.GetHeadPosition() ;
		while(pos)
		{
			prev = pos ;
			CGOBALVIARENT *pGobalViarent = gobalViarentList.GetNext(pos) ;
			if (strViarentName == pGobalViarent->strViarentName)
			{
				gobalViarentList.RemoveAt(prev) ;
				DELETE_POINT(pGobalViarent) ;

				break;
			}
		}
	}

	void RemoveAtById(int nViarentID)
	{
		if (GetGobalViarentListSize() <= 0)
		{
			return  ;
		}

		POSITION prev;
		POSITION pos = gobalViarentList.GetHeadPosition() ;
		while(pos)
		{
			prev = pos ;
			CGOBALVIARENT *pGobalViarent = gobalViarentList.GetNext(pos) ;
			if (nViarentID == pGobalViarent->nViarentID)
			{
				gobalViarentList.RemoveAt(prev) ;
				DELETE_POINT(pGobalViarent) ;

				break;
			}
		}
	}

	void ReSortId()
	{
		if (GetGobalViarentListSize() <= 0)
		{
			return  ;
		}

		int i = 0 ;
		POSITION pos = gobalViarentList.GetHeadPosition() ;
		while(pos)
		{
			CGOBALVIARENT *pGobalViarent = gobalViarentList.GetNext(pos) ;
			pGobalViarent->nViarentID = i++ ;
		}
	}

	void RemoveAll()
	{
		gobalViarentList.RemoveAll() ;
	}

	CGOBALVIARENT* GetGobalViarentByName(CString strViarentName)
	{
		if (GetGobalViarentListSize() <= 0)
		{
			return NULL ;
		}

		POSITION pos = gobalViarentList.GetHeadPosition() ;
		while(pos)
		{
			CGOBALVIARENT *pGobalViarent = gobalViarentList.GetNext(pos) ;
			if (strViarentName == pGobalViarent->strViarentName)
			{
				return pGobalViarent ;
			}
		}

		return NULL ;
	}

	CGOBALVIARENT* GetGobalViarentById(int nViarentID)
	{
		if (GetGobalViarentListSize() <= 0)
		{
			return NULL ;
		}

		POSITION pos = gobalViarentList.GetHeadPosition() ;
		while(pos)
		{
			CGOBALVIARENT *pGobalViarent = gobalViarentList.GetNext(pos) ;
			if (nViarentID == pGobalViarent->nViarentID)
			{
				return pGobalViarent ;
			}
		}

		return NULL ;
	}

	bool CheckViarentFormat(int nViarentValueType,CString strViarentValue)
	{
		try
		{
			//int;double;string;bool;matrix;2dpos;3dpos;
			if (strViarentValue.IsEmpty()) return true ;

			switch(nViarentValueType)
			{
			case 0:
				{
					CString strValue(_T("")) ;
					int nFind = strViarentValue.Find(',') ;
					if (nFind >= 0) return false ;
					strValue = strViarentValue ;

					break ;
				}
			case 1:
				{
					CString strValue(_T("")) ;
					int nFind = strViarentValue.Find(',') ;
					if (nFind >= 0) return false ;
					strValue = strViarentValue ;

					break ;
				}
			case 2:
				{
					CString strValue(_T("")) ;
					strValue = strViarentValue ;

					break ;
				}
			case 3:
				{
					CString strValue(_T("")) ;
					int nFind = strViarentValue.Find(',') ;
					if (nFind >= 0) return false ;
					strValue = strViarentValue ;

					break ;
				}
			case 4:
				{
					//Format:dbValue1,dbValue2,dbValue3,dbValue4,dbValue5,dbValue6
					CString strValue(_T("")) ;
					int nFind = strViarentValue.Find(',') ;
					if (nFind < 0) return false ;
					strValue = strViarentValue.Mid(0,nFind) ;
					strViarentValue = strViarentValue.Mid(nFind+1,strViarentValue.GetLength()) ;

					nFind = strViarentValue.Find(',') ;
					if (nFind < 0) return false ;
					strValue = strViarentValue.Mid(0,nFind) ;
					strViarentValue = strViarentValue.Mid(nFind+1,strViarentValue.GetLength()) ;

					nFind = strViarentValue.Find(',') ;
					if (nFind < 0) return false ;
					strValue = strViarentValue.Mid(0,nFind) ;
					strViarentValue = strViarentValue.Mid(nFind+1,strViarentValue.GetLength()) ;

					nFind = strViarentValue.Find(',') ;
					if (nFind < 0) return false ;
					strValue = strViarentValue.Mid(0,nFind) ;
					strViarentValue = strViarentValue.Mid(nFind+1,strViarentValue.GetLength()) ;

					nFind = strViarentValue.Find(',') ;
					if (nFind < 0) return false ;
					strValue = strViarentValue.Mid(0,nFind) ;
					strViarentValue = strViarentValue.Mid(nFind+1,strViarentValue.GetLength()) ;

					nFind = strViarentValue.Find(',') ;
					if (nFind >= 0) return false ;
					strValue = strViarentValue ;

					break ;
				}
			case 5:
				{
					//Format:dbValue1,dbValue2
					CString strValue(_T("")) ;
					int nFind = strViarentValue.Find(',') ;
					if (nFind < 0) return false ;
					strValue = strViarentValue.Mid(0,nFind) ;
					strViarentValue = strViarentValue.Mid(nFind+1,strViarentValue.GetLength()) ;

					nFind = strViarentValue.Find(',') ;
					if (nFind >= 0) return false ;
					strValue = strViarentValue ;

					break;
				}
			case 6:
				{
					//Format:dbValue1,dbValue2,dbValue3
					CString strValue(_T("")) ;
					int nFind = strViarentValue.Find(',') ;
					if (nFind < 0) return false ;
					strValue = strViarentValue.Mid(0,nFind) ;
					strViarentValue = strViarentValue.Mid(nFind+1,strViarentValue.GetLength()) ;

					nFind = strViarentValue.Find(',') ;
					if (nFind < 0) return false ;
					strValue = strViarentValue.Mid(0,nFind) ;
					strViarentValue = strViarentValue.Mid(nFind+1,strViarentValue.GetLength()) ;

					nFind = strViarentValue.Find(',') ;
					if (nFind >= 0) return false ;
					strValue = strViarentValue ;

					break;
				}
			default:
				break;
			}
		}
		catch (...)
		{
			return false ;
		}
		return true ;
	}

	bool GetViarentValue(int nViarentValueType,CString strViarentValue,any &aViarentValue)
	{
		try
		{
			//int;double;string;bool;matrix;2dpos;3dpos;
			if (strViarentValue.IsEmpty()) return true ;

			switch(nViarentValueType)
			{
			case 0:
				{
					CString strValue(_T("")) ;
					int nFind = strViarentValue.Find(',') ;
					if (nFind >= 0) return false ;
					strValue = strViarentValue ;
					aViarentValue = _wtoi(strValue) ;

					break ;
				}
			case 1:
				{
					CString strValue(_T("")) ;
					int nFind = strViarentValue.Find(',') ;
					if (nFind >= 0) return false ;
					strValue = strViarentValue ;
					aViarentValue = _wtof(strValue) ;

					break ;
				}
			case 2:
				{
					CString strValue(_T("")) ;
					strValue = strViarentValue ;
					aViarentValue = (CString)strValue ;

					break ;
				}
			case 3:
				{
					CString strValue(_T("")) ;
					int nFind = strViarentValue.Find(',') ;
					if (nFind >= 0) return false ;
					strValue = strViarentValue ;
					aViarentValue = (bool)_wtoi(strValue) ;

					break ;
				}
			case 4:
				{
					//Format:dbValue1,dbValue2,dbValue3,dbValue4,dbValue5,dbValue6
					HTuple hHom2d ;
					CString strValue(_T("")) ;
					int nFind = strViarentValue.Find(',') ;
					if (nFind < 0) return false ;
					strValue = strViarentValue.Mid(0,nFind) ;
					strViarentValue = strViarentValue.Mid(nFind+1,strViarentValue.GetLength()) ;
					hHom2d[0] = _wtof(strValue) ;

					nFind = strViarentValue.Find(',') ;
					if (nFind < 0) return false ;
					strValue = strViarentValue.Mid(0,nFind) ;
					strViarentValue = strViarentValue.Mid(nFind+1,strViarentValue.GetLength()) ;
					hHom2d[1] = _wtof(strValue) ;

					nFind = strViarentValue.Find(',') ;
					if (nFind < 0) return false ;
					strValue = strViarentValue.Mid(0,nFind) ;
					strViarentValue = strViarentValue.Mid(nFind+1,strViarentValue.GetLength()) ;
					hHom2d[2] = _wtof(strValue) ;

					nFind = strViarentValue.Find(',') ;
					if (nFind < 0) return false ;
					strValue = strViarentValue.Mid(0,nFind) ;
					strViarentValue = strViarentValue.Mid(nFind+1,strViarentValue.GetLength()) ;
					hHom2d[3] = _wtof(strValue) ;

					nFind = strViarentValue.Find(',') ;
					if (nFind < 0) return false ;
					strValue = strViarentValue.Mid(0,nFind) ;
					strViarentValue = strViarentValue.Mid(nFind+1,strViarentValue.GetLength()) ;
					hHom2d[4] = _wtof(strValue) ;

					nFind = strViarentValue.Find(',') ;
					if (nFind >= 0) return false ;
					strValue = strViarentValue ;
					hHom2d[5] = _wtof(strValue) ;

					aViarentValue = (HTuple)hHom2d ;

					break ;
				}
			case 5:
				{
					//Format:dbValue1,dbValue2
					V2DPoint point2D ;
					CString strValue(_T("")) ;
					int nFind = strViarentValue.Find(',') ;
					if (nFind < 0) return false ;
					strValue = strViarentValue.Mid(0,nFind) ;
					strViarentValue = strViarentValue.Mid(nFind+1,strViarentValue.GetLength()) ;
					point2D.dbX = _wtof(strValue) ;

					nFind = strViarentValue.Find(',') ;
					if (nFind >= 0) return false ;
					strValue = strViarentValue ;
					point2D.dbY = _wtof(strValue) ;

					aViarentValue = (V2DPoint)point2D ;

					break;
				}
			case 6:
				{
					//Format:dbValue1,dbValue2,dbValue3
					V3DPoint point3D ;
					CString strValue(_T("")) ;
					int nFind = strViarentValue.Find(',') ;
					if (nFind < 0) return false ;
					strValue = strViarentValue.Mid(0,nFind) ;
					strViarentValue = strViarentValue.Mid(nFind+1,strViarentValue.GetLength()) ;
					point3D.dbX = _wtof(strValue) ;

					nFind = strViarentValue.Find(',') ;
					if (nFind < 0) return false ;
					strValue = strViarentValue.Mid(0,nFind) ;
					strViarentValue = strViarentValue.Mid(nFind+1,strViarentValue.GetLength()) ;
					point3D.dbY = _wtof(strValue) ;

					nFind = strViarentValue.Find(',') ;
					if (nFind >= 0) return false ;
					strValue = strViarentValue ;
					point3D.dbZ = _wtof(strValue) ;

					aViarentValue = (V3DPoint)point3D ;

					break;
				}
			default:
				break;
			}
		}
		catch (...)
		{
			return false ;
		}
		return true ;
	}

	bool CheckViarentName(CString strNewName)
	{
		try
		{
			int nCountViarent = GetGobalViarentListSize() ;
			if (nCountViarent <= 0) return true ;

			POSITION pos = gobalViarentList.GetHeadPosition() ;
			while(pos)
			{
				CGOBALVIARENT *pGobalViarent = gobalViarentList.GetNext(pos) ;
				if (strNewName == pGobalViarent->strViarentName) return false ;
			}
		}
		catch (...)
		{
			return false ;
		}
		return true ;
	}

public:
	GobalViarentList gobalViarentList ;
};
