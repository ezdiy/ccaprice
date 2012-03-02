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
#ifndef CCAPRICE_STDLIB_HDR
#define CCAPRICE_STDLIB_HDR
#include "ccaprice.h"

/* 
 * Handle size_t and NULL according to standard.  By themselfs as new
 * types / macros alltogether.  You're not allowed to include other
 * standard headers with other standard headers.
 */
#if !defined(CCAPRICE_TYPE__SIZE_T_DEFINED)
	typedef  CCAPRICE_TYPE__SIZE_T size_t;
#	define   CCAPRICE_TYPE__SIZE_T_DEFINED
#endif
#ifdef  NULL
#undef  NULL
#endif
#define NULL CCAPRICE_NULL

#define EXIT_SUCCESS (0x00)
#define EXIT_FAILURE (0xFF)

#define CCAPRICE_SIGNEXTEND(V) \
    union {                    \
        int32_t W;             \
        struct {               \
            int16_t L;         \
            int16_t H;         \
        } S;                   \
    } signext = { V }

#ifdef CCAPRICE_EXTENSIONS
#	define MIN(X,Y) ({              \
    CCAPRICE_SIGNEXTEND((X)-(Y));   \
    ((Y)+(((X)-(Y))& signext.S.H)); \
})
#	define MAX(X,Y) ({              \
    CCAPRICE_SIGNEXTEND((Y)-(X));   \
    ((X)+(((Y)-(X))&~signext.S.H)); \
})
#endif

CCAPRICE_EXPORT void  atexit(void (*)());
CCAPRICE_EXPORT void  exit  (int);
CCAPRICE_EXPORT void  abort ();
CCAPRICE_EXPORT int   raise (int);
CCAPRICE_EXPORT char* getenv(const char *);

/* malloc / free */
CCAPRICE_EXPORT void *malloc(size_t);
CCAPRICE_EXPORT void *calloc(size_t, size_t);
CCAPRICE_EXPORT void  free  (void *);

/* rand / srand */
CCAPRICE_EXPORT void  srand(unsigned int);
CCAPRICE_EXPORT int   rand();

#endif
