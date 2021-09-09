#pragma once
#include "Communicationbase.h"
#include "CommunicationSocketBase.h"
#include "vCriticalSection.h"

class CCommunicationSocketInterface :
	public CCommunicationBase
{
public:
	CCommunicationSocketInterface(void);
	~CCommunicationSocketInterface(void);

	virtual COMM_CODE Comm_Init(string strInitInfo)  ;

	virtual COMM_CODE Comm_Release() ;

	virtual COMM_CODE Comm_Close()  ;

	virtual COMM_CODE Comm_ClearData()  ;

	virtual COMM_CODE Comm_RevData(string &strRevData)  ;

	virtual COMM_CODE Comm_SendData(string strSendData)  ;

private:
	CCommunicationSocketBase*           m_pCommSocketBase ;
	CMgrDllCommunicationSocketIm        m_dllCommSocketIm ;
	bool                                m_bInitOk ;
	CRITICAL_SECTION                    m_Critical ;
};
