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
.text
.global __ccaprice_main
.global _start
.global __ccaprice_syscall_arm

#ifndef __PATHCC__
.type   _start                ,%function
.type   __ccaprice_syscall_arm,%function
#endif

/*
 * TODO: figure this mess out.  It's rather confusing.
 */
_start:
    push {lr}

__ccaprice_syscall_arm:
    mov   ip, sp
    stmfd sp!,{r4,r5,r6,r7}
    mov   r7, r0
    mov   r0, r1
    mov   r1, r2
    mov   r2, r3
    ldmfd ip, {r3,r4,r5,r6}
    svc   0
    ldmfd sp!,{r4,r5,r6,r7}
    tst   lr, #1
    moveq pc, lr
    bx    lr

.size _start                ,.-_start
.size __ccaprice_syscall_arm,.-__ccaprice_syscall_arm
