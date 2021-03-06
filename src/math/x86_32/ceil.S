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
.global LABEL(ceil)
.global LABEL(ceilf)
.global LABEL(ceill)
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
    
LABEL(ceil):   CEIL(fldl)
LABEL(ceilf):  CEIL(flds)
LABEL(ceill):  CEIL(fldt)
    
#undef CEIL
