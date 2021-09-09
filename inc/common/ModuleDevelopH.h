#ifndef __MODULE_DEVELOP_HEADER_H__
#define __MODULE_DEVELOP_HEADER_H__

//////////////////////////////////////////////////////////////////////////
//函数返回值见标准软件开发返回值规范
//////////////////////////////////////////////////////////////////////////
//DLL_VER_INFO动态库版本信息
//		_dwByteSize：结构体字节大小，主要用于接口参数传出时分配内存用
//		_dwVerInfo：结构体的版本，用于日后版本开发规则的扩充
//		_szLibType：用于标示模块库类型，模块库升级过程中该类型不允许更改
//					（程序运行中对各模块所需版本信息自检用38字节信息加1个字节的结束0字符）
//					采用GUID形式进行生成，中心管理员在归档时进行维护
//		_cbFlagUnicode：Unicode模块库标志，0表示非Unicode模块库，非0表示Unicode模块库
//		_cbCmdCount: 支持的字符串命令个数，0则表示不支持字符串命令
//		_cbReserved：保留部分，结构体版本1中必须全为0
//		_cbExtraInfo：附加信息部分，由模块开发开发者存储特殊附加信息用
typedef struct tagDLL_VER_INFO{
	//版本1的变量
	DWORD	_dwByteSize;//结构体字节大小（或结构体头字节大小）
	DWORD	_dwVerInfo;//结构体的版本
	DWORD	_dwVerMain;//模块库主版本号
	DWORD	_dwVerSubMain;//模块库主次版本号
	DWORD	_dwVerSubSub;//模块库次次版本号
	DWORD	_dwInterfaceNo;//支持的有效最大的接口号（最小有效接口号：1，
							//接口号顺序必须连续增加，即模块库支持接口号5，
							//则必须支持1，2，3，4的接口号）
	char	_szLibType[39];//ANSI模块库类型，升级过程中该类型不能更改，采用GUID进行标示，
							//形式如："{1838BB85-891B-414d-8687-9898DF0D3B6F}"
	BYTE	_cbFlagUnicode;//UNICODE模块库标志
	BYTE	_cbCmdCount;//支持的字符串命令个数，0则表示不支持字符串命令
	BYTE	_cbReserved[127];//保留，做后续扩展用
	BYTE	_cbExtraInfo[320];//用于存储附加信息
} DLL_VER_INFO;

//DLL_CMD_INFO模块支持字符串命令结构体
//		_dwByteSize：结构体字节大小，主要用于接口参数传出时分配内存用；
//		_dwVerInfo：结构体的版本，用于日后版本开发规则的扩充；
//		_szCmd：具体的字符串命令；
//		_ptrFunc：与字符串命令关联的响应函数；
typedef struct tagDLL_CMD_INFO{
	//版本1的变量
	DWORD	_dwByteSize;//结构体字节大小（或结构体头字节大小）
	DWORD	_dwVerInfo;//结构体的版本
	char	_szCmd[124];//ANSI字符串命令
	DWORD	_ptrFunc;//与字符串命令相对应的响应函数
} DLL_CMD_INFO;

//CMgrDllDelegate方便调用者编写显示调用动态库函数
class CMgrDllDelegate
{
public:
	CMgrDllDelegate(LPCTSTR lpcszDllPathFullName){
		////
		m_lpszDllPathFullName=new TCHAR[1];
		m_hLib=NULL;
		m_bFuncLoaded=FALSE;

		////
		SetLibName(lpcszDllPathFullName);
	}
	virtual ~CMgrDllDelegate(){
		delete[] m_lpszDllPathFullName;
		m_lpszDllPathFullName=NULL;
		ReleaseLib();
	}

	//设置动态库完整路径名称
	void SetLibName(LPCTSTR lpcszDllPathFullName){
		delete[] m_lpszDllPathFullName;
		m_lpszDllPathFullName=NULL;
		if( NULL==lpcszDllPathFullName || 0==*lpcszDllPathFullName ){
			m_lpszDllPathFullName = new TCHAR[1];
			*m_lpszDllPathFullName = 0;
		}
		else{
			TCHAR* pSrc=(TCHAR*) lpcszDllPathFullName;
			TCHAR* pDst = pSrc;
			while( 0!=(*pDst) ){
				pDst++;
			}
			m_lpszDllPathFullName = new TCHAR[pDst-pSrc+1];
			pDst = m_lpszDllPathFullName;
			while( 0!=*pSrc ){
				*pDst = *pSrc;
				pSrc++;
				pDst++;
			}
			*pDst = 0;
		}
	}

	//释放动态库
	void ReleaseLib(){
		if( NULL!=m_hLib ){
			::FreeLibrary(m_hLib);
			m_hLib=NULL;
		}
		m_bFuncLoaded=FALSE;
	}

	//获取动态库版本信息
	DWORD DllGetVerInfo(DLL_VER_INFO& dllVerInfo){
		DWORD rlt = 0x00;
		if( !_LoadFunc() ){
			rlt = _HandleErrInLoadFunc();
		}
		else{
			rlt = ((DWORD (__stdcall*)(DLL_VER_INFO&)) m_pfncGetDllInfo)(dllVerInfo);
		}
		////
		return rlt;
	}

	//创建接口指针
	DWORD DllCreateInterface(long nInterfaceNo,void** ppInterface){
		DWORD rlt = 0x00;
		if( !_LoadFunc() ){
			rlt = _HandleErrInLoadFunc();
		}
		else{
				rlt = ((DWORD (__stdcall*)(long,void**)) m_pfnCreateInterface)(nInterfaceNo, ppInterface);
		}
		////
		return rlt;
	}

	//获取模块库支持的命令字符串信息
	DWORD DllGetCmdInfo(long& nCmdIndex, DLL_CMD_INFO* pDllCmdInfo){
		DWORD rlt = 0x00;
		if( !_LoadFunc() ){
			rlt = _HandleErrInLoadFunc();
		}
		else{
			rlt = ((DWORD (__stdcall*)(long&,DLL_CMD_INFO*)) m_pfncGetCmdInfo)(nCmdIndex, pDllCmdInfo);
		}
		////
		return rlt;
	}

protected:
	//获取动态库导出函数指针，子类可根据需要重载，_DoLoadFunc与_DoCorrectFuncLoadedFlag必须同时重载
	virtual void _DoLoadFunc(){
		////载入通用函数指针
		m_pfncGetDllInfo = (void*) ::GetProcAddress((HMODULE) m_hLib, (LPCSTR) "DllGetVerInfo");
		m_pfnCreateInterface = (void*) ::GetProcAddress((HMODULE) m_hLib, (LPCSTR) "DllCreateInterface");
		m_pfncGetCmdInfo = (void*) ::GetProcAddress((HMODULE) m_hLib, (LPCSTR) "DllGetCmdInfo");

		////载入子类特殊函数指针
	}

	//刷新函数指针获取标志，子类可根据需要重载，_DoLoadFunc与_DoCorrectFuncLoadedFlag必须同时重载
	virtual void _DoCorrectFuncLoadedFlag(){
		m_bFuncLoaded = (NULL != m_pfncGetDllInfo) &&
						(NULL != m_pfnCreateInterface) &&
						(NULL != m_pfncGetCmdInfo);

		////进行子类特殊函数指针的载入判断
	}

	//形成在错误值，在载入动态库及获取函数指针中
	DWORD _HandleErrInLoadFunc(){
		DWORD rlt=0x00;
		if( NULL==_GetLibModule() ){//动态库载入失败
			rlt = 0x80000004;
		}
		else{//在动态库中，载入函数指针失败
			rlt = 0x80000005;
		}
		return rlt;
	}

	//载入动态库，及获取函数指针
	BOOL _LoadFunc(){
		if( !_IsFuncLoaded() ){
			if( !__LoadLib() )
				return FALSE;
			////
			_DoLoadFunc();

			////
			_DoCorrectFuncLoadedFlag();
			return _IsFuncLoaded();
		}
		////
		return TRUE;
	}

	BOOL _IsFuncLoaded() const{
		return m_bFuncLoaded;
	}

	HMODULE _GetLibModule() const{
		return m_hLib;
	}

private:
	BOOL __LoadLib(){
		if( NULL==m_hLib ){
			m_hLib = ::LoadLibrary(m_lpszDllPathFullName);
		}
		return (NULL!=m_hLib);
	}

protected:
	BOOL m_bFuncLoaded;

private:
	LPTSTR m_lpszDllPathFullName;
	HMODULE m_hLib;

	////
	void* m_pfncGetDllInfo;
	void* m_pfnCreateInterface;
	void* m_pfncGetCmdInfo;
};

#endif
