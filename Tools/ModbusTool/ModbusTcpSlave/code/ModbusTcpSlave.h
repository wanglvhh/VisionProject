// ModbusTcpSlave.h : ModbusTcpSlave DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CModbusTcpSlaveApp
// �йش���ʵ�ֵ���Ϣ������� ModbusTcpSlave.cpp
//

class CModbusTcpSlaveApp : public CWinApp
{
public:
	CModbusTcpSlaveApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
