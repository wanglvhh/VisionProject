#ifndef SOCKDLL_DEFINE
#define SOCKDLL_DEFINE

//导入导出定义
#ifndef SOCKDLL_EXPORT
	#define SOCKDLL_API	extern "C" __declspec(dllimport)
#else
	#define SOCKDLL_API	extern "C" __declspec(dllexport)
#endif

/////////////////////////////////////////////////////////
//导入、导出函数定义

//创建SOCKET
SOCKDLL_API BOOL __stdcall InitSockEx(HWND hWnd,BOOL bServer,int& nMainSocketID,LPCTSTR lpsIP=NULL,UINT nPort=5000,BOOL bEnableMultiSameClients=FALSE);

//发送数据
SOCKDLL_API BOOL __stdcall SendDataEx(LPCTSTR lpsData,DWORD dwToSend,int nMainSocketID,DWORD* pdwSended=NULL,int nListenSocketID=0);

//接收数据(最多收取dwBuffLen-1个字符)
SOCKDLL_API BOOL __stdcall ReadDataEx(LPTSTR lpsData,DWORD dwBuffLen,int nMainSocketID,DWORD* pdwReaded=NULL,int nListenSocketID=0);

//关闭SOCKET,if(nMainSocketID==0)则关闭所有主SOCKETS;
//else(若nListenSocketID==0,则关闭指定主SOCKET;else则关闭指定主SOCKET's_listenSocket)
SOCKDLL_API BOOL __stdcall CloseSockEx(int nMainSocketID=0,int nListenSocketID=0);

SOCKDLL_API BOOL __stdcall GetAssociatsSocketIP(int nMainSocketID,int nListenSocketID,DWORD* pdwMainSocketIP,DWORD* pdwListenSocketIP);
//////////////////////////////////////////////////////////

//各种消息定义
#define WM_SOCKETS				(WM_USER+57)	

#define IDWM_SOCKET_ACCEPT			0		//一个新的客户机连到服务器端
#define IDWM_SOCKET_RECEIVE			1		//有网络信息需要读取
#define IDWM_SOCKET_CLOSE			2		//关闭指定的SOCKET 或关闭网络连接
//扩展版
#define IDWM_SOCKET_SEND_COMPLETED	3		//用于支持大容量的数据传送

//接收发送的缓冲区大小
#define SOCKET_BUFSIZE		0x4000

////////////////////////////////
//调用者响应消息	WM_SOCKETS
/*
	//LOWORD(LPARAM)==nID(服务器版ListenSocket's_ID), HIWORD(LPARAM)--预留扩展
	//LOWORD(WPARAM)==网络事件消息, HIWORD(WPARAM)==nID(主SOCKET's_ID)
	switch( LOWORD(wParam) )
	{
	case IDWM_SOCKET_ACCEPT:
		此消息对服务器有效，用于通知一个新的客户加入

	case IDWM_SOCKET_RECEIVE:
		有信息需要读取，调用ReadData();

	case IDWM_SOCKET_CLOSE:
		SOCKET关闭
	case IDWM_SOCKET_SEND_COMPLETED:
		通知前一次SendData()函数调用数据已传送完成
	}
*/
///////////////////////
///////////////////////
#endif
