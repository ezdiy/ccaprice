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
#ifndef CCAPRICE_FLOAT_HDR
#define CCAPRICE_FLOAT_HDR

/*
 * These are fairly universal values.  I don't suspect these to be any
 * different across most desktop PCs.  TODO:  Better compatability for
 * future (possible ports to other architectures).
 */
#define FLT_RADIX        2

#define FLT_MIN          1.17549435e-38F
#define FLT_MAX          3.40282347e+38F
#define FLT_EPSILON      1.19209290e-07F

#define FLT_MANT_DIG     24
#define FLT_MIN_EXP      (-125)
#define FLT_MAX_EXP      128

#define FLT_DIG          6
#define FLT_MIN_10_EXP   (-37)
#define FLT_MAX_10_EXP   38

#define DBL_MIN          2.2250738585072014e-308
#define DBL_MAX          1.7976931348623157e+308
#define DBL_EPSILON      2.2204460492503131e-16

#define DBL_MANT_DIG     53
#define DBL_MIN_EXP      (-1021)
#define DBL_MAX_EXP      1024

#define DBL_DIG          15
#define DBL_MIN_10_EXP   (-307)
#define DBL_MAX_10_EXP   308

#endif
