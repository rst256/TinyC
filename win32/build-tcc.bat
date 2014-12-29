@rem ----------------------------------------------------
@rem batch file to build tcc using mingw gcc
@rem ----------------------------------------------------
@cls
@echo -------------------------------- Building Tiny C --------------------------------
@set install_to=c:\lua\5.1\clibs\luatcc
@set libtcc_src=../libtcc.c
@set flags_extras= -DCONFIG_TCC_PP_EXTRAS -DCONFIG_TCC_STATE_EXTRAS -DCONFIG_TCC_CORE_DEBUG
@rem set flags_extras=

@rem "parsing" build cmdline options
@rem set libtcc_src= %libtcc_src% ../lua/libtcc.c
@rem set luaapi= dfgdf
@rem for %%x in (%*) do (
@rem 	@echo %%x %%%x%
@rem 	if not %%x =="" echo "%%x !="""
@rem )


@set /p VERSION= < ..\VERSION
@echo>..\config.h #define TCC_VERSION "%VERSION%"

@if _%PROCESSOR_ARCHITEW6432%_==_AMD64_ goto x86_64
@if _%PROCESSOR_ARCHITECTURE%_==_AMD64_ goto x86_64

@echo Configure for x86 architecture
@set target=-DTCC_TARGET_PE -DTCC_TARGET_I386
@set CC=mingw32-gcc -Os -s -fno-strict-aliasing %flags_extras%
@set P=32
@goto tools

:x86_64
@echo Configure for x86_64 architecture
@set target=-DTCC_TARGET_PE -DTCC_TARGET_X86_64
@rem mingw 64 has an ICE with -Os
@set CC=mingw32-gcc -O0 -s -fno-strict-aliasing %flags_extras%
@set P=64
@goto tools

:tools
@echo Build tools ...
@%CC% %target% tools/tiny_impdef.c -o tiny_impdef.exe
@IF %ERRORLEVEL% EQU 1 GOTO error

@%CC% %target% tools/tiny_libmaker.c -o tiny_libmaker.exe
@IF %ERRORLEVEL% EQU 1 GOTO error

:libtcc
@echo Build libtcc ...
@if not exist libtcc\nul mkdir libtcc
@copy ..\libtcc.h libtcc\libtcc.h > build.log
@copy ..\zlist.h libtcc\zlist.h > build.log
%CC% %target% -shared  -static -DLIBTCC_AS_DLL -DONE_SOURCE %libtcc_src% -o libtcc.dll -Wl,-out-implib,libtcc/libtcc.a
@IF %ERRORLEVEL% EQU 1 GOTO error

@tiny_impdef libtcc.dll -o libtcc/libtcc.def
@IF %ERRORLEVEL% EQU 1 GOTO error

:tcc
@echo Build tcc ...
@%CC% %target% ../tcc.c -o tcc.exe -ltcc -Llibtcc
@IF %ERRORLEVEL% EQU 1 GOTO error
:copy_std_includes
@echo Copy c standart includes ...
@copy ..\include\*.h include

:libtcc1.a
@echo Build libtcc1.a ...
@.\tcc %target% -c ../lib/libtcc1.c
@IF %ERRORLEVEL% EQU 1 GOTO error
@.\tcc %target% -c lib/crt1.c
@IF %ERRORLEVEL% EQU 1 GOTO error
@.\tcc %target% -c lib/wincrt1.c
@IF %ERRORLEVEL% EQU 1 GOTO error
@.\tcc %target% -c lib/dllcrt1.c
@IF %ERRORLEVEL% EQU 1 GOTO error
@.\tcc %target% -c lib/dllmain.c
@IF %ERRORLEVEL% EQU 1 GOTO error
@.\tcc %target% -c lib/chkstk.S
@IF %ERRORLEVEL% EQU 1 GOTO error
@goto lib%P%

:lib32
@echo Build lib32 ...
@.\tcc %target% -c ../lib/alloca86.S
@IF %ERRORLEVEL% EQU 1 GOTO error
@.\tcc %target% -c ../lib/alloca86-bt.S
@IF %ERRORLEVEL% EQU 1 GOTO error
@.\tcc %target% -c ../lib/bcheck.c
@IF %ERRORLEVEL% EQU 1 GOTO error
@tiny_libmaker lib/libtcc1.a libtcc1.o alloca86.o alloca86-bt.o crt1.o wincrt1.o dllcrt1.o dllmain.o chkstk.o bcheck.o
@IF %ERRORLEVEL% EQU 1 GOTO error
@goto clear

:lib64
@echo Build lib64 ...
@.\tcc %target% -c ../lib/alloca86_64.S
@IF %ERRORLEVEL% EQU 1 GOTO error
@tiny_libmaker lib/libtcc1.a libtcc1.o alloca86_64.o crt1.o wincrt1.o dllcrt1.o dllmain.o chkstk.o
@IF %ERRORLEVEL% EQU 1 GOTO error
:clear
@echo Clear ...
@del *.o

:install

@echo ------------------------------- Installing Tiny C --------------------------------
@if not exist %install_to%\nul mkdir %install_to%

@if not exist %install_to%\include\nul mkdir %install_to%\include
@copy include %install_to%\include /Y /V >install.log

@if not exist %install_to%\include\sec_api\nul mkdir %install_to%\include\sec_api
@copy include\sec_api %install_to%\include\sec_api /Y /V >install.log
@if not exist %install_to%\include\sec_api\sys\nul mkdir %install_to%\include\sec_api\sys
@copy include\sec_api\sys %install_to%\include\sec_api\sys /Y /V >install.log

@if not exist %install_to%\include\sys\nul mkdir %install_to%\include\sys
@copy include\sys %install_to%\include\sys /Y /V >install.log

@if not exist %install_to%\include\winapi\nul mkdir %install_to%\include\winapi
@copy include\winapi %install_to%\include\winapi /Y /V >install.log

@if not exist %install_to%\libtcc\nul mkdir %install_to%\libtcc
@copy libtcc %install_to%\libtcc /Y /V >install.log

@if not exist %install_to%\lib\nul mkdir %install_to%\lib
@copy lib %install_to%\lib /Y /V >install.log

@copy libtcc.dll %install_to% /Y /V >install.log
@copy tcc.exe %install_to% /Y /V >install.log

@echo ------------------------- Testing installed complnents -------------------------
cmd /k run-quick-tests.bat  %install_to%
@IF %ERRORLEVEL% EQU 1 GOTO error
@echo ------------------------- Testing complnents sussefull -------------------------
@rem pause
@goto end

:error
@echo ------------------------------- Make Tiny C failed -------------------------------
@rem pause


:end
