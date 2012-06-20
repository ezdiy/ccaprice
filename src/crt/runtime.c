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
__CCAPRICE_INTERNAL_FUNC(uintptr_t, __ccaprice_syscall_core, (int, ...));

/* ENVIROMENT */
char **__ccaprice_enviroment;

#if defined(__CCAPRICE_TARGET_X86_32)
int __ccaprice_syscall_error() {
	register int no __asm__("%edx");
	__asm__ __volatile__ (
		"mov  %eax, %edx\n\t"
		"negl %edx      \n\t"
	);
	return no;
}
#elif defined(__CCAPRICE_TARGET_X86_64)
int __ccaprice_syscall_error() {
	register int no __asm__("%rcx");
	__asm__ __volatile__ (
		"mov %rax, %rcx\n\t"
		"neg %rcx      \n\t"
	);
	return no;
}
#endif

#define ISTR1(C) ISTR2(C)
#define ISTR2(C) #C
	const char *__ccaprice_build_date __CCAPRICE_USED = __DATE__;
	const char *__ccaprice_build_time __CCAPRICE_USED = __TIME__;
	const char *__ccaprice_build_comp __CCAPRICE_USED = __COMP__;
	const char *__ccaprice_build_info __CCAPRICE_USED = ISTR1(__INFO__);
#undef ISTR1
#undef ISTR2

#if defined(BSD)
	const char *__ccaprice_build_host __CCAPRICE_USED = "BSD";
#elif defined(LINUX)
	const char *__ccaprice_build_host __CCAPRICE_USED = "LINUX";
#elif defined(WIN)
	const char *__ccaprice_build_host __CCAPRICE_USED = "WIN";
#endif

void __ccaprice_main(int argc, char **argv) {
	__CCAPRICE_INTERNAL_FUNC(void, __ccaprice_locale_init, ());
	__CCAPRICE_INTERNAL_FUNC(void, __ccaprice_init, ());
	__CCAPRICE_INTERNAL_FUNC(void, __ccaprice_exit, (int));
	__CCAPRICE_INTERNAL_FUNC(void, __ccaprice_posix_errno_set, (int*));
	__CCAPRICE_INTERNAL_FUNC(int, main, (int, char **, char **));

	int function_only_errno;
	__ccaprice_posix_errno_set(&function_only_errno);
	__ccaprice_enviroment = &argv[argc+1];
	__ccaprice_locale_init();
	__ccaprice_init();
	__ccaprice_exit(main(argc, argv, __ccaprice_enviroment));
}

/*
 * SYSCALL0 doesn't return
 * SYSCALL1 does    return
 */
#if !defined(WIN)
#	define SYSCALL0(TYPE, NAME, LIST, CORE) TYPE NAME LIST {        (TYPE)__ccaprice_syscall_core CORE; }
#	define SYSCALL1(TYPE, NAME, LIST, CORE) TYPE NAME LIST { return (TYPE)__ccaprice_syscall_core CORE; }
#else
#	define SYSCALL0(TYPE, NAME, LIST, CORE) TYPE NAME LIST { }
#	define SYSCALL1(TYPE, NAME, LIST, CORE) TYPE NAME LIST { return (TYPE)0; }
#endif

SYSCALL1(ssize_t,write, (int f,const void *b,size_t c),(SYS_write,f,b,c))
SYSCALL1(ssize_t,read,  (int f,void *b,size_t c),      (SYS_read, f,b,c))
SYSCALL1(int,    open,  (const char *f,int b),         (SYS_open, f,b,0777))
SYSCALL1(int,    kill,  (pid_t f,int b),               (SYS_kill, f,b))
SYSCALL1(int,    unlink,(const char *f),               (SYS_unlink,f))
SYSCALL1(int,    ioctl, (int f, int b, void *c),       (SYS_ioctl,f,b,c))
SYSCALL1(int,    close, (int f),                       (SYS_close,f))
SYSCALL0(void,  _exit,  (int f),                       (SYS_exit, f))
SYSCALL1(pid_t,  getpid,(),                            (SYS_getpid))

#ifndef SYS_mmap2
    SYSCALL1(void*,  mmap,  (void *f,size_t b,int c,int d,int e, off_t q),(SYS_mmap, f, b, c, d, e, q))
#else
    SYSCALL1(void*,  mmap,  (void *f,size_t b,int c,int d,int e, off_t q),(SYS_mmap2, (long)f, b, c, d, e, q>>12))
#endif

SYSCALL1(int,    munmap,(void *f,size_t b),(SYS_munmap, f, b))

#undef SYSCALL0
#undef SYSCALL1
