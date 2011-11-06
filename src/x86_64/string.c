#include "inc/string.h"
void *memcpy(void *dst, const void *src, register size_t count)
{
	unsigned char *odst = (unsigned char*) dst;
	unsigned char *osrc = (unsigned char*) src;
	uintptr_t      dsta = (16-(uintptr_t)dst)&15;
	unsigned int   loops;
	
	while(dsta--) *odst++ = *osrc++;
	count -= dsta;
	loops  = count >> 6; /* in 64 byte chunks */
	count -= loops << 6;
	
	if (((uintptr_t)osrc & 15) == 0) {
		int i;
		for(i = loops; i > 0; --i) {
			__m128 v0 = _mm_load_ps((float*)(osrc +  0));
			__m128 v1 = _mm_load_ps((float*)(osrc + 16));
			__m128 v2 = _mm_load_ps((float*)(osrc + 32));
			__m128 v3 = _mm_load_ps((float*)(osrc + 48));
			_mm_store_ps((float*)(odst+ 0), v0);
			_mm_store_ps((float*)(odst+16), v1);
			_mm_store_ps((float*)(odst+32), v2);
			_mm_store_ps((float*)(odst+48), v3);
			
			osrc += 64, odst += 64;
		}
	}
	else {
		int i;
		for(i = loops; i > 0; --i) {
			__m128 v0 = _mm_loadu_ps((float*)(osrc +  0));
			__m128 v1 = _mm_loadu_ps((float*)(osrc + 16));
			__m128 v2 = _mm_loadu_ps((float*)(osrc + 32));
			__m128 v3 = _mm_loadu_ps((float*)(osrc + 48));
			_mm_store_ps((float*)(odst+ 0), v0);
			_mm_store_ps((float*)(odst+16), v1);
			_mm_store_ps((float*)(odst+32), v2);
			_mm_store_ps((float*)(odst+48), v3);
			
			osrc += 64, odst += 64;
		}
	}
	while(dsta--) *odst++ = *osrc++;
	return dst;
}

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

char *strncpy(char *dst, const char *src, register size_t count) {
	return memcpy(dst, src, count);
}
char *strcpy(char *dst, const char *src) {
	return strncpy(dst, src, strlen(src));
}

size_t strlen(const char *src)
{
	#define BITS_TO_ZERO_SET(x) \
		(x),0,1,0,2,0,1,0,3,0,1,0,2,0,1,0
	static const unsigned char table_bt0[256] = {
		BITS_TO_ZERO_SET(7),BITS_TO_ZERO_SET(4), /*-3*/
		BITS_TO_ZERO_SET(5),BITS_TO_ZERO_SET(4), /*-1*/
		BITS_TO_ZERO_SET(6),BITS_TO_ZERO_SET(4), /*-2*/
		BITS_TO_ZERO_SET(5),BITS_TO_ZERO_SET(4), /*-2*/
		BITS_TO_ZERO_SET(7),BITS_TO_ZERO_SET(4), /*-3*/
		BITS_TO_ZERO_SET(5),BITS_TO_ZERO_SET(4), /*-1*/
		BITS_TO_ZERO_SET(6),BITS_TO_ZERO_SET(4), /*-2*/
		BITS_TO_ZERO_SET(5),BITS_TO_ZERO_SET(4)  /*-2*/
	};
	#undef BITS_TO_ZERO_SET

	__m128i         xmm   [2];
	register int    mask = 0;
	register size_t len  = 0;
	
	/* allign data to 16 bytes */
	while ((((uintptr_t)src)&(sizeof(__m128i)-1)) != 0) {
		if (*src++ == 0) return len;
		++len;
	}
	xmm[0] = _mm_setzero_si128();
	for (;;) {
		xmm[1] = _mm_load_si128((__m128i*)src);
		xmm[1] = _mm_cmpeq_epi8(xmm[1], xmm[0]);
		if ((mask = _mm_movemask_epi8(xmm[1])) != 0) {
			len +=((unsigned char)mask) ? 
				table_bt0[(unsigned char)mask] : table_bt0[mask>>8]+8;
			break;
		}
		src += sizeof(__m128i), len += sizeof(__m128i);
	}
	return len;
}
