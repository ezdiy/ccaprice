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
#ifndef CCAPRICE_CCAPRICE_HDR
#define CCAPRICE_CCAPRICE_HDR

#define STRING_STRLEN_OPTIMAL
#define STRING_MEMCHR_OPTIMAL
#define STRING_MEMCPY_OPTIMAL
#define STRING_MEMSET_OPTIMAL

#ifdef __SSE2__
#define STRING_STRLEN_OPTIMAL_SSE2
#define STRING_MEMCHR_OPTIMAL_SSE2
#define STRING_MEMCPY_OPTIMAL_SSE2
#define STRING_MEMSET_OPTIMAL_SSE2
#endif

#define CCAPRICE_COMPILE_TIME_ASSERT(name, x) \
	typedef int CompileTimeAssertFailed_##name[(x)*2-1]

#if defined(CCAPRICE_TARGET_X86_64) || defined(__x86_64__)
	#define STRING_STRLEN_X86_64
	#define STRING_MEMCHR_X86_64
	#define STRING_MEMCPY_X86_64
	#define STRING_MEMSET_X86_64
	typedef unsigned char       uint8_t;
	typedef unsigned short      uint16_t;
	typedef unsigned int        uint32_t;
	typedef unsigned long       uint64_t;
	typedef uint64_t            intptr_t;
	typedef int                 int32_t;
	#if !defined(CCAPRICE_NO_SIZE_T) || defined(BSD)
	typedef unsigned int        size_t;
	typedef int                 ssize_t;
	#endif
#elif defined(CCAPRICE_TARGET_X86) || defined(__x86__)
	#define _LARGEFILE64_SOURCE /* EXTENSION */
	
	#define STRING_STRLEN_X86
	#define STRING_MEMCHR_X86
	#define STRING_MEMCPY_X86
	#define STRING_MEMSET_X86
	typedef unsigned char       uint8_t;
	typedef unsigned short      uint16_t;
	typedef unsigned int        uint32_t;
	typedef unsigned long long  uint64_t;
	typedef int                 int32_t;
	typedef uint64_t            intptr_t;
	#if !defined(CCAPRICE_NO_SIZE_T) || defined(BSD)
	typedef unsigned int        size_t;
	typedef long                ssize_t;
	#endif
#else
	#include <stdint.h>
#endif /* !CCAPRICE_TARGET_X86_64 */

#define CCAPRICE_BITS2BYTES(X) (X>>3)
#define CCAPRICE_BYTES2BITS(X) (X<<3)
/* Ensure type sizes */
CCAPRICE_COMPILE_TIME_ASSERT(uint16_t, sizeof(uint16_t) == CCAPRICE_BITS2BYTES(16));
CCAPRICE_COMPILE_TIME_ASSERT(uint32_t, sizeof(uint32_t) == CCAPRICE_BITS2BYTES(32));
CCAPRICE_COMPILE_TIME_ASSERT(uint64_t, sizeof(uint64_t) == CCAPRICE_BITS2BYTES(64));

#define CCAPRICE_INTERNAL_TYPE(TYPE, NAME)       \
	extern TYPE NAME
#define CCAPRICE_INTERNAL_FUNC(TYPE, NAME, LIST) \
	CCAPRICE_INTERNAL_TYPE(TYPE,NAME) LIST

#ifdef CCAPRICE_COMPILING
#	define CCAPRICE_EXPORT
#else
#	define CCAPRICE_EXPORT extern
#endif /* !CCAPRICE_COMPILING    */
#endif /* !CCAPRICE_CCAPRICE_HDR */
