#pragma once
#include "ModuleDevelopH.h"
#include "CommunicationData.h"

class CMgrDllCommunication232Im : public CMgrDllDelegate
{
public:
#ifdef _DEBUG
	CMgrDllCommunication232Im(LPCTSTR lpcszDllPathFullName=_T("Communication232D.dll"))
		: CMgrDllDelegate(lpcszDllPathFullName)
	{
	}
#else
	CMgrDllCommunication232Im(LPCTSTR lpcszDllPathFullName=_T("Communication232.dll"))
		: CMgrDllDelegate(lpcszDllPathFullName)
	{
	}
#endif
	virtual ~CMgrDllCommunication232Im(){
	}
};

class CCommunication232Base
{
public:
	virtual COMM_CODE Comm_Init(string strInitInfo) = 0 ;

	virtual COMM_CODE Comm_Close() = 0 ;

	virtual COMM_CODE Comm_ClearData() = 0 ;

	virtual COMM_CODE Comm_RevData(string &strRevData) = 0 ;

	virtual COMM_CODE Comm_SendData(string strSendData) = 0 ;
};