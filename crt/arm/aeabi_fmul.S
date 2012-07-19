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

EXPORT_LOCAL_SYM(fmul_n) /* NAN       */
EXPORT_LOCAL_SYM(fmul_i) /* INF       */
EXPORT_LOCAL_SYM(fmul_z) /* ZERO      */
EXPORT_LOCAL_SYM(fmul_d) /* DENORMALS */
EXPORT_LOCAL_SYM(fmul_u)

AEABI_LABEL(fmul)
    mov            ip,  #0xFF
    and            r2,  ip, r0, lsr #23
    doit           ne,  tt
    cond(and,s,ne) r3,  ip, r1, lsr #23
    teqne          r2,  ip
    teqne          r3,  ip
    beq            LOCAL_SYM(fmul_s)

LOCAL_LABEL(fmul_x)
    /*
     * Add the exponents together to determine the final sign
     * using the `eor` instruction.
     */
    add            r2,  r2, r3  @ Add exponents
    eor            ip,  r0, r1  @ Determine sign
    
    /*
     * Convert the mantissa to an unsigned integral value.  If the
     * result is POT (power of two), branch to a seperate path and
     * handle that there. Make up for final alignment as well.
     */
    movs           r0,  r0, lsl #9
    doit           ne
    cond(mov,s,ne) r1,  r1, lsl #9
    beq            LOCAL_SYM(fmul_l)
    mov            r3,  #0x08000000
    orr            r0,  r3, r0, lsr #5
    orr            r1,  r3, r1, lsr #5
    
    /*
     * TODO: Support for ARM < 4.  There is no umull instruction
     * on any ARM's predating the ARM4 architecture.
     */
    umull          r3,  r1, r0, r1
    and            r0,  ip, #0x80000000
    cmp            r1,  #(1 << 23)
    doit           cc,  tt
    movcc          r1,  r1, lsl #1
    orrcc          r1,  r1, r3, lsr #31
    movcc          r3,  r3, lsl #1
    
    orr            r0,  r0, r1  @ Add the sign value to the result
    
    /*
     * Here we apply the exponent bias while checking for any possible
     * under or overflows (branching off to fmul_u to handle that)
     */
    sbc            r2,  r3, #127
    cmp            r2,  #(254-1)
    bhi            LOCAL_SYM(fmul_u)
    
    /*
     * Round the resulting value and merge the final exponent to it
     * this is all achived with adc.
     */
    cmp            r3,  #0x80000000
    adc            r0,  r0, r2, lsl #23
    doit           eq
    biceq          r0,  r0, #1
    sret

/*
 * MUL 0x1p*: to skip a lot of wasteless code.
 * This idea comes from llvm-gcc ieee754-sf.S
 */
LOCAL_LABEL(fmul_l)
    teq            r0,  #0
    and            ip,  ip, #0x80000000
    doit           eq
    moveq          r1,  r1, lsl #9
    orr            r0,  ip, r0, lsr #9
    orr            r0,  r0, r1, lsr #9
    subs           r2,  r2, #127
    doit           gt,  tt
    cond(rsb,s,gt) r3,  r2, #255
    orrgt          r0,  r0, r2, lsl #23
    mret(gt)
    
    /*
     * Handle all underflow / overflows here accordingly.
     * NOTE: this just fixes it up for the fmul_u below.
     */
    orr            r0,  r0, #0x00800000
    mov            r3,  #0
    subs           r2,  r2, #1

LOCAL_LABEL(fmul_u)
    bgt            LOCAL_SYM(fmul_o)  @ Overflowed -> fmul_o
    cmn            r2,  #(24+1)
    doit           le,  t
    bicle          r0,  r0, #0x7FFFFFFF
    
    /*
     * Shift value right and round the result.
     * NOTE: this can be optimized
     */
    rsb            r2,  r2, #0
    movs           r1,  r0, lsl #1
    shift1         lsr, ip, r0, r2
    rsb            r2,  r2, #32
    shift1         lsl, ip, r0, r2
    movs           r0,  r1, rrx
    adc            r0,  r0, #0
    orrs           r3,  r3, ip, lsl #1
    doit           eq
    biceq          r0,  r0, ip, lsr #31
    sret
    
/*
 * Some arguments are denormalized, so we must scale them
 * left to preserve the sign bit.  The amount we scale them
 * must be computed.  This is all done here.
 */
LOCAL_LABEL(fmul_d)
    teq            r2,  #0
    and            ip,  r0, #0x80000000
   
1:  doit           eq,  tt
    moveq          r0,  r0, lsl #1
    tsteq          r0,  #0x00800000
    subeq          r2,  r2, #1
    beq            1b
    orr            r0,  r0, ip
    teq            r3,  #0
    and            ip,  r1, #0x80000000
2:  doit           eq,  tt
    moveq          r1,  r1, lsl #1
    
    tsteq          r1,  #0x00800000
    subeq          r3,  r3, #1
    beq            2b
    orr            r1,  r1, ip
    b              LOCAL_SYM(fmul_x)

LOCAL_LABEL(fmul_s)
    /*
     * Isolate and remove the INF and NAN cases since this is for
     * handling denormalized situations.
     */
    and            r3,  ip, r1, lsr #23
    teq            r2,  ip
    doit           ne
    teqne          r3,  ip
    beq            1f

    /*
     * Here arguments are denormalized or zero.  We handle those
     * accordingly to branch back to dmul_d
     */
    bics           ip,  r0, #0x80000000
    doit           ne
    cond(bic,s,ne) ip,  r1, #0x80000000
    bne            LOCAL_SYM(fmul_d)

/*
 * Result is zero but we determine the sign anyways so we don't use
 * another branch.  Computing sign for any case is cheaper.
 */
LOCAL_LABEL(fmul_z)
    eor            r0,  r0, r1
    bic            r0,  r0, #0x7fffffff
    sret

    /*
     * Arguments are either INF or NAN.  I should note the previous
     * comments about arguments are always about one or BOTH args.
     */
1:  teq            r0,  #0x0
    doit           ne,  ett
    teqne          r0,  #0x80000000
    moveq          r0,  r1
    teqne          r1,  #0x0
    teqne          r1,  #0x80000000
    beq            LOCAL_SYM(fmul_n)
    teq            r2,  ip
    bne            1f
    movs           r2,  r0, lsl #9
    bne            LOCAL_SYM(fmul_n)
1:  teq            r3,  ip
    bne            LOCAL_SYM(fmul_i)
    movs           r3,  r1, lsl #9
    doit           ne
    movne          r0,  r1
    bne            LOCAL_SYM(fmul_n)

/*
 * The result is INF, but the sign needs to be determined.
 * I always figured -INF would be +INF-1 :P
 */
LOCAL_LABEL(fmul_i)
    eor            r0,  r0, r1

/*
 * Overflow handling we return INF.  The neat thing is the sign is
 * already stored.
 */
LOCAL_LABEL(fmul_o)
    and            r0,  r0, #0x80000000
    orr            r0,  r0, #0x7F000000
    orr            r0,  r0, #0x00800000
    sret

/*
 * Handle quiet NAN's here, and we're DONE! What a support for double
 * multiplication support.
 */
LOCAL_LABEL(fmul_n)
    orr            r0,  r0, #0x7F000000
    orr            r0,  r0, #0x00c00000
    sret
