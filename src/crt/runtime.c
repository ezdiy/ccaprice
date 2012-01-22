/* Implement runtime sycalls here */
#include "runtime.h"
#include "inc/stdarg.h"
#include "inc/string.h"

#ifdef __x86_64__
int ccaprice_syscall_error() {
	register int no __asm__("%rcx");
	__asm__ __volatile__ (
		"mov %rax, %rcx\n\t"
		"neg %rcx      \n\t"
	);
	return no;
}
#endif
#ifdef __i386__
int ccaprice_syscall_error() {
	register int no __asm__("%edx");
	__asm__ __volatile__ (
		"mov  %eax, %edx\n\t"
		"negl %edx      \n\t"
	);
	return no;
}
#endif
extern int ccaprice_syscall_core(int, ...); /* syscall :D */

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
