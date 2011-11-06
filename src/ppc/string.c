#include "inc/string.h"

void *memcpy(void *dst, const void *src, register size_t count)
{
	register char* dst8 = (char*) dst; /* store in machine register for speed */
	register char* src8 = (char*) src; /* store in machine register for speed */
	
	/*
	 * Decrement pointers: pre-increent is faster than post-increment
	 * for pointers on PowerPC architectures.
	 */
	--src8;
	--dst8;
	
	/*
	 * The PowerPC  arhictetures  have no
	 * instructions for post-incrementing
	 * pointers.
	 * 
	 * So  instead, we'll  use  pre-incrementing
	 * since the  PowerPC architectur  does have
	 * a set  of  instructions to load and store
	 * data that uses  pre-increment of pointers
	 */
	while(count--)
		*++dst8 = *++src8;
		
	return dst;
}

void *memmove(void *dst, const void *src, register size_t count)
{
	register char *dst8 = (char*) dst; /* store in machine register for speed */
	register char *src8 = (char*) src; /* store in machine register for speed */
	
	/*
	 * Decrement pointers: pre-increent is faster than post-increment
	 * for pointers on PowerPC architectures.
	 */
	--dst8;
	--src8;
	
	if (dst8 > src8) {
		/*
		 * Move backwards, this routine is highly
		 * optimized.
		 */
		if (count != 0) {
			do {
				count--;
				*++dst8 = *++src8;
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
		
		/*
		 * Decrement pointers: pre-increent is faster than post-increment
		 * for pointers on PowerPC architectures.
		 */
		dstr--;
		srcr--;
		
		do {
			if((*++dstr = *++srcr) == 0) {
				while (--count != 0)
					*++dstr = 0; /* PAD */
			}
		} while (--count != 0);
	}
	return dst;
}

char *strncpy(char *dst, const char *src) {
	return strncpy(dst, src, strlen(src));
}
