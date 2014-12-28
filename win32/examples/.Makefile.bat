
@REM @echo off
@set tcc_include=-I..\libtcc -I..\include
@set tcc_lib= -L..\lib  -ltcc1 ..\libtcc.dll
@set cc=..\tcc
@ set tcc_flags=-g  -B.\

@set out=..\%~n1.exe
@set testdir=scripts
@set testcmd=..\%out% tccstate.c -I..\..\libtcc

%cc% -o %out%  %~n1.c %tcc_flags%  %tcc_include%  %tcc_lib%
@IF %ERRORLEVEL% EQU 1 GOTO error
@rem set CONFIG_TCCDIR=..
@cd %testdir%
%testcmd%
:error
pause
exit

