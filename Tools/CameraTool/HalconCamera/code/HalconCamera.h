// HalconCamera.h : HalconCamera DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

// CHalconCameraApp
// �йش���ʵ�ֵ���Ϣ������� HalconCamera.cpp
//

class CHalconCameraApp : public CWinApp
{
public:
	CHalconCameraApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
