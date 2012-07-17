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
.global ceil
.global ceilf
.global ceill
/*
 * Pathscale doesn't like .type.  Despite it being valid GAS syntax
 * and the idea that it should work since pathscale is a GCC fork.
 */
#ifndef __PATHCC__
    .type ceil,   @function
    .type ceilf,  @function
    .type ceill,  @function

#endif

/*
 * This is terrible looking I suppose there should be
 * a nicer way at doing this without all the mov.
 */
1:  fstcw 4(%esp)      // control word store
    mov   5(%esp), %ah
    mov   %al, 5(%esp)
    fldcw 4(%esp)      // load modified control
    frndint            // round
    mov   %ah, 5(%esp)
    fldcw 4(%esp)      // restore original
    ret

#define CEIL(X)      \
    X 4(%esp);       \
    mov $0xB, %al;   \
    jmp 1b
    
ceil:   CEIL(fldl)
ceilf:  CEIL(flds)
ceill:  CEIL(fldt)
    
#undef CEIL