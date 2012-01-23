/*
 * Copyright (C) 2012 
 * 	Dale Weiler
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#define CCAPRICE_NO_SIZE_T 1
#include <emmintrin.h>
#include "inc/string.h"
#undef  CCAPRICE_NO_SIZE_T
static const size_t memchr_bsf_table[256] = {
	CCAPRICE_BSF_TABLE_EXPAND
};

void *memchr(const void *src, int cmp, register size_t cnt)
{
	#ifdef STRING_MEMCHR_OPTIMAL
		#if defined(STRING_MEMCHR_X86_64) || defined(STRING_MEMCHR_X86)
		/*
		 * SSE optimized version of memchr.  Handles 16-bit alligned
		 * data first, then 32-bit alligned data. Then collects any
		 * trailing data.
		 */
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
		#else
			#define STRING_MEMCHR_NONE
		#endif
	#endif /* !STRING_MEMCHR_OPTIMAL */
	
	#ifdef STRING_MEMCHR_NONE
		#warning "[ccaprice] no optimized memchr implementation, using naive method (could be slow)"
		int   i;
		char *s = (char*)src;
		for (i=0; i<cnt; i++) {
			if (*s == cmp) return s;
			else s++;
		}
		return 0;
	#endif /* !STRING_MEMCHR_NONE */
	
	return 0; /* Compiler warns no return */
}
