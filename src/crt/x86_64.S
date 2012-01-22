.text
.global ccaprice_syscall
.type   ccaprice_syscall,%function

ccaprice_syscall:
	call ccaprice_syscall_trace
	movq %rdi   , %rax
	movq %rsi   , %rdi
	movq %rdx   , %rsi
	movq %rcx   , %rdx
	movq %r8    , %r10
	movq %r9    , %r8
	movq 8(%rsp), %r9
	
	syscall
	cmpq $-4095, %rax 
	jae ccaprice_syscall_error
	ret

.size ccaprice_syscall,.-ccaprice_syscall

_start:
	
