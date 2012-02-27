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
typedef u_int8_t                  uint8_t;
typedef u_int16_t                 uint16_t;
typedef u_int32_t                 uint32_t;
typedef u_int64_t                 uint64_t;
#	if defined (__PTRDIFF_TYPE__)
	typedef signed   __PTRDIFF_TYPE__ intptr_t;
	typedef unsigned __PTRDIFF_TYPE__ uintptr_t;
#else
	typedef signed   long             intptr_t;
	typedef unsigned long             uintptr_t;
#endif
#if !defined(NULL)
#	if defined(__cplusplus)
		/*
		 * C++ Specification says that NULL should be 0
		 * opposed to C which defined it as ((void*)0).
		 */
#		define NULL 0
#	else
#		define NULL ((void*)0)
#	endif
#endif

/* Ensure type sizes: When compiling ccaprice only */
#if defined(CCAPRICE_CP)
CCAPRICE_COMPILE_TIME_ASSERT(uint16_t, sizeof(uint16_t) == 2);
CCAPRICE_COMPILE_TIME_ASSERT(uint32_t, sizeof(uint32_t) == 4);
CCAPRICE_COMPILE_TIME_ASSERT(uint64_t, sizeof(uint64_t) == 8);
#endif

#endif /* !CCAPRICE_STDDEF_HDR */
