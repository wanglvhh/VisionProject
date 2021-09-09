#pragma once
#include "Communication232base.h"
#include "CommunicationData.h"
#include "SerialPort.h"
#include "SerialPortInfo.h"
using namespace itas109;

class CCommunication232Interface :
	public CCommunication232Base, public has_slots<>
{
public:
	CCommunication232Interface(void);
	~CCommunication232Interface(void);

	virtual COMM_CODE Comm_Init(string strInitInfo);

	virtual COMM_CODE Comm_Close() ;

	virtual COMM_CODE Comm_ClearData() ;

	virtual COMM_CODE Comm_RevData(string &strRevData)  ;

	virtual COMM_CODE Comm_SendData(string strSendData)  ;
private:
	CRITICAL_SECTION          m_csComm232 ;
	string                    m_strData ;
	bool                      m_bSerialOpen ;
	CSerialPort               m_serialPort ;
};
