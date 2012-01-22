.text
.global ccaprice_syscall
.type   ccaprice_syscall,%function

ccaprice_syscall:
	call ccaprice_syscall_trace
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
	
	int $0x80
	
	popl %ebx
	popl %esi
	popl %edi
	popl %ebp
	
	cmpl $-4095,%eax
	jae  ccaprice_syscall_error
	ret
	
.size ccaprice_syscall,.-ccaprice_syscall
	
