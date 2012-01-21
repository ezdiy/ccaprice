#ifndef CCAPRICE_ASSERT_DEF
#define CCAPRICE_ASSERT_DEF
#include "ccaprice.h"

#ifndef NDEBUG
#define assert(expr) ccaprice_assert(__FILE__,__LINE__,(expr))
#else
#define assert(expr) /* Do nothing */
#endif

/*
 * Internal function not to be used outside scope of library
 */
CCAPRICE_EXPORT void ccaprice_assert(const char*,int,int);

#endif
