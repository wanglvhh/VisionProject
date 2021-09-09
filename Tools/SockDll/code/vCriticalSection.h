#ifndef __V_CRITICALSECTION_H__
#define __V_CRITICALSECTION_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <windows.h>
/////////////////////////////////////////////////////////////

class VCriticalSection{
public:
	VCriticalSection(LPCRITICAL_SECTION pCric)
	{
		m_pCriticalSection=pCric;
		::EnterCriticalSection(m_pCriticalSection);
	}
	~VCriticalSection()
	{
		::LeaveCriticalSection(m_pCriticalSection);
	}
private:
	LPCRITICAL_SECTION m_pCriticalSection;
};
/////////////////////////////////////////////////////////////
#endif