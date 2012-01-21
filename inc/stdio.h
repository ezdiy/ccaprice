#ifndef CCAPRICE_STDIO_HDR
#define CCAPRICE_STDIO_HDR
#include "ccaprice.h"
typedef struct ccaprice_file {
	int    fd;
	char   buffer[2048];
	long   bufpos;
} FILE;

#endif /* !CCAPRICE_STDIO_HDR */
