@rem run c interpreter

@set cint=..\..\introspect.exe
@rem %cint% %~n1.c
@%cint% %1  -I..\..\libtcc
@echo exit code %ERRORLEVEL% 
pause
exit

