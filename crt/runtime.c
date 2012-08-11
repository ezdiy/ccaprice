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
#include <string.h>
#include <locale.h>

const char *__ccaprice_build_date __CCAPRICE_USED = __DATE__;
const char *__ccaprice_build_time __CCAPRICE_USED = __TIME__;
const char *__ccaprice_build_comp __CCAPRICE_USED = __COMP__;
const char *__ccaprice_build_info __CCAPRICE_USED = __INFO__;
const char *__ccaprice_build_host __CCAPRICE_USED = __OSOS__;


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

#ifndef WINDOWS
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
    __ccaprice_locale_init(); /* TODO: rewrite all this local hack */
    
    void __ccaprice_setup();
    __ccaprice_setup();
    
    __CCAPRICE_INSTANCE.fini  = fini;
    
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
 * There is only a required 17 system calls to implement the entire functionality
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
__SYS_LSEEK  { __SYSCALL_PERFORM(__SYSCALL_DORETURN,       SYS_lseek,  3); }
__SYS_FCNTL  { __SYSCALL_PERFORM(__SYSCALL_DORETURN,       SYS_fcntl,  3); }
__SYS_WRITEV { __SYSCALL_PERFORM(__SYSCALL_DORETURN,       SYS_writev, 3); }
__SYS_RENAME { __SYSCALL_PERFORM(__SYSCALL_DORETURN,       SYS_rename, 2); }
__SYS_PAUSE  { __SYSCALL_PERFORM(__SYSCALL_DORETURN,       SYS_pause,  0); }
#else
/*
 * Everything for windows is here.  Lets start shall we?
 * Windows has a really neat way at doing calls to the kernel.
 * Every process has access to kernel32.dll which is stored in a PEB
 * structure.  We don't need to go over the details of how that's
 * handled since we only need a handle to kernel32.dll.  The code that
 * does this isn't really wrote to look pretty.  Once we have a handle
 * we can find the exports table, iterate the table to find the functions
 * we need to implement the syscalls here.
 */
#include "windows.h"

/*
 * All of the function pointers to interface with the kernel to perform
 * kernel calls are here.
 */
PFNKERNEL32_SETFILEPOINTER_PROC SetFilePointer = NULL;
PFNKERNEL32_WRITEFILE_PROC      WriteFile      = NULL;
PFNKERNEL32_GETSTDHANDLE_PROC   GetStdHandle   = NULL;
PFNKERNEL32_EXITPROCESS_PROC    ExitProcess    = NULL;
PFNKERNEL32_GETCOMMANDLINE_PROC GetCommandLine = NULL;
PFNKERNEL32_HEAPALLOC_PROC      HeapAlloc      = NULL;
PFNKERNEL32_HEAPFREE_PROC       HeapFree       = NULL;
PFNKERNEL32_GETPROCESSHEAP_PROC GetProcessHeap = NULL;
PFNKERNEL32_GETFILETYPE_PROC    GetFileType    = NULL;

/*
 * This needs to be gurded by a critical section some day.  Yes I know it's
 * nasty.
 */
__ccaprice_win_filehandle __ccaprice_filehandles[__CCCAPRICE_MAXFILE_HANDLES];

void *__ccaprice_func_find(void *lib, const char *name) {
    PIMAGE_NT_HEADERS       header      = ((PIMAGE_NT_HEADERS)((char*)lib+((PIMAGE_DOS_HEADER)lib)->e_lfanew));
    PIMAGE_DATA_DIRECTORY   export_dat  = (PIMAGE_DATA_DIRECTORY)(&header->OptionalHeader.DataDirectory[0]);
    PIMAGE_EXPORT_DIRECTORY export_dir  = (PIMAGE_EXPORT_DIRECTORY)((char*)lib + export_dat->VirtualAddress);
    
    void **function_table = (void**)((char*)lib + export_dir->AddressOfFunctions);
    WORD  *ordinals_table = (WORD*) ((char*)lib + export_dir->AddressOfNameOrdinals);
    char **wordname_table = (char**)((char*)lib + export_dir->AddressOfNames);
    
    /*
     * Ordinal import is faster than name import. No need to do strange things
     * with string comparisions which is really slow!.
     */
    if (((DWORD)name >> 16) == 0) {
        WORD  ordinal = LOWORD(name);
        DWORD base    = export_dir->Base;
        
        if (ordinal < base || ordinal > base + export_dir->NumberOfFunctions)
            return NULL;
            
        return (void*)((char*)lib + (DWORD)function_table[ordinal - base]);
    } else {
        DWORD i;
        for (i = 0; i < export_dir->NumberOfNames; i++)
            if (!strcmp(name,  (char*)lib + (DWORD)wordname_table[i]))
                return (void*)((char*)lib + (DWORD)function_table[ordinals_table[i]]);
    }
    /* TODO: forwarded lookups */
    return NULL;
}
void __ccaprice_start (int (WINAPI *main)(int, char **)) {
    void *PEB  = NULL;
    void *BASE = NULL;
    
    /*
     * Store address of PEB in PEB.  Then work down the PEB structure
     * and linked list for the base address of kernel32.dll.
     */
    __asm__ __volatile__ ("mov %%fs:0x30, %0" : "=r"(PEB));
    BASE =
        *((void**)((unsigned char *)( *((void**)((unsigned char *)(                    
                *((void**)((unsigned char *)(                 
                    *((void**)((unsigned char *)(             
                    *((void**)((unsigned char *)PEB + 0x0C))  // Peb->Ldr
                ) + 0x14))                                    // .InMemoryOrderModuleList.Flink (1st)
            ) + 0x00))                                        //                                (2nd)
        ) + 0x00))                                            //                                (3rd)
    ) + 0x10));                                               // .BaseAddress (kernel32.dll)
 
    /*
     * Obtain all the required functions for ccaprice from kernel32.dll.
     * Now that we have a valid handle.
     */
    SetFilePointer = __ccaprice_func_find(BASE, "SetFilePointer");
    WriteFile      = __ccaprice_func_find(BASE, "WriteFile");
    GetStdHandle   = __ccaprice_func_find(BASE, "GetStdHandle");
    ExitProcess    = __ccaprice_func_find(BASE, "ExitProcess");
    GetCommandLine = __ccaprice_func_find(BASE, "GetCommandLineA");
    HeapAlloc      = __ccaprice_func_find(BASE, "HeapAlloc");
    GetProcessHeap = __ccaprice_func_find(BASE, "GetProcessHeap");
    HeapFree       = __ccaprice_func_find(BASE, "HeapFree");
    GetFileType    = __ccaprice_func_find(BASE, "GetFileType");
    
    /*
     * TODO: the stack is all fucked up.  I can't seem to beable to
     * use GetCommandLine to setup the stuff required to call main
     */
    ExitProcess(0);
}

HFILE __ccaprice_filehandle(int fd) {
    __ccaprice_win_filehandle *handle;
    /* LOCK ()  */
    switch (fd) {
        case 0: return GetStdHandle(STD_INPUT_HANDLE);
        case 1: return GetStdHandle(STD_OUTPUT_HANDLE);
        case 2: return GetStdHandle(STD_ERROR_HANDLE);
        default:
            if ((fd >= 3) && (fd < __CCCAPRICE_MAXFILE_HANDLES)) {
                handle = &__ccaprice_filehandles[(size_t)fd - 3];
                if (handle->used)
                    return handle->file;
            }
        /* no break, fall to null */
    }
    return NULL;
}

/*
 * Actual systemcalls (these must work exactly like posix ones) so we
 * emulate the entier interface of these 17 functions for windows.
 */
__SYS_WRITE  {
    DWORD wrote;
    WriteFile(__ccaprice_filehandle(A1), A2, A3, &wrote, ((LPOVERLAPPED)NULL));
    return wrote;
}

__SYS_READ   { /*TODO*/ }
__SYS_OPEN   { /*TODO*/ }
__SYS_KILL   { /*TODO*/ }
__SYS_UNLINK { /*TODO*/ }
__SYS_IOCTL  { /*TODO*/ }
__SYS_CLOSE  { /*TODO*/ }
__SYS_EXIT   { /*TODO*/ }
__SYS_GETPID { /*TODO*/ }
__SYS_MMAP   { /*TODO*/ }
__SYS_MUNMAP { /*TODO*/ }
__SYS_FUTEX  { /*TODO*/ }
__SYS_LSEEK  { 
    HFILE *file = __ccaprice_filehandle(A1);
    DWORD  head;
    DWORD  bind;
    if (!file) {
        /* errno = EBADF; */
        return -1;
    }
    
    switch (A3) {
        case 0: head = FILE_CURRENT; break;
        case 1: head = FILE_BEGIN;   break;
        case 2: head = FILE_END;     break;
        default:
            /* errno = EINVAL; */
            /* UNLOCK() */
            return -1;
            break;
    }
    
    if ((bind = SetFilePointer(file, A2, ((PLONG)NULL), head)) == 0xFFFFFFFF)
        return -1;
    else
        return ((long)head);
    return 0;
}

__SYS_FCNTL  {  }
__SYS_WRITEV {
    //return write(A1, A2, A3);
}
__SYS_RENAME {  }
__SYS_PAUSE  {  }
#endif
