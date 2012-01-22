/* Implement runtime sycalls here */
#include "runtime.h"
#include "inc/stdarg.h"
#include "inc/string.h"

/* In [arch].S */
CCAPRICE_INTERNAL_FUNC(int, ccaprice_syscall_core, (int, ...));

/* MALLOC Requires this */
static void *ccaprice_runtime_curbrk = NULL;
#if defined(CCAPRICE_TARGET_X86) || defined(__i386__)
int ccaprice_syscall_error() {
	register int no __asm__("%edx");
	__asm__ __volatile__ (
		"mov  %eax, %edx\n\t"
		"negl %edx      \n\t"
	);
	return no;
}
#elif defined(CCAPRICE_TARGET_X86_64) || defined(__x86_64__)
int ccaprice_syscall_error() {
	register int no __asm__("%rcx");
	__asm__ __volatile__ (
		"mov %rax, %rcx\n\t"
		"neg %rcx      \n\t"
	);
	return no;
}
#endif

#ifdef CCAPRICE_TARGET_X86
int ccaprice_runtime_brk(void *address) {
	void *vfbrk, *vfscr;
	__asm__ __volatile__ (
		"movl %%ebx , %1   \n\t"
		"movl %3    , %%ebx\n\t"
		"int  $0x80 # %2   \n\t"
		"movl %1    , %%ebx\n\t" :
			"=a"(vfbrk),
			"=r"(vfscr) : 
				"0"(SYS_brk),
				"g"(address)
	);
	ccaprice_runtime_curbrk = vfbrk;
	return (vfbrk < address)?-1:0;
}
#elif defined(CCAPRICE_TARGET_X86_64)
int ccaprice_runtime_brk(void *address) {
	void *vfbrk;
	register unsigned long res;
	register unsigned long adr __asm__("rdi") = (unsigned long)address;
	__asm__ __volatile__ (
		"movq %1, %%rax\n\t"
		"syscall       \n\t" :
			"=a"(res) :
				"i"(SYS_brk), "r"(adr) :
					"memory","cc", "r11", "cx"
	);
	if ((unsigned long)res>=(unsigned long)-4095)
		res = (unsigned long)-1;
		
	ccaprice_runtime_curbrk = vfbrk = (void*)res;
	return (vfbrk < address)?-1:0;
}
#endif
/*
 * SYSCALL0 doesn't return
 * SYSCALL1 does    return
 */
#define SYSCALL0(TYPE, NAME, LIST, CORE) TYPE NAME LIST {        (TYPE)ccaprice_syscall_core CORE; }
#define SYSCALL1(TYPE, NAME, LIST, CORE) TYPE NAME LIST { return (TYPE)ccaprice_syscall_core CORE; }

SYSCALL1(ssize_t,write, (int f,const void *b,size_t c),(SYS_write,f,b,c))
SYSCALL1(ssize_t,read,  (int f,void *b,size_t c),      (SYS_read, f,b,c))
SYSCALL1(int,    open,  (const char *f,int b),         (SYS_open, f,b))
SYSCALL1(int,    kill,  (pid_t f,int b),               (SYS_kill, f,b))
SYSCALL1(int,    close, (int f),                       (SYS_close,f))
SYSCALL1(int,    brk,   (int f),                       (SYS_brk,  f))
SYSCALL0(void,  _exit,  (int f),                       (SYS_exit, f))
SYSCALL1(pid_t,  getpid,(),                            (SYS_getpid))
