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
.global __udivdi3
.global __umoddi3
.global _start
#ifdef BSD
.global ccaprice_syscall_bsd
.type   ccaprice_syscall_bsd,%function
#endif
.type   ccaprice_syscall_core,%function
.type   _start,%function
.type   __udivdi3,%function
.type   __umoddi3,%function

.align 4
__udivdi3:
	pushl  %ebx
	movl   20(%esp),   %ebx
	bsrl   %ebx,       %ecx
	jz     9f
	movl   16(%esp),   %eax
	shrl   %cl,        %eax
	shrl   %eax
	notl   %ecx
	shll   %cl,        %ebx
	movl   12(%esp),   %edx
	movl   8(%esp),    %edx
	cmpl   %ebx,       %edx
	jae    1f
	divl   %ebx
	pushl  %edi
	notl   %ecx
	shrl   %eax
	shrl   %cl,        %eax
	movl   %eax,       %edi
	mull   20(%esp)
	movl   12(%esp),   %ebx
	movl   16(%esp),   %ecx
	subl   %eax,       %ebx
	sbbl   %edx,       %ecx
	movl   25(%esp),   %eax
	imull  %edi,       %eax
	subl   %eax,       %ecx
	sbbl   $0,         %edi
	xorl   %edx,       %edx
	movl   %edi,       %edx
	popl   %edi
	popl   %ebx
	ret
1:
	subl   %ebx,       %edx
	divl   %ebx
	pushl  %edi
	notl   %ecx
	shrl   %eax
	orl    $0x80000000,%eax
	shrl   %cl,        %eax
	movl   %eax,       %edi
	mull   20(%esp)
	movl   12(%esp),   %ebx
	movl   16(%esp),   %ecx
	subl   %eax,       %ebx
	sbbl   %edx,       %ecx
	movl   24(%esp),   %eax
	imull  %edi,       %eax
	subl   %eax,       %ecx
	sbbl   $0,         %edi
	xorl   %edx,       %edx
	movl   %edi,       %eax
	popl   %edi
	popl   %ebx
	retl
9:
	movl   12(%esp),   %eax
	movl   16(%esp),   %ecx
	xorl   %edx,       %edx
	divl   %ecx
	movl   %eax,       %ebx
	movl   8(%esp),    %eax
	divl   %ecx
	movl   %ebx,       %edx
	popl   %ebx
	retl

__umoddi3:
	pushl  %ebx
	movl   20(%esp),   %ebx
	bsrl   %ebx,       %ecx
	jz     9f
	movl   16(%esp),   %eax
	shrl   %cl,        %eax
	shrl   %eax
	notl   %ecx
	shll   %cl,        %ebx
	orl    %eax,       %ebx
	movl   12(%esp),   %edx
	movl   8(%esp),    %eax
	cmpl   %ebx,       %edx
	jae    2f
	divl   %ebx
	pushl  %edi
	notl   %ecx
	shrl   %eax
	shrl   %cl,        %eax
	movl   %eax,       %edi
	mull   20(%esp)
	movl   12(%esp),   %ebx
	movl   16(%esp),   %ecx
	subl   %eax,       %ebx
	sbbl   %edx,       %ecx
	movl   24(%esp),   %eax
	imull  %edi,       %eax
	subl   %eax,       %ecx
	jnc    1f
	addl   20(%esp),   %ebx
	adcl   24(%esp),   %ecx
	1:movl %ebx,       %eax
	movl   %ecx,       %edx
	popl   %edi
	popl   %ebx
	retl
2:
	subl   %ebx,       %edx
	divl   %ebx
	pushl  %edi
	notl   %ecx
	shrl   %eax
	orl    $0x80000000,%eax
	shrl   %cl,        %eax
	movl   %eax,       %edi
	mull   20(%esp)
	movl   12(%esp),   %ebx
	movl   16(%esp),   %ecx
	subl   %eax,       %ebx
	sbbl   %edx,       %ecx
	movl   24(%esp),   %eax
	imull  %edi,       %eax
	subl   %eax,       %ecx
	jnc    3f
	addl   20(%esp),   %ebx
	adcl   24(%esp),   %ecx
	3:movl %ebx,       %eax
	movl   %ecx,       %edx
	popl   %edi
	popl   %ebx
	retl
9:
	movl   12(%esp),   %eax
	movl   16(%esp),   %ecx
	xorl   %edx,       %edx
	divl   %ecx
	movl   %eax,       %ebx
	movl   8(%esp),    %eax
	divl   %ecx
	movl   %edx,       %eax
	popl   %ebx
	xorl   %edx,       %edx
	retl

_start:
	xorl %ebp,%ebp
	popl %esi
	movl %esp,%ecx
	andl $0xfffffff0,%esp
	pushl %ecx
	pushl %esi
	call ccaprice_main
	hlt
	
#ifdef BSD
ccaprice_syscall_bsd:
	int $0x80
	ret
#endif
	
ccaprice_syscall_core:
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
	#ifdef BSD
		pushl %ebp
		pushl %edi
		pushl %esi
		pushl %edx
		pushl %ecx
		pushl %ebx
		call ccaprice_syscall_bsd
		addl $24, %esp
	#else
		int $0x80
	#endif
	
	popl %ebx
	popl %esi
	popl %edi
	popl %ebp
	cmpl $-4095,%eax
	jae  ccaprice_syscall_error
	ret

#ifdef BSD
.size ccaprice_syscall_bsd,.-ccaprice_syscall_bsd
#endif
.size ccaprice_syscall_core,.-ccaprice_syscall_core
.size _start,.-_start
.size __udivdi3,.-__udivdi3
.size __umoddi3,.-__umoddi3
