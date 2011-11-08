#ifndef  CCAPRICE_STRING_HDR
#define  CCAPRICE_STRING_HDR
#include "ccaprice.h"
#include "stddef.h"  /* size_t */
#include <xmmintrin.h>

/* Copying */
CCAPRICE_EXPORT void   *memcpy (void*, const void*, register size_t);
CCAPRICE_EXPORT void   *memmove(void*, const void*, register size_t);
CCAPRICE_EXPORT char   *strncpy(char*, const char*, register size_t);
CCAPRICE_EXPORT char   *strcpy (char*, const char*);

/* Concatenation */
CCAPRICE_EXPORT char   *strncat(char*, const char*, register size_t);
CCAPRICE_EXPORT char   *strcat (char*, const char*);

/* Comparision */
CCAPRICE_EXPORT int     memcmp (const void*, const void*, register size_t);
CCAPRICE_EXPORT int     strncmp(const char*, const char*, register size_t);
CCAPRICE_EXPORT int     strcmp (const char*, const char*);

/* Searching */
CCAPRICE_EXPORT void    *memchr(const void*, int, register size_t);
CCAPRICE_EXPORT char    *strchr(const char*, int);

/* Others */
CCAPRICE_EXPORT size_t  strlen (const char*);

#endif /* !CCAPRICE_STRING_HDR */
