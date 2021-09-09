#include "StdAfx.h"
#include "SystemIni.h"

CSystemIni g_sysIni ;

CSystemIni::CSystemIni(void)
{
}

CSystemIni::~CSystemIni(void)
{
}

BOOL CSystemIni::Initialize(void *pvoid)
{
	if( !CBaseIni::Initialize(pvoid) )
		return FALSE;
	////////////
	SetInitStatus(FALSE);
	if( !pvoid ) return FALSE;
	::_tcscpy(m_szFileName,(LPCTSTR) pvoid);
	SetInitStatus(TRUE);
	////////////
	LoadPara();
	WritePara();

	return IsInitialized();
}

void CSystemIni::LoadPara()
{
	const TCHAR szSections[][64]={
		{_T("OptionPara")},//0
	};

	m_strVersion            = ReadString(szSections[0],_T("Version"),_T("VisionProject V1.0.0.1")) ;
	m_strProjectPath        = ReadString(szSections[0],_T("ProjectPath"),_T("")) ;
}

void CSystemIni::WritePara()
{
	const TCHAR szSections[][64]={
		{_T("OptionPara")},//0
	};

	WriteString(szSections[0],_T("Version"),m_strVersion) ;
	WriteString(szSections[0],_T("ProjectPath"),m_strProjectPath) ;
}