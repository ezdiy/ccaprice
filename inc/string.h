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
CCAPRICE_EXPORT void   *memchr (const void*, int, register size_t);
CCAPRICE_EXPORT char   *strchr (const char*, int);

/* Others */
CCAPRICE_EXPORT void   *memset (void *, int, register size_t);
CCAPRICE_EXPORT size_t  strlen (const char*);


/*
 * Fast bit-scan-forward table
 */
#define CCAPRICE_BSF_TABLE_EXPAND \
	7,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0, \
	5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0, \
	6,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0, \
	5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0, \
	7,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0, \
	5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0, \
	6,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0, \
	5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0

#endif /* !CCAPRICE_STRING_HDR */
