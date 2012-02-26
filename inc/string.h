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
#ifndef  CCAPRICE_STRING_HDR
#define  CCAPRICE_STRING_HDR
#include "ccaprice.h"
#include "stddef.h"    /* size_t */

/* Copying */
CCAPRICE_EXPORT void   *memcpy (void*, const void*, register size_t);
CCAPRICE_EXPORT void   *memmove(void*, const void*, register size_t);
CCAPRICE_EXPORT char   *strncpy(char*, const char*, register size_t);
CCAPRICE_EXPORT char   *strcpy (char*, const char*);
/* Concatenation */
CCAPRICE_EXPORT char   *strncat(char*, const char*, register size_t);
CCAPRICE_EXPORT char   *strcat (char*, const char*);

/* Comparision */
CCAPRICE_EXPORT int     memcmp (const void*, const void*, register size_t);
CCAPRICE_EXPORT int     strncmp(const char*, const char*, register size_t);
CCAPRICE_EXPORT int     strcmp (const char*, const char*);

/* Searching */
CCAPRICE_EXPORT void   *memchr (const void*, int, register size_t);
CCAPRICE_EXPORT char   *strchr (const char*, int);
CCAPRICE_EXPORT char   *strrchr(const char*, int);
CCAPRICE_EXPORT char   *strstr (const char*, const char*);
CCAPRICE_EXPORT char   *strpbrk(const char*, const char*);
CCAPRICE_EXPORT size_t  strcspn(const char*, const char*);
CCAPRICE_EXPORT size_t  strspn (const char*, const char*);
CCAPRICE_EXPORT char   *strtok (char *, const char*);

/* Others */
CCAPRICE_EXPORT char   *strerror(int);
CCAPRICE_EXPORT void   *memset  (void *, int, register size_t);
CCAPRICE_EXPORT size_t  strlen  (const char*);


/*
 * Fast bit-scan-forward table
 */
#define CCAPRICE_BSF_TABLE_EXPAND \
	7,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0, \
	5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0, \
	6,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0, \
	5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0, \
	7,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0, \
	5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0, \
	6,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0, \
	5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0

#endif /* !CCAPRICE_STRING_HDR */
