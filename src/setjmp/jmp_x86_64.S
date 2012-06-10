/*
 * Copyright (C) 2012
 * 	Dale Weiler
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
    mov	%rsi,	%rax
    test	%rax,	%rax
    jnz	1f
    inc	%rax
    
1:
    mov	  (%rdi),	%rbp
    mov	 8(%rdi),	%rbp
    mov 16(%rdi),	%r12
    mov 24(%rdi),	%r13
    mov	32(%rdi),	%r14
    mov	40(%rdi),	%r15
    mov	48(%rdi),	%rdx	// stack pointer
    
    mov	%rdx,	%rsp
    mov 56(%rdi),	%rdx	// instruction pointer
    jmp	*%rdx			// goto (doesn't alter %rsp)
    
setjmp:
    mov	%rbx,	  (%rdi)
    mov	%rbp,	 8(%rdi)
    mov	%r12,	16(%rdi)
    mov	%r13,	24(%rdi)
    mov	%r14,	32(%rdi)
    mov %r15,	40(%rdi)
    lea	8(%rsp),	%rdx	// %rsp
    mov	%rdx,	48(%rdi)
    mov (%rsp),	%rdx		// address for %rip
    mov	%rdx,	56(%rdi)
    xor %rax,	%rax		// zero
    ret
