#ifndef __MODULE_DEVELOP_HEADER_H__
#define __MODULE_DEVELOP_HEADER_H__
//////////////////////////////////////////////////////////////////////////
//��������ֵ����׼�����������ֵ�淶
//////////////////////////////////////////////////////////////////////////
//DLL_VER_INFO��̬��汾��Ϣ
//		_dwByteSize���ṹ���ֽڴ�С����Ҫ���ڽӿڲ�������ʱ�����ڴ���
//		_dwVerInfo���ṹ��İ汾�������պ�汾�������������
//		_szLibType�����ڱ�ʾģ������ͣ�ģ������������и����Ͳ��������
//					�����������жԸ�ģ������汾��Ϣ�Լ���38�ֽ���Ϣ��1���ֽڵĽ���0�ַ���
//					����GUID��ʽ�������ɣ����Ĺ���Ա�ڹ鵵ʱ����ά��
//		_cbFlagUnicode��Unicodeģ����־��0��ʾ��Unicodeģ��⣬��0��ʾUnicodeģ���
//		_cbCmdCount: ֧�ֵ��ַ������������0���ʾ��֧���ַ�������
//		_cbReserved���������֣��ṹ��汾1�б���ȫΪ0
//		_cbExtraInfo��������Ϣ���֣���ģ�鿪�������ߴ洢���⸽����Ϣ��
typedef struct tagDLL_VER_INFO{
	//�汾1�ı���
	DWORD	_dwByteSize;//�ṹ���ֽڴ�С����ṹ��ͷ�ֽڴ�С��
	DWORD	_dwVerInfo;//�ṹ��İ汾
	DWORD	_dwVerMain;//ģ������汾��
	DWORD	_dwVerSubMain;//ģ������ΰ汾��
	DWORD	_dwVerSubSub;//ģ���δΰ汾��
	DWORD	_dwInterfaceNo;//֧�ֵ���Ч���Ľӿںţ���С��Ч�ӿںţ�1��
							//�ӿں�˳������������ӣ���ģ���֧�ֽӿں�5��
							//�����֧��1��2��3��4�Ľӿںţ�
	char	_szLibType[39];//ANSIģ������ͣ����������и����Ͳ��ܸ��ģ�����GUID���б�ʾ��
							//��ʽ�磺"{1838BB85-891B-414d-8687-9898DF0D3B6F}"
	BYTE	_cbFlagUnicode;//UNICODEģ����־
	BYTE	_cbCmdCount;//֧�ֵ��ַ������������0���ʾ��֧���ַ�������
	BYTE	_cbReserved[127];//��������������չ��
	BYTE	_cbExtraInfo[320];//���ڴ洢������Ϣ
} DLL_VER_INFO;

//DLL_CMD_INFOģ��֧���ַ�������ṹ��
//		_dwByteSize���ṹ���ֽڴ�С����Ҫ���ڽӿڲ�������ʱ�����ڴ��ã�
//		_dwVerInfo���ṹ��İ汾�������պ�汾������������䣻
//		_szCmd��������ַ������
//		_ptrFunc�����ַ��������������Ӧ������
typedef struct tagDLL_CMD_INFO{
	//�汾1�ı���
	DWORD	_dwByteSize;//�ṹ���ֽڴ�С����ṹ��ͷ�ֽڴ�С��
	DWORD	_dwVerInfo;//�ṹ��İ汾
	char	_szCmd[124];//ANSI�ַ�������
	DWORD	_ptrFunc;//���ַ����������Ӧ����Ӧ����
} DLL_CMD_INFO;

//CMgrDllDelegate��������߱�д��ʾ���ö�̬�⺯��
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

	//���ö�̬������·������
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

	//�ͷŶ�̬��
	void ReleaseLib(){
		/*if (m_lpszDllPathFullName)
		{
		delete[] m_lpszDllPathFullName;
		m_lpszDllPathFullName=NULL;
		}*/
		if( NULL!=m_hLib ){
			::FreeLibrary(m_hLib);
			m_hLib=NULL;
		}
		m_bFuncLoaded=FALSE;
	}

	//��ȡ��̬��汾��Ϣ
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

	//�����ӿ�ָ��
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

	//��ȡģ���֧�ֵ������ַ�����Ϣ
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
	//��ȡ��̬�⵼������ָ�룬����ɸ�����Ҫ���أ�_DoLoadFunc��_DoCorrectFuncLoadedFlag����ͬʱ����
	virtual void _DoLoadFunc(){
		////����ͨ�ú���ָ��
		m_pfncGetDllInfo = (void*) ::GetProcAddress((HMODULE) m_hLib, (LPCSTR) "DllGetVerInfo");
		m_pfnCreateInterface = (void*) ::GetProcAddress((HMODULE) m_hLib, (LPCSTR) "DllCreateInterface");
		m_pfncGetCmdInfo = (void*) ::GetProcAddress((HMODULE) m_hLib, (LPCSTR) "DllGetCmdInfo");

		////�����������⺯��ָ��
	}

	//ˢ�º���ָ���ȡ��־������ɸ�����Ҫ���أ�_DoLoadFunc��_DoCorrectFuncLoadedFlag����ͬʱ����
	virtual void _DoCorrectFuncLoadedFlag(){
		m_bFuncLoaded = (NULL != m_pfncGetDllInfo) &&
						(NULL != m_pfnCreateInterface) &&
						(NULL != m_pfncGetCmdInfo);

		////�����������⺯��ָ��������ж�
	}

	//�γ��ڴ���ֵ�������붯̬�⼰��ȡ����ָ����
	DWORD _HandleErrInLoadFunc(){
		DWORD rlt=0x00;
		if( NULL==_GetLibModule() ){//��̬������ʧ��
			rlt = 0x80000004;
		}
		else{//�ڶ�̬���У����뺯��ָ��ʧ��
			rlt = 0x80000005;
		}
		return rlt;
	}

	//���붯̬�⣬����ȡ����ָ��
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
