[1mdiff --git a/.Makefile.bat b/.Makefile.bat[m
[1mindex aa3a722..429fc6b 100644[m
[1m--- a/.Makefile.bat[m
[1m+++ b/.Makefile.bat[m
[36m@@ -9,14 +9,19 @@[m
 @SET target=-DTCC_TARGET_PE -DTCC_TARGET_I386[m
 @SET CC=mingw32-gcc [m
 @SET P=32[m
[31m-@GOTO tools[m
[32m+[m[32m@GOTO ut_tools[m
 [m
 :x86_64[m
 @SET target=-DTCC_TARGET_PE -DTCC_TARGET_X86_64[m
 @REM mingw 64 has an ICE with -Os[m
 @SET CC=x86_64-pc-mingw32-gcc -O0 -s -fno-strict-aliasing[m
 @SET P=64[m
[31m-@GOTO tools[m
[32m+[m[32m@GOTO ut_tools[m
[32m+[m
[32m+[m[32m:ut_tools[m
[32m+[m[32m@IF NOT EXIST include\nul mkdir include[m
[32m+[m[32m@copy ..\include\ut*.h include[m
[32m+[m[32m@IF %ERRORLEVEL% EQU 1 GOTO error[m
 [m
 :tools[m
 %CC% %target% tools/tiny_impdef.c -o tiny_impdef.exe [m
[1mdiff --git a/tcc.h b/tcc.h[m
[1mindex 3f41917..9cbf1bf 100644[m
[1m--- a/tcc.h[m
[1m+++ b/tcc.h[m
[36m@@ -356,8 +356,10 @@[m [mtypedef struct Section {[m
     struct Section *link;    /* link to another section */[m
     struct Section *reloc;   /* corresponding section for relocation, if any */[m
     struct Section *hash;     /* hash table for symbols */[m
[32m+[m[32m    struct Section *generic; /* generic data */[m
     struct Section *next;[m
     char name[1];           /* section name */[m
[32m+[m
 } Section;[m
 [m
 typedef struct DLLReference {[m
[1mdiff --git a/tccgen.c b/tccgen.c[m
[1mindex 3a4a3f1..407751f 100644[m
[1m--- a/tccgen.c[m
[1m+++ b/tccgen.c[m
[36m@@ -3906,8 +3906,12 @@[m [mvpushi(type2.ref->v);[m
             }[m
             next();[m
         }else if (tok == ':' || tok == TOK_CL_ARROW) {[m
[31m-            int qualifiers;[m
[31m-				SValue *sv = vtop;[m
[32m+[m[32m           int qualifiers;[m
[32m+[m[32m           int bt, v, t;[m
[32m+[m
[32m+[m[32m           SValue *sv = vtop;[m
[32m+[m[32m           t = sv->type.t & VT_TYPE;[m
[32m+[m[32m           bt = t & VT_BTYPE;[m
             /* field */ [m
            if (tok == TOK_CL_ARROW) [m
               indir();[m
[1mdiff --git a/win32/libtcc.dll b/win32/libtcc.dll[m
[1mindex 478a7e9..43c473e 100644[m
Binary files a/win32/libtcc.dll and b/win32/libtcc.dll differ
warning: LF will be replaced by CRLF in tcc.h.
The file will have its original line endings in your working directory.
warning: LF will be replaced by CRLF in tccgen.c.
The file will have its original line endings in your working directory.
