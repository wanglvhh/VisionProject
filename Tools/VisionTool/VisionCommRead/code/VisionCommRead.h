// VisionCommRead.h : VisionCommRead DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

// CVisionCommReadApp
// �йش���ʵ�ֵ���Ϣ������� VisionCommRead.cpp
//

class CVisionCommReadApp : public CWinApp
{
public:
	ULONG_PTR m_gdiplusToken;
public:
	CVisionCommReadApp();

// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
};
