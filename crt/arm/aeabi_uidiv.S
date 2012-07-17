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

AEABI_LABEL(uidiv)
    push  {r7, lr}
    mov    r7, sp 
    clz    r2, r0
    tst    r1, r1
    clz    r3, r1
    mov    ip, #0
    beq    LOCAL_SYM(ret)
    mov    lr, #1
    subs   r3, r3, r2
    blt    LOCAL_SYM(ret)

LOCAL_LABEL(loop)
    subs   r2, r0, r1, lsl r3
    orrhs  ip, ip, lr, lsl r3
    movhs  r0, r2
    subsne r3, r3, #1
    bhi    LOCAL_SYM(loop)
    
LOCAL_LABEL(ret)
    mov    r0, ip
    pop   {r7, pc}
