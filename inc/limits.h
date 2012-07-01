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
#ifndef __CCAPRICE_LIMITS_HDR__
#define __CCAPRICE_LIMITS_HDR__
#include <ccaprice.h>
#include <bits/limits.h>

/*
 * Macro to make min constants universal.  This determins min sizes from
 * max sizes (which are platform specific).
 */
#define __CCAPRICE_MIN(X) ((-X##_MAX)-1)

/*
 * Universal min constants; we don't specify CHAR here because of the, odd
 * cases where compile compilers support -unsigned-char and define a macro
 * which overrides the constants.
 */
#define  SHRT_MIN     __CCAPRICE_MIN(SHRT)
#define  SCHAR_MIN    __CCAPRICE_MIN(SCHAR)
#define  LLONG_MIN    __CCAPRICE_MIN(LLONG)
#define  LONG_MIN     __CCAPRICE_MIN(LONG)
#define  INT_MIN      __CCAPRICE_MIN(INT)

#ifdef __CHAR_UNSIGNED__
#   define CHAR_MIN 0
#   define CHAR_MAX 255
#else
#   define CHAR_MIN (-128)
#   define CHAR_MAX 127
#endif

/* Universal pretyt much! */
#define CHAR_BIT   8
#define SCHAR_MAX  127
#define UCHAR_MAX  255
#define SHRT_MAX   0x7fff
#define USHRT_MAX  0xffff
#define INT_MAX    0x7fffffff
#define UINT_MAX   0xffffffffU
#define ULONG_MAX  (2UL*LONG_MAX+1)
#define ULLONG_MAX (2ULL*LLONG_MAX+1)

#endif
