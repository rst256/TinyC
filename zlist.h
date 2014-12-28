#ifndef _H_ZLIST_TCC_
#define _H_ZLIST_TCC_

#define ZLIST_STUB(ARG) ARG


#ifndef PUB_FUNC
	#define PUB_FUNC 
	struct TCCState;
	typedef struct TCCState TCCState;
#endif
/*
typedef char* zstring_t;
typedef zstring_t* zstringlist_t;
*/

/* build new list */
/*
LIBTCCAPI zstringlist_t zlist_build(int argc, char **argv);
LIBTCCAPI  int tcc_include_paths_nb(TCCState *s);
*/

// foreach list item macros (don't like - don't use!)
#define foreach_helper(VAR, INDEX_VAR, LIST) if( (LIST) != 0 ) \
		for(int INDEX_VAR=0; (VAR = (LIST)[INDEX_VAR]) != 0; INDEX_VAR++)
#define foreach(VAR, LIST) foreach_helper(VAR, VAR##_index, LIST)
// --------- ZLIST	struct EXT_T; 

#define ZLIST_BUILDER(NAME, EXT_T, ITEM_TYPE, ...) \
	typedef ITEM_TYPE* EXT_T; \
	PUB_FUNC EXT_T NAME(int argc, ITEM_TYPE* argv)
// --------- ZLIST


#define TCC_STATE_LIST_TYPE(NAME, ITEM_TYPE, ...) \
	ZLIST_BUILDER(NAME##_zlist_build, NAME##_zlist_t, ITEM_TYPE); \
	ZLIST_BUILDER(NAME##_zlistref_build, NAME##_zlist_t, ITEM_TYPE) 

/*
#define TCC_STATE_LIST_API(TYPE, NAME) \
	PUB_FUNC TYPE##_zlist_t* tcc_get_##NAME(TCCState *s); \
	PUB_FUNC TYPE##_zlistref_t* tcc_getref_##NAME(TCCState *s); \
	PUB_FUNC int tcc_##NAME##_count(TCCState *s)
*/

#define TCC_STATE_LIST_API_HELPER(TYPE, CONSTR_REF, CONSTR_COPY, NAME) \
	PUB_FUNC TYPE tcc_get_##NAME(TCCState *s);	\
	PUB_FUNC TYPE tcc_getref_##NAME(TCCState *s);	\
	PUB_FUNC int tcc_##NAME##_count(TCCState *s);	
#define TCC_STATE_LIST_API(TYPE, NAME) \
	TCC_STATE_LIST_API_HELPER(TYPE##_zlist_t, TYPE##_zlist_build, TYPE##_zlistref_build, NAME)

typedef char* string;

TCC_STATE_LIST_TYPE(string, char *);


TCC_STATE_LIST_API(string, include_paths);
TCC_STATE_LIST_API(string, sysinclude_paths);
TCC_STATE_LIST_API(string, library_paths);
TCC_STATE_LIST_API(string, crt_paths);
TCC_STATE_LIST_API(string, target_deps);


#undef ZLIST_BUILDER
#undef TCC_STATE_LIST_API_HELPER
#undef TCC_STATE_LIST_API
#undef TCC_STATE_LIST_TYPE



/*
struct TCCStringList{
	int count;
	string*items;
};
typedef struct TCCStringList TCCStringList;
*/

/*
#define ZLIST_TYPEDEF(ITEM_TYPE, TYPE_NAME) typedef ITEM_TYPE* TYPE_NAME; \
LIBTCCAPI TYPE_NAME TYPE_NAME##_build(int argc, ITEM_TYPE argv); \
LIBTCCAPI void TYPE_NAME##_free(TYPE_NAME zlist); \
LIBTCCAPI int TYPE_NAME##_count(TYPE_NAME zlist); \
LIBTCCAPI ITEM_TYPE TYPE_NAME##_item(TYPE_NAME zlist, int index); \

#define ZLIST_IMPLDEF(ITEM_TYPE, TYPE_NAME) \
LIBTCCAPI TYPE_NAME TYPE_NAME##_build(int argc, ITEM_TYPE argv); \
LIBTCCAPI void TYPE_NAME##_free(TYPE_NAME zlist); \
LIBTCCAPI int TYPE_NAME##_count(TYPE_NAME zlist); \
LIBTCCAPI ITEM_TYPE TYPE_NAME##_item(TYPE_NAME zlist, int index); \
*/

/* for easy define dynamic pointers */
/*
#define va_array(VAR, TYPE, COUNT) TYPE **VAR = tcc_malloc(sizeof(TYPE)*(COUNT))
#define va_var(VAR, TYPE) TYPE *VAR = tcc_malloc(sizeof(TYPE)) 
*/

/* foreach list item macros */
/*
#define foreach_helper(VAR, INDEX_VAR, LIST) int INDEX_VAR; \
	for(INDEX_VAR=0; (VAR = list_item((LIST), INDEX_VAR) ) != 0; INDEX_VAR++)
#define foreach(VAR, LIST) foreach_helper(VAR, VAR##_iter_index, LIST)
*/
// foreach zlist item macros 

/*
// build new list 
LIBTCCAPI TCCStringList *list_build(int argc, string*argv);

// get list item at index 
LIBTCCAPI stringlist_item(TCCStringList *s, int index);

// free string list 
LIBTCCAPI void list_free(TCCStringList *s);

// return list of all include paths 
LIBTCCAPI TCCStringList *tcc_get_include_paths(TCCState *s);
*/


#endif // _H_ZLIST_TCC_