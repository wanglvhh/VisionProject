// VisionDll.h : VisionDll DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

// CVisionDllApp
// �йش���ʵ�ֵ���Ϣ������� VisionDll.cpp
//

class CVisionDllApp : public CWinApp
{
public:
	CVisionDllApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
