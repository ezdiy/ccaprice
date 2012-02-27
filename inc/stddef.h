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
#ifndef CCAPRICE_STDDEF_HDR
#define CCAPRICE_STDDEF_HDR
#include "ccaprice.h"

/*
 * Only tage advantage of type attributes if the compiler supports it.
 * Thankfully PathScale/EkoPath/Clang/GCC are all backwards compatible
 * in this regard.
 */
#if ((__COMPID__ == CCAPRICE_COMPILER_EKOPATH) || \
     (__COMPID__ == CCAPRICE_COMPILER_CLANG)   || \
     (__COMPID__ == CCAPRICE_COMPILER_GCC))
#	define REG8  __QI__
#	define REG16 __HI__
#	define REG32 __SI__
#	define REG64 __DI__
#	define _U_INT_(S) typedef unsigned int ccaprice_uint_##S __attribute__( (__mode__( REG##S )))
#else
	/*
	 * There is not much fall back we can assume from compilers at
	 * this point.  To our advantage <sys/types.h> defines some odd
	 * and (not guranteed) types that we could try to use.
	 */
#	warning "[ccaprice] Experimental feature selected: might not work"
#	define _U_INT_(S) typedef u_int##S##_t ccaprice_uint_##S
#endif

/*
 * Create the ccaprice_uint_* types for re-typedef to correct types
 * later.  These are guranteed to always be 8/16/32/64 bits on all
 * platforms.
 */
_U_INT_(8);
_U_INT_(16);
_U_INT_(32);
_U_INT_(64);
#undef REG8
#undef REG16
#undef REG32
#undef REG64
#undef _U_INT_

typedef ccaprice_uint_8  uint8_t;
typedef ccaprice_uint_16 uint16_t;
typedef ccaprice_uint_32 uint32_t;
typedef ccaprice_uint_64 uint64_t;

#if defined (__PTRDIFF_TYPE__)
	typedef signed   __PTRDIFF_TYPE__ intptr_t;
	typedef unsigned __PTRDIFF_TYPE__ uintptr_t;
#else
	/*
	 * These are correct for X86 and x86_64.  Just a thought
	 * there should be a more correct way to fallbacking if
	 * __PTRDIFF_TYPE__ is not defined.  TODO!
	 */
	typedef signed   long             intptr_t;
	typedef unsigned long             uintptr_t;
#endif

/*
 * We handle null correctly here.
 * In GNUG mode there is a builtin __null we can
 * use to our advantage.
 * 
 * Otherwise we make NULL the correct constant according
 * to the language at play.
 */
#if !defined(NULL)
#	if defined(__GNUG__) /* C++ */
#		define NULL __null
#	else
#		if defined(__cplusplus)
		/*
		 * C++ Specification says that NULL should be 0
		 * opposed to C which defined it as ((void*)0).
		 */
#			define NULL 0
#		else
#			define NULL ((void*)0)
#		endif
#	endif
#endif

#if !defined(offsetof)
#	if ((__COMPID__ == CCAPRICE_COMPILER_EKOPATH) || \
	    (__COMPID__ == CCAPRICE_COMPILER_CLANG)   || \
	    (__COMPID__ == CCAPRICE_COMPILER_GCC))
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

/*
 * Generate static assertions only when compiling the library.
 * There might be something broken with someones toolchain if
 * these ever assert.
 */
#if defined(CCAPRICE_CP)
	CCAPRICE_COMPILE_TIME_ASSERT(uint16_t, sizeof(uint16_t) == 2);
	CCAPRICE_COMPILE_TIME_ASSERT(uint32_t, sizeof(uint32_t) == 4);
	CCAPRICE_COMPILE_TIME_ASSERT(uint64_t, sizeof(uint64_t) == 8);
#endif
#endif /* !CCAPRICE_STDDEF_HDR */
