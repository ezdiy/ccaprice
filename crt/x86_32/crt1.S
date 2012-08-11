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
#include <bits/asm.h>
.weak _init
.weak _fini

.text
.global _start
_start:
    xor  %ebp, %ebp
    pop  %ecx
    mov  %esp, %eax
    and  $-16, %esp
#ifndef WINDOWS
    push %esp
    push %esp
    push %edx
    push $_fini
    push $_init
    push %eax
    push %ecx
    push main
    call LABEL(__ccaprice_start)
#else
    push main
    call LABEL(__ccaprice_start)
.global __main
__main:
1:  jmp  1b
#endif

#ifdef WINDOWS
/*
 * CFI directive uses 8 for WIN64 (future support?)
 */
#define cpush(X)           .cfi_adjust_cfa_offset 4; .cfi_rel_offset X, 0
#define cpop(X)            .cfi_adjust_cfa_offset -4; .cfi_restore X
.cfi_startproc
.global ___chkstk_ms
___chkstk_ms:
    pushl %ecx
    cpush(%ecx)
    pushl %eax
    cpush(%eax)
    cmpl $0x1000,  %eax
    leal 12(%esp), %ecx
    jb   2f
1:
    subl $0x1000,  %ecx
    orl  $0x0,    (%ecx)
    subl $0x1000,  %eax
    cmpl $0x1000,  %eax
    ja   1b
2:
    subl %eax,     %ecx
    orl  $0x0,    (%ecx)
    
    popl %eax
    cpop(%eax)
    popl %ecx
    cpop(%ecx)
    ret
.cfi_endproc
#endif
