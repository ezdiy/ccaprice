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
.syntax unified
.align 3

AEABI_LABEL(uidivmod)
    push  {lr}
    sub    sp, sp, #4
    mov    r2, sp
    bl     LOCAL_SYM(divmod)
    ldr    r1, [sp]
    add    sp, sp, #4
    pop   {pc}
    
LOCAL_LABEL(divmod)
    push  {r4, r7, lr}
    add    r7, sp, #4
    clz    r4, r0
    tst    r1, r1
    clz    r3, r1
    mov    ip, #0
    beq    LOCAL_SYM(ret)
    mov    lr, #1
    subs   r3, r3, r4
    blt    LOCAL_SYM(ret)
    
LOCAL_LABEL(loop)
    subs   r4, r0, r1, lsl r3
    orrhs  ip, ip, lr, lsl r3
    movhs  r0, r4
    subsne r3, r3, #1
    bhi    LOCAL_SYM(loop)
    subs   r4, r0, r1
    orrhs  ip, r0, r1
    movhs  r0, r4
    
LOCAL_LABEL(ret)
    str    r0, [r2]
    mov    r0, ip
    
