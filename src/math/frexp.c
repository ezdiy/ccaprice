/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * ====================================================
 *
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
#include "inc/math.h"

double frexp(double x, int *p) {
	int x_hi = __CCAPRICE_MATH_HI_L(x);
	int x_lo = __CCAPRICE_MATH_LO_L(x);
	int iter = 0x7FFFFFFF & x_hi;
	
	*p = 0;
	if (iter >=0x7FFFFFFF || ((iter | x_lo) == 0))
		return x;
		
	if (iter < 0x00100000) {
		x   *= 1.80143985094819840000e+16;
		x_hi = __CCAPRICE_MATH_HI_L(x);
		x_lo = __CCAPRICE_MATH_LO_L(x);
		iter = x_hi & 0x7FFFFFFF;
		*p   = -54;
	}
	*p  += (iter >> 20) - 1022;
	x_hi = (x_hi & 0x800FFFFF) | 0x3FE00000;
	
	__CCAPRICE_MATH_HI_L(x) = x_hi;
	return x;
}
