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
.globl LABEL(longjmp)
.globl LABEL(setjmp)

LABEL(longjmp):
    mov    4(%esp),    %edx
    mov    8(%esp),    %eax
    test    %eax,    %eax
    jnz    1f
    inc    %eax

// 4 byte move (32 bit)
1:
    mov      (%edx),    %ebx
    mov  4(%edx),    %esi
    mov  8(%edx),    %edi
    mov    12(%edx),    %ebp
    mov 16(%edx),    %ecx
    mov    %ecx,    %esp
    mov    20(%edx),    %ecx
    jmp *%ecx
    
LABEL(setjmp):
    mov    4(%esp),    %eax
    mov    %ebx,    (%eax)
    mov    %esi,    4(%eax)
    mov    %edi,    8(%eax)
    mov    %ebp,    12(%eax)
    lea    4(%esp),    %ecx
    mov    %ecx,    16(%eax)
    mov    (%esp),    %ecx
    mov    %ecx,    20(%eax)
    xor    %eax,    %eax
    ret
    
