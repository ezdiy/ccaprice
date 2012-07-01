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
#ifndef __CCAPRICE_SYSCALL_TEMPLATE
#ifndef __CCAPRICE_CRT_HDR
#define __CCAPRICE_CRT_HDR
#include <ccaprice.h>
#include <stdint.h>
#include <stddef.h>
#include <bits/syscall.h>
#include <bits/types.h>

/*
 * Only need 10 interfaces with the kernel so far: that's not bad at all!
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
#define __SYS_MMAP    void*  _mmap  (void       *A1, size_t      A2, int    A3, int A4, int A5, off_t A6)
#define __SYS_MUNMAP  int     munmap(void       *A1, size_t      A2)


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
    RET __ccaprice_syscall_args_##S ( \
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

/*
 * This is the syscall template system.  This is portable, powerful and
 * scary as fuck!  I'm not even going to explain how much hack is
 * involved here.  I want to keep down all the requirement to write insane
 * amounts of code for porting.  This does just that using insane preprocessor
 * hacks.
 *
 * Disclaimer:  Do not even attempt to modify this unless you're at ballmers
 *              peak.  This is simple to follow, but instantly breaks if you
 *              play with it too much.
 */
#else
    #ifndef __CCAPRICE_SYSCALL_TEMPLATE_USED
    #define __CCAPRICE_SYSCALL_TEMPLATE_USED
    /* handle optional macros */
    #ifndef SYSCALL_EXP_0
    #define SYSCALL_EXP_0
    #endif
    #ifndef SYSCALL_EXP_1
    #define SYSCALL_EXP_1
    #endif
    #ifndef SYSCALL_EXP_2
    #define SYSCALL_EXP_2
    #endif
    #ifndef SYSCALL_EXP_3
    #define SYSCALL_EXP_3
    #endif
    #ifndef SYSCALL_EXP_4
    #define SYSCALL_EXP_4
    #endif
    #ifndef SYSCALL_EXP_5
    #define SYSCALL_EXP_5
    #endif
    #ifndef SYSCALL_EXP_6
    #define SYSCALL_EXP_6
    #endif

    #ifndef SYSCALL_BEFORE
    #define SYSCALL_BEFORE
    #endif
    #ifndef SYSCALL_AFTER
    #define SYSCALL_AFTER
    #endif

    /* DO NOT EDIT: consult Dale Weiler first, this is magic! */
    #define SYSCALL_TYPE                 long
    #define SYSCALL_MAX                  6
    #define SYSCALL_ARG_0                SYSCALL_TYPE A0
    #define SYSCALL_ARG_1 SYSCALL_ARG_0, SYSCALL_TYPE A1
    #define SYSCALL_ARG_2 SYSCALL_ARG_1, SYSCALL_TYPE A2
    #define SYSCALL_ARG_3 SYSCALL_ARG_2, SYSCALL_TYPE A3
    #define SYSCALL_ARG_4 SYSCALL_ARG_3, SYSCALL_TYPE A4
    #define SYSCALL_ARG_5 SYSCALL_ARG_4, SYSCALL_TYPE A5
    #define SYSCALL_ARG_6 SYSCALL_ARG_5, SYSCALL_TYPE A6
    #define SYSCALL_ASM_0(SIZE)  \
        SYSCALL_CALL             \
        SYSCALL_FINISHED (SIZE)
    #define SYSCALL_ASM_1(SIZE)  SYSCALL_ASM_0(SIZE)
    #define SYSCALL_ASM_2(SIZE)  SYSCALL_ASM_1(SIZE)
    #define SYSCALL_ASM_3(SIZE)  SYSCALL_ASM_2(SIZE)
    #define SYSCALL_ASM_4(SIZE)  SYSCALL_ASM_3(SIZE)
    #define SYSCALL_ASM_5(SIZE)  SYSCALL_ASM_4(SIZE)
    #define SYSCALL_ASM_6(SIZE)  \
        SYSCALL_BEFORE     "\n\t"\
        SYSCALL_CALL       "\n\t"\
        SYSCALL_AFTER      "\n\t"\
        SYSCALL_FINISHED (SIZE)
    #define SYSCALL_ASMS(SIZE) SYSCALL_ASM_##SIZE (SIZE)
    #define SYSCALL_ARGS(SIZE) SYSCALL_ARG_##SIZE
    #define SYSCALL_LSTS(SIZE) SYSCALL_LST_##SIZE
    #define SYSCALL_FILL(SIZE) SYSCALL_EXP_##SIZE
    #define SYSCALL_FINISHED(SIZE)                       \
        : SYSCALL_RETURN (r)                             \
        : SYSCALL_LSTS(SIZE)                             \
        : SYSCALL_CLOBBERS
    #define SYSCALL_TEMPLATE(SIZE)                       \
    typedef char                                         \
    SYSCALL_CONCAT(static_assert_check,__LINE__) [       \
        SIZE <= SYSCALL_MAX ? 1 : -1                     \
    ];                                                   \
    static inline long SYSCALL_CONCAT (                  \
        __ccaprice_syscall_args_,                        \
        SIZE                                             \
    )(SYSCALL_ARGS(SIZE)) {                              \
        unsigned long r;                                 \
        SYSCALL_FILL(SIZE)                               \
        __asm__ __volatile__ (SYSCALL_ASMS(SIZE));       \
        return r;                                        \
    }
    #define SYSCALL_NDOCAT(X,Y) X##Y
    #define SYSCALL_CONCAT(X,Y) SYSCALL_NDOCAT(X,Y)
    SYSCALL_TEMPLATE(0)
    SYSCALL_TEMPLATE(1)
    SYSCALL_TEMPLATE(2)
    SYSCALL_TEMPLATE(3)
    SYSCALL_TEMPLATE(4)
    SYSCALL_TEMPLATE(5)
    SYSCALL_TEMPLATE(6)
    /* undef all the stuff this file defined */
    #undef SYSCALL_TYPE
    #undef SYSCALL_MAX
    #undef SYSCALL_ARG_0
    #undef SYSCALL_ARG_1
    #undef SYSCALL_ARG_2
    #undef SYSCALL_ARG_3
    #undef SYSCALL_ARG_4
    #undef SYSCALL_ARG_5
    #undef SYSCALL_ARG_6
    #undef SYSCALL_ASM_0
    #undef SYSCALL_ASM_1
    #undef SYSCALL_ASM_2
    #undef SYSCALL_ASM_3
    #undef SYSCALL_ASM_4
    #undef SYSCALL_ASM_5
    #undef SYSCALL_ASM_6
    #undef SYSCALL_ASMS
    #undef SYSCALL_ARGS
    #undef SYSCALL_LSTS
    #undef SYSCALL_FILL
    #undef SYSCALL_FINISHED
    #undef SYSCALL_TEMPLATE
    #undef SYSCALL_NDOCAT
    #undef SYSCALL_CONCAT
    /* and all stuff user defined           */
    #undef SYSCALL_LST_0
    #undef SYSCALL_LST_1
    #undef SYSCALL_LST_2
    #undef SYSCALL_LST_3
    #undef SYSCALL_LST_4
    #undef SYSCALL_LST_5
    #undef SYSCALL_LST_6
    #undef SYSCALL_EXP_0
    #undef SYSCALL_EXP_1
    #undef SYSCALL_EXP_2
    #undef SYSCALL_EXP_3
    #undef SYSCALL_EXP_4
    #undef SYSCALL_EXP_5
    #undef SYSCALL_EXP_6
    #undef SYSCALL_BEFORE
    #undef SYSCALL_AFTER
    #undef SYSCALL_RETURN
    #undef SYSCALL_CLOBBERS
    #undef SYSCALL_CALL
    #endif
#endif
