cd %1
c:
REM echo off
set tcc_include=-Ilibtcc -I%2\include
set tcc_lib= -L%2\lib -ltcc1 libtcc.dll
set lua_include=-I%LUA_DEV%\include
set lua_lib=-L%LUA_DEV% -llua5.1
set tcc_flags=-g -shared -B.\

tcc   %1\luatcc.c %tcc_flags%  %lua_include% %tcc_include% %lua_lib% %tcc_lib%
IF %ERRORLEVEL% EQU 1 GOTO error
%LUA_DEV%\lua.exe %1\test.lua
IF %ERRORLEVEL% EQU 1 GOTO error
@echo Ok.
exit
:error
@echo Failed. 
pause
exit

