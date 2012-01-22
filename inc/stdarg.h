#ifndef CCAPRICE_STDARG_HDR
#define CCAPRICE_STDARG_HDR

#ifndef __GCC__
/*
 * We're not on a GCC compiler, lets try implementing out own
 * stdarg system.  This is undefined behaviour.  But it works.
 */
#if defined(CCAPRICE_TARGET_X86) || defined(__x86__)
	typedef int            va_item;
	typedef unsigned char *va_list;
#elif defined(CCAPRICE_TARGET_X86_64) || defined(__x86_64__)
	typedef long           va_item;
	typedef unsigned char *va_list;
#else
#	error "Cannot find sutible target for stdarh.h"
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
#	define va_start(v,f)  __builtin_va_start(v,f);
#	define va_end(v)      __builtin_va_end  (v);
#	define va_arg(v,a)    __builtin_va_arg  (v,a);
#endif

#endif
