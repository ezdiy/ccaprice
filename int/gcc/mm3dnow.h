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
#ifndef __CCAPRICE_INTERNAL_GCC_MM3DNOW_HDR
#define __CCAPRICE_INTERNAL_GCC_MM3DNOW_HDR
/*
 * We provide our own internal headers because compiler developers some how
 * managed to fuck up by including stdlib.h for malloc
 */
#if !defined(__GNUC__)
#    error "internal mm3dnow.h bundled with ccaprice will not work with your compiler"
#endif

#include "int/mmintrin.h"

#define __MM3DNOW_PROTO(X) __MM3DNOW_PROTO(X)

__MM3DNOW_PROTO(void) _m_femms (void) {
    __builtin_ia32_femms();
}
__MM3DNOW_PROTO(__m64) _m_pavgusb (__m64 __A, __m64 __B) {
    return (__m64)__builtin_ia32_pavgusb ((__v8qi)__A, (__v8qi)__B);
}
__MM3DNOW_PROTO(__m64) _m_pf2id (__m64 __A) {
    return (__m64)__builtin_ia32_pf2id ((__v2sf)__A);
}
__MM3DNOW_PROTO(__m64) _m_pfacc (__m64 __A, __m64 __B) {
    return (__m64)__builtin_ia32_pfacc ((__v2sf)__A, (__v2sf)__B);
}
__MM3DNOW_PROTO(__m64) _m_pfadd (__m64 __A, __m64 __B) {
    return (__m64)__builtin_ia32_pfadd ((__v2sf)__A, (__v2sf)__B);
}
__MM3DNOW_PROTO(__m64) _m_pfcmpeq (__m64 __A, __m64 __B) {
    return (__m64)__builtin_ia32_pfcmpeq ((__v2sf)__A, (__v2sf)__B);
}
__MM3DNOW_PROTO(__m64) _m_pfcmpge (__m64 __A, __m64 __B) {
    return (__m64)__builtin_ia32_pfcmpge ((__v2sf)__A, (__v2sf)__B);
}
__MM3DNOW_PROTO(__m64) _m_pfcmpgt (__m64 __A, __m64 __B) {
    return (__m64)__builtin_ia32_pfcmpgt ((__v2sf)__A, (__v2sf)__B);
}
__MM3DNOW_PROTO(__m64)_m_pfmax (__m64 __A, __m64 __B) {
    return (__m64)__builtin_ia32_pfmax ((__v2sf)__A, (__v2sf)__B);
}
__MM3DNOW_PROTO(__m64)
_m_pfmin (__m64 __A, __m64 __B) {
    return (__m64)__builtin_ia32_pfmin ((__v2sf)__A, (__v2sf)__B);
}
__MM3DNOW_PROTO(__m64)_m_pfmul (__m64 __A, __m64 __B) {
    return (__m64)__builtin_ia32_pfmul ((__v2sf)__A, (__v2sf)__B);
}
__MM3DNOW_PROTO(__m64)_m_pfrcp (__m64 __A) {
    return (__m64)__builtin_ia32_pfrcp ((__v2sf)__A);
}
__MM3DNOW_PROTO(__m64)_m_pfrcpit1 (__m64 __A, __m64 __B) {
    return (__m64)__builtin_ia32_pfrcpit1 ((__v2sf)__A, (__v2sf)__B);
}
__MM3DNOW_PROTO(__m64)_m_pfrcpit2 (__m64 __A, __m64 __B) {
    return (__m64)__builtin_ia32_pfrcpit2 ((__v2sf)__A, (__v2sf)__B);
}
__MM3DNOW_PROTO(__m64)_m_pfrsqrt (__m64 __A) {
    return (__m64)__builtin_ia32_pfrsqrt ((__v2sf)__A);
}
__MM3DNOW_PROTO(__m64)_m_pfrsqit1 (__m64 __A, __m64 __B) {
    return (__m64)__builtin_ia32_pfrsqit1 ((__v2sf)__A, (__v2sf)__B);
}
__MM3DNOW_PROTO(__m64)_m_pfsub (__m64 __A, __m64 __B) {
    return (__m64)__builtin_ia32_pfsub ((__v2sf)__A, (__v2sf)__B);
}
__MM3DNOW_PROTO(__m64)_m_pfsubr (__m64 __A, __m64 __B) {
    return (__m64)__builtin_ia32_pfsubr ((__v2sf)__A, (__v2sf)__B);
}
__MM3DNOW_PROTO(__m64)_m_pi2fd (__m64 __A) {
    return (__m64)__builtin_ia32_pi2fd ((__v2si)__A);
}
__MM3DNOW_PROTO(__m64) _m_pmulhrw (__m64 __A, __m64 __B) {
    return (__m64)__builtin_ia32_pmulhrw ((__v4hi)__A, (__v4hi)__B);
}
__MM3DNOW_PROTO(void)
_m_prefetch (void *__P) {
    __builtin_prefetch (__P, 0, 3 /* _MM_HINT_T0 */);
}
__MM3DNOW_PROTO(void) _m_prefetchw (void *__P) {
    __builtin_prefetch (__P, 1, 3 /* _MM_HINT_T0 */);
}
__MM3DNOW_PROTO(__m64) _m_from_float (float __A) {
    return __extension__ (__m64)(__v2sf) { __A, 0.0f };
}
__MM3DNOW_PROTO(float)
_m_to_float (__m64 __A) {
    union {
        __v2sf v;
        float a[2];
    } __tmp;
    __tmp.v = (__v2sf)__A;
    return __tmp.a[0];
}

#ifdef __3dNOW_A__
__MM3DNOW_PROTO(__m64) _m_pf2iw (__m64 __A) {
    return (__m64)__builtin_ia32_pf2iw ((__v2sf)__A);
}
__MM3DNOW_PROTO(__m64) _m_pfnacc (__m64 __A, __m64 __B) {
    return (__m64)__builtin_ia32_pfnacc ((__v2sf)__A, (__v2sf)__B);
}
__MM3DNOW_PROTO(__m64) _m_pfpnacc (__m64 __A, __m64 __B) {
    return (__m64)__builtin_ia32_pfpnacc ((__v2sf)__A, (__v2sf)__B);
}
__MM3DNOW_PROTO(__m64) _m_pi2fw (__m64 __A) {
    return (__m64)__builtin_ia32_pi2fw ((__v2si)__A);
}
__MM3DNOW_PROTO(__m64) _m_pswapd (__m64 __A) {
    return (__m64)__builtin_ia32_pswapdsf ((__v2sf)__A);
}
#endif
#endif
#undef __MM3DNOW_PROTO
#endif
