#pragma once
#include "Communicationbase.h"
#include "Communication232Base.h"
#include "vCriticalSection.h"

class CCommunication232Interface :
	public CCommunicationBase
{
public:
	CCommunication232Interface(void);
	~CCommunication232Interface(void);

	virtual COMM_CODE Comm_Init(string strInitInfo)  ;

	virtual COMM_CODE Comm_Release() ;

	virtual COMM_CODE Comm_Close()  ;

	virtual COMM_CODE Comm_ClearData()  ;

	virtual COMM_CODE Comm_RevData(string &strRevData)  ;

	virtual COMM_CODE Comm_SendData(string strSendData)  ;

private:
	CCommunication232Base*           m_pComm232Base ;
	CMgrDllCommunication232Im        m_dllComm232Im ;
	bool                             m_bInitOk ;
	CRITICAL_SECTION                 m_Critical ;
};
