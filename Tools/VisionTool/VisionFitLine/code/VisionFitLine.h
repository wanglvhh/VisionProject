// VisionFitLine.h : VisionFitLine DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

// CVisionFitLineApp
// �йش���ʵ�ֵ���Ϣ������� VisionFitLine.cpp
//

class CVisionFitLineApp : public CWinApp
{
public:
	CVisionFitLineApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
