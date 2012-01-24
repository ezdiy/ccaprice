/*
 * Copyright (C) 2012 
 * 	Dale Weiler
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef CCAPRICE_STDIO_HDR
#define CCAPRICE_STDIO_HDR
#include "ccaprice.h"
#include "src/crt/runtime.h" /* sycalls */

#define CCAPRICE_STDIO_FILE_BUFFER_LEN 2048
typedef struct ccaprice_file {
	int    fd;
	int    eof;
	int    self; /* SELF'ed itself? */
	int    err;
	char   buffer_dat[CCAPRICE_STDIO_FILE_BUFFER_LEN];
	size_t buffer_pos;
}  FILE;

#define EOF -1
#define stdout        ccaprice_stdout()  /* because symbol of alignment issues */
#define stdin         ccaprice_stdin ()  /* because symbol of alignment issues */
CCAPRICE_EXPORT FILE *ccaprice_stdout(); /* because symbol of alignment issues */
CCAPRICE_EXPORT FILE *ccaprice_stdin (); /* because symbol of alignment issues */

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
