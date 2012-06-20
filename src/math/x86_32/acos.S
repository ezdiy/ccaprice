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
.global acosf
.global acosl
.global acos
/*
 * Pathscale doesn't like .type.  Despite it being valid GAS syntax
 * and the idea that it should work since pathscale is a GCC fork.
 */
#ifndef __PATHCC__
	.type acosf,@function
	.type acosl,@function
	.type acos, @function
#endif

acosf:
    flds 4(%esp)
    jmp  1f

acosl:
    fldt 4(%esp)
    jmp  1f
    
acos:
    fldt 4(%esp)
1:  fld  %st(0)
    fld1
    fsub %st(0), %st(1)
    fadd %st(2)
    fmulp
    fsqrt
    fabs
    fxch %st(1)
    fpatan
    ret
