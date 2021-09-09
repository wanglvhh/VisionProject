#pragma once
#include "ModuleDevelopH.h"
#include "CommunicationData.h"

class CMgrDllCommunicationRtuMasterBaseIm : public CMgrDllDelegate
{
public:
#ifdef _DEBUG
	CMgrDllCommunicationRtuMasterBaseIm(LPCTSTR lpcszDllPathFullName=_T("CommunicationRtuMasterD.dll"))
		: CMgrDllDelegate(lpcszDllPathFullName)
	{
	}
#else
	CMgrDllCommunicationRtuMasterBaseIm(LPCTSTR lpcszDllPathFullName=_T("CommunicationRtuMaster.dll"))
		: CMgrDllDelegate(lpcszDllPathFullName)
	{
	}
#endif
	virtual ~CMgrDllCommunicationRtuMasterBaseIm(){
	}
};

class CCommunicationRtuMasterBase
{
public:
	virtual COMM_CODE Comm_Init(string strInitInfo) = 0 ;

	virtual COMM_CODE Comm_Close() = 0 ;

	virtual COMM_CODE Comm_ClearData() = 0 ;

	virtual COMM_CODE Comm_RevData(string &strRevData) = 0 ;

	virtual COMM_CODE Comm_SendData(string strSendData) = 0 ;
};