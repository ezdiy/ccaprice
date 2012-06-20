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
 * Pathscale doesn't like .type.  Despite it being valid GAS syntax
 * and the idea that it should work since pathscale is a GCC fork.
 */
#ifndef __PATHCC__
    .type feclearexcept,@function
    .type feraiseexcept,@function
    .type fetestexcept, @function
    .type fegetround,   @function
    .type fesetround,   @function
    .type fesetenv,     @function
    .type fegetenv,     @function
#endif
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
    mov    4(%esp),    %ecx
    not    %ecx
    test    $0x3F,        %ecx
    jnz    2f

1:    fnclex
    xor    %eax,        %eax
    ret
2:    fnstsw    %ax                // not eax
    and    %ecx,        %eax    // magic
    jz    1b
    sub    $0x20,        %esp
    fnstenv (%esp)
    mov    %al,        4(%esp)
    fldenv    (%esp)
    add    $0x20,        %esp
    xor    %eax,        %eax    // zero
    ret

FENV(raiseexcept)
    mov    4(%esp),    %eax
    sub    $0x20,        %esp
    fnstenv    (%esp)
    or    %al,        4(%esp)
    fldenv    (%esp)
    add    $0x20,        %esp
    xor    %eax,        %eax    // zero
    ret

FENV(testexcept)
    mov    4(%esp),    %ecx
    fnstsw    %ax
    and    %ecx,        %eax
    ret

FENV(setround)
    mov    4(%esp),    %ecx
    push    %eax
    xor    %eax,        %eax    // zero
    fnstcw    (%esp)
    andb    $0xF3,        1(%esp)    // only one byte (the %ch seems hacky)
    or    %ch,        1(%esp)    // sorry :3
    fldcw    (%esp)
    pop    %ecx            // safe
    ret

FENV(getround)
    push    %eax
    fnstcw    (%esp)            // store control word
    pop    %eax
    and    $0xC00,        %eax    // toward zero ~0xC00
    ret

FENV(getenv)
    mov    4(%esp),    %ecx
    xor    %eax,        %eax
    fnstenv    (%ecx)
    ret

FENV(setenv)
    mov    4(%esp),    %ecx
    xor    %eax,        %eax
    test    %ecx,        %ecx
    jz    1f
    fldenv    (%ecx)
    ret

1:    push    %eax             // 6
    push    %eax             // 5
    push    %eax             // 4
    push    %eax             // 3
    push    %eax             // 2
    push    %eax             // 1

    pushl    $0x37F
    fldenv    (%esp)
    add    $0x1C,        %esp
    ret

.size feclearexcept, .-feclearexcept
.size feraiseexcept, .-feraiseexcept
.size fetestexcept,  .-fetestexcept
.size fegetround,    .-fegetround
.size fesetround,    .-fesetround
.size fesetenv,      .-fesetenv
.size fegetenv,      .-fegetenv
#undef FENV
