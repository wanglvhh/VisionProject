// Vision2DCamera.h : Vision2DCamera DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

// CVision2DCameraApp
// �йش���ʵ�ֵ���Ϣ������� Vision2DCamera.cpp
//

class CVision2DCameraApp : public CWinApp
{
public:
	ULONG_PTR m_gdiplusToken;
public:
	CVision2DCameraApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};
