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
#include "runtime.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

#define UNGET   8
#define BUFSIZE 1024

/*
 * STDOUT, STDERR, STDIN static implementations for stdio code.
 * These are part of the runtime currently.
 * 
 * TODO: move to src/stdio
 */
static unsigned char __ccaprice_stdin_buf [BUFSIZE+UNGET];
static unsigned char __ccaprice_stdout_buf[BUFSIZE+UNGET];
static unsigned char __ccaprice_stderr_buf[UNGET];

static int __ccaprice_stdio_close(FILE *f) {
    return close(f->fd);
}

static size_t __ccaprice_stdio_write(FILE *fp, const unsigned char *buf, size_t len) {
    /*
     * TODO: all of it
     */
    return 0;
}

static FILE __ccaprice_stdin_impl = {
    .buf      = __ccaprice_stdin_buf+UNGET,
    .buf_size = sizeof(__ccaprice_stdin_buf-UNGET),
    .fd       = 0,
    .flags    = __CCAPRICE_F_PERM | __CCAPRICE_F_NOWR,
    
};

static FILE __ccaprice_stdout_impl = {
    .buf      = __ccaprice_stdout_buf+UNGET,
    .buf_size = sizeof(__ccaprice_stdout_buf-UNGET),
    .fd       = 1,
    .flags    = __CCAPRICE_F_PERM | __CCAPRICE_F_NORD,
    .lbf      = '\n',
    .write    = &__ccaprice_stdio_write,
    .close    = &__ccaprice_stdio_close,
};

static FILE __ccaprice_stderr_impl = {
    .buf      = __ccaprice_stderr_buf+UNGET,
    .buf_size = 0,
    .fd       = 2,
    .flags    = __CCAPRICE_F_PERM | __CCAPRICE_F_NORD,
    .lbf      = -1,
    .write    = &__ccaprice_stdio_write,
    .close    = &__ccaprice_stdio_close,
};

/*
 * These will be initialized by the static constructors stage which is
 * handled by the runtime code.
 */
FILE *const __ccaprice_stdout = &__ccaprice_stdout_impl;
FILE *const __ccaprice_stderr = &__ccaprice_stderr_impl;
FILE *const __ccaprice_stdin  = &__ccaprice_stdin_impl;

#undef BUFSIZE
#undef UNGET

/* returns a thread safe caprice instance */
__ccaprice_instance *__ccaprice (void) {
    static __ccaprice_instance instance;
    return &instance;
}

/*
 * These are global: TODO: guard for thread safe support in C11
 * I really dislike errno since in ANSI C it can only be two values
 */
char **__ccaprice_enviroment = NULL;
int   *__ccaprice_errno      = NULL;

const char *__ccaprice_build_date __CCAPRICE_USED = __DATE__;
const char *__ccaprice_build_time __CCAPRICE_USED = __TIME__;
const char *__ccaprice_build_comp __CCAPRICE_USED = __COMP__;
const char *__ccaprice_build_info __CCAPRICE_USED = __INFO__;
const char *__ccaprice_build_host __CCAPRICE_USED = __OSOS__;

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
    
    __CCAPRICE_INSTANCE.fini = fini;
    
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
__SYS_FUTEX  { __SYSCALL_PERFORM(__SYSCALL_DORETURN,       SYS_futex,  6); }
