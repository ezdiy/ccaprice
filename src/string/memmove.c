#include "inc/string.h"

void *memmove(void *dst, const void *src, register size_t count)
{
	char *dst8 = (char*) dst;
	char *src8 = (char*) src;
	
	if (dst > src) {
		/*
		 * Move backwards, this routine is highly
		 * optimized.
		 */
		if (count != 0) {
			do {
				count--;
				*dst8++ = *src8++;
			} while (count != 0);
		}
		return dst;
	}
	return memcpy(dst, src, count);
}
