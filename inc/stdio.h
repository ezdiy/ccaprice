#ifndef CCAPRICE_STDIO_HDR
#define CCAPRICE_STDIO_HDR
#include "ccaprice.h"
#include "src/crt/runtime.h" /* sycalls */

#define CCAPRICE_STDIO_FILE_BUFFER_LEN 2048
typedef struct ccaprice_file {
	int    fd;
	int    eof;
	int    err;
	char   buffer_dat[CCAPRICE_STDIO_FILE_BUFFER_LEN];
	size_t buffer_pos;
}  FILE;

#define EOF -1
#define stdout        ccaprice_stdout()  /* because symbol of alignment issues */
#define stdin         ccaprice_stdin ()  /* because symbol of alignment issues */
CCAPRICE_EXPORT FILE *ccaprice_stdout(); /* because symbol of alignment issues */
CCAPRICE_EXPORT FILE *ccaprice_stdin (); /* because symbol of alignment issues */

extern FILE   ccaprice_stdio_file_dat[CCAPRICE_STDIO_FILE_BUFFER_LEN];
extern size_t ccaprice_stdio_file_pos;

CCAPRICE_EXPORT int    fclose(FILE *);
CCAPRICE_EXPORT int    feof  (FILE *);
CCAPRICE_EXPORT int    fflush(FILE *);
CCAPRICE_EXPORT FILE * fopen (const char *, const char *);
CCAPRICE_EXPORT int    fputc (int, FILE*);
CCAPRICE_EXPORT int    fputs (const char *, FILE*);
CCAPRICE_EXPORT size_t fwrite(const void *, size_t, size_t, FILE*);
CCAPRICE_EXPORT int    fputs (const char *, FILE*);
CCAPRICE_EXPORT int    puts  (const char*);

#endif /* !CCAPRICE_STDIO_HDR      */
