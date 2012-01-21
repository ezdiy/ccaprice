#ifndef CCAPRICE_STDIO_HDR
#define CCAPRICE_STDIO_HDR
#include "ccaprice.h"
#include "src/crt/runtime.h" /* sycalls */
typedef struct ccaprice_file {
	int    fd;
	char   buffer_dat[1024];
	size_t buffer_pos;
}  FILE;

#define EOF -1
#define stdout (ccaprice_stdout())       /* because symbol of alignment issues */
#define stdin  (ccaprice_stdin ())       /* because symbol of alignment issues */
CCAPRICE_EXPORT FILE *ccaprice_stdout(); /* because symbol of alignment issues */
CCAPRICE_EXPORT FILE *ccaprice_stdin (); /* because symbol of alignment issues */

extern FILE   ccaprice_stdio_file_dat[1024];
extern size_t ccaprice_stdio_file_pos;

CCAPRICE_EXPORT int    fclose(FILE *);
CCAPRICE_EXPORT int    fflush(FILE *);
CCAPRICE_EXPORT FILE * fopen (const char *, const char *);
CCAPRICE_EXPORT int    fputc (int, FILE*);
CCAPRICE_EXPORT int    fputs (const char *, FILE*);
CCAPRICE_EXPORT size_t fwrite(const void *, size_t, size_t, FILE*);
CCAPRICE_EXPORT int    fputs (const char *, FILE*);

#endif /* !CCAPRICE_STDIO_HDR      */
