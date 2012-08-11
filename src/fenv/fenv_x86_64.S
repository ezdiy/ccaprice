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
.global feclearexcept
.global feraiseexcept
.global fetestexcept
.global fegetround
.global fesetround
.global fesetenv
.global fegetenv
/*
 * FENV stub macro incase additional underscores need to be added later
 * for another assembler or linker who can't resolve symbols.
 */
#define FENV(X) fe##X:
/*
 * The following <fenv.h> functions here:
 *
 *    feclearexcept
 *    feraiseexcept
 *    fetextexcept
 *
 *    fesetround
 *    fegetround
 *
 *    fegetenv
 *    fesetenv
 */
FENV(clearexcept)
    mov    %edi,        %ecx
    not    %ecx
    stmxcsr    -8(%esp)
    and    %ecx,        -8(%rsp)
    ldmxcsr    -8(%esp)
    test    $0x3F,        %ecx
    jnz    2f

1:    fnclex
    xor    %eax,        %eax
    ret

2:    fnstsw    %ax
    and    %ecx,        %eax
    jz    1b
    sub    $0x20,        %rsp
    fnstenv    (%rsp)
    mov    %al,        4(%esp)
    fldenv    (%rsp)
    add    $0x20,        %rsp
    xor    %eax,        %eax    // zero
    ret

FENV(raiseexcept)
    stmxcsr    -8(%rsp)
    or    %edi,        -8(%rsp)
    ldmxcsr    -8 (%rsp)
    fnstenv    -32(%rsp)
    or    %edi,        -28(%rsp)
    fldenv    -32(%rsp)
    xor    %eax,        %eax
    ret

FENV(testexcept)
    push    %rax
    stmxcsr (%rsp)
    pop    %rsi
    fnstsw    %ax
    or    %esi,        %eax
    and    %edi,        %eax
    ret

FENV(setround)
    push    %rax
    xor    %eax,        %eax    // zero
    mov    %edi,        %ecx
    fnstcw    (%rsp)
    andb    $0xF3,        1(%rsp) // 1 byte (ugly %ch same as i386)
    or    %ch,        1(%rsp)
    fldcw    (%rsp)
    stmxcsr    (%rsp)
    shl    $0x03,        %ch    // this is faster than the i386 way
    andb    $0x9F,        1(%rsp) // single byte
    or    %ch,        1(%rsp)    // 1 byte (ugly %ch same as i386)
    ldmxcsr    (%rsp)            // ... about time
    pop    %rcx
    ret

FENV(getround)
    push    %rax
    stmxcsr    (%rsp)
    pop    %rax
    shr    $0x3,        %eax
    and    $0xC00,        %eax     // 0xC, %ah could work too (this is faster)
    ret

FENV(getenv)
    xor    %eax,        %eax     // zero
    fnstenv    (%rdi)
    stmxcsr    28(%rdi)
    ret

FENV(setenv)
    xor    %eax,        %eax
    inc    %rdi
    jz 1f
    fldenv    -1(%rdi)
    ldmxcsr    27(%rdi)
    ret

1:    push    %rax             // 5-6
    push    %rax             // 3-4
    push    %rax             // 1-2
    pushq    $0x37F
    fldenv    (%rsp)
    pushq    $0x1F80
    ldmxcsr    (%rsp)
    add    $0x28,        %rsp
    ret
#undef FENV
