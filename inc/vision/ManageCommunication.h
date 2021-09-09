#pragma once
#include <iostream>
#include <string.h>
using namespace std ;

#include <boost/any.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/make_shared.hpp>
using namespace boost;

#include "CommunicationBase.h"

struct COMM232NODE
{
public:
	string strPortName ;
	int    nBaudRate ;
	int    nParity ;
	int    nDataBits ;
	int    nStop ;

	COMM232NODE()
	{
		strPortName = "COM1" ;
		nBaudRate = 19200 ;
		nParity = 0 ;
		nDataBits = 8 ;
		nStop = 0 ;
	}

	~COMM232NODE()
	{
		strPortName = " " ;
		nBaudRate = 0 ;
		nParity = 0 ;
		nDataBits = 0 ;
		nStop = 0 ;
	}
};

struct COMMSOCKETNODE
{
public:
	int      nSocketType ;
	string   strIpAddress ;
	UINT     uIpPort ;

	COMMSOCKETNODE()
	{
		nSocketType = 0 ;
		strIpAddress = "127.0.0.1" ;
		uIpPort = 60000 ;
	}

	~COMMSOCKETNODE()
	{
		nSocketType = -1 ;
		strIpAddress = "" ;
		uIpPort = 0 ;
	}
};

class CCommunicationNode:public CObject
{
public:
	CCommunicationNode()
	{
		nCommId = -1 ;
		nCommType = -1 ;
		strCommName = "" ;
		pCommunicationBase = NULL ;
	}

	~CCommunicationNode()
	{
		nCommId = -1 ;
		nCommType = -1 ;
		strCommName = "" ;
		if (pCommunicationBase)
		{
			delete pCommunicationBase ;
			pCommunicationBase = NULL ;
		}
	}

public:
	int                         nCommId ;
	int                         nCommType ;
	any                         aCommValue ;
	string                      strCommName ;
	CMgrDllCommunicationBaseIm  mgrDllCommuncitionBaseIm ;
	CCommunicationBase*         pCommunicationBase ;
};

typedef CTypedPtrList<CObList, CCommunicationNode *> CommNodeList ;

class CManageCommunication
{
public:
	CManageCommunication()
	{
		commNodeList.RemoveAll() ;
	}

	~CManageCommunication()
	{
		commNodeList.RemoveAll() ;
	}

	int GetCommNodeListSize()
	{
		return (int)commNodeList.GetSize() ;
	}

	void AddTail(CCommunicationNode *pNewCommNode)
	{
		if (pNewCommNode)
		{
			commNodeList.AddTail(pNewCommNode) ;
		}
	}

	void RemoveAtById(int nCommId)
	{
		if (GetCommNodeListSize() <= 0)
		{
			return  ;
		}

		POSITION prev;
		POSITION pos = commNodeList.GetHeadPosition() ;
		while(pos)
		{
			prev = pos ;
			CCommunicationNode *pCommNode = commNodeList.GetNext(pos) ;
			if (nCommId == pCommNode->nCommId)
			{
				commNodeList.RemoveAt(prev) ;

				if (pCommNode)
				{
					if (pCommNode->pCommunicationBase)
					{
						delete pCommNode->pCommunicationBase ;
						pCommNode->pCommunicationBase = NULL ;
					}

					delete pCommNode ;
					pCommNode = NULL ;
				}

				break;
			}
		}
	}

	void ReSortId()
	{
		if (GetCommNodeListSize() <= 0)
		{
			return  ;
		}

		int i = 0 ;
		POSITION pos = commNodeList.GetHeadPosition() ;
		while(pos)
		{
			CCommunicationNode *pCommNode = commNodeList.GetNext(pos) ;
			pCommNode->nCommId = i++ ;
		}
	}

	void RemoveAll()
	{
		commNodeList.RemoveAll() ;
	}

	CCommunicationNode* GetCommNodeById(int nCommId)
	{
		if (GetCommNodeListSize() <= 0)
		{
			return NULL ;
		}

		POSITION pos = commNodeList.GetHeadPosition() ;
		while(pos)
		{
			CCommunicationNode *pCommNode = commNodeList.GetNext(pos) ;
			if (nCommId == pCommNode->nCommId)
			{
				return pCommNode ;
				//break;
			}
		}

		return NULL ;
	}

	CCommunicationNode* GetCommNodeByName(string strCommName)
	{
		if (GetCommNodeListSize() <= 0)
		{
			return NULL ;
		}

		POSITION pos = commNodeList.GetHeadPosition() ;
		while(pos)
		{
			CCommunicationNode *pCommNode = commNodeList.GetNext(pos) ;
			if (strCommName == pCommNode->strCommName)
			{
				return pCommNode ;
				//break;
			}
		}

		return NULL ;
	}

	bool CheckCommName(CString strNewName)
	{
		try
		{
			int nCountComm = GetCommNodeListSize() ;
			if (nCountComm <= 0) return true ;

			POSITION pos = commNodeList.GetHeadPosition() ;
			while(pos)
			{
				CCommunicationNode *pCommNode = commNodeList.GetNext(pos) ;
				if (strNewName == pCommNode->strCommName.c_str()) return false ;
			}
		}
		catch (...)
		{
			return false ;
		}
		return true ;
	}

	string GetCommInfo(CCommunicationNode *pCommNode)
	{
		USES_CONVERSION ;
		try
		{
			if (NULL == pCommNode) return "" ;

			CString strInfo(_T("")),strTmp(_T("")) ;
			if (0 == pCommNode->nCommType)
			{
				//串口通信
				COMM232NODE comm232Node = any_cast<COMM232NODE>(pCommNode->aCommValue) ;
				strInfo = comm232Node.strPortName.c_str() ;
				strTmp.Format(_T(",%d"),comm232Node.nBaudRate) ;
				strInfo += strTmp ;

				if (E_COMM_PARITYNONE == comm232Node.nParity)
				{
					strTmp = _T(",0") ;
				}
				else if (E_COMM_PARITYODD == comm232Node.nParity)
				{
					strTmp = _T(",1") ;
				}
				else if (E_COMM_PARITYEVEN == comm232Node.nParity)
				{
					strTmp = _T(",2") ;
				}
				else if (E_COMM_PARITYMARK == comm232Node.nParity)
				{
					strTmp = _T(",3") ;
				}
				else if (E_COMM_PARITYSPACE == comm232Node.nParity)
				{
					strTmp = _T(",4") ;
				}
				strInfo += strTmp ;

				if (E_COMM_DATABITS5 == comm232Node.nDataBits)
				{
					strTmp = _T(",5") ;
				}
				else if (E_COMM_DATABITS6 == comm232Node.nDataBits)
				{
					strTmp = _T(",6") ;
				}
				else if (E_COMM_DATABITS7 == comm232Node.nDataBits)
				{
					strTmp = _T(",7") ;
				}
				else if (E_COMM_DATABITS8 == comm232Node.nDataBits)
				{
					strTmp = _T(",8") ;
				}
				strInfo += strTmp ;

				if (E_COMM_STOPONE == comm232Node.nStop)
				{
					strTmp = _T(",0") ;
				}
				else if (E_COMM_STOPONEANDHALF == comm232Node.nStop)
				{
					strTmp = _T(",1") ;
				}
				else if (E_COMM_STOPTWO == comm232Node.nStop)
				{
					strTmp = _T(",2") ;
				}
				strInfo += strTmp ;

				return W2A(strInfo) ;
			}
			else if (1 == pCommNode->nCommType)
			{
				//网络通信
				COMMSOCKETNODE commSocketNode = any_cast<COMMSOCKETNODE>(pCommNode->aCommValue) ;
				strTmp.Format(_T(",%d,"),commSocketNode.uIpPort) ;
				strInfo = commSocketNode.strIpAddress.c_str() ;
				strInfo += strTmp ;

				if (0 == commSocketNode.nSocketType)
				{
					strTmp = _T("Serve") ;
				}
				else if (1 == commSocketNode.nSocketType)
				{
					strTmp = _T("Client") ;
				}
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
	CommNodeList commNodeList ;
};