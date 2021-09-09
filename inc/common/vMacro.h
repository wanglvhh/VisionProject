///////////////////////////////////////////////////////////////////
#ifndef __VMACRO_H__
#define __VMACRO_H__
/****************************************************************\
		This Header File is used as definition some general and
	useful macro!(All rights reserved!)
		Designed by Vinca!
													2002.11
\****************************************************************/
///////////////////位图有关的宏(only 16- or 32-bpp must exist bit mask)
#define DIB_FILE_FLAGS	0x4D42	//"BM"
#define IsWin32Dib(lpbi)	\
	((*(LPDWORD)(lpbi))!=sizeof(BITMAPCOREHEADER))
//位图每行对齐于4字节边界(用于计算DIB行的存储长度)(低5位清零，调整到32Bits的边界)
#define WIDTHBYTES(bits)	((((DWORD)(bits+31)) & 0xFFFFFFE0)>>3)
///////////////////通用Dll有关的宏
typedef void* (__stdcall* vVoidPtFuncVoid)(void);
typedef void  (__stdcall* vVoidFuncVoid)(void);
//x_pfunc代表函数原形指针,y_handle代表dll句柄
//z_funcName代表要获取的dll中函数名称(字符串)
//返回获取的函数指针
#define GetPfunc(x_pfunc,y_handle,z_funcName)		\
	((x_pfunc) GetProcAddress((y_handle),(z_funcName)))

//////////////////////调试宏
#ifdef _DEBUG
	#define vTrace(x)											\
			{													\
				TCHAR* pvTrace_x=(TCHAR*) ((LPCTSTR) (x));		\
				TCHAR szvTraceBuffer[2]={0,0};					\
				UINT uvTrace_x_len=::_tcslen((LPCTSTR) (x));	\
				for( UINT vTrace_i=0;vTrace_i<uvTrace_x_len;vTrace_i++ ){	\
					szvTraceBuffer[0]=pvTrace_x[vTrace_i];				\
					::OutputDebugString(szvTraceBuffer);		\
				}												\
				if( uvTrace_x_len==0 || pvTrace_x[uvTrace_x_len-1]!=TCHAR('\n') )	\
					::OutputDebugString(TEXT("\n"));			\
			}
#else
	#define vTrace(x)
#endif

#define VTRACE(x)		vTrace(x)
#define Trace(x)		vTrace(x)
//////////////////////////////
///	'\r'==0x0D; '\n'==0x0A
//////////////////////////////
#endif
