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
#ifndef __CCAPRICE_POSIX_STRINGS_HDR__
#define __CCAPRICE_POSIX_STRINGS_HDR__
#include "inc/ccaprice.h"

#if !defined(__CCAPRICE_TYPE__SIZE_T_DEFINED)
	typedef  __CCAPRICE_TYPE__SIZE_T size_t;
#	define   __CCAPRICE_TYPE__SIZE_T_DEFINED
#endif

__CCAPRICE_EXPORT int   bcmp       (const void *, const void *, size_t); // alias to memcmp
__CCAPRICE_EXPORT void  bcopy      (const void *, void *,       size_t); // alias to bcopy
__CCAPRICE_EXPORT void  bzero      (void *,                     size_t); // memset(0)
__CCAPRICE_EXPORT int   ffs        (int);
__CCAPRICE_EXPORT char *index      (const char *, int);                  // strchr
__CCAPRICE_EXPORT char *rindex     (const char *, int);                  // strstr
__CCAPRICE_EXPORT int   strcasecmp (const char *, const char *);
__CCAPRICE_EXPORT int   strncasecmp(const char *, const char *, size_t);

#endif
