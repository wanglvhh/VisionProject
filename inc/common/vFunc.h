#ifndef __V_FUNC_H__
#define __V_FUNC_H__
/**********************************************************************************\
    本图文件主要包括一些常用的全局辅助函数
    设计者：  Vinca
              2003.11.4
\**********************************************************************************/
////////////////////////////////////////////////////////////////////////////////////
#include <windows.h>
#include <tchar.h>
#include <stdarg.h>
#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <io.h>
#include <boost/locale.hpp>
using namespace boost::locale::conv;
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
/*----------------------------------------------------------------------------------
  检测WINDOWS的版本
  返回值：-999  -- 错误
      -2    -- win32s
      -1    -- win95
      0   -- win98
      1   -- winnt
      2   -- win2k
      999   -- 更高版本
----------------------------------------------------------------------------------*/
inline int GetWinVer()
{
  int nRet ( -999 );
  BOOL bOsVersionInfoEx ( TRUE );
  OSVERSIONINFOEX osvi;
  ::ZeroMemory ( ( void* ) &osvi, sizeof ( OSVERSIONINFOEX ) );
  osvi.dwOSVersionInfoSize = sizeof ( OSVERSIONINFOEX );

  if ( ! ( bOsVersionInfoEx =::GetVersionEx ( ( LPOSVERSIONINFO ) &osvi ) ) )
  {
    ::ZeroMemory ( ( void* ) &osvi, sizeof ( OSVERSIONINFOEX ) );
    osvi.dwOSVersionInfoSize = sizeof ( OSVERSIONINFO );

    if ( !::GetVersionEx ( ( LPOSVERSIONINFO ) &osvi ) )
      return nRet;
  }

  //////
  switch ( osvi.dwPlatformId )
  {
    case VER_PLATFORM_WIN32s:
      nRet = -2;
      break;

    case VER_PLATFORM_WIN32_WINDOWS:
      if ( ( osvi.dwMajorVersion > 4 ) ||
           ( ( osvi.dwMajorVersion == 4 ) && ( osvi.dwMinorVersion > 0 ) ) )
        nRet = 0;

      else nRet = -1;

      break;

    case VER_PLATFORM_WIN32_NT:
      if ( osvi.dwMajorVersion <= 4 )
        nRet = 1;

      else if ( osvi.dwMajorVersion == 5 )
        nRet = 2;

      else
        nRet = 999;

      break;
  }

  //////
  return nRet;
}

//VS开发环境默认为gbk2312,如修改编码保存格式为utf8，可以暂时解决乱码
//直接处理gbk转utf8编码
inline string gbktoutf8(string const &text)
{
	//"UTF-8", "GBK"
	std::string const &to_encoding("UTF-8");
	std::string const &from_encoding("GBK");
	method_type how = default_method;
	return boost::locale::conv::between(text,to_encoding,from_encoding,how) ;
	//return boost::locale::conv::between(text.c_str(), text.c_str() + text.size(), to_encoding, from_encoding, how);
}

////直接处理utf8转gbk
inline string utf8togbk(std::string const &text)
{
	std::string const &to_encoding("GBK");
	std::string const &from_encoding("UTF-8");
	method_type how = default_method;
	return boost::locale::conv::between(text,to_encoding,from_encoding,how) ;
	//return boost::locale::conv::between(text.c_str(), text.c_str() + text.size(), to_encoding, from_encoding, how);
}

////直接处理big5转utf8
inline string big5toutf8(std::string const &text)
{
	std::string const &to_encoding("UTF-8");
	std::string const &from_encoding("BIG5");
	method_type how = default_method;
	return boost::locale::conv::between(text,to_encoding,from_encoding,how) ;
	//return boost::locale::conv::between(text.c_str(), text.c_str() + text.size(), to_encoding, from_encoding, how);
}

////直接处理utf8转big5
inline string utf8tobig5(std::string const &text)
{
	std::string const &to_encoding("BIG5");
	std::string const &from_encoding("UTF-8");
	method_type how = default_method;
	return boost::locale::conv::between(text,to_encoding,from_encoding,how) ;
	//return boost::locale::conv::between(text.c_str(), text.c_str() + text.size(), to_encoding, from_encoding, how);
}

/*----------------------------------------------------------------------------------
  RegisterComDll(): 用于对进程内组件注册/注销
  入口参数:
      lpcszDllFullPath -- 待注册的DLL完整路径名称
      bRegister -- TRUE表示注册，FALSE表示注销
  返回值:
      -4表示DLL路径参数非法
      -3表示DLL指定路径下不存在
      -2表示DLL中入口函数不存在
      -1表示函数调用失败
      0表示成功执行
----------------------------------------------------------------------------------*/
inline int RegisterComDll ( LPCTSTR lpcszDllFullPath, BOOL bRegister = TRUE )
{
  if ( NULL == lpcszDllFullPath || 0 == *lpcszDllFullPath )
    return -4;

  HINSTANCE hLib =::LoadLibrary ( lpcszDllFullPath );

  if ( NULL == hLib ) return -3;

  typedef long ( __stdcall * pFunc ) ( void );
  int ret ( 0 );

  if ( bRegister )
  {
    pFunc func = ( pFunc ) ::GetProcAddress ( ( HMODULE ) hLib, LPCSTR ( "DllRegisterServer" ) );

    if ( NULL != func )
    {
      long _r = func();

      if ( _r < 0 ) ret = -1;
    }

    else ret = -2;
  }

  else
  {
    pFunc func = ( pFunc ) ::GetProcAddress ( ( HMODULE ) hLib, LPCSTR ( "DllUnregisterServer" ) );

    if ( NULL != func )
    {
      long _r = func();

      if ( _r < 0 ) ret = -1;
    }

    else ret = -2;
  }

  ::FreeLibrary ( ( HMODULE ) hLib );
  return ret;
}

/*----------------------------------------------------------------------------------
  GetWinSysFreq(): 获取当前的系统频率
----------------------------------------------------------------------------------*/
inline double GetWinSysFreq ( void )
{
  _LARGE_INTEGER dfValue;
  ::QueryPerformanceFrequency ( &dfValue );
  return ( double ) dfValue.QuadPart;
}

/*----------------------------------------------------------------------------------
  GetWinCurSysCounter(): 获取当前的系统COUNTER记数值
----------------------------------------------------------------------------------*/
inline LONGLONG GetWinCurSysCounter ( void )
{
  _LARGE_INTEGER dfValue;
  ::QueryPerformanceCounter ( &dfValue );
  return ( LONGLONG ) dfValue.QuadPart;
}
/*------------------------------------*/

inline DWORD GetCurTime_us()
{
  static double dbFreq = 0;
  LONGLONG tStart = 0, tEnd = 0, tDelay = 0;
  DWORD dwDelay;

  if ( dbFreq < 0.000001 )
    dbFreq = GetWinSysFreq();

  //  tDelay=(LONGLONG) (dbFreq*usToDelay/1000000.0);
  tStart = GetWinCurSysCounter();
  dwDelay = (DWORD)(( 1000000.0 / dbFreq ) * tStart);
  return ( DWORD ) ( dwDelay );
}

inline DWORD GetCurTime_ms()
{
  static double dbFreq = 0;
  LONGLONG tStart = 0, tEnd = 0, tDelay = 0;
  DWORD dwDelay;

  if ( dbFreq < 0.000001 )
    dbFreq = GetWinSysFreq();

  //  tDelay=(LONGLONG) (dbFreq*usToDelay/1000000.0);
  tStart = GetWinCurSysCounter();
  dwDelay = ( DWORD )(( 1000000.0 / dbFreq ) * tStart);
  return ( DWORD ) ( dwDelay / 1000 );
}
/*----------------------------------------------------------------------------------
  vDelay_us(): us单位的延时
  vDelay_ms(): ms单位的延时
  vDelay_s():  s单位的延时
----------------------------------------------------------------------------------*/
inline void vDelay_us ( double usToDelay )
{
  static double dbFreq = 0;
  LONGLONG tStart, tEnd, tDelay = 0;

  if ( dbFreq < 0.000001 )
    dbFreq = GetWinSysFreq();

  if ( usToDelay < 0 ) usToDelay = 0;

  tDelay = ( LONGLONG ) ( dbFreq * usToDelay / 1000000.0 );
  tStart = GetWinCurSysCounter();

  while ( 1 )
  {
    tEnd = GetWinCurSysCounter();

    if ( tEnd < tStart || ( tEnd - tStart ) >= tDelay )
      break;
  }
}

inline void vDelay_ms ( double msToDelay )
{
  vDelay_us ( msToDelay * 1000.0 );
}
inline void vDelay_s ( double sToDelay )
{
  vDelay_us ( sToDelay * 1000000.0 );
}

/*----------------------------------------------------------------------------------
  进行消息循环的等待
----------------------------------------------------------------------------------*/
inline void DoEvent ( void )
{
  MSG msg;

  while ( ::PeekMessage ( &msg, NULL, 0, 0, PM_REMOVE ) )
  {
    ::TranslateMessage ( &msg );
    ::DispatchMessage ( &msg );
  }
}

/*----------------------------------------------------------------------------------
  获取指定窗口的顶级窗口句柄
----------------------------------------------------------------------------------*/
//inline HWND GetTopHwnd ( HWND hWnd )
//{
//  HWND hwndPre = hWnd;
//
//  if ( !::IsWindow ( hWnd ) ) return ( HWND ) NULL;
//
//  while ( ::IsWindow ( hwndPre ) )
//  {
//    hWnd = hwndPre;
//    hwndPre = ( HWND ) ::GetWindowLong ( hWnd, GWL_HWNDPARENT );
//  }
//
//  return hWnd;
//}

/*----------------------------------------------------------------------------------
  hdc--窗口DC;
  bRatio--位图是否进行缩放处理(若进行，则cx代表缩放后的宽度，
                    cy代表缩放后的高度)
  x,y--代表目标hdc上绘画的位置起点坐标
----------------------------------------------------------------------------------*/
inline void DrawTransBmp ( HDC hdc, HBITMAP hBitmap, BOOL bRatio,
                           int x = 0, int y = 0, int cx = 0, int cy = 0, COLORREF clr = RGB ( 255, 255, 255 ) )
{
  ////////参数检测
  if ( ( !hdc ) || ( !hBitmap ) ) return;

  BITMAP bm;
  memset ( ( void* ) &bm, 0, sizeof ( BITMAP ) );
  ::GetObject ( hBitmap, sizeof ( BITMAP ), &bm );

  if ( ( !bRatio ) || ( bRatio && ( ( 0 == cx ) || ( 0 == cy ) ) ) )
  {
    cx = bm.bmWidth;
    cy = bm.bmHeight;
  }

  ////////
  HDC dcIm =::CreateCompatibleDC ( hdc );
  ::SetMapMode ( dcIm, ::GetMapMode ( hdc ) );
  HBITMAP hbIm = ( HBITMAP ) ::SelectObject ( dcIm, hBitmap );
  ////
  HDC dcImage =::CreateCompatibleDC ( hdc );
  ::SetMapMode ( dcImage, ::GetMapMode ( hdc ) );
  HBITMAP hBitmapImage =::CreateCompatibleBitmap ( hdc, cx, cy );
  HBITMAP hOldBitmapImage = ( HBITMAP ) ::SelectObject ( dcImage, hBitmapImage );
  ::StretchBlt ( dcImage, 0, 0, cx, cy, dcIm, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY );
  ////
  ::SelectObject ( dcIm, hbIm );
  ::DeleteDC ( dcIm );
  ////
  HDC dcAnd =::CreateCompatibleDC ( hdc );
  ::SetMapMode ( dcAnd, ::GetMapMode ( hdc ) );
  HBITMAP bitmapAnd =::CreateBitmap ( cx, cy, 1, 1, NULL );
  HBITMAP hOldBitmapAnd = ( HBITMAP ) ::SelectObject ( dcAnd, bitmapAnd );
  ::SetBkColor ( dcImage, clr );
  ::BitBlt ( dcAnd, 0, 0, cx, cy, dcImage, 0, 0, SRCCOPY );
  HDC dcXor =::CreateCompatibleDC ( hdc );
  ::SetMapMode ( dcXor, ::GetMapMode ( hdc ) );
  HBITMAP bitmapXor =::CreateCompatibleBitmap ( dcImage, cx, cy );
  HBITMAP hOldBitmapXor = ( HBITMAP ) ::SelectObject ( dcXor, bitmapXor );
  ::BitBlt ( dcXor, 0, 0, cx, cy, dcImage, 0, 0, SRCCOPY );
  ::BitBlt ( dcXor, 0, 0, cx, cy, dcAnd, 0, 0, 0x220326 );
  HDC dcTemp = CreateCompatibleDC ( hdc );
  ::SetMapMode ( dcTemp, ::GetMapMode ( hdc ) );
  HBITMAP bitmapTemp =::CreateCompatibleBitmap ( dcImage, cx, cy );
  HBITMAP hOldBitmapTemp = ( HBITMAP ) ::SelectObject ( dcTemp, bitmapTemp );
  ::BitBlt ( dcTemp, 0, 0, cx, cy, hdc, x, y, SRCCOPY );
  ::BitBlt ( dcTemp, 0, 0, cx, cy, dcAnd, 0, 0, SRCAND );
  ::BitBlt ( dcTemp, 0, 0, cx, cy, dcXor, 0, 0, SRCINVERT );
  ::BitBlt ( hdc, x, y, cx, cy, dcTemp, 0, 0, SRCCOPY );
  ////////
  ::DeleteObject ( ::SelectObject ( dcImage, hOldBitmapImage ) );
  ::DeleteDC ( dcImage );
  ::DeleteObject ( ::SelectObject ( dcAnd, hOldBitmapAnd ) );
  ::DeleteDC ( dcAnd );
  ::DeleteObject ( ::SelectObject ( dcXor, hOldBitmapXor ) );
  ::DeleteDC ( dcXor );
  ::DeleteObject ( ::SelectObject ( dcTemp, hOldBitmapTemp ) );
  ::DeleteDC ( dcTemp );
}

inline PBYTE CStringToIPAddress(CString strAddress)
{
	USES_CONVERSION;
	DWORD dwIP = inet_addr(W2A(strAddress));
	return (PBYTE)&dwIP;
}

/*----------------------------------------------------------------------------------
  获取2点间的距离
----------------------------------------------------------------------------------*/
inline double Points2Dist ( double x1, double y1, double x2, double y2 )
{
  double tmp1 = x1 - x2;
  double tmp2 = y1 - y2;
  double ret = tmp1 * tmp1 + tmp2 * tmp2;
  return ::sqrt ( ret );
}

/*----------------------------------------------------------------------------------
  获取两个值中的最小或最大值值
----------------------------------------------------------------------------------*/
template<class T>
T Min ( T& t1, T& t2 )
{
  return ( t1 < t2 ? t1 : t2 );
}
template<class T>
T Max ( T& t1, T& t2 )
{
  return ( t1 > t2 ? t1 : t2 );
}

/*----------------------------------------------------------------------------------
  GetBit(): 返回指定的值中的指定位的状态(1--返回TRUE；0--返回FALSE)
----------------------------------------------------------------------------------*/
template<class T>
BOOL GetBit ( const T tValue, const int nIndex )
{
  assert ( nIndex > -1 && nIndex < 32 );
  BOOL bRet ( FALSE );
  DWORD dwMask ( 0x01 );
  DWORD dwTmp ( 0 );

  switch ( sizeof ( T ) )
  {
    case 4:
    case 3:
    case 2:
    case 1:
      dwMask <<= nIndex;
      dwTmp = dwMask & tValue;

      if ( dwTmp != 0 ) bRet = TRUE;

      break;

    default:
      break;
  }

  ////////
  return bRet;
}

/*----------------------------------------------------------------------------------
  检测2指针是否重叠
----------------------------------------------------------------------------------*/
template<class T>
BOOL IsPtrEqual64 ( const T* pDest, const __int64* pSrc )
{
  BOOL bRet ( FALSE );
  T* pTmp = NULL;

  ////
  switch ( sizeof ( T ) )
  {
    case 8:
      if ( ( ( __int64* ) pDest ) == pSrc ) bRet = TRUE;

      break;

    case 4:
      pTmp = ( T* ) pSrc;

      if ( pDest == pTmp || pDest == ( pTmp + 1 ) ) bRet = TRUE;

      break;

    case 2:
      pTmp = ( T* ) pSrc;

      if ( pDest == pTmp || pDest == ( pTmp + 1 ) || pDest == ( pTmp + 2 ) || pDest == ( pTmp + 3 ) )
        bRet = TRUE;

      break;

    default:  //1
      pTmp = ( T* ) pSrc;

      if ( pDest == pTmp || pDest == ( pTmp + 1 ) || pDest == ( pTmp + 2 ) || pDest == ( pTmp + 3 ) ||
           pDest == ( pTmp + 4 ) || pDest == ( pTmp + 5 ) || pDest == ( pTmp + 6 ) || pDest == ( pTmp + 7 ) )
        bRet = TRUE;

      break;
  }

  //
  return bRet;
}

template<class T>
BOOL IsPtrEqual32 ( const T* pDest, const __int32* pSrc )
{
  BOOL bRet ( FALSE );
  T* pTmp = NULL;

  ////
  switch ( sizeof ( T ) )
  {
    case 8:
    case 4:
      if ( ( ( __int32* ) pDest ) == pSrc ) bRet = TRUE;

      break;

    case 2:
      pTmp = ( T* ) pSrc;

      if ( pDest == pTmp || pDest == ( pTmp + 1 ) ) bRet = TRUE;

      break;

    default:  //1
      pTmp = ( T* ) pSrc;

      if ( pDest == pTmp || pDest == ( pTmp + 1 ) || pDest == ( pTmp + 2 ) || pDest == ( pTmp + 3 ) )
        bRet = TRUE;

      break;
  }

  //
  return bRet;
}

/*----------------------------------------------------------------------------------
  弧度与角度互相转换函数
----------------------------------------------------------------------------------*/
inline double GetArcAssoValue ( double dbDest, BOOL bArcToAngle = TRUE )
{
  double dbRet = 0;

  if ( bArcToAngle ) //弧度转换成角度
  {
    dbRet = 180.0 / 3.141592653589793;
    dbRet *= dbDest;
  }

  else //角度转换成弧度
  {
    dbRet = 3.141592653589793 / 180.0;
    dbRet *= dbDest;
  }

  return dbRet;
}

/*----------------------------------------------------------------------------------
  检测指定文件是否存在
----------------------------------------------------------------------------------*/
inline BOOL vFileIsExist ( LPCTSTR lpszFullPathName )
{
  DWORD attr =::GetFileAttributes ( lpszFullPathName );

  if ( -1 == attr || ( FILE_ATTRIBUTE_DIRECTORY & attr ) == FILE_ATTRIBUTE_DIRECTORY )
    return FALSE;

  return TRUE;
}

/*----------------------------------------------------------------------------------
  检测指定目录是否存在
----------------------------------------------------------------------------------*/
inline BOOL vPathIsExist ( LPCTSTR lpszPath )
{
  DWORD attr =::GetFileAttributes ( lpszPath );

  if ( -1 == attr || ( FILE_ATTRIBUTE_DIRECTORY & attr ) != FILE_ATTRIBUTE_DIRECTORY )
    return FALSE;

  return TRUE;
}

/*----------------------------------------------------------------------------------
  创建指定文件
----------------------------------------------------------------------------------*/
inline BOOL vCreateFile ( LPCTSTR lpszFullPathName )
{
  if ( !vFileIsExist ( lpszFullPathName ) )
  {
    HANDLE hFile =::CreateFile ( lpszFullPathName, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ,
                                 NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_NORMAL,
                                 NULL );

    if ( INVALID_HANDLE_VALUE == hFile )
      return FALSE;

    ::CloseHandle ( hFile );
  }

  return TRUE;
}

//遍历文件夹中的文件
inline long FindDirFile(CString szDirPath,CStringArray &arr)
{
	long nCount = 0;
	BOOL bFind = FALSE;
	CFileFind finder;
	CString szDirPathTemp;
	szDirPathTemp=szDirPath+_T("\\*.*");
	bFind = finder.FindFile(szDirPathTemp);

	while(bFind)
	{
		bFind=finder.FindNextFile();

		if (finder.IsDots())
		{
			continue;
		}
		else if(finder.IsDirectory())
		{
			continue;
		}
		else
		{
			CString strTemp;
			strTemp.Format(_T("%s\\%s"),szDirPath,finder.GetFileName());
			arr.Add(strTemp);
			nCount++;
		}
	}
	return nCount;
}

inline void CreateAllDirectory(CString szPath)
{
	CString szPathTemp=szPath;

	long nPos=szPathTemp.ReverseFind('\\');

	if (nPos>-1)
	{
		szPathTemp=szPathTemp.Left(nPos);
		// 		TRACE(szPathTemp+"\n");
		CreateAllDirectory(szPathTemp);
		// 		TRACE(szPathTemp+"\n");

		DWORD dwRet=GetFileAttributes(szPathTemp) ;
		if (dwRet== FILE_ATTRIBUTE_DIRECTORY)

			return ;

		else
			// 		if (dwRet!= -1)

		{
			// 		if (DeleteFile(Dir))                              // delete the file with the same name
			bool bExist = false;
			char szFind[MAX_PATH];
			WIN32_FIND_DATA FindFileData;

			USES_CONVERSION;
			std::string s(W2A(szPathTemp));
			strcpy(szFind,s.c_str());

			//strcpy(szFind,szPathTemp);
			HANDLE hFind=::FindFirstFile((LPCWSTR)szFind,&FindFileData);
			if(INVALID_HANDLE_VALUE == hFind)
			{
				CreateDirectory(szPathTemp,NULL);
			}
			FindClose(hFind);
			// 			return true;
			// 			if (CreateDirectory(szPathTemp, NULL))
			//
			// 				return ;
			//
			// 			AfxMessageBox(_T("Can not create directory"), MB_OK);
		}
	}
	else
		return;
}
/*----------------------------------------------------------------------------------
  变参数的OutputDebugString()函数的封装，方便调、测试信息的输出
----------------------------------------------------------------------------------*/
inline void vInfoPrint ( const char* fmt, ... )
{
  char buf[8192];
  buf[0] = 0;
  va_list ap;
  va_start ( ap, fmt );
  vsprintf ( buf, fmt, ap );
  va_end ( ap );
  ::OutputDebugStringA ( buf );
}

/*----------------------------------------------------------------------------------
  字符串IP地址转换成4个BYTE
  192.168.1.2 ==>> cbHh=192; chHl=168; cbLh=1; cbLl=2;
----------------------------------------------------------------------------------*/
inline void vGetBytesIP ( LPCSTR lpcszIp, BYTE& cbHh, BYTE& cbHl, BYTE& cbLh, BYTE& cbLl )
{
  cbHh = cbHl = cbLh = cbLl = 0;

  if ( NULL == lpcszIp || 0 == *lpcszIp )
    return;

  char* pCh = ( char* ) ( LPCSTR ) lpcszIp;

  if ( pCh ) cbHh = ( BYTE ) ::strtol ( pCh, NULL, 10 );

  pCh =::strchr ( pCh, ( '.' ) );
  pCh++;

  if ( pCh ) cbHl = ( BYTE ) ::strtol ( pCh, NULL, 10 );

  pCh =::strchr ( pCh, ( '.' ) );
  pCh++;

  if ( pCh ) cbLh = ( BYTE ) ::strtol ( pCh, NULL, 10 );

  pCh =::strchr ( pCh, ( '.' ) );
  pCh++;

  if ( pCh ) cbLl = ( BYTE ) ::strtol ( pCh, NULL, 10 );
}

/*----------------------------------------------------------------------------------
  IP地址，4字节DWORD与4个BYTE的互相转换
----------------------------------------------------------------------------------*/
inline void vIPConverDWORD ( DWORD& dwIp, BYTE& cbHh, BYTE& cbHl,
                             BYTE& cbLh, BYTE& cbLl, BOOL bIpTo4Bytes = TRUE )
{
  if ( bIpTo4Bytes ) //DWORD==>>4Bytes
  {
    cbHh = HIBYTE ( HIWORD ( dwIp ) );
    cbHl = LOBYTE ( HIWORD ( dwIp ) );
    cbLh = HIBYTE ( LOWORD ( dwIp ) );
    cbLl = LOBYTE ( LOWORD ( dwIp ) );
  }

  else //4Bytes==>>DWORD
  {
    dwIp = MAKELONG ( MAKEWORD ( cbLl, cbLh ), MAKEWORD ( cbHl, cbHh ) );
  }
}

/*----------------------------------------------------------------------------------
  执行电脑关机操作
  dwMask —— Bit31~~Bit28：0001表示同时强制关闭所有进程
                0010表示同时强制关闭不响应的进程
        Bit3~~Bit0：0000表示关机及关闭电源
              0001表示关闭系统
              0010表示系统重起
              0011表示注销

----------------------------------------------------------------------------------*/
inline void vCloseComputer ( DWORD dwMask = 0x00 )
{
  ////针对Win2K及以上电脑做权限的特殊处理
  if ( ::GetWinVer() > 0 )
  {
    TOKEN_PRIVILEGES tp;
    memset ( &tp, 0, sizeof ( tp ) );
    HANDLE hToken = NULL;
    LUID luid;
    memset ( &luid, 0, sizeof ( luid ) );

    if ( !::OpenProcessToken ( GetCurrentProcess(),
                               TOKEN_ADJUST_PRIVILEGES,
                               &hToken ) )
    {
      return;
    }

    if ( !::LookupPrivilegeValue ( NULL, SE_SHUTDOWN_NAME, &luid ) )
    {
      return;
    }

    tp.PrivilegeCount = 1;
    tp.Privileges[0].Luid = luid;
    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    ::AdjustTokenPrivileges ( hToken, FALSE, &tp, 0, NULL, NULL );
  }

  ////执行关闭电脑的操作
  UINT uFlags = 0x00;

  //辅助标志
  switch ( 0x0F & ( dwMask >> 28 ) )
  {
    case 0x01:
      uFlags |= EWX_FORCE;
      break;

    case 0x02:
      if ( ::GetWinVer() > 0 )
      {
        uFlags |= 0x00000010;
      }

      break;
  }

  //执行标志
  switch ( 0x0F & dwMask )
  {
    case 0x01:
      uFlags |= EWX_SHUTDOWN;
      break; //表示关闭系统

    case 0x02:
      uFlags |= EWX_REBOOT;
      break; //表示系统重起

    case 0x03:
      uFlags |= EWX_LOGOFF;
      break; //表示注销

    default:
      uFlags |= EWX_POWEROFF;
      break; //表示关机及关闭电源
  }

  ::ExitWindowsEx ( uFlags, 0x00 );
}

/*----------------------------------------------------------------------------------
  获取指定的文件
  lpcszTitle：待显示的标题
  lpcszFilter：_T("Dll Files (*.dll)|*.dll|Ocx Files (*.ocx)|*.ocx|All Files (*.*)|*.*||")
  lpcszInitDir：初始路径
  lpcszDefExt：默认的文件扩展名(不包括".")：例：_T("txt")
  dwMaskStyle：bit0 —— 1表示显示已存在的文件
        bit1 —— 1表示显示隐藏文件
        bit2 —— 1表示创建新文件时进行提示操作
        bit3 —— 1表示路径必须存在
  返回值：若返回的值不为NULL；则函数调用者需释放内存(delete[])
----------------------------------------------------------------------------------*/
inline TCHAR* vGetFile ( LPCTSTR lpcszTitle, LPCTSTR lpcszFilter,
                         LPCTSTR lpcszInitDir,
                         HINSTANCE hInst, HWND hWndParent,
                         DWORD dwMaskStyle = 0x01, LPCTSTR lpcszDefExt = NULL )
{
  ////////
  TCHAR szDefaultFilter[64] = _T ( "All Files (*.*)|*.*||" );
  TCHAR szFilter[256] = _T ( "" );
  TCHAR szTitle[256] = _T ( "" );
  TCHAR szInitDir[256] = _T ( "" );
  TCHAR szReceive[1024] = _T ( "" );
  TCHAR szDefExt[16] = _T ( "" );
  TCHAR* pCh = NULL;
  ////
  OPENFILENAME of;
  memset ( &of, 0, sizeof ( OPENFILENAME ) );
  of.lStructSize = sizeof ( OPENFILENAME );
  of.Flags = OFN_LONGNAMES;

  if ( 0x01 & dwMaskStyle ) of.Flags |= OFN_FILEMUSTEXIST;

//  if( 0x02&dwMaskStyle ) of.Flags |= OFN_FORCESHOWHIDDEN;
  if ( 0x04 & dwMaskStyle ) of.Flags |= OFN_CREATEPROMPT;

  if ( 0x08 & dwMaskStyle ) of.Flags |= OFN_PATHMUSTEXIST;

  of.hwndOwner = hWndParent;
  of.hInstance = hInst;

  if ( NULL == lpcszFilter || 0 == *lpcszFilter )
    ::_tcscpy ( szFilter, szDefaultFilter );

  else
    ::_tcscpy ( szFilter, lpcszFilter );

  pCh = &szFilter[0];

  while ( ( pCh =::_tcschr ( pCh, TCHAR ( '|' ) ) ) != NULL ) * pCh++ = TCHAR ( '\0' );

  of.lpstrFilter = &szFilter[0];

  if ( NULL != lpcszTitle && 0 != *lpcszTitle )
    ::_tcscpy ( szTitle, lpcszTitle );

  of.lpstrTitle = &szTitle[0];

  if ( NULL == lpcszInitDir || 0 == *lpcszInitDir )
    ::GetCurrentDirectory ( 256, szInitDir );

  else
    ::_tcscpy ( szInitDir, lpcszInitDir );

  of.lpstrInitialDir = &szInitDir[0];

  if ( NULL != lpcszDefExt && 0 != *lpcszDefExt )
  {
    if ( ::_tcslen ( lpcszDefExt ) > 3 ) ::_tcsncpy ( szDefExt, lpcszDefExt, 3 );

    else ::_tcscpy ( szDefExt, lpcszDefExt );
  }

  of.lpstrDefExt = &szDefExt[0];
  of.lpstrFile = &szReceive[0];
  of.nMaxFile = 1024;

  if ( ::GetOpenFileName ( &of ) )
  {
    int len =(int)::_tcslen ( of.lpstrFile );
    pCh = new TCHAR[len + 1];

    if ( NULL != pCh )
      ::_tcscpy ( pCh, of.lpstrFile );

    return pCh;
  }

  return NULL;
}

/*----------------------------------------------------------------------------------
  获取当前程序所在的路径
----------------------------------------------------------------------------------*/
inline BOOL GetLocalPath ( LPTSTR lpszRetBuff, long nBuffSize, BOOL bCorrect = TRUE )
{
  int len;
  TCHAR *pCh;
  TCHAR* pszPath = new TCHAR[1024];
  ////
  ::GetModuleFileName ( NULL, pszPath, 1024 );
  pCh =::_tcsrchr ( pszPath, TCHAR ( '\\' ) );

  if ( bCorrect )
  {
    if ( NULL == pCh )
    {
      len =(int)::_tcslen ( pszPath );
      pszPath[len] = TCHAR ( '\\' );
      len++;
      pszPath[len] = 0;
    }

    else
    {
      pCh++;
      *pCh = 0;
    }
  }

  else
  {
    if ( NULL != pCh )
    {
      *pCh = 0;
    }
  }

  ////
  len =(int)::_tcslen ( pszPath );

  if ( NULL == lpszRetBuff || len < 1 || nBuffSize < ( len + 1 ) )
  {
    if ( NULL != lpszRetBuff )
      lpszRetBuff[0] = 0;

    delete[] pszPath;
    return FALSE;
  }

  else
  {
    memcpy ( lpszRetBuff, pszPath, sizeof ( TCHAR ) * ( len + 1 ) );
    delete[] pszPath;
    return TRUE;
  }
}
//
inline BOOL IsDigital ( CString str )
{
  TCHAR szBuff;

  if ( str.GetLength() <= 0 )
    return FALSE;

  for ( int i = 0; i < str.GetLength(); i++ )
  {
    szBuff = str[i];

    if ( szBuff == 46 || szBuff == 45 ) //"-","."符号判断
      continue;

    if ( !::isdigit ( szBuff ) ) //数字判断
    {
      return FALSE;
    }
  }

  return TRUE;
}

inline int AnsiToUnicode( char* inBuf, unsigned int iInLen, wchar_t* outBuf, unsigned int iOutLen )
{
	iInLen = min(iInLen,strlen(inBuf));
	int wclen = ::MultiByteToWideChar( CP_ACP, NULL, inBuf, iInLen, NULL, 0 );
	if( (int)iOutLen < wclen )
		return wclen;
	wclen = ::MultiByteToWideChar( CP_ACP, NULL, inBuf, iInLen, outBuf, iOutLen );
	return wclen;
}

inline int UnicodeToAnsi( wchar_t* inBuf, unsigned int iInLen, char* outBuf, unsigned int iOutLen )
{
	iInLen = min(iInLen,wcslen(inBuf));
	int ansilen = ::WideCharToMultiByte( CP_ACP, NULL, inBuf, iInLen, NULL, 0, NULL, NULL );
	if( (int)iOutLen < ansilen )
		return ansilen;
	ansilen = ::WideCharToMultiByte( CP_ACP, NULL, inBuf, iInLen, outBuf, iOutLen, NULL, NULL );
	return ansilen;
}
/*----------------------------------------------------------------------------------
  vGetUnicodeFromMultiByte()：从MultiByte转换成Unicode
  返回值：0失败，成功时返回unicode字符串字符个数
      成功时，外部需释放*ppszUnicodeRet内存
----------------------------------------------------------------------------------*/
inline int vGetUnicodeFromMultiByte ( const char* pszMultiByte, wchar_t** ppszUnicodeRet, UINT nCodePage = -1 )
{
  int nRlt = 0;

  if ( NULL != ppszUnicodeRet )
  {
    *ppszUnicodeRet = NULL;
  }

  if ( NULL != pszMultiByte && 0 != *pszMultiByte && NULL != ppszUnicodeRet )
  {
    if ( -1 == nCodePage ) //本地代码页
    {
      nCodePage = ::GetACP();
    }

    int nSize = ::MultiByteToWideChar ( nCodePage, 0, pszMultiByte, -1, NULL, 0 );
    *ppszUnicodeRet = new wchar_t[nSize + 1];
    nRlt = ::MultiByteToWideChar ( nCodePage, 0, pszMultiByte, -1, *ppszUnicodeRet, nSize );

    if ( 0 == nRlt )
    {
      delete[] *ppszUnicodeRet;
      *ppszUnicodeRet = NULL;
    }
  }

  return nRlt;
}

/*----------------------------------------------------------------------------------
  vGetMultiByteFromUnicode()：从Unicode转换成MultiByte
  返回值：0失败，成功时返回MultiByte字符串字符个数
      成功时，外部需释放*ppszMultiByteRet内存
----------------------------------------------------------------------------------*/
inline int vGetMultiByteFromUnicode ( const wchar_t* pszUnicode, char** ppszMultiByteRet, UINT nCodePage = -1 )
{
  int nRlt = 0;

  if ( NULL != ppszMultiByteRet )
  {
    *ppszMultiByteRet = NULL;
  }

  if ( NULL != pszUnicode && 0x00 != *pszUnicode && NULL != ppszMultiByteRet )
  {
    if ( -1 == nCodePage ) //本地代码页
    {
      nCodePage = ::GetACP();
    }

    int nSize = ::WideCharToMultiByte ( nCodePage, 0, pszUnicode, -1, NULL, 0, NULL, NULL );
    *ppszMultiByteRet = new char[nSize + 1];
    nRlt = ::WideCharToMultiByte ( nCodePage, 0, pszUnicode, -1, *ppszMultiByteRet, nSize, NULL, NULL );

    if ( 0 == nRlt )
    {
      delete[] *ppszMultiByteRet;
      *ppszMultiByteRet = NULL;
    }
  }

  return nRlt;
}

inline double liabs ( double a )
{
  if ( a < 0 )
  {
    a = 0 - a;
  }

  return a;
}

inline CString CircleFitByPratt ( double x[], double y[], int n, double* ArcX, double* ArcY, double* ArcRadius )
{
  int i = 0;
  double tmpx = 0;
  double tmpy = 0;
  double Xi = 0, Yi = 0, Zi = 0;

  for ( i = 0; i < n; i++ )
  {
    tmpx += x[i];
    tmpy += y[i];
  }

  tmpx = tmpx / n;
  tmpy = tmpy / n;

  double centroidx = tmpx;
  double centroidy = tmpy;
  double Mxx = 0, Myy = 0, Mxy = 0, Mxz = 0, Myz = 0, Mzz = 0;

  for ( i = 0; i < n ; i++ )
  {
    Xi = x[i] - centroidx;
    Yi = y[i] - centroidy;
    Zi = Xi * Xi + Yi * Yi;
    Mxy = Mxy + Xi * Yi;
    Mxx = Mxx + Xi * Xi;
    Myy = Myy + Yi * Yi;
    Mxz = Mxz + Xi * Zi;
    Myz = Myz + Yi * Zi;
    Mzz = Mzz + Zi * Zi;
  }

  Mxx = Mxx / n;
  Myy = Myy / n;
  Mxy = Mxy / n;
  Mxz = Mxz / n;
  Myz = Myz / n;
  Mzz = Mzz / n;
  double  Mz = Mxx + Myy;
  double  Cov_xy = Mxx * Myy - Mxy * Mxy;
  double  Mxz2 = Mxz * Mxz;
  double  Myz2 = Myz * Myz;

  double  A2 = 4 * Cov_xy - 3 * Mz * Mz - Mzz;
  double  A1 = Mzz * Mz + 4 * Cov_xy * Mz - Mxz2 - Myz2 - Mz * Mz * Mz;
  double  A0 = Mxz2 * Myy + Myz2 * Mxx - Mzz * Cov_xy - 2 * Mxz * Myz * Mxy + Mz * Mz * Cov_xy;
  double  A22 = A2 + A2;
  double  epsilon = 1e-12;
  double  ynew = 1e+20;
  double  IterMax = 20;
  double  xnew = 0;

  for ( i = 0; i < IterMax; i++ )
  {
    double  yold = ynew;
    ynew = A0 + xnew * ( A1 + xnew * ( A2 + 4.*xnew * xnew ) );

    if ( liabs ( ynew ) > liabs ( yold ) )
    {
      //AfxMessageBox(_T("Newton-Pratt goes wrong direction: |ynew| > |yold|"));
      ::OutputDebugString ( _T ( "Newton-Pratt goes wrong direction: |ynew| > |yold|" ) ) ;
      xnew = 0;
      break;
    }

    double    Dy = A1 + xnew * ( A22 + 16 * xnew * xnew );
    double    xold = xnew;
    xnew = xold - ynew / Dy;

    if ( liabs ( ( xnew - xold ) / xnew ) < epsilon )
      break;

    if ( i >= IterMax )
    {
      //AfxMessageBox(_T("Newton-Pratt will not converge"));
      ::OutputDebugString ( _T ( "Newton-Pratt will not converge" ) ) ;
      xnew = 0;
    }

    if ( xnew < 0 )
    {
      CString tmp ;
      tmp.Format ( _T ( "Newton-Pratt negative root:  x=%f\n" ), xnew );
      ::OutputDebugString ( tmp ) ;
      //AfxMessageBox(tmp);
      xnew = 0;
    }

    double  DET = xnew * xnew - xnew * Mz + Cov_xy;
    double  Centerx = ( Mxz * ( Myy - xnew ) - Myz * Mxy ) / DET / 2;
    double  Centery = ( Myz * ( Mxx - xnew ) - Mxz * Mxy ) / DET / 2;
    double  Parx = Centerx + centroidx;
    double  Pary = Centery + centroidy;
    double  Parz = sqrt ( Centerx * Centerx + Centery * Centery + Mz );

    CString tmp ;
    tmp.Format ( _T ( "%2d个点:%f, %f, %f\n" ), n, Parx, Pary, Parz );
    ::OutputDebugString ( tmp ) ;
    //AfxMessageBox(tmp) ;
    *ArcX = Parx ;
    *ArcY = Pary ;
    *ArcRadius = Parz ;
    return tmp;
  }
}

inline CString CircleFitByTaubin ( double x[], double y[], int n )
{
  int i = 0;
  double tmpx = 0;
  double tmpy = 0;
  double Xi = 0, Yi = 0, Zi = 0;

  for ( i = 0; i < n; i++ )
  {
    tmpx += x[i];
    tmpy += y[i];
  }

  tmpx = tmpx / n;
  tmpy = tmpy / n;

  double centroidx = tmpx;
  double centroidy = tmpy;
  double Mxx = 0, Myy = 0, Mxy = 0, Mxz = 0, Myz = 0, Mzz = 0;

  for ( i = 0; i < n ; i++ )
  {
    Xi = x[i] - centroidx;
    Yi = y[i] - centroidy;
    Zi = Xi * Xi + Yi * Yi;
    Mxy = Mxy + Xi * Yi;
    Mxx = Mxx + Xi * Xi;
    Myy = Myy + Yi * Yi;
    Mxz = Mxz + Xi * Zi;
    Myz = Myz + Yi * Zi;
    Mzz = Mzz + Zi * Zi;
  }

  Mxx = Mxx / n;
  Myy = Myy / n;
  Mxy = Mxy / n;
  Mxz = Mxz / n;
  Myz = Myz / n;
  Mzz = Mzz / n;

  double  Mz = Mxx + Myy;
  double  Cov_xy = Mxx * Myy - Mxy * Mxy;
  double  A3 = 4 * Mz;
  double  A2 = -3 * Mz * Mz - Mzz;
  double  A1 = Mzz * Mz + 4 * Cov_xy * Mz - Mxz * Mxz - Myz * Myz - Mz * Mz * Mz;
  double  A0 = Mxz * Mxz * Myy + Myz * Myz * Mxx - Mzz * Cov_xy - 2 * Mxz * Myz * Mxy + Mz * Mz * Cov_xy;
  double  A22 = A2 + A2;
  double  A33 = A3 + A3 + A3;
  double  xnew = 0;
  double  ynew = 1e+20;
  double  epsilon = 1e-12;
  double  IterMax = 20;

  for ( i = 0; i < IterMax; i++ )
  {
    double  yold = ynew;
    ynew = A0 + xnew * ( A1 + xnew * ( A2 + xnew * A3 ) );

    if ( liabs ( ynew ) > liabs ( yold ) )
    {
      AfxMessageBox ( _T ( "Newton-Taubin goes wrong direction: |ynew| > |yold|" ) );
      xnew = 0;
      break;
    }

    double    Dy = A1 + xnew * ( A22 + xnew * A33 );
    double    xold = xnew;
    xnew = xold - ynew / Dy;

    if ( liabs ( ( xnew - xold ) / xnew ) < epsilon )
      break;

    if ( i >= IterMax )
    {
      AfxMessageBox ( _T ( "Newton-Taubin will not converge" ) );
      xnew = 0;
    }

    if ( xnew < 0 )
    {
      CString tmp ;
      tmp.Format ( _T ( "Newton-Taubin negative root:  x=%f\n" ), xnew );
      AfxMessageBox ( tmp );
      xnew = 0;
    }
  }

  double  DET = xnew * xnew - xnew * Mz + Cov_xy;
  double  Centerx = ( Mxz * ( Myy - xnew ) - Myz * Mxy ) / DET / 2;
  double  Centery = ( Myz * ( Mxx - xnew ) - Mxz * Mxy ) / DET / 2;
  double  Parx = Centerx + centroidx;
  double  Pary = Centery + centroidy;
  double  Parz = sqrt ( Centerx * Centerx + Centery * Centery + Mz );

  CString tmp ;
  tmp.Format ( _T ( "%2d个点:%f, %f, %f\n" ), n, Parx, Pary, Parz );
  AfxMessageBox ( tmp ) ;
  return tmp;
}

inline CString GetStringByVal ( int nGray )
{
  CString strText ;
  strText.Format ( _T("%d"), nGray );

  if ( strText.GetLength() == 1 )
  {
    strText = _T("00") + strText + _T("T") ;
  }

  else if ( strText.GetLength() == 2 )
  {
    strText = _T("0") + strText + _T("T");
  }

  else
  {
    strText = strText + _T("T");
  }

  return strText ;
}

//函 数 名：CharToHex()
//功能描述：把ASCII字符转换为16进制
//函数说明：
//调用函数：
//全局变量：
//输    入：ASCII字符
//返    回：16进制
/////////////////////////////////////////////////////////////////////
inline unsigned char CharToHex(unsigned char bHex){
	if((bHex>=0)&&(bHex<=9))
		bHex += 0x30;
	else if((bHex>=10)&&(bHex<=15))//大写字母
		bHex += 0x37;
	else bHex = 0xff;
	return bHex;
}
/////////////////////////////////////////////////////////////////////
//函 数 名：HexToChar()
//功能描述：把16进制转换为ASCII字符
//函数说明：
//调用函数：
//全局变量：
//输    入：16进制
//返    回：ASCII字符
/////////////////////////////////////////////////////////////////////
inline unsigned char HexToChar(unsigned char bChar){
	if((bChar>=0x30)&&(bChar<=0x39))
		bChar -= 0x30;
	else if((bChar>=0x41)&&(bChar<=0x46))//大写字母
		bChar -= 0x37;
	else if((bChar>=0x61)&&(bChar<=0x66))//小写字母
		bChar -= 0x57;
	else bChar = 0xff;
	return bChar;
}

inline CString ConvertCStringtoHex(CString Data)
{
	//CString转换成char[]
	wchar_t* a=(wchar_t*)Data.GetBuffer( Data.GetLength() );
	int nLen = WideCharToMultiByte( CP_ACP, 0, a, -1, NULL, 0, NULL, NULL );
	if (nLen == 0)
	{
		return NULL;
	}
	char* pResult = new char[nLen];
	char tagChar[2048];
	WideCharToMultiByte( CP_ACP, 0, a, -1, pResult, nLen, NULL, NULL );
	strncpy( tagChar,pResult , sizeof(tagChar));
	//转换成hex
	CString sResult=_T("");
	int nLoop=0;
	while(tagChar[nLoop]!='\0')
	{
		static const char *hex="0123456789ABCDEF";
		if(tagChar[nLoop]<127&&tagChar[nLoop]>0)
		{
			sResult += '0';
			sResult += '0';
			unsigned char chHexA = hex[((unsigned char)(tagChar[nLoop]) >> 4) & 0x0f];
			unsigned char chHexB = hex[(unsigned char)(tagChar[nLoop]) & 0x0f];
			sResult += (char)chHexA;
			sResult += (char)chHexB;
			nLoop++;
		}
		else
		{
			unsigned char chHexA = hex[((unsigned char)(tagChar[nLoop]) >> 4) & 0x0f];
			unsigned char chHexB = hex[(unsigned char)(tagChar[nLoop]) & 0x0f];
			sResult += (char)chHexA;
			sResult += (char)chHexB;

			if(tagChar[++nLoop]=='\0') break;
			sResult+= hex[((unsigned char)(tagChar[nLoop]) >> 4) & 0x0f];
			sResult+=hex[(unsigned char)(tagChar[nLoop]) & 0x0f];
			nLoop++;
		}
	}
	return sResult;
}

inline CString ConvertHextoCString(CString hex)
{
	CString result=_T("");

	char temp[3];
	int i=0;
	if(hex.GetLength()%4!=0)
	{
		return _T("");
	}
	int lenhex=hex.GetLength();
	while(i<lenhex)
	{
		long h4 = (long)CharToHex((long)hex.GetAt(i));
		long h3 = (long)CharToHex((long)hex.GetAt(i+1));

		long h2 = (long)CharToHex((long)hex.GetAt(i+2));
		long h1 = (long)CharToHex((long)hex.GetAt(i+3));

		long t1=h4*16+h3;
		long t2=h2*16+h1;
		if(t1==0)
		{
			temp[0]=t2;
			temp[1]='\0';
		}
		else
		{
			temp[0]=t1;
			temp[1]=t2;
			temp[2]='\0';
		}
		i+=4;
		result+=temp;
	}
	return result;
}

inline long CharToHex(long ch)
{
	long la = (ch>=(long) 'A' ? (ch -(long) 'A' + 10) : (ch -(long) '0'));
	return la;
}

inline void GetExepath ( TCHAR *pPath ) //获取执行目录
{
  TCHAR exePath[MAX_PATH];
  ::memset ( exePath, 0, sizeof ( TCHAR ) *MAX_PATH );
  ::GetModuleFileName ( NULL, exePath, MAX_PATH );
  TCHAR* pEnd = _tcsrchr ( exePath, _T ( '\\' ) );
  * ( pEnd + 1 ) = NULL;

  if ( pPath != NULL )
  {
    _tcscpy ( pPath, exePath );
  }
}

inline CString GetExepath()
{
	TCHAR chPath[MAX_PATH];
	GetExepath(chPath);

	return (CString)chPath;
}

inline void DoEvents()
{
  MSG msg;

  if ( PeekMessage ( &msg, NULL, 0, 0, PM_NOREMOVE ) )
  {
    GetMessage ( &msg, NULL, 0, 0 );

    if ( msg.message == WM_QUIT )
    {
      return;
    }

    TranslateMessage ( &msg );
    DispatchMessage ( &msg );
  }
}

inline void Delay ( DWORD dwTime )
{
  if ( 0 == dwTime )
  {
    return;
  }

  long start = GetTickCount();

  while ( TRUE )
  {
    DoEvents();

    if ( ( GetTickCount() - start ) >= dwTime )
      break;
  }
}

inline CString GetBrowseFolder ( HWND pParent, CString wndTitle )
{
  char        szDir[MAX_PATH] = {0};
  BROWSEINFO    bi;
  ITEMIDLIST    *pidl = NULL;

  bi.hwndOwner = pParent;
  bi.pidlRoot = NULL;
  bi.pszDisplayName = (LPWSTR)szDir;
  bi.lpszTitle = wndTitle;
  bi.ulFlags = BIF_RETURNONLYFSDIRS;
  bi.lpfn = NULL;
  bi.lParam = 0;
  bi.iImage = 0;

  pidl = SHBrowseForFolder ( &bi );

  if ( NULL == pidl )
    return _T("");

  if ( !SHGetPathFromIDList ( pidl, (LPWSTR)szDir ) )
    return _T("");

  return CString ( szDir );
}

inline BOOL DeleteFolder ( char *pStrFolder )
{
	USES_CONVERSION;

	if ( ( NULL == pStrFolder ) )
		return FALSE;

	/*检查输入目录是否是合法目录*/
	if ( _access ( pStrFolder, 0 ) != 0 )
	{
		//m_strLoadText.LoadString(IDS_ORDER_IS_NOT_EXSIT);
		//AfxMessageBox(m_strLoadText,MB_OK|MB_ICONERROR);
		return FALSE;
	}

	/*创建源目录中查找文件的通配符*/
	CString strWildcard ( pStrFolder );

	if ( strWildcard.Right ( 1 ) != _T ( '\\' ) )
	{
		strWildcard += _T ( "\\" );
	}

	strWildcard += _T ( "*.*" );
	/*打开文件查找，查看源目录中是否存在匹配的文件*/
	/*调用FindFile后，必须调用FindNextFile才能获得查找文件的信息*/
	CFileFind finder;
	BOOL bWorking = finder.FindFile ( strWildcard );

	while ( bWorking )
	{
		/*查找下一个文件*/
		bWorking = finder.FindNextFile();

		/*跳过当前目录“.”和上一级目录“..”*/
		if ( finder.IsDots() )
		{
			continue;
		}

		/*得到当前目录的子文件的路径*/
		CString strSubFile = finder.GetFilePath();

		/*判断当前文件是否是目录,*/
		/*如果是目录，递归调用删除目录,*/
		/*否则，直接删除文件*/
		USES_CONVERSION;
		if ( finder.IsDirectory() )
		{
			if ( !DeleteFolder ( /*( LPSTR )*/ /*( LPCSTR )*/ T2A( strSubFile ) ) )
			{
				finder.Close();
				return FALSE;
			}
		}

		else
		{
			if ( !DeleteFileA((LPCSTR)T2A(strSubFile) ) )
			{
				finder.Close();
				return FALSE;
			}
		}
	} /*while (bWorking)*/

	/*关闭文件查找*/
	finder.Close();
	/*删除空目录*/
	return RemoveDirectory ( A2T ( pStrFolder ) );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void SaveLog(CString csLog )
{
	if(csLog.IsEmpty())
	{
		return;
	}
	CString strFile = _T("D:\\LogFile");
	if(!vPathIsExist(strFile))
	{
		if(!::CreateDirectory(strFile,NULL))
		{
			strFile = _T("");
		}
	}
	SYSTEMTIME tm;
	memset(&tm,0,sizeof(tm));
	::GetLocalTime(&tm);
	CString strTextFile ;
	CString strTime ;
	DWORD dwYear,dwMonth,dwDay ;
	DWORD dwHour,dwMinute ,dwSecond;
	dwYear = tm.wYear ;
	dwMonth = tm.wMonth ;
	dwDay = tm.wDay ;
	dwHour = tm.wHour ;
	dwMinute = tm.wMinute ;
	dwSecond = tm.wSecond ;
	strTextFile.Format(_T("%d-%d-%d"),dwYear,dwMonth,dwDay) ;
	strTime.Format(_T("%d(时):%d(分):%d(秒)----"),dwHour,dwMinute,dwSecond) ;
	////////////写数据
	char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
	setlocale( LC_CTYPE, ("chs"));
	try
	{
		CStdioFile f;
		CString strPath ;
		strPath = strFile+_T("\\")+strTextFile + _T(".txt") ;
		if(!f.Open(strPath,CFile::modeRead|CFile::modeWrite))
		{
			if(!f.Open(strPath,CFile::modeCreate|CFile::modeWrite))
			{
				setlocale( LC_CTYPE, old_locale );
				free( old_locale );//还原区域设定
				return ;
			}
		}
		f.SeekToEnd();
		CString csContent = strTime + csLog ;
		csContent+="\r\n";
		f.WriteString(csContent);
		f.Close();
		setlocale( LC_CTYPE, old_locale );
		free( old_locale );//还原区域设定
	}
	catch( CFileException* e )
	{
		e;
	}
	return  ;
}

inline time_t FileTimeToTime_t(const FILETIME &ft)
{
	ULARGE_INTEGER ui;
	ui.LowPart = ft.dwLowDateTime;
	ui.HighPart = ft.dwHighDateTime;
	return ((LONGLONG)(ui.QuadPart - 116444736000000000) / 10000000);
}

inline int GetDiffSeconds(const SYSTEMTIME &t1, const SYSTEMTIME &t2)
{
	FILETIME fTime1 = { 0, 0 };
	FILETIME fTime2 = { 0, 0 };
	SystemTimeToFileTime(&t1, &fTime1);
	SystemTimeToFileTime(&t2, &fTime2);

	time_t tt1 = FileTimeToTime_t(fTime1);
	time_t tt2 = FileTimeToTime_t(fTime2);

	return (int)(tt2 - tt1);
}

inline int GetDiffDays(const SYSTEMTIME &t1, const SYSTEMTIME &t2)
{
	int diffSeconds = GetDiffSeconds(t1, t2);

	return abs(diffSeconds) / (24 * 3600);
}

////////////////////////////////////////////////////////////////////////////////////
#endif
