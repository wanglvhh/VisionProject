// CommunicationDll.h : CommunicationDll DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCommunicationDllApp
// �йش���ʵ�ֵ���Ϣ������� CommunicationDll.cpp
//

class CCommunicationDllApp : public CWinApp
{
public:
	CCommunicationDllApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
