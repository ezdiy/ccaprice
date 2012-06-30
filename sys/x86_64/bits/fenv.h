/*
 * Copyright (C) 2012
 *  Dale Weiler
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
#ifndef __CCAPRICE_SYS_FENV_HDR
#define __CCAPRICE_SYS_FENV_HDR

# define FE_INVALID    1
# define FE_DIVBYZERO  4
# define FE_OVERFLOW   8
# define FE_UNDERFLOW  16
# define FE_INEXACT    32

# define FE_ALL_EXCEPT 63

# define FE_TONEAREST  0
# define FE_DOWNWARD   0x400
# define FE_UPWARD     0x800
# define FE_TOWARDZERO 0xC00

# define FE_DFL_ENV    ((const fenv_t*)-1)

typedef unsigned short fexcept_t;
typedef struct {
    fexcept_t __cntrlword;
    fexcept_t __dummy0000;
    fexcept_t __statuword;
    fexcept_t __dummy1111;
    fexcept_t __tagsndata;
    fexcept_t __dummy2222;

    unsigned int  __eip;
    fexcept_t     __cs_sel;
    unsigned int  __opcode:11;
    unsigned int  __dummy3333:5;
    unsigned int  __datoffset;
    fexcept_t     __datselect;
    fexcept_t     __dummy4444;
    unsigned int  __mxcsr;
} fenv_t;

#endif
