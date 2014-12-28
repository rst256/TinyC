#include <stdio.h>
#include <stdlib.h>

#include "libtcc.h"

#include <windows.h>
#include <winbase.h>
//#define _WIN32_WINNT 0x0501





  
typedef void (*MYPROC)(LPTSTR);




int dlopen(const char * filename ){
HINSTANCE hinstLib;
 MYPROC ProcAdd;
BOOL fFreeResult, fRunTimeLinkSuccess = FALSE;
 

// Get a handle to our DLL module created in the previous example. Make sure you already copied the mydllpro.lib and mydllpro.dll to the appropriate folders...
 hinstLib = LoadLibrary("dll");

  

// If the handle is valid, try to get the function address.
if (hinstLib != NULL)
{
	printf("The LoadLibrary(L\"dll\") dll handle is valid...\n");
	ProcAdd = (MYPROC) GetProcAddress(hinstLib, "HelloWorld");
	// If the function address is valid, call the function.
	if (ProcAdd != NULL){
		printf("The function address is valid: %p\n\n", ProcAdd);
		fRunTimeLinkSuccess = TRUE;
		// Pass some text, mydll() will display it on the standard output...
		(ProcAdd) ("\nThis message is via DLL function...\n");
	}else
		printf("\nThe function address is NOT valid, error: %d.\n", GetLastError());
	
	
	// Free up the DLL module.
	fFreeResult = FreeLibrary(hinstLib);
	if (fFreeResult != 0)
		printf("FreeLibrary() is OK.\n");
	else
		printf("FreeLibrary() is not OK, error: %d.\n", GetLastError());
}else
	printf("The LoadLibrary(L\"mydllpro\") dll handle is not valid, error: %d.\n", GetLastError());

// If unable to call the DLL function, use an alternative.
if (!fRunTimeLinkSuccess)
	printf("This message via alternative method...\n");

return 0;
}



int print_file(const char *filename) {
	FILE *f = fopen(filename, "rb");
		
	if (!f) {
		fprintf(stderr, "failed to open source file: %s\n", filename);
		fflush(stderr);
		return 0;
	}

	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET);
	
	char *string = malloc(fsize + 1);
	fread(string, fsize, 1, f);
	fclose(f);
	
	string[fsize] = 0;
	printf("%s\n", string);

	free(string);
	return 1;
}

int TccMain(int argc, char **argv, TCCState * tccState){
	printf("tccState is %p=%p\n", tccState, GetTccState());
	//printf("output_type is %i\n", tccState->output_type);

	//return main(argc, argv);
}

int main(int argc, char **argv)
{
	if( !dlopen("init.dll") ) 
		fprintf(stderr, "Could not reseive tcc state\n");

	//HelloWorld();
	//return print_file(argv[0]);
	return 0;
}