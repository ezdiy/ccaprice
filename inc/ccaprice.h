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
#ifndef __CCAPRICE_CCAPRICE_HDR__
#define __CCAPRICE_CCAPRICE_HDR__
/*
 * When not compiling and including we need to determine
 * the architecture at compile-time without asking the
 * user to pass any macro to the command line build line
 * this is exactly what this does.
 */
#if !defined(__CCAPRICE_CP)
#if defined(__amd64__)     || \
    defined(__amd64)       || \
    defined(__x86_64__)    || \
    defined(__x86_64)      || \
    defined(_M_X64)        || \
    defined(_M_AMD64)
 #define __CCAPRICE_TARGET_X86_64
 #define __CCAPRICE_SUPPORTED
#if defined(i386)          || \
    defined(__i386__)      || \
    defined(__i486__)      || \
    defined(__i586__)      || \
    defined(__i686__)      || \
    defined(__i386)        || \
    defined(__IA32__)      || \
    defined(_M_IX86)       || \
    defined(__X86__)       || \
    defined(_X86_)         || \
    defined(__THW_INTEL__) || \
    defined(__I86__)       || \
    defined(__INTEL__)
 #define __CCAPRICE_TARGET_X86_32
 #define __CCAPRICE_SUPPORTED
#if defined(__arm__)             || \
    defined(__thumb__)           || \
    defined(__TARGET_ARCH_ARM)   || \
    defined(__TARGET_ARCH_THUMB) || \
    defined(_ARM)
 #define __CCAPRICE_TARGET_ARM
 #define __CCAPRICE_SUPPORTED
#endif
#endif
#endif
#endif

/*
 * Ensure that a valid target has been selected for compilation. Otherwise
 * force a compiler error.
 */
#if !defined(__CCAPRICE_SUPPORTED)     && \
    !defined(__CCAPRICE_TARGET_X86_64) && \
    !defined(__CCAPRICE_TARGET_X86_32) && \
    !defined(__CCAPRICE_TARGET_ARM)
# error "[ccaprice] Target not supported"
#endif

/*
 * The makefile should set a -D__INFO__=, if it doesn't we'll handle
 * defining __INFO__ to a string literal explaining that the build
 * did not include information.
 */
#if !defined(__INFO__)
# define __INFO__ "No information Specified during build"
#endif
/* cannot be enumerated required by more preprocessing */
#define __CCAPRICE_COMPILER_EKOPATH 0xFF0000
#define __CCAPRICE_COMPILER_CLANG   0x00FF00
#define __CCAPRICE_COMPILER_GCC     0x0000FF

#if defined(__PATHCC__)
# define __COMP__   "EKOPATH"
# define __COMPID__ __CCAPRICE_COMPILER_EKOPATH
# define __CCAPRICE_USED __attribute__((__used__))
#elif defined(__clang__)
# define __COMP__   "CLANG"
# define __COMPID__ __CCAPRICE_COMPILER_CLANG
# define __CCAPRICE_USED __attribute__((__used__))
#elif defined(__GNUC__)
# define __COMP__   "GCC"
# define __COMPID__ __CCAPRICE_COMPILER_GCC
# define __CCAPRICE_USED __attribute__((__used__))
#else
# warning "Unsupported compiler"
#endif

#define __CCAPRICE_INTERNAL_TYPE(TYPE, NAME)       extern TYPE NAME
#define __CCAPRICE_INTERNAL_FUNC(TYPE, NAME, LIST) __CCAPRICE_INTERNAL_TYPE(TYPE,NAME) LIST

#if defined(CCAPRICE_CP)
# define __CCAPRICE_EXPORT
#else
# define __CCAPRICE_EXPORT extern
#endif

__CCAPRICE_EXPORT const char *__ccaprice_build_date;
__CCAPRICE_EXPORT const char *__ccaprice_build_info;
__CCAPRICE_EXPORT const char *__ccaprice_build_comp;
__CCAPRICE_EXPORT const char *__ccaprice_build_time;
__CCAPRICE_EXPORT const char *__ccaprice_build_host;
#if defined(__CCAPRICE_EXTENSIONS)
# define __CCAPRICE_BUILD_DATE __ccaprice_build_date
# define __CCAPRICE_BUILD_INFO __ccaprice_build_info
# define __CCAPRICE_BUILD_COMP __ccaprice_build_comp
# define __CCAPRICE_BUILD_TIME __ccaprice_build_time
# define __CCAPRICE_BUILD_HOST __ccaprice_build_host
#endif

/*
 * We handle null correctly here.
 * In GNUG mode there is a builtin __null we can
 * use to our advantage.
 *
 * Otherwise we make NULL the correct constant according
 * to the language at play.
 */
#if defined(__GNUG__) /* C++ */
# define __CCAPRICE_NULL __null
#else
# if defined(__cplusplus)
  /*
   * C++ Specification says that NULL should be 0
   * opposed to C which defines it as ((void*)0).
   */
#  define __CCAPRICE_NULL 0
# else
#  define __CCAPRICE_NULL ((void*)0)
# endif
#endif

#define __CCAPRICE_COMPILE_TIME_ASSERT(name, x) \
 typedef int __CompileTimeAssertFailed_##name[(x)?1:-1]
 

/* TODO: everything here on down needs to be removed! */

/*
 * We can override code if -DNAIVE is passed by the build
 * script.
 */
#if !defined(__CCAPRICE_NAIVE)
# define __STRING_STRLEN_OPTIMAL
# define __STRING_MEMCHR_OPTIMAL
# define __STRING_MEMCPY_OPTIMAL
# define __STRING_MEMSET_OPTIMAL
# define __STDLIB_RANDOM_OPTIMAL
# if defined(__SSE2__)
#  define __STRING_STRLEN_OPTIMAL_SSE2
#  define __STRING_MEMCHR_OPTIMAL_SSE2
#  define __STRING_MEMCPY_OPTIMAL_SSE2
#  define __STRING_MEMSET_OPTIMAL_SSE2
#  define __STDLIB_RANDOM_OPTIMAL_SSE2
# endif
#endif

/*
 * Stores a threadsafe running instance for the library.  Contains the
 * thread stuff and static destructor call function pointer
 * 
 * TODO:
 *  FILE locking
 *  ldso destructors
 */
typedef struct {
    volatile int thread_item;
    int          threaded;
    void        *file_head;
    int          file_lock[2];
    
    void       (*fini)(void);
} __ccaprice_instance;

__CCAPRICE_EXPORT __ccaprice_instance *__ccaprice(void);

#define __CCAPRICE_INSTANCE (*__ccaprice())

/*
 * Thread utility functions for lock/unlock.  These only allow thread
 * safety in the implementation.  These shouldn't be used outside of the
 * implementation.
 */
__CCAPRICE_INTERNAL_FUNC(void, __ccaprice_thread_lock,  (volatile int *));
__CCAPRICE_INTERNAL_FUNC(void, __ccaprice_thread_unlock,(volatile int *));
#define __CCAPRICE_DOLOCK(X) (__CCAPRICE_INSTANCE.thread_item ? (__ccaprice_thread_lock  (X), 1) : ((void)(X), 1))
#define __CCAPRICE_UNLOCK(X) (__CCAPRICE_INSTANCE.thread_item ? (__ccaprice_thread_unlock(X), 1) : ((void)(X), 1))

#define __CCAPRICE_OFDOLOCK() __CCAPRICE_DOLOCK(__CCAPRICE_INSTANCE.file_lock)
#define __CCAPRICE_OFUNLOCK() __CCAPRICE_UNLOCK(__CCAPRICE_INSTANCE.file_lock)

#define __CCAPRICE_FDOLOCK(F) int __ccaprice_locked_file = ((F)->lock>=0 ? __ccaprice_file_dolock((F)) : 0)
#define __CCAPRICE_FUNLOCK(F) if (__ccaprice_locked_file) __ccaprice_file_unlock((F)); else


#endif
