// Communication232.h : Communication232 DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCommunication232App
// �йش���ʵ�ֵ���Ϣ������� Communication232.cpp
//

class CCommunication232App : public CWinApp
{
public:
	CCommunication232App();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
