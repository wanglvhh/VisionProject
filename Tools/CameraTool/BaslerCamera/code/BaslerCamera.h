// BaslerCamera.h : BaslerCamera DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

// CBaslerCameraApp
// �йش���ʵ�ֵ���Ϣ������� BaslerCamera.cpp
//

class CBaslerCameraApp : public CWinApp
{
public:
	CBaslerCameraApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
