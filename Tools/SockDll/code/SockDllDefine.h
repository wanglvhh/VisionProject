#ifndef SOCKDLL_DEFINE
#define SOCKDLL_DEFINE

//���뵼������
#ifndef SOCKDLL_EXPORT
	#define SOCKDLL_API	extern "C" __declspec(dllimport)
#else
	#define SOCKDLL_API	extern "C" __declspec(dllexport)
#endif

/////////////////////////////////////////////////////////
//���롢������������

//����SOCKET
SOCKDLL_API BOOL __stdcall InitSockEx(HWND hWnd,BOOL bServer,int& nMainSocketID,LPCTSTR lpsIP=NULL,UINT nPort=5000,BOOL bEnableMultiSameClients=FALSE);

//��������
SOCKDLL_API BOOL __stdcall SendDataEx(LPCTSTR lpsData,DWORD dwToSend,int nMainSocketID,DWORD* pdwSended=NULL,int nListenSocketID=0);

//��������(�����ȡdwBuffLen-1���ַ�)
SOCKDLL_API BOOL __stdcall ReadDataEx(LPTSTR lpsData,DWORD dwBuffLen,int nMainSocketID,DWORD* pdwReaded=NULL,int nListenSocketID=0);

//�ر�SOCKET,if(nMainSocketID==0)��ر�������SOCKETS;
//else(��nListenSocketID==0,��ر�ָ����SOCKET;else��ر�ָ����SOCKET's_listenSocket)
SOCKDLL_API BOOL __stdcall CloseSockEx(int nMainSocketID=0,int nListenSocketID=0);

SOCKDLL_API BOOL __stdcall GetAssociatsSocketIP(int nMainSocketID,int nListenSocketID,DWORD* pdwMainSocketIP,DWORD* pdwListenSocketIP);
//////////////////////////////////////////////////////////

//������Ϣ����
#define WM_SOCKETS				(WM_USER+57)	

#define IDWM_SOCKET_ACCEPT			0		//һ���µĿͻ���������������
#define IDWM_SOCKET_RECEIVE			1		//��������Ϣ��Ҫ��ȡ
#define IDWM_SOCKET_CLOSE			2		//�ر�ָ����SOCKET ��ر���������
//��չ��
#define IDWM_SOCKET_SEND_COMPLETED	3		//����֧�ִ����������ݴ���

//���շ��͵Ļ�������С
#define SOCKET_BUFSIZE		0x4000

////////////////////////////////
//��������Ӧ��Ϣ	WM_SOCKETS
/*
	//LOWORD(LPARAM)==nID(��������ListenSocket's_ID), HIWORD(LPARAM)--Ԥ����չ
	//LOWORD(WPARAM)==�����¼���Ϣ, HIWORD(WPARAM)==nID(��SOCKET's_ID)
	switch( LOWORD(wParam) )
	{
	case IDWM_SOCKET_ACCEPT:
		����Ϣ�Է�������Ч������֪ͨһ���µĿͻ�����

	case IDWM_SOCKET_RECEIVE:
		����Ϣ��Ҫ��ȡ������ReadData();

	case IDWM_SOCKET_CLOSE:
		SOCKET�ر�
	case IDWM_SOCKET_SEND_COMPLETED:
		֪ͨǰһ��SendData()�������������Ѵ������
	}
*/
///////////////////////
///////////////////////
#endif
