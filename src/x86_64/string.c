#include "inc/string.h"

void *memcpy(void *dst, const void *src, register size_t count)
{
	unsigned long cnt32;
	unsigned long rst32;
	unsigned char *dst8;
	unsigned char *src8;
	
	typedef struct {
		unsigned char data[32];
	} memcpy_data;
	
	memcpy_data* dst32 = (memcpy_data*)dst;
	memcpy_data* src32 = (memcpy_data*)src;
	
	/*
	 * Copy all the words we can
	 */
	cnt32 = count / sizeof(memcpy_data);
	rst32 = count % sizeof(memcpy_data);
	
	while (cnt32-->0)
		*dst32++ = *src32++;
	
	/* 
	 * Copy the remaining bytes that could not fit
	 * inside a word.
	 */
	dst8 = (unsigned char*)dst32;
	src8 = (unsigned char*)src32;
	
	while (rst32-->0)
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
