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

__CCAPRICE_INTERNAL_FUNC(void, free, (void*));
__CCAPRICE_INTERNAL_FUNC(int,  main, (int, char **, char **));

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
 * We emulate the posix open/close/read/write functions which required
 * file descriptors.  This is how we handle the mapping between them
 * and actual file handles.
 */
#define __CCAPRICE_MAXFILE_HANDLES 4099
typedef struct {
    HANDLE             file;
    BOOL               text;
    BOOL               used;
} __ccaprice_win_filehandle;

/*
 * All of the function pointers to interface with the kernel to perform
 * kernel calls are here.
 */
PFNKERNEL32_SETFILEPOINTER_PROC       SetFilePointer       = NULL;
PFNKERNEL32_WRITEFILE_PROC            WriteFile            = NULL;
PFNKERNEL32_GETSTDHANDLE_PROC         GetStdHandle         = NULL;
PFNKERNEL32_EXITPROCESS_PROC          ExitProcess          = NULL;
PFNKERNEL32_GETCOMMANDLINE_PROC       GetCommandLine       = NULL;
PFNKERNEL32_VIRTUALALLOC_PROC         VirtualAlloc         = NULL;
PFNKERNEL32_VIRTUALFREE_PROC          VirtualFree          = NULL;
PFNKERNEL32_GETPROCESSHEAP_PROC       GetProcessHeap       = NULL;
PFNKERNEL32_GETFILETYPE_PROC          GetFileType          = NULL;
PFNKERNEL32_MOVEFILE_PROC             MoveFile             = NULL;
PFNKERNEL32_GETPROCESSID_PROC         GetProcessId         = NULL;
PFNKERNEL32_GETCURRENTPROCESS_PROC    GetCurrentProcess    = NULL;
PFNKERNEL32_DELETEFILE_PROC           DeleteFile           = NULL;
PFNKERNEL32_HEAPALLOC_PROC            HeapAlloc            = NULL;
PFNKERNEL32_HEAPFREE_PROC             HeapFree             = NULL;
PFNKERNEL32_GETMODULEHANDLE_PROC      GetModuleHandle      = NULL;
PFNKERNEL32_GETENVIROMENTSTRINGS_PROC GetEnviromentStrings = NULL;
PFNKERNEL32_CREATEFILE_PROC           CreateFile           = NULL;
/*
 * This needs to be gurded by a critical section some day.  Yes I know it's
 * nasty.
 */
__ccaprice_win_filehandle __ccaprice_filehandles[__CCAPRICE_MAXFILE_HANDLES];

#ifdef  __CCAPRICE_DEBUG
#define DEBUG_SYM(NAME, SPACE) printf("[ccaprice] %s %s found -> 0x%x\n", SPACE, #NAME, NAME)
#define DEBUG_LOG(NAME,   ...) printf(NAME, __VA_ARGS__)
#else
#define DEBUG_SYM(NAME, SPACE)
#define DEBUG_LOG(NAME,   ...)
#endif

void *__ccaprice_func_find(void *lib, const char *name) {    
    PIMAGE_NT_HEADERS       header      = ((PIMAGE_NT_HEADERS)((char*)lib+((PIMAGE_DOS_HEADER)lib)->e_lfanew));
    PIMAGE_DATA_DIRECTORY   export_dat  = (PIMAGE_DATA_DIRECTORY)(&header->OptionalHeader.DataDirectory[0]);
    PIMAGE_EXPORT_DIRECTORY export_dir  = (PIMAGE_EXPORT_DIRECTORY)((char*)lib + export_dat->VirtualAddress);
    
    void **function_table = (void**)((char*)lib + export_dir->AddressOfFunctions);
    WORD  *ordinals_table = (WORD*) ((char*)lib + export_dir->AddressOfNameOrdinals);
    char **wordname_table = (char**)((char*)lib + export_dir->AddressOfNames);
    
    void *address = NULL;
    
    /*
     * Ordinal import is faster than name import. No need to do strange things
     * with string comparisions which is really slow!.
     */
    if (((DWORD)name >> 16) == 0) {
        WORD  ordinal = LOWORD(name);
        DWORD base    = export_dir->Base;
        
        if (ordinal < base || ordinal > base + export_dir->NumberOfFunctions)
            return NULL;
            
        address = (void*)((char*)lib + (DWORD)function_table[ordinal - base]);
    } else {
        DWORD i;
        for (i = 0; i < export_dir->NumberOfNames; i++)
            if (!strcmp(name,  (char*)lib + (DWORD)wordname_table[i]))
                address = (void*)((char*)lib + (DWORD)function_table[ordinals_table[i]]);
    }
    
    /* forwarded? */
    if ((char*)address >= (char*)export_dir && (char*)address < (char*)export_dir + export_dat->Size) {
        char   *library  = strdup((char*)address);
        char   *function;
        HMODULE module;
        
        if (!library)
            return NULL;
           
        /* name and terminate */
        function = strchr(library, '.');
        *function++ = '\0';
        
        DEBUG_LOG("[ccaprice] function %s is forwarded to %s (patching...)\n", name, function);
        
        /* try forward */
        address = (module = GetModuleHandle((LPCSTR)library)) ?
                    (__ccaprice_func_find(module, function))  :
                    (NULL);
    
        free(library);
    }
    return address;
}

/*
 * This is some serious magic to get the command line arguments
 * and size from the kernel to pass to main.
 */
typedef struct {
    char *argv[32+1];
    int   argc;
    char *done;
} __ccaprice_commandline_data;

void __ccaprice_calculate_commandline(__ccaprice_commandline_data *data) {
    
    char *sys = (char*)GetCommandLine();
    int   len = strlen(sys);
    
    /* copy */
    char *cmd = (char*)HeapAlloc(GetProcessHeap(), 0, sizeof(char*) * (len + 1));
    data->done = cmd;
    if (!cmd) return;
    strcpy(cmd, sys);
    
    /* step 1: handle quoted file names) */
    if (*cmd == '"') {
        cmd ++;
        data->argv[0] = cmd; /* exe name */
        
        /* skip to next quote */
        while (*cmd && *cmd != '"')
            cmd++;
        
        /* terminate */
        if (*cmd)
            *cmd ++ = '\0';
        else
            return;
    } else {
        data->argv[0] = cmd; /* exe name */
        
        /* skip to next white space */
        while (*cmd && *cmd != ' ')
            cmd++;
        
        /* terminate */
        if (*cmd)
            *cmd ++ = '\0';
    }
    /* main loop to calculate argument list */
    for (;;) {
        
        /* skip whitespace */
        while (*cmd && *cmd == ' ')
            cmd++;
        
        if (*cmd == 0)
            return;
            
        /* argument starts with quote */
        if (*cmd == '"') {
            cmd++;
            
            /* add to list */
            data->argv[data->argc++] = cmd;
            data->argv[data->argc]   = NULL;
            
            /* skip all to end quote */
            while (*cmd && *cmd != '"')
                cmd++;
                
            if (*cmd == 0)
                return;
            
            /* terminate */
            if (*cmd)
                *cmd++ = '\0';
        } else {
            /* add to list */
            data->argv[data->argc++] = cmd;
            data->argv[data->argc]   = 0;
            
            /* skip to next space */
            while (*cmd && *cmd != ' ')
                cmd++;
                
            if (*cmd == 0)
                return;
            
            /* terminate */
            if (*cmd)
                *cmd = '\0';
        }
        
        if (data->argc >= 32)
            return;
    }
}

void __ccaprice_start () {
    void *PEB  = NULL;
    void *BASE = NULL;
    __ccaprice_commandline_data cmd = { {0}, 1, 0 };
    int                         ret =   0;
    
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
    WriteFile            = __ccaprice_func_find(BASE, "WriteFile");     // must be first!
    GetStdHandle         = __ccaprice_func_find(BASE, "GetStdHandle");  // must be second!
    
    DEBUG_LOG("[ccaprice] Found kernel32.dll base address 0x%x\n\nFinding functions ...\n", BASE);
    
    SetFilePointer       = __ccaprice_func_find(BASE, "SetFilePointer");
    ExitProcess          = __ccaprice_func_find(BASE, "ExitProcess");
    GetModuleHandle      = __ccaprice_func_find(BASE, "GetModuleHandleA");
    GetCommandLine       = __ccaprice_func_find(BASE, "GetCommandLineA");
    GetProcessHeap       = __ccaprice_func_find(BASE, "GetProcessHeap");
    GetFileType          = __ccaprice_func_find(BASE, "GetFileType");
    MoveFile             = __ccaprice_func_find(BASE, "MoveFileA");
    GetProcessId         = __ccaprice_func_find(BASE, "GetProcessId");
    GetCurrentProcess    = __ccaprice_func_find(BASE, "GetCurrentProcess");
    VirtualAlloc         = __ccaprice_func_find(BASE, "VirtualAlloc");
    VirtualFree          = __ccaprice_func_find(BASE, "VirtualFree");
    DeleteFile           = __ccaprice_func_find(BASE, "DeleteFileA");
    HeapAlloc            = __ccaprice_func_find(BASE, "HeapAlloc");
    HeapFree             = __ccaprice_func_find(BASE, "HeapFree");
    GetEnviromentStrings = __ccaprice_func_find(BASE, "GetEnvironmentStringsA");
    CreateFile           = __ccaprice_func_find(BASE, "CreateFileA");
    
    DEBUG_SYM(WriteFile,"            ");
    DEBUG_SYM(GetStdHandle,"         ");
    DEBUG_SYM(SetFilePointer,"       ");
    DEBUG_SYM(ExitProcess,"          ");
    DEBUG_SYM(GetCommandLine,"       ");
    DEBUG_SYM(GetProcessHeap,"       ");
    DEBUG_SYM(GetFileType,"          ");
    DEBUG_SYM(MoveFile,"             ");
    DEBUG_SYM(GetProcessId,"         ");
    DEBUG_SYM(GetCurrentProcess,"    ");
    DEBUG_SYM(VirtualAlloc,"         ");
    DEBUG_SYM(VirtualFree,"          ");
    DEBUG_SYM(HeapAlloc,"            ");
    DEBUG_SYM(HeapFree,"             ");
    DEBUG_SYM(GetEnviromentStrings," ");
    DEBUG_SYM(CreateFile,"           ");
    
    /*
     * Specify some filetypes from the getgo. So our structure accuratly
     * reflects the correct values.
     */
    __ccaprice_filehandles[0].text = !!(GetFileType(__ccaprice_filehandle(0)) == FILE_TYPE_CHAR);
    __ccaprice_filehandles[1].text = !!(GetFileType(__ccaprice_filehandle(1)) == FILE_TYPE_CHAR);
    __ccaprice_filehandles[2].text = !!(GetFileType(__ccaprice_filehandle(2)) == FILE_TYPE_CHAR);
    
    /*
     * This will actually allocate memory that needs to be freed
     * and this needs to yet be parsed into a list.
     * 
     * TODO: fix this!
     */
    __ccaprice_enviroment = (char**)GetEnviromentStrings();
    
    /*
     * Invoke main and store the return status of it some where
     * it will be used for the call to the kernel via ExitProcess.
     */
    __ccaprice_calculate_commandline(&cmd);
    ret = main(cmd.argc, cmd.argv, __ccaprice_enviroment);
    
    /*
     * Cleanup any used heap space for command line agruments
     * since the calculation of them above.
     */
    if (cmd.done)
        HeapFree(GetProcessHeap(), 0, cmd.done);
        
    ExitProcess(ret);
}

HFILE __ccaprice_filehandle(int fd) {
    __ccaprice_win_filehandle *handle;
    /* LOCK ()  */
    switch (fd) {
        case 0: return GetStdHandle(STD_INPUT_HANDLE);
        case 1: return GetStdHandle(STD_OUTPUT_HANDLE);
        case 2: return GetStdHandle(STD_ERROR_HANDLE);
        default:
            if ((fd >= 3) && (fd < __CCAPRICE_MAXFILE_HANDLES)) {
                handle = &__ccaprice_filehandles[(size_t)fd - 3];
                if (handle->used)
                    return handle->file;
            }
        /* no break, fall to null */
    }
    return NULL;
}

/*
 * Adds a file handle to with the file-descriptor id to the file
 * handle table.
 */
int __ccaprice_fileadd(HANDLE file) {
    __ccaprice_win_filehandle *handle = NULL;
    ssize_t                    search;
        
    /*
     * Find the next valid handle in the list that we can use
     * by checking all the handle->used fields.
     * 
     * We start the search from offset 3 because STDOUT,
     * STDIN, and STDERR exist within those first three entries.
     */
    for (search = 3; search < __CCAPRICE_MAXFILE_HANDLES; search++) {
        handle = &__ccaprice_filehandles[search];
        if (!handle->used)
            break;
    }
    
    /*
     * Couldn't find a mapping for a file handle?  We probably exceeded
     * the limit.
     */
    if (handle->used)
        return 0;
    
    handle->used = 1;
    handle->file = file;
    
    /*
     * Search is an interesting value, it's actually the file descriptor
     * (the location in the file handles table to the real file handle)
     */
    return search;
}

/*
 * Actual systemcalls (these must work exactly like posix ones) so we
 * emulate the entier interface of these 17 functions for windows.
 */
__SYS_WRITE  {
    HANDLE       fileh; // file handle
    DWORD        wrote;
    
    if ((fileh = __ccaprice_filehandle(A1)) == NULL)
        return -1;
    
    /* not a standard descriptor ?*/
    if (!WriteFile(fileh, A2, A3, &wrote, ((LPOVERLAPPED)NULL)))
        return -1;
        
    return ((ssize_t)wrote);
}

__SYS_UNLINK { return (DeleteFile((LPCSTR)A1) != 0); }
__SYS_EXIT   { ExitProcess(A1); }
__SYS_GETPID { return GetProcessId(GetCurrentProcess()); }
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

__SYS_WRITEV {
    /*
     * Implements writev in a brute-force sort of way.  Don't expect this to be
     * anywhere near the speed as the writev syscall on linux.
     */
    typedef struct { char *base; size_t len; } data;
    data    *obtain = (data*)A2;
    ssize_t  totals = 0;
    ssize_t  amount = 0;
    ssize_t  checks = 0;
    for (; amount < A3; amount++) {
        if ((checks = write(A1, obtain[amount].base, obtain[amount].len)) == -1)
            return -1;
        totals += checks;
    }
        
    return totals;
}
__SYS_RENAME { return MoveFile((LPCSTR)A1, (LPCSTR)A2); }

/*
 * These are trivial to implement if you don't need to support vminfo
 * or any of that crazy shit.
 */
__SYS_MUNMAP {
    if (!VirtualFree(A1, 0, MEM_RELEASE))
        goto stop;
stop:
    return 0;
}

__SYS_MMAP   {
    A1 = VirtualAlloc(A1, A2, MEM_RESERVE | MEM_COMMIT | MEM_TOP_DOWN, PAGE_READWRITE);
    if (!A1) {
        A1 = NULL;
        goto stop;
    }
/*
 * The jump makes debugging much simpler.  Also we're going to implement
 * a spinlock later which will be rel ptr fixed.
 */
stop:
    /* rel ptr */
    return A1;
}

__SYS_OPEN   {
    DWORD access = (A2 & O_RDONLY) ? GENERIC_READ  : GENERIC_WRITE;
    DWORD select = (A2 & O_APPEND) ? OPEN_EXISTING : CREATE_ALWAYS;
    
    HANDLE file  = CreateFile((LPCSTR)A1, access, 0, 0, select, 0, 0);
    if (file == INVALID_HANDLE_VALUE)
        return 0;
    
    /*
     * Add the file mapping to the file descriptor table.  We will return
     * this file descriptor from fileadd(open.<<>>)
     */
    return __ccaprice_fileadd(file);
}

/*
 * All of these need to be implemented yet.  There is going to be a ton
 * of work getting the spinlocks right.
 */
__SYS_READ   { /*TODO*/ return -1; }
__SYS_FCNTL  { /*TODO*/ return -1; }
__SYS_KILL   { /*TODO*/ return -1; }
__SYS_IOCTL  { /*TODO*/ return -1; }
__SYS_CLOSE  { /*TODO*/ return -1; }
__SYS_FUTEX  { /*TODO*/ return -1; }
__SYS_PAUSE  { /*TODO*/ return -1; }

#endif
