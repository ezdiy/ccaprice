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

AEABI_LABEL(dmul)
    stmfd  sp!, {r4, r5, r6, lr}
    
    /*
     * Masking out various components while trapping any possible
     * zero, denormal, INF, or NAN.
     */
    mov    ip, #0xFF
    orr    ip, ip, #0x700
    ands   r4, ip, xh, lsr #20
    andnes r5, ip, yh, lsr #20
    teqne  r4, ip
    teqne  r5, ip
    bleq   LOCAL_SYM(dmul_s)
    
    /*
     * Add the exponents together to determine the final sign
     * using the `eor` instruction.
     */
    add    r4, r4, r5
    eor    r6, xh, yh
    
    /*
     * Convert the mantissa into an unsigned integral.  If the value
     * is POT (power of two) we branch it to a seperate path.
     */
    bic    xh, xh, ip, lsl #21
    bic    yh, yh, ip, lsl #21
    orrs   r5, xl, xh, lsl #12
    orrnes r5, yl, yh, lsl #12
    orr    xh, xh, #0x00100000
    orr    yh, yh, #0x00100000
    beq    LOCAL_SYM(dmul_1)
    
    /*
     * TODO: Support for ARM < 4.  There is no umull instruction
     * on any ARM's predating the ARM4 architecture.
     */
    umull  ip, lr, xl, yl
    mov    r5, #0
    umlal  lr, r5, xh, yl
    and    yl, r6, #0x80000000
    umlal  lr, r5, xl, yh
    mov    r6, #0
    umlal  r5, r6, xh, yh
    
    /*
     * The least significant bits in `ip` aren't significant entierly.
     * The state of the multiplication only makes the LSB significant
     * for the final rounding.  So we fold them into lr.
     */
    teq    ip, #0
    orrne  lr, lr, #1
    
    /*
     * Readjust the result upon the mosr significant bit position
     * otherwise shifting to the final position to add a sign to
     * the result is not possible.
     */
    sub    r4, r4, #0xFF
    cmp    r6, #(1 << (20 -11))
    sbc    r4, r4, #0x300
    bcs    1f
    movs   lr, lr, lsl #1
    adcs   r5, r5, r5
    adc    r6, r6, r6
1:
    /*
     * We shift to the final position now since the result has
     * been adjusted to allow this.
     */
    orr    xh, yl, r6, lsl #11
    orr    xh, xh, r5, lsr #11
    mov    xl, r5, lsl #11
    orr    xl, xl, lr, lsr #21
    mov    lr, lr, lsl #11
    
    /*
     * Check the exponent range for any sign of an underflow or
     * overflow and handle by branching off with bhi
     */
    subs   ip, r4, #(254-1)
    cmphi  ip, #0x700
    bhi    LOCAL_SYM(dmul_u)
    
    /*
     * Finally round the result and merge the final exponent
     * and return.
     */
    cmp    lr, #0x80000000
    moveqs lr, xl, lsr #1
    adcs   xl, xl, #0
    adc    xh, xh, r4, lsl #20
    RLDM  "r4, r5, r6"

LOCAL_LABEL(dmul_1)
    and    r6, r6, #0x80000000
    orr    xh, r6, xh
    orr    xl, xl, yl
    eor    xh, xh, yh
    subs   r4, r4, ip, lsl #1
    rsbgts r5, r4, ip
    orrgt  xh, xh, r4, lsl #20
    RLDM  "r4, r5, r6" gt
    
    /*
     * This is an annoying hack to fix things for underflow and
     * overflows.
     */
    orr    xh, xh, #0x00100000
    mov    lr, #0
    subs   r4, r4, #1
    
LOCAL_LABEL(dmul_u)
    /*
     * Overflow? Branch to __dmul_o and handle accordingly.
     * This is annoying because it slows us down, but this must
     * be handled inorder to stay IEEE754 compatible.
     */
    bgt    LOCAL_SYM(dmul_o)
    
    /*
     * Check is it's possible for a denormalized result.  Otherwise we
     * just return a signed zero.
     */
    cmn    r4, #(53 + 1)
    movle  xl, #0
    bicle  xh, xh, #0x7FFFFFFF
    RLDM  "r4, r5, r6" le
    
    /*
     * Calculate the correct shift value then use that to shift the
     * result right of 1 to 20 bits, while perserving the sign bit and
     * finally rounding it.
     */
    rsb    r4, r4, #0
    subs   r4, r4, #32
    bge    2f
    adds   r4, r4, #12
    bgt    1f
    
    add    r4, r4, #20
    rsb    r5, r4, #32
    mov    r3, xl, lsl r5
    mov    xl, xl, lsl r4
    orr    xl, xl, xh, lsl r5
    and    r2, xh, #0x80000000
    bic    xh, xh, #0x80000000
    adds   xl, xl, r3, lsr #31
    adc    xh, r2, xh, lsr r4
    orrs   lr, lr, r3, lsl #1
    biceq  xl, xl, r3, lsr #31
    RLDM  "r4, r5, r6"
    
    /*
     * Shift the result right of the 21 to 31 bit mark, or left 11 bits
     * to 1 bits after a register from xh to xl.  Then round the result.
     */
1:  rsb    r4, r4, #12
    rsb    r5, r4, #32
    mov    r3, xl, lsl r4
    mov    xl, xl, lsr r5
    orr    xl, xl, xh, lsl r4
    bic    xh, xh, #0x7fffffff
    adds   xl, xl, r3, lsr #31
    adc    xh, xh, #0
    orrs   lr, lr, r3, lsl #1
    biceq  xl, xl, r3, lsr #31
    RLDM  "r4, r5, r6"
    
    /*
     * Shift the value right of the 32 to 64 bit mark, or 0 bit to 32
     * bits after a switch of xh to xl.  The leftover bits are stored
     * in re0r60lr for rounding.
     */
2:  rsb    r5, r4, #32
    orr    lr, lr, xl, lsl r5
    mov    r3, xl, lsr r4
    orr    r3, r3, xh, lsl r5
    mov    xl, xh, lsr r4
    bic    xh, xh, #0x7fffffff
    bic    xl, xl, xh, lsr r4
    add    xl, xl, r3, lsr #31
    orrs   lr, lr, r3, lsl #1
    biceq  xl, xl, r3, lsr #31
    RLDM  "r4, r5, r6"
    
/*
 * Some arguments are denormalized, so we must scale them
 * left to preserve the sign bit.  The amount we scale them
 * must be computed.  This is all done here.
 */
LOCAL_LABEL(dmul_d)
    teq    r4, #0
    bne    2f
    and    r6, xh, #0x80000000
1:  movs   xl, xl, lsl #1
    adc    xh, xh, xh
    tst    xh, #0x00100000
    subeq  r4, r4, #1
    beq    1b
    orr    xh, xh, r6
    teq    r5, #0
    movne  pc, lr
2:  and    r6, yh, #0x80000000
3:  movs   yl, yl, lsl #1
    adc    yh, yh, yh
    tst    yh, #0x00100000
    subeq  r5, r5, #1
    beq    3b
    orr    yh, yh, r6
    mov    pc, lr

LOCAL_LABEL(dmul_s)
    /*
     * Isolate and remove the INF and NAN cases since this is for
     * handling denormalized situations.
     */
    teq    r4, ip
    and    r5, ip, yh, lsr #20
    teqne  r5, ip
    beq    1f
    
    /*
     * Here arguments are denormalized or zero.  We handle those
     * accordingly to branch back to dmul_d
     */
    orrs   r6, xl, xh, lsl #1
    orrnes r6, yl, yh, lsl #1
    bne    LOCAL_SYM(dmul_d)
    
/*
 * Result is zero but we determine the sign anyways so we don't use
 * another branch.  Computing sign for any case is cheaper.
 */
LOCAL_LABEL(dmul_z)
    eor    xh, xh, yh
    bic    xh, xh, #0x7FFFFFFF
    mov    xl, #0
    RLDM  "r4, r5, r6"

    /*
     * Arguments are either INF or NAN.  I should note the previous
     * comments about arguments are always about one or BOTH args.
     */
1:  orrs   r6, xl, xh, lsl #1
    moveq  xl, yl
    moveq  xh, yh
    orrnes r6, yl, yh, lsl #1
    beq    LOCAL_SYM(dmul_n)
    teq    r4, ip
    bne    1f
    orrs   r6, xl, xh, lsl #12
    bne    LOCAL_SYM(dmul_n)
1:  teq    r5, ip
    bne    LOCAL_SYM(dmul_i)
    orrs   r6, yl, yh, lsl #12
    movne  xl, yl
    movne  xh, yh
    bne    LOCAL_SYM(dmul_n)
    
/*
 * The result is INF, but the sign needs to be determined.
 * I always figured -INF would be +INF-1 :P
 */
LOCAL_LABEL(dmul_i)
    eor    xh, xh, yh
    
/*
 * Overflow handling we return INF.  The neat thing is the sign is
 * already stored in XH.
 */
LOCAL_LABEL(dmul_o)
    and    xh, xh, #0x80000000
    orr    xh, xh, #0x7F000000
    orr    xh, xh, #0x00F00000
    mov    xl, #0
    RLDM  "r4, r5, r6"
    
/*
 * Handle quiet NAN's here, and we're DONE! What a support for double
 * multiplication support.
 */
LOCAL_LABEL(dmul_n)
    orr    xh, xh, #0x7F000000
    orr    xh, xh, #0x00F80000
    RLDM  "r4, r5, r6"
