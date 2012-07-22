/*
 * Copyright (C) 2012
 *  Dale Weiler
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
#ifndef __CCAPRICE_CRT_HDR
#define __CCAPRICE_CRT_HDR
#include <ccaprice.h>
#include <stdint.h>
#include <stddef.h>
#include <bits/types.h>
#include <bits/syscall.h>

/*
 * Only need 15 interfaces with the kernel so far: that's not bad at all!
 * for an ANSI library.
 */
#define __SYS_WRITE   ssize_t write (int         A1, const void *A2, size_t A3)
#define __SYS_READ    ssize_t read  (int         A1, void       *A2, size_t A3)
#define __SYS_OPEN    int     open  (const char* A1, int         A2)
#define __SYS_KILL    int     kill  (pid_t       A1, int         A2)
#define __SYS_UNLINK  int     unlink(const char* A1)
#define __SYS_IOCTL   int     ioctl (int         A1, int         A2, void  *A3)
#define __SYS_CLOSE   int     close (int         A1)
#define __SYS_EXIT    void   _exit  (int         A1)
#define __SYS_GETPID  pid_t   getpid()
#define __SYS_MMAP    void*  _mmap  (void       *A1, size_t      A2, int    A3, int   A4, int  A5, off_t A6)
#define __SYS_MUNMAP  int     munmap(void       *A1, size_t      A2)
#define __SYS_FUTEX   int     futex (int        *A1, int         A2, int    A3, void *A4, int *A5, int   A6)
#define __SYS_LSEEK   off_t   lseek (int         A1, off_t       A2, int    A3)
#define __SYS_FCNTL   int     fcntl (int         A1, int         A2, int    A3)
#define __SYS_WRITEV  ssize_t writev(int         A1, const void *A2, int    A3)

/*
 * Systemcall fillers to make life simpler in princible.  This is all nasty
 * all really nasty.
 */
#define __SYSCALL_DORETURN       return
#define __SYSCALL_NORETURN       {/* no return */}
#define __SYSCALL_ARGUMENTS_0 
#define __SYSCALL_ARGUMENTS_1                         , (long)A1
#define __SYSCALL_ARGUMENTS_2    __SYSCALL_ARGUMENTS_1, (long)A2
#define __SYSCALL_ARGUMENTS_3    __SYSCALL_ARGUMENTS_2, (long)A3
#define __SYSCALL_ARGUMENTS_4    __SYSCALL_ARGUMENTS_3, (long)A4
#define __SYSCALL_ARGUMENTS_5    __SYSCALL_ARGUMENTS_4, (long)A5
#define __SYSCALL_ARGUMENTS_6    __SYSCALL_ARGUMENTS_5, (long)A6
#define __SYSCALL_ARGUMENTS(X)   __SYSCALL_ARGUMENTS_##X
#define __SYSCALL_PERFORM(RET,NUM,S)     \
    RET __ccaprice_syscall_args_##S (    \
        NUM                              \
        __SYSCALL_ARGUMENTS(S)           \
    )

__CCAPRICE_EXPORT ssize_t write (int, const void*, size_t);
__CCAPRICE_EXPORT ssize_t read  (int, void      *, size_t);
__CCAPRICE_EXPORT int     open  (const char     *, int);
__CCAPRICE_EXPORT int     unlink(const char     *);
__CCAPRICE_EXPORT int     close (int);
__CCAPRICE_EXPORT int     kill  (pid_t, int);
__CCAPRICE_EXPORT void    _exit (int);
__CCAPRICE_EXPORT pid_t   getpid();
__CCAPRICE_EXPORT void  *_mmap  (void *, size_t, int, int, int, off_t);
__CCAPRICE_EXPORT int     munmap(void *, size_t);
__CCAPRICE_EXPORT int     futex (int*, int, int, void*, int*, int);
__CCAPRICE_EXPORT off_t   lseek (int, off_t, int);
__CCAPRICE_EXPORT int     fcntl (int, int, int);
__CCAPRICE_EXPORT ssize_t writev(int, const void*, int);

/* TODO: hack! fix! workaround! */
#ifdef SYS_mmap2
#   ifdef SYS_mmap
#       undef SYS_mmap
#   endif
#   define SYS_mmap SYS_mmap2
#   define mmap(X1,X2,X3,X4,X5,X6) _mmap(X1,X2,X3,X4,X5,(X6)>>12)
#else
#   define mmap _mmap
#endif

#endif
