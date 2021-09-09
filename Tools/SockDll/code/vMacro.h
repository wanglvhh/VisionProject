///////////////////////////////////////////////////////////////////
#ifndef __VMACRO_H__
#define __VMACRO_H__
/****************************************************************\
	This Header File is used as Debuging;Only Trace string;
		general trace macro!
	Designed by Vinca!
								2002.11
\****************************************************************/
//////////////////////
#pragma warning( disable : 4067 )
//////////////////////////////////////////////////////////////////
#ifdef vTrace(x)
	#undef vTrace(x)
#endif

#ifdef _DEBUG
	#define vTrace(x)											\
			{													\
				TCHAR* pvTrace_x=(TCHAR*) ((LPCTSTR) (x));		\
				UINT uvTrace_x_len=::_tcslen((LPCTSTR) (x));	\
				::OutputDebugString(x);							\
				if( uvTrace_x_len==0 || pvTrace_x[uvTrace_x_len-1]!=TCHAR('\n') )	\
					::OutputDebugString(TEXT("\n"));			\
			}
#else
	#define vTrace(x)
#endif

#ifdef VTRACE(x)
	#undef VTRACE(x)
#endif
#define VTRACE(x)		vTrace(x)
#ifdef Trace(x)
	#undef Trace(x)
#endif
#define Trace(x)		vTrace(x)

//x_pfunc������ԭ��ָ��,y_handle����dll���
//z_funcName����Ҫ��ȡ��dll�к�������(�ַ���)
//���ػ�ȡ�ĺ���ָ��
#ifdef GetPfunc(x_pfunc,y_handle,z_funcName)
	#undef GetPfunc(x_pfunc,y_handle,z_funcName)
#endif
#define GetPfunc(x_pfunc,y_handle,z_funcName)		\
	((x_pfunc) GetProcAddress((y_handle),(LPCTSTR)(z_funcName)))
//////////////////////////////////////////////////////////////////
#pragma warning( default : 4067 )
//////////////////////
#endif
