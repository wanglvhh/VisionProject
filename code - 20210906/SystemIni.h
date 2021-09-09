#pragma once

class CSystemIni :
	public CBaseIniEx
{
public:
	CString     m_strVersion ;
	CString     m_strProjectPath ;
public:
	CSystemIni(void);
	~CSystemIni(void);

	void LoadPara() ;
	void WritePara() ;
	virtual BOOL Initialize(void* pvoid=NULL);
};

extern CSystemIni g_sysIni ;
