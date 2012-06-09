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
#include "ccaprice.h"
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

/* Math constants */
#define M_1_PI  (0.3183098861837907)
#define M_2_PI  (0.6366197723675814)
#define M_E     (2.7182818284590450)
#define M_EULER (0.5772156649015329)
#define M_PI    (3.1415926535897932)
#define M_PI_2  (1.5707963267948966)
#define M_PI_4  (0.7853981633974483)
#ifdef __CCAPRICE_EXTENSIONS
#	define M_TAU   (6.2831853071795864)
#endif

__CCAPRICE_EXPORT int    abs   (int); /* STDLIB-ify */
__CCAPRICE_EXPORT double acos  (double);
__CCAPRICE_EXPORT double atan  (double);
__CCAPRICE_EXPORT double ceil  (double);
__CCAPRICE_EXPORT double fabs  (double);
__CCAPRICE_EXPORT int    finite(double);
__CCAPRICE_EXPORT double floor (double);
__CCAPRICE_EXPORT double frexp (double, int*);
__CCAPRICE_EXPORT int    ilogb (double);
__CCAPRICE_EXPORT int    isnan (double);
__CCAPRICE_EXPORT double sqrt  (double);
#endif /* !CCAPRICE_MATH_HDR */
