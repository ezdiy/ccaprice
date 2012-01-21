#ifndef CCAPRICE_STDIO_HDR
#define CCAPRICE_STDIO_HDR
#include "ccaprice.h"
typedef struct ccaprice_file {
	int    fd;
	char   buffer[2048];
	long   bufpos;
} FILE;

#ifdef CCAPRICE_TARGET_X86_64
typedef int ssize_t;
#elif defined(CCAPRICE_TARGET_X86)
typedef long ssize_t;


#endif /* !CCAPRUICE_TARGET_X86_64 */
#endif /* !CCAPRICE_STDIO_HDR      */
