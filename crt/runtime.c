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

__CCAPRICE_INTERNAL_FUNC(void,  free,   (void*));
__CCAPRICE_INTERNAL_FUNC(void*, realloc,(void*, size_t));
__CCAPRICE_INTERNAL_FUNC(void*, malloc, (size_t));
__CCAPRICE_INTERNAL_FUNC(int,   main,   (int, char **, char **));
__CCAPRICE_INTERNAL_FUNC(int,   printf, (const char *, ...));

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
#define __CCAPRICE_WINDOWS_NO_EXPORTS
#include <windows.h>
#include <signal.h>

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
 * kernel calls are here (see bottom of windows.h)
 */
static PFNKERNEL32_SETFILEPOINTER_PROC              SetFilePointer              = NULL;
static PFNKERNEL32_WRITEFILE_PROC                   WriteFile                   = NULL;
static PFNKERNEL32_GETSTDHANDLE_PROC                GetStdHandle                = NULL;
static PFNKERNEL32_EXITPROCESS_PROC                 ExitProcess                 = NULL;
static PFNKERNEL32_GETCOMMANDLINE_PROC              GetCommandLine              = NULL;
static PFNKERNEL32_VIRTUALALLOC_PROC                VirtualAlloc                = NULL;
static PFNKERNEL32_VIRTUALFREE_PROC                 VirtualFree                 = NULL;
static PFNKERNEL32_GETPROCESSHEAP_PROC              GetProcessHeap              = NULL;
static PFNKERNEL32_GETFILETYPE_PROC                 GetFileType                 = NULL;
static PFNKERNEL32_MOVEFILE_PROC                    MoveFile                    = NULL;
static PFNKERNEL32_GETPROCESSID_PROC                GetProcessId                = NULL;
static PFNKERNEL32_GETCURRENTPROCESS_PROC           GetCurrentProcess           = NULL;
static PFNKERNEL32_DELETEFILE_PROC                  DeleteFile                  = NULL;
static PFNKERNEL32_HEAPALLOC_PROC                   HeapAlloc                   = NULL;
static PFNKERNEL32_HEAPFREE_PROC                    HeapFree                    = NULL;
static PFNKERNEL32_GETMODULEHANDLE_PROC             GetModuleHandle             = NULL;
static PFNKERNEL32_GETENVIROMENTSTRINGS_PROC        GetEnviromentStrings        = NULL;
static PFNKERNEL32_CREATEFILE_PROC                  CreateFile                  = NULL;
static PFNKERNEL32_SUSPENDTHREAD_PROC               SuspendThread               = NULL;
static PFNKERNEL32_GETCURRENTTHREAD_PROC            GetCurrentThread            = NULL;
static PFNKERNEL32_READFILE_PROC                    ReadFile                    = NULL;
static PFNKERNEL32_SETUNHANDLEDEXCEPTIONFILTER_PROC SetUnhandledExceptionFilter = NULL;

#define data_add(a,v) ((((a)==0||((int*)(a)-2)[1]+(1)>=((int*)(a)-2)[0])?data_grow((void**)&(a),(1),sizeof(*(a))):0),(a)[((int*)(a)-2)[1]++]=(v))
#define data_count(a) ((a)? ((int*)(a)-2)[1]:0)
#define data_free(a)  ((a)?free(((int*)(a)-2)),0:0)

static void *data_grow(void **a, int in, int it) {
    int m = *a ? 2 * ((int*)(*a)-2)[0]+in : in+1;
    void *p = realloc(*a ? ((int*)(*a)-2) : 0, it * m + sizeof(int)*2);
    if (p) {
        if (!*a) ((int*)p)[1] = 0;
        *a = (void*)((int*)p+2);
        ((int*)(*a)-2)[0] = m;
    }
    return *a;
}

/*
 * This needs to be gurded by a critical section some day.  Yes I know it's
 * nasty.
 */
__ccaprice_win_filehandle __ccaprice_filehandles[__CCAPRICE_MAXFILE_HANDLES];

#ifndef NDEBUG
#define DEBUG_SYM(NAME, SPACE) do { if (WriteFile && GetStdHandle) { printf("[ccaprice] %s %s found -> 0x%x\n", SPACE, #NAME, NAME); } } while (0)
#define DEBUG_LOG(NAME,   ...) do { if (WriteFile && GetStdHandle) { printf(NAME, __VA_ARGS__); } } while (0)
#else
#define DEBUG_SYM(NAME, SPACE)
#define DEBUG_LOG(NAME,   ...)
#endif

void *__ccaprice_func_find(void *lib, const char *name) {    
    PIMAGE_NT_HEADERS       header      = ((PIMAGE_NT_HEADERS)((char*)lib+((PIMAGE_DOS_HEADER)lib)->e_lfanew));
    PIMAGE_DATA_DIRECTORY   export_dat  = (PIMAGE_DATA_DIRECTORY)(&header->OptionalHeader.DataDirectory[0]);
    PIMAGE_EXPORT_DIRECTORY export_dir  = (PIMAGE_EXPORT_DIRECTORY)((char*)lib + export_dat->VirtualAddress);
    
    DEBUG_LOG("[ccaprice] finding %s using:\n", name);
    DEBUG_LOG("    header          = 0x%x\n", header);
    DEBUG_LOG("    exportdata      = 0x%x\n", export_dat);
    DEBUG_LOG("    exportdirectory = 0x%x\n", export_dir);
    
    void **function_table = (void**)((char*)lib + export_dir->AddressOfFunctions);
    WORD  *ordinals_table = (WORD*) ((char*)lib + export_dir->AddressOfNameOrdinals);
    char **wordname_table = (char**)((char*)lib + export_dir->AddressOfNames);
    
    DEBUG_LOG("    functiontable   = 0x%x\n", function_table);
    DEBUG_LOG("    ordinalstable   = 0x%x\n", ordinals_table);
    DEBUG_LOG("    wordnametable   = 0x%x\n", wordname_table);
    
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
    char **argv;
    char **argp;
    int    argc;
    char  *done;
} __ccaprice_commandline_data;

void __ccaprice_calculate_commandline(__ccaprice_commandline_data *data) {
    char   *get  = (char*)GetEnviromentStrings();
    char   *sys  = (char*)GetCommandLine();
    char   *cmd  = strdup(sys); /* copy */
    
    /*
     * Figure out argp first. Then handle command line stuff for argc
     * and argv later.
     */
    while (*get) {
        /* find end */
        char   *itm = NULL;
        char   *end = get;
        while (*end != '\0') data_add(itm, *end++);
        
        data_add(data->argp, itm); 
        get = end + 1;
    }
    
    data->done = cmd;
    
    /* step 1: handle quoted file names) */
    if (*cmd == '"') {
        data_add(data->argv, cmd); /* exe name */
        
        /* skip to next quote */
        while (*cmd && *cmd != '"')
            cmd++;
        
        /* terminate */
        if (*cmd)
            *cmd ++ = '\0';
        else
            return;
    } else {
        data_add(data->argv, cmd); /* exe name */
        
        /* skip to next white space */
        while (*cmd && *cmd != ' ')
            cmd++;
        
        /* terminate */
        if (*cmd)
            *cmd ++ = '\0';
    }
    /* main loop to calculate argument list */
    DEBUG_LOG("[ccaprice] Calculating argument list for main invokation ...\n", "");
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
            data_add(data->argv, cmd);
            data_add(data->argv, NULL);
            data->argc++;
            
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
            data_add(data->argv, cmd);
            data_add(data->argv, NULL);
            data->argc++;
            
            /* skip to next space */
            while (*cmd && *cmd != ' ')
                cmd++;
                
            if (*cmd == 0)
                return;
            
            /* terminate */
            if (*cmd)
                *cmd = '\0';
        }
    }
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

/* structured exception handling (SEH) for signal ... this is fugly
 * we all hate windows's SEH (ALL OF US EVEN YOU) [YES YOU, THE ONE
 * READING THIS].
 */
/* signal funptrs (stolen from signal.c) */
__CCAPRICE_INTERNAL_TYPE(void (*__ccaprice_sigfpe)(int),);
__CCAPRICE_INTERNAL_TYPE(void (*__ccaprice_sigill)(int),);
__CCAPRICE_INTERNAL_TYPE(void (*__ccaprice_sigsegv)(int),);

static LPTOP_LEVEL_EXCEPTION_FILTER OEH;
static LONG CALLBACK SEH(EXCEPTION_POINTERS *e) {
	int    sig;
	void (*hnd)(int);
	
	switch (e->ExceptionRecord->ExceptionCode) {
		case EXCEPTION_ACCESS_VIOLATION:
		case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
		case EXCEPTION_DATATYPE_MISALIGNMENT:
		case EXCEPTION_GUARD_PAGE:
		case EXCEPTION_IN_PAGE_ERROR:
		case EXCEPTION_STACK_OVERFLOW:
			sig = SIGSEGV;
			hnd = __ccaprice_sigsegv;
			break;
			
		case EXCEPTION_ILLEGAL_INSTRUCTION:
        case EXCEPTION_PRIV_INSTRUCTION:
            sig = SIGILL;
            hnd = __ccaprice_sigill;
            break;

        case EXCEPTION_INT_DIVIDE_BY_ZERO:
        case EXCEPTION_INT_OVERFLOW:
        case EXCEPTION_FLT_DENORMAL_OPERAND:
        case EXCEPTION_FLT_DIVIDE_BY_ZERO:
        case EXCEPTION_FLT_INEXACT_RESULT:
        case EXCEPTION_FLT_INVALID_OPERATION:
        case EXCEPTION_FLT_OVERFLOW:
        case EXCEPTION_FLT_STACK_CHECK:
        case EXCEPTION_FLT_UNDERFLOW:
            sig = SIGFPE;
            hnd = __ccaprice_sigfpe;
            break;

        default:
            return OEH ? OEH(e) : EXCEPTION_EXECUTE_HANDLER;
    }

         if(hnd == SIG_DFL) return EXCEPTION_EXECUTE_HANDLER;
    else if(hnd == SIG_IGN) return EXCEPTION_CONTINUE_EXECUTION;
		
    hnd(sig);
    return EXCEPTION_CONTINUE_EXECUTION;
}

void __ccaprice_start () {
    void *PEB  = NULL;
    void *BASE = NULL;
    
    __ccaprice_commandline_data cmd = { 0, 0, 1, 0 };
    int                         ret =   0;
    
    /*
     * Store address of PEB in PEB.  Then work down the PEB structure
     * and linked list for the base address of kernel32.dll.
     */
    __asm__ __volatile__ ("mov %%fs:0x30, %0" : "=r"(PEB));
    BASE = *((void**)((unsigned char *)(
            *((void**)((unsigned char *)(                    
             *((void**)((unsigned char *)(                 
              *((void**)((unsigned char *)(             
               *((void**)((unsigned char *)PEB + 0x0C))
                ) + 0x14))
               )  + 0x00))
              )   + 0x00))
             )    + 0x10)
            );
    /*
     * Obtain all the required functions for ccaprice from kernel32.dll.
     * Now that we have a valid handle.
     */
    WriteFile            = __ccaprice_func_find(BASE, "WriteFile");     // must be first!
    GetStdHandle         = __ccaprice_func_find(BASE, "GetStdHandle");  // must be second!
 
    DEBUG_LOG("[ccaprice] Found PEB @ 0x30(FS), points to 0x%x\n", PEB); 
    DEBUG_LOG("[ccaprice] Found kernel32.dll base address 0x%x\n\nFinding functions ...\n", BASE);
    
	/* see bottom of windows.h */
    SetFilePointer               = __ccaprice_func_find(BASE, "SetFilePointer");
    ExitProcess                  = __ccaprice_func_find(BASE, "ExitProcess");
    GetModuleHandle              = __ccaprice_func_find(BASE, "GetModuleHandleA");
    GetCommandLine               = __ccaprice_func_find(BASE, "GetCommandLineA");
    GetProcessHeap               = __ccaprice_func_find(BASE, "GetProcessHeap");
    GetFileType                  = __ccaprice_func_find(BASE, "GetFileType");
    MoveFile                     = __ccaprice_func_find(BASE, "MoveFileA");
    GetProcessId                 = __ccaprice_func_find(BASE, "GetProcessId");
    GetCurrentProcess            = __ccaprice_func_find(BASE, "GetCurrentProcess");
    VirtualAlloc                 = __ccaprice_func_find(BASE, "VirtualAlloc");
    VirtualFree                  = __ccaprice_func_find(BASE, "VirtualFree");
    DeleteFile                   = __ccaprice_func_find(BASE, "DeleteFileA");
    HeapAlloc                    = __ccaprice_func_find(BASE, "HeapAlloc");
    HeapFree                     = __ccaprice_func_find(BASE, "HeapFree");
    GetEnviromentStrings         = __ccaprice_func_find(BASE, "GetEnvironmentStringsA");
    CreateFile                   = __ccaprice_func_find(BASE, "CreateFileA");
    SuspendThread                = __ccaprice_func_find(BASE, "SuspendThread");
    GetCurrentThread             = __ccaprice_func_find(BASE, "GetCurrentThread");
    ReadFile                     = __ccaprice_func_find(BASE, "ReadFile");
	SetUnhandledExceptionFilter  = __ccaprice_func_find(BASE, "SetUnhandledExceptionFilter"); 
    
    DEBUG_SYM(WriteFile,"                   ");
    DEBUG_SYM(GetStdHandle,"                ");
    DEBUG_SYM(SetFilePointer,"              ");
    DEBUG_SYM(ExitProcess,"                 ");
    DEBUG_SYM(GetCommandLine,"              ");
    DEBUG_SYM(GetProcessHeap,"              ");
    DEBUG_SYM(GetFileType,"                 ");
    DEBUG_SYM(MoveFile,"                    ");
    DEBUG_SYM(GetProcessId,"                ");
    DEBUG_SYM(GetCurrentProcess,"           ");
    DEBUG_SYM(VirtualAlloc,"                ");
    DEBUG_SYM(VirtualFree,"                 ");
    DEBUG_SYM(HeapAlloc,"                   ");
    DEBUG_SYM(HeapFree,"                    ");
    DEBUG_SYM(GetEnviromentStrings,"        ");
    DEBUG_SYM(CreateFile,"                  ");
    DEBUG_SYM(SuspendThread,"               ");
    DEBUG_SYM(GetCurrentThread,"            ");
    DEBUG_SYM(ReadFile,"                    ");
	DEBUG_SYM(SetUnhandledExceptionFilter," ");
	
	/* setup SEH for signals */
	OEH = SetUnhandledExceptionFilter(SEH);
    
    /*
     * Invoke main and store the return status of it some where
     * it will be used for the call to the kernel via ExitProcess.
     */
    __ccaprice_calculate_commandline(&cmd);
    ret = main(cmd.argc, cmd.argv, cmd.argp);
    
    data_free(cmd.argv);
    data_free(cmd.argp);
    free     (cmd.done);
    
    /*
     * Cleanup any used heap space for command line agruments
     * since the calculation of them above.
     */
    if (cmd.done)
        HeapFree(GetProcessHeap(), 0, cmd.done);
        
    ExitProcess(ret);
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
        
    handle->text = !!(GetFileType(file) == FILE_TYPE_CHAR);
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

    /*
     * TextMode is always ascii! Translate LF -> CRLF. To respect the
     * WINDOWS way.
     */
    if (A1 <= 3 || (A1 > 3 && __ccaprice_filehandles[(size_t)A1 - 3].text)) {
        const char *src = (const char *)A2;
        const char *end = "\r\n"; /* CRLF */
        size_t      beg = 0;
        size_t      itr = 0;
        size_t      put = 0;
        
        for (itr = 0; itr < A3; itr++) {
            if (src[itr] != '\n')
                continue;
            
            /* don't translate this step */
            if (itr > 0 && src[itr-1] == '\r')
                continue;
                
            if (itr > beg) {
                if (!WriteFile(fileh, &src[beg], itr-beg, &wrote, ((LPOVERLAPPED)NULL)))
                    return -1;
                put += wrote;
            }
            
            if (!WriteFile(fileh, end, 2, &wrote, ((LPOVERLAPPED)NULL)))
                return -1;
            
            /*
             * Even though we wrote two bytes for CRLF.  We really only wrote
             * '\n'. Which we must respect here.
             */
            put ++;
            beg = itr+1;
        }
        if (itr > beg) {
            if (!WriteFile(fileh, &src[beg], itr-beg, &wrote, ((LPOVERLAPPED)NULL)))
                return -1;
            put += wrote;
        }
        return ((ssize_t)put);
    }
    /* not a text mode file ? */
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
__SYS_READ   { 
    HANDLE file = __ccaprice_filehandle(A1);
    BOOL   text = (A1 <= 3 || (A1 > 3 && __ccaprice_filehandles[(size_t)A1 - 3].text));
    char  *core = (text) ? (char*)malloc(A3) : (char*)A2;
    DWORD  size;
    
    if (!ReadFile(file, core, A3, &size, 0)) return -1; /* ERROR */
    if (!size)                               return  0; /* EOF   */
    
    /*
     * Textmode translate CR -> LF because windows files are strange like
     * that. For some convoluted reason.
     */
    if  (text) {
        char *dst = (char*)A2;
        DWORD itr = 0;
        
        for (; itr < size; itr++) {
            if (core[itr] != '\r') {
                *dst++ = core[itr];
                continue;
            }
            
            /*
             * Is the next character LF? If so convert CR to LF otherwise
             * just copy the byte.
             */
            if (itr + 1 < size) {
                if (core[itr + 1] == '\n')
                    *dst++ = '\n', itr++;
                else
                    *dst++ = core[itr];
            } else if (size > 1) {
                /*
                 * Peak ahead one byte to determine the line ending.
                 * This is more of a pain in the ass than it is fun.
                 */
                DWORD look = 0;
                char  peek = 0;
                
                ReadFile(file, &peek, 1, &look, 0);
                if (!look)
                    *dst++ = core[itr];
                else if(peek == '\n')
                    *dst++ = '\n';
                else {
                    /*
                     * Move backwards one on the current file to unpeek.
                     * This is the nasty part.
                     */
                    lseek(A1, -1, 1/*SEEK_CUR*/);
                    *dst++ = core[itr];
                }
            } else {
                *dst++ = core[itr];
            }
        }
        free(core);
    }
    return size;
}
__SYS_FCNTL  { /*TODO*/ return -1; }
__SYS_KILL   { /*TODO*/ return -1; }
__SYS_IOCTL  { /*TODO*/ return -1; }
__SYS_CLOSE  { /*TODO*/ return -1; }
__SYS_FUTEX  { /*TODO*/ return -1; }

__SYS_PAUSE  { return (SuspendThread(GetCurrentThread()) != -1); }

#endif
