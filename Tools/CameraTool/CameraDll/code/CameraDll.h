// CameraDll.h : CameraDll DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

// CCameraDllApp
// �йش���ʵ�ֵ���Ϣ������� CameraDll.cpp
//

class CCameraDllApp : public CWinApp
{
public:
	CCameraDllApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
