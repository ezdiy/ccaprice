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
#include <math.h>

double floor(double x) {
    unsigned i,j;

    int x_hi =  __CCAPRICE_MATH_HI_L(x);
    int x_lo =  __CCAPRICE_MATH_LO_L(x);
    int iter = ((x_hi>>20)&0x7ff)-0x3ff;

    if (iter < 20) {
        if (iter < 0) {
            if (1.0e300+x > 0.0) {
                if(x_hi >= 0)
                    x_hi = 0x00000000, x_lo = 0x00000000;
                else if (((x_hi & 0x7FFFFFFF) | x_lo) != 0)
                    x_hi = 0xbff00000, x_lo = 0x00000000;
            }
        } else {
            i = (0x000FFFFF) >> iter;
            if (((x_hi & i) | x_lo) == 0)
                return x;
            if (1.0e300+x > 0.0)
                x_hi = (x_hi<0) ? (x_hi+(0x00100000>>iter)) : x_hi, x_hi &= (~i), x_lo=0;
        }
    } else if (iter > 51)
        return (iter==0x400)?x+x:x;
    else {
        i = ((unsigned)(0xFFFFFFFF)) >> (iter - 20);
        if ((x_lo & i) == 0)
            return x;
        if (1.0e300+x > 0.0) {
            if (x_hi < 0) {
                if (iter == 20)
                    x_hi ++;
                else
                    j = x_lo + (1<<(52-iter)), x_hi = (j < x_lo) ? x+1: x, x_lo = j;
            }
            x_lo &= (~i);
        }
    }
    __CCAPRICE_MATH_HI_L(x) = x_hi;
    __CCAPRICE_MATH_LO_L(x) = x_lo;
    return x;
}
