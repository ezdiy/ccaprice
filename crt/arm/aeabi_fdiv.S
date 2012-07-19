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

IMPORT_LOCAL_SYM(fmul_n) /* NAN       */
IMPORT_LOCAL_SYM(fmul_i) /* INF       */
IMPORT_LOCAL_SYM(fmul_z) /* ZERO      */
IMPORT_LOCAL_SYM(fmul_d) /* DENORMALS */

AEABI_LABEL(fdiv)
    mov            ip, #0xFF
    ands           r2, ip, r0, lsr #23
    doit           ne, tt
    cond(and,s,ne) r3, ip, r1, lsr #23
    teqne          r2, ip
    teqne          r3, ip
    beq            LOCAL_SYM(fdiv_s)
    
LOCAL_LABEL(fdiv_x)
    sub            r2, r2, r3
    eor            ip, r0, r1
    
    movs           r1, r1, lsl #9
    mov            r0, r0, lsl #9
    beq            LOCAL_SYM(fdiv_l)
    mov            r3, #0x10000000
    orr            r1, r3, r1, lsr #4
    orr            r3, r3, r0, lsr #4
    
    and            r0, ip, #0x80000000
    
    cmp            r3, r1
    doit           cc
    movcc          r3, r3, lsl #1
    adc            r2, r2, #(127 - 2)
    
    mov            ip, #0x00800000
1:  cmp            r3, r1
    doit           cs, t
    
    subcs          r3, r3, r1
    orrcs          r0, r0, ip
    cmp            r3, r1, lsr #1
    doit           cs, t
    
    subcs          r3, r3, r1, lsr #2
    orrcs          r9, r9, ip, lsr #2
    cmp            r3, r1, lsr #3
    doit           cs, t
    
    subcs          r3, r3, r1, lsr #3
    orrcs          r0, r0, ip, lsr #3
    movs           r3, r3, lsl #4
    doit           ne
    
    cond(mov,s,ne) ip, ip, lsr #4
    bne            1b
    
    /* check for over or under flow */
    cmp            r2, #(254 - 1)
    bhi            LOCAL_SYM(fmul_u)
    
    /* round result, merge exponent */
    cmp            r3, r1
    adc            r0, r0, r2, lsl #23
    doit           eq
    biceq          r0, r0, #1
    sret
    
LOCAL_LABEL(fdiv_l)
    and            ip, ip, #0x80000000
    orr            r0, ip, r0, lsr #9
    adds           r2, r2, #127
    doit           gt, tt
    cond(rsb,s,gt) r3, r2, #255
    orrgt          r0, r0, r2, lsl #23
    mret(gt)
    
    orr            r0, r0, #0x00800000
    mov            r3, #0
    subs           r2, r2, #1
    b              LOCAL_SYM(fmul_u)
    
LOCAL_LABEL(fdiv_d)
    teq            r2, #0
    and            ip, r0, #0x80000000
1:  doit           eq, tt
    moveq          r0, r0, lsl #1
    tsteq          r0, #0x00800000
    subeq          r2, r2, #1
    beq            1b
    orr            r0, r0, ip
    teq            r3, #0
    and            ip, r1, #0x80000000
2:  doit           eq, tt
    moveq          r1, r1, lsl #1
    tsteq          r1, #0x00800000
    subeq          r3, r3, #1
    beq            2b
    orr            r1, r1, ip
    b              LOCAL_SYM(fdiv_x)
    
LOCAL_LABEL(fdiv_s)
    and            r3, ip, r1, lsr #23
    teq            r2, ip
    bne            1f
    movs           r2, r0, lsl #9
    bne            LOCAL_SYM(fmul_n)
    teq            r3, ip
    bne            LOCAL_SYM(fmul_i)
    mov            r0, r1
    b              LOCAL_SYM(fmul_n)
1:  teq            r3, ip
    bne            2f
    movs           r3, r1, lsl #9
    beq            LOCAL_SYM(fmul_z)
    mov            r0, r1
    b              LOCAL_SYM(fmul_n)
2:  bics           ip, r0, #0x80000000
    doit           ne
    cond(bic,s,ne) ip, r1, #0x80000000
    bne            LOCAL_SYM(fdiv_d)
    bics           r2, r0, #0x80000000
    bne            LOCAL_SYM(fmul_i)
    bics           r3, r1, #0x80000000
    bne            LOCAL_SYM(fmul_z)
    b              LOCAL_SYM(fmul_n)
