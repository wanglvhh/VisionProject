#pragma once
#include <iostream>
#include <string.h>
using namespace std ;

#include <boost/any.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/make_shared.hpp>
using namespace boost;

#include "ModbusBase.h"

struct RTUMASTERNODE
{
public:
	int    nSlaveID ;
	string strPortName ;
	int    nBaudRate ;
	int    nParity ;
	int    nDataBits ;
	int    nStop ;

	RTUMASTERNODE()
	{
		nSlaveID = 1 ;
		strPortName = "COM1" ;
		nBaudRate = 19200 ;
		nParity = 0 ;
		nDataBits = 8 ;
		nStop = 0 ;
	}

	~RTUMASTERNODE()
	{
		nSlaveID = -1 ;
		strPortName = " " ;
		nBaudRate = 0 ;
		nParity = 0 ;
		nDataBits = 0 ;
		nStop = 0 ;
	}
};

struct RTUSLAVENODE
{
public:
	int    nSlaveID ;
	string strPortName ;
	int    nBaudRate ;
	int    nParity ;
	int    nDataBits ;
	int    nStop ;

	RTUSLAVENODE()
	{
		nSlaveID = 1 ;
		strPortName = "COM2" ;
		nBaudRate = 19200 ;
		nParity = 0 ;
		nDataBits = 8 ;
		nStop = 0 ;
	}

	~RTUSLAVENODE()
	{
		nSlaveID = -1 ;
		strPortName = " " ;
		nBaudRate = 0 ;
		nParity = 0 ;
		nDataBits = 0 ;
		nStop = 0 ;
	}
};

struct TCPMASTERNODE
{
public:
	int    nSlaveID ;
	string   strIpAddress ;
	UINT     uIpPort ;

	TCPMASTERNODE()
	{
		nSlaveID = 1 ;
		strIpAddress = "127.0.0.1" ;
		uIpPort = 60000 ;
	}

	~TCPMASTERNODE()
	{
		nSlaveID = -1 ;
		strIpAddress = "" ;
		uIpPort = 0 ;
	}
};

struct TCPSLAVENODE
{
public:
	int    nSlaveID ;
	string   strIpAddress ;
	UINT     uIpPort ;

	TCPSLAVENODE()
	{
		nSlaveID = 1 ;
		strIpAddress = "127.0.0.1" ;
		uIpPort = 60000 ;
	}

	~TCPSLAVENODE()
	{
		nSlaveID = -1 ;
		strIpAddress = "" ;
		uIpPort = 0 ;
	}
};

class CModbusNode:public CObject
{
public:
	CModbusNode()
	{
		nModbusID = -1 ;
		nModbusType = 0 ;
		strModbusName = "" ;
		pModbusBase = NULL ;
	}

	~CModbusNode()
	{
		nModbusID = -1 ;
		nModbusType = -1 ;
		strModbusName = "" ;
		if (pModbusBase)
		{
			delete pModbusBase ;
			pModbusBase = NULL ;
		}
	}

public:
	int                      nModbusID ;
	int                      nModbusType ;
	any                      aModbusValue ;
	string                   strModbusName ;
	CMgrDllModbusBaseDllIm   mgrDllModbusBaseDllIm ;
	CModbusBase*             pModbusBase ;
};

typedef CTypedPtrList<CObList, CModbusNode *> ModbusNodeList ;

class CManageModbus
{
public:
	CManageModbus()
	{
		modbusNodeList.RemoveAll() ;
	}

	~CManageModbus()
	{
		modbusNodeList.RemoveAll() ;
	}

	int GetModbusNodeListSize()
	{
		return (int)modbusNodeList.GetSize() ;
	}

	void AddTail(CModbusNode *pNewModbusNode)
	{
		if (pNewModbusNode)
		{
			modbusNodeList.AddTail(pNewModbusNode) ;
		}
	}

	void RemoveAtById(int nModbusID)
	{
		if (GetModbusNodeListSize() <= 0)
		{
			return  ;
		}

		POSITION prev;
		POSITION pos = modbusNodeList.GetHeadPosition() ;
		while(pos)
		{
			prev = pos ;
			CModbusNode *pModbusNode = modbusNodeList.GetNext(pos) ;
			if (nModbusID == pModbusNode->nModbusID)
			{
				modbusNodeList.RemoveAt(prev) ;

				if (pModbusNode)
				{
					if (pModbusNode->pModbusBase)
					{
						delete pModbusNode->pModbusBase ;
						pModbusNode->pModbusBase = NULL ;
					}

					delete pModbusNode ;
					pModbusNode = NULL ;
				}

				break;
			}
		}
	}

	void ReSortId()
	{
		if (GetModbusNodeListSize() <= 0)
		{
			return  ;
		}

		int i = 0 ;
		POSITION pos = modbusNodeList.GetHeadPosition() ;
		while(pos)
		{
			CModbusNode *pModbusNode = modbusNodeList.GetNext(pos) ;
			pModbusNode->nModbusID = i++ ;
		}
	}

	void RemoveAll()
	{
		modbusNodeList.RemoveAll() ;
	}

	CModbusNode* GetModbusNodeById(int nModbusID)
	{
		if (GetModbusNodeListSize() <= 0)
		{
			return NULL ;
		}

		POSITION pos = modbusNodeList.GetHeadPosition() ;
		while(pos)
		{
			CModbusNode *pModbusNode = modbusNodeList.GetNext(pos) ;
			if (nModbusID == pModbusNode->nModbusID)
			{
				return pModbusNode ;
				//break;
			}
		}

		return NULL ;
	}

	CModbusNode* GetModbusNodeByName(string strModbusName)
	{
		if (GetModbusNodeListSize() <= 0)
		{
			return NULL ;
		}

		POSITION pos = modbusNodeList.GetHeadPosition() ;
		while(pos)
		{
			CModbusNode *pModbusNode = modbusNodeList.GetNext(pos) ;
			if (strModbusName == pModbusNode->strModbusName)
			{
				return pModbusNode ;
				//break;
			}
		}

		return NULL ;
	}

	bool CheckModbusName(CString strNewName)
	{
		try
		{
			int nCountComm = GetModbusNodeListSize() ;
			if (nCountComm <= 0) return true ;

			POSITION pos = modbusNodeList.GetHeadPosition() ;
			while(pos)
			{
				CModbusNode *pModbusNode = modbusNodeList.GetNext(pos) ;
				if (strNewName == pModbusNode->strModbusName.c_str()) return false ;
			}
		}
		catch (...)
		{
			return false ;
		}
		return true ;
	}

	string GetModbusInfo(CModbusNode *pModbusNode)
	{
		USES_CONVERSION ;
		try
		{
			if (NULL == pModbusNode) return "" ;

			CString strInfo(_T("")),strTmp(_T("")) ;
			if (0 == pModbusNode->nModbusType)
			{
				//RtuMaster
				RTUMASTERNODE rtuMasterNode = any_cast<RTUMASTERNODE>(pModbusNode->aModbusValue) ;
				strInfo = rtuMasterNode.strPortName.c_str() ;
				strTmp.Format(_T(",%d"),rtuMasterNode.nBaudRate) ;
				strInfo += strTmp ;

				if (E_COMM_PARITYNONE == rtuMasterNode.nParity)
				{
					strTmp = _T(",0") ;
				}
				else if (E_COMM_PARITYODD == rtuMasterNode.nParity)
				{
					strTmp = _T(",1") ;
				}
				else if (E_COMM_PARITYEVEN == rtuMasterNode.nParity)
				{
					strTmp = _T(",2") ;
				}
				strInfo += strTmp ;

				if (E_COMM_DATABITS5 == rtuMasterNode.nDataBits)
				{
					strTmp = _T(",5") ;
				}
				else if (E_COMM_DATABITS6 == rtuMasterNode.nDataBits)
				{
					strTmp = _T(",6") ;
				}
				else if (E_COMM_DATABITS7 == rtuMasterNode.nDataBits)
				{
					strTmp = _T(",7") ;
				}
				else if (E_COMM_DATABITS8 == rtuMasterNode.nDataBits)
				{
					strTmp = _T(",8") ;
				}
				strInfo += strTmp ;

				if (E_COMM_STOPONE == rtuMasterNode.nStop)
				{
					strTmp = _T(",0") ;
				}
				else if (E_COMM_STOPTWO == rtuMasterNode.nStop)
				{
					strTmp = _T(",1") ;
				}
				strInfo += strTmp ;

				strTmp.Format(_T(",%d"),rtuMasterNode.nSlaveID) ;
				strInfo += strTmp ;

				return W2A(strInfo) ;
			}
			else if (1 == pModbusNode->nModbusType)
			{
				//RtuSlave
				RTUSLAVENODE rtuSlaveNode = any_cast<RTUSLAVENODE>(pModbusNode->aModbusValue) ;
				strInfo = rtuSlaveNode.strPortName.c_str() ;
				strTmp.Format(_T(",%d"),rtuSlaveNode.nBaudRate) ;
				strInfo += strTmp ;

				if (E_COMM_PARITYNONE == rtuSlaveNode.nParity)
				{
					strTmp = _T(",0") ;
				}
				else if (E_COMM_PARITYODD == rtuSlaveNode.nParity)
				{
					strTmp = _T(",1") ;
				}
				else if (E_COMM_PARITYEVEN == rtuSlaveNode.nParity)
				{
					strTmp = _T(",2") ;
				}
				strInfo += strTmp ;

				if (E_COMM_DATABITS5 == rtuSlaveNode.nDataBits)
				{
					strTmp = _T(",5") ;
				}
				else if (E_COMM_DATABITS6 == rtuSlaveNode.nDataBits)
				{
					strTmp = _T(",6") ;
				}
				else if (E_COMM_DATABITS7 == rtuSlaveNode.nDataBits)
				{
					strTmp = _T(",7") ;
				}
				else if (E_COMM_DATABITS8 == rtuSlaveNode.nDataBits)
				{
					strTmp = _T(",8") ;
				}
				strInfo += strTmp ;

				if (E_COMM_STOPONE == rtuSlaveNode.nStop)
				{
					strTmp = _T(",0") ;
				}
				else if (E_COMM_STOPTWO == rtuSlaveNode.nStop)
				{
					strTmp = _T(",1") ;
				}
				strInfo += strTmp ;

				strTmp.Format(_T(",%d"),rtuSlaveNode.nSlaveID) ;
				strInfo += strTmp ;

				return W2A(strInfo) ;
			}
			else if (2 == pModbusNode->nModbusType)
			{
				//TcpMaster
				TCPMASTERNODE tcpMasterNode = any_cast<TCPMASTERNODE>(pModbusNode->aModbusValue) ;
				strTmp.Format(_T(",%d"),tcpMasterNode.uIpPort) ;
				strInfo = tcpMasterNode.strIpAddress.c_str() ;
				strInfo += strTmp ;

				strTmp.Format(_T(",%d"),tcpMasterNode.nSlaveID) ;
				strInfo += strTmp ;

				return W2A(strInfo) ;
			}
			else if (3 == pModbusNode->nModbusType)
			{
				//TcpSlave
				TCPSLAVENODE tcpSlaveNode = any_cast<TCPSLAVENODE>(pModbusNode->aModbusValue) ;
				strTmp.Format(_T(",%d"),tcpSlaveNode.uIpPort) ;
				strInfo = tcpSlaveNode.strIpAddress.c_str() ;
				strInfo += strTmp ;

				strTmp.Format(_T(",%d"),tcpSlaveNode.nSlaveID) ;
				strInfo += strTmp ;

				return W2A(strInfo) ;
			}
		}
		catch (...)
		{
			return "" ;
		}

		return "" ;
	}

public:
	ModbusNodeList modbusNodeList ;
};