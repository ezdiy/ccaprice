#ifndef CCAPRICE_CRT_HDR
#define CCAPRICE_CRT_HDR
#include "inc/ccaprice.h"
#include <syscall.h>

typedef int32_t pid_t;

CCAPRICE_EXPORT ssize_t write(int, const void*, size_t);
CCAPRICE_EXPORT ssize_t read (int, void      *, size_t);
CCAPRICE_EXPORT int     open (const char     *, int);
CCAPRICE_EXPORT int     close(int);
CCAPRICE_EXPORT int     kill (pid_t, int);
CCAPRICE_EXPORT void   *sbrk (int);
CCAPRICE_EXPORT void   _exit (int);
CCAPRICE_EXPORT pid_t  getpid();

/* <hack> */
/* linux/BSD X86 / X86_64 only */
#if defined(__x86__)             || \
	defined(CCAPRICE_TARGET_X86) || \
	defined(__x86_64__)          || \
	defined(CCAPRICE_TARGET_X86_64)
	#define O_ACCMODE  0003
	#define O_RDONLY   00
	#define O_WRONLY   01
	#define O_RDWR     02
	#define O_CREAT    0100
	#define O_EXCL     0200
	#define O_NOCTTY   0400
	#define O_TRUNC    01000
	#define O_APPEND   02000
	#define O_NONBLOCK 04000
	#define O_NDELAY   04000
	#define O_SYNC     010000
	#define O_FSYNC    010000
	#define O_ASYNC    020000
#endif /* !O_MODES          */
#endif /* !CCAPRICE_CRT_HDR */
