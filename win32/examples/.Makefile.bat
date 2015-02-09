..\tcc -g  -WAll %~n1.c 
@IF %ERRORLEVEL% EQU 1 GOTO error
%~n1.exe
@GOTO end
:error
@ECHO Build %~n1 fail!
:end
@pause