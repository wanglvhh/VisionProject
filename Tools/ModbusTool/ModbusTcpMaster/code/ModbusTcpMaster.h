// ModbusTcpMaster.h : ModbusTcpMaster DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CModbusTcpMasterApp
// �йش���ʵ�ֵ���Ϣ������� ModbusTcpMaster.cpp
//

class CModbusTcpMasterApp : public CWinApp
{
public:
	CModbusTcpMasterApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
