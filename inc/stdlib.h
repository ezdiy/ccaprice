#ifndef CCAPRICE_STDLIB
#define CCAPRICE_STDLIB
#include "ccaprice.h"

CCAPRICE_EXPORT void atexit(void (*)());
CCAPRICE_EXPORT void exit  (int);
CCAPRICE_EXPORT void abort ();

/* Internal functions */
CCAPRICE_EXPORT void ccaprice_abort(int);
CCAPRICE_EXPORT int  ccaprice_raise(int);

/* malloc / free */
CCAPRICE_EXPORT void *malloc(size_t);
CCAPRICE_EXPORT void  free  (void *);

#endif
