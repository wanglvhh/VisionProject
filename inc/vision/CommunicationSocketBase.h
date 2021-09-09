#pragma once
#include "ModuleDevelopH.h"
#include "CommunicationData.h"

class CMgrDllCommunicationSocketIm : public CMgrDllDelegate
{
public:
#ifdef _DEBUG
	CMgrDllCommunicationSocketIm(LPCTSTR lpcszDllPathFullName=_T("CommunicationSocketD.dll"))
		: CMgrDllDelegate(lpcszDllPathFullName)
	{
	}
#else
	CMgrDllCommunicationSocketIm(LPCTSTR lpcszDllPathFullName=_T("CommunicationSocket.dll"))
		: CMgrDllDelegate(lpcszDllPathFullName)
	{
	}
#endif
	virtual ~CMgrDllCommunicationSocketIm(){
	}
};

class CCommunicationSocketBase
{
public:
	virtual COMM_CODE Comm_Init(string strInitInfo) = 0 ;

	virtual COMM_CODE Comm_Close() = 0 ;

	virtual COMM_CODE Comm_ClearData() = 0 ;

	virtual COMM_CODE Comm_RevData(string &strRevData) = 0 ;

	virtual COMM_CODE Comm_SendData(string strSendData) = 0 ;
};