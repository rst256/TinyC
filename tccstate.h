#ifndef _TCCSTATE_H
#define _TCCSTATE_H

struct TCCState {

    int verbose; /* if true, display some information during compilation */
    int nostdinc; /* if true, no standard headers are added */
    int nostdlib; /* if true, no standard libraries are added */
    int nocommon; /* if true, do not use common symbols for .bss data */
    int static_link; /* if true, static linking is performed */
    int rdynamic; /* if true, all symbols are exported */
    int symbolic; /* if true, resolve symbols in the current module first */
    int alacarte_link; /* if true, only link in referenced objects from archive */

    char *tcc_lib_path; /* CONFIG_TCCDIR or -B option */
    char *soname; /* as specified on the command line (-soname) */
    char *rpath; /* as specified on the command line (-Wl,-rpath=) */

    /* output type, see TCC_OUTPUT_XXX */
    int output_type;
    /* output format, see TCC_OUTPUT_FORMAT_xxx */
    int output_format;

    /* C language options */
    int char_is_unsigned;
    int leading_underscore;
    
    /* warning switches */
    int warn_write_strings;
    int warn_unsupported;
    int warn_error;
    int warn_none;
    int warn_implicit_function_declaration;

    /* compile with debug symbol (and use them if error during execution) */
    int do_debug;
#ifdef CONFIG_TCC_BCHECK
    /* compile with built-in memory and bounds checker */
    int do_bounds_check;
#endif

    addr_t text_addr; /* address of text section */
    int has_text_addr;

    unsigned long section_align; /* section alignment */

    char *init_symbol; /* symbols to call at load-time (not used currently) */
    char *fini_symbol; /* symbols to call at unload-time (not used currently) */
    
#ifdef TCC_TARGET_I386
    int seg_size; /* 32. Can be 16 with i386 assembler (.code16) */
#endif

    /* array of all loaded dlls (including those referenced by loaded dlls) */
    DLLReference **loaded_dlls;
    int nb_loaded_dlls;

    /* include paths */
    char **include_paths;
    int nb_include_paths;

    char **sysinclude_paths;
    int nb_sysinclude_paths;

    /* library paths */
    char **library_paths;
    int nb_library_paths;

    /* crt?.o object path */
    char **crt_paths;
    int nb_crt_paths;

    /* error handling */
    void *error_opaque;
    void (*error_func)(void *opaque, const char *msg);
    int error_set_jmp_enabled;
    jmp_buf error_jmp_buf;
    int nb_errors;

    /* output file for preprocessing (-E) */
    FILE *ppfp;

    /* for -MD/-MF: collected dependencies for this compilation */
    char **target_deps;
    int nb_target_deps;

    /* compilation */
    BufferedFile *include_stack[INCLUDE_STACK_SIZE];
    BufferedFile **include_stack_ptr;

    int ifdef_stack[IFDEF_STACK_SIZE];
    int *ifdef_stack_ptr;

    /* included files enclosed with #ifndef MACRO */
    int cached_includes_hash[CACHED_INCLUDES_HASH_SIZE];
    CachedInclude **cached_includes;
    int nb_cached_includes;

    /* #pragma pack stack */
    int pack_stack[PACK_STACK_SIZE];
    int *pack_stack_ptr;

    /* inline functions are stored as token lists and compiled last
       only if referenced */
    struct InlineFunc **inline_fns;
    int nb_inline_fns;

    /* sections */
    Section **sections;
    int nb_sections; /* number of sections, including first dummy section */

    Section **priv_sections;
    int nb_priv_sections; /* number of private sections */

    /* got & plt handling */
    Section *got;
    Section *plt;
    struct sym_attr *sym_attrs;
    int nb_sym_attrs;
    /* give the correspondance from symtab indexes to dynsym indexes */
    int *symtab_to_dynsym;

    /* temporary dynamic symbol sections (for dll loading) */
    Section *dynsymtab_section;
    /* exported dynamic symbol section */
    Section *dynsym;
    /* copy of the gobal symtab_section variable */
    Section *symtab;
    /* tiny assembler state */
    Sym *asm_labels;

#ifdef TCC_TARGET_PE
    /* PE info */
    int pe_subsystem;
    unsigned pe_file_align;
    unsigned pe_stack_size;
# ifdef TCC_TARGET_X86_64
    Section *uw_pdata;
    int uw_sym;
    unsigned uw_offs;
# endif
#endif

#ifdef TCC_IS_NATIVE
    /* for tcc_relocate */
    void *runtime_mem;
# ifdef HAVE_SELINUX
    void *write_mem;
    unsigned long mem_size;
# endif
# if !defined TCC_TARGET_PE && (defined TCC_TARGET_X86_64 || defined TCC_TARGET_ARM)
    /* write PLT and GOT here */
    char *runtime_plt_and_got;
    unsigned runtime_plt_and_got_offset;
#  define TCC_HAS_RUNTIME_PLTGOT
# endif
#endif

    /* used by main and tcc_parse_args only */
    char **files; /* files seen on command line */
    int nb_files; /* number thereof */
    int nb_libraries; /* number of libs thereof */
    char *outfile; /* output filename */
    char *option_m; /* only -m32/-m64 handled */
    int print_search_dirs; /* option */
    int option_r; /* option -r */
    int do_bench; /* option -bench */
    int gen_deps; /* option -MD  */
    char *deps_outfile; /* option -MF */
};

#endif //_TCCSTATE_H