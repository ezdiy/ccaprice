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
#include <stdarg.h> /*TODO: FIX! */

#define EOF -1
#define SEEK_SET (EOF      + 1)
#define SEEK_CUR (SEEK_SET + 1)
#define SEEK_END (SEEK_CUR + 1)

/* reserved */
#define __CCAPRICE_F_PERM  1
#define __CCAPRICE_F_NORD (1 << 2)
#define __CCAPRICE_F_NOWR (1 << 3)
#define __CCAPRICE_F_EOF  (1 << 4)
#define __CCAPRICE_F_ERR  (1 << 5)
#define __CCAPRICE_F_SVB  (1 << 6)

#define __CCAPRICE_UNGET   8
#define __CCAPRICE_BUFSIZE 1024

typedef struct __ccaprice_file {
    unsigned          flags;
    unsigned char    *buf;
    signed char       mode;
    signed char       lbf;
    size_t            buf_size;
    int               fd;
    
    /* buffering */
    unsigned char *rpos;
    unsigned char *rend;
    unsigned char *wpos;
    unsigned char *wend;
    unsigned char *base;
    
    
    /* function pointer callbacks */
    int    (*close)(struct __ccaprice_file *);
    size_t (*read) (struct __ccaprice_file *,       unsigned char *, size_t);
    size_t (*write)(struct __ccaprice_file *, const unsigned char *, size_t);
    off_t  (*seek) (struct __ccaprice_file *, off_t, int);
    
    /* it's also a linked list :P */
    struct __ccaprice_file *prev;
    struct __ccaprice_file *next;
    
    /* threading */
    int lock;
    
}  FILE;

extern FILE * const __ccaprice_stdout;
extern FILE * const __ccaprice_stdin ;
extern FILE * const __ccaprice_stderr;

#define stdout  (__ccaprice_stdout)
#define stdin   (__ccaprice_stdin )
#define stderr  (__ccaprice_stderr)

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
__CCAPRICE_EXPORT int  vfprintf(FILE *, const char *, va_list);
__CCAPRICE_EXPORT int   fprintf(FILE *, const char *, ...);

#endif /* !CCAPRICE_STDIO_HDR      */
