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
#ifndef __CCAPRICE_WINDOWS_HDR
#define __CCAPRICE_WINDOWS_HDR

#define WINAPI __stdcall
#define CONST  const

#define LOWORD(l) ((WORD)(((unsigned long)(l)) & 0xffff))
/*
 * The following documentation was used to implement these structures
 *  ImageHlp Structures            -- http://msdn.microsoft.com/en-us/library/windows/desktop/ms680198%28v=vs.85%29.aspx
 *  IMAGE_EXPORT_DIRECTORY         -- http://www.csie.ntu.edu.tw/~r92094/win32asm/PE/IMAGE_EXPORT_DIRECTORY
 *  IMAGE_DOS_HEADER               -- http://www.nirsoft.net/kernel_struct/vista/IMAGE_DOS_HEADER.html
 *  PEB                            -- http://msdn.microsoft.com/en-us/library/windows/desktop/aa813706%28v=vs.85%29.aspx
 *  PEB_LDR_DATA                   -- http://msdn.microsoft.com/en-us/library/windows/desktop/aa813708%28v=vs.85%29.aspx
 *  RTL_USER_PROCESS_PARAMETERS    -- http://msdn.microsoft.com/en-us/library/windows/desktop/aa813741%28v=vs.85%29.aspx
 *  UNICODE_STRING                 -- http://msdn.microsoft.com/en-us/library/windows/desktop/aa380518%28v=vs.85%29.aspx
 *  Windows Data Types             -- http://msdn.microsoft.com/en-us/library/windows/desktop/aa383751%28v=vs.85%29.aspx
 *  Windows Data Types for Strings -- http://msdn.microsoft.com/en-us/library/windows/desktop/dd374131%28v=vs.85%29.aspx
 */
 
/*
 * TODO: more WIN64 stuff for future porting.
 * We implement some WIN64 ifdef configurations
 * for types (for a future port)
 */
#if defined(_WIN64)
    /*
     * GCC implements the MSVC __int types as keywords! Not as library
     * typedefs.
     */
    typedef __int64 LONG_PTR;
#else
    typedef long    LONG_PTR;
#endif

typedef unsigned short WCHAR;
typedef unsigned char  BYTE;
typedef unsigned short WORD;
typedef unsigned char  CHAR;
typedef unsigned long  DWORD;
typedef void          *PVOID;
typedef void          *HANDLE;
typedef void          *HFILE;
typedef unsigned long  ULONG;
typedef WCHAR         *PWSTR;
typedef long           LONG;
typedef LONG          *PLONG;
typedef int            BOOL;
typedef DWORD         *LPDWORD;
typedef CONST void    *LPCVOID;
typedef void          *LPVOID;
typedef unsigned long  ULONG_PTR;
typedef unsigned int   UINT;
typedef void           VOID;
typedef CHAR          *LPSTR;
typedef WCHAR         *LPWSTR;
typedef size_t         SIZE_T;
typedef const CHAR    *LPCSTR;
typedef void          *HMODULE;

#ifdef UNICODE
    typedef LPWSTR LPTSTR;
    typedef WCHAR  TCHAR;
#else
    typedef LPSTR  LPTSTR;
    typedef CHAR   TCHAR;
#endif

typedef TCHAR     *LPTCH;

#define __STRUCT_TYPEDEF(X) X, *P##X

typedef struct {
    WORD                  Length;
    WORD                  MaximumLength;
    PWSTR                 Buffer;
} __STRUCT_TYPEDEF(LSA_UNICODE_STRING),
  __STRUCT_TYPEDEF(UNICODE_STRING);

/* only implement what we need */
typedef struct {
    WORD                  Machine;
    WORD                  NumberOfSections;
    DWORD                 TimeDateStamp;
    DWORD                 PointerToSymbolTable;
    DWORD                 NumberOfSymbols;
    WORD                  SizeOfOptionalHeader;
    WORD                  Characteristics;
} __STRUCT_TYPEDEF(IMAGE_FILE_HEADER);

typedef struct {
    DWORD                 VirtualAddress;
    DWORD                 Size;
} __STRUCT_TYPEDEF(IMAGE_DATA_DIRECTORY);

typedef struct {
    WORD                  Magic;
    BYTE                  MajorLinkerVersion;
    BYTE                  MinorLinkerVersion;
    DWORD                 SizeOfCode;
    DWORD                 SizeOfInitializedData;
    DWORD                 SizeOfUninitializedData;
    DWORD                 AddressOfEntryPoint;
    DWORD                 BaseOfCode;
    DWORD                 BaseOfData;
    DWORD                 ImageBase;
    DWORD                 SectionAlignment;
    DWORD                 FileAlignment;
    WORD                  MajorOperatingSystemVersion;
    WORD                  MinorOperatingSystemVersion;
    WORD                  MajorImageVersion;
    WORD                  MinorImageVersion;
    WORD                  MajorSubsystemVersion;
    WORD                  MinorSubsystemVersion;
    DWORD                 Win32VersionValue;
    DWORD                 SizeOfImage;
    DWORD                 SizeOfHeaders;
    DWORD                 CheckSum;
    WORD                  Subsystem;
    WORD                  DllCharacteristics;
    DWORD                 SizeOfStackReserve;
    DWORD                 SizeOfStackCommit;
    DWORD                 SizeOfHeapReserve;
    DWORD                 SizeOfHeapCommit;
    DWORD                 LoaderFlags;
    DWORD                 NumberOfRvaAndSizes;
    IMAGE_DATA_DIRECTORY  DataDirectory[16];
} __STRUCT_TYPEDEF(IMAGE_OPTIONAL_HEADER);

typedef struct {
    DWORD                 Signature;
    IMAGE_FILE_HEADER     FileHeader;
    IMAGE_OPTIONAL_HEADER OptionalHeader;
} __STRUCT_TYPEDEF(IMAGE_NT_HEADERS);

typedef struct {
    DWORD                 Characteristics;
    DWORD                 TimeDateStamp;
    WORD                  MajorVersion;
    WORD                  MinorVersion;
    DWORD                 Name;
    DWORD                 Base;
    DWORD                 NumberOfFunctions;
    DWORD                 NumberOfNames;
    DWORD                 AddressOfFunctions;    // RVA
    DWORD                 AddressOfNames;        // RVA
    DWORD                 AddressOfNameOrdinals; // RVA
} __STRUCT_TYPEDEF(IMAGE_EXPORT_DIRECTORY);

typedef struct _LIST_ENTRY {
    struct _LIST_ENTRY *Flink;
    struct _LIST_ENTRY *Blink;
}__STRUCT_TYPEDEF(LIST_ENTRY);
    
typedef struct {
    BYTE                           Reserved1[16];
    PVOID                          Reserved2[10];
    UNICODE_STRING                 ImagePathName;
    UNICODE_STRING                 CommandLine;
} __STRUCT_TYPEDEF(RTL_USER_PROCESS_PARAMETERS);

typedef struct {
    BYTE                           Reserved1[8];
    PVOID                          Reserved2[3];
    LIST_ENTRY                     InMemoryOrderModuleList;
} __STRUCT_TYPEDEF(PEB_LDR_DATA);

typedef struct {
    WORD                           e_magic;
    WORD                           e_cblp;
    WORD                           e_cp;
    WORD                           e_crlc;
    WORD                           e_cparhdr;
    WORD                           e_minalloc;
    WORD                           e_maxalloc;
    WORD                           e_ss;
    WORD                           e_sp;
    WORD                           e_csum;
    WORD                           e_ip;
    WORD                           e_cs;
    WORD                           e_lfarlc;
    WORD                           e_ovno;
    WORD                           e_res[4];
    WORD                           e_oemid;
    WORD                           e_oeminfo;
    WORD                           e_res2[10];
    LONG                           e_lfanew;                    
} __STRUCT_TYPEDEF(IMAGE_DOS_HEADER);

typedef struct {
    DWORD  nLength;
    LPVOID lpSecurityDescriptor;
    BOOL   bInheritHandle;
} __STRUCT_TYPEDEF(SECURITY_ATTRIBUTES), *LPSECURITY_ATTRIBUTES;

/* 
 * OVERLAPPED:
 * http://msdn.microsoft.com/en-us/library/windows/desktop/ms684342%28v=vs.85%29.aspx
 */
typedef struct {
    ULONG_PTR             Internal;
    ULONG_PTR             InternalHigh;
    union {
        struct {
            DWORD         Offset;
            DWORD         OffsetHigh;
        };
        PVOID             Pointer;
    };
    HANDLE                hEvent;
} OVERLAPPED, *LPOVERLAPPED;

/*
 * Some various macro constants that should evaluate to constant expressions
 * according to the microsoft documentation.
 */
#define INVALID_HANDLE_VALUE ((HANDLE)(LONG_PTR)-1)

/* 
 * SetFilePointer:
 * http://msdn.microsoft.com/en-us/library/windows/desktop/aa365541%28v=vs.85%29.aspx
 */
#define FILE_BEGIN    0
#define FILE_CURRENT  1
#define FILE_END      2
typedef DWORD (WINAPI *PFNKERNEL32_SETFILEPOINTER_PROC)(HANDLE, LONG, PLONG, DWORD);

/*
 * WriteFile:
 * http://msdn.microsoft.com/en-us/library/windows/desktop/aa365747%28v=vs.85%29.aspx
 */
typedef BOOL (WINAPI *PFNKERNEL32_WRITEFILE_PROC)(HANDLE, LPCVOID, DWORD, LPDWORD, LPOVERLAPPED);

/*
 * GetStdHandle:
 * http://msdn.microsoft.com/en-us/library/windows/desktop/ms683231%28v=vs.85%29.aspx
 */
#define STD_INPUT_HANDLE  ((DWORD)-10)
#define STD_OUTPUT_HANDLE ((DWORD)-11)
#define STD_ERROR_HANDLE  ((DWORD)-12)
typedef HANDLE (WINAPI *PFNKERNEL32_GETSTDHANDLE_PROC)(DWORD);

/*
 * ExitProcess:
 * http://msdn.microsoft.com/en-us/library/windows/desktop/ms682658%28v=vs.85%29.aspx
 */
typedef VOID (WINAPI *PFNKERNEL32_EXITPROCESS_PROC)(UINT);

/*
 * GetCommandLine:
 * http://msdn.microsoft.com/en-us/library/windows/desktop/ms683156%28v=vs.85%29.aspx
 */
typedef LPSTR (WINAPI *PFNKERNEL32_GETCOMMANDLINE_PROC)(VOID);

/*
 * GetProcessHeap:
 * http://msdn.microsoft.com/en-us/library/windows/desktop/aa366569%28v=vs.85%29.aspx
 */
typedef HANDLE (WINAPI *PFNKERNEL32_GETPROCESSHEAP_PROC)(VOID);

/*
 * GetFileType:
 * http://msdn.microsoft.com/en-us/library/windows/desktop/aa364960%28v=vs.85%29.aspx
 * 
 * TODO: anything older than Windows XP this doesn't exist.
 */
#define FILE_TYPE_CHAR    0x0002
#define FILE_TYPE_DISK    0x0001
#define FILE_TYPE_PIPE    0x0003
#define FILE_TYPE_REMOTE  0x8000
#define FILE_TYPE_UNKNOWN 0x0000
typedef DWORD (WINAPI *PFNKERNEL32_GETFILETYPE_PROC)(HANDLE);

/*
 * MoveFile:
 * http://msdn.microsoft.com/en-us/library/aa365239%28v=vs.85%29.aspx
 */
typedef BOOL (WINAPI *PFNKERNEL32_MOVEFILE_PROC)(LPCSTR, LPCSTR);

/*
 * GetProcessId:
 * http://msdn.microsoft.com/en-us/library/windows/desktop/ms683215%28v=vs.85%29.aspx
 */
typedef DWORD (WINAPI *PFNKERNEL32_GETPROCESSID_PROC)(HANDLE);

/*
 * GetCurrentProcess:
 * http://msdn.microsoft.com/en-us/library/windows/desktop/ms683179%28v=vs.85%29.aspx
 */
typedef HANDLE (WINAPI *PFNKERNEL32_GETCURRENTPROCESS_PROC)(VOID);

/*
 * VirtualAlloc:
 * http://msdn.microsoft.com/en-us/library/windows/desktop/aa366887%28v=vs.85%29.aspx
 */
#define MEM_COMMIT      0x00001000
#define MEM_RESERVE     0x00002000
#define MEM_RESET       0x00080000
#define MEM_RESET_UNDO  0x10000000
#define MEM_LARGE_PAGES 0x20000000
#define MEM_PHYSICAL    0x00400000
#define MEM_TOP_DOWN    0x00100000
#define MEM_WRITE_WATCH 0x00200000
typedef LPVOID (WINAPI *PFNKERNEL32_VIRTUALALLOC_PROC)(LPVOID, SIZE_T, DWORD, DWORD);

/*
 * VirtualFree:
 * http://msdn.microsoft.com/en-us/library/windows/desktop/aa366892%28v=vs.85%29.aspx
 */
#define MEM_DECOMMIT    0x4000
#define MEM_RELEASE     0x8000
typedef BOOL (WINAPI *PFNKERNEL32_VIRTUALFREE_PROC)(LPVOID, SIZE_T, DWORD);

/*
 * DeleteFile:
 * http://msdn.microsoft.com/en-us/library/windows/desktop/aa363915%28v=vs.85%29.aspx
 */
typedef BOOL (WINAPI *PFNKERNEL32_DELETEFILE_PROC)(LPCSTR);

/*
 * HeapAlloc:
 * http://msdn.microsoft.com/en-us/library/windows/desktop/aa366597%28v=vs.85%29.aspx
 */
#define HEAP_GENERATE_EXCEPTIONS 0x00000004
#define HEAP_NO_SERIALIZE        0x00000001
#define HEAP_ZERO_MEMORY         0x00000008
typedef LPVOID (WINAPI *PFNKERNEL32_HEAPALLOC_PROC)(HANDLE, DWORD, SIZE_T);

/*
 * HeapFree:
 * http://msdn.microsoft.com/en-us/library/windows/desktop/aa366701%28v=vs.85%29.aspx
 */
typedef BOOL (WINAPI *PFNKERNEL32_HEAPFREE_PROC)(HANDLE, DWORD, LPVOID);

/*
 * GetModuleHandle:
 * http://msdn.microsoft.com/en-us/library/windows/desktop/ms683199%28v=vs.85%29.aspx
 */
typedef HMODULE (WINAPI *PFNKERNEL32_GETMODULEHANDLE_PROC)(LPCSTR);

/*
 * GetEnviromentStrings:
 * http://msdn.microsoft.com/en-us/library/windows/desktop/ms683187%28v=vs.85%29.aspx
 */
typedef LPTCH (WINAPI *PFNKERNEL32_GETENVIROMENTSTRINGS_PROC)(VOID);

/*
 * CreateFile:
 * http://msdn.microsoft.com/en-us/library/windows/desktop/aa363858%28v=vs.85%29.aspx
 */
#define FILE_SHARE_DELETE            0x00000004
#define FILE_SHARE_READ              0x00000001
#define FILE_SHARE_WRITE             0x00000002

#define CREATE_ALWAYS                2
#define CREATE_NEW                   1
#define OPEN_ALWAYS                  4
#define OPEN_EXISTING                3
#define TRUNCATE_EXISTING            5

#define FILE_ATTRIBUTE_ARCHIVE       0x0020
#define FILE_ATTRIBUTE_ENCRYPTED     0x4000
#define FILE_ATTRIBUTE_HIDDEN        0x0002
#define FILE_ATTRIBUTE_NORMAL        0x0080
#define FILE_ATTRIBUTE_OFFLINE       0x1000
#define FILE_ATTRIBUTE_READONLY      0x0001
#define FILE_ATTRIBUTE_SYSTEM        0x0004
#define FILE_ATTRIBUTE_TEMPORARY     0x0100

#define FILE_FLAG_BACKUP_SEMANTICS   0x02000000
#define FILE_FLAG_DELETE_ON_CLOSE    0x04000000
#define FILE_FLAG_NO_BUFFERING       0x20000000
#define FILE_FLAG_OPEN_NO_RECALL     0x00100000
#define FILE_FLAG_OPEN_REPARSE_POINT 0x00200000
#define FILE_FLAG_OVERLAPPED         0x40000000
#define FILE_FLAG_POSIX_SEMANTICS    0x01000000
#define FILE_FLAG_RANDOM_ACCESS      0x10000000
#define FILE_FLAG_SECCION_AWARE      0x00800000
#define FILE_FLAG_SEQUENTIAL_SCAN    0x08000000
#define FILE_FLAG_WRITE_THROUGH      0x80000000

typedef HANDLE (WINAPI *PFNKERNEL32_CREATEFILE_PROC)(LPCSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);

/*
 * Memory Protection Constants:
 * http://msdn.microsoft.com/en-us/library/windows/desktop/aa366786%28v=vs.85%29.aspx
 */
#define PAGE_EXECUTE            0x10
#define PAGE_EXECUTE_READ       0x20
#define PAGE_EXECUTE_READWRITE  0x40
#define PAGE_EXECUTE_WRITECOPY  0x80
#define PAGE_NOACCESS           0x01
#define PAGE_READONLY           0x02
#define PAGE_READWRITE          0x04
#define PAGE_WRITECOPY          0x08
#define PAGE_GUARD              0x100
#define PAGE_NOCACHE            0x200
#define PAGE_WRITECOMBINE       0x400

/*
 * Generic Rights:
 * http://msdn.microsoft.com/en-us/library/windows/desktop/aa363874%28v=vs.85%29.aspx
 */
#define GENERIC_READ            0x80000000
#define GENERIC_WRITE           0x40000000
#define GENERIC_EXECUTE         0x20000000
#define GENERIC_ALL             0x10000000

/*
 * SuspendThread:
 * http://msdn.microsoft.com/en-us/library/windows/desktop/ms686345%28v=vs.85%29.aspx
 */
typedef DWORD (WINAPI *PFNKERNEL32_SUSPENDTHREAD_PROC)(HANDLE);

/*
 * GetCurrentThread:
 * http://msdn.microsoft.com/en-us/library/windows/desktop/ms683182%28v=vs.85%29.aspx
 */
typedef HANDLE (WINAPI *PFNKERNEL32_GETCURRENTTHREAD_PROC)(VOID);

#undef __STRUCT_TYPEDEF
#endif
