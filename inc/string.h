#ifndef  CCAPRICE_STRING_HDR
#define  CCAPRICE_STRING_HDR
#include "ccaprice.h"
#include "stddef.h"  /* size_t */

CCAPRICE_EXPORT void *memcpy (void*, const void*, register size_t);
CCAPRICE_EXPORT void *memmove(void*, const void*, register size_t);
CCAPRICE_EXPORT char *strncpy(char*, const char*, register size_t);
CCAPRICE_EXPORT char *strcpy (char*, const char*);



#endif /* !CCAPRICE_STRING_HDR */
