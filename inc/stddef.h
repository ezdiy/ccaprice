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
#ifndef __CCAPRICE_STDDEF_HDR__
#define __CCAPRICE_STDDEF_HDR__
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


/*
 * We can just undef NULL if it already is.  There is something about
 * the whole setup of the standard headers that makes it annoying to
 * manage types.
 */
#ifdef  NULL
#undef  NULL
#endif
#define NULL __CCAPRICE_NULL

#if !defined(offsetof)
#	if ((__COMPID__ == __CCAPRICE_COMPILER_EKOPATH) || \
	    (__COMPID__ == __CCAPRICE_COMPILER_CLANG)   || \
	    (__COMPID__ == __CCAPRICE_COMPILER_GCC))
#		define offsetof(TYPE, MEMBER) __builtin_offsetof(TYPE, MEMBER)
#	else
		/*
		 * Unsafe fallback: This is actually undefined behaviour. However
		 * there are a wide range of compilers that make this code do what
		 * offsetof() is expected to do.
		 */
#		define offsetof(TYPE, MEMBER) ((size_t) &((TYPE*)0)->MEMBER)
#	endif
#endif

#if !defined(__CCAPRICE_TYPE__PTRDIFF_T_DEFINED)
    typedef  unsigned __CCAPRICE_TYPE_INTPTR_T ptrdiff_t;
#   define   __CCAPRICE_TYPE_PTRDIFF_T_DEFINED
#endif

#endif /* !CCAPRICE_STDDEF_HDR */
