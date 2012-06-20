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
#ifndef __CCAPRICE_INTERNAL_CLANG_XMMINTRIN_HDR
#define __CCAPRICE_INTERNAL_CLANG_XMMINTRIN_HDR
/*
 * We provide our own internal headers because compiler developers some how
 * managed to fuck up by including stdlib.h for malloc
 */
#if !defined(__clang__)
#    error "internal xmmintrin.h bundled with ccaprice will not work with your compiler"
#endif

#ifndef __SSE__
#    error "SSE instruction set not enabled"
#endif

#include "int/mmintrin.h"

typedef int   __v4si __attribute__((__vector_size__(16)));
typedef float __v4sf __attribute__((__vector_size__(16)));
typedef float __m128 __attribute__((__vector_size__(16)));

#define __XMMINTRIN_PROTO(X) static __inline__ X __attribute__((__always_inline__, __nodebug__))

#define _MM_HINT_T0  3
#define _MM_HINT_T1  2
#define _MM_HINT_T2  1
#define _MM_HINT_NTA 0

/* aliasing and macros (can't be functionized) */
#define _mm_prefetch(a, sel) (__builtin_prefetch((void *)(a), 0, (sel)))
#define _mm_load_ps1(p) _mm_load1_ps(p)
#define _mm_shuffle_pi16(a, n) __extension__ ({     \
    __m64 __a = (a);                                \
    (__m64)__builtin_ia32_pshufw((__v4hi)__a, (n)); \
})

#define _mm_shuffle_ps(a, b, mask) __extension__ ({ \
    __m128 __a = (a);                                                \
    __m128 __b = (b);                                                \
    (__m128)__builtin_shufflevector((__v4sf)__a, (__v4sf)__b,        \
                                  (mask) & 0x3, ((mask) & 0xc) >> 2, \
                                  (((mask) & 0x30) >> 4) + 4,        \
                                  (((mask) & 0xc0) >> 6) + 4);       \
})

#define _MM_SHUFFLE(z, y, x, w) (((z) << 6) | ((y) << 4) | ((x) << 2) | (w))

#define _MM_EXCEPT_INVALID    (0x0001)
#define _MM_EXCEPT_DENORM     (0x0002)
#define _MM_EXCEPT_DIV_ZERO   (0x0004)
#define _MM_EXCEPT_OVERFLOW   (0x0008)
#define _MM_EXCEPT_UNDERFLOW  (0x0010)
#define _MM_EXCEPT_INEXACT    (0x0020)
#define _MM_EXCEPT_MASK       (0x003f)
#define _MM_MASK_INVALID      (0x0080)
#define _MM_MASK_DENORM       (0x0100)
#define _MM_MASK_DIV_ZERO     (0x0200)
#define _MM_MASK_OVERFLOW     (0x0400)
#define _MM_MASK_UNDERFLOW    (0x0800)
#define _MM_MASK_INEXACT      (0x1000)
#define _MM_MASK_MASK         (0x1f80)

#define _MM_ROUND_NEAREST     (0x0000)
#define _MM_ROUND_DOWN        (0x2000)
#define _MM_ROUND_UP          (0x4000)
#define _MM_ROUND_TOWARD_ZERO (0x6000)
#define _MM_ROUND_MASK        (0x6000)

#define _MM_FLUSH_ZERO_MASK   (0x8000)
#define _MM_FLUSH_ZERO_ON     (0x8000)
#define _MM_FLUSH_ZERO_OFF    (0x0000)

#define _MM_GET_EXCEPTION_MASK()   (_mm_getcsr() & _MM_MASK_MASK)
#define _MM_GET_EXCEPTION_STATE()  (_mm_getcsr() & _MM_EXCEPT_MASK)
#define _MM_GET_FLUSH_ZERO_MODE()  (_mm_getcsr() & _MM_FLUSH_ZERO_MASK)
#define _MM_GET_ROUNDING_MODE()    (_mm_getcsr() & _MM_ROUND_MASK)
#define _MM_SET_EXCEPTION_MASK(x)  (_mm_setcsr((_mm_getcsr() & ~_MM_MASK_MASK)       | (x)))
#define _MM_SET_EXCEPTION_STATE(x) (_mm_setcsr((_mm_getcsr() & ~_MM_EXCEPT_MASK)     | (x)))
#define _MM_SET_FLUSH_ZERO_MODE(x) (_mm_setcsr((_mm_getcsr() & ~_MM_FLUSH_ZERO_MASK) | (x)))
#define _MM_SET_ROUNDING_MODE(x)   (_mm_setcsr((_mm_getcsr() & ~_MM_ROUND_MASK)      | (x)))

#define _MM_TRANSPOSE4_PS(row0, row1, row2, row3) \
    do {                                          \
        __m128 tmp3, tmp2, tmp1, tmp0;            \
        tmp0   = _mm_unpacklo_ps((row0), (row1)); \
        tmp2   = _mm_unpacklo_ps((row2), (row3)); \
        tmp1   = _mm_unpackhi_ps((row0), (row1)); \
        tmp3   = _mm_unpackhi_ps((row2), (row3)); \
        (row0) = _mm_movelh_ps(tmp0, tmp2);       \
        (row1) = _mm_movehl_ps(tmp2, tmp0);       \
        (row2) = _mm_movelh_ps(tmp1, tmp3);       \
        (row3) = _mm_movehl_ps(tmp3, tmp1);       \
    } while (0)

/* compat */
#define _m_pextrw _mm_extract_pi16
#define _m_pinsrw _mm_insert_pi16
#define _m_pmaxsw _mm_max_pi16
#define _m_pmaxub _mm_max_pu8
#define _m_pminsw _mm_min_pi16
#define _m_pminub _mm_min_pu8
#define _m_pmovmskb _mm_movemask_pi8
#define _m_pmulhuw _mm_mulhi_pu16
#define _m_pshufw _mm_shuffle_pi16
#define _m_maskmovq _mm_maskmove_si64
#define _m_pavgb _mm_avg_pu8
#define _m_pavgw _mm_avg_pu16
#define _m_psadbw _mm_sad_pu8
#define _m_ _mm_
#define _m_ _mm_

/* Arhictecture specific stuff for x86_64 */
#ifdef __x86_64__
__XMMINTRIN_PROTO(long long)_mm_cvtss_si64(__m128 a)
{
    return __builtin_ia32_cvtss2si64(a);
}
__XMMINTRIN_PROTO(__m128)_mm_cvtsi64_ss(__m128 a, long long b)
{
    a[0] = b;
    return a;
}
#endif

__XMMINTRIN_PROTO(__m128)_mm_add_ss(__m128 a, __m128 b)
{
    a[0] += b[0];
    return a;
}
__XMMINTRIN_PROTO(__m128)_mm_add_ps(__m128 a, __m128 b)
{
    return a + b;
}
__XMMINTRIN_PROTO(__m128)_mm_sub_ss(__m128 a, __m128 b)
{
    a[0] -= b[0];
    return a;
}
__XMMINTRIN_PROTO(__m128)_mm_sub_ps(__m128 a, __m128 b)
{
    return a - b;
}
__XMMINTRIN_PROTO(__m128)_mm_mul_ss(__m128 a, __m128 b)
{
    a[0] *= b[0];
    return a;
}
__XMMINTRIN_PROTO(__m128)_mm_mul_ps(__m128 a, __m128 b)
{
    return a * b;
}
__XMMINTRIN_PROTO(__m128)_mm_div_ss(__m128 a, __m128 b)
{
    a[0] /= b[0];
    return a;
}
__XMMINTRIN_PROTO(__m128)_mm_div_ps(__m128 a, __m128 b)
{
    return a / b;
}
__XMMINTRIN_PROTO(__m128)_mm_sqrt_ss(__m128 a)
{
    return __builtin_ia32_sqrtss(a);
}
__XMMINTRIN_PROTO(__m128)_mm_sqrt_ps(__m128 a)
{
    return __builtin_ia32_sqrtps(a);
}
__XMMINTRIN_PROTO(__m128)_mm_rcp_ss(__m128 a)
{
    return __builtin_ia32_rcpss(a);
}
__XMMINTRIN_PROTO(__m128)_mm_rcp_ps(__m128 a)
{
    return __builtin_ia32_rcpps(a);
}
__XMMINTRIN_PROTO(__m128)_mm_rsqrt_ss(__m128 a)
{
    return __builtin_ia32_rsqrtss(a);
}
__XMMINTRIN_PROTO(__m128)_mm_rsqrt_ps(__m128 a)
{
    return __builtin_ia32_rsqrtps(a);
}
__XMMINTRIN_PROTO(__m128)_mm_min_ss(__m128 a, __m128 b)
{
    return __builtin_ia32_minss(a, b);
}
__XMMINTRIN_PROTO(__m128)_mm_min_ps(__m128 a, __m128 b)
{
    return __builtin_ia32_minps(a, b);
}
__XMMINTRIN_PROTO(__m128)_mm_max_ss(__m128 a, __m128 b)
{
    return __builtin_ia32_maxss(a, b);
}
__XMMINTRIN_PROTO(__m128)_mm_max_ps(__m128 a, __m128 b)
{
    return __builtin_ia32_maxps(a, b);
}
__XMMINTRIN_PROTO(__m128)_mm_and_ps(__m128 a, __m128 b)
{
    return (__m128)((__v4si)a & (__v4si)b);
}
__XMMINTRIN_PROTO(__m128)_mm_andnot_ps(__m128 a, __m128 b)
{
    return (__m128)(~(__v4si)a & (__v4si)b);
}
__XMMINTRIN_PROTO(__m128)_mm_or_ps(__m128 a, __m128 b)
{
    return (__m128)((__v4si)a | (__v4si)b);
}
__XMMINTRIN_PROTO(__m128)_mm_xor_ps(__m128 a, __m128 b)
{
    return (__m128)((__v4si)a ^ (__v4si)b);
}
__XMMINTRIN_PROTO(__m128)_mm_cmpeq_ss(__m128 a, __m128 b)
{
    return (__m128)__builtin_ia32_cmpss(a, b, 0);
}
__XMMINTRIN_PROTO(__m128)_mm_cmpeq_ps(__m128 a, __m128 b)
{
    return (__m128)__builtin_ia32_cmpps(a, b, 0);
}
__XMMINTRIN_PROTO(__m128)_mm_cmplt_ss(__m128 a, __m128 b)
{
    return (__m128)__builtin_ia32_cmpss(a, b, 1);
}
__XMMINTRIN_PROTO(__m128)_mm_cmplt_ps(__m128 a, __m128 b)
{
    return (__m128)__builtin_ia32_cmpps(a, b, 1);
}
__XMMINTRIN_PROTO(__m128)_mm_cmple_ss(__m128 a, __m128 b)
{
    return (__m128)__builtin_ia32_cmpss(a, b, 2);
}
__XMMINTRIN_PROTO(__m128)_mm_cmple_ps(__m128 a, __m128 b)
{
    return (__m128)__builtin_ia32_cmpps(a, b, 2);
}
__XMMINTRIN_PROTO(__m128)_mm_cmpgt_ss(__m128 a, __m128 b)
{
    return (__m128)__builtin_ia32_cmpss(b, a, 1);
}
__XMMINTRIN_PROTO(__m128)_mm_cmpgt_ps(__m128 a, __m128 b)
{
    return (__m128)__builtin_ia32_cmpps(b, a, 1);
}
__XMMINTRIN_PROTO(__m128)_mm_cmpge_ss(__m128 a, __m128 b)
{
    return (__m128)__builtin_ia32_cmpss(b, a, 2);
}
__XMMINTRIN_PROTO(__m128)_mm_cmpge_ps(__m128 a, __m128 b)
{
    return (__m128)__builtin_ia32_cmpps(b, a, 2);
}
__XMMINTRIN_PROTO(__m128)_mm_cmpneq_ss(__m128 a, __m128 b)
{
    return (__m128)__builtin_ia32_cmpss(a, b, 4);
}
__XMMINTRIN_PROTO(__m128)_mm_cmpneq_ps(__m128 a, __m128 b)
{
    return (__m128)__builtin_ia32_cmpps(a, b, 4);
}
__XMMINTRIN_PROTO(__m128)_mm_cmpnlt_ss(__m128 a, __m128 b)
{
    return (__m128)__builtin_ia32_cmpss(a, b, 5);
}
__XMMINTRIN_PROTO(__m128)_mm_cmpnlt_ps(__m128 a, __m128 b)
{
    return (__m128)__builtin_ia32_cmpps(a, b, 5);
}
__XMMINTRIN_PROTO(__m128)_mm_cmpnle_ss(__m128 a, __m128 b)
{
    return (__m128)__builtin_ia32_cmpss(a, b, 6);
}
__XMMINTRIN_PROTO(__m128)_mm_cmpnle_ps(__m128 a, __m128 b)
{
    return (__m128)__builtin_ia32_cmpps(a, b, 6);
}
__XMMINTRIN_PROTO(__m128)_mm_cmpngt_ss(__m128 a, __m128 b)
{
    return (__m128)__builtin_ia32_cmpss(b, a, 5);
}
__XMMINTRIN_PROTO(__m128)_mm_cmpngt_ps(__m128 a, __m128 b)
{
    return (__m128)__builtin_ia32_cmpps(b, a, 5);
}
__XMMINTRIN_PROTO(__m128)_mm_cmpnge_ss(__m128 a, __m128 b)
{
    return (__m128)__builtin_ia32_cmpss(b, a, 6);
}
__XMMINTRIN_PROTO(__m128)_mm_cmpnge_ps(__m128 a, __m128 b)
{
    return (__m128)__builtin_ia32_cmpps(b, a, 6);
}
__XMMINTRIN_PROTO(__m128)_mm_cmpord_ss(__m128 a, __m128 b)
{
    return (__m128)__builtin_ia32_cmpss(a, b, 7);
}
__XMMINTRIN_PROTO(__m128)_mm_cmpord_ps(__m128 a, __m128 b)
{
    return (__m128)__builtin_ia32_cmpps(a, b, 7);
}
__XMMINTRIN_PROTO(__m128)_mm_cmpunord_ss(__m128 a, __m128 b)
{
    return (__m128)__builtin_ia32_cmpss(a, b, 3);
}
__XMMINTRIN_PROTO(__m128)_mm_cmpunord_ps(__m128 a, __m128 b)
{
    return (__m128)__builtin_ia32_cmpps(a, b, 3);
}
__XMMINTRIN_PROTO(int)_mm_comieq_ss(__m128 a, __m128 b)
{
    return __builtin_ia32_comieq(a, b);
}
__XMMINTRIN_PROTO(int)_mm_comilt_ss(__m128 a, __m128 b)
{
    return __builtin_ia32_comilt(a, b);
}
__XMMINTRIN_PROTO(int)_mm_comile_ss(__m128 a, __m128 b)
{
    return __builtin_ia32_comile(a, b);
}
__XMMINTRIN_PROTO(int)_mm_comigt_ss(__m128 a, __m128 b)
{
    return __builtin_ia32_comigt(a, b);
}
__XMMINTRIN_PROTO(int)_mm_comige_ss(__m128 a, __m128 b)
{
    return __builtin_ia32_comige(a, b);
}
__XMMINTRIN_PROTO(int)_mm_comineq_ss(__m128 a, __m128 b)
{
    return __builtin_ia32_comineq(a, b);
}
__XMMINTRIN_PROTO(int)_mm_ucomieq_ss(__m128 a, __m128 b)
{
    return __builtin_ia32_ucomieq(a, b);
}
__XMMINTRIN_PROTO(int)_mm_ucomilt_ss(__m128 a, __m128 b)
{
    return __builtin_ia32_ucomilt(a, b);
}
__XMMINTRIN_PROTO(int)_mm_ucomile_ss(__m128 a, __m128 b)
{
    return __builtin_ia32_ucomile(a, b);
}
__XMMINTRIN_PROTO(int)_mm_ucomigt_ss(__m128 a, __m128 b)
{
    return __builtin_ia32_ucomigt(a, b);
}
__XMMINTRIN_PROTO(int)_mm_ucomige_ss(__m128 a, __m128 b)
{
    return __builtin_ia32_ucomige(a, b);
}
__XMMINTRIN_PROTO(int)_mm_ucomineq_ss(__m128 a, __m128 b)
{
    return __builtin_ia32_ucomineq(a, b);
}
__XMMINTRIN_PROTO(int)_mm_cvtss_si32(__m128 a)
{
    return __builtin_ia32_cvtss2si(a);
}
__XMMINTRIN_PROTO(int)_mm_cvt_ss2si(__m128 a)
{
    return _mm_cvtss_si32(a);
}
__XMMINTRIN_PROTO(__m64)_mm_cvtps_pi32(__m128 a)
{
    return (__m64)__builtin_ia32_cvtps2pi(a);
}
__XMMINTRIN_PROTO(__m64)_mm_cvt_ps2pi(__m128 a)
{
    return _mm_cvtps_pi32(a);
}
__XMMINTRIN_PROTO(int)_mm_cvttss_si32(__m128 a)
{
    return a[0];
}
__XMMINTRIN_PROTO(int)_mm_cvtt_ss2si(__m128 a)
{
    return _mm_cvttss_si32(a);
}
__XMMINTRIN_PROTO(long long)_mm_cvttss_si64(__m128 a)
{
    return a[0];
}
__XMMINTRIN_PROTO(__m64)_mm_cvttps_pi32(__m128 a)
{
    return (__m64)__builtin_ia32_cvttps2pi(a);
}
__XMMINTRIN_PROTO(__m64)_mm_cvtt_ps2pi(__m128 a)
{
    return _mm_cvttps_pi32(a);
}
__XMMINTRIN_PROTO(__m128)_mm_cvtsi32_ss(__m128 a, int b)
{
    a[0] = b;
    return a;
}
__XMMINTRIN_PROTO(__m128)_mm_cvt_si2ss(__m128 a, int b)
{
    return _mm_cvtsi32_ss(a, b);
}
__XMMINTRIN_PROTO(__m128)_mm_cvtpi32_ps(__m128 a, __m64 b)
{
    return __builtin_ia32_cvtpi2ps(a, (__v2si)b);
}
__XMMINTRIN_PROTO(__m128)_mm_cvt_pi2ps(__m128 a, __m64 b)
{
    return _mm_cvtpi32_ps(a, b);
}
__XMMINTRIN_PROTO(float)_mm_cvtss_f32(__m128 a)
{
    return a[0];
}

__XMMINTRIN_PROTO(__m128)_mm_loadh_pi(__m128 a, const __m64 *p)
{
    typedef float __mm_loadh_pi_v2f32 __attribute__((__vector_size__(8)));
    struct __mm_loadh_pi_struct {
        __mm_loadh_pi_v2f32 u;
    } __attribute__((__packed__, __may_alias__));
    __mm_loadh_pi_v2f32 b = ((struct __mm_loadh_pi_struct*)p)->u;
    __m128 bb = __builtin_shufflevector(b, b, 0, 1, 0, 1);
    return __builtin_shufflevector(a, bb, 0, 1, 4, 5);
}

__XMMINTRIN_PROTO(__m128)_mm_loadl_pi(__m128 a, const __m64 *p)
{
    typedef float __mm_loadl_pi_v2f32 __attribute__((__vector_size__(8)));
    struct __mm_loadl_pi_struct {
        __mm_loadl_pi_v2f32 u;
    } __attribute__((__packed__, __may_alias__));
    __mm_loadl_pi_v2f32 b = ((struct __mm_loadl_pi_struct*)p)->u;
    __m128 bb = __builtin_shufflevector(b, b, 0, 1, 0, 1);
    return __builtin_shufflevector(a, bb, 4, 5, 2, 3);
}

__XMMINTRIN_PROTO(__m128)_mm_load_ss(const float *p)
{
    struct __mm_load_ss_struct {
        float u;
    } __attribute__((__packed__, __may_alias__));
    float u = ((struct __mm_load_ss_struct*)p)->u;
    return (__m128) {
        u, 0, 0, 0
    };
}
__XMMINTRIN_PROTO(__m128)_mm_load1_ps(const float *p)
{
    struct __mm_load1_ps_struct {
        float u;
    } __attribute__((__packed__, __may_alias__));
    float u = ((struct __mm_load1_ps_struct*)p)->u;
    return (__m128) {
        u, u, u, u
    };
}
__XMMINTRIN_PROTO(__m128)_mm_load_ps(const float *p)
{
    return *(__m128*)p;
}
__XMMINTRIN_PROTO(__m128)_mm_loadu_ps(const float *p)
{
    struct __loadu_ps {
        __m128 v;
    } __attribute__((__packed__, __may_alias__));
    return ((struct __loadu_ps*)p)->v;
}
__XMMINTRIN_PROTO(__m128)_mm_loadr_ps(const float *p)
{
    __m128 a = _mm_load_ps(p);
    return __builtin_shufflevector(a, a, 3, 2, 1, 0);
}
__XMMINTRIN_PROTO(__m128)_mm_set_ss(float w)
{
    return (__m128) {
        w, 0, 0, 0
    };
}
__XMMINTRIN_PROTO(__m128)_mm_set1_ps(float w)
{
    return (__m128) {
        w, w, w, w
    };
}
__XMMINTRIN_PROTO(__m128)_mm_set_ps1(float w)
{
    return _mm_set1_ps(w);
}
__XMMINTRIN_PROTO(__m128)_mm_set_ps(float z, float y, float x, float w)
{
    return (__m128) {
        w, x, y, z
    };
}
__XMMINTRIN_PROTO(__m128)_mm_setr_ps(float z, float y, float x, float w)
{
    return (__m128) {
        z, y, x, w
    };
}
static __inline__ __m128 __attribute__((__always_inline__))_mm_setzero_ps(void)
{
    return (__m128) {
        0, 0, 0, 0
    };
}
static __inline__ void __attribute__((__always_inline__))_mm_storeh_pi(__m64 *p, __m128 a)
{
    __builtin_ia32_storehps((__v2si *)p, a);
}
static __inline__ void __attribute__((__always_inline__))_mm_storel_pi(__m64 *p, __m128 a)
{
    __builtin_ia32_storelps((__v2si *)p, a);
}
static __inline__ void __attribute__((__always_inline__))_mm_store_ss(float *p, __m128 a)
{
    struct __mm_store_ss_struct {
        float u;
    } __attribute__((__packed__, __may_alias__));
    ((struct __mm_store_ss_struct*)p)->u = a[0];
}
__XMMINTRIN_PROTO(void)_mm_storeu_ps(float *p, __m128 a)
{
    __builtin_ia32_storeups(p, a);
}
__XMMINTRIN_PROTO(void)_mm_store1_ps(float *p, __m128 a)
{
    a = __builtin_shufflevector(a, a, 0, 0, 0, 0);
    _mm_storeu_ps(p, a);
}
__XMMINTRIN_PROTO(void)_mm_store_ps1(float *p, __m128 a)
{
    return _mm_store1_ps(p, a);
}
__XMMINTRIN_PROTO(void)_mm_store_ps(float *p, __m128 a)
{
    *(__m128 *)p = a;
}
__XMMINTRIN_PROTO(void)_mm_storer_ps(float *p, __m128 a)
{
    a = __builtin_shufflevector(a, a, 3, 2, 1, 0);
    _mm_store_ps(p, a);
}
__XMMINTRIN_PROTO(void)_mm_stream_pi(__m64 *p, __m64 a)
{
    __builtin_ia32_movntq(p, a);
}
__XMMINTRIN_PROTO(void)_mm_stream_ps(float *p, __m128 a)
{
    __builtin_ia32_movntps(p, a);
}
__XMMINTRIN_PROTO(void)_mm_sfence(void)
{
    __builtin_ia32_sfence();
}
__XMMINTRIN_PROTO(int)_mm_extract_pi16(__m64 a, int n)
{
    __v4hi b = (__v4hi)a;
    return (unsigned short)b[n & 3];
}
__XMMINTRIN_PROTO(__m64)_mm_insert_pi16(__m64 a, int d, int n)
{
    __v4hi b = (__v4hi)a;
    b[n & 3] = d;
    return (__m64)b;
}
__XMMINTRIN_PROTO(__m64)_mm_max_pi16(__m64 a, __m64 b)
{
    return (__m64)__builtin_ia32_pmaxsw((__v4hi)a, (__v4hi)b);
}
__XMMINTRIN_PROTO(__m64)_mm_max_pu8(__m64 a, __m64 b)
{
    return (__m64)__builtin_ia32_pmaxub((__v8qi)a, (__v8qi)b);
}
__XMMINTRIN_PROTO(__m64)_mm_min_pi16(__m64 a, __m64 b)
{
    return (__m64)__builtin_ia32_pminsw((__v4hi)a, (__v4hi)b);
}
__XMMINTRIN_PROTO(__m64)_mm_min_pu8(__m64 a, __m64 b)
{
    return (__m64)__builtin_ia32_pminub((__v8qi)a, (__v8qi)b);
}
__XMMINTRIN_PROTO(int)_mm_movemask_pi8(__m64 a)
{
    return __builtin_ia32_pmovmskb((__v8qi)a);
}
__XMMINTRIN_PROTO(__m64)_mm_mulhi_pu16(__m64 a, __m64 b)
{
    return (__m64)__builtin_ia32_pmulhuw((__v4hi)a, (__v4hi)b);
}
__XMMINTRIN_PROTO(void)_mm_maskmove_si64(__m64 d, __m64 n, char *p)
{
    __builtin_ia32_maskmovq((__v8qi)d, (__v8qi)n, p);
}
__XMMINTRIN_PROTO(__m64)_mm_avg_pu8(__m64 a, __m64 b)
{
    return (__m64)__builtin_ia32_pavgb((__v8qi)a, (__v8qi)b);
}
__XMMINTRIN_PROTO(__m64)_mm_avg_pu16(__m64 a, __m64 b)
{
    return (__m64)__builtin_ia32_pavgw((__v4hi)a, (__v4hi)b);
}
__XMMINTRIN_PROTO(__m64)_mm_sad_pu8(__m64 a, __m64 b)
{
    return (__m64)__builtin_ia32_psadbw((__v8qi)a, (__v8qi)b);
}
__XMMINTRIN_PROTO(unsigned int)_mm_getcsr(void)
{
    return __builtin_ia32_stmxcsr();
}
__XMMINTRIN_PROTO(void)_mm_setcsr(unsigned int i)
{
    __builtin_ia32_ldmxcsr(i);
}
__XMMINTRIN_PROTO(__m128)_mm_unpackhi_ps(__m128 a, __m128 b)
{
    return __builtin_shufflevector(a, b, 2, 6, 3, 7);
}
__XMMINTRIN_PROTO(__m128)_mm_unpacklo_ps(__m128 a, __m128 b)
{
    return __builtin_shufflevector(a, b, 0, 4, 1, 5);
}
__XMMINTRIN_PROTO(__m128)_mm_move_ss(__m128 a, __m128 b)
{
    return __builtin_shufflevector(a, b, 4, 1, 2, 3);
}
__XMMINTRIN_PROTO(__m128)_mm_movehl_ps(__m128 a, __m128 b)
{
    return __builtin_shufflevector(a, b, 6, 7, 2, 3);
}
__XMMINTRIN_PROTO(__m128)_mm_movelh_ps(__m128 a, __m128 b)
{
    return __builtin_shufflevector(a, b, 0, 1, 4, 5);
}
__XMMINTRIN_PROTO(__m128)_mm_cvtpi16_ps(__m64 a)
{
    __m64 b, c;
    __m128 r;
    b = _mm_setzero_si64();
    b = _mm_cmpgt_pi16(b, a);
    c = _mm_unpackhi_pi16(a, b);
    r = _mm_setzero_ps();
    r = _mm_cvtpi32_ps(r, c);
    r = _mm_movelh_ps(r, r);
    c = _mm_unpacklo_pi16(a, b);
    r = _mm_cvtpi32_ps(r, c);
    return r;
}
__XMMINTRIN_PROTO(__m128)_mm_cvtpu16_ps(__m64 a)
{
    __m64 b, c;
    __m128 r;
    b = _mm_setzero_si64();
    c = _mm_unpackhi_pi16(a, b);
    r = _mm_setzero_ps();
    r = _mm_cvtpi32_ps(r, c);
    r = _mm_movelh_ps(r, r);
    c = _mm_unpacklo_pi16(a, b);
    r = _mm_cvtpi32_ps(r, c);
    return r;
}
__XMMINTRIN_PROTO(__m128)_mm_cvtpi8_ps(__m64 a)
{
    __m64 b;
    b = _mm_setzero_si64();
    b = _mm_cmpgt_pi8(b, a);
    b = _mm_unpacklo_pi8(a, b);
    return _mm_cvtpi16_ps(b);
}
__XMMINTRIN_PROTO(__m128)_mm_cvtpu8_ps(__m64 a)
{
    __m64 b;
    b = _mm_setzero_si64();
    b = _mm_unpacklo_pi8(a, b);
    return _mm_cvtpi16_ps(b);
}
__XMMINTRIN_PROTO(__m128)_mm_cvtpi32x2_ps(__m64 a, __m64 b)
{
    __m128 c;
    c = _mm_setzero_ps();
    c = _mm_cvtpi32_ps(c, b);
    c = _mm_movelh_ps(c, c);
    return _mm_cvtpi32_ps(c, a);
}
__XMMINTRIN_PROTO(__m64)_mm_cvtps_pi16(__m128 a)
{
    __m64 b, c;
    b = _mm_cvtps_pi32(a);
    a = _mm_movehl_ps(a, a);
    c = _mm_cvtps_pi32(a);
    return _mm_packs_pi16(b, c);
}
__XMMINTRIN_PROTO(__m64)_mm_cvtps_pi8(__m128 a)
{
    __m64 b, c;
    b = _mm_cvtps_pi16(a);
    c = _mm_setzero_si64();
    return _mm_packs_pi16(b, c);
}
__XMMINTRIN_PROTO(int)_mm_movemask_ps(__m128 a)
{
    return __builtin_ia32_movmskps(a);
}

/*
 * GCC has a broken setup:
 * when xmmintrin.h is included and __SSE2__ is present
 * it includes emmintrin.h and depends on it.
 */
#ifdef __SSE2__
# include "int/emmintrin.h"
#endif

#undef __XMMINTRIN_PROTO
#endif
