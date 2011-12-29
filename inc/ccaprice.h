#ifndef CCAPRICE_CCAPRICE_HDR
#define CCAPRICE_CCAPRICE_HDR

/* options */
#define STRING_STRLEN_OPTIMAL
#define STRING_MEMCHR_OPTIMAL
#define STRING_MEMCPY_OPTIMAL
#define STRING_STRLEN_X86_64
#define STRING_MEMCHR_X86_64
#define STRING_MEMCPY_X86_64

#ifdef CCAPRICE_COMPILING
#	define CCAPRICE_EXPORT
#else
#	define CCAPRICE_EXPORT extern
#endif /* !CCAPRICE_COMPILING    */
#endif /* !CCAPRICE_CCAPRICE_HDR */
