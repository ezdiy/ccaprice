/*
 * Copyright (C) 2012 
 * 	Dale Weiler
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
2:	not %edi
	sub $0x20,%rsp
	fnstenv (%rsp)
	and %edi,4(%rsp)
	or %esi,4(%rsp)
	fldenv (%rsp)
	stmxcsr (%rsp)
	and %edi,(%rsp)
	ldmxcsr (%rsp)
	add $0x20,%rsp
	ret
/*
 * The following <fenv.h> functions here:
 *
 *	feclearexcept
 *	feraiseexcept
 *	fetextexcept
 *
 *	fesetround
 *	fegetround
 *
 *	fegetenv
 *	fesetenv
 */
FENV(clearexcept)	
	xor %eax,%eax
	xor %esi,%esi
	test %edi,%edi
	jnz 2b
	ret
FENV(raiseexcept)
	xor %eax,%eax
	mov %edi,%esi
	xor %edi,%edi
	test %esi,%esi
	jnz 2b
	ret
FENV(testexcept)
	push %rax
	stmxcsr (%rsp)
	pop %rsi
	fnstsw %ax
	or %esi,%eax
	and %edi,%eax
	ret
FENV(setround)
	xor %eax,%eax
	sub $0x20,%rsp
	fnstenv (%rsp)
	andb $0xf3,1(%rsp)
	or %edi,(%rsp)
	fldenv (%rsp)
	stmxcsr (%rsp)
	shl $0x3,%edi
	andb $0x9f,1(%rsp)
	or %edi,(%rsp)
	ldmxcsr (%rsp)
	add $0x20,%rsp
	ret
FENV(getround)
	push %rax
	stmxcsr (%rsp)
	pop %rax
	shr $0x3,%eax
	and $0xc,%ah
	ret
FENV(getenv)
	xor %eax,%eax
	fnstenv (%rdi)
	stmxcsr 28(%rdi)
	ret
FENV(setenv)
	xor %eax,%eax
	inc %rdi
	jz 1f
	fldenv -1(%rdi)
	ldmxcsr 27(%rdi)
	ret
1:	push %rax
	push %rax
	push %rax
	pushq $0x37f
	fldenv (%rsp)
	pushq $0x1f80
	ldmxcsr (%rsp)
	add $0x28,%rsp
	ret
	
.size feclearexcept, .-feclearexcept
.size feraiseexcept, .-feraiseexcept
.size fetestexcept,  .-fetestexcept
.size fegetround,    .-fegetround
.size fesetround,    .-fesetround
.size fesetenv,      .-fesetenv
.size fegetenv,      .-fegetenv
#undef FENV