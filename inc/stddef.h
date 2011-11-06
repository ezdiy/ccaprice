#ifndef CCAPRICE_STDDEF_HDR
#define CCAPRICE_STDDEF_HDR
#include "ccaprice.h"

#define NULL (void*)0

typedef unsigned long uintptr_t;

/*
 * Take advantage  of GCC builtins, as  the  latter  method, despite
 * working, is  considered  undefined behaviour. The  reasong  being
 * is it derefrences a null pointer, and uses a  cast  that voilates
 * C's aliasing rules.  It can also lead to cofusing compiler errors
 * if an argument is misspelled.
 */
#ifdef __GCC__
#	define offsetof(TYPE,MEMBER) __builtin_offsetof(TYPE,MEMBER)
#else
#	define offsetof(TYPE,MEMBER) \
		((size_t) ((char*)&((TYPE*)(0))->MEMBER-(char*)0))
#endif /* !__GCC__ */
#endif /* !CCAPRICE_STDDEF_HDR */
