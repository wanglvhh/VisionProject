// VisionModbusRead.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "VisionModbusRead.h"

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

// CVisionModbusReadApp

BEGIN_MESSAGE_MAP(CVisionModbusReadApp, CWinApp)
END_MESSAGE_MAP()

// CVisionModbusReadApp ����

CVisionModbusReadApp::CVisionModbusReadApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CVisionModbusReadApp ����

CVisionModbusReadApp theApp;

// CVisionModbusReadApp ��ʼ��

BOOL CVisionModbusReadApp::InitInstance()
{
	CWinApp::InitInstance();

	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

	AfxInitRichEdit2();

	return TRUE;
}

int CVisionModbusReadApp::ExitInstance()
{
	// TODO: �ڴ����ר�ô����/����û���
	Gdiplus::GdiplusShutdown(m_gdiplusToken);

	return CWinApp::ExitInstance();
}