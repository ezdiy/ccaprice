#ifndef __CCAPRICE_INTERNAL_CLANG_MM3DNOW_HDR
#define __CCAPRICE_INTERNAL_CLANG_MM3DNOW_HDR
#if !defined(__GNUC__)
#    error "internal mm3dnow.h bundled with ccaprice will not work with your compiler"
#endif
#include "int/mmintrin.h"
typedef float __v2sf __attribute__((__vector_size__(8)));
#ifndef __clang__
#    define __MM3DNOW_PROTO(X) static __inline__ X __attribute__((__always_inline__))
#else
#    define __MM3DNOW_PROTO(X) static __inline__ X __attribute__((__always_inline__, __nodebug__))
#endif
__MM3DNOW_PROTO(void)_m_femms() {
    __builtin_ia32_femms();
}
__MM3DNOW_PROTO(__m64)_m_pavgusb(__m64 __m1, __m64 __m2) {
    return (__m64)__builtin_ia32_pavgusb((__v8qi)__m1, (__v8qi)__m2);
}
__MM3DNOW_PROTO(__m64)_m_pf2id(__m64 __m) {
    return (__m64)__builtin_ia32_pf2id((__v2sf)__m);
}
__MM3DNOW_PROTO(__m64)_m_pfacc(__m64 __m1, __m64 __m2) {
    return (__m64)__builtin_ia32_pfacc((__v2sf)__m1, (__v2sf)__m2);
}
__MM3DNOW_PROTO(__m64)_m_pfadd(__m64 __m1, __m64 __m2) {
    return (__m64)__builtin_ia32_pfadd((__v2sf)__m1, (__v2sf)__m2);
}
__MM3DNOW_PROTO(__m64)_m_pfcmpeq(__m64 __m1, __m64 __m2) {
    return (__m64)__builtin_ia32_pfcmpeq((__v2sf)__m1, (__v2sf)__m2);
}
__MM3DNOW_PROTO(__m64)_m_pfcmpge(__m64 __m1, __m64 __m2) {
    return (__m64)__builtin_ia32_pfcmpge((__v2sf)__m1, (__v2sf)__m2);
}
__MM3DNOW_PROTO(__m64)_m_pfcmpgt(__m64 __m1, __m64 __m2) {
    return (__m64)__builtin_ia32_pfcmpgt((__v2sf)__m1, (__v2sf)__m2);
}
__MM3DNOW_PROTO(__m64)_m_pfmax(__m64 __m1, __m64 __m2) {
    return (__m64)__builtin_ia32_pfmax((__v2sf)__m1, (__v2sf)__m2);
}
__MM3DNOW_PROTO(__m64)_m_pfmin(__m64 __m1, __m64 __m2) {
    return (__m64)__builtin_ia32_pfmin((__v2sf)__m1, (__v2sf)__m2);
}
__MM3DNOW_PROTO(__m64)_m_pfmul(__m64 __m1, __m64 __m2) {
    return (__m64)__builtin_ia32_pfmul((__v2sf)__m1, (__v2sf)__m2);
}
__MM3DNOW_PROTO(__m64)_m_pfrcp(__m64 __m) {
    return (__m64)__builtin_ia32_pfrcp((__v2sf)__m);
}
__MM3DNOW_PROTO(__m64)_m_pfrcpit1(__m64 __m1, __m64 __m2) {
    return (__m64)__builtin_ia32_pfrcpit1((__v2sf)__m1, (__v2sf)__m2);
}
__MM3DNOW_PROTO(__m64)_m_pfrcpit2(__m64 __m1, __m64 __m2) {
    return (__m64)__builtin_ia32_pfrcpit2((__v2sf)__m1, (__v2sf)__m2);
}
__MM3DNOW_PROTO(__m64)_m_pfrsqrt(__m64 __m) {
    return (__m64)__builtin_ia32_pfrsqrt((__v2sf)__m);
}
__MM3DNOW_PROTO(__m64)_m_pfrsqrtit1(__m64 __m1, __m64 __m2) {
    return (__m64)__builtin_ia32_pfrsqit1((__v2sf)__m1, (__v2sf)__m2);
}
__MM3DNOW_PROTO(__m64)_m_pfsub(__m64 __m1, __m64 __m2) {
    return (__m64)__builtin_ia32_pfsub((__v2sf)__m1, (__v2sf)__m2);
}
__MM3DNOW_PROTO(__m64)_m_pfsubr(__m64 __m1, __m64 __m2) {
    return (__m64)__builtin_ia32_pfsubr((__v2sf)__m1, (__v2sf)__m2);
}
__MM3DNOW_PROTO(__m64)_m_pi2fd(__m64 __m) {
    return (__m64)__builtin_ia32_pi2fd((__v2si)__m);
}
__MM3DNOW_PROTO(__m64)_m_pmulhrw(__m64 __m1, __m64 __m2) {
    return (__m64)__builtin_ia32_pmulhrw((__v4hi)__m1, (__v4hi)__m2);
}
__MM3DNOW_PROTO(__m64)_m_pf2iw(__m64 __m) {
    return (__m64)__builtin_ia32_pf2iw((__v2sf)__m);
}
__MM3DNOW_PROTO(__m64)_m_pfnacc(__m64 __m1, __m64 __m2) {
    return (__m64)__builtin_ia32_pfnacc((__v2sf)__m1, (__v2sf)__m2);
}
__MM3DNOW_PROTO(__m64)_m_pfpnacc(__m64 __m1, __m64 __m2) {
    return (__m64)__builtin_ia32_pfpnacc((__v2sf)__m1, (__v2sf)__m2);
}
__MM3DNOW_PROTO(__m64)_m_pi2fw(__m64 __m) {
    return (__m64)__builtin_ia32_pi2fw((__v2si)__m);
}
__MM3DNOW_PROTO(__m64)_m_pswapdsf(__m64 __m) {
    return (__m64)__builtin_ia32_pswapdsf((__v2sf)__m);
}
__MM3DNOW_PROTO(__m64)_m_pswapdsi(__m64 __m) {
    return (__m64)__builtin_ia32_pswapdsi((__v2si)__m);
}
#undef __MM3DNOW_PROTO
#endif
