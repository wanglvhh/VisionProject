#ifndef __MODULE_DEVELOP_HELPER_H__
#include "ModuleDevelopH.h"
//////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) DWORD __stdcall DllGetVerInfo(DLL_VER_INFO& dllVerInfo);
extern "C" __declspec(dllexport) DWORD __stdcall DllCreateInterface(long nInterfaceNo,void** ppInterface);
extern "C" __declspec(dllexport) DWORD __stdcall DllGetCmdInfo(long& nCmdIndex, DLL_CMD_INFO* pDllCmdInfo);
//////////////////////////////////////////////////////////////////////////
#endif
