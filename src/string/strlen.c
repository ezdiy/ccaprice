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
#ifdef STRING_STRLEN_OPTIMAL_SSE2
	#define CCAPRICE_NO_SIZE_T 1
	#include <xmmintrin.h>
	#include "inc/string.h"
	#undef  CCAPRICE_NO_SIZE_T
#else
	#include "inc/ccaprice.h"
	#include "inc/string.h"
#endif

static const unsigned char strlen_bsf_table[256] = {
	CCAPRICE_BSF_TABLE_EXPAND
};

size_t strlen(const char *src) {
	#ifdef STRING_STRLEN_OPTIMAL
		#if defined(STRING_STRLEN_X86_64) && defined(STRING_STRLEN_OPTIMAL_SSE2)
			/*
			 * Fast strlen using SSE, counts data till allignment
			 * the counts in chunks of sizeof(__m128i).
			 */
			__m128i         xmm1;
			register int    mask = 0;
			register size_t len  = 0;
			
			/* allign data to 16 bytes */
			while ((((intptr_t)src) & 15)) {
				if (*src++ == 0)
					return len;
				++ len;
			}
			__m128i xmm0 = _mm_setzero_si128();
			for (;;) {
				xmm1 = _mm_load_si128((__m128i*)src);
				xmm1 = _mm_cmpeq_epi8(xmm1, xmm0);
				if ((mask = _mm_movemask_epi8(xmm1)) != 0) {
					
					/* Newer versions have a built-in bit-scan-forward */
					#if ((__GNUC__ >=4) || ((__GNUC__ ==3) && (__GNUC_MINOR__ >= 4)))
						len += __builtin_ctz(mask);
					#elif defined (__GNUC__)
					/* Older version of GCC use bsf instruction */
					size_t p;
					__asm__ (
						"bsf %1,%0":"=r"(p):"rm"(mask)
					);
					len += p;
					#else
					/* Use highly-optimized BSF table */
					len +=((unsigned char)mask) ? 
						strlen_bsf_table[(unsigned char)mask] : \
						strlen_bsf_table[mask>>8]+8;
					#endif
					break;
				}
				src += sizeof(__m128i), len += sizeof(__m128i);
			}
			return len;
		#elif defined(STRING_STRLEN_X86)
			/*
			 * Vector optimized strlen using GPR:
			 *	This could be seen as a little more complicated than
			 * 	the SSE2 implementation above.
			 * 
			 * 	The general idea of how this works is described below
			 */
			size_t len = 0;
			for (;;) {
				size_t x = *(size_t*)src; /* Undefined behaviour */
				if (!(x & 0x000000FF)) return len+0;
				if (!(x & 0x0000FF00)) return len+1;
				if (!(x & 0x00FF0000)) return len+2;
				if (!(x & 0xFF000000)) return len+3;

				src+=4, len+=4;
			}
			/*
			 * The implementation above reads a `double - word` from
			 * memory, extracts each of it's bytes [mask] and checks
			 * bytes against 0 boolean check `!`.
			 */
			 return len;
		#else
			#define STRING_STRLEN_NONE
		#endif
	#else
		#define STRING_STRLEN_NONE
	#endif /* !STRING_STRLEN_OPTIMAL */
	
	#ifdef STRING_STRLEN_NONE
		#warning "[ccaprice] no optimized strlen implementation, using naive method (could be slow)"
		const char *s = src;
		while (*src) src++;
		return src - s;
	#endif /* !STRING_STRLEN_NONE */
}
