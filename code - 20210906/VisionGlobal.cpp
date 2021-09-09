#include "StdAfx.h"
#include "VisionGlobal.h"
#include "VisionProjectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define CHECKSTATUS(bStatus) {if(!bStatus) return false;}

bool VisionGlobal::m_bInitStatus = false ;

VisionGlobal g_VisionGlobal ;

VisionGlobal::VisionGlobal(void)
{
	m_pLua = NULL ;
	m_bInitStatus = false ;
}

VisionGlobal::~VisionGlobal(void)
{
	DELETE_POINT(m_pLua) ;
	m_bInitStatus = false ;
}

bool VisionGlobal::InitScript()
{
	try
	{
		// 创建Lua状态
		m_pLua = lua_open() ;
		if (!m_pLua)
		{
			m_bInitStatus = false ;
			return false;
		}
		m_bInitStatus = true ;

		luaL_openlibs(m_pLua) ;
		//注册函数
		RegisterAll() ;
	}
	catch (...)
	{
		return false ;
	}

	m_bInitStatus = true ;
	return true ;
}

bool VisionGlobal::RegisterAll()
{
	try
	{
		if (!m_bInitStatus) return false ;

		//系统接口
		lua_pushcfunction(m_pLua, VpScript_MessageBox);
		lua_setglobal    (m_pLua, "VpScript_MessageBox");

		//全局变量接口
		lua_pushcfunction(m_pLua, VpScript_GetIntGobalViarentById);
		lua_setglobal    (m_pLua, "VpScript_GetIntGobalViarentById");

		lua_pushcfunction(m_pLua, VpScript_SetIntGobalViarentById);
		lua_setglobal    (m_pLua, "VpScript_SetIntGobalViarentById");

		lua_pushcfunction(m_pLua, VpScript_GetIntGobalViarentByName);
		lua_setglobal    (m_pLua, "VpScript_GetIntGobalViarentByName");

		lua_pushcfunction(m_pLua, VpScript_SetIntGobalViarentByName);
		lua_setglobal    (m_pLua, "VpScript_SetIntGobalViarentByName");

		lua_pushcfunction(m_pLua, VpScript_GetDoubleGobalViarentById);
		lua_setglobal    (m_pLua, "VpScript_GetDoubleGobalViarentById");

		lua_pushcfunction(m_pLua, VpScript_SetDoubleGobalViarentById);
		lua_setglobal    (m_pLua, "VpScript_SetDoubleGobalViarentById");

		lua_pushcfunction(m_pLua, VpScript_GetDoubleGobalViarentByName);
		lua_setglobal    (m_pLua, "VpScript_GetDoubleGobalViarentByName");

		lua_pushcfunction(m_pLua, VpScript_SetDoubleGobalViarentByName);
		lua_setglobal    (m_pLua, "VpScript_SetDoubleGobalViarentByName");

		lua_pushcfunction(m_pLua, VpScript_GetStringGobalViarentById);
		lua_setglobal    (m_pLua, "VpScript_GetStringGobalViarentById");

		lua_pushcfunction(m_pLua, VpScript_SetStringGobalViarentById);
		lua_setglobal    (m_pLua, "VpScript_SetStringGobalViarentById");

		lua_pushcfunction(m_pLua, VpScript_GetStringGobalViarentByName);
		lua_setglobal    (m_pLua, "VpScript_GetStringGobalViarentByName");

		lua_pushcfunction(m_pLua, VpScript_SetStringGobalViarentByName);
		lua_setglobal    (m_pLua, "VpScript_SetStringGobalViarentByName");

		lua_pushcfunction(m_pLua, VpScript_GetBoolGobalViarentById);
		lua_setglobal    (m_pLua, "VpScript_GetBoolGobalViarentById");

		lua_pushcfunction(m_pLua, VpScript_SetBoolGobalViarentById);
		lua_setglobal    (m_pLua, "VpScript_SetBoolGobalViarentById");

		lua_pushcfunction(m_pLua, VpScript_GetBoolGobalViarentByName);
		lua_setglobal    (m_pLua, "VpScript_GetBoolGobalViarentByName");

		lua_pushcfunction(m_pLua, VpScript_SetBoolGobalViarentByName);
		lua_setglobal    (m_pLua, "VpScript_SetBoolGobalViarentByName");

		lua_pushcfunction(m_pLua, VpScript_GetMatrixGobalViarentById);
		lua_setglobal    (m_pLua, "VpScript_GetMatrixGobalViarentById");

		lua_pushcfunction(m_pLua, VpScript_SetMatrixGobalViarentById);
		lua_setglobal    (m_pLua, "VpScript_SetMatrixGobalViarentById");

		lua_pushcfunction(m_pLua, VpScript_GetMatrixGobalViarentByName);
		lua_setglobal    (m_pLua, "VpScript_GetMatrixGobalViarentByName");

		lua_pushcfunction(m_pLua, VpScript_SetMatrixGobalViarentByName);
		lua_setglobal    (m_pLua, "VpScript_SetMatrixGobalViarentByName");

		lua_pushcfunction(m_pLua, VpScript_Get2DPosGobalViarentById);
		lua_setglobal    (m_pLua, "VpScript_Get2DPosGobalViarentById");

		lua_pushcfunction(m_pLua, VpScript_Set2DPosGobalViarentById);
		lua_setglobal    (m_pLua, "VpScript_Set2DPosGobalViarentById");

		lua_pushcfunction(m_pLua, VpScript_Get2DPosGobalViarentByName);
		lua_setglobal    (m_pLua, "VpScript_Get2DPosGobalViarentByName");

		lua_pushcfunction(m_pLua, VpScript_Set2DPosGobalViarentByName);
		lua_setglobal    (m_pLua, "VpScript_Set2DPosGobalViarentByName");

		lua_pushcfunction(m_pLua, VpScript_Get3DPosGobalViarentById);
		lua_setglobal    (m_pLua, "VpScript_Get3DPosGobalViarentById");

		lua_pushcfunction(m_pLua, VpScript_Set3DPosGobalViarentById);
		lua_setglobal    (m_pLua, "VpScript_Set3DPosGobalViarentById");

		lua_pushcfunction(m_pLua, VpScript_Get3DPosGobalViarentByName);
		lua_setglobal    (m_pLua, "VpScript_Get3DPosGobalViarentByName");

		lua_pushcfunction(m_pLua, VpScript_Set3DPosGobalViarentByName);
		lua_setglobal    (m_pLua, "VpScript_Set3DPosGobalViarentByName");

		lua_pushcfunction(m_pLua, VpScript_ReadDataByCommId);
		lua_setglobal    (m_pLua, "VpScript_ReadDataByCommId");

		lua_pushcfunction(m_pLua, VpScript_SendDataByCommId);
		lua_setglobal    (m_pLua, "VpScript_SendDataByCommId");

		lua_pushcfunction(m_pLua, VpScript_ReadDataByCommName);
		lua_setglobal    (m_pLua, "VpScript_ReadDataByCommName");

		lua_pushcfunction(m_pLua, VpScript_SendDataByCommName);
		lua_setglobal    (m_pLua, "VpScript_SendDataByCommName");
	}
	catch (...)
	{
		return false ;
	}

	return true ;
}

bool VisionGlobal::LoadScript(const char* pScriptPath)
{
	USES_CONVERSION ;
	try
	{
		if (!m_bInitStatus) return false ;

		CString strScriptPath(pScriptPath) ;
		if (!vFileIsExist(strScriptPath)) return false ;
		// 如果需要马上执行Lua脚本可以用luaL_dofile宏
		if( luaL_dofile(m_pLua, W2A(strScriptPath)) )
		{
			CString str;
			str.Format(L"Load lua file error:");
			str += lua_tostring(m_pLua, -1);
			AfxMessageBox(str);
			return false ;
		}
	}
	catch (...)
	{
		return false ;
	}

	return true ;
}

void VisionGlobal::CloseScript()
{
	try
	{
		if (m_pLua)
		{
			lua_close(m_pLua) ;
		}
	}
	catch (...)
	{
	}
}

void VisionGlobal::ScriptErrorMsg(lua_State* L, const char* const pszErrorInfo)
{
	try
	{
		lua_pushstring(L, pszErrorInfo);
		lua_error(L);
	}
	catch (...)
	{
	}
}

void VisionGlobal::ScriptCheckParamCount(lua_State* L, int paramCount)
{
	try
	{
		// lua_gettop获取栈中元素个数.
		if (lua_gettop(L) != paramCount)
		{
			ScriptErrorMsg(L, ERROR_ARGUMENT_COUNT);
		}
	}
	catch (...)
	{
	}
}

#pragma region     SystemInterface

int VisionGlobal::VpScript_MessageBox(lua_State* L)
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		USES_CONVERSION ;

		CString strMessage(_T(""))  ;

		ScriptCheckParamCount(L,1) ;
		strMessage = lua_tostring(L,1) ;
		AfxMessageBox(strMessage) ;

		return 0 ;
	}
	catch (...)
	{
		return 0;
	}
}

#pragma endregion  SystemInterface

#pragma region     GobalViarentInterface

int VisionGlobal::VpScript_GetIntGobalViarentById(lua_State* L)
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		int nGobalViarentId = -1 ;

		ScriptCheckParamCount(L,1) ;
		nGobalViarentId = lua_tointeger(L,1) ;

		int nCountGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentListSize() ;
		if (nCountGobalViarent <= 0)
		{
			lua_pushboolean(L,false) ;
			lua_pushinteger(L,0) ;
			AfxMessageBox(_T("全局变量列表为空")) ;
			return 2 ;
		}

		if (nGobalViarentId < 0 || nGobalViarentId >= nCountGobalViarent)
		{
			lua_pushboolean(L,false) ;
			lua_pushinteger(L,0) ;
			AfxMessageBox(_T("全局变量Id越界")) ;
			return 2 ;
		}

		CGOBALVIARENT *pGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentById(nGobalViarentId) ;
		if (NULL == pGobalViarent)
		{
			lua_pushboolean(L,false) ;
			lua_pushinteger(L,0) ;
			AfxMessageBox(_T("获取全局变量为空")) ;
			return 2 ;
		}

		lua_pushboolean(L,true) ;
		lua_pushinteger(L,any_cast<int>(pGobalViarent->aViarentValue)) ;
		return 2 ;
	}
	catch (...)
	{
		lua_pushboolean(L,false) ;
		lua_pushinteger(L,0) ;
		return 2 ;
	}
}

int VisionGlobal::VpScript_SetIntGobalViarentById(lua_State* L)
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		int nGobalViarentId = -1,nSetValue = 0 ;

		ScriptCheckParamCount(L,2) ;
		nGobalViarentId = lua_tointeger(L,1) ;
		nSetValue       = lua_tointeger(L,2) ;

		int nCountGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentListSize() ;
		if (nCountGobalViarent <= 0)
		{
			lua_pushboolean(L,false) ;
			AfxMessageBox(_T("全局变量列表为空")) ;
			return 1 ;
		}

		if (nGobalViarentId < 0 || nGobalViarentId >= nCountGobalViarent)
		{
			lua_pushboolean(L,false) ;
			AfxMessageBox(_T("全局变量Id越界")) ;
			return 1 ;
		}

		CGOBALVIARENT *pGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentById(nGobalViarentId) ;
		if (NULL == pGobalViarent)
		{
			lua_pushboolean(L,false) ;
			AfxMessageBox(_T("获取全局变量为空")) ;
			return 1 ;
		}

		pGobalViarent->aViarentValue = nSetValue ;
		pGobalViarent->strViarentValue.Format(_T("%d"),nSetValue) ;

		lua_pushboolean(L,true) ;
		return 1 ;
	}
	catch (...)
	{
		lua_pushboolean(L,false) ;
		return 1 ;
	}
}

int VisionGlobal::VpScript_GetIntGobalViarentByName(lua_State* L)
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		CString strGobalViarentName(_T(""));

		ScriptCheckParamCount(L,1) ;
		strGobalViarentName = lua_tostring(L,1) ;

		int nCountGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentListSize() ;
		if (nCountGobalViarent <= 0)
		{
			lua_pushboolean(L,false) ;
			lua_pushinteger(L,0) ;
			AfxMessageBox(_T("全局变量列表为空")) ;
			return 2 ;
		}

		CGOBALVIARENT *pGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentByName(strGobalViarentName) ;
		if (NULL == pGobalViarent)
		{
			lua_pushboolean(L,false) ;
			lua_pushinteger(L,0) ;
			AfxMessageBox(_T("获取全局变量为空")) ;
			return 2 ;
		}

		lua_pushboolean(L,true) ;
		lua_pushinteger(L,any_cast<int>(pGobalViarent->aViarentValue)) ;
		return 2 ;
	}
	catch (...)
	{
		lua_pushboolean(L,false) ;
		lua_pushinteger(L,0) ;
		return 2 ;
	}
}

int VisionGlobal::VpScript_SetIntGobalViarentByName(lua_State* L)
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		CString strGobalViarentName(_T(""));
		int nSetValue = 0 ;

		ScriptCheckParamCount(L,2) ;
		strGobalViarentName = lua_tostring(L,1) ;
		nSetValue           = lua_tointeger(L,2) ;

		int nCountGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentListSize() ;
		if (nCountGobalViarent <= 0)
		{
			lua_pushboolean(L,false) ;
			AfxMessageBox(_T("全局变量列表为空")) ;
			return 1 ;
		}

		CGOBALVIARENT *pGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentByName(strGobalViarentName) ;
		if (NULL == pGobalViarent)
		{
			lua_pushboolean(L,false) ;
			AfxMessageBox(_T("获取全局变量为空")) ;
			return 1 ;
		}

		pGobalViarent->aViarentValue = nSetValue ;
		pGobalViarent->strViarentValue.Format(_T("%d"),nSetValue) ;

		lua_pushboolean(L,true) ;
		return 1 ;
	}
	catch (...)
	{
		lua_pushboolean(L,false) ;
		return 1 ;
	}
}

int VisionGlobal::VpScript_GetDoubleGobalViarentById(lua_State* L)
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		int nGobalViarentId = -1 ;

		ScriptCheckParamCount(L,1) ;
		nGobalViarentId = lua_tointeger(L,1) ;

		int nCountGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentListSize() ;
		if (nCountGobalViarent <= 0)
		{
			lua_pushboolean(L,false) ;
			lua_pushnumber(L,0.0) ;
			AfxMessageBox(_T("全局变量列表为空")) ;
			return 2 ;
		}

		if (nGobalViarentId < 0 || nGobalViarentId >= nCountGobalViarent)
		{
			lua_pushboolean(L,false) ;
			lua_pushnumber(L,0.0) ;
			AfxMessageBox(_T("全局变量Id越界")) ;
			return 2 ;
		}

		CGOBALVIARENT *pGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentById(nGobalViarentId) ;
		if (NULL == pGobalViarent)
		{
			lua_pushboolean(L,false) ;
			lua_pushnumber(L,0.0) ;
			AfxMessageBox(_T("获取全局变量为空")) ;
			return 2 ;
		}

		lua_pushboolean(L,true) ;
		lua_pushnumber(L,any_cast<double>(pGobalViarent->aViarentValue)) ;
		return 2 ;
	}
	catch (...)
	{
		lua_pushboolean(L,false) ;
		lua_pushnumber(L,0.0) ;
		return 2 ;
	}
}

int VisionGlobal::VpScript_SetDoubleGobalViarentById(lua_State* L)
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		int nGobalViarentId = -1 ;
		double dbSetValue = 0.0 ;

		ScriptCheckParamCount(L,2) ;
		nGobalViarentId = lua_tointeger(L,1) ;
		dbSetValue      = lua_tonumber(L,2) ;

		int nCountGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentListSize() ;
		if (nCountGobalViarent <= 0)
		{
			lua_pushboolean(L,false) ;
			AfxMessageBox(_T("全局变量列表为空")) ;
			return 1 ;
		}

		if (nGobalViarentId < 0 || nGobalViarentId >= nCountGobalViarent)
		{
			lua_pushboolean(L,false) ;
			AfxMessageBox(_T("全局变量Id越界")) ;
			return 1 ;
		}

		CGOBALVIARENT *pGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentById(nGobalViarentId) ;
		if (NULL == pGobalViarent)
		{
			lua_pushboolean(L,false) ;
			AfxMessageBox(_T("获取全局变量为空")) ;
			return 1 ;
		}

		pGobalViarent->aViarentValue = dbSetValue ;
		pGobalViarent->strViarentValue.Format(_T("%f"),dbSetValue) ;

		lua_pushboolean(L,true) ;
		return 1 ;
	}
	catch (...)
	{
		lua_pushboolean(L,false) ;
		return 1 ;
	}
}

int VisionGlobal::VpScript_GetDoubleGobalViarentByName(lua_State* L)
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		CString strGobalViarentName(_T(""));

		ScriptCheckParamCount(L,1) ;
		strGobalViarentName = lua_tostring(L,1) ;

		int nCountGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentListSize() ;
		if (nCountGobalViarent <= 0)
		{
			lua_pushboolean(L,false) ;
			lua_pushnumber(L,0.0) ;
			AfxMessageBox(_T("全局变量列表为空")) ;
			return 2 ;
		}

		CGOBALVIARENT *pGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentByName(strGobalViarentName) ;
		if (NULL == pGobalViarent)
		{
			lua_pushboolean(L,false) ;
			lua_pushnumber(L,0.0) ;
			AfxMessageBox(_T("获取全局变量为空")) ;
			return 2 ;
		}

		lua_pushboolean(L,true) ;
		lua_pushnumber(L,any_cast<double>(pGobalViarent->aViarentValue)) ;
		return 2 ;
	}
	catch (...)
	{
		lua_pushboolean(L,false) ;
		lua_pushnumber(L,0.0) ;
		return 2 ;
	}
}

int VisionGlobal::VpScript_SetDoubleGobalViarentByName(lua_State* L)
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		CString strGobalViarentName(_T(""));
		double dbSetValue = 0.0 ;

		ScriptCheckParamCount(L,2) ;
		strGobalViarentName = lua_tostring(L,1) ;
		dbSetValue          = lua_tonumber(L,2) ;

		int nCountGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentListSize() ;
		if (nCountGobalViarent <= 0)
		{
			lua_pushboolean(L,false) ;
			AfxMessageBox(_T("全局变量列表为空")) ;
			return 1 ;
		}

		CGOBALVIARENT *pGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentByName(strGobalViarentName) ;
		if (NULL == pGobalViarent)
		{
			lua_pushboolean(L,false) ;
			AfxMessageBox(_T("获取全局变量为空")) ;
			return 1 ;
		}

		pGobalViarent->aViarentValue = dbSetValue ;
		pGobalViarent->strViarentValue.Format(_T("%f"),dbSetValue) ;

		lua_pushboolean(L,true) ;
		return 1 ;
	}
	catch (...)
	{
		lua_pushboolean(L,false) ;
		return 1 ;
	}
}

int VisionGlobal::VpScript_GetStringGobalViarentById(lua_State* L)
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		USES_CONVERSION ;

		int nGobalViarentId = -1 ;

		ScriptCheckParamCount(L,1) ;
		nGobalViarentId = lua_tointeger(L,1) ;

		int nCountGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentListSize() ;
		if (nCountGobalViarent <= 0)
		{
			lua_pushboolean(L,false) ;
			lua_pushstring(L,"") ;
			AfxMessageBox(_T("全局变量列表为空")) ;
			return 2 ;
		}

		if (nGobalViarentId < 0 || nGobalViarentId >= nCountGobalViarent)
		{
			lua_pushboolean(L,false) ;
			lua_pushstring(L,"") ;
			AfxMessageBox(_T("全局变量Id越界")) ;
			return 2 ;
		}

		CGOBALVIARENT *pGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentById(nGobalViarentId) ;
		if (NULL == pGobalViarent)
		{
			lua_pushboolean(L,false) ;
			lua_pushstring(L,"") ;
			AfxMessageBox(_T("获取全局变量为空")) ;
			return 2 ;
		}

		lua_pushboolean(L,true) ;
		lua_pushstring(L,W2A(any_cast<CString>(pGobalViarent->aViarentValue))) ;
		return 2 ;
	}
	catch (...)
	{
		lua_pushboolean(L,false) ;
		lua_pushstring(L,"") ;
		return 2 ;
	}
}

int VisionGlobal::VpScript_SetStringGobalViarentById(lua_State* L)
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		int nGobalViarentId = -1 ;
		CString strSetValue(_T("")) ;

		ScriptCheckParamCount(L,2) ;
		nGobalViarentId = lua_tointeger(L,1) ;
		strSetValue     = lua_tostring(L,2) ;

		int nCountGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentListSize() ;
		if (nCountGobalViarent <= 0)
		{
			lua_pushboolean(L,false) ;
			AfxMessageBox(_T("全局变量列表为空")) ;
			return 1 ;
		}

		if (nGobalViarentId < 0 || nGobalViarentId >= nCountGobalViarent)
		{
			lua_pushboolean(L,false) ;
			AfxMessageBox(_T("全局变量Id越界")) ;
			return 1 ;
		}

		CGOBALVIARENT *pGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentById(nGobalViarentId) ;
		if (NULL == pGobalViarent)
		{
			lua_pushboolean(L,false) ;
			AfxMessageBox(_T("获取全局变量为空")) ;
			return 1 ;
		}

		pGobalViarent->aViarentValue = strSetValue ;
		pGobalViarent->strViarentValue = strSetValue ;

		lua_pushboolean(L,true) ;
		return 1 ;
	}
	catch (...)
	{
		lua_pushboolean(L,false) ;
		return 1 ;
	}
}

int VisionGlobal::VpScript_GetStringGobalViarentByName(lua_State* L)
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		USES_CONVERSION ;

		CString strGobalViarentName(_T(""));

		ScriptCheckParamCount(L,1) ;
		strGobalViarentName = lua_tostring(L,1) ;

		int nCountGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentListSize() ;
		if (nCountGobalViarent <= 0)
		{
			lua_pushboolean(L,false) ;
			lua_pushstring(L,"") ;
			AfxMessageBox(_T("全局变量列表为空")) ;
			return 2 ;
		}

		CGOBALVIARENT *pGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentByName(strGobalViarentName) ;
		if (NULL == pGobalViarent)
		{
			lua_pushboolean(L,false) ;
			lua_pushstring(L,"") ;
			AfxMessageBox(_T("获取全局变量为空")) ;
			return 2 ;
		}

		lua_pushboolean(L,true) ;
		lua_pushstring(L,W2A(any_cast<CString>(pGobalViarent->aViarentValue))) ;
		return 2 ;
	}
	catch (...)
	{
		lua_pushboolean(L,false) ;
		lua_pushstring(L,"") ;
		return 2 ;
	}
}

int VisionGlobal::VpScript_SetStringGobalViarentByName(lua_State* L)
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		CString strGobalViarentName(_T(""));
		CString strSetValue(_T("")) ;

		ScriptCheckParamCount(L,2) ;
		strGobalViarentName = lua_tostring(L,1) ;
		strSetValue         = lua_tostring(L,2) ;

		int nCountGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentListSize() ;
		if (nCountGobalViarent <= 0)
		{
			lua_pushboolean(L,false) ;
			AfxMessageBox(_T("全局变量列表为空")) ;
			return 1 ;
		}

		CGOBALVIARENT *pGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentByName(strGobalViarentName) ;
		if (NULL == pGobalViarent)
		{
			lua_pushboolean(L,false) ;
			AfxMessageBox(_T("获取全局变量为空")) ;
			return 1 ;
		}

		pGobalViarent->aViarentValue = strSetValue ;
		pGobalViarent->strViarentValue = strSetValue ;

		lua_pushboolean(L,true) ;
		return 1 ;
	}
	catch (...)
	{
		lua_pushboolean(L,false) ;
		return 1 ;
	}
}

int VisionGlobal::VpScript_GetBoolGobalViarentById(lua_State* L)
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		USES_CONVERSION ;

		int nGobalViarentId = -1 ;

		ScriptCheckParamCount(L,1) ;
		nGobalViarentId = lua_tointeger(L,1) ;

		int nCountGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentListSize() ;
		if (nCountGobalViarent <= 0)
		{
			lua_pushboolean(L,false) ;
			lua_pushboolean(L,false) ;
			AfxMessageBox(_T("全局变量列表为空")) ;
			return 2 ;
		}

		if (nGobalViarentId < 0 || nGobalViarentId >= nCountGobalViarent)
		{
			lua_pushboolean(L,false) ;
			lua_pushboolean(L,false) ;
			AfxMessageBox(_T("全局变量Id越界")) ;
			return 2 ;
		}

		CGOBALVIARENT *pGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentById(nGobalViarentId) ;
		if (NULL == pGobalViarent)
		{
			lua_pushboolean(L,false) ;
			lua_pushboolean(L,false) ;
			AfxMessageBox(_T("获取全局变量为空")) ;
			return 2 ;
		}

		lua_pushboolean(L,true) ;
		lua_pushboolean(L,any_cast<bool>(pGobalViarent->aViarentValue)) ;
		return 2 ;
	}
	catch (...)
	{
		lua_pushboolean(L,false) ;
		lua_pushboolean(L,false) ;
		return 2 ;
	}
}

int VisionGlobal::VpScript_SetBoolGobalViarentById(lua_State* L)
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		int nGobalViarentId = -1 ;
		bool bSetValue(false) ;

		ScriptCheckParamCount(L,2) ;
		nGobalViarentId = lua_tointeger(L,1) ;
		bSetValue       = lua_toboolean(L,2) ;

		int nCountGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentListSize() ;
		if (nCountGobalViarent <= 0)
		{
			lua_pushboolean(L,false) ;
			AfxMessageBox(_T("全局变量列表为空")) ;
			return 1 ;
		}

		if (nGobalViarentId < 0 || nGobalViarentId >= nCountGobalViarent)
		{
			lua_pushboolean(L,false) ;
			AfxMessageBox(_T("全局变量Id越界")) ;
			return 1 ;
		}

		CGOBALVIARENT *pGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentById(nGobalViarentId) ;
		if (NULL == pGobalViarent)
		{
			lua_pushboolean(L,false) ;
			AfxMessageBox(_T("获取全局变量为空")) ;
			return 1 ;
		}

		pGobalViarent->aViarentValue = bSetValue ;
		pGobalViarent->strViarentValue.Format(_T("%d"),(int)bSetValue) ;

		lua_pushboolean(L,true) ;
		return 1 ;
	}
	catch (...)
	{
		lua_pushboolean(L,false) ;
		return 1 ;
	}
}

int VisionGlobal::VpScript_GetBoolGobalViarentByName(lua_State* L)
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		USES_CONVERSION ;

		CString strGobalViarentName(_T(""));

		ScriptCheckParamCount(L,1) ;
		strGobalViarentName = lua_tostring(L,1) ;

		int nCountGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentListSize() ;
		if (nCountGobalViarent <= 0)
		{
			lua_pushboolean(L,false) ;
			lua_pushboolean(L,false) ;
			AfxMessageBox(_T("全局变量列表为空")) ;
			return 2 ;
		}

		CGOBALVIARENT *pGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentByName(strGobalViarentName) ;
		if (NULL == pGobalViarent)
		{
			lua_pushboolean(L,false) ;
			lua_pushboolean(L,false) ;
			AfxMessageBox(_T("获取全局变量为空")) ;
			return 2 ;
		}

		lua_pushboolean(L,true) ;
		lua_pushboolean(L,any_cast<bool>(pGobalViarent->aViarentValue)) ;
		return 2 ;
	}
	catch (...)
	{
		lua_pushboolean(L,false) ;
		lua_pushboolean(L,false) ;
		return 2 ;
	}
}

int VisionGlobal::VpScript_SetBoolGobalViarentByName(lua_State* L)
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		CString strGobalViarentName(_T(""));
		bool bSetValue(false) ;

		ScriptCheckParamCount(L,2) ;
		strGobalViarentName = lua_tostring(L,1) ;
		bSetValue           = lua_toboolean(L,2) ;

		int nCountGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentListSize() ;
		if (nCountGobalViarent <= 0)
		{
			lua_pushboolean(L,false) ;
			AfxMessageBox(_T("全局变量列表为空")) ;
			return 1 ;
		}

		CGOBALVIARENT *pGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentByName(strGobalViarentName) ;
		if (NULL == pGobalViarent)
		{
			lua_pushboolean(L,false) ;
			AfxMessageBox(_T("获取全局变量为空")) ;
			return 1 ;
		}

		pGobalViarent->aViarentValue = bSetValue ;
		pGobalViarent->strViarentValue.Format(_T("%d"),(int)bSetValue) ;

		lua_pushboolean(L,true) ;
		return 1 ;
	}
	catch (...)
	{
		lua_pushboolean(L,false) ;
		return 1 ;
	}
}

int VisionGlobal::VpScript_GetMatrixGobalViarentById(lua_State* L)
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		USES_CONVERSION ;

		int nGobalViarentId = -1 ;

		ScriptCheckParamCount(L,1) ;
		nGobalViarentId = lua_tointeger(L,1) ;

		int nCountGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentListSize() ;
		if (nCountGobalViarent <= 0)
		{
			lua_pushboolean(L,false) ;
			lua_pushstring(L,"") ;
			AfxMessageBox(_T("全局变量列表为空")) ;
			return 2 ;
		}

		if (nGobalViarentId < 0 || nGobalViarentId >= nCountGobalViarent)
		{
			lua_pushboolean(L,false) ;
			lua_pushstring(L,"") ;
			AfxMessageBox(_T("全局变量Id越界")) ;
			return 2 ;
		}

		CGOBALVIARENT *pGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentById(nGobalViarentId) ;
		if (NULL == pGobalViarent)
		{
			lua_pushboolean(L,false) ;
			lua_pushstring(L,"") ;
			AfxMessageBox(_T("获取全局变量为空")) ;
			return 2 ;
		}

		lua_pushboolean(L,true) ;
		lua_pushstring(L,T2A(pGobalViarent->strViarentValue)) ;
		return 2 ;
	}
	catch (...)
	{
		lua_pushboolean(L,false) ;
		lua_pushstring(L,"") ;
		return 2 ;
	}
}

int VisionGlobal::VpScript_SetMatrixGobalViarentById(lua_State* L)
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		int nGobalViarentId = -1 ;
		CString strSetValue(_T("")) ;

		ScriptCheckParamCount(L,2) ;
		nGobalViarentId = lua_tointeger(L,1) ;
		strSetValue     = lua_tostring(L,2) ;

		int nCountGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentListSize() ;
		if (nCountGobalViarent <= 0)
		{
			lua_pushboolean(L,false) ;
			AfxMessageBox(_T("全局变量列表为空")) ;
			return 1 ;
		}

		if (nGobalViarentId < 0 || nGobalViarentId >= nCountGobalViarent)
		{
			lua_pushboolean(L,false) ;
			AfxMessageBox(_T("全局变量Id越界")) ;
			return 1 ;
		}

		CGOBALVIARENT *pGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentById(nGobalViarentId) ;
		if (NULL == pGobalViarent)
		{
			lua_pushboolean(L,false) ;
			AfxMessageBox(_T("获取全局变量为空")) ;
			return 1 ;
		}

		if (!pDlg->m_projectData.m_mgGobalViarent.CheckViarentFormat(pGobalViarent->nViarentType,strSetValue))
		{
			lua_pushboolean(L,false) ;
			AfxMessageBox(_T("设置矩阵格式不对")) ;
			return 1 ;
		}

		pGobalViarent->strViarentValue = strSetValue ;
		pDlg->m_projectData.m_mgGobalViarent.GetViarentValue(pGobalViarent->nViarentType,strSetValue,pGobalViarent->aViarentValue) ;

		lua_pushboolean(L,true) ;
		return 1 ;
	}
	catch (...)
	{
		lua_pushboolean(L,false) ;
		return 1 ;
	}
}

int VisionGlobal::VpScript_GetMatrixGobalViarentByName(lua_State* L)
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		USES_CONVERSION ;

		CString strGobalViarentName(_T(""));

		ScriptCheckParamCount(L,1) ;
		strGobalViarentName = lua_tostring(L,1) ;

		int nCountGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentListSize() ;
		if (nCountGobalViarent <= 0)
		{
			lua_pushboolean(L,false) ;
			lua_pushstring(L,"") ;
			AfxMessageBox(_T("全局变量列表为空")) ;
			return 2 ;
		}

		CGOBALVIARENT *pGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentByName(strGobalViarentName) ;
		if (NULL == pGobalViarent)
		{
			lua_pushboolean(L,false) ;
			lua_pushstring(L,"") ;
			AfxMessageBox(_T("获取全局变量为空")) ;
			return 2 ;
		}

		lua_pushboolean(L,true) ;
		lua_pushstring(L,T2A(pGobalViarent->strViarentValue)) ;
		return 2 ;
	}
	catch (...)
	{
		lua_pushboolean(L,false) ;
		lua_pushstring(L,"") ;
		return 2 ;
	}
}

int VisionGlobal::VpScript_SetMatrixGobalViarentByName(lua_State* L)
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		CString strGobalViarentName(_T(""));
		CString strSetValue(_T("")) ;

		ScriptCheckParamCount(L,2) ;
		strGobalViarentName = lua_tostring(L,1) ;
		strSetValue         = lua_tostring(L,2) ;

		int nCountGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentListSize() ;
		if (nCountGobalViarent <= 0)
		{
			lua_pushboolean(L,false) ;
			AfxMessageBox(_T("全局变量列表为空")) ;
			return 1 ;
		}

		CGOBALVIARENT *pGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentByName(strGobalViarentName) ;
		if (NULL == pGobalViarent)
		{
			lua_pushboolean(L,false) ;
			AfxMessageBox(_T("获取全局变量为空")) ;
			return 1 ;
		}

		if (!pDlg->m_projectData.m_mgGobalViarent.CheckViarentFormat(pGobalViarent->nViarentType,strSetValue))
		{
			lua_pushboolean(L,false) ;
			AfxMessageBox(_T("设置矩阵格式不对")) ;
			return 1 ;
		}

		pGobalViarent->strViarentValue = strSetValue ;
		pDlg->m_projectData.m_mgGobalViarent.GetViarentValue(pGobalViarent->nViarentType,strSetValue,pGobalViarent->aViarentValue) ;

		lua_pushboolean(L,true) ;
		return 1 ;
	}
	catch (...)
	{
		lua_pushboolean(L,false) ;
		return 1 ;
	}
}

int VisionGlobal::VpScript_Get2DPosGobalViarentById(lua_State* L)
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		USES_CONVERSION ;

		int nGobalViarentId = -1 ;

		ScriptCheckParamCount(L,1) ;
		nGobalViarentId = lua_tointeger(L,1) ;

		int nCountGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentListSize() ;
		if (nCountGobalViarent <= 0)
		{
			lua_pushboolean(L,false) ;
			lua_pushstring(L,"") ;
			AfxMessageBox(_T("全局变量列表为空")) ;
			return 2 ;
		}

		if (nGobalViarentId < 0 || nGobalViarentId >= nCountGobalViarent)
		{
			lua_pushboolean(L,false) ;
			lua_pushstring(L,"") ;
			AfxMessageBox(_T("全局变量Id越界")) ;
			return 2 ;
		}

		CGOBALVIARENT *pGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentById(nGobalViarentId) ;
		if (NULL == pGobalViarent)
		{
			lua_pushboolean(L,false) ;
			lua_pushstring(L,"") ;
			AfxMessageBox(_T("获取全局变量为空")) ;
			return 2 ;
		}

		CString strValue(_T("")) ;
		V2DPoint point2D = any_cast<V2DPoint>(pGobalViarent->aViarentValue);
		strValue.Format(_T("%.5f,%.5f"),point2D.dbX,point2D.dbY) ;

		lua_pushboolean(L,true) ;
		lua_pushstring(L,W2A(strValue)) ;
		return 2 ;
	}
	catch (...)
	{
		lua_pushboolean(L,false) ;
		lua_pushstring(L,"") ;
		return 2 ;
	}
}

int VisionGlobal::VpScript_Set2DPosGobalViarentById(lua_State* L)
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		int nGobalViarentId = -1 ;
		CString strSetValue(_T("")) ;

		ScriptCheckParamCount(L,2) ;
		nGobalViarentId = lua_tointeger(L,1) ;
		strSetValue     = lua_tostring(L,2) ;

		int nCountGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentListSize() ;
		if (nCountGobalViarent <= 0)
		{
			lua_pushboolean(L,false) ;
			AfxMessageBox(_T("全局变量列表为空")) ;
			return 1 ;
		}

		if (nGobalViarentId < 0 || nGobalViarentId >= nCountGobalViarent)
		{
			lua_pushboolean(L,false) ;
			AfxMessageBox(_T("全局变量Id越界")) ;
			return 1 ;
		}

		CGOBALVIARENT *pGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentById(nGobalViarentId) ;
		if (NULL == pGobalViarent)
		{
			lua_pushboolean(L,false) ;
			AfxMessageBox(_T("获取全局变量为空")) ;
			return 1 ;
		}

		if (!pDlg->m_projectData.m_mgGobalViarent.CheckViarentFormat(pGobalViarent->nViarentType,strSetValue))
		{
			lua_pushboolean(L,false) ;
			AfxMessageBox(_T("设置2DPos格式不对")) ;
			return 1 ;
		}

		pGobalViarent->strViarentValue = strSetValue ;
		pDlg->m_projectData.m_mgGobalViarent.GetViarentValue(pGobalViarent->nViarentType,strSetValue,pGobalViarent->aViarentValue) ;

		lua_pushboolean(L,true) ;
		return 1 ;
	}
	catch (...)
	{
		lua_pushboolean(L,false) ;
		return 1 ;
	}
}

int VisionGlobal::VpScript_Get2DPosGobalViarentByName(lua_State* L)
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		USES_CONVERSION ;

		CString strGobalViarentName(_T(""));

		ScriptCheckParamCount(L,1) ;
		strGobalViarentName = lua_tostring(L,1) ;

		int nCountGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentListSize() ;
		if (nCountGobalViarent <= 0)
		{
			lua_pushboolean(L,false) ;
			lua_pushstring(L,"") ;
			AfxMessageBox(_T("全局变量列表为空")) ;
			return 2 ;
		}

		CGOBALVIARENT *pGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentByName(strGobalViarentName) ;
		if (NULL == pGobalViarent)
		{
			lua_pushboolean(L,false) ;
			lua_pushstring(L,"") ;
			AfxMessageBox(_T("获取全局变量为空")) ;
			return 2 ;
		}

		CString strValue(_T("")) ;
		V2DPoint point2D = any_cast<V2DPoint>(pGobalViarent->aViarentValue);
		strValue.Format(_T("%.5f,%.5f"),point2D.dbX,point2D.dbY) ;

		lua_pushboolean(L,true) ;
		lua_pushstring(L,W2A(strValue)) ;
		return 2 ;
	}
	catch (...)
	{
		lua_pushboolean(L,false) ;
		lua_pushstring(L,"") ;
		return 2 ;
	}
}

int VisionGlobal::VpScript_Set2DPosGobalViarentByName(lua_State* L)
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		CString strGobalViarentName(_T(""));
		CString strSetValue(_T("")) ;

		ScriptCheckParamCount(L,2) ;
		strGobalViarentName = lua_tostring(L,1) ;
		strSetValue         = lua_tostring(L,2) ;

		int nCountGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentListSize() ;
		if (nCountGobalViarent <= 0)
		{
			lua_pushboolean(L,false) ;
			AfxMessageBox(_T("全局变量列表为空")) ;
			return 1 ;
		}

		CGOBALVIARENT *pGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentByName(strGobalViarentName) ;
		if (NULL == pGobalViarent)
		{
			lua_pushboolean(L,false) ;
			AfxMessageBox(_T("获取全局变量为空")) ;
			return 1 ;
		}

		if (!pDlg->m_projectData.m_mgGobalViarent.CheckViarentFormat(pGobalViarent->nViarentType,strSetValue))
		{
			lua_pushboolean(L,false) ;
			AfxMessageBox(_T("设置2DPos格式不对")) ;
			return 1 ;
		}

		pGobalViarent->strViarentValue = strSetValue ;
		pDlg->m_projectData.m_mgGobalViarent.GetViarentValue(pGobalViarent->nViarentType,strSetValue,pGobalViarent->aViarentValue) ;

		lua_pushboolean(L,true) ;
		return 1 ;
	}
	catch (...)
	{
		lua_pushboolean(L,false) ;
		return 1 ;
	}
}

int VisionGlobal::VpScript_Get3DPosGobalViarentById(lua_State* L)
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		USES_CONVERSION ;

		int nGobalViarentId = -1 ;

		ScriptCheckParamCount(L,1) ;
		nGobalViarentId = lua_tointeger(L,1) ;

		int nCountGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentListSize() ;
		if (nCountGobalViarent <= 0)
		{
			lua_pushboolean(L,false) ;
			lua_pushstring(L,"") ;
			AfxMessageBox(_T("全局变量列表为空")) ;
			return 2 ;
		}

		if (nGobalViarentId < 0 || nGobalViarentId >= nCountGobalViarent)
		{
			lua_pushboolean(L,false) ;
			lua_pushstring(L,"") ;
			AfxMessageBox(_T("全局变量Id越界")) ;
			return 2 ;
		}

		CGOBALVIARENT *pGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentById(nGobalViarentId) ;
		if (NULL == pGobalViarent)
		{
			lua_pushboolean(L,false) ;
			lua_pushstring(L,"") ;
			AfxMessageBox(_T("获取全局变量为空")) ;
			return 2 ;
		}

		CString strValue(_T("")) ;
		V3DPoint point3D = any_cast<V3DPoint>(pGobalViarent->aViarentValue);
		strValue.Format(_T("%.5f,%.5f,%.5f"),point3D.dbX,point3D.dbY,point3D.dbZ) ;

		lua_pushboolean(L,true) ;
		lua_pushstring(L,T2A(strValue)) ;
		return 2 ;
	}
	catch (...)
	{
		lua_pushboolean(L,false) ;
		lua_pushstring(L,"") ;
		return 2 ;
	}
}

int VisionGlobal::VpScript_Set3DPosGobalViarentById(lua_State* L)
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		int nGobalViarentId = -1 ;
		CString strSetValue(_T("")) ;

		ScriptCheckParamCount(L,2) ;
		nGobalViarentId = lua_tointeger(L,1) ;
		strSetValue     = lua_tostring(L,2) ;

		int nCountGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentListSize() ;
		if (nCountGobalViarent <= 0)
		{
			lua_pushboolean(L,false) ;
			AfxMessageBox(_T("全局变量列表为空")) ;
			return 1 ;
		}

		if (nGobalViarentId < 0 || nGobalViarentId >= nCountGobalViarent)
		{
			lua_pushboolean(L,false) ;
			AfxMessageBox(_T("全局变量Id越界")) ;
			return 1 ;
		}

		CGOBALVIARENT *pGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentById(nGobalViarentId) ;
		if (NULL == pGobalViarent)
		{
			lua_pushboolean(L,false) ;
			AfxMessageBox(_T("获取全局变量为空")) ;
			return 1 ;
		}

		if (!pDlg->m_projectData.m_mgGobalViarent.CheckViarentFormat(pGobalViarent->nViarentType,strSetValue))
		{
			lua_pushboolean(L,false) ;
			AfxMessageBox(_T("设置3DPos格式不对")) ;
			return 1 ;
		}

		pGobalViarent->strViarentValue = strSetValue ;
		pDlg->m_projectData.m_mgGobalViarent.GetViarentValue(pGobalViarent->nViarentType,strSetValue,pGobalViarent->aViarentValue) ;

		lua_pushboolean(L,true) ;
		return 1 ;
	}
	catch (...)
	{
		lua_pushboolean(L,false) ;
		return 1 ;
	}
}

int VisionGlobal::VpScript_Get3DPosGobalViarentByName(lua_State* L)
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		USES_CONVERSION ;

		CString strGobalViarentName(_T(""));

		ScriptCheckParamCount(L,1) ;
		strGobalViarentName = lua_tostring(L,1) ;

		int nCountGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentListSize() ;
		if (nCountGobalViarent <= 0)
		{
			lua_pushboolean(L,false) ;
			lua_pushstring(L,"") ;
			AfxMessageBox(_T("全局变量列表为空")) ;
			return 2 ;
		}

		CGOBALVIARENT *pGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentByName(strGobalViarentName) ;
		if (NULL == pGobalViarent)
		{
			lua_pushboolean(L,false) ;
			lua_pushstring(L,"") ;
			AfxMessageBox(_T("获取全局变量为空")) ;
			return 2 ;
		}

		CString strValue(_T("")) ;
		V3DPoint point3D = any_cast<V3DPoint>(pGobalViarent->aViarentValue);
		strValue.Format(_T("%.5f,%.5f,%.5f"),point3D.dbX,point3D.dbY,point3D.dbZ) ;

		lua_pushboolean(L,true) ;
		lua_pushstring(L,W2A(strValue)) ;
		return 2 ;
	}
	catch (...)
	{
		lua_pushboolean(L,false) ;
		lua_pushstring(L,"") ;
		return 2 ;
	}
}

int VisionGlobal::VpScript_Set3DPosGobalViarentByName(lua_State* L)
{
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		CString strGobalViarentName(_T(""));
		CString strSetValue(_T("")) ;

		ScriptCheckParamCount(L,2) ;
		strGobalViarentName = lua_tostring(L,1) ;
		strSetValue         = lua_tostring(L,2) ;

		int nCountGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentListSize() ;
		if (nCountGobalViarent <= 0)
		{
			lua_pushboolean(L,false) ;
			AfxMessageBox(_T("全局变量列表为空")) ;
			return 1 ;
		}

		CGOBALVIARENT *pGobalViarent = pDlg->m_projectData.m_mgGobalViarent.GetGobalViarentByName(strGobalViarentName) ;
		if (NULL == pGobalViarent)
		{
			lua_pushboolean(L,false) ;
			AfxMessageBox(_T("获取全局变量为空")) ;
			return 1 ;
		}

		if (!pDlg->m_projectData.m_mgGobalViarent.CheckViarentFormat(pGobalViarent->nViarentType,strSetValue))
		{
			lua_pushboolean(L,false) ;
			AfxMessageBox(_T("设置3DPos格式不对")) ;
			return 1 ;
		}

		pGobalViarent->strViarentValue = strSetValue ;
		pDlg->m_projectData.m_mgGobalViarent.GetViarentValue(pGobalViarent->nViarentType,strSetValue,pGobalViarent->aViarentValue) ;

		lua_pushboolean(L,true) ;
		return 1 ;
	}
	catch (...)
	{
		lua_pushboolean(L,false) ;
		return 1 ;
	}
}

#pragma endregion  GobalViarentInterface

#pragma region    Comm

int VisionGlobal::VpScript_ReadDataByCommId(lua_State* L)
{
	USES_CONVERSION ;
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		int nCommId = -1 ;
		double dbWaitTime = 0.0 ;
		DWORD dwWaitTime = 0 ;
		CString strReadData(_T("")) ;

		ScriptCheckParamCount(L,2) ;
		nCommId = lua_tointeger(L,1) ;
		dbWaitTime = lua_tonumber(L,2) ;
		dwWaitTime = dbWaitTime * 1000 ;

		int nCountComm = pDlg->m_projectData.m_mgCommunication.GetCommNodeListSize() ;
		if (nCountComm <= 0)
		{
			lua_pushboolean(L,false) ;
			lua_pushstring(L,"") ;
			AfxMessageBox(_T("通信列表为空")) ;
			return 2 ;
		}

		if (nCommId < 0 || nCommId >= nCountComm)
		{
			lua_pushboolean(L,false) ;
			lua_pushstring(L,"") ;
			AfxMessageBox(_T("通信Id越界")) ;
			return 2 ;
		}

		CCommunicationNode *pCommNode = pDlg->m_projectData.m_mgCommunication.GetCommNodeById(nCommId) ;
		if (NULL == pCommNode)
		{
			lua_pushboolean(L,false) ;
			lua_pushstring(L,"") ;
			AfxMessageBox(_T("没有查找对应的通信节点")) ;
			return 2 ;
		}

		string strRecData("") ;
		bool bRecieveRet = true ;
		DWORD dwStartTime, dwEndTime ;
		DWORD dwSpend = 0;
		dwStartTime = ::GetTickCount() ;
		while (1)
		{
			pCommNode->pCommunicationBase->Comm_RevData(strRecData) ;
			if (strRecData.length() > 0)
			{
				bRecieveRet = true ;
				break;
			}

			dwEndTime = GetTickCount() ;
			dwSpend = dwEndTime - dwStartTime ;
			if (dwSpend >= dwWaitTime)
			{
				bRecieveRet = false ;
				break ;
			}

			Sleep ( 10 );
			::DoEvent();
		}

		if (!bRecieveRet)
		{
			lua_pushboolean(L,false) ;
			lua_pushstring(L,"") ;
			return 2 ;
		}

		strReadData = strRecData.c_str() ;

		lua_pushboolean(L,true) ;
		lua_pushstring(L,W2A(strReadData)) ;
		return 2 ;
	}
	catch (...)
	{
		lua_pushboolean(L,false) ;
		lua_pushstring(L,"") ;
		return 2 ;
	}
}

int VisionGlobal::VpScript_SendDataByCommId(lua_State* L)
{
	USES_CONVERSION ;
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		int nCommId = -1 ;
		CString strSendData(_T("")) ;

		ScriptCheckParamCount(L,2) ;
		nCommId = lua_tointeger(L,1) ;
		strSendData = lua_tostring(L,2) ;

		int nCountComm = pDlg->m_projectData.m_mgCommunication.GetCommNodeListSize() ;
		if (nCountComm <= 0)
		{
			AfxMessageBox(_T("通信列表为空")) ;
			return 0 ;
		}

		if (nCommId < 0 || nCommId >= nCountComm)
		{
			AfxMessageBox(_T("通信Id越界")) ;
			return 0 ;
		}

		CCommunicationNode *pCommNode = pDlg->m_projectData.m_mgCommunication.GetCommNodeById(nCommId) ;
		if (NULL == pCommNode)
		{
			AfxMessageBox(_T("没有查找对应的通信节点")) ;
			return 0 ;
		}

		pCommNode->pCommunicationBase->Comm_SendData(W2A(strSendData)) ;

		return 0 ;
	}
	catch (...)
	{
		return 0 ;
	}
}
int VisionGlobal::VpScript_ReadDataByCommName(lua_State* L)
{
	USES_CONVERSION ;
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		CString strCommName(_T("")) ;
		double dbWaitTime = 0.0 ;
		DWORD dwWaitTime = 0 ;
		CString strReadData(_T("")) ;

		ScriptCheckParamCount(L,2) ;
		strCommName = lua_tostring(L,1) ;
		dbWaitTime = lua_tonumber(L,2) ;
		dwWaitTime = dbWaitTime * 1000 ;

		int nCountComm = pDlg->m_projectData.m_mgCommunication.GetCommNodeListSize() ;
		if (nCountComm <= 0)
		{
			lua_pushboolean(L,false) ;
			lua_pushstring(L,"") ;
			AfxMessageBox(_T("通信列表为空")) ;
			return 2 ;
		}

		CCommunicationNode *pCommNode = pDlg->m_projectData.m_mgCommunication.GetCommNodeByName(W2A(strCommName)) ;
		if (NULL == pCommNode)
		{
			lua_pushboolean(L,false) ;
			lua_pushstring(L,"") ;
			AfxMessageBox(_T("没有查找对应的通信节点")) ;
			return 2 ;
		}

		string strRecData("") ;
		bool bRecieveRet = true ;
		DWORD dwStartTime, dwEndTime ;
		DWORD dwSpend = 0;
		dwStartTime = ::GetTickCount() ;
		while (1)
		{
			pCommNode->pCommunicationBase->Comm_RevData(strRecData) ;
			if (strRecData.length() > 0)
			{
				bRecieveRet = true ;
				break;
			}

			dwEndTime = GetTickCount() ;
			dwSpend = dwEndTime - dwStartTime ;
			if (dwSpend >= dwWaitTime)
			{
				bRecieveRet = false ;
				break ;
			}

			Sleep ( 10 );
			::DoEvent();
		}

		if (!bRecieveRet)
		{
			lua_pushboolean(L,false) ;
			lua_pushstring(L,"") ;
			return 2 ;
		}

		strReadData = strRecData.c_str() ;

		lua_pushboolean(L,true) ;
		lua_pushstring(L,W2A(strReadData)) ;
		return 2 ;
	}
	catch (...)
	{
		lua_pushboolean(L,false) ;
		lua_pushstring(L,"") ;
		return 2 ;
	}
}

int VisionGlobal::VpScript_SendDataByCommName(lua_State* L)
{
	USES_CONVERSION ;
	CVisionProjectDlg *pDlg = (CVisionProjectDlg *)AfxGetMainWnd();
	try
	{
		CString strCommName(_T("")) ;
		CString strSendData(_T("")) ;

		ScriptCheckParamCount(L,2) ;
		strCommName = lua_tostring(L,1) ;
		strSendData = lua_tostring(L,2) ;

		int nCountComm = pDlg->m_projectData.m_mgCommunication.GetCommNodeListSize() ;
		if (nCountComm <= 0)
		{
			AfxMessageBox(_T("通信列表为空")) ;
			return 0 ;
		}

		CCommunicationNode *pCommNode = pDlg->m_projectData.m_mgCommunication.GetCommNodeByName(W2A(strCommName)) ;
		if (NULL == pCommNode)
		{
			AfxMessageBox(_T("没有查找对应的通信节点")) ;
			return 0 ;
		}

		pCommNode->pCommunicationBase->Comm_SendData(W2A(strSendData)) ;

		return 0 ;
	}
	catch (...)
	{
		return 0 ;
	}
}

#pragma endregion Comm