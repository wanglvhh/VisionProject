// ModbusTcpSlave.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "ModbusTcpSlave.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ������ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CModbusTcpSlaveApp

BEGIN_MESSAGE_MAP(CModbusTcpSlaveApp, CWinApp)
END_MESSAGE_MAP()


// CModbusTcpSlaveApp ����

CModbusTcpSlaveApp::CModbusTcpSlaveApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CModbusTcpSlaveApp ����

CModbusTcpSlaveApp theApp;


// CModbusTcpSlaveApp ��ʼ��

BOOL CModbusTcpSlaveApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
