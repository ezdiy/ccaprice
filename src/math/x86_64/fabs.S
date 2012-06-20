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
.global fabs
.global fabsf
.global fabsl
/*
 * Pathscale doesn't like .type.  Despite it being valid GAS syntax
 * and the idea that it should work since pathscale is a GCC fork.
 */
#ifndef __PATHCC__
    .type fabs,   @function
    .type fabsf,  @function
    .type fabsl,  @function
#endif


fabs:
    xor   %eax,        %eax
    dec   %rax
    shr   %rax
    movq  %rax,        %xmm1
    andpd %xmm1,       %xmm0
    ret
    
fabsf:
    mov   $0x7FFFFFFF, %eax
    movq  %rax,        %xmm1
    andps %xmm1,       %xmm0
    ret

/*
 * The FPU has to be used for long double support since SIMD doesn't
 * allow 80 bits of precision.  This sucks because the FPU is slower
 * but there is no optional choice.
 */
fabsl:
    fldt 8(%rsp)
    fabs
    ret
