// ModbusRtuMaster.h : ModbusRtuMaster DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CModbusRtuMasterApp
// �йش���ʵ�ֵ���Ϣ������� ModbusRtuMaster.cpp
//

class CModbusRtuMasterApp : public CWinApp
{
public:
	CModbusRtuMasterApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
