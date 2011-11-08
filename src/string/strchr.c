#include "inc/string.h"

char *strchr(const char *src, int cmp) {
	
	#if 0
	do {
		if (*src == cmp)
			return (char*) src;
	} while (*src++);
	#endif
	
	return memchr((void*)src, cmp, strlen(src));
	
	#if 0
	return 0;
	#endif
}
