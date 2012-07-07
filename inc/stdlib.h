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
#ifndef __CCAPRICE_STDLIB_HDR__
#define __CCAPRICE_STDLIB_HDR__
#include <ccaprice.h>
#include <bits/types.h>

#ifdef  NULL
#undef  NULL
#endif
#define NULL __CCAPRICE_NULL

#define EXIT_SUCCESS (0x00)
#define EXIT_FAILURE (0xFF)
#define CHAR_BIT      8

#define __CCAPRICE_SIGNEXTEND(V)  \
    union {                       \
        int32_t W;                \
        struct {                  \
            int16_t L;            \
            int16_t H;            \
        } S;                      \
    } signext = { V }

/*
 * Used to implement atoi, atol, atoll
 */
#define __CCAPRICE_STR2NUMERIC(T,S) \
    T   r=0;                        \
    int n=0;                        \
    while (isspace(*S)) {           \
        S++;                        \
    }                               \
    switch (*S) {                   \
        case '-': n=1;              \
        case '+': S++;              \
    }                               \
    while (isdigit(*S)) {           \
        r = r * 10 - (*S++-'0');    \
    }                               \
    return n?r:-r
    
/*
 * Used to implement abs, labs, llabs
 */
#define __CCAPRICE_ABS(T, S)        \
    return (T)((S>0)?S:-S)
    
    
/*
 * Used to implement div, ldiv, lldiv
 */
#define __CCAPRICE_DIV(T, S1, S2)   \
    return (T){S1/S2, S1%S2}

#ifdef __CCAPRICE_EXTENSIONS
# define MIN(X,Y) ({                \
    __CCAPRICE_SIGNEXTEND((X)-(Y)); \
    ((Y)+(((X)-(Y))& signext.S.H)); \
})
# define MAX(X,Y) ({                \
    __CCAPRICE_SIGNEXTEND((Y)-(X)); \
    ((X)+(((Y)-(X))&~signext.S.H)); \
})
#endif

/*
 * I wonder if C++ has any template specialized versions of these
 * like div<T>.  If it does these will need to be __cplusplus protected
 * for sanity reasons.
 */
typedef struct { int       quot, rem; } div_t;
typedef struct { long      quot, rem; } ldiv_t;
typedef struct { long long quot, rem; } lldiv_t;

__CCAPRICE_EXPORT void      abort  ();
__CCAPRICE_EXPORT int       abs    (int);
__CCAPRICE_EXPORT int       atoi   (const char *);
__CCAPRICE_EXPORT long      atol   (const char *);
__CCAPRICE_EXPORT long long atoll  (const char *);
__CCAPRICE_EXPORT void     *bsearch(const void *, const void *, size_t, size_t, int(*)(const void *, const void *));
__CCAPRICE_EXPORT div_t     div    (int, int);
__CCAPRICE_EXPORT void      exit   (int);
__CCAPRICE_EXPORT void      atexit (void (*)());
__CCAPRICE_EXPORT int       raise  (int);
__CCAPRICE_EXPORT char     *getenv (const char *);
__CCAPRICE_EXPORT long      labs   (long);
__CCAPRICE_EXPORT ldiv_t    ldiv   (long, long);
__CCAPRICE_EXPORT long long llabs  (long long);
__CCAPRICE_EXPORT lldiv_t   lldiv  (long long, long long);
__CCAPRICE_EXPORT void     *malloc (size_t);
__CCAPRICE_EXPORT void     *calloc (size_t, size_t);
__CCAPRICE_EXPORT void      free   (void*);
__CCAPRICE_EXPORT void     *realloc(void *, size_t);
__CCAPRICE_EXPORT int       puts   (const char *);
__CCAPRICE_EXPORT void      qsort  (void *, size_t, size_t, int (*)(const void *, const void *));
__CCAPRICE_EXPORT void      srand  (unsigned int);
__CCAPRICE_EXPORT int       rand   ();

#endif
