//#if !defined(_H_ZLIST_TCC_) || !def
//#define _H_ZLIST_TCC_


#ifdef TMPL_IMPLEMENT
#define TMPL_IMPL(CODE) { CODE }
#define TMPL_DEF(DEFINE) 
#else
#define TMPL_IMPL(CODE) ;
#define TMPL_DEF(DEFINE) DEFINE;
#endif


#define TMPL_OPAQUE_REF(NAME, PRIVATE) struct NAME TMPL_IMPL(PRIVATE) \
typedef struct NAME * NAME;

#define TMPL_STUB(ARG) ARG


#ifndef PUB_FUNC
	#define PUB_FUNC 
	struct TCCState;
	typedef struct TCCState TCCState;
#endif


#define ZLIST_BUILDER(NAME, EXT_T, ITEM_TYPE, COPY_FUNC) \
	PUB_FUNC EXT_T NAME(int argc, ITEM_TYPE* argv) TMPL_IMPL( \
		int i; \
		if(argc == 0) return 0; \
		EXT_T new_zlist = tcc_malloc(sizeof(ITEM_TYPE)*argc); \
		for(i = 0; i < argc; i++) \
			new_zlist[i] = COPY_FUNC(argv[i]); \
		new_zlist[argc] = 0; \
		return new_zlist; \
	)

#ifndef _ZLIST_STATIC_CODE_H
#define _ZLIST_STATIC_CODE_H

#define ZLIST_FOREACH_HELPER(VAR, INDEX_VAR, LIST) if( (LIST) != 0 ) \
		for(int INDEX_VAR=0; (VAR = (LIST)[INDEX_VAR]) != 0; INDEX_VAR++)
#define foreach(VAR, LIST) ZLIST_FOREACH_HELPER(VAR, VAR##_index_##__LINE__, LIST)
#define foreach_i(VAR, VAR_I, LIST) ZLIST_FOREACH_HELPER(VAR, VAR_I, LIST)

#endif

#define TCC_STATE_LIST_TYPE(TYPE, ITEM_TYPE, FUNC_COPY, FUNC_REF) \
	TMPL_DEF( typedef ITEM_TYPE * TYPE##_zlist_t ) \
	ZLIST_BUILDER(TYPE##_zlist_build, TYPE##_zlist_t, ITEM_TYPE, FUNC_COPY); \
	ZLIST_BUILDER(TYPE##_zlistref_build, TYPE##_zlist_t, ITEM_TYPE, FUNC_REF)


#define TCC_STATE_LIST_API_HELPER(TYPE, CONSTR_REF, CONSTR_COPY, NAME) \
	PUB_FUNC TYPE tcc_get_##NAME(TCCState *s) TMPL_IMPL(  \
		return CONSTR_REF(s->nb_##NAME, s->NAME); \
	) \
	PUB_FUNC TYPE tcc_getref_##NAME(TCCState *s) TMPL_IMPL(  \
		return CONSTR_COPY(s->nb_##NAME, s->NAME); \
	) \
	PUB_FUNC int tcc_##NAME##_count(TCCState *s) TMPL_IMPL(  \
		return s->nb_##NAME; \
	) 
#define TCC_STATE_LIST_API(TYPE, NAME) \
	TCC_STATE_LIST_API_HELPER(TYPE##_zlist_t, TYPE##_zlist_build, TYPE##_zlistref_build, NAME)
	
#define TCC_LIST_COUNT(NAME, TCC) tcc_##NAME##_count(TCC)
#define TCC_LIST_REF(NAME, TCC) tcc_getref_##NAME(TCC)
#define TCC_LIST(NAME, TCC) tcc_get_##NAME(TCC)

#if 	defined(TCC_STATE_LIST_API) && \
		defined(TCC_STATE_LIST_TYPE) 

TCC_STATE_LIST_TYPE(string, char*, tcc_strdup, TMPL_STUB );

TCC_STATE_LIST_API(string, include_paths);
TCC_STATE_LIST_API(string, sysinclude_paths);
TCC_STATE_LIST_API(string, library_paths);
TCC_STATE_LIST_API(string, crt_paths);
TCC_STATE_LIST_API(string, target_deps);
TCC_STATE_LIST_API(string, files);



#undef TCC_STATE_LIST_API
#undef TCC_STATE_LIST_TYPE

#else
	#error TCC_STATE_LIST_API, TCC_STATE_LIST_TYPE not defined!
#endif

