#include "inc/string.h"

static const unsigned char strlen_bsf_table[256] = {
	CCAPRICE_BSF_TABLE_EXPAND
};

size_t strlen(const char *src)
{
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
}
