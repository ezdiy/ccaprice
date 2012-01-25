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
#include "inc/ccaprice.h"
#ifdef STDLIB_RAND_OPTIMAL
	#ifdef STDLIB_RAND_OPTIMAL_SSE2
		#include <emmintrin.h>
		#define CCAPRICE_STDLIB_RAND_SSE_STAIRS1 0x00
		#define CCAPRICE_STDLIB_RAND_SSE_STAIRS2 0x01
		#define CCAPRICE_STDLIB_RAND_SSE_SHUFFLE (2,3,0,1)
		static __m128i ccaprice_stdlib_rseed;
	#else
	static unsigned int ccaprice_stdlib_rseed;
	#endif
#else
	static unsigned int ccaprice_stdlib_rseed;
#endif

#ifdef STDLIB_RAND_OPTIMAL
	#ifdef STDLIB_RAND_OPTIMAL_SSE2
		void srand(unsigned int seed) {
			ccaprice_stdlib_rseed = _mm_set_epi32(
				seed+CCAPRICE_STDLIB_RAND_SSE_STAIRS1,
				seed+CCAPRICE_STDLIB_RAND_SSE_STAIRS1,
				seed+CCAPRICE_STDLIB_RAND_SSE_STAIRS2,
				seed+CCAPRICE_STDLIB_RAND_SSE_STAIRS2
			);
		}
		
		#define DATA(X) \
		static const unsigned int data_##X
			
		inline int rand() {
			unsigned int ret;
			
			__m128i split;
			__m128i multi;
			__m128i adder;
			__m128i mmask;
			__m128i smask;
			__m128i store;
			
			DATA(multi)[4]={0x000343FD,0x000043FD,0x000343FD,0x00010DCD};
			DATA(adder)[4]={0x00269EC3,0x009E9EC3,0x00D19EC3,0x00000001};
			DATA(mmask)[4]={0xFFFFFFFF,0x00000000,0xFFFFFFFF,0x00000000};
			DATA(smask)[4]={0x00007FFF,0x00007FFF,0x00007FFF,0x00007FFF};
			#undef DATA
			
			adder = _mm_load_si128   ((__m128i*)data_adder);
			multi = _mm_load_si128   ((__m128i*)data_multi);
			mmask = _mm_load_si128   ((__m128i*)data_mmask);
			smask = _mm_load_si128   ((__m128i*)data_smask);
			
			split = _mm_shuffle_epi32(
				ccaprice_stdlib_rseed,
				_MM_SHUFFLE CCAPRICE_STDLIB_RAND_SSE_SHUFFLE
			);
			
			ccaprice_stdlib_rseed = _mm_mul_epu32(ccaprice_stdlib_rseed, multi);
			multi                 = _mm_shuffle_epi32(
				multi,
				_MM_SHUFFLE CCAPRICE_STDLIB_RAND_SSE_SHUFFLE
			);
			split                 = _mm_mul_epu32(split, multi);
			ccaprice_stdlib_rseed = _mm_and_si128(ccaprice_stdlib_rseed, mmask);
			split                 = _mm_and_si128(split, mmask);
			split                 = _mm_shuffle_epi32(
				split,
				_MM_SHUFFLE CCAPRICE_STDLIB_RAND_SSE_SHUFFLE
			);
			ccaprice_stdlib_rseed = _mm_or_si128  (ccaprice_stdlib_rseed, split);
			ccaprice_stdlib_rseed = _mm_add_epi32 (ccaprice_stdlib_rseed, adder);
			store                 = _mm_srai_epi32(ccaprice_stdlib_rseed, 0x10);
			store                 = _mm_and_si128 (store, smask);
			
			_mm_storeu_si128((__m128i*)&ret, store);
			return ret;
			
			#undef CCAPRICE_STDLIB_RAND_SSE_SHUFFLE
			#undef CCAPRICE_STDLIB_RAND_SSE_STAIRS2
			#undef CCAPRICE_STDLIB_RAND_SSE_STAIRS1
		}
	#else
		#define STDLIB_RAND_NONE
	#endif
#endif

#ifdef STDLIB_RAND_NONE
	#warning "[ccaprice] no optimized rand implementation, using naive method (could be slow)"
	void srand(unsigned int seed) {
		ccaprice_stdlib_rseed = seed;
	}
	int rand() {
		ccaprice_stdlib_rseed = \
			(0x343FD*ccaprice_stdlib_rseed + 0x269EC3);
		return (ccaprice_stdlib_rseed>>16)&0x7FFF;
	}
#endif
