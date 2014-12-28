
#include "zlist.h"


#warning Enable advanced tcc api. Remember this api is VERY BETA and only for tcc development.\
Dont use this api in you project. Interface of this api may be changed.

/* build new list */
/*
PUB_FUNC zstringlist_t zlist_build(int argc, char **argv){
	int i;
	if(argc == 0) return 0;
	zstringlist_t new_zlist = tcc_malloc(sizeof(zstring_t)*argc);
	for(i = 0; i < argc; i++)
		new_zlist[i] = tcc_strdup(argv[i]);
	new_zlist[argc] = 0;
	return new_zlist;
}
*/


/*
#define ZLIST_BUILDER(NAME, EXT_T, ITEM_TYPE, COPY_FUNC) \
	PUB_FUNC ITEM_TYPE* NAME(int argc, ITEM_TYPE* argv){ 	int i; \
		if(argc == 0) return 0; \
		ITEM_TYPE* new_zlist = tcc_malloc(sizeof(ITEM_TYPE)*argc); \
		for(i = 0; i < argc; i++) \
			new_zlist[i] = COPY_FUNC(argv[i]); \
		new_zlist[argc] = 0; \
		return new_zlist; \
	}
*/

#define ZLIST_BUILDER(NAME, EXT_T, ITEM_TYPE, COPY_FUNC) \
	PUB_FUNC EXT_T NAME(int argc, ITEM_TYPE* argv){ 	int i; \
		if(argc == 0) return 0; \
		ITEM_TYPE* new_zlist = tcc_malloc(sizeof(ITEM_TYPE)*argc); \
		for(i = 0; i < argc; i++) \
			new_zlist[i] = COPY_FUNC(argv[i]); \
		new_zlist[argc] = 0; \
		return new_zlist; \
	}


#define ZLIST_FOREACH_HELPER(VAR, INDEX_VAR, LIST) if( (LIST) != 0 ) \
		for(int INDEX_VAR=0; (VAR = (LIST)[INDEX_VAR]) != 0; INDEX_VAR++)
#define ZLIST_FOREACH(VAR, LIST) foreach_helper(VAR, VAR##_index, LIST)







#define TCC_STATE_LIST_TYPE(TYPE, ITEM_TYPE, FUNC_COPY, FUNC_REF) \
	ZLIST_BUILDER(TYPE##_zlist_build, TYPE##_zlist_t, ITEM_TYPE, FUNC_COPY); \
	ZLIST_BUILDER(TYPE##_zlistref_build, TYPE##_zlist_t, ITEM_TYPE, FUNC_REF); 
/*
#define TCC_STATE_LIST_API(TYPE, NAME) \
	PUB_FUNC TYPE* tcc_get_##NAME(TCCState *s){ \
		return TYPE##_zlist_build(s->nb_##NAME, s->NAME); \
	} \
	PUB_FUNC TYPE* tcc_getref_##NAME(TCCState *s){ \
		return TYPE##_zlistref_build(s->nb_##NAME, s->NAME); \
	} \
	PUB_FUNC int tcc_##NAME##_count(TCCState *s){ \
		return s->nb_##NAME; \
	} 
*/

#define TCC_STATE_LIST_API_HELPER(TYPE, CONSTR_REF, CONSTR_COPY, NAME) \
	PUB_FUNC TYPE tcc_get_##NAME(TCCState *s){ \
		return CONSTR_REF(s->nb_##NAME, s->NAME); \
	} \
	PUB_FUNC TYPE tcc_getref_##NAME(TCCState *s){ \
		return CONSTR_COPY(s->nb_##NAME, s->NAME); \
	} \
	PUB_FUNC int tcc_##NAME##_count(TCCState *s){ \
		return s->nb_##NAME; \
	} 
#define TCC_STATE_LIST_API(TYPE, NAME) \
	TCC_STATE_LIST_API_HELPER(TYPE##_zlist_t, TYPE##_zlist_build, TYPE##_zlistref_build, NAME)
	

/*
#define TCC_GET_ZLIST(NAME) \
	PUB_FUNC zstringlist_t tcc_get_##NAME(TCCState *s){ \
		return zlist_build(s->nb_##NAME, s->NAME); \
	} \
	PUB_FUNC int tcc_##NAME##_count(TCCState *s){ \
		return s->nb_##NAME; \
	}
*/

TCC_STATE_LIST_TYPE(string, char*, tcc_strdup, ZLIST_STUB );
// build include_paths api 
TCC_STATE_LIST_API(string, include_paths);

// build sysinclude_paths 
TCC_STATE_LIST_API(string, sysinclude_paths);

// build library_paths 
TCC_STATE_LIST_API(string, library_paths);

// build crt_paths 
TCC_STATE_LIST_API(string, crt_paths);

// build target_deps 
TCC_STATE_LIST_API(string, target_deps);



#undef ZLIST_BUILDER
#undef TCC_STATE_LIST_API_HELPER
#undef TCC_STATE_LIST_API
#undef TCC_STATE_LIST_TYPE

/* build  */
/*
PUB_FUNC TCCStringList *list_build(int argc, char **argv){
	va_var(nl, TCCStringList); 
	va_array(nl->items, )
}
*/

/* get list item at index */
/*
PUB_FUNC inline char *list_item(TCCStringList *s, int index){
	if(index >= s->count) return 0;
	return s->items[index];
}
*/


/* free string list */
/*
PUB_FUNC void list_free(TCCStringList *s){
	int i;
	int c = s->count;
	char **lst = s->items;
	for(i=0; i<c; i++)
		tcc_free(lst[i]);
	tcc_free(lst);
	tcc_free(s);
}
*/
