#pragma once
//#include "stdafx.h"

class CCSerialize
{
public:
	CCSerialize (LPCTSTR lpszFileName, BOOL bIsLoad, void* lpBuf = NULL);
	~CCSerialize(void);
	void SaveCopyFile(LPCTSTR lpszFileName);
	void LoadCopyFile(LPCTSTR lpszFileName);
	void SaveBuf(BYTE* Buf, DWORD Length);
	void LoadBuf(BYTE* Buf, DWORD Length);

	//写入
	void operator<<(BYTE by);
	void operator<<(WORD w);
	void operator<<(LONG l);
	void operator<<(DWORD dw);
	void operator<<(float f);
	void operator<<(double d);
	void operator<<(LONGLONG dwdw);
	void operator<<(ULONGLONG dwdw);
	void operator<<(int i);
	void operator<<(short w);
	void operator<<(char ch);
#ifdef _NATIVE_WCHAR_T_DEFINED
	void operator<<(wchar_t ch);
#endif
	void operator<<(unsigned u);
	void operator<<(bool b);
	void operator<<(CString lpszFileName);

	//读出
	void operator>>(BYTE& by);
	void operator>>(WORD& w);
	void operator>>(LONG& l);
	void operator>>(DWORD& dw);
	void operator>>(float& f);
	void operator>>(double& d);
	void operator>>(LONGLONG& dwdw);
	void operator>>(ULONGLONG& dwdw);
	void operator>>(int& i);
	void operator>>(short& w);
	void operator>>(char& ch);
#ifdef _NATIVE_WCHAR_T_DEFINED
	void operator>>(wchar_t& ch);
#endif
	void operator>>(unsigned& u);
	void operator>>(bool& b);
	void operator>>(CString& lpszFileName);

private:
	DWORD m_dwLoadLeng;
	BOOL m_bIsLoad;
	FILE *Serializefp;
	int m_nOverFlow;//为超过DWORD准备
	BYTE* m_lpBufCur;//读写数据
};
