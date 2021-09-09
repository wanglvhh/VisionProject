// SockDll.h : main header file for the SOCKDLL DLL
//

#if !defined(AFX_SOCKDLL_H__F666CB45_CA4E_11D6_AAAF_00E04C3AA9CB__INCLUDED_)
#define AFX_SOCKDLL_H__F666CB45_CA4E_11D6_AAAF_00E04C3AA9CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSockDllApp
// See SockDll.cpp for the implementation of this class
//

class CSockDllApp : public CWinApp
{
public:
	CSockDllApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSockDllApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CSockDllApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOCKDLL_H__F666CB45_CA4E_11D6_AAAF_00E04C3AA9CB__INCLUDED_)
