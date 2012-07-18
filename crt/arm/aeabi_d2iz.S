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
#include "asm.h"
.align 3

AEABI_LABEL(d2iz)
    mov    r2, xh, lsl #1
    adds   r2, r2, #(1 << 21)
    bcs    2f
    bpl    1f
    mov    r3, #(0xFFFFFC00 + 31)
    subs   r2, r3, r2, asr #21
    bls    3f
    
    /*
     * Scale the value accordingly while managing
     * The sign bit.
     */
    mov    r3, xh, lsl #11
    orr    r3, r3, #0x80000000
    orr    r3, r3, xl, lsl #21
    tst    xh, #0x80000000
    shift1 lsr, r0, r3, r2
    doit   ne
    rsbne  r0, r0, #0
    sret
    
1:  mov    r0, #0
    sret
    
2:  orrs   xl, xl, xh, lsl #12
    bne    4f                    @ is nan?
    
3:  ands   r0, xh, #0x80000000   @ sign bit
    doit   eq
    moveq  r0, #0x7FFFFFFF
    sret
    
4:  mov    r0, #0
    sret
    
