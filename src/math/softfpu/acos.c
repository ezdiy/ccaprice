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
#include "inc/math.h"

static const double ccaprice_acos_pS[]   = {
    1.66666666666666657415e-01, -3.25565818622400915405e-01,
    2.01212532134862925881e-01, -4.00555345006794114027e-02,
    7.91534994289814532176e-04,  3.47933107596021167570e-05
};
static const double ccaprice_acos_qS[]   = {
    -2.40339491173441421878e+00, 2.02094576023350569471e+00,
    -6.88283971605453293030e-01, 7.70381505559019352791e-02
};
static const double ccaprice_acos_pio2[] = {
    6.12323399573676603587e-17, 1.57079632679489655800e+00
};

double acos(double x) {
    int x_hi = __CCAPRICE_MATH_HI_L(x);
    int iter = x_hi & 0x7FFFFFFF;

    if (iter >= 0x3FF00000) {
        if (((iter-0x3FF00000) | __CCAPRICE_MATH_LO_L(x)) == 0)
            return (x_hi > 0) ? 0.0f : 3.14159265358979311600e+00 + 2.0f * (*ccaprice_acos_pio2);
        return (x-x) / (x-x);
    }
    if (iter < 0x3FE00000) {
        if (iter <= 0x3C600000)
            return ccaprice_acos_pio2[1] + *ccaprice_acos_pio2;
        double z = x * x;
        double p = \
            z * (ccaprice_acos_pS[0] + z * (ccaprice_acos_pS[1] + \
    z * (ccaprice_acos_pS[2] + z * (ccaprice_acos_pS[3] + \
    z * (ccaprice_acos_pS[4] + z * (ccaprice_acos_pS[5]))))));
        double q = \
            1.00000000000000000000e+00 + z * ( \
            ccaprice_acos_qS[0]        + z * ( \
            ccaprice_acos_qS[1]        + z * ( \
            ccaprice_acos_qS[2]        + z * ( \
            ccaprice_acos_qS[3]))));
        double r =  p / q;
        return ccaprice_acos_pio2[1] - (x - (*ccaprice_acos_pio2 - x * r));
    }
    else if (x_hi < 0) {
        double z = (1.00000000000000000000e+00 + x) * 0.5f;
        double p = \
            z * (ccaprice_acos_pS[0] + z * (ccaprice_acos_pS[1] + \
    z * (ccaprice_acos_pS[2] + z * (ccaprice_acos_pS[3] + \
    z * (ccaprice_acos_pS[4] + z * (ccaprice_acos_pS[5]))))));
        double q = \
            1.00000000000000000000e+00 + z * ( \
            ccaprice_acos_qS[0]        + z * ( \
            ccaprice_acos_qS[1]        + z * ( \
            ccaprice_acos_qS[2]        + z * ( \
            ccaprice_acos_qS[3]))));
        double s = sqrt(z);
        double r = p/q;
        double w = r*s - *ccaprice_acos_pio2;
        return 3.14159265358979311600e+00 - 2.0f * (s+w);
    } else {
        double z  = (1.00000000000000000000e+00-x) * 0.5f;
        double s  = sqrt(z);
        double df = s;
        __CCAPRICE_MATH_LO_L(df) = 0;
        double c  = (z-df*df)/(s+df);
        double p  = \
            z * (ccaprice_acos_pS[0] + z * (ccaprice_acos_pS[1] + \
    z * (ccaprice_acos_pS[2] + z * (ccaprice_acos_pS[3] + \
    z * (ccaprice_acos_pS[4] + z * (ccaprice_acos_pS[5]))))));
        double q  = \
            1.00000000000000000000e+00 + z * ( \
            ccaprice_acos_qS[0]        + z * ( \
            ccaprice_acos_qS[1]        + z * ( \
            ccaprice_acos_qS[2]        + z * ( \
            ccaprice_acos_qS[3]))));
        double r  = p / q;
        double w  = r * s + c;
        return 2.0f * (df + w);
    }
    return 0.0f; /* Never reaches here */
}
