#include "stdafx.h"
#include "CSerialize.h"

CCSerialize::CCSerialize(LPCTSTR lpszFileName, BOOL bIsLoad, void* lpBuf)
{
	m_bIsLoad = bIsLoad ;
	if(TRUE == bIsLoad)
		Serializefp = _tfopen(lpszFileName,_T("r+b"));
	else
	{
		Serializefp = _tfopen(lpszFileName,_T("w+b"));//应该清掉原有数据
	}

	m_lpBufCur = (BYTE*)lpBuf;
	if (m_lpBufCur == NULL)
	{
		m_lpBufCur = new BYTE[1024];
	}

	m_dwLoadLeng = 0;
	m_nOverFlow = 0;
}

CCSerialize::~CCSerialize(void)
{
	if(Serializefp != NULL)
		fclose(Serializefp);
	if(m_lpBufCur)
		delete[] m_lpBufCur;
}

void CCSerialize::SaveCopyFile(LPCTSTR lpszFileName)
{
	if(Serializefp == NULL)
		return;
	if(m_bIsLoad)
		return;
	FILE *fpRead;
	fpRead = _tfopen(lpszFileName,_T("r+b"));
	DWORD  dwLen = 0;
	DWORD dwWriteLen = 0;
	BYTE buf[4096];
	DWORD   dwTempLen = sizeof(buf);
	memset(buf,0,dwTempLen);
	fseek(Serializefp, 0, SEEK_END);
	if(fpRead == NULL)
	{
		memset(buf,0,dwTempLen);
		fwrite(buf,sizeof(BYTE),sizeof(dwLen),Serializefp);
		fseek(Serializefp, 0, SEEK_END);
	}
	else
	{
		fseek(fpRead, 0, SEEK_END);
		dwLen = ftell(fpRead);
		rewind(fpRead);
		memset(buf,0,dwTempLen);
		memcpy(buf,&dwLen,sizeof(dwLen));
		fwrite(buf,sizeof(BYTE),sizeof(dwLen),Serializefp);
		fseek(Serializefp, 0, SEEK_END);
		while(dwLen>0)
		{
			memset(buf,0,dwTempLen);
			if(dwLen >=dwTempLen)
			{
				fread(buf,sizeof(BYTE),dwTempLen,fpRead);
				fwrite(buf,sizeof(BYTE),dwTempLen,Serializefp);
				fseek(Serializefp, 0, SEEK_END);
				dwWriteLen +=dwTempLen;
				fseek(fpRead,dwWriteLen,SEEK_SET);
				dwLen -= dwTempLen;
			}
			else
			{
				fread(buf,sizeof(BYTE),dwLen,fpRead);
				fwrite(buf,sizeof(BYTE),dwLen,Serializefp);
				dwWriteLen +=dwLen;
				fseek(Serializefp, 0, SEEK_END);
				fseek(fpRead,dwWriteLen,SEEK_SET);
				dwLen -= dwLen;
			}
		}
	}
	fclose(fpRead);
}

void CCSerialize::LoadCopyFile(LPCTSTR lpszFileName)
{
	if(Serializefp == NULL)
		return;
	if(!m_bIsLoad)
		return;
	FILE *fpWrite;
	fpWrite = _tfopen(lpszFileName,_T("w+b"));
	DWORD  dwLen = 0;
	BYTE buf[4096];
	DWORD   dwTempLen = sizeof(buf);

	memset(buf,0,dwTempLen);
	fseek(Serializefp,m_dwLoadLeng,SEEK_SET);
	fread(buf,sizeof(BYTE),sizeof(dwLen),Serializefp);
	memcpy(&dwLen,buf,sizeof(dwLen));
	m_dwLoadLeng +=sizeof(dwLen);
	fseek(Serializefp,m_dwLoadLeng,SEEK_SET);
	while(dwLen>0)
	{
		memset(buf,0,dwTempLen);
		if(dwLen >=dwTempLen)
		{
			fread(buf,sizeof(BYTE),dwTempLen,Serializefp);
			fwrite(buf,sizeof(BYTE),dwTempLen,fpWrite);
			fseek(fpWrite, 0, SEEK_END);
			m_dwLoadLeng +=dwTempLen;
			fseek(Serializefp,m_dwLoadLeng,SEEK_SET);
			dwLen -= dwTempLen;
		}
		else
		{
			fread(buf,sizeof(BYTE),dwLen,Serializefp);
			fwrite(buf,sizeof(BYTE),dwLen,fpWrite);
			m_dwLoadLeng +=dwLen;
			fseek(fpWrite, 0, SEEK_END);
			fseek(Serializefp,m_dwLoadLeng,SEEK_SET);
			dwLen -= dwLen;
		}
	}
	fclose(fpWrite);
}

void CCSerialize::SaveBuf(BYTE* Buf, DWORD Length)
{
	if(Serializefp == NULL)
		return;
	if(m_bIsLoad)
		return;
	if(Length == 0)
		return;
	fseek(Serializefp, 0, SEEK_END);
	fwrite(Buf,sizeof(BYTE),Length,Serializefp);
	fseek(Serializefp, 0, SEEK_END);
}

void CCSerialize::LoadBuf(BYTE* Buf, DWORD Length)
{
	if(Serializefp == NULL)
		return;
	if(!m_bIsLoad)
		return;
	memset(Buf,0,1024);
	fseek(Serializefp,m_dwLoadLeng,SEEK_SET);
	fread(Buf,sizeof(BYTE),Length,Serializefp);
	m_dwLoadLeng +=Length;
	fseek(Serializefp,m_dwLoadLeng,SEEK_SET);
}

void CCSerialize::operator<<(int i)
{
	return CCSerialize::operator<<((LONG)i);
}

void CCSerialize::operator<<(unsigned u)
{
	return CCSerialize::operator<<((LONG)u);
}

void CCSerialize::operator<<(short w)
{
	return CCSerialize::operator<<((WORD)w);
}

void CCSerialize::operator<<(char ch)
{
	return CCSerialize::operator<<((BYTE)ch);
}

#ifdef _NATIVE_WCHAR_T_DEFINED
void CCSerialize::operator<<(wchar_t ch)
{
	return CCSerialize::operator<<((WORD)ch);
}
#endif

void CCSerialize::operator<<(bool b)
{
	return CCSerialize::operator <<((BYTE)(b ? 1 : 0));
}

void CCSerialize::operator<<(BYTE by)
{
	*(UNALIGNED BYTE*)m_lpBufCur = by;
	SaveBuf(m_lpBufCur,sizeof(BYTE));
}

void CCSerialize::operator<<(LONGLONG dwdw)
{
	*(UNALIGNED LONGLONG*)m_lpBufCur = dwdw;
	SaveBuf(m_lpBufCur,sizeof(LONGLONG));
}

void CCSerialize::operator<<(ULONGLONG dwdw)
{
	*(UNALIGNED ULONGLONG*)m_lpBufCur = dwdw;
	SaveBuf(m_lpBufCur,sizeof(ULONGLONG));
}

void CCSerialize::operator<<(WORD w)
{
	*(UNALIGNED WORD*)m_lpBufCur = w;
	m_lpBufCur += sizeof(WORD);
	SaveBuf(m_lpBufCur,sizeof(BYTE));
}
void CCSerialize::operator<<(LONG l)
{
	*(UNALIGNED LONG*)m_lpBufCur = l;
	SaveBuf(m_lpBufCur,sizeof(LONG));
}
void CCSerialize::operator<<(DWORD dw)
{
	*(UNALIGNED DWORD*)m_lpBufCur = dw;
	SaveBuf(m_lpBufCur,sizeof(DWORD));
}
void CCSerialize::operator<<(float f)
{
	*(UNALIGNED float*)m_lpBufCur = f;
	SaveBuf(m_lpBufCur,sizeof(float));
}
void CCSerialize::operator<<(double d)
{
	*(UNALIGNED double*)m_lpBufCur = d;
	SaveBuf(m_lpBufCur,sizeof(double));
}

void CCSerialize::operator>>(int& i)
{
	return CCSerialize::operator>>((LONG&)i);
}

void CCSerialize::operator>>(unsigned& u)
{
	return CCSerialize::operator>>((LONG&)u);
}

void CCSerialize::operator>>(short& w)
{
	return CCSerialize::operator>>((WORD&)w);
}

void CCSerialize::operator>>(char& ch)
{
	return CCSerialize::operator>>((BYTE&)ch);
}

#ifdef _NATIVE_WCHAR_T_DEFINED
void CCSerialize::operator>>(wchar_t& ch)
{
	return CCSerialize::operator>>((WORD&)ch);
}
#endif

void CCSerialize::operator>>(bool& b)
{
	BYTE by;
	operator>>(by);
	b = (by ? true : false);
}

void CCSerialize::operator>>(BYTE& by)
{
	LoadBuf(m_lpBufCur,sizeof(BYTE));
	by = *(UNALIGNED BYTE*)m_lpBufCur;
}

void CCSerialize::operator>>(LONGLONG& dwdw)
{
	LoadBuf(m_lpBufCur,sizeof(LONGLONG));
	dwdw = *(UNALIGNED LONGLONG*)m_lpBufCur;
}

void CCSerialize::operator>>(ULONGLONG& dwdw)
{
	LoadBuf(m_lpBufCur,sizeof(ULONGLONG));
	dwdw = *(UNALIGNED ULONGLONG*)m_lpBufCur;
}

void CCSerialize::operator>>(WORD& w)
{
	LoadBuf(m_lpBufCur,sizeof(WORD));
	w = *(UNALIGNED WORD*)m_lpBufCur;
	m_lpBufCur += sizeof(WORD);
}

void CCSerialize::operator>>(DWORD& dw)
{
	LoadBuf(m_lpBufCur,sizeof(DWORD));
	dw = *(UNALIGNED DWORD*)m_lpBufCur;
}

void CCSerialize::operator>>(float& f)
{
	LoadBuf(m_lpBufCur,sizeof(float));
	f = *(UNALIGNED float*)m_lpBufCur;
}
void CCSerialize::operator>>(double& d)
{
	LoadBuf(m_lpBufCur,sizeof(double));
	d = *(UNALIGNED double*)m_lpBufCur;
}

void CCSerialize::operator>>(LONG& l)
{
	LoadBuf(m_lpBufCur,sizeof(LONG));
	l = *(UNALIGNED LONG*)m_lpBufCur;
}

void CCSerialize::operator>>(CString& lpszFileName)
{
	DWORD dwLength;
	LoadBuf(m_lpBufCur,sizeof(DWORD));
	dwLength = *(UNALIGNED DWORD*)m_lpBufCur;
#ifdef _UNICODE
	LoadBuf(m_lpBufCur,dwLength*2);
	lpszFileName.Format(_T("%s"),m_lpBufCur);
#else
	LoadBuf(m_lpBufCur,dwLength);
	lpszFileName.Format(_T("%s"),m_lpBufCur);
#endif
}

void CCSerialize::operator<<(CString lpszFileName)
{
	DWORD dwLength = lpszFileName.GetLength();
	*(UNALIGNED DWORD*)m_lpBufCur = dwLength;
	SaveBuf(m_lpBufCur,sizeof(DWORD));
#ifdef _UNICODE
	memcpy(m_lpBufCur,lpszFileName,dwLength*2);
	SaveBuf(m_lpBufCur,dwLength*2);
#else
	memcpy(m_lpBufCur,lpszFileName,dwLength);
	SaveBuf(m_lpBufCur,dwLength);
#endif
}