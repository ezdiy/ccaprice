/*
 * Copyright (C) 2012
 *     Dale Weiler, Daniel Kolesa
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
#ifndef __CCAPRICE_INTERNAL_GCC_EMMINTRIN_HDR
#define __CCAPRICE_INTERNAL_GCC_EMMINTRIN_HDR

#ifndef __SSE2__
#	error "SSE2 instruction set not enabled"
#else

#include "int/xmmintrin.h"

typedef double    __v2df  __attribute__ ((__vector_size__(16)));
typedef long long __v2di  __attribute__ ((__vector_size__(16)));
typedef int       __v4si  __attribute__ ((__vector_size__(16)));
typedef short     __v8hi  __attribute__ ((__vector_size__(16)));
typedef char      __v16qi __attribute__ ((__vector_size__(16)));
typedef long long __m128i __attribute__ ((__vector_size__ (16), __may_alias__));
typedef double    __m128d __attribute__ ((__vector_size__ (16), __may_alias__));

#define __EMMINTRIN_PROTO(X) extern __inline X __attribute__((__gnu_inline__, __always_inline__, __artificial__))
#define _MM_SHUFFLE2(fp1,fp0) (((fp1) << 1) | (fp0))

__EMMINTRIN_PROTO(__m128d)
_mm_set_sd (double __F) {
    return __extension__ (__m128d) {
        __F, 0.0
    };
}
__EMMINTRIN_PROTO(__m128d)
_mm_set1_pd (double __F) {
    return __extension__ (__m128d) {
        __F, __F
    };
}
__EMMINTRIN_PROTO(__m128d)
_mm_set_pd1 (double __F) {
    return _mm_set1_pd (__F);
}
__EMMINTRIN_PROTO(__m128d)
_mm_set_pd (double __W, double __X) {
    return __extension__ (__m128d) {
        __X, __W
    };
}
__EMMINTRIN_PROTO(__m128d)
_mm_setr_pd (double __W, double __X) {
    return __extension__ (__m128d) {
        __W, __X
    };
}
__EMMINTRIN_PROTO(__m128d)
_mm_setzero_pd (void) {
    return __extension__ (__m128d) {
        0.0, 0.0
    };
}
__EMMINTRIN_PROTO(__m128d)
_mm_move_sd (__m128d __A, __m128d __B) {
    return (__m128d) __builtin_ia32_movsd ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(__m128d)
_mm_load_pd (double const *__P) {
    return *(__m128d *)__P;
}
__EMMINTRIN_PROTO(__m128d)
_mm_loadu_pd (double const *__P) {
    return __builtin_ia32_loadupd (__P);
}
__EMMINTRIN_PROTO(__m128d)
_mm_load1_pd (double const *__P) {
    return _mm_set1_pd (*__P);
}
__EMMINTRIN_PROTO(__m128d)
_mm_load_sd (double const *__P) {
    return _mm_set_sd (*__P);
}
__EMMINTRIN_PROTO(__m128d)
_mm_load_pd1 (double const *__P) {
    return _mm_load1_pd (__P);
}
__EMMINTRIN_PROTO(__m128d)
_mm_loadr_pd (double const *__P) {
    __m128d __tmp = _mm_load_pd (__P);
    return __builtin_ia32_shufpd (__tmp, __tmp, _MM_SHUFFLE2 (0,1));
}
__EMMINTRIN_PROTO(void)
_mm_store_pd (double *__P, __m128d __A) {
    *(__m128d *)__P = __A;
}
__EMMINTRIN_PROTO(void)
_mm_storeu_pd (double *__P, __m128d __A) {
    __builtin_ia32_storeupd (__P, __A);
}
__EMMINTRIN_PROTO(void)
_mm_store_sd (double *__P, __m128d __A) {
    *__P = __builtin_ia32_vec_ext_v2df (__A, 0);
}
__EMMINTRIN_PROTO(double)
_mm_cvtsd_f64 (__m128d __A) {
    return __builtin_ia32_vec_ext_v2df (__A, 0);
}
__EMMINTRIN_PROTO(void)
_mm_storel_pd (double *__P, __m128d __A) {
    _mm_store_sd (__P, __A);
}
__EMMINTRIN_PROTO(void)
_mm_storeh_pd (double *__P, __m128d __A) {
    *__P = __builtin_ia32_vec_ext_v2df (__A, 1);
}
__EMMINTRIN_PROTO(void)
_mm_store1_pd (double *__P, __m128d __A) {
    _mm_store_pd (__P, __builtin_ia32_shufpd (__A, __A, _MM_SHUFFLE2 (0,0)));
}
__EMMINTRIN_PROTO(void)
_mm_store_pd1 (double *__P, __m128d __A) {
    _mm_store1_pd (__P, __A);
}
__EMMINTRIN_PROTO(void)
_mm_storer_pd (double *__P, __m128d __A) {
    _mm_store_pd (__P, __builtin_ia32_shufpd (__A, __A, _MM_SHUFFLE2 (0,1)));
}
__EMMINTRIN_PROTO(int)
_mm_cvtsi128_si32 (__m128i __A) {
    return __builtin_ia32_vec_ext_v4si ((__v4si)__A, 0);
}
#ifdef __x86_64__
__EMMINTRIN_PROTO(long long)
_mm_cvtsi128_si64 (__m128i __A) {
    return __builtin_ia32_vec_ext_v2di ((__v2di)__A, 0);
}
__EMMINTRIN_PROTO(long long)
_mm_cvtsi128_si64x (__m128i __A) {
    return __builtin_ia32_vec_ext_v2di ((__v2di)__A, 0);
}
#endif
__EMMINTRIN_PROTO(__m128d)
_mm_add_pd (__m128d __A, __m128d __B) {
    return (__m128d)__builtin_ia32_addpd ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(__m128d)
_mm_add_sd (__m128d __A, __m128d __B) {
    return (__m128d)__builtin_ia32_addsd ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(__m128d)
_mm_sub_pd (__m128d __A, __m128d __B) {
    return (__m128d)__builtin_ia32_subpd ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(__m128d)
_mm_sub_sd (__m128d __A, __m128d __B) {
    return (__m128d)__builtin_ia32_subsd ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(__m128d)
_mm_mul_pd (__m128d __A, __m128d __B) {
    return (__m128d)__builtin_ia32_mulpd ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(__m128d)
_mm_mul_sd (__m128d __A, __m128d __B) {
    return (__m128d)__builtin_ia32_mulsd ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(__m128d)
_mm_div_pd (__m128d __A, __m128d __B) {
    return (__m128d)__builtin_ia32_divpd ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(__m128d)
_mm_div_sd (__m128d __A, __m128d __B) {
    return (__m128d)__builtin_ia32_divsd ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(__m128d)
_mm_sqrt_pd (__m128d __A) {
    return (__m128d)__builtin_ia32_sqrtpd ((__v2df)__A);
}
__EMMINTRIN_PROTO(__m128d)
_mm_sqrt_sd (__m128d __A, __m128d __B) {
    __v2df __tmp = __builtin_ia32_movsd ((__v2df)__A, (__v2df)__B);
    return (__m128d)__builtin_ia32_sqrtsd ((__v2df)__tmp);
}
__EMMINTRIN_PROTO(__m128d)
_mm_min_pd (__m128d __A, __m128d __B) {
    return (__m128d)__builtin_ia32_minpd ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(__m128d)
_mm_min_sd (__m128d __A, __m128d __B) {
    return (__m128d)__builtin_ia32_minsd ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(__m128d)
_mm_max_pd (__m128d __A, __m128d __B) {
    return (__m128d)__builtin_ia32_maxpd ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(__m128d)
_mm_max_sd (__m128d __A, __m128d __B) {
    return (__m128d)__builtin_ia32_maxsd ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(__m128d)
_mm_and_pd (__m128d __A, __m128d __B) {
    return (__m128d)__builtin_ia32_andpd ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(__m128d)
_mm_andnot_pd (__m128d __A, __m128d __B) {
    return (__m128d)__builtin_ia32_andnpd ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(__m128d)
_mm_or_pd (__m128d __A, __m128d __B) {
    return (__m128d)__builtin_ia32_orpd ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(__m128d)
_mm_xor_pd (__m128d __A, __m128d __B) {
    return (__m128d)__builtin_ia32_xorpd ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(__m128d)
_mm_cmpeq_pd (__m128d __A, __m128d __B) {
    return (__m128d)__builtin_ia32_cmpeqpd ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(__m128d)
_mm_cmplt_pd (__m128d __A, __m128d __B) {
    return (__m128d)__builtin_ia32_cmpltpd ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(__m128d)
_mm_cmple_pd (__m128d __A, __m128d __B) {
    return (__m128d)__builtin_ia32_cmplepd ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(__m128d)
_mm_cmpgt_pd (__m128d __A, __m128d __B) {
    return (__m128d)__builtin_ia32_cmpgtpd ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(__m128d)
_mm_cmpge_pd (__m128d __A, __m128d __B) {
    return (__m128d)__builtin_ia32_cmpgepd ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(__m128d)
_mm_cmpneq_pd (__m128d __A, __m128d __B) {
    return (__m128d)__builtin_ia32_cmpneqpd ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(__m128d)
_mm_cmpnlt_pd (__m128d __A, __m128d __B) {
    return (__m128d)__builtin_ia32_cmpnltpd ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(__m128d)
_mm_cmpnle_pd (__m128d __A, __m128d __B) {
    return (__m128d)__builtin_ia32_cmpnlepd ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(__m128d)
_mm_cmpngt_pd (__m128d __A, __m128d __B) {
    return (__m128d)__builtin_ia32_cmpngtpd ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(__m128d)
_mm_cmpnge_pd (__m128d __A, __m128d __B) {
    return (__m128d)__builtin_ia32_cmpngepd ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(__m128d)
_mm_cmpord_pd (__m128d __A, __m128d __B) {
    return (__m128d)__builtin_ia32_cmpordpd ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(__m128d)
_mm_cmpunord_pd (__m128d __A, __m128d __B) {
    return (__m128d)__builtin_ia32_cmpunordpd ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(__m128d)
_mm_cmpeq_sd (__m128d __A, __m128d __B) {
    return (__m128d)__builtin_ia32_cmpeqsd ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(__m128d)
_mm_cmplt_sd (__m128d __A, __m128d __B) {
    return (__m128d)__builtin_ia32_cmpltsd ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(__m128d)
_mm_cmple_sd (__m128d __A, __m128d __B) {
    return (__m128d)__builtin_ia32_cmplesd ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(__m128d)
_mm_cmpgt_sd (__m128d __A, __m128d __B) {
    return (__m128d) __builtin_ia32_movsd ((__v2df) __A,
                                           (__v2df)
                                           __builtin_ia32_cmpltsd ((__v2df) __B,
                                                   (__v2df)
                                                   __A));
}
__EMMINTRIN_PROTO(__m128d)
_mm_cmpge_sd (__m128d __A, __m128d __B) {
    return (__m128d) __builtin_ia32_movsd ((__v2df) __A,
                                           (__v2df)
                                           __builtin_ia32_cmplesd ((__v2df) __B,
                                                   (__v2df)
                                                   __A));
}
__EMMINTRIN_PROTO(__m128d)
_mm_cmpneq_sd (__m128d __A, __m128d __B) {
    return (__m128d)__builtin_ia32_cmpneqsd ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(__m128d)
_mm_cmpnlt_sd (__m128d __A, __m128d __B) {
    return (__m128d)__builtin_ia32_cmpnltsd ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(__m128d)
_mm_cmpnle_sd (__m128d __A, __m128d __B) {
    return (__m128d)__builtin_ia32_cmpnlesd ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(__m128d)
_mm_cmpngt_sd (__m128d __A, __m128d __B) {
    return (__m128d) __builtin_ia32_movsd ((__v2df) __A,
                                           (__v2df)
                                           __builtin_ia32_cmpnltsd ((__v2df) __B,
                                                   (__v2df)
                                                   __A));
}
__EMMINTRIN_PROTO(__m128d)
_mm_cmpnge_sd (__m128d __A, __m128d __B) {
    return (__m128d) __builtin_ia32_movsd ((__v2df) __A,
                                           (__v2df)
                                           __builtin_ia32_cmpnlesd ((__v2df) __B,
                                                   (__v2df)
                                                   __A));
}
__EMMINTRIN_PROTO(__m128d)
_mm_cmpord_sd (__m128d __A, __m128d __B) {
    return (__m128d)__builtin_ia32_cmpordsd ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(__m128d)
_mm_cmpunord_sd (__m128d __A, __m128d __B) {
    return (__m128d)__builtin_ia32_cmpunordsd ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(int)
_mm_comieq_sd (__m128d __A, __m128d __B) {
    return __builtin_ia32_comisdeq ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(int)
_mm_comilt_sd (__m128d __A, __m128d __B) {
    return __builtin_ia32_comisdlt ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(int)
_mm_comile_sd (__m128d __A, __m128d __B) {
    return __builtin_ia32_comisdle ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(int)
_mm_comigt_sd (__m128d __A, __m128d __B) {
    return __builtin_ia32_comisdgt ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(int)
_mm_comige_sd (__m128d __A, __m128d __B) {
    return __builtin_ia32_comisdge ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(int)
_mm_comineq_sd (__m128d __A, __m128d __B) {
    return __builtin_ia32_comisdneq ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(int)
_mm_ucomieq_sd (__m128d __A, __m128d __B) {
    return __builtin_ia32_ucomisdeq ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(int)
_mm_ucomilt_sd (__m128d __A, __m128d __B) {
    return __builtin_ia32_ucomisdlt ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(int)
_mm_ucomile_sd (__m128d __A, __m128d __B) {
    return __builtin_ia32_ucomisdle ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(int)
_mm_ucomigt_sd (__m128d __A, __m128d __B) {
    return __builtin_ia32_ucomisdgt ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(int)
_mm_ucomige_sd (__m128d __A, __m128d __B) {
    return __builtin_ia32_ucomisdge ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(int)
_mm_ucomineq_sd (__m128d __A, __m128d __B) {
    return __builtin_ia32_ucomisdneq ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_set_epi64x (long long __q1, long long __q0) {
    return __extension__ (__m128i)(__v2di) {
        __q0, __q1
    };
}
__EMMINTRIN_PROTO(__m128i)
_mm_set_epi64 (__m64 __q1,  __m64 __q0) {
    return _mm_set_epi64x ((long long)__q1, (long long)__q0);
}
__EMMINTRIN_PROTO(__m128i)
_mm_set_epi32 (int __q3, int __q2, int __q1, int __q0) {
    return __extension__ (__m128i)(__v4si) {
        __q0, __q1, __q2, __q3
    };
}
__EMMINTRIN_PROTO(__m128i)
_mm_set_epi16 (short __q7, short __q6, short __q5, short __q4,
               short __q3, short __q2, short __q1, short __q0) {
    return __extension__ (__m128i)(__v8hi) {
        __q0, __q1, __q2, __q3, __q4, __q5, __q6, __q7
    };
}
__EMMINTRIN_PROTO(__m128i)
_mm_set_epi8 (char __q15, char __q14, char __q13, char __q12,
              char __q11, char __q10, char __q09, char __q08,
              char __q07, char __q06, char __q05, char __q04,
              char __q03, char __q02, char __q01, char __q00) {
    return __extension__ (__m128i)(__v16qi) {
        __q00, __q01, __q02, __q03, __q04, __q05, __q06, __q07,
               __q08, __q09, __q10, __q11, __q12, __q13, __q14, __q15
    };
}
__EMMINTRIN_PROTO(__m128i)
_mm_set1_epi64x (long long __A) {
    return _mm_set_epi64x (__A, __A);
}
__EMMINTRIN_PROTO(__m128i)
_mm_set1_epi64 (__m64 __A) {
    return _mm_set_epi64 (__A, __A);
}
__EMMINTRIN_PROTO(__m128i)
_mm_set1_epi32 (int __A) {
    return _mm_set_epi32 (__A, __A, __A, __A);
}
__EMMINTRIN_PROTO(__m128i)
_mm_set1_epi16 (short __A) {
    return _mm_set_epi16 (__A, __A, __A, __A, __A, __A, __A, __A);
}
__EMMINTRIN_PROTO(__m128i)
_mm_set1_epi8 (char __A) {
    return _mm_set_epi8 (__A, __A, __A, __A, __A, __A, __A, __A,
                         __A, __A, __A, __A, __A, __A, __A, __A);
}
__EMMINTRIN_PROTO(__m128i)
_mm_setr_epi64 (__m64 __q0, __m64 __q1) {
    return _mm_set_epi64 (__q1, __q0);
}
__EMMINTRIN_PROTO(__m128i)
_mm_setr_epi32 (int __q0, int __q1, int __q2, int __q3) {
    return _mm_set_epi32 (__q3, __q2, __q1, __q0);
}
__EMMINTRIN_PROTO(__m128i)
_mm_setr_epi16 (short __q0, short __q1, short __q2, short __q3,
                short __q4, short __q5, short __q6, short __q7) {
    return _mm_set_epi16 (__q7, __q6, __q5, __q4, __q3, __q2, __q1, __q0);
}
__EMMINTRIN_PROTO(__m128i)
_mm_setr_epi8 (char __q00, char __q01, char __q02, char __q03,
               char __q04, char __q05, char __q06, char __q07,
               char __q08, char __q09, char __q10, char __q11,
               char __q12, char __q13, char __q14, char __q15) {
    return _mm_set_epi8 (__q15, __q14, __q13, __q12, __q11, __q10, __q09, __q08,
                         __q07, __q06, __q05, __q04, __q03, __q02, __q01, __q00);
}
__EMMINTRIN_PROTO(__m128i)
_mm_load_si128 (__m128i const *__P) {
    return *__P;
}
__EMMINTRIN_PROTO(__m128i)
_mm_loadu_si128 (__m128i const *__P) {
    return (__m128i) __builtin_ia32_loaddqu ((char const *)__P);
}
__EMMINTRIN_PROTO(__m128i)
_mm_loadl_epi64 (__m128i const *__P) {
    return _mm_set_epi64 ((__m64)0LL, *(__m64 *)__P);
}
__EMMINTRIN_PROTO(void)
_mm_store_si128 (__m128i *__P, __m128i __B) {
    *__P = __B;
}
__EMMINTRIN_PROTO(void)
_mm_storeu_si128 (__m128i *__P, __m128i __B) {
    __builtin_ia32_storedqu ((char *)__P, (__v16qi)__B);
}
__EMMINTRIN_PROTO(void)
_mm_storel_epi64 (__m128i *__P, __m128i __B) {
    *(long long *)__P = __builtin_ia32_vec_ext_v2di ((__v2di)__B, 0);
}
__EMMINTRIN_PROTO(__m64)
_mm_movepi64_pi64 (__m128i __B) {
    return (__m64) __builtin_ia32_vec_ext_v2di ((__v2di)__B, 0);
}
__EMMINTRIN_PROTO(__m128i)
_mm_movpi64_epi64 (__m64 __A) {
    return _mm_set_epi64 ((__m64)0LL, __A);
}
__EMMINTRIN_PROTO(__m128i)
_mm_move_epi64 (__m128i __A) {
    return (__m128i)__builtin_ia32_movq128 ((__v2di) __A);
}
__EMMINTRIN_PROTO(__m128i)
_mm_setzero_si128 (void) {
    return __extension__ (__m128i)(__v4si) {
        0, 0, 0, 0
    };
}
__EMMINTRIN_PROTO(__m128d)
_mm_cvtepi32_pd (__m128i __A) {
    return (__m128d)__builtin_ia32_cvtdq2pd ((__v4si) __A);
}
__EMMINTRIN_PROTO(__m128)
_mm_cvtepi32_ps (__m128i __A) {
    return (__m128)__builtin_ia32_cvtdq2ps ((__v4si) __A);
}
__EMMINTRIN_PROTO(__m128i)
_mm_cvtpd_epi32 (__m128d __A) {
    return (__m128i)__builtin_ia32_cvtpd2dq ((__v2df) __A);
}
__EMMINTRIN_PROTO(__m64)
_mm_cvtpd_pi32 (__m128d __A) {
    return (__m64)__builtin_ia32_cvtpd2pi ((__v2df) __A);
}
__EMMINTRIN_PROTO(__m128)
_mm_cvtpd_ps (__m128d __A) {
    return (__m128)__builtin_ia32_cvtpd2ps ((__v2df) __A);
}
__EMMINTRIN_PROTO(__m128i)
_mm_cvttpd_epi32 (__m128d __A) {
    return (__m128i)__builtin_ia32_cvttpd2dq ((__v2df) __A);
}
__EMMINTRIN_PROTO(__m64)
_mm_cvttpd_pi32 (__m128d __A) {
    return (__m64)__builtin_ia32_cvttpd2pi ((__v2df) __A);
}
__EMMINTRIN_PROTO(__m128d)
_mm_cvtpi32_pd (__m64 __A) {
    return (__m128d)__builtin_ia32_cvtpi2pd ((__v2si) __A);
}
__EMMINTRIN_PROTO(__m128i)
_mm_cvtps_epi32 (__m128 __A) {
    return (__m128i)__builtin_ia32_cvtps2dq ((__v4sf) __A);
}
__EMMINTRIN_PROTO(__m128i)
_mm_cvttps_epi32 (__m128 __A) {
    return (__m128i)__builtin_ia32_cvttps2dq ((__v4sf) __A);
}
__EMMINTRIN_PROTO(__m128d)
_mm_cvtps_pd (__m128 __A) {
    return (__m128d)__builtin_ia32_cvtps2pd ((__v4sf) __A);
}
__EMMINTRIN_PROTO(int)
_mm_cvtsd_si32 (__m128d __A) {
    return __builtin_ia32_cvtsd2si ((__v2df) __A);
}
#ifdef __x86_64__
__EMMINTRIN_PROTO(long long)
_mm_cvtsd_si64 (__m128d __A) {
    return __builtin_ia32_cvtsd2si64 ((__v2df) __A);
}
__EMMINTRIN_PROTO(long long)
_mm_cvtsd_si64x (__m128d __A) {
    return __builtin_ia32_cvtsd2si64 ((__v2df) __A);
}
#endif
__EMMINTRIN_PROTO(int)
_mm_cvttsd_si32 (__m128d __A) {
    return __builtin_ia32_cvttsd2si ((__v2df) __A);
}
#ifdef __x86_64__
__EMMINTRIN_PROTO(long long)
_mm_cvttsd_si64 (__m128d __A) {
    return __builtin_ia32_cvttsd2si64 ((__v2df) __A);
}
__EMMINTRIN_PROTO(long long)
_mm_cvttsd_si64x (__m128d __A) {
    return __builtin_ia32_cvttsd2si64 ((__v2df) __A);
}
#endif
__EMMINTRIN_PROTO(__m128)
_mm_cvtsd_ss (__m128 __A, __m128d __B) {
    return (__m128)__builtin_ia32_cvtsd2ss ((__v4sf) __A, (__v2df) __B);
}
__EMMINTRIN_PROTO(__m128d)
_mm_cvtsi32_sd (__m128d __A, int __B) {
    return (__m128d)__builtin_ia32_cvtsi2sd ((__v2df) __A, __B);
}
#ifdef __x86_64__
__EMMINTRIN_PROTO(__m128d)
_mm_cvtsi64_sd (__m128d __A, long long __B) {
    return (__m128d)__builtin_ia32_cvtsi642sd ((__v2df) __A, __B);
}
__EMMINTRIN_PROTO(__m128d)
_mm_cvtsi64x_sd (__m128d __A, long long __B) {
    return (__m128d)__builtin_ia32_cvtsi642sd ((__v2df) __A, __B);
}
#endif
__EMMINTRIN_PROTO(__m128d)
_mm_cvtss_sd (__m128d __A, __m128 __B) {
    return (__m128d)__builtin_ia32_cvtss2sd ((__v2df) __A, (__v4sf)__B);
}
#ifdef __OPTIMIZE__
__EMMINTRIN_PROTO(__m128d)
_mm_shuffle_pd(__m128d __A, __m128d __B, const int __mask) {
    return (__m128d)__builtin_ia32_shufpd ((__v2df)__A, (__v2df)__B, __mask);
}
#else
#define _mm_shuffle_pd(A, B, N)						\
  ((__m128d)__builtin_ia32_shufpd ((__v2df)(__m128d)(A),		\
				   (__v2df)(__m128d)(B), (int)(N)))
#endif
__EMMINTRIN_PROTO(__m128d)
_mm_unpackhi_pd (__m128d __A, __m128d __B) {
    return (__m128d)__builtin_ia32_unpckhpd ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(__m128d)
_mm_unpacklo_pd (__m128d __A, __m128d __B) {
    return (__m128d)__builtin_ia32_unpcklpd ((__v2df)__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(__m128d)
_mm_loadh_pd (__m128d __A, double const *__B) {
    return (__m128d)__builtin_ia32_loadhpd ((__v2df)__A, __B);
}
__EMMINTRIN_PROTO(__m128d)
_mm_loadl_pd (__m128d __A, double const *__B) {
    return (__m128d)__builtin_ia32_loadlpd ((__v2df)__A, __B);
}
__EMMINTRIN_PROTO(int)
_mm_movemask_pd (__m128d __A) {
    return __builtin_ia32_movmskpd ((__v2df)__A);
}
__EMMINTRIN_PROTO(__m128i)
_mm_packs_epi16 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_packsswb128 ((__v8hi)__A, (__v8hi)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_packs_epi32 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_packssdw128 ((__v4si)__A, (__v4si)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_packus_epi16 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_packuswb128 ((__v8hi)__A, (__v8hi)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_unpackhi_epi8 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_punpckhbw128 ((__v16qi)__A, (__v16qi)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_unpackhi_epi16 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_punpckhwd128 ((__v8hi)__A, (__v8hi)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_unpackhi_epi32 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_punpckhdq128 ((__v4si)__A, (__v4si)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_unpackhi_epi64 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_punpckhqdq128 ((__v2di)__A, (__v2di)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_unpacklo_epi8 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_punpcklbw128 ((__v16qi)__A, (__v16qi)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_unpacklo_epi16 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_punpcklwd128 ((__v8hi)__A, (__v8hi)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_unpacklo_epi32 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_punpckldq128 ((__v4si)__A, (__v4si)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_unpacklo_epi64 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_punpcklqdq128 ((__v2di)__A, (__v2di)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_add_epi8 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_paddb128 ((__v16qi)__A, (__v16qi)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_add_epi16 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_paddw128 ((__v8hi)__A, (__v8hi)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_add_epi32 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_paddd128 ((__v4si)__A, (__v4si)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_add_epi64 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_paddq128 ((__v2di)__A, (__v2di)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_adds_epi8 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_paddsb128 ((__v16qi)__A, (__v16qi)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_adds_epi16 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_paddsw128 ((__v8hi)__A, (__v8hi)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_adds_epu8 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_paddusb128 ((__v16qi)__A, (__v16qi)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_adds_epu16 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_paddusw128 ((__v8hi)__A, (__v8hi)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_sub_epi8 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_psubb128 ((__v16qi)__A, (__v16qi)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_sub_epi16 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_psubw128 ((__v8hi)__A, (__v8hi)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_sub_epi32 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_psubd128 ((__v4si)__A, (__v4si)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_sub_epi64 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_psubq128 ((__v2di)__A, (__v2di)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_subs_epi8 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_psubsb128 ((__v16qi)__A, (__v16qi)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_subs_epi16 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_psubsw128 ((__v8hi)__A, (__v8hi)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_subs_epu8 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_psubusb128 ((__v16qi)__A, (__v16qi)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_subs_epu16 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_psubusw128 ((__v8hi)__A, (__v8hi)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_madd_epi16 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_pmaddwd128 ((__v8hi)__A, (__v8hi)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_mulhi_epi16 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_pmulhw128 ((__v8hi)__A, (__v8hi)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_mullo_epi16 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_pmullw128 ((__v8hi)__A, (__v8hi)__B);
}
__EMMINTRIN_PROTO(__m64)
_mm_mul_su32 (__m64 __A, __m64 __B) {
    return (__m64)__builtin_ia32_pmuludq ((__v2si)__A, (__v2si)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_mul_epu32 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_pmuludq128 ((__v4si)__A, (__v4si)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_slli_epi16 (__m128i __A, int __B) {
    return (__m128i)__builtin_ia32_psllwi128 ((__v8hi)__A, __B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_slli_epi32 (__m128i __A, int __B) {
    return (__m128i)__builtin_ia32_pslldi128 ((__v4si)__A, __B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_slli_epi64 (__m128i __A, int __B) {
    return (__m128i)__builtin_ia32_psllqi128 ((__v2di)__A, __B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_srai_epi16 (__m128i __A, int __B) {
    return (__m128i)__builtin_ia32_psrawi128 ((__v8hi)__A, __B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_srai_epi32 (__m128i __A, int __B) {
    return (__m128i)__builtin_ia32_psradi128 ((__v4si)__A, __B);
}
#ifdef __OPTIMIZE__
__EMMINTRIN_PROTO(__m128i)
_mm_srli_si128 (__m128i __A, const int __N) {
    return (__m128i)__builtin_ia32_psrldqi128 (__A, __N * 8);
}
__EMMINTRIN_PROTO(__m128i)
_mm_slli_si128 (__m128i __A, const int __N) {
    return (__m128i)__builtin_ia32_pslldqi128 (__A, __N * 8);
}
#else
#define _mm_srli_si128(A, N) \
  ((__m128i)__builtin_ia32_psrldqi128 ((__m128i)(A), (int)(N) * 8))
#define _mm_slli_si128(A, N) \
  ((__m128i)__builtin_ia32_pslldqi128 ((__m128i)(A), (int)(N) * 8))
#endif
__EMMINTRIN_PROTO(__m128i)
_mm_srli_epi16 (__m128i __A, int __B) {
    return (__m128i)__builtin_ia32_psrlwi128 ((__v8hi)__A, __B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_srli_epi32 (__m128i __A, int __B) {
    return (__m128i)__builtin_ia32_psrldi128 ((__v4si)__A, __B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_srli_epi64 (__m128i __A, int __B) {
    return (__m128i)__builtin_ia32_psrlqi128 ((__v2di)__A, __B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_sll_epi16 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_psllw128((__v8hi)__A, (__v8hi)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_sll_epi32 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_pslld128((__v4si)__A, (__v4si)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_sll_epi64 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_psllq128((__v2di)__A, (__v2di)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_sra_epi16 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_psraw128 ((__v8hi)__A, (__v8hi)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_sra_epi32 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_psrad128 ((__v4si)__A, (__v4si)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_srl_epi16 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_psrlw128 ((__v8hi)__A, (__v8hi)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_srl_epi32 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_psrld128 ((__v4si)__A, (__v4si)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_srl_epi64 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_psrlq128 ((__v2di)__A, (__v2di)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_and_si128 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_pand128 ((__v2di)__A, (__v2di)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_andnot_si128 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_pandn128 ((__v2di)__A, (__v2di)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_or_si128 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_por128 ((__v2di)__A, (__v2di)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_xor_si128 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_pxor128 ((__v2di)__A, (__v2di)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_cmpeq_epi8 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_pcmpeqb128 ((__v16qi)__A, (__v16qi)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_cmpeq_epi16 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_pcmpeqw128 ((__v8hi)__A, (__v8hi)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_cmpeq_epi32 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_pcmpeqd128 ((__v4si)__A, (__v4si)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_cmplt_epi8 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_pcmpgtb128 ((__v16qi)__B, (__v16qi)__A);
}
__EMMINTRIN_PROTO(__m128i)
_mm_cmplt_epi16 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_pcmpgtw128 ((__v8hi)__B, (__v8hi)__A);
}
__EMMINTRIN_PROTO(__m128i)
_mm_cmplt_epi32 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_pcmpgtd128 ((__v4si)__B, (__v4si)__A);
}
__EMMINTRIN_PROTO(__m128i)
_mm_cmpgt_epi8 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_pcmpgtb128 ((__v16qi)__A, (__v16qi)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_cmpgt_epi16 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_pcmpgtw128 ((__v8hi)__A, (__v8hi)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_cmpgt_epi32 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_pcmpgtd128 ((__v4si)__A, (__v4si)__B);
}
#ifdef __OPTIMIZE__
__EMMINTRIN_PROTO(int)
_mm_extract_epi16 (__m128i const __A, int const __N) {
    return (unsigned short) __builtin_ia32_vec_ext_v8hi ((__v8hi)__A, __N);
}
__EMMINTRIN_PROTO(__m128i)
_mm_insert_epi16 (__m128i const __A, int const __D, int const __N) {
    return (__m128i) __builtin_ia32_vec_set_v8hi ((__v8hi)__A, __D, __N);
}
#else
#define _mm_extract_epi16(A, N) \
  ((int) (unsigned short) __builtin_ia32_vec_ext_v8hi ((__v8hi)(__m128i)(A), (int)(N)))
#define _mm_insert_epi16(A, D, N)				\
  ((__m128i) __builtin_ia32_vec_set_v8hi ((__v8hi)(__m128i)(A),	\
					  (int)(D), (int)(N)))
#endif
__EMMINTRIN_PROTO(__m128i)
_mm_max_epi16 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_pmaxsw128 ((__v8hi)__A, (__v8hi)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_max_epu8 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_pmaxub128 ((__v16qi)__A, (__v16qi)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_min_epi16 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_pminsw128 ((__v8hi)__A, (__v8hi)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_min_epu8 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_pminub128 ((__v16qi)__A, (__v16qi)__B);
}
__EMMINTRIN_PROTO(int)
_mm_movemask_epi8 (__m128i __A) {
    return __builtin_ia32_pmovmskb128 ((__v16qi)__A);
}
__EMMINTRIN_PROTO(__m128i)
_mm_mulhi_epu16 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_pmulhuw128 ((__v8hi)__A, (__v8hi)__B);
}
#ifdef __OPTIMIZE__
__EMMINTRIN_PROTO(__m128i)
_mm_shufflehi_epi16 (__m128i __A, const int __mask) {
    return (__m128i)__builtin_ia32_pshufhw ((__v8hi)__A, __mask);
}
__EMMINTRIN_PROTO(__m128i)
_mm_shufflelo_epi16 (__m128i __A, const int __mask) {
    return (__m128i)__builtin_ia32_pshuflw ((__v8hi)__A, __mask);
}
__EMMINTRIN_PROTO(__m128i)
_mm_shuffle_epi32 (__m128i __A, const int __mask) {
    return (__m128i)__builtin_ia32_pshufd ((__v4si)__A, __mask);
}
#else
#define _mm_shufflehi_epi16(A, N) \
  ((__m128i)__builtin_ia32_pshufhw ((__v8hi)(__m128i)(A), (int)(N)))
#define _mm_shufflelo_epi16(A, N) \
  ((__m128i)__builtin_ia32_pshuflw ((__v8hi)(__m128i)(A), (int)(N)))
#define _mm_shuffle_epi32(A, N) \
  ((__m128i)__builtin_ia32_pshufd ((__v4si)(__m128i)(A), (int)(N)))
#endif
__EMMINTRIN_PROTO(void)
_mm_maskmoveu_si128 (__m128i __A, __m128i __B, char *__C) {
    __builtin_ia32_maskmovdqu ((__v16qi)__A, (__v16qi)__B, __C);
}
__EMMINTRIN_PROTO(__m128i)
_mm_avg_epu8 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_pavgb128 ((__v16qi)__A, (__v16qi)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_avg_epu16 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_pavgw128 ((__v8hi)__A, (__v8hi)__B);
}
__EMMINTRIN_PROTO(__m128i)
_mm_sad_epu8 (__m128i __A, __m128i __B) {
    return (__m128i)__builtin_ia32_psadbw128 ((__v16qi)__A, (__v16qi)__B);
}
__EMMINTRIN_PROTO(void)
_mm_stream_si32 (int *__A, int __B) {
    __builtin_ia32_movnti (__A, __B);
}

/*
 * added in 4.7.x see commit: 
 * http://gcc.gnu.org/git/?p=gcc.git;a=commitdiff;h=821b85a2a0869b5128bd67e192a5a97748cbd90d
 */
#if ((__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__) >= 40700)
#ifdef __x86_64__ 
__EMMINTRIN_PROTO(void)
_mm_stream_si64 (long long int *__A, long long int __B) {
    __builtin_ia32_movnti64 (__A, __B);
}
#endif
#endif

__EMMINTRIN_PROTO(void)
_mm_stream_si128 (__m128i *__A, __m128i __B) {
    __builtin_ia32_movntdq ((__v2di *)__A, (__v2di)__B);
}
__EMMINTRIN_PROTO(void)
_mm_stream_pd (double *__A, __m128d __B) {
    __builtin_ia32_movntpd (__A, (__v2df)__B);
}
__EMMINTRIN_PROTO(void)
_mm_clflush (void const *__A) {
    __builtin_ia32_clflush (__A);
}
__EMMINTRIN_PROTO(void)
_mm_lfence (void) {
    __builtin_ia32_lfence ();
}
__EMMINTRIN_PROTO(void)
_mm_mfence (void) {
    __builtin_ia32_mfence ();
}
__EMMINTRIN_PROTO(__m128i)
_mm_cvtsi32_si128 (int __A) {
    return _mm_set_epi32 (0, 0, 0, __A);
}
#ifdef __x86_64__
__EMMINTRIN_PROTO(__m128i)
_mm_cvtsi64_si128 (long long __A) {
    return _mm_set_epi64x (0, __A);
}
__EMMINTRIN_PROTO(__m128i)
_mm_cvtsi64x_si128 (long long __A) {
    return _mm_set_epi64x (0, __A);
}
#endif
__EMMINTRIN_PROTO(__m128)
_mm_castpd_ps(__m128d __A) {
    return (__m128) __A;
}
__EMMINTRIN_PROTO(__m128i)
_mm_castpd_si128(__m128d __A) {
    return (__m128i) __A;
}
__EMMINTRIN_PROTO(__m128d)
_mm_castps_pd(__m128 __A) {
    return (__m128d) __A;
}
__EMMINTRIN_PROTO(__m128i)
_mm_castps_si128(__m128 __A) {
    return (__m128i) __A;
}
__EMMINTRIN_PROTO(__m128)
_mm_castsi128_ps(__m128i __A) {
    return (__m128) __A;
}
__EMMINTRIN_PROTO(__m128d)
_mm_castsi128_pd(__m128i __A) {
    return (__m128d) __A;
}

#undef __EMMINTRIN_PROTO
#endif
#endif
