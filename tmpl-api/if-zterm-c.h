
#define TCC_STATE_LIST_TYPE(TYPE, ITEM_TYPE, FUNC_COPY, FUNC_REF) \
	API_DEF( typedef ITEM_TYPE * TYPE##_zlist_t ) \
	ZLIST_BUILDER(TYPE##_zlist_build, TYPE##_zlist_t, ITEM_TYPE, FUNC_COPY); \
	ZLIST_BUILDER(TYPE##_zlistref_build, TYPE##_zlist_t, ITEM_TYPE, FUNC_REF)


#define TCC_STATE_LIST_API_HELPER(TYPE, CONSTR_REF, CONSTR_COPY, NAME) \
	PUB_FUNC TYPE tcc_get_##NAME(TCCState *s) API_IMPL(  \
		return CONSTR_REF(s->nb_##NAME, s->NAME); \
	) \
	PUB_FUNC TYPE tcc_getref_##NAME(TCCState *s) API_IMPL(  \
		return CONSTR_COPY(s->nb_##NAME, s->NAME); \
	) \
	PUB_FUNC int tcc_##NAME##_count(TCCState *s) API_IMPL(  \
		return s->nb_##NAME; \
	) 
#define TCC_STATE_LIST_API(TYPE, NAME) \
	TCC_STATE_LIST_API_HELPER(TYPE##_zlist_t, TYPE##_zlist_build, TYPE##_zlistref_build, NAME)
	
#define TCC_LIST_COUNT(NAME, TCC) tcc_##NAME##_count(TCC)
#define TCC_LIST_REF(NAME, TCC) tcc_getref_##NAME(TCC)
#define TCC_LIST(NAME, TCC) tcc_get_##NAME(TCC)

