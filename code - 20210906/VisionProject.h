// VisionProject.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

// CVisionProjectApp:
// �йش����ʵ�֣������ VisionProject.cpp
//

class CVisionProjectApp : public CWinApp
{
public:
public:
	CVisionProjectApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CVisionProjectApp theApp;