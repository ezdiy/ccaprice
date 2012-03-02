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
#ifndef CCAPRICE_POSIX_STRINGS_HDR
#define CCAPRICE_POSIX_STRINGS_HDR
#include "inc/ccaprice.h"

#if !defined(CCAPRICE_TYPE__SIZE_T_DEFINED)
	typedef  CCAPRICE_TYPE__SIZE_T size_t;
#	define   CCAPRICE_TYPE__SIZE_T_DEFINED
#endif

CCAPRICE_EXPORT int   bcmp       (const void *, const void *, size_t); // alias to memcmp
CCAPRICE_EXPORT void  bcopy      (const void *, void *,       size_t); // alias to bcopy
CCAPRICE_EXPORT void  bzero      (void *,                     size_t); // memset(0)
CCAPRICE_EXPORT int   ffs        (int);  
CCAPRICE_EXPORT char *index      (const char *, int);                  // strchr
CCAPRICE_EXPORT char *rindex     (const char *, int);                  // strstr
CCAPRICE_EXPORT int   strcasecmp (const char *, const char *);
CCAPRICE_EXPORT int   strncasecmp(const char *, const char *, size_t);

#endif
