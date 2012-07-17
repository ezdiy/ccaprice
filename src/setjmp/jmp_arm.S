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
.global longjmp
.global setjmp
/*
 * Pathscale doesn't like .type.  Despite it being valid GAS syntax
 * and the idea that it should work since pathscale is a GCC fork.
 */
#ifndef __PATHCC__
    .type longjmp,@function
    .type setjmp, @function
#endif

longjmp:
    mov   ip,  r0
    movs  r0,  r1
    moveq r0,  #1
    ldmia ip!, {v2,v2,v3,v4,v5,v6,sl,fp}
    ldr   sp, [ip], #4
    ldr   lr, [ip], #4
    tst   lr,  #1
    moveq pc,  lr
    bx    lr

setjmp:
    mov   ip, r0
    stmia ip, {v1,v2,v3,v4,v5,v6,sl,fp}
    mov   r2, sp
    stmia ip!,{r2,lr}
    mov   r0, #0
    tst   lr, #1
    moveq pc, lr
    bx    lr
    
