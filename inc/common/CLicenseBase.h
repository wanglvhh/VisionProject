#pragma once
#include "ModuleDevelopH.h"

class CMgrDllLicenseIm : public CMgrDllDelegate
{
public:
#ifdef _DEBUG
	CMgrDllLicenseIm(LPCTSTR lpcszDllPathFullName=_T("NYLicense.dll"))
		: CMgrDllDelegate(lpcszDllPathFullName)
	{
	}
#else
	CMgrDllLicenseIm(LPCTSTR lpcszDllPathFullName=_T("NYLicense.dll"))
		: CMgrDllDelegate(lpcszDllPathFullName)
	{
	}
#endif
	virtual ~CMgrDllLicenseIm(){
	}
};

class CLicenseBase
{
public:
	virtual bool License_CreateMachineFile() = 0;
	virtual bool License_CreateLicenseFile() = 0 ;
	virtual bool License_CheckLicense() = 0;
	virtual bool License_CreateMachineCode(CString &strMachineCode) = 0 ;
	virtual bool License_CreateLicenseCode(CString strMachineCode,CString &strLicenseCode) = 0 ;
	virtual bool License_CheckLicenseCode(CString strMachineCode,CString strLicenseCode) = 0 ;
};