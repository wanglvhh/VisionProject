#include "stdafx.h"
#include "ModuleDevelopHelper.h"
#include "vMacro.h"
#include "ModbusRtuMasterInterface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) DWORD __stdcall DllGetVerInfo(DLL_VER_INFO& dllVerInfo)
{
	//外部调用者查询模块库支持的实际版本结构体内存字节大小
	if( 0==dllVerInfo._dwByteSize ){
		dllVerInfo._dwByteSize = sizeof(DLL_VER_INFO);
		return 0x00;
	}
	else if( dllVerInfo._dwByteSize<sizeof(DLL_VER_INFO) ){
		return vMAKE_RLT(FALSE, 0x00, 0x000008);
	}
	else{
		DLL_VER_INFO di;
		memset(&di, 0, sizeof(DLL_VER_INFO));
		////此处设置模块库支持的DLL_VER_INFO最新版本结构体字节大小
		di._dwByteSize = sizeof(DLL_VER_INFO);

		////此处设置模块库支持的DLL_VER_INFO的最新版本
		di._dwVerInfo = 1;//tagDLL_VER_INFO当前结构体版本

		////此处修订模块库版本信息
		di._dwVerMain = 3;//动态库当前主版本号
		di._dwVerSubMain = 0;//动态库当前次主版本号
		di._dwVerSubSub = 1;//动态库当前次次版本号

		////此处修订模块库支持的接口信息
		di._dwInterfaceNo = 1000;//动态库当前支持的最大接口号

		////此处添加模块库类型信息
		strcpy(di._szLibType, "{3F025B4F-936A-45d3-B4BF-BAE6ACA81FA5}");//该模块库类型

		////设置模块库UNICODE标志
#ifdef	_UNICODE
		di._cbFlagUnicode = 1;
#else
		di._cbFlagUnicode = 0;
#endif

		////此处修订模块库支持的字符串命令的个数
		di._cbCmdCount = 0;

		////此处附加信息的添加_cbExtraInfo
		//::_tcscpy((TCHAR*) di._cbExtraInfo, TEXT("附加信息"));

		////
		memcpy(&dllVerInfo, &di, sizeof(DLL_VER_INFO));
		return 0x00;
	}
}

extern "C" __declspec(dllexport) DWORD __stdcall DllCreateInterface(long nInterfaceNo,void** ppInterface)
{
	DLL_VER_INFO di;
	di._dwByteSize = sizeof(DLL_VER_INFO);
	::DllGetVerInfo(di);
	if( NULL==ppInterface ){
		return vMAKE_RLT(FALSE, 0, 0x000002);
	}
	*ppInterface = NULL;
	////
	if( nInterfaceNo>(long) di._dwInterfaceNo || nInterfaceNo<1 ){
		return vMAKE_RLT(FALSE, 0, 0x000003);
	}
	////
	switch( nInterfaceNo ){
	case (int)E_TOOL_MODBUS_RTUMASTER :
		{
			CModbusRtuMasterInterface * pVision = new CModbusRtuMasterInterface();
			*ppInterface = (void*) ((CModbusRtuMasterBase*) pVision);
		}
		break;
	}
	////
	return 0x00;
}

extern "C" __declspec(dllexport) DWORD __stdcall DllGetCmdInfo(long& nCmdIndex, DLL_CMD_INFO* pDllCmdInfo)
{
	////判断是否支持字符串命令
	BOOL bCmd = FALSE;
	////此处修订是否支持字符串命令标志
	//bCmd = TRUE;

	if( !bCmd ){//模块不支持字符串命令
		return vMAKE_RLT(FALSE, 0, 0x000009);
	}

	////
	long nCmdCount = 0;
	////此处添加支持字符串命令个数
	//nCmdCount = 1;

	////
	if( nCmdIndex<0 ){//客户查询模块支持的字符串命令的个数
		nCmdIndex = nCmdCount;
		return 0x00;
	}
	else{
		if( nCmdIndex>=nCmdCount ){
			return vMAKE_RLT(FALSE, 0, 0x000009);
		}
		else{
			////
			if( NULL==pDllCmdInfo ){
				return vMAKE_RLT(FALSE, 0, 0x000002);
			}
			////
			if( 0==pDllCmdInfo->_dwByteSize ){
				pDllCmdInfo->_dwByteSize = sizeof(DLL_CMD_INFO);
				return 0x00;
			}
			else if( pDllCmdInfo->_dwByteSize<sizeof(DLL_CMD_INFO) ){
				return vMAKE_RLT(FALSE, 0x00, 0x000008);
			}
			else{
				DLL_CMD_INFO ci;
				memset(&ci, 0, sizeof(DLL_VER_INFO));
				////此处设置模块库支持的DLL_CMD_INFO最新版本结构体字节大小
				ci._dwByteSize = sizeof(DLL_CMD_INFO);

				////此处设置模块库支持的DLL_CMD_INFO的最新版本
				ci._dwVerInfo = 1;//tagDLL_CMD_INFO当前结构体版本

				////此处修订具体的命令字符串内容
				//::strcpy(ci._szCmd, "C_G_SZ_FRESH_RES");

				////此处修订具体的字符串命令响应函数
				//ci._ptrFunc = (DWORD) funcOnFreshRes;

				////
				memcpy(pDllCmdInfo, &ci, sizeof(DLL_CMD_INFO));
				return 0x00;
			}
		}
	}
}
//////////////////////////////////////////////////////////////////////////