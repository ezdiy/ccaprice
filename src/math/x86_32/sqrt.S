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
.global sqrt
.global sqrtf
.global sqrtl
/*
 * Pathscale doesn't like .type.  Despite it being valid GAS syntax
 * and the idea that it should work since pathscale is a GCC fork.
 */
#ifndef __PATHCC__
    .type sqrt,   @function
    .type sqrtf,  @function
    .type sqrtl,  @function
#endif

/*
 * All of the following is required to stay conformant with the way
 * sqrt is intended to work. `fsqrt` while being simpler and quicker
 * to use and return with isn't actually what the standard says we
 * have to do.  However sqrtf, and sqrtl can.
 */
sqrt:
    fldl 4(%esp)
    fsqrt
    fstsw %ax
    sub $12, %esp
    fld %st(0)
    fstpt (%esp)
    mov (%esp), %ecx
    and $0x7FF, %ecx
    cmp $0x400, %ecx
    jnz 1f
    and $0x200, %eax
    sub $0x100, %eax
    sub %eax,  (%esp)
    fstp %st(0)
    fldt (%esp)
1:
    add $12, %esp
    fstpl  4(%esp)
    fldl   4(%esp)
    ret
    
sqrtf:
    flds  4(%esp)
    fsqrt
    fstps 4(%esp)
    flds  4(%esp)
    ret
    
sqrtl:
    fldt  4(%esp)
    fsqrt
    ret
