@rem run c interpreter
tcc %1 -E
@set cint=..\..\introspect.exe
@rem %cint% %~n1.c
@%cint% %1  -I..\..\libtcc -E
@echo exit code %ERRORLEVEL% 
pause
exit

