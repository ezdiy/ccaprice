#include "inc/string.h"

void *memcpy(void *dst, const void *src, register size_t count)
{
	register char* dst8 = (char*) dst; /* store in machine register for speed */
	register char* src8 = (char*) src; /* store in machine register for speed */
	
	/*
	 * Direct byte-per-byte copying, surprisingly this generates decent
	 * assembly.  This however will be slower on architectures that have
	 * no actual pos-incrementing instructions for pointers.  Such as the
	 * PowerPC.
	 */
	while (count--)
		*dst8++ = *src8++;
		
	return dst;
}

void *memmove(void *dst, const void *src, register size_t count)
{
	register char *dst8 = (char*) dst; /* store in machine register for speed */
	register char *src8 = (char*) src; /* store in machine register for speed */
	
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

char *strncpy(char *dst, const char *src, register size_t count)
{
	if (count != 0) {
		register char       *dstr = dst; /* store in machine register for speed */
		register const char *srcr = src; /* store in machine register for speed */

		do {
			if ((*dstr++ = *srcr++) == 0) {
				while (--count != 0)
					*dstr++ = 0; /* PAD */
			}
		} while (--count != 0);
	}
	return dst;
}

char *strcpy(char *dst, const char *src) {
	return strncpy(dst, src, strlen(src));
}
