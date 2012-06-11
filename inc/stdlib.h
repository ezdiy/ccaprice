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
#ifndef __CCAPRICE_STDLIB_HDR__
#define __CCAPRICE_STDLIB_HDR__
#include "ccaprice.h"

/*
 * Handle size_t and NULL according to standard.  By themselfs as new
 * types / macros alltogether.  You're not allowed to include other
 * standard headers with other standard headers.
 */
#if !defined(__CCAPRICE_TYPE__SIZE_T_DEFINED)
	typedef  __CCAPRICE_TYPE__SIZE_T size_t;
#	define   __CCAPRICE_TYPE__SIZE_T_DEFINED
#endif
#ifdef  NULL
#undef  NULL
#endif
#define NULL __CCAPRICE_NULL

#define EXIT_SUCCESS (0x00)
#define EXIT_FAILURE (0xFF)
#define CHAR_BIT      8

#define __CCAPRICE_SIGNEXTEND(V) \
    union {                      \
        int32_t W;               \
        struct {                 \
            int16_t L;           \
            int16_t H;           \
        } S;                     \
    } signext = { V }

#ifdef __CCAPRICE_EXTENSIONS
#	define MIN(X,Y) ({              \
    __CCAPRICE_SIGNEXTEND((X)-(Y)); \
    ((Y)+(((X)-(Y))& signext.S.H)); \
})
#	define MAX(X,Y) ({              \
    __CCAPRICE_SIGNEXTEND((Y)-(X)); \
    ((X)+(((Y)-(X))&~signext.S.H)); \
})
#endif

__CCAPRICE_EXPORT void  atexit (void (*)());
__CCAPRICE_EXPORT void  exit   (int);
__CCAPRICE_EXPORT void  abort  ();
__CCAPRICE_EXPORT int   raise  (int);
__CCAPRICE_EXPORT char* getenv (const char *);
__CCAPRICE_EXPORT void  qsort  (void *, size_t, size_t, int (*)(const void *, const void *));
__CCAPRICE_EXPORT void *bsearch(const void *, const void *, size_t, size_t, int(*)(const void *, const void *));

/* dynamic memory managment stuff */
__CCAPRICE_EXPORT void *malloc (size_t);
__CCAPRICE_EXPORT void *calloc (size_t, size_t);
__CCAPRICE_EXPORT void  free   (void*);
__CCAPRICE_EXPORT void *realloc(void *, size_t);

/* rand / srand */
__CCAPRICE_EXPORT void  srand(unsigned int);
__CCAPRICE_EXPORT int   rand();

#endif
