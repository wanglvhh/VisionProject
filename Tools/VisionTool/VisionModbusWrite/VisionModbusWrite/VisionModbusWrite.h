// VisionModbusWrite.h : VisionModbusWrite DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CVisionModbusWriteApp
// �йش���ʵ�ֵ���Ϣ������� VisionModbusWrite.cpp
//

class CVisionModbusWriteApp : public CWinApp
{
public:
	CVisionModbusWriteApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
