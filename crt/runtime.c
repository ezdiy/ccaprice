/*
 * Copyright (C) 2012
 *     Dale Weiler
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
#include "runtime.h" /* TODO: fix! fix! fix! */
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

/*
 * These are global: TODO: guard for thread safe support in C11
 * I really dislike errno since in ANSI C it can only be two values
 */
char **__ccaprice_enviroment = NULL;
int   *__ccaprice_errno      = NULL;

#define ISTR1(C) ISTR2(C)
#define ISTR2(C) #C
    const char *__ccaprice_build_date __CCAPRICE_USED = __DATE__;
    const char *__ccaprice_build_time __CCAPRICE_USED = __TIME__;
    const char *__ccaprice_build_comp __CCAPRICE_USED = __COMP__;
    const char *__ccaprice_build_info __CCAPRICE_USED = ISTR1(__INFO__);
#undef ISTR1
#undef ISTR2

/*
 * This can be extended when more OS's are actually supported.  I think this
 * would do much better as a build step somehow so this doesn't need to be
 * modified on each new supported OS.
 */
#if defined(BSD)
    const char *__ccaprice_build_host __CCAPRICE_USED = "BSD";
#elif defined(LINUX)
    const char *__ccaprice_build_host __CCAPRICE_USED = "LINUX";
#endif

int __ccaprice_start (
    int  (*main)(int, char **, char **), int argc, char **argv,
    int  (*init)(int, char **, char **),
    void (*fini)(void),
    void (*lini)(void) /* for ldso */
) {
    __CCAPRICE_INTERNAL_FUNC(void, __ccaprice_locale_init, ());
    __CCAPRICE_INTERNAL_FUNC(void, __ccaprice_init,        ());
    __CCAPRICE_INTERNAL_FUNC(void, __ccaprice_exit,     (int));
    
    int arno;
    __ccaprice_errno      = &arno;
    __ccaprice_enviroment = &argv[argc+1];
    __ccaprice_locale_init();
    __ccaprice_init();
    
     /* static constructors */
    if (init) {
        init (
            argc,
            argv,
            __ccaprice_enviroment /* &argv[argc+1] */
        );
    }
        
    __ccaprice_exit (
        main (
            argc,
            argv,
            __ccaprice_enviroment /* &argv[argc+1] */
        )
    );
    return 0;
}

/*
 * There is only a required 10 system calls to implement the entire functionality
 * of the standard library.  We assume all systems have these.  We also assume
 * the way at invoking them is by syscall which is why there is a syscall template
 * to easily implement the functionality to call the kernel.  We use the SYS_*
 * identifers for syscall numbers (implemented in sys/bits).
 */
__SYS_WRITE  { __SYSCALL_PERFORM(__SYSCALL_DORETURN,       SYS_write,  3); }
__SYS_READ   { __SYSCALL_PERFORM(__SYSCALL_DORETURN,       SYS_read,   3); }
__SYS_OPEN   { __SYSCALL_PERFORM(__SYSCALL_DORETURN,       SYS_open,   2); }
__SYS_KILL   { __SYSCALL_PERFORM(__SYSCALL_DORETURN,       SYS_kill,   2); }
__SYS_UNLINK { __SYSCALL_PERFORM(__SYSCALL_DORETURN,       SYS_unlink, 1); }
__SYS_IOCTL  { __SYSCALL_PERFORM(__SYSCALL_DORETURN,       SYS_ioctl,  3); }
__SYS_CLOSE  { __SYSCALL_PERFORM(__SYSCALL_DORETURN,       SYS_close,  1); }
__SYS_EXIT   { __SYSCALL_PERFORM(__SYSCALL_NORETURN,       SYS_exit,   1); }
__SYS_GETPID { __SYSCALL_PERFORM(__SYSCALL_DORETURN,       SYS_getpid, 0); }
__SYS_MMAP   { __SYSCALL_PERFORM(__SYSCALL_DORETURN(void*),SYS_mmap,   6); }
__SYS_MUNMAP { __SYSCALL_PERFORM(__SYSCALL_DORETURN,       SYS_munmap, 2); }
