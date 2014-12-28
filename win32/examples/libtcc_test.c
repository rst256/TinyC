/*
 * Simple Test program for libtcc
 *
 * libtcc can be useful to use tcc as a "backend" for a code generator.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "libtcc.h"

/* this function is called by the generated code */
int add(int a, int b)
{
    return a + b;
}

char my_program[] =
"int fib(int n)\n"
"{\n"
"    if (n <= 2)\n"
"        return 1;\n"
"    else\n"
"        return fib(n-1) + fib(n-2);\n"
"}\n"
"\n"
"int foo(int n)\n"
"{\n"
"    printf(\"Hello World!\\n\");\n"
"    printf(\"fib(%d) = %d\\n\", n, fib(n));\n"
"    printf(\"add(%d, %d) = %d\\n\", n, 2 * n, add(n, 2 * n));\n"
"    return 0;\n"
"}\n";

int main(int argc, char **argv)
{
	int (*the_main)(int, char **);
	
	tccState = tcc_new();
	if (!tccState) {
		fprintf(stderr, "Could not create tcc state\n");
		exit(1);
	}
	tcc_add_include_path(tccState, "libtcc");
    /* if tcclib.h and libtcc1.a are not installed, where can we find them */
    /*
    if (argc >= 2 && !memcmp(argv[1], "lib_path=",9))
        tcc_set_lib_path(tccState, argv[1]+9);
    */


	/* MUST BE CALLED before any compilation */
	tcc_set_output_type(tccState, TCC_OUTPUT_MEMORY);
	//tcc_add_symbol(tccState, "tccState", (void*)tccState);
	//tcc_add_file(tccState, "libtcc.dll");
    //tcc_add_symbol(tccState, "include", include);

    if (argc >= 1 )
		if(tcc_add_file(tccState, argv[1]) == -1){
			fprintf(stderr, "failed to open source file: %s\n", argv[1]);
			fflush(stderr);
			return 1;
		}

		



    //include( "init.dll");

    /* relocate the code */
    if (tcc_relocate(tccState, TCC_RELOCATE_AUTO) < 0)
        return 1;

    /* get entry symbol */
    the_main = tcc_get_symbol(tccState, "main");
    if (!the_main)
        return 1;

	char *tcs_argv[1] ;
//tcs_argv[0] = "hggfhfgh";
	tcs_argv[0] = strdup( argv[1] );
	/* run the code */
	the_main(1,  tcs_argv);
	
	/* delete the state */
	tcc_delete(tccState);
	
	return 0;
}
