#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//#include "libtcc.h"

#define head "libtcc.h"
#include head

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

#define ZLIST_FOREACH_HELPER(VAR, INDEX_VAR, LIST) if( (LIST) != 0 ) \
		for(int INDEX_VAR=0; (VAR = (LIST)[INDEX_VAR]) != 0; INDEX_VAR++)
#define foreach(VAR, LIST) ZLIST_FOREACH_HELPER(VAR, VAR##_index_##__LINE__, LIST)
#define foreach_i(VAR, VAR_I, LIST) ZLIST_FOREACH_HELPER(VAR, VAR_I, LIST)


#define TCC_LIST_COUNT(NAME, TCC) tcc_##NAME##_count(TCC)
#define TCC_LIST_REF(NAME, TCC) tcc_getref_##NAME(TCC)
#define TCC_LIST(NAME, TCC) tcc_get_##NAME(TCC)

#define ZLIST_DUMP(NAME) \
	printf("%s(%i):\n", #NAME, TCC_LIST_COUNT(NAME, tcc)); \
	foreach_i(s, i, TCC_LIST_REF(NAME, tcc)) printf("\t%i: %s\n", i, s);

//	foreach_i(s, i, TCC_LIST_REF(NAME, tcc)) printf("%i: %s\n", i, s);
		
	



void tcc_state(TCCState * tcc){
	char *s;
	printf("\n");
	ZLIST_DUMP(include_paths);
	ZLIST_DUMP(sysinclude_paths);
	ZLIST_DUMP(library_paths);
	ZLIST_DUMP(crt_paths);
	ZLIST_DUMP(target_deps);
}

int main(int argc, char **argv)
{

	int (*the_main)(int, char **, TCCState *);
	/*
	string* arg_list = zlist_build(argc, argv);
	char * s;
	*/

	/*
	foreach(s, arg_list)
		printf("%i: %s\n", s_index, s);
	*/

        /*
        int s_index; if( (arg_list) != 0 ) for(s_index=0; (s = (arg_list)[s_index]) != 0; s_index++)
                printf("%i: %s\n", s_index, s);
        */

	tccState = tcc_new();
	if (!tccState) {
		fprintf(stderr, "Could not create tcc state\n");
		exit(1);
	}
	/*
	printf("include path count is %i\n", tcc_include_paths_nb(tccState));
	zstringlist_t paths=tcc_get_include_paths(tccState);
	foreach(s, paths)
		printf("include path #%i: %s\n", s_index+1, s);
	*/
	tcc_state(tccState);
	for1(){
	tcc_state(tccState);

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
	/*
	printf("include path count is %i\n", tcc_include_paths_nb(tccState));
	*/
	/*
	paths=tcc_get_include_paths(tccState);
		foreach(s, paths)
			printf("include path #%i: %s\n", s_index+1, s);
	*/
	tcc_state(tccState);

	tcc_add_include_path(tccState, "libtcc");

	/*
	printf("include path count is %i\n", tcc_include_paths_nb(tccState));
	foreach(s, tcc_get_include_paths(tccState))
		printf("include path #%i: %s\n", s_index+1, s);
	*/
	tcc_state(tccState);

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
//printf("output_type is %i\n", tccState->verbose);

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
