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
CCAPRICE_EXPORT void   _exit (int);
CCAPRICE_EXPORT pid_t  getpid();

#endif /* !CCAPRICE_CRT_HDR */
