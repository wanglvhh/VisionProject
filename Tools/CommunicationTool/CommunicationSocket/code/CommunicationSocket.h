// CommunicationSocket.h : CommunicationSocket DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCommunicationSocketApp
// �йش���ʵ�ֵ���Ϣ������� CommunicationSocket.cpp
//

class CCommunicationSocketApp : public CWinApp
{
public:
	CCommunicationSocketApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
