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
.global __umoddi3
.align 4

__umoddi3:
    pushl  %ebx
    movl   20(%esp),   %ebx
    bsrl   %ebx,       %ecx
    jz     9f
    movl   16(%esp),   %eax
    shrl   %cl,        %eax
    shrl   %eax
    notl   %ecx
    shll   %cl,        %ebx
    orl    %eax,       %ebx
    movl   12(%esp),   %edx
    movl   8(%esp),    %eax
    cmpl   %ebx,       %edx
    jae    2f
    divl   %ebx
    pushl  %edi
    notl   %ecx
    shrl   %eax
    shrl   %cl,        %eax
    movl   %eax,       %edi
    mull   20(%esp)
    movl   12(%esp),   %ebx
    movl   16(%esp),   %ecx
    subl   %eax,       %ebx
    sbbl   %edx,       %ecx
    movl   24(%esp),   %eax
    imull  %edi,       %eax
    subl   %eax,       %ecx
    jnc    1f
    addl   20(%esp),   %ebx
    adcl   24(%esp),   %ecx
    1:movl %ebx,       %eax
    movl   %ecx,       %edx
    popl   %edi
    popl   %ebx
    retl
2:
    subl   %ebx,       %edx
    divl   %ebx
    pushl  %edi
    notl   %ecx
    shrl   %eax
    orl    $0x80000000,%eax
    shrl   %cl,        %eax
    movl   %eax,       %edi
    mull   20(%esp)
    movl   12(%esp),   %ebx
    movl   16(%esp),   %ecx
    subl   %eax,       %ebx
    sbbl   %edx,       %ecx
    movl   24(%esp),   %eax
    imull  %edi,       %eax
    subl   %eax,       %ecx
    jnc    3f
    addl   20(%esp),   %ebx
    adcl   24(%esp),   %ecx
    3:movl %ebx,       %eax
    movl   %ecx,       %edx
    popl   %edi
    popl   %ebx
    retl
9:
    movl   12(%esp),   %eax
    movl   16(%esp),   %ecx
    xorl   %edx,       %edx
    divl   %ecx
    movl   %eax,       %ebx
    movl   8(%esp),    %eax
    divl   %ecx
    movl   %edx,       %eax
    popl   %ebx
    xorl   %edx,       %edx
    retl
