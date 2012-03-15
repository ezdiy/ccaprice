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
#ifndef CCAPRICE_STDARG_HDR
#define CCAPRICE_STDARG_HDR

/* Ensure nothing tramples this. */
#ifdef va_list
#undef va_list
#endif
#ifdef va_start
#undef va_start
#endif
#ifdef va_arg
#undef va_arg
#endif
#ifdef va_end
#undef va_end
#endif 

#ifndef __GNUC__
/*
 * We're not on a GCC compiler, lets try implementing out own
 * stdarg system.  This is undefined behaviour.  But it works.
 */
#if defined(CCAPRICE_TARGET_X86_32)
	typedef int   va_item;
	typedef char *va_list;
#elif defined(CCAPRICE_TARGET_X86_64)
	typedef long  va_item;
	typedef char *va_list;
#else
#	error "Cannot find sutible target for stdarg.h"
#endif
#	define va_start(A,L) (A =((va_list)&(L)+va_size(L)))
#	define va_arg(A,T)   (A+=va_rsize(T),*((T*)(A-va_rsize(T))))
#	define va_rsize(T)   (((sizeof(T)+sizeof(int)-1)/sizeof(int))*sizeof(int))
#	define va_size(T)    ((sizeof(T)+sizeof(va_item)-1)&~(sizeof(va_item)-1))
#	define va_end(A)     (A=(void *)(0))
#else
/*
 * GCC has builtins, these are much safer and faster.
 */
#	define va_list        __builtin_va_list
#	define va_start(v,f)  __builtin_va_start(v,f)
#	define va_end(v)      __builtin_va_end(v)
#	define va_arg(v,a)    __builtin_va_arg(v,a)
#endif

#endif
