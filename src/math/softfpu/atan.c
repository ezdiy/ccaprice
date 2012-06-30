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

static const double ccaprice_atan_hi[] = {
    4.63647609000806093515e-01,  7.85398163397448278999e-01,
    9.82793723247329054082e-01,  1.57079632679489655800e+00
};
static const double ccaprice_atan_lo[] = {
    2.26987774529616870924e-17,  3.06161699786838301793e-17,
    1.39033110312309984516e-17,  6.12323399573676603587e-17
};
static const double ccaprice_atan_at[] = {
    3.33333333333329318027e-01, -1.99999999998764832476e-01,
    1.42857142725034663711e-01, -1.11111104054623557880e-01,
    9.09088713343650656196e-02, -7.69187620504482999495e-02,
    6.66107313738753120669e-02, -5.83357013379057348645e-02,
    4.97687799461593236017e-02, -3.65315727442169155270e-02,
    1.62858201153657823623e-02
};

double atan(double x) {
    int x_hi = __CCAPRICE_MATH_HI_L(x);
    int x_id = 0x00000000;
    int iter = x_hi & 0x7FFFFFFFF;

    if (iter >= 0x44100000) {
        if (iter > 0x7FF00000 || (iter == 0x7FF00000 && (__CCAPRICE_MATH_LO_L(x) != 0)))
            return x+x; /* NaN */
        return (x_hi > 0)?ccaprice_atan_hi[3]+ccaprice_atan_lo[3]:
                 -ccaprice_atan_hi[3]-ccaprice_atan_lo[3];
    }
    if (iter < 0x3FDC0000) {
        if (iter < 0x3E200000 && 1.0e300+x > 1.0)
            return x;
        x_id = -1;
    } else {
        x = fabs(x);
        if (iter < 0x3FF30000) {
            if (iter < 0x3FE60000) x_id = 0, x = (2.0*x-1.0)/(2.0+x);
            else                   x_id = 1, x = (x-1.0)/(x+1.0);
        } else {
            if (iter < 0x40038000) x_id = 2, x = (x-1.5)/(1.0+1.5*x);
            else                   x_id = 3, x = -1.0/x;
        }
    }
    double z  = x*x;
    double w  = z*z;
    double s1 = z * (ccaprice_atan_at[0x00]+w*(ccaprice_atan_at[0x02]+w*
            (ccaprice_atan_at[0x04]+w*(ccaprice_atan_at[0x06]+w*
            (ccaprice_atan_at[0x08]+w*(ccaprice_atan_at[0x0A]))))));
    double s2 = w * (ccaprice_atan_at[0x01]+w*(ccaprice_atan_at[0x03]+w*
            (ccaprice_atan_at[0x05]+w*(ccaprice_atan_at[0x07]+w*
            (ccaprice_atan_at[0x09])))));
    if (!(x_id < 0)) {
        z = ccaprice_atan_hi[x_id] - ((x*(s1+s2)-ccaprice_atan_lo[x_id])-x);
        return (x_hi < 0) ? -z:z;
    }
    return x - x * (s1 + s2);
}
