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
.global LABEL(atan)
.global LABEL(atanf)
.global LABEL(atanl)
.global LABEL(atan2)
.global LABEL(atan2f)
.global LABEL(atan2l)
/*
 * This could be put inside a stub and jmp * to it
 * but exact instructions are likely faster than an
 * additional jmp (expecially for math)
 */
#define RETURN       \
    fpatan;          \
    ret
#define ATAN(X)      \
    X 4(%esp);       \
    fld1;            \
    RETURN
#define ATAN2(X,Y,Z) \
    X Y (%esp);      \
    X Z (%esp);      \
    RETURN  
    
LABEL(atan):   ATAN (fldl)
LABEL(atanf):  ATAN (flds)
LABEL(atanl):  ATAN (fldt)
LABEL(atan2):  ATAN2(fldl, 4, 12)
LABEL(atan2f): ATAN2(flds, 4,  8)
LABEL(atan2l): ATAN2(fldt, 4, 16)
    
#undef RETURN
#undef ATAN
#undef ATAN2
