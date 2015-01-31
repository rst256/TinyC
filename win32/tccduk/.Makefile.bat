@REM @echo off
@ rem set tcc_include=-I..\libtcc -I..\include
@set tcc_include=-I..\include\winapi  -I..\include ..\libtcc.dll
@ set tcc_lib= -L..\lib  -ltcc1 ..\libtcc.dll
@set cc=..\tcc
@set tcc_flags=-g  -B.\ 
@rem set flags_extras= -DCONFIG_TCC_PP_EXTRAS -DCONFIG_TCC_STATE_EXTRAS

@set out=..\%~n1.exe

%cc% %flags_extras% -o %out%  %~n1.c %tcc_flags%  %tcc_include%  %tcc_lib%
@IF %ERRORLEVEL% EQU 1 GOTO error
%out%
pause
exit
:error
@echo "FAIL!"
pause


