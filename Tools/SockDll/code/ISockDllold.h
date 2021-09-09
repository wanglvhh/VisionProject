// ISockDllold.h: interface for the ISockDllold class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ISOCKDLLOLD_H__F5BAFC41_18AD_11D7_9446_C0DD4DC15C51__INCLUDED_)
#define AFX_ISOCKDLLOLD_H__F5BAFC41_18AD_11D7_9446_C0DD4DC15C51__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "vMacro.h"
#include "vList.h"
////////////////////////////
struct LIST_NODE;
struct PARA;
////////////////////////////
typedef struct SOCK_PARA
{
	struct{
		WORD _hiPara;
		WORD _loPara;
	} _wpara,_lpara;
	SOCK_PARA(){::ZeroMemory((void*) this,sizeof(this));}
	void SetPara(const WPARAM wpara,const LPARAM lpara)
	{
		_wpara._hiPara=HIWORD(wpara);
		_wpara._loPara=LOWORD(wpara);
		_lpara._hiPara=HIWORD(lpara);
		_lpara._loPara=LOWORD(lpara);
	}
	void SetPara(const WORD hiWpara,const WORD loWpara,const WORD hiLpara,const WORD loLpara)
	{
		_wpara._hiPara=hiWpara;_wpara._loPara=loWpara;
		_lpara._hiPara=hiLpara;_lpara._loPara=loLpara;
	}
	WPARAM GetWpara()
	{
		WPARAM wpara=(WPARAM) (MAKELONG(_wpara._loPara,_wpara._hiPara));
		return wpara;
	}
	LPARAM GetLpara()
	{
		LPARAM lpara=(LPARAM) (MAKELONG(_lpara._loPara,_lpara._hiPara));
		return lpara;
	}
}SOCK_PARA;

class ISockDllold
{
public:
	BOOL GetSocketIP(int nMainSocketID,int nListenSocketID,DWORD& dwMainSocketIP,DWORD& dwListenSocketIP);
	ISockDllold();
	void Delete();
	LRESULT NotifyParent(SOCK_PARA& SockPara,BOOL bySend=TRUE);

	//////////////////
	BOOL InitSock(HWND hWnd, BOOL bServer, int& nMainSocketID, LPCTSTR lpsIP=NULL, UINT nPort=5000, BOOL bEnableMultiSameClients=FALSE);
	BOOL SendData(LPCTSTR lpsData,DWORD dwToSend,int nMainSocketID,DWORD* pdwSended=NULL,int nListenSocketID=0);
	BOOL ReadData(LPTSTR lpsData,DWORD dwBuffLen,int nMainSocketID,DWORD* pdwReaded=NULL,int nListenSocketID=0);
	BOOL CloseSock(int nMainSocketID=0,int nListenSocketID=0);

private:
	int CreateNewMainSocketID();
	BOOL SearchedNode(int nMainSocketID,void** ppret,DWORD& dwPos);
	/////////////
	~ISockDllold();
	vListPtr<LIST_NODE> m_listForSockets;
};
extern ISockDllold* g_pISockDllold;

#endif // !defined(AFX_ISOCKDLLOLD_H__F5BAFC41_18AD_11D7_9446_C0DD4DC15C51__INCLUDED_)
