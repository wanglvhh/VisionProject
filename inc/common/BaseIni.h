// BaseIni.h: interface for the CBaseIni class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HLINI_H__B1A16B6F_CD76_11D7_9FC4_00E04C4242E5__INCLUDED_)
#define AFX_HLINI_H__B1A16B6F_CD76_11D7_9FC4_00E04C4242E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#define NOT_USE_MFC
//�����õ���Ini�ļ��Ļ���
class CBaseIni
{
public:
	TCHAR m_szFileName[MAX_PATH];//ini�ļ�������·������
	CBaseIni();
	virtual ~CBaseIni();

public:
	void DeleteIniSection(LPCTSTR lpszSection);
	void DeleteIniKey(LPCTSTR lpszSection,LPCTSTR lpszKey);
	LPTSTR ReadIniField(LPCTSTR lpszSection,LPCTSTR lpszKey,LPCTSTR lpszDefaultValue=NULL);
	void WriteIniField(LPCTSTR lpszSection,LPCTSTR lpszKey,LPCTSTR lpszValue=NULL);
	BOOL IsInitialized() const{
		return m_bInitialized;
	}
	BOOL SetInitStatus(BOOL bInitial=TRUE){
		m_bInitialized=bInitial;
		return IsInitialized();
	}
	static BOOL CreateFile(LPCTSTR lpszFullPathName);
	static BOOL FileIsEnableOpen(LPCTSTR lpszFullPathName);
	static void FileAttribeRW(LPCTSTR lpszFullPathName);
	static BOOL FileIsExist(LPCTSTR lpszFullPathName);
	static BOOL PathIsExist(LPCTSTR lpszPath);
	virtual BOOL Initialize(void* pvoid=NULL);

private:
	BOOL m_bInitialized;//��ʾ�Ƿ��ѳ�ʼ��
};

class CBaseIniEx : public CBaseIni
{
public:
#ifndef NOT_USE_MFC
	void WriteString(LPCTSTR lpszSection,LPCTSTR lpszKey,LPCTSTR lpszValue=NULL);
	CString ReadString(LPCTSTR lpszSection,LPCTSTR lpszKey,LPCTSTR lpszDefaultValue=NULL);
#endif
	double ReadDouble(LPCTSTR lpszSection, LPCTSTR lpszKey,double dbDefault=0);
	long ReadInt(LPCTSTR lpszSection,LPCTSTR lpszKey,long lDefault=0);
	void WriteDouble(LPCTSTR lpszSection,LPCTSTR lpszKey,const double dbToWrite=0);
	void WriteInt(LPCTSTR lpszSection,LPCTSTR lpszKey,const long lToWrite=0);
	CBaseIniEx();
	~CBaseIniEx();
};

#endif // !defined(AFX_HLINI_H__B1A16B6F_CD76_11D7_9FC4_00E04C4242E5__INCLUDED_)
