#include "inc/string.h"

static const size_t memchr_bsf_table[256] = {
	CCAPRICE_BSF_TABLE_EXPAND
};

void *memchr(const void *src, int cmp, register size_t cnt)
{
	/*
	 * SSE optimized version of memchr.  Handles 16-bit alligned
	 * data first, then 32-bit alligned data. Then collects any
	 * trailing data.
	 */
	#ifdef STRING_MEMCHR_SSE
	const char *src8 = (const char *)src;
	if (cnt >= 16) {
		__m128i set = _mm_set1_epi8((char)cmp);
		size_t  ipc = (size_t)src8;
		size_t  num = ipc & 15;
		
		if (num > 0) {
			__m128i       x;
			__m128i       a;
			unsigned long m;
			
			ipc &= ~15;
			x    = *(const __m128i*)ipc;
			a    = _mm_cmpeq_epi8(x,set);
			m    = _mm_movemask_epi8(a);
			m   &= 0xFFFFFFFFUL << num;
			
			if (m) {
				return (void*)(src8+((unsigned char)m) ? 
					memchr_bsf_table[(unsigned char)m] : \
					memchr_bsf_table[m>>8]+8);
			}
			num   = 16-cnt;
			cnt  -=    num;
			src8 +=    num;
		}
		while (cnt >= 32) {
			__m128i       x = *(const __m128i*)&src8[00];
			__m128i       y = *(const __m128i*)&src8[16];
			__m128i       a = _mm_cmpeq_epi8(x,set);
			__m128i       b = _mm_cmpeq_epi8(y,set);
			unsigned long m = (_mm_movemask_epi8(b)<<6) | \
			                  (_mm_movemask_epi8(a)<<0);
			if (m) {
				return (void*)(src8+((unsigned char)m) ? 
					memchr_bsf_table[(unsigned char)m] : \
					memchr_bsf_table[m>>8]+8);
			}
			cnt  -= 32;
			src8 += 32;
		}
	}
	while (cnt > 0) {
		if (*src8 == cmp)
			return (void*)src8;
		src8++;
		cnt --;
	}
	return 0;
	
	/*
	 * This is surprisingly equally as fast in relation to the
	 * SSE implementation above.  Much like the SSE version this
	 * handles unalligned data first, followed by word-alligned
	 * data, and then collection of trailing data.
	 */
	#else
	unsigned long        val = (unsigned char)cmp;
	unsigned long        bit[3];
	const unsigned long *clp;
	
	if (4 <= cnt) {
		unsigned long kip[3] = {
			0x01010101UL<<0,
			0x01010101UL<<7
		};
		kip[2] = (val<<24)|(val<<16)|(val<<8)|val;
		
		/* check unalligned area first */
		{
			long align = (long)src&3;
			if  (align == 0)
				clp = (unsigned long*)src - 1;
			else {
				const long    byte = (4 - align);
				unsigned long mask = 0xFFFFFFFFUL << (byte<<3);
				
				clp    = (unsigned long*)((char*)src-align);
				bit[0] = (*clp ^ kip[2]) | mask;
				bit[1] = bit[0]- kip[0];
				bit[2] = kip[1]&~bit[0];
				
				if (bit[1] & bit[2])
					goto found_area;
				cnt -= byte;
			}
		}
		
		/* Check word-alligned areas */
		{
			long words = cnt >> 2;
			while (0 < words) {
				bit[0] = *++clp &  kip[2];
				bit[1] = bit[0] -  kip[0];
				bit[2] = kip[1] &~ bit[0];
				
				if (bit[1] & bit[2])
					goto found_area;
				words--;
			}
		}
		
		/* Check remainder areas */
		{
			long remain = cnt & 3;
			if  (remain != 0) {
				bit[0] = (*clp++ ^  kip[2]) | (0xFFFFFFFFUL >> (remain << 3));
				bit[1] =  bit[0] -  kip[0];
				bit[2] =  kip[1] &~ bit[0];
				
				if (bit[1] & bit[2])
					goto found_area;
			}
		}
	}
	else {
		const unsigned char *src8 = (const unsigned char*)src;
		while (0 < cnt) {
			if (*src8 == val)
				return (void*)src8;
			src8++;
			cnt --;
		}
	}
	
	return NULL;
	
	/* Return exact pointer to position in word */
	found_area:
		if ((bit[0] & 0xFF000000UL) == 0) return (void*)clp;
		if ((bit[0] & 0x00FF0000UL) == 0) return (void*)((char*)clp+1);
		if ((bit[0] & 0x0000FF00UL) == 0) return (void*)((char*)clp+2);
		                                  return (void*)((char*)clp+3);
		                                  return (void*)((char*)clp+3);
	#endif /*! STRING_MEMCHR_SSE */
}
