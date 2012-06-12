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
#ifndef CCAPRICE_CRT_HDR
#define CCAPRICE_CRT_HDR
#include "inc/ccaprice.h"
#include "inc/stdint.h"
#include "inc/stddef.h"
#if defined(LINUX)
#	include "sys/linux.h"
#elif defined(BSD)
#	include "sys/bsd.h"
#endif


typedef int32_t pid_t;
#if defined(i386)   || defined(__x86__)
#	define PAGE_SIZE 4096
#	define SIZE_MAX 0xffffffff
#endif
#if defined(x86_64) || defined(__x86_64__)
#	define PAGE_SIZE 4096
#	define SIZE_MAX 0xffffffffffffffff
#endif

__CCAPRICE_EXPORT ssize_t write (int, const void*, size_t);
__CCAPRICE_EXPORT ssize_t read  (int, void      *, size_t);
__CCAPRICE_EXPORT int     open  (const char     *, int);
__CCAPRICE_EXPORT int     unlink(const char     *);
__CCAPRICE_EXPORT int     close (int);
__CCAPRICE_EXPORT int     kill  (pid_t, int);
__CCAPRICE_EXPORT void    _exit (int);
__CCAPRICE_EXPORT pid_t   getpid();
__CCAPRICE_EXPORT int     munmap(void *, size_t);
__CCAPRICE_EXPORT void   *mmap  (void *, size_t, int, int, int, off_t);

/* <hack> */
/* linux/BSD X86 / X86_64 only */
#if defined(__CCAPRICE_TARGET_X86_32) || defined(__CCAPRICE_TARGET_X86_64)
	#define O_ACCMODE   0003
	#define O_RDONLY    00
	#define O_WRONLY    01
	#define O_RDWR      02
	#define O_CREAT     0100
	#define O_EXCL      0200
	#define O_NOCTTY    0400
	#define O_TRUNC     01000
	#define O_APPEND    02000
	#define O_NONBLOCK  04000
	#define O_NDELAY    04000
	#define O_SYNC      010000
	#define O_FSYNC     010000
	#define O_ASYNC     020000
	#define O_LARGEFILE 0200000
#endif /* !O_MODES          */
#endif /* !CCAPRICE_CRT_HDR */
