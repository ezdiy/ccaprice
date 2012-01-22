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

#ifndef CCAPRICE_NO_SIZE_T
#	define NULL (void*)0
#endif

#ifndef uintptr_t
	typedef unsigned long uintptr_t;
#endif

/*
 * Take advantage  of GCC builtins, as  the  latter  method, despite
 * working, is  considered  undefined behaviour. The  reason   being
 * is it derefrences a null pointer, and uses a  cast  that voilates
 * C's aliasing rules.  It can also lead to cofusing compiler errors
 * if an argument is misspelled.  None the less it's a genuis way at
 * implementing the behaviour of offsetof.  There might be a  better
 * way at implementing this functionality  for another compiler. I.E
 * a compiler builtin like GCC.
 */
#ifdef __GNUC__
#	define offsetof(TYPE,MEMBER) __builtin_offsetof(TYPE,MEMBER)
#else
#	define offsetof(TYPE,MEMBER) \
		((size_t) ((char*)&((TYPE*)(0))->MEMBER-(char*)0))
#endif /* !__GCC__ */
#endif /* !CCAPRICE_STDDEF_HDR */
