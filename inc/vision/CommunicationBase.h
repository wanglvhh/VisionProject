#pragma once
#include "ModuleDevelopH.h"
#include "CommunicationData.h"

class CMgrDllCommunicationBaseIm : public CMgrDllDelegate
{
public:
#ifdef _DEBUG
	CMgrDllCommunicationBaseIm(LPCTSTR lpcszDllPathFullName=_T("CommunicationDllD.dll"))
		: CMgrDllDelegate(lpcszDllPathFullName)
	{
	}
#else
	CMgrDllCommunicationBaseIm(LPCTSTR lpcszDllPathFullName=_T("CommunicationDll.dll"))
		: CMgrDllDelegate(lpcszDllPathFullName)
	{
	}
#endif
	virtual ~CMgrDllCommunicationBaseIm(){
	}
};

class CCommunicationBase
{
public:
	virtual COMM_CODE Comm_Init(string strInitInfo) = 0 ;

	virtual COMM_CODE Comm_Release() = 0 ;

	virtual COMM_CODE Comm_Close() = 0 ;

	virtual COMM_CODE Comm_ClearData() = 0 ;

	virtual COMM_CODE Comm_RevData(string &strRevData) = 0 ;

	virtual COMM_CODE Comm_SendData(string strSendData) = 0 ;
};