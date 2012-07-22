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
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>


#include <atomic.h>
#include <bits/syscall.h>
__CCAPRICE_INTERNAL_FUNC(void, _exit, (int));

/* this is nasty ... */
FILE *__ccaprice_o_dat = ((void*)0);
FILE *__ccaprice_i_dat = ((void*)0);
FILE *__ccaprice_e_dat = ((void*)0);

FILE *__ccaprice_stdout() { return __ccaprice_o_dat; }
FILE *__ccaprice_stdin () { return __ccaprice_i_dat; }
FILE *__ccaprice_stderr() { return __ccaprice_e_dat; }

void __ccaprice_init() {
    __CCAPRICE_INTERNAL_TYPE(FILE, __ccaprice_stdio_file_dat[__CCAPRICE_STDIO_FILE_BUFFER_LEN]);
    /* setup stdout at startup */
    __ccaprice_i_dat     = &__ccaprice_stdio_file_dat[0]; //malloc(sizeof(FILE));
    __ccaprice_o_dat     = &__ccaprice_stdio_file_dat[1]; //malloc(sizeof(FILE));
    __ccaprice_e_dat     = &__ccaprice_stdio_file_dat[2];
    __ccaprice_i_dat->fd = 0;
    __ccaprice_o_dat->fd = 1;
    __ccaprice_e_dat->fd = 2;
}

void __ccaprice_exit(int status) {
    /*
     * libc needs to be reinitialized when we
     * arrive here for some odd reason.  Thats
     * okay though.  This causes no harm.
     */
    __ccaprice_init();
    exit(status);
}

/*
 * C++ requires as least 32 atexit functions, C does not
 * however this needs to stay backwards compatible with
 * C++.
 */
static short  __ccaprice_atexit_position = 0;
static void (*__ccaprice_atexit_functions[32])() = {
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

void atexit(void (*fun)()) {
    if (fun && __ccaprice_atexit_position + 1 < 32) {
        __ccaprice_atexit_functions[__ccaprice_atexit_position] = fun;
        __ccaprice_atexit_position ++;
        return;
    }
    if (__ccaprice_atexit_position +1 >= 32)
        __ccaprice_atexit_position =0;
    atexit(fun); /* try again */
}

void exit(int status) {
    /*
     * When more than one thread calls exit we must hang and wait for the
     * actual call to exit kills it all.
     */
    static int lock;
    while (__ccaprice_atomic_swap(&lock, 1))
        __ccaprice_syscall_args_0(SYS_pause);
        
    int   i=sizeof(__ccaprice_atexit_functions)/sizeof(*__ccaprice_atexit_functions);
    while(i-->0) {
        if (__ccaprice_atexit_functions[i]) {
            __ccaprice_atexit_functions[i](); /* call in reverse order */
        }
    }

    /* static destructors */
    if (__CCAPRICE_INSTANCE.fini)
        __CCAPRICE_INSTANCE.fini();
    
    /*
     *  TODO:
     *  seeks_on_exit,
     *  flush_on_exit
     */
    
    _exit(status&0xFF);
    for (;;);
}
