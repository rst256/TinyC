#define API_OBJECT TCCState
API_OBJECT(TCCState,


TCC_STATE_LIST_TYPE(string, char*, tcc_strdup, TMPL_STUB );

LIST(string, include_paths);
LIST(string, sysinclude_paths);
LIST(string, library_paths);
LIST(string, crt_paths);
LIST(string, target_deps);
LIST(string, files);

)


