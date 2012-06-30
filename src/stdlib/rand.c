/*
 * Copyright (C) 2012
 *     Dale Weiler
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
#include <ccaprice.h>
#if defined(__STDLIB_RANDOM_OPTIMAL)
#    if defined(__STDLIB_RANDOM_OPTIMAL_SSE2)
#        include <emmintrin.h>
#        define __CCAPRICE_STDLIB_RANDOM_SSE_STAIRS1 0x00
#        define __CCAPRICE_STDLIB_RANDOM_SSE_STAIRS2 0x01
#        define __CCAPRICE_STDLIB_RANDOM_SSE_SHUFFLE _MM_SHUFFLE(2,3,0,1)
        static __m128i __ccaprice_stdlib_rseed;
#    else
        static unsigned int __ccaprice_stdlib_rseed;
#    endif
#else
    static unsigned int __ccaprice_stdlib_rseed;
#endif

#ifdef __STDLIB_RANDOM_OPTIMAL
    #ifdef __STDLIB_RANDOM_OPTIMAL_SSE2
        void srand(unsigned int seed) {
            __ccaprice_stdlib_rseed = _mm_set_epi32(
                seed+__CCAPRICE_STDLIB_RANDOM_SSE_STAIRS1,
                seed+__CCAPRICE_STDLIB_RANDOM_SSE_STAIRS1,
                seed+__CCAPRICE_STDLIB_RANDOM_SSE_STAIRS2,
                seed+__CCAPRICE_STDLIB_RANDOM_SSE_STAIRS2
            );
        }

        #define DATA(X) \
        static const unsigned int data_##X[4]

        inline int rand() {
            __m128i split;
            __m128i multi;
            __m128i adder;
            __m128i mmask;
            __m128i smask;
            __m128i store;

            DATA(multi)={0x000343FD,0x000043FD,0x000343FD,0x00010DCD};
            DATA(adder)={0x00269EC3,0x009E9EC3,0x00D19EC3,0x00000001};
            DATA(mmask)={0xFFFFFFFF,0x00000000,0xFFFFFFFF,0x00000000};
            DATA(smask)={0x00007FFF,0x00007FFF,0x00007FFF,0x00007FFF};
            #undef DATA

            adder = _mm_load_si128   ((__m128i*)data_adder);
            multi = _mm_load_si128   ((__m128i*)data_multi);
            mmask = _mm_load_si128   ((__m128i*)data_mmask);
            smask = _mm_load_si128   ((__m128i*)data_smask);

            split = _mm_shuffle_epi32(
                __ccaprice_stdlib_rseed,
                __CCAPRICE_STDLIB_RANDOM_SSE_SHUFFLE
            );

            __ccaprice_stdlib_rseed = _mm_mul_epu32(__ccaprice_stdlib_rseed, multi);
            multi                   = _mm_shuffle_epi32(
                multi,
                __CCAPRICE_STDLIB_RANDOM_SSE_SHUFFLE
            );
            split                   = _mm_mul_epu32(split, multi);
            __ccaprice_stdlib_rseed = _mm_and_si128(__ccaprice_stdlib_rseed, mmask);
            split                   = _mm_and_si128(split, mmask);
            split                   = _mm_shuffle_epi32(
                split,
                __CCAPRICE_STDLIB_RANDOM_SSE_SHUFFLE
            );
            __ccaprice_stdlib_rseed = _mm_or_si128  (__ccaprice_stdlib_rseed, split);
            __ccaprice_stdlib_rseed = _mm_add_epi32 (__ccaprice_stdlib_rseed, adder);
            store                   = _mm_srai_epi32(__ccaprice_stdlib_rseed, 0x10);
            store                   = _mm_and_si128 (store, smask);

            return (unsigned int)_mm_cvtsi128_si32(store);

            #undef __CCAPRICE_STDLIB_RANDOM_SSE_SHUFFLE
            #undef __CCAPRICE_STDLIB_RANDOM_SSE_STAIRS2
            #undef __CCAPRICE_STDLIB_RANDOM_SSE_STAIRS1
        }
    #else
        #define __STDLIB_RANDOM_NONE
    #endif
#endif

#ifdef __STDLIB_RANDOM_NONE
    #warning "[ccaprice] no optimized rand implementation, using naive method (could be slow)"
    void srand(unsigned int seed) {
        __ccaprice_stdlib_rseed = seed;
    }
    int rand() {
        __ccaprice_stdlib_rseed = \
            (0x343FD*__ccaprice_stdlib_rseed + 0x269EC3);
        return (__ccaprice_stdlib_rseed>>16)&0x7FFF;
    }
#endif
