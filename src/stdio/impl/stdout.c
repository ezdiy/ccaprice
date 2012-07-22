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
#include <stdio.h>
 
static unsigned char __ccaprice_stdout_buf[__CCAPRICE_BUFSIZE + __CCAPRICE_UNGET];
static FILE __ccaprice_stdout_impl = {
    .buf      = __ccaprice_stdout_buf+__CCAPRICE_UNGET,
    .buf_size = sizeof(__ccaprice_stdout_buf-__CCAPRICE_UNGET),
    .fd       = 1,
    .flags    = __CCAPRICE_F_PERM | __CCAPRICE_F_NORD,
    .lbf      = '\n',
};

FILE *const __ccaprice_stdout = &__ccaprice_stdout_impl;
