#ifndef CCAPRICE_CCAPRICE_HDR
#define CCAPRICE_CCAPRICE_HDR

/* options */
#define STRING_STRLEN_SSE
#define STRING_MEMCHR_SSE
#define STRING_MEMCPY_SSE

#ifdef CCAPRICE_COMPILING
#	define CCAPRICE_EXPORT
#else
#	define CCAPRICE_EXPORT extern
#endif /* !CCAPRICE_COMPILING    */
#endif /* !CCAPRICE_CCAPRICE_HDR */
