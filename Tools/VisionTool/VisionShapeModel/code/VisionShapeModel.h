// VisionShapeModel.h : VisionShapeModel DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

// CVisionShapeModelApp
// �йش���ʵ�ֵ���Ϣ������� VisionShapeModel.cpp
//

class CVisionShapeModelApp : public CWinApp
{
public:
	CVisionShapeModelApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
