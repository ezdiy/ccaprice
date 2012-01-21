#ifndef CCAPRICE_STDDEF_HDR
#define CCAPRICE_STDDEF_HDR
#include "ccaprice.h"

#define NULL (void*)0

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
#ifdef __GCC__
#	define offsetof(TYPE,MEMBER) __builtin_offsetof(TYPE,MEMBER)
#else
#	define offsetof(TYPE,MEMBER) \
		((size_t) ((char*)&((TYPE*)(0))->MEMBER-(char*)0))
#endif /* !__GCC__ */
#endif /* !CCAPRICE_STDDEF_HDR */
