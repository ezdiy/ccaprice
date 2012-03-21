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
#if defined(MAC)
#	define ENTRY start
#elif defined(WIN)
#	define ENTRY __main
#else
#	define ENTRY _start
#endif 

.text
.global __ccaprice_syscall_core
.global __ccaprice_main
.global ENTRY
#ifndef __PATHCC__
.type   __ccaprice_syscall_core,%function
.type   ENTRY,%function
#endif

ENTRY:
	xorq %rbp,%rbp
	popq %rsi
	movq %rsi,%rdi
	movq %rsp,%rsi
	andq $~15,%rsp
	pushq %rax
	pushq %rsp
	call __ccaprice_main
	hlt
	
__ccaprice_syscall_core:
	movq %rdi   , %rax
	movq %rsi   , %rdi
	movq %rdx   , %rsi
	movq %rcx   , %rdx
	movq %r8    , %r10
	movq %r9    , %r8
	movq 8(%rsp), %r9
	
	syscall
	cmpq $-4095, %rax 
	jae __ccaprice_syscall_error
	ret

.size __ccaprice_syscall_core,.-__ccaprice_syscall_core
.size ENTRY,.-ENTRY
