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
#ifndef __CCAPRICE_MATH_HDR__
#define __CCAPRICE_MATH_HDR__

#ifdef __cplusplus
extern "C" {
#endif

#include <ccaprice.h>
#if defined(__CCAPRICE_TARGET_X86_32) || defined(__CCAPRICE_TARGET_X86_64)
	#define __CCAPRICE_MATH_HI_L(X) *(1+((int*)(&X)))
	#define __CCAPRICE_MATH_LO_L(X) *(0+((int*)(&X)))
	#define __CCAPRICE_MATH_HI_P(X) *(1+((int*) (X)))
	#define __CCAPRICE_MATH_LO_P(X) *(0+((int*) (X)))
#else
	#define __CCAPRICE_MATH_HI_L(X) *(0+((int*)(&X)))
	#define __CCAPRICE_MATH_LO_L(X) *(1+((int*)(&X)))
	#define __CCAPRICE_MATH_HI_P(X) *(0+((int*) (X)))
	#define __CCAPRICE_MATH_LO_P(X) *(1+((int*) (X)))
#endif

#if defined(__CCAPRICE_TARGET_X86_32) || defined(__CCAPRICE_TARGET_X86_64)
	#define FP_ILOGB0      (-2147483647 - 1)
	#define FP_ILOGBNAN    (-2147483647 - 1)
#endif

#define M_E             2.7182818284590452354   /* e          */
#define M_LOG2E         1.4426950408889634074   /* log_2 e    */
#define M_LOG10E        0.43429448190325182765  /* log_10 e   */
#define M_LN2           0.69314718055994530942  /* log_e 2    */
#define M_LN10          2.30258509299404568402  /* log_e 10   */
#define M_PI            3.14159265358979323846  /* pi         */
#define M_PI_2          1.57079632679489661923  /* pi/2       */
#define M_PI_4          0.78539816339744830962  /* pi/4       */
#define M_1_PI          0.31830988618379067154  /* 1/pi       */
#define M_2_PI          0.63661977236758134308  /* 2/pi       */
#define M_2_SQRTPI      1.12837916709551257390  /* 2/sqrt(pi) */
#define M_SQRT2         1.41421356237309504880  /* sqrt(2)    */
#define M_SQRT1_2       0.70710678118654752440  /* 1/sqrt(2)  */


__CCAPRICE_EXPORT double      acos  (double);
__CCAPRICE_EXPORT float       acosf (float);
__CCAPRICE_EXPORT long double acosl (long double);
__CCAPRICE_EXPORT double      asin  (double);
__CCAPRICE_EXPORT float       asinf (float);
__CCAPRICE_EXPORT long double asinl (long double);
__CCAPRICE_EXPORT double      atan  (double);
__CCAPRICE_EXPORT float       atanf (float);
__CCAPRICE_EXPORT long double atanl (long double);
__CCAPRICE_EXPORT double      atan2 (double, double);
__CCAPRICE_EXPORT float       atan2f(float, float);
__CCAPRICE_EXPORT long double atan2l(long double, long double);
__CCAPRICE_EXPORT double      ceil  (double);
__CCAPRICE_EXPORT float       ceilf (float);
__CCAPRICE_EXPORT long double ceill (long double);
__CCAPRICE_EXPORT double      fabs  (double);
__CCAPRICE_EXPORT float       fabsf (float);
__CCAPRICE_EXPORT long double fabsl (long double);
__CCAPRICE_EXPORT double      fmod  (double);
__CCAPRICE_EXPORT float       fmodf (float);
__CCAPRICE_EXPORT long double fmodl (long double);
__CCAPRICE_EXPORT double      log   (double);
__CCAPRICE_EXPORT float       logf  (float);
__CCAPRICE_EXPORT long double logl  (long double);
__CCAPRICE_EXPORT double      log10 (double);
__CCAPRICE_EXPORT float       log10f(float);
__CCAPRICE_EXPORT long double log10l(long double);
__CCAPRICE_EXPORT double      sqrt  (double);
__CCAPRICE_EXPORT float       sqrtf (float);
__CCAPRICE_EXPORT long double sqrtl (long double);

#ifdef __cplusplus
}
#endif

#endif /* !CCAPRICE_MATH_HDR */
