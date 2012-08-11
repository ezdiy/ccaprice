/*
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
#include <bits/asm.h>
.global sin
.global sinf
.global sinl

sin:
    fldl   4(%esp)
    jmp    L3
    
sinl:
    fldt   4(%esp)
    jmp    L3
    
sinf:
    flds   4(%esp)
    jmp    L3
    
    
L1: fldpi
    fld    %st(0)
    faddp  %st, %st(0)
    fxch   %st(1)
    
L2: fprem1
    fstsw  %ax
    sahf
    jp     L2
    fxch   %st(1)
    fstp   %st(0)
L3:
    fsin
    fstsw  %ax
    sahf
    jp     L1
    ret
