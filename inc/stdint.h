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
#ifndef __CCAPRICE_STDINT_HDR__
#define __CCAPRICE_STDINT_HDR__
#include "ccaprice.h"
/*
 * Only tage advantage of type attributes if the compiler supports it.
 * Thankfully PathScale/EkoPath/Clang/GCC are all backwards compatible
 * in this regard.
 */
#if ((__COMPID__ == __CCAPRICE_COMPILER_EKOPATH) || \
     (__COMPID__ == __CCAPRICE_COMPILER_CLANG)   || \
     (__COMPID__ == __CCAPRICE_COMPILER_GCC))
#	define __REG8  __QI__
#	define __REG16 __HI__
#	define __REG32 __SI__
#	define __REG64 __DI__
#	define __SINT(S) typedef int          __ccaprice_sint_##S __attribute__( (__mode__( __REG##S )))
#	define __UINT(S) typedef unsigned int __ccaprice_uint_##S __attribute__( (__mode__( __REG##S )))
#endif
/*
 * Create the ccaprice_uint_* types for re-typedef to correct types
 * later.  These are guranteed to always be 8/16/32/64 bits on all
 * platforms.
 */
__UINT(8);  __SINT(8);
__UINT(16); __SINT(16);
__UINT(32); __SINT(32);
__UINT(64); __SINT(64);
#undef __REG8
#undef __REG16
#undef __REG32
#undef __REG64
#undef __UINT
#undef __SINT
/*
 * Only bother to define these types if we can gurantee that no system or
 * standard stdint.h or inttypes.h was included.
 */
#if !defined(_STDINT_H)      && !defined(_STDINT_H_)  && \
    !defined(_SYS_STDINT_H_) && !defined(_INTTYPES_H) && \
    !defined(_INTTYPES_H_)   && !defined(_SYS__STDINT_H_)
	typedef __ccaprice_uint_8  uint8_t;
	typedef __ccaprice_uint_16 uint16_t;
	typedef __ccaprice_uint_32 uint32_t;
	typedef __ccaprice_uint_64 uint64_t;
	typedef __ccaprice_sint_8  int8_t;
	typedef __ccaprice_sint_16 int16_t;
	typedef __ccaprice_sint_32 int32_t;
	typedef __ccaprice_sint_64 int64_t;
#	if defined (__PTRDIFF_TYPE__)
		typedef signed   __PTRDIFF_TYPE__ intptr_t;
		typedef unsigned __PTRDIFF_TYPE__ uintptr_t;
#	else
		/*
		 * These are correct for X86 and x86_64.  Just a thought
		 * there should be a more correct way to fallbacking if
		 * __PTRDIFF_TYPE__ is not defined.  TODO!
		 */
		typedef signed   long             intptr_t;
		typedef unsigned long             uintptr_t;
#	endif
#endif
/*
 * Generate static assertions only when compiling the library.
 * There might be something broken with someones toolchain if
 * these ever assert.
 */
#if defined(__CCAPRICE_CP)
	__CCAPRICE_COMPILE_TIME_ASSERT(uint8_t , sizeof(uint8_t)  == 1);
	__CCAPRICE_COMPILE_TIME_ASSERT(uint16_t, sizeof(uint16_t) == 2);
	__CCAPRICE_COMPILE_TIME_ASSERT(uint32_t, sizeof(uint32_t) == 4);
	__CCAPRICE_COMPILE_TIME_ASSERT(uint64_t, sizeof(uint64_t) == 8);
	__CCAPRICE_COMPILE_TIME_ASSERT(int8_t ,  sizeof(int8_t)   == 1);
	__CCAPRICE_COMPILE_TIME_ASSERT(int16_t,  sizeof(int16_t)  == 2);
	__CCAPRICE_COMPILE_TIME_ASSERT(int32_t,  sizeof(int32_t)  == 4);
	__CCAPRICE_COMPILE_TIME_ASSERT(int64_t,  sizeof(int64_t)  == 8);
#endif
#endif
