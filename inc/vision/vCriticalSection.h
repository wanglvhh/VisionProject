#ifndef __V_CRITICALSECTION_H__
#define __V_CRITICALSECTION_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <windows.h>
/////////////////////////////////////////////////////////////
#define VCriticalSection	vCriticalSection
/////用于进程内的线程同步
class vCriticalSection{
public:
	vCriticalSection(LPCRITICAL_SECTION pCric)
	{
		if( (m_pCriticalSection=pCric)!=NULL )
			::EnterCriticalSection(m_pCriticalSection);
	}
	~vCriticalSection()
	{
		if( m_pCriticalSection!=NULL )
			::LeaveCriticalSection(m_pCriticalSection);
	}
private:
	LPCRITICAL_SECTION m_pCriticalSection;
};

//////用于进程间或进程内的线程同步
class vMutexEntry
{
public:
	vMutexEntry(HANDLE hMutex=NULL){
		if( (m_hMutex=hMutex)!=NULL ){
			::WaitForSingleObject(m_hMutex,INFINITE);
		}
	}
	~vMutexEntry(){
		if( m_hMutex!=NULL )
			::ReleaseMutex(m_hMutex);
	}
private:
	HANDLE m_hMutex;
};
/////////////////////////////////////////////////////////////
#endif