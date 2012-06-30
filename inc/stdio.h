/*
 * Copyright (C) 2012
 *  Dale Weiler
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
#ifndef __CCAPRICE_STDIO_HDR__
#define __CCAPRICE_STDIO_HDR__
#include <ccaprice.h>
#include <bits/types.h>

#define __CCAPRICE_STDIO_FILE_BUFFER_LEN 2048
typedef struct ccaprice_file {
 int    fd;
 int    eof;
 int    self; /* SELF'ed itself? */
 int    err;
 char   buffer_dat[__CCAPRICE_STDIO_FILE_BUFFER_LEN];
 size_t buffer_pos;
}  FILE;

#define EOF -1
#define stdout          __ccaprice_stdout()  /* because symbol of alignment issues */
#define stdin           __ccaprice_stdin ()  /* because symbol of alignment issues */
__CCAPRICE_EXPORT FILE *__ccaprice_stdout(); /* because symbol of alignment issues */
__CCAPRICE_EXPORT FILE *__ccaprice_stdin (); /* because symbol of alignment issues */

__CCAPRICE_EXPORT int    fclose(FILE *);
__CCAPRICE_EXPORT int    feof  (FILE *);
__CCAPRICE_EXPORT int    fflush(FILE *);
__CCAPRICE_EXPORT FILE * fopen (const char *, const char *);
__CCAPRICE_EXPORT int    fputc (int, FILE*);
__CCAPRICE_EXPORT int    fputs (const char *, FILE*);
__CCAPRICE_EXPORT size_t fwrite(const void *, size_t, size_t, FILE*);
__CCAPRICE_EXPORT int    fputs (const char *, FILE*);
__CCAPRICE_EXPORT int    puts  (const char*);
__CCAPRICE_EXPORT int    remove(const char*);
__CCAPRICE_EXPORT int    printf(const char *, ...);

#endif /* !CCAPRICE_STDIO_HDR      */
