#pragma once
#include <iostream>
#include <string.h>
using namespace std ;

#include <boost/any.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/make_shared.hpp>
using namespace boost;

//#include "AddComm232Dlg.h"
//
//#include "AddCommTcpDlg.h"

//#include "Communicationallbase.h"

//
//
//class CCommunicationNode:public CObject
//{
//public:
//	CCommunicationNode()
//	{
//		nCommId = -1 ;
//		nCommType = -1 ;
//		strCommName = "" ;
//		pCommAllBase = NULL ;
//	}
//
//	~CCommunicationNode()
//	{
//		nCommId = -1 ;
//		nCommType = -1 ;
//		strCommName = "" ;
//		if (pCommAllBase)
//		{
//			delete pCommAllBase ;
//			pCommAllBase = NULL ;
//		}
//	}
//
//public:
//	int      nCommId ;
//	int      nCommType ;
//	any      aCommValue ;
//	string   strCommName ;
//	CCommunicationAllBase*     pCommAllBase ;
//	CMgrDllCommunicationBaseIm mgrDllCommBase ;
//};
//
//typedef CTypedPtrList<CObList, CCommunicationNode *> CommNodeList ;
//
//class CManageCommunication
//{
//public:
//	CManageCommunication()
//	{
//	}
//
//	~CManageCommunication()
//	{
//	}
//
//	int GetCommNodeListSize()
//	{
//		return (int)commNodeList.GetSize() ;
//	}
//
//	void AddTail(CCommunicationNode *pNewCommNode)
//	{
//		if (pNewCommNode)
//		{
//			commNodeList.AddTail(pNewCommNode) ;
//		}
//	}
//
//	void RemoveAtById(int nCommId)
//	{
//		if (GetCommNodeListSize() <= 0)
//		{
//			return  ;
//		}
//
//		POSITION prev;
//		POSITION pos = commNodeList.GetHeadPosition() ;
//		while(pos)
//		{
//			prev = pos ;
//			CCommunicationNode *pCommNode = commNodeList.GetNext(pos) ;
//			if (nCommId == pCommNode->nCommId)
//			{
//				commNodeList.RemoveAt(prev) ;
//
//				if (pCommNode)
//				{
//					delete pCommNode ;
//					pCommNode = NULL ;
//				}
//
//				break;
//			}
//		}
//	}
//
//	void RemoveAll()
//	{
//		commNodeList.RemoveAll() ;
//	}
//
//	CCommunicationNode* GetCommNodeById(int nCommId)
//	{
//		if (GetCommNodeListSize() <= 0)
//		{
//			return NULL ;
//		}
//
//		POSITION pos = commNodeList.GetHeadPosition() ;
//		while(pos)
//		{
//			CCommunicationNode *pCommNode = commNodeList.GetNext(pos) ;
//			if (nCommId == pCommNode->nCommId)
//			{
//				return pCommNode ;
//				//break;
//			}
//		}
//
//		return NULL ;
//	}
//
//	CCommunicationNode* GetCommNodeBySn(string strCommName)
//	{
//		if (GetCommNodeListSize() <= 0)
//		{
//			return NULL ;
//		}
//
//		POSITION pos = commNodeList.GetHeadPosition() ;
//		while(pos)
//		{
//			CCommunicationNode *pCommNode = commNodeList.GetNext(pos) ;
//			if (strCommName == pCommNode->strCommName)
//			{
//				return pCommNode ;
//				//break;
//			}
//		}
//
//		return NULL ;
//	}
//
//	bool CheckCommName(CString strNewName)
//	{
//		try
//		{
//			int nCountComm = GetCommNodeListSize() ;
//			if (nCountComm <= 0) return true ;
//
//			POSITION pos = commNodeList.GetHeadPosition() ;
//			while(pos)
//			{
//				CCommunicationNode *pCommNode = commNodeList.GetNext(pos) ;
//				if (strNewName == pCommNode->strCommName.c_str()) return false ;
//			}
//		}
//		catch (...)
//		{
//			return false ;
//		}
//		return true ;
//	}
//
//public:
//	CommNodeList commNodeList ;
//};