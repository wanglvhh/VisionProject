// VisionCommWrite.h : VisionCommWrite DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

// CVisionCommWriteApp
// �йش���ʵ�ֵ���Ϣ������� VisionCommWrite.cpp
//

class CVisionCommWriteApp : public CWinApp
{
public:
	ULONG_PTR m_gdiplusToken;
public:
	CVisionCommWriteApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};
