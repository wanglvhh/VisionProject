// ModbusDll.h : ModbusDll DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CModbusDllApp
// �йش���ʵ�ֵ���Ϣ������� ModbusDll.cpp
//

class CModbusDllApp : public CWinApp
{
public:
	CModbusDllApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
