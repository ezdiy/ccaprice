#include "inc/string.h"

/*
 * Fast bit-scan-forward table
 */
static const unsigned char strlen_bsf_table[256] = {
	7,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
	5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
	6,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
	5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
	7,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
	5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
	6,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
	5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
};

size_t strlen(const char *src)
{
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
				strlen_bsf_table[(unsigned char)mask] : \
				strlen_bsf_table[mask>>8]+8;
			break;
		}
		src += sizeof(__m128i), len += sizeof(__m128i);
	}
	return len;
}
