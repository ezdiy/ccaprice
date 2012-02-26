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

/*
 * The makefile should set a -D__INFO__=, if it doesn't we'll handle
 * defining __INFO__ to a string literal explaining that the build
 * did not include information.
 */
#ifndef __INFO__
#define __INFO__ "No information Specified during build"
#endif

#if   defined(__GNUC__)
#	define CCAPRICE_BUILD_COMP "GCC"
#	define CCAPRICE_USED __attribute__((__used__))
#elif defined(__clang__)
#	define CCAPRICE_BUILD_COMP "CLANG"
#	define CCAPRICE_USED __attribute__((__used__))
#elif defined(__TINYC__) 
#	define CCAPRICE_BUILD_COMP "TINYC"
	/*
	 * TinyC doesn't have a __used__ attribute. Instead lets setup
	 * a section called .used for it.  It's guranteed not to be
	 * removed then.
	 */
#	define CCAPRICE_USED __attribute__((__section__(".used")))
#else
#	error "Unsupported compiler"
#endif

#define STRING_STRLEN_OPTIMAL 0x01
#define STRING_MEMCHR_OPTIMAL 0x01
#define STRING_MEMCPY_OPTIMAL 0x01
#define STRING_MEMSET_OPTIMAL 0x01

#define STDLIB_RAND_OPTIMAL   0x01

#ifdef __SSE2__
	#define STRING_STRLEN_OPTIMAL_SSE2
	#define STRING_MEMCHR_OPTIMAL_SSE2
	#define STRING_MEMCPY_OPTIMAL_SSE2
	#define STRING_MEMSET_OPTIMAL_SSE2
	
	#define STDLIB_RAND_OPTIMAL_SSE2
#endif

#define CCAPRICE_COMPILE_TIME_ASSERT(name, x) \
	typedef int CompileTimeAssertFailed_##name[(x)?1:-1]

#if defined(CCAPRICE_TARGET_X86_64) || defined(__x86_64__)
	#define STRING_STRLEN_X86_64
	#define STRING_MEMCHR_X86_64
	#define STRING_MEMCPY_X86_64
	#define STRING_MEMSET_X86_64
	#include <stdint.h>
	#include <stddef.h>
	typedef int                 ssize_t;
#elif defined(CCAPRICE_TARGET_X86) || defined(__x86__)
	#define _LARGEFILE64_SOURCE /* EXTENSION */
	
	#define STRING_STRLEN_X86
	#define STRING_MEMCHR_X86
	#define STRING_MEMCPY_X86
	#define STRING_MEMSET_X86
	#include <stdint.h>
	#include <stddef.h>
	typedef long                ssize_t;
#else
	#error "[ccaprice] Target not supported"
#endif /* !CCAPRICE_TARGET_X86_64 */

/* Ensure type sizes */
CCAPRICE_COMPILE_TIME_ASSERT(uint16_t, sizeof(uint16_t) == 2);
CCAPRICE_COMPILE_TIME_ASSERT(uint32_t, sizeof(uint32_t) == 4);
CCAPRICE_COMPILE_TIME_ASSERT(uint64_t, sizeof(uint64_t) == 8);

#define CCAPRICE_INTERNAL_TYPE(TYPE, NAME)       \
	extern TYPE NAME
#define CCAPRICE_INTERNAL_FUNC(TYPE, NAME, LIST) \
	CCAPRICE_INTERNAL_TYPE(TYPE,NAME) LIST

#ifdef CCAPRICE_CP
#	define CCAPRICE_EXPORT
#else
#	define CCAPRICE_EXPORT extern
#endif /* !CCAPRICE_COMPILING    */

CCAPRICE_EXPORT const char *ccaprice_build_date;
CCAPRICE_EXPORT const char *ccaprice_build_info;
#ifdef CCAPRICE_EXTENSIONS
#	define CCAPRICE_BUILD_DATE ccaprice_build_date
#	define CCAPRICE_BUILD_INFO ccaprice_build_info
#endif

#endif /* !CCAPRICE_CCAPRICE_HDR */
