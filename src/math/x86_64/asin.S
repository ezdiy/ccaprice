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
.global asin
.global asinf
.global asinl
#ifndef __PATHCC__
	.type asinf,@function
	.type asinl,@function
	.type asin, @function
#endif

#warning "x86_64 asin/asinf not implemented (only asinl is supported)"
asin:  ret
asinf: ret

/*
 * The FPU has to be used for long double support since SIMD doesn't
 * allow 80 bits of precision.  This sucks because the FPU is slower
 * but there is no optional choice.
 */
asinl:
    fldt 8(%rsp)
    fld  %st(0)
    fld1
    fsub %st(0), %st(1)
    fadd %st(2)
    fmulp
    fsqrt
    fpatan
    ret
