// BaseIni.cpp: implementation of the CBaseIni class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <assert.h>
#include <tchar.h>
#include <stdio.h>
#include "BaseIni.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*/////////////////////////////////////////////////////////////////////
	class CBaseIni
/////////////////////////////////////////////////////////////////////*/
CBaseIni::CBaseIni()
{
	m_bInitialized=FALSE;
}

CBaseIni::~CBaseIni()
{
}

BOOL CBaseIni::Initialize(void* pvoid)
{
	::ZeroMemory((void*) m_szFileName,sizeof(TCHAR)*MAX_PATH);
	m_bInitialized=FALSE;
	if( NULL!=pvoid ){
		::_tcscpy(m_szFileName,(LPTSTR) pvoid);
		m_bInitialized=TRUE;
	}
	////
	return m_bInitialized;
}

BOOL CBaseIni::PathIsExist(LPCTSTR lpszPath)
{
	DWORD attr=::GetFileAttributes(lpszPath);
	if( -1==attr || (FILE_ATTRIBUTE_DIRECTORY&attr)!=FILE_ATTRIBUTE_DIRECTORY )
		return FALSE;
	return TRUE;
}

BOOL CBaseIni::FileIsExist(LPCTSTR lpszFullPathName)
{
	DWORD attr=::GetFileAttributes(lpszFullPathName);
	if( -1==attr || (FILE_ATTRIBUTE_DIRECTORY&attr)==FILE_ATTRIBUTE_DIRECTORY )
		return FALSE;
	return TRUE;
}

void CBaseIni::FileAttribeRW(LPCTSTR lpszFullPathName)
{
	DWORD attr=::GetFileAttributes(lpszFullPathName);
	if( FileIsExist(lpszFullPathName) ){
		if( (FILE_ATTRIBUTE_READONLY&attr)==FILE_ATTRIBUTE_READONLY ){
			attr &= (~FILE_ATTRIBUTE_READONLY);
			attr |= FILE_ATTRIBUTE_NORMAL;
			::SetFileAttributes(lpszFullPathName,attr);
		}
	}
}

BOOL CBaseIni::FileIsEnableOpen(LPCTSTR lpszFullPathName)
{
	if( !FileIsExist(lpszFullPathName) ) return FALSE;
	/////////
	HANDLE hFile=::CreateFile(lpszFullPathName,GENERIC_READ,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if( INVALID_HANDLE_VALUE==hFile )
		return FALSE;
	::CloseHandle(hFile);
	return TRUE;
}

BOOL CBaseIni::CreateFile(LPCTSTR lpszFullPathName)
{
	if( FileIsExist(lpszFullPathName) ){
		FileAttribeRW(lpszFullPathName);
		return TRUE;
	}
	else{
		HANDLE hFile=::CreateFile(lpszFullPathName,GENERIC_READ | GENERIC_WRITE,FILE_SHARE_READ,
			NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_NORMAL,
			NULL);
		if( INVALID_HANDLE_VALUE==hFile ) return FALSE;
		::CloseHandle(hFile);
		return TRUE;
	}
}

//写入某一字段
void CBaseIni::WriteIniField(LPCTSTR lpszSection, LPCTSTR lpszKey, LPCTSTR lpszValue)
{
	assert( IsInitialized() );
	::WritePrivateProfileString(lpszSection,lpszKey,lpszValue,m_szFileName);
}

//读取某一字段值，函数内部分配内存，外部调用者负责释放内存，失败返回空
LPTSTR CBaseIni::ReadIniField(LPCTSTR lpszSection, LPCTSTR lpszKey, LPCTSTR lpszDefaultValue)
{
	assert( IsInitialized() );
	TCHAR buff[MAX_PATH];
	::ZeroMemory((void*) buff,sizeof(TCHAR)*MAX_PATH);
	/////
	DWORD re=::GetPrivateProfileString(lpszSection,lpszKey,lpszDefaultValue,buff,MAX_PATH,m_szFileName);
	if( 0>=re )
		return (LPTSTR) NULL;
	TCHAR* p=new TCHAR[re+1];
	if( NULL==p )
		return (LPTSTR) NULL;
	::ZeroMemory((void*) p,sizeof(TCHAR)*(re+1));
	::CopyMemory((void*) p,(void*) buff,sizeof(TCHAR)*re);
	return p;
}

void CBaseIni::DeleteIniKey(LPCTSTR lpszSection, LPCTSTR lpszKey)
{
	assert( IsInitialized() );
	WriteIniField(lpszSection,lpszKey,NULL);
}

void CBaseIni::DeleteIniSection(LPCTSTR lpszSection)
{
	assert( IsInitialized() );
	WriteIniField(lpszSection,NULL,NULL);
}

/*///////////////////////////////////////////////////////////////
	class CBaseIniEx
///////////////////////////////////////////////////////////////*/
CBaseIniEx::CBaseIniEx()
{
}

CBaseIniEx::~CBaseIniEx()
{
}

void CBaseIniEx::WriteInt(LPCTSTR lpszSection, LPCTSTR lpszKey, const long lToWrite)
{
	TCHAR buff[MAX_PATH];
	::ZeroMemory((void*) buff,sizeof(TCHAR)*MAX_PATH);
	::_stprintf(buff,_T("%ld"),lToWrite);
	WriteIniField(lpszSection,lpszKey,buff);
}

void CBaseIniEx::WriteDouble(LPCTSTR lpszSection, LPCTSTR lpszKey, const double dbToWrite)
{
	TCHAR buff[MAX_PATH];
	::ZeroMemory((void*) buff,sizeof(TCHAR)*MAX_PATH);
	::_stprintf(buff,_T("%f"),dbToWrite);
	WriteIniField(lpszSection,lpszKey,buff);
}

long CBaseIniEx::ReadInt(LPCTSTR lpszSection, LPCTSTR lpszKey, long lDefault)
{
	TCHAR* p=ReadIniField(lpszSection,lpszKey);
	if( NULL==p ) return lDefault;
	long ret=::_ttol(p);
	delete[] p;
	return ret;
}

double CBaseIniEx::ReadDouble(LPCTSTR lpszSection, LPCTSTR lpszKey, double dbDefault)
{
	TCHAR* p=ReadIniField(lpszSection,lpszKey);
	if( NULL==p ) return dbDefault;
	double ret= _wtof(p)/*atof(p)*/;
	delete[] p;
	return ret;
}

#ifndef NOT_USE_MFC
CString CBaseIniEx::ReadString(LPCTSTR lpszSection, LPCTSTR lpszKey, LPCTSTR lpszDefaultValue)
{
	CString strRet(_T(""));
	TCHAR* p=ReadIniField(lpszSection,lpszKey,lpszDefaultValue);
	if( NULL!=p ){
		strRet=p;
		delete[] p;
	}
	return strRet;
}

void CBaseIniEx::WriteString(LPCTSTR lpszSection, LPCTSTR lpszKey, LPCTSTR lpszValue)
{
	WriteIniField(lpszSection,lpszKey,lpszValue);
}
#endif