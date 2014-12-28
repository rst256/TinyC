@rem ----------------------------------------------------
@rem batch file to build tcc using mingw gcc
@rem ----------------------------------------------------
@set install_to=c:\lua\5.1\clibs\luatcc
@set /p VERSION= < ..\VERSION
@echo>..\config.h #define TCC_VERSION "%VERSION%"

@if _%PROCESSOR_ARCHITEW6432%_==_AMD64_ goto x86_64
@if _%PROCESSOR_ARCHITECTURE%_==_AMD64_ goto x86_64

@set target=-DTCC_TARGET_PE -DTCC_TARGET_I386
@set CC=mingw32-gcc -Os -s -fno-strict-aliasing
@set P=32
@goto tools

:x86_64
@set target=-DTCC_TARGET_PE -DTCC_TARGET_X86_64
@rem mingw 64 has an ICE with -Os
@set CC=mingw32-gcc -O0 -s -fno-strict-aliasing
@set P=64
@goto tools

:tools
@%CC% %target% tools/tiny_impdef.c -o tiny_impdef.exe
@%CC% %target% tools/tiny_libmaker.c -o tiny_libmaker.exe

:libtcc
@if not exist libtcc\nul mkdir libtcc
@copy ..\libtcc.h libtcc\libtcc.h
@copy ..\tccstate.h libtcc\tccstate.h
%CC% %target% -shared  -static -DLIBTCC_AS_DLL -DONE_SOURCE ../libtcc.c -o libtcc.dll -Wl,-out-implib,libtcc/libtcc.a
tiny_impdef libtcc.dll -o libtcc/libtcc.def

:tcc
@%CC% %target% ../tcc.c -o tcc.exe -ltcc -Llibtcc

:copy_std_includes
@copy ..\include\*.h include

:libtcc1.a
@.\tcc %target% -c ../lib/libtcc1.c
@.\tcc %target% -c lib/crt1.c
@.\tcc %target% -c lib/wincrt1.c
@.\tcc %target% -c lib/dllcrt1.c
@.\tcc %target% -c lib/dllmain.c
@.\tcc %target% -c lib/chkstk.S
goto lib%P%

:lib32
.\tcc %target% -c ../lib/alloca86.S
.\tcc %target% -c ../lib/alloca86-bt.S
.\tcc %target% -c ../lib/bcheck.c
tiny_libmaker lib/libtcc1.a libtcc1.o alloca86.o alloca86-bt.o crt1.o wincrt1.o dllcrt1.o dllmain.o chkstk.o bcheck.o
@goto the_end

:lib64
.\tcc %target% -c ../lib/alloca86_64.S
tiny_libmaker lib/libtcc1.a libtcc1.o alloca86_64.o crt1.o wincrt1.o dllcrt1.o dllmain.o chkstk.o
:the_end
del *.o

:install
@if not exist %install_to%\nul mkdir %install_to%

@if not exist %install_to%\include\nul mkdir %install_to%\include
@copy include %install_to%\include /Y /V

@if not exist %install_to%\include\sec_api\nul mkdir %install_to%\include\sec_api
@copy include\sec_api %install_to%\include\sec_api /Y /V
@if not exist %install_to%\include\sec_api\sys\nul mkdir %install_to%\include\sec_api\sys
@copy include\sec_api\sys %install_to%\include\sec_api\sys /Y /V

@if not exist %install_to%\include\sys\nul mkdir %install_to%\include\sys
@copy include\sys %install_to%\include\sys /Y /V

@if not exist %install_to%\include\winapi\nul mkdir %install_to%\include\winapi
@copy include\winapi %install_to%\include\winapi /Y /V

@if not exist %install_to%\libtcc\nul mkdir %install_to%\libtcc
@copy libtcc %install_to%\libtcc /Y /V

@if not exist %install_to%\lib\nul mkdir %install_to%\lib
@copy lib %install_to%\lib /Y /V

@copy libtcc.dll %install_to% /Y /V
