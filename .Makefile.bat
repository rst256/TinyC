@CD win32
@ECHO --------------------- Build TinyC ---------------------
@SET /p VERSION= < ..\VERSION
@ECHO>..\config.h #define TCC_VERSION "%VERSION%"

@if _%PROCESSOR_ARCHITEW6432%_==_AMD64_ GOTO x86_64
@if _%PROCESSOR_ARCHITECTURE%_==_AMD64_ GOTO x86_64

@SET target=-DTCC_TARGET_PE -DTCC_TARGET_I386
@SET CC=mingw32-gcc 
@SET P=32
@GOTO ut_tools

:x86_64
@SET target=-DTCC_TARGET_PE -DTCC_TARGET_X86_64
@REM mingw 64 has an ICE with -Os
@SET CC=x86_64-pc-mingw32-gcc -O0 -s -fno-strict-aliasing
@SET P=64
@GOTO ut_tools

:ut_tools
@IF NOT EXIST include\nul mkdir include
@copy ..\include\ut*.h include
@IF %ERRORLEVEL% EQU 1 GOTO error

:tools
%CC% %target% tools/tiny_impdef.c -o tiny_impdef.exe 
@IF %ERRORLEVEL% EQU 1 GOTO error
%CC% %target% tools/tiny_libmaker.c -o tiny_libmaker.exe  
@IF %ERRORLEVEL% EQU 1 GOTO error

:libtcc
@IF NOT EXIST libtcc\nul mkdir libtcc
@copy ..\libtcc.h libtcc\libtcc.h
%CC% %target% -shared  -DONE_SOURCE    ../libtcc.c -o libtcc.dll -Wl,-out-implib,libtcc/libtcc.a
@IF %ERRORLEVEL% EQU 1 GOTO error
tiny_impdef libtcc.dll -o libtcc/libtcc.def
@IF %ERRORLEVEL% EQU 1 GOTO error

:tcc
%CC% %target% ../tcc.c -o tcc.exe -ltcc -Llibtcc
@IF %ERRORLEVEL% EQU 1 GOTO error

:copy_std_includes
@copy ..\include\*.h include
@IF %ERRORLEVEL% EQU 1 GOTO error

:libtcc1.a
.\tcc %target% -c ../lib/libtcc1.c
.\tcc %target% -c lib/crt1.c
.\tcc %target% -c lib/wincrt1.c
.\tcc %target% -c lib/dllcrt1.c
.\tcc %target% -c lib/dllmain.c
.\tcc %target% -c lib/chkstk.S
@IF %ERRORLEVEL% EQU 1 GOTO error
@GOTO lib%P%

:lib32
.\tcc %target% -c ../lib/alloca86.S
.\tcc %target% -c ../lib/alloca86-bt.S
.\tcc %target% -c ../lib/bcheck.c
tiny_libmaker lib/libtcc1.a libtcc1.o alloca86.o alloca86-bt.o crt1.o wincrt1.o dllcrt1.o dllmain.o chkstk.o bcheck.o
@IF %ERRORLEVEL% EQU 1 GOTO error
@GOTO the_end

:lib64
.\tcc %target% -c ../lib/alloca86_64.S
tiny_libmaker lib/libtcc1.a libtcc1.o alloca86_64.o crt1.o wincrt1.o dllcrt1.o dllmain.o chkstk.o
@IF %ERRORLEVEL% EQU 1 GOTO error

:the_end
@del *.o

@ECHO ------------------- Build TestApp -------------------
tcc.exe examples\testtt.c -o examples\testtt.exe
@IF %ERRORLEVEL% EQU 1 GOTO error
@ECHO -------------------- Run TestApp --------------------
examples\testtt.exe
@IF %ERRORLEVEL% EQU 1 GOTO error
@GOTO end
:error
@ECHO ------------------ Build %~n1 fail! ------------------
:end
@pause