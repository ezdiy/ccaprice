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
#include "runtime.h"
#include "inc/stdarg.h"
#include "inc/stdio.h"
#include "inc/string.h"
#include "inc/locale.h"

/* In [arch].S */
CCAPRICE_INTERNAL_FUNC(int, ccaprice_syscall_core, (int, ...));

#ifdef BSD
	#define SYS_BRK SYS_break
#else
	#define SYS_BRK SYS_brk
#endif

/* ENVIROMENT */
char **ccaprice_enviroment;

/* MALLOC Requires this */
void *ccaprice_runtime_curbrk = NULL;
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
	void *vfbrk;
	#ifdef BSD
	__asm__ __volatile__ (
		"bsd_syscall: \n\t"
		"int $0x80    \n\t"
		"ret          \n\t"
	);
	#endif
	__asm__ __volatile__ (
		"pushl    %%ebx   \n\t"
		"movl %2, %%ebx   \n\t"
		#ifdef BSD
		"int  $0x80       \n\t"
		"popl %%ebx       \n\t"
		#else
		"call bsd_syscall \n\t"
		"addl $4, %esp    \n\t" /* realign the stack pointer */
		#endif
		:
			"=a"(vfbrk) :
				"0"(SYS_BRK),
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
				"i"(SYS_BRK), "r"(adr) :
					"memory","cc", "r11", "cx"
	);
	if ((unsigned long)res>=(unsigned long)-4095)
		res = (unsigned long)-1;
		
	ccaprice_runtime_curbrk = vfbrk = (void*)res;
	return (vfbrk < address)?-1:0;
}
#endif

void ccaprice_main(int argc, char **argv) {	
	CCAPRICE_INTERNAL_FUNC(void, ccaprice_locale_init, ());
	CCAPRICE_INTERNAL_FUNC(void, ccaprice_init, ());
	CCAPRICE_INTERNAL_FUNC(void, ccaprice_exit, (int));
	CCAPRICE_INTERNAL_FUNC(void, ccaprice_posix_errno_set, (int*));
	CCAPRICE_INTERNAL_FUNC(int, main, (int, char **, char **));
	
	int function_only_errno;
	ccaprice_posix_errno_set(&function_only_errno);
	ccaprice_enviroment = &argv[argc+1];
	ccaprice_locale_init();
	ccaprice_init();
	ccaprice_exit(main(argc, argv, ccaprice_enviroment));
}

/*
 * SYSCALL0 doesn't return
 * SYSCALL1 does    return
 */
#define SYSCALL0(TYPE, NAME, LIST, CORE) TYPE NAME LIST {        (TYPE)ccaprice_syscall_core CORE; }
#define SYSCALL1(TYPE, NAME, LIST, CORE) TYPE NAME LIST { return (TYPE)ccaprice_syscall_core CORE; }

SYSCALL1(ssize_t,write, (int f,const void *b,size_t c),(SYS_write,f,b,c))
SYSCALL1(ssize_t,read,  (int f,void *b,size_t c),      (SYS_read, f,b,c))
SYSCALL1(int,    open,  (const char *f,int b),         (SYS_open, f,b,0777))
SYSCALL1(int,    kill,  (pid_t f,int b),               (SYS_kill, f,b))
SYSCALL1(int,    close, (int f),                       (SYS_close,f))
SYSCALL0(void,  _exit,  (int f),                       (SYS_exit, f))
SYSCALL1(pid_t,  getpid,(),                            (SYS_getpid))
