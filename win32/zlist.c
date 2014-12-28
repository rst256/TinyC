# 1 "../zlist.h" 1






struct TCCState;
typedef struct TCCState TCCState;




 

 



 

 



 



 
# 41 "../zlist.h" 3
 







 char ** string_zlist_build(int argc, char ** argv) ;  char ** string_zlistref_build(int argc, char ** argv);


 char ** tcc_get_include_paths(TCCState *s);  char ** tcc_getref_include_paths(TCCState *s);  int tcc_include_paths_count(TCCState *s);



 char ** tcc_get_sysinclude_paths(TCCState *s);  char ** tcc_getref_sysinclude_paths(TCCState *s);  int tcc_sysinclude_paths_count(TCCState *s);





 char ** tcc_get_library_paths(TCCState *s);  char ** tcc_getref_library_paths(TCCState *s);  int tcc_library_paths_count(TCCState *s);




 char ** tcc_get_crt_paths(TCCState *s);  char ** tcc_getref_crt_paths(TCCState *s);  int tcc_crt_paths_count(TCCState *s);




 char ** tcc_get_target_deps(TCCState *s);  char ** tcc_getref_target_deps(TCCState *s);  int tcc_target_deps_count(TCCState *s);
# 87 "../zlist.h" 3
 
# 101 "../zlist.h" 3
 

 



 

 




 
 
# 129 "../zlist.h" 3
 
# 2 "../zlist.c" 2





 
# 18 "../zlist.c"
 
# 64 "../zlist.c"
 

 string_zlist_t* string_zlist_build(int argc, char** argv){ int i; if(argc == 0) return 0; char** new_zlist = tcc_malloc(sizeof(char*)*argc); for(i = 0; i < argc; i++) new_zlist[i] = (tcc_strdup)(argv[i]); new_zlist[argc] = 0; return new_zlist; } ;  * string_zlistref_build(int argc, char** argv){ int i; if(argc == 0) return 0; char** new_zlist = tcc_malloc(sizeof(char*)*argc); for(i = 0; i < argc; i++) new_zlist[i] = (ZLIST_STUB)(argv[i]); new_zlist[argc] = 0; return new_zlist; } ;;

 
 string_zlist_t* tcc_get_include_paths(TCCState *s){ return string_zlist_build(s->nb_include_paths, s->include_paths); }  string_zlistref_t* tcc_getref_include_paths(TCCState *s){ return string_zlistref_build(s->nb_include_paths, s->include_paths); }  int tcc_include_paths_count(TCCState *s){ return s->nb_include_paths; };

 
 string_zlist_t* tcc_get_sysinclude_paths(TCCState *s){ return string_zlist_build(s->nb_sysinclude_paths, s->sysinclude_paths); }  string_zlistref_t* tcc_getref_sysinclude_paths(TCCState *s){ return string_zlistref_build(s->nb_sysinclude_paths, s->sysinclude_paths); }  int tcc_sysinclude_paths_count(TCCState *s){ return s->nb_sysinclude_paths; };

 
 string_zlist_t* tcc_get_library_paths(TCCState *s){ return string_zlist_build(s->nb_library_paths, s->library_paths); }  string_zlistref_t* tcc_getref_library_paths(TCCState *s){ return string_zlistref_build(s->nb_library_paths, s->library_paths); }  int tcc_library_paths_count(TCCState *s){ return s->nb_library_paths; };

 
 string_zlist_t* tcc_get_crt_paths(TCCState *s){ return string_zlist_build(s->nb_crt_paths, s->crt_paths); }  string_zlistref_t* tcc_getref_crt_paths(TCCState *s){ return string_zlistref_build(s->nb_crt_paths, s->crt_paths); }  int tcc_crt_paths_count(TCCState *s){ return s->nb_crt_paths; };

 
 string_zlist_t* tcc_get_target_deps(TCCState *s){ return string_zlist_build(s->nb_target_deps, s->target_deps); }  string_zlistref_t* tcc_getref_target_deps(TCCState *s){ return string_zlistref_build(s->nb_target_deps, s->target_deps); }  int tcc_target_deps_count(TCCState *s){ return s->nb_target_deps; };




 





 

 





 


 
# 114 "../zlist.c"
 
