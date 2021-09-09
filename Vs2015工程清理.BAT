@echo off
echo ============================================
echo = 【名称：】工程清理.BAT                                           =
echo = 【作者：】王律                                                    =
echo = 【日期：】2020-07-09                                              =
echo = 【版本：】Ver1.0                                                      =
                    =
echo ============================================
pause
echo 正在清理中，请稍等......
echo===========================================================================
 
FOR /R %dir% %%d IN (*.pdb vc60.pdb vc90.pdb *.exp *.obj *.pch *.idb *.ncb *.opt *.plg *.sbr *.ilk *.aps *.sdf *.temp *.dcu *.bsc *.ipch *.VC.db) DO DEL /f /s /q "%%d" 2>nul

FOR /R . %%d IN (.) DO rd /s /q "%%d\Tmp" 2>nul

FOR /R . %%d IN (.) DO rd /s /q "%%d\tmp" 2>nul

FOR /R . %%d IN (.) DO rd /s /q "%%d\tmp" 2>nul

FOR /R . %%d IN (.) DO rd /s /q "%%d\tmp" 2>nul

FOR /R . %%d IN (.) DO rd /s /q "%%d\ipch" 2>nul
echo===========================================================================
 
ECHO 文件清理完毕！本程序将在5秒后退出！现在进入倒计时......... 
@echo off 
echo WScript.Sleep 300 > %temp%.\tmp
$.vbsset/ai=20:Timeoutifsetlocalset/ai=echo倒计时……cscript//nologo
$.vbs 
goto Timeout 
goto End 
:Next 
cls & 
echo.