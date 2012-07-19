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
#ifndef __CCAPRICE_CRT_ARM_ASM_HDR
#define __CCAPRICE_CRT_ARM_ASM_HDR

/*
 * For double precision floating point only.
 * The endianess order is different between the
 * FPA and VFP.
 */
#if defined(__VFP_FP__) && !defined(__ARMEB__)
#   define xl r0
#   define xh r1
#   define yl r2
#   define yh r3
#else
#   define xh r0
#   define xl r1
#   define yh r2
#   define yl r3
#endif

#define LOCAL_SYM(X)    L__##X
#define LOCAL_LABEL(X)  LOCAL_SYM(X):
    


#define AEABI_LABEL(X)     \
    .global __##aeabi_##X; \
    __##aeabi_##X:

#if defined(__thumb2__)
    .macro doit cond, suffix=""
        it\suffix   \cond
    .endm

    .macro shift1 op, arg0, arg1, arg2
        \op  \arg0, \arg1, \arg2
    .endm

#   define cond(o1,o2,c) o1##o2##c
#else
    .macro doit cond, suffix=""
    .endm
    
    .macro shift1 op, arg0, arg1, arg2
        mov  \arg0, \arg1, \op \arg2
    .endm

#   define cond(o1,o2,c) o1##c##o2
#endif

#define sret     bx         lr
#define mret(X)  bx##X      lr

#define IMPORT_LOCAL_SYM(N) .global LOCAL_SYM(N)
#define EXPORT_LOCAL_SYM(N) .global LOCAL_SYM(N)

/*
 * Handy utility for returning based on registers
 * and such (must be stringized)
 */
.macro RLDM regs=, cond=, dirn=ia
    .ifc "\regs", ""
    ldr\cond      lr, [sp], #4
    .else
    ldm\cond\dirn sp!, {\regs, lr}
    .endif
    bx\cond       lr
.endm

#endif
