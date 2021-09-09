// Vision2DCamera.h : Vision2DCamera DLL 的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号

// CVision2DCameraApp
// 有关此类实现的信息，请参阅 Vision2DCamera.cpp
//

class CVision2DCameraApp : public CWinApp
{
public:
	ULONG_PTR m_gdiplusToken;
public:
	CVision2DCameraApp();

// 重写
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};
