// VisionModbusRead.h : VisionModbusRead DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

// CVisionModbusReadApp
// �йش���ʵ�ֵ���Ϣ������� VisionModbusRead.cpp
//

class CVisionModbusReadApp : public CWinApp
{
public:
	ULONG_PTR m_gdiplusToken;
public:
	CVisionModbusReadApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};
