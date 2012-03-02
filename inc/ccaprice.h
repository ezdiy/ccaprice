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
 * When not compiling and including we need to determine
 * the architecture at compile-time without asking the
 * user to pass any macro to the command line build line
 * this is exactly what this does.
 */
#if !defined(CCAPRICE_CP)
#if defined(__amd64__)     || \
    defined(__amd64)       || \
    defined(__x86_64__)    || \
    defined(__x86_64)      || \
    defined(_M_X64)
	#define CCAPRICE_TARGET_X86_64
#else
#if defined(i386)          || \
    defined(__i386__)      || \
    defined(__i486__)      || \
    defined(__i586__)      || \
    defined(__i686__)      || \
    defined(__i386)        || \
    defined(__IA32__)      || \
    defined(_M_IX86)       || \
    defined(__X86__)       || \
    defined(_X86_)         || \
    defined(__THW_INTEL__) || \
    defined(__I86__)       || \
    defined(__INTEL__)
	#define CCAPRICE_TARGET_X86
#endif
#endif
#endif
/*
 * The makefile should set a -D__INFO__=, if it doesn't we'll handle
 * defining __INFO__ to a string literal explaining that the build
 * did not include information.
 */
#if !defined(__INFO__)
#	define __INFO__ "No information Specified during build"
#endif
/* cannot be enumerated required by more preprocessing */
#define CCAPRICE_COMPILER_EKOPATH 0xFF0000
#define CCAPRICE_COMPILER_CLANG   0x00FF00
#define CCAPRICE_COMPILER_GCC     0x0000FF

#if defined(__PATHCC__)
#	define __COMP__   "EKOPATH"
#	define __COMPID__ CCAPRICE_COMPILER_EKOPATH
#	define CCAPRICE_USED __attribute__((__used__))
#elif defined(__clang__)
#	define __COMP__   "CLANG"
#	define __COMPID__ CCAPRICE_COMPILER_CLANG
#	define CCAPRICE_USED __attribute__((__used__))
#elif defined(__GNUC__)
#	define __COMP__   "GCC"
#	define __COMPID__ CCAPRICE_COMPILER_GCC
#	define CCAPRICE_USED __attribute__((__used__))
#else
#	error "Unsupported compiler"
#endif

#if !defined(CCAPRICE_NAIVE)
#	define STRING_STRLEN_OPTIMAL 0x01
#	define STRING_MEMCHR_OPTIMAL 0x01
#	define STRING_MEMCPY_OPTIMAL 0x01
#	define STRING_MEMSET_OPTIMAL 0x01
#	define STDLIB_RANDOM_OPTIMAL 0x01
#	if defined(__SSE2__)
#		define STRING_STRLEN_OPTIMAL_SSE2
#		define STRING_MEMCHR_OPTIMAL_SSE2
#		define STRING_MEMCPY_OPTIMAL_SSE2
#		define STRING_MEMSET_OPTIMAL_SSE2
#		define STDLIB_RANDOM_OPTIMAL_SSE2
#	endif
#endif

#define CCAPRICE_COMPILE_TIME_ASSERT(name, x) \
	typedef int CompileTimeAssertFailed_##name[(x)?1:-1]

/*
 * Almost every GCC-like compiler has __SIZE_TYPE__ defined to be used
 * safely by library implementators.  Otherwise we fall back to a lame
 * long unsigned int which is most likely correct for all systems.
 */
#if defined(__SIZE_TYPE__)
#	define CCAPRICE_TYPE__SIZE_T __SIZE_TYPE__
#else
#	warning "[ccaprice] no __SIZE_TYPE__ found, using long unsigned int (could fail)"
#	define CCAPRICR_TYPE__SIZE_T long unsigned int
#endif
/*
 * We handle null correctly here.
 * In GNUG mode there is a builtin __null we can
 * use to our advantage.
 * 
 * Otherwise we make NULL the correct constant according
 * to the language at play.
 */
#if defined(__GNUG__) /* C++ */
#	define CCAPRICE_NULL __null
#else
#	if defined(__cplusplus)
		/*
		 * C++ Specification says that NULL should be 0
		 * opposed to C which defines it as ((void*)0).
		 */
#		define CCAPRICE_NULL 0
#	else
#		define CCAPRICE_NULL ((void*)0)
#	endif
#endif

#if defined(CCAPRICE_TARGET_X86_64)
#	define STRING_STRLEN_X86_64
#	define STRING_MEMCHR_X86_64
#	define STRING_MEMCPY_X86_64
#	define STRING_MEMSET_X86_64
#elif defined(CCAPRICE_TARGET_X86)
#	define _LARGEFILE64_SOURCE
	
#	define STRING_STRLEN_X86
#	define STRING_MEMCHR_X86
#	define STRING_MEMCPY_X86
#	define STRING_MEMSET_X86
#else
#	error "[ccaprice] Target not supported"
#endif /* !CCAPRICE_TARGET_X86_64 */

#define CCAPRICE_INTERNAL_TYPE(TYPE, NAME)       extern TYPE NAME
#define CCAPRICE_INTERNAL_FUNC(TYPE, NAME, LIST) CCAPRICE_INTERNAL_TYPE(TYPE,NAME) LIST

#if defined(CCAPRICE_CP)
#	define CCAPRICE_EXPORT
#else
#	define CCAPRICE_EXPORT extern
#endif

CCAPRICE_EXPORT const char *ccaprice_build_date;
CCAPRICE_EXPORT const char *ccaprice_build_info;
CCAPRICE_EXPORT const char *ccaprice_build_comp;
CCAPRICE_EXPORT const char *ccaprice_build_time;
CCAPRICE_EXPORT const char *ccaprice_build_host;
#if defined(CCAPRICE_EXTENSIONS)
#	define CCAPRICE_BUILD_DATE ccaprice_build_date
#	define CCAPRICE_BUILD_INFO ccaprice_build_info
#	define CCAPRICE_BUILD_COMP ccaprice_build_comp
#	define CCAPRICE_BUILD_TIME ccaprice_build_time
#	define CCAPRICE_BUILD_HOST ccaprice_build_host
#endif
#endif
