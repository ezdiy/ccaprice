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
.text
.global ccaprice_syscall_core
.global ccaprice_main
.global _start
.type   ccaprice_syscall_core,%function
.type   _start,%function

_start:
	xorl %ebp,%ebp
	popl %esi
	movl %esp,%ecx
	andl $0xfffffff0,%esp
	pushl %ecx
	pushl %esi
	call ccaprice_main
	hlt
	
	
ccaprice_syscall_core:
	#ifndef BSD
		pushl %ebp
		pushl %edi
		pushl %esi
		pushl %ebx
		movl 44(%esp),%ebp
		movl 40(%esp),%edi
		movl 36(%esp),%esi
		movl 32(%esp),%edx
		movl 28(%esp),%ecx
		movl 24(%esp),%ebx
		movl 20(%esp),%eax
	#else
		push 44(%esp)
		push 40(%esp)
		push 36(%esp)
		push 32(%esp)
		push 28(%esp)
		push 24(%esp)
		push 20(%esp)
	#endif
	
	int $0x80
	
	#ifndef BSD
		popl %ebx
		popl %esi
		popl %edi
		popl %ebp
	#endif
	
	cmpl $-4095,%eax
	jae  ccaprice_syscall_error
	ret
	
.size ccaprice_syscall_core,.-ccaprice_syscall_core
.size _start,.-_start
	
