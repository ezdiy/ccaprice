#include "inc/string.h"

static const unsigned char strlen_bsf_table[256] = {
	CCAPRICE_BSF_TABLE_EXPAND
};

size_t strlen(const char *src)
{
	/*
	 * Fast strlen using SSE, counts data till allignment
	 * the counts in chunks of sizeof(__m128i).
	 */
	#ifdef STRING_STRLEN_SSE
	__m128i         xmm0;
	__m128i         xmm1;
	register int    mask = 0;
	register size_t len  = 0;
	
	/* allign data to 16 bytes */
	while ((((uintptr_t)src)&(sizeof(__m128i)-1)) != 0) {
		if (*src++ == 0) return len;
		++len;
	}
	xmm0 = _mm_setzero_si128();
	for (;;) {
		xmm1 = _mm_load_si128((__m128i*)src);
		xmm1 = _mm_cmpeq_epi8(xmm1, xmm0);
		if ((mask = _mm_movemask_epi8(xmm1)) != 0) {
			len +=((unsigned char)mask) ? 
				strlen_bsf_table[(unsigned char)mask] : \
				strlen_bsf_table[mask>>8]+8;
			break;
		}
		src += sizeof(__m128i), len += sizeof(__m128i);
	}
	return len;
	
	/*
	 * Alternitive fallback method for no SSE, much like memchr()
	 * this function counts string length in word-sized chunks.
	 */
	#else
	unsigned long kip[3] = {
		0x01010101UL,
		0x01010101UL << 7
	};
	unsigned long        bit[3];
	const unsigned long *clp;
	
	long n = (long)src & 3;
	if  (n == 0)
		clp = (unsigned long*)(src - 1);
	else {
		clp = (unsigned long*)(src - n);
		kip[3] = 0xFFFFFFFFL << ((4-n)<<3);
		bit[0] = *clp |   kip[2];
		bit[1] = bit[0] - kip[0];
		bit[2] = kip[1] &~bit[0];
		
		if (bit[1] & bit[2])
			goto result_area;
	}
	
	for (;;) {
		bit[0] = *++clp;
		bit[1] = bit[0] - kip[0];
		bit[2] = kip[1] &~bit[0];
		
		if (bit[1] & bit[2])
			break;
	}
	
	result_area: {
		size_t len = (const char *)clp - src;
		if ((bit[0] & 0xFF000000UL) == 0) return len;
		if ((bit[0] & 0x00FF0000UL) == 0) return len + 1;
		if ((bit[0] & 0x0000FF00UL) == 0) return len + 2;
		                                  return len + 3;
	}
	#endif /*! STRING_STRLEN_SSE */
}
