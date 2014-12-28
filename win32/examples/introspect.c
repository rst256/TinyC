#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "libtcc.h"


static TCCState *tccState;

static TCCState *GetTccState(void){
	return tccState;
}

/*
const char build_in_defines[] =
"#include \"libtcc.h\"\n"
" TCCState *GetTccState(void);\n"
"#define HOST_APP \"introspect.exe\"\n"
"\n";
const 	char * build_in_header = "..\\libtcc\\libtcc.h";
*/

int main(int argc, char **argv)
{
	
	int (*the_main)(int, char **, TCCState *);
	
	tccState = tcc_new();
	if (!tccState) {
		fprintf(stderr, "Could not create tcc state\n");
		exit(1);
	}
	//tcc_add_include_path(tccState, "..\\..\\libtcc");
	//tcc_add_sysinclude_path(tccState, "..\\include");
	//tcc_add_sysinclude_path(tccState, "..\\include\\winapi");

	//tcc_set_lib_path(tccState, "d:\\download\\C\\tcc-0.9.26\\");
	int i;
    if (argc > 1 ){
		for(i=1; i<argc; i++)
			if(argv[i][0] == '-')
				tcc_set_options(tccState, argv[i]);
	}

	
    /* if tcclib.h and libtcc1.a are not installed, where can we find them */
    /*
    if (argc >= 2 && !memcmp(argv[1], "lib_path=",9))
        tcc_set_lib_path(tccState, argv[1]+9);
    */


	/* MUST BE CALLED before any compilation */
	tcc_set_output_type(tccState, TCC_OUTPUT_MEMORY);
	tcc_add_symbol(tccState, "GetTccState", (void*)GetTccState);
	//tcc_add_file(tccState, "..\\libtcc.dll");
   // tcc_add_symbol(tccState, "include", include);
/*

	if(tcc_add_file(tccState, build_in_header) == -1){
		fprintf(stderr, "failed to add script system header file: %s\n", build_in_header);
		fflush(stderr);
		return 1;
	}
*/

	/*
	if(tcc_compile_string(tccState, build_in_defines) == -1){
		fprintf(stderr, "failed to add defines for build-in functions:\n%s\n", build_in_defines);
		fflush(stderr);
		return 1;
	}
	*/
    if (argc > 1 ){
		for(i=1; i<argc; i++)
			if(argv[i][0]!='-')
				if(tcc_add_file(tccState, argv[i]) == -1){
					fprintf(stderr, "failed to open source file: %s\n", argv[i]);
					fflush(stderr);
					//return 1;
				}
	}

		



    //include( "init.dll");

    /* relocate the code */
    if (tcc_relocate(tccState, TCC_RELOCATE_AUTO) < 0){
			fprintf(stderr, "failed to recolate source\n");
			fflush(stderr);
			return 0;
		}

    /* get entry symbol */
    the_main = tcc_get_symbol(tccState, "TccMain");
    if (!the_main){
			fprintf(stderr, "run failed TccMain not defined\n");
			fflush(stderr);
			return 0;
		}

	/*
	if(argc <= 1){
		//tcs_argv[0] = "hggfhfgh";
	}else
		//tcs_argv[0] = strdup( argv[1] );
	}
	*/
	/* run the code */
	//char ** tcs_argv;
	int exit_code = the_main(argc,  argv, tccState);
	
	/*delete the state*/
	tcc_delete(tccState);
	
	return exit_code;
}
