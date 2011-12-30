#ifndef CCAPRICE_CCAPRICE_HDR
#define CCAPRICE_CCAPRICE_HDR

#define STRING_STRLEN_OPTIMAL
#define STRING_MEMCHR_OPTIMAL
#define STRING_MEMCPY_OPTIMAL
#define STRING_MEMSET_OPTIMAL

#define CCAPRICE_COMPILE_TIME_ASSERT(name, x) \
	typedef int CompileTimeAssertFailed_##name[(x)*2-1]

#ifdef CCAPRICE_TARGET_X86_64
	#define STRING_STRLEN_X86_64
	#define STRING_MEMCHR_X86_64
	#define STRING_MEMCPY_X86_64
	#define STRING_MEMSET_X86_64
	typedef unsigned char       uint8_t;
	typedef unsigned short      uint16_t;
	typedef unsigned int        uint32_t;
	typedef unsigned long       uint64_t;
#elif defined(CCAPRICE_TARGET_X86)
	#define STRING_STRLEN_X86
	#define STRING_MEMCHR_X86
	#define STRING_MEMCPY_X86
	#define STRING_MEMSET_X86
	typedef unsigned char       uint8_t;
	typedef unsigned short      uint16_t;
	typedef unsigned int        uint32_t;
	typedef unsigned long long  uint64_t;
#else
	#include <stdint.h>
#endif /* !CCAPRICE_TARGET_X86_64 */

/* Ensure type sizes */
CCAPRICE_COMPILE_TIME_ASSERT(uint32_t, sizeof(uint32_t)==4);
CCAPRICE_COMPILE_TIME_ASSERT(uint16_t, sizeof(uint16_t)==2);
CCAPRICE_COMPILE_TIME_ASSERT(uint64_t, sizeof(uint64_t)==8);

#ifdef CCAPRICE_COMPILING
#	define CCAPRICE_EXPORT
#else
#	define CCAPRICE_EXPORT extern
#endif /* !CCAPRICE_COMPILING    */
#endif /* !CCAPRICE_CCAPRICE_HDR */
