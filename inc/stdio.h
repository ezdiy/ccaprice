#ifndef CCAPRICE_STDIO_HDR
#define CCAPRICE_STDIO_HDR
#include "ccaprice.h"
typedef struct ccaprice_file {
	int    fd;
} __attribute__((aligned (16))) FILE;

#define stdout (ccaprice_stdout())
#define stdin  (ccaprice_stdin ())

CCAPRICE_EXPORT int puts(const char *);
CCAPRICE_EXPORT FILE *ccaprice_stdout();
CCAPRICE_EXPORT FILE *ccaprice_stdin ();

#endif /* !CCAPRICE_STDIO_HDR      */
