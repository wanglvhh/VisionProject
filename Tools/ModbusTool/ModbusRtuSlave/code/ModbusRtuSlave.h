// ModbusRtuSlave.h : ModbusRtuSlave DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CModbusRtuSlaveApp
// �йش���ʵ�ֵ���Ϣ������� ModbusRtuSlave.cpp
//

class CModbusRtuSlaveApp : public CWinApp
{
public:
	CModbusRtuSlaveApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
