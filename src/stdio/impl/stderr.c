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
__CCAPRICE_INTERNAL_FUNC(size_t, __ccaprice_stdio_write, (FILE *, const unsigned char *, size_t));
__CCAPRICE_INTERNAL_FUNC(off_t,  __ccaprice_stdio_seek,  (FILE *, off_t, int));
__CCAPRICE_INTERNAL_FUNC(int,    __ccaprice_stdio_close, (FILE *));

static unsigned char __ccaprice_stderr_buf[__CCAPRICE_UNGET];
static FILE __ccaprice_stderr_impl = {
    .buf      = __ccaprice_stderr_buf+__CCAPRICE_UNGET,
    .buf_size = 0,
    .fd       = 2,
    .flags    = __CCAPRICE_F_PERM | __CCAPRICE_F_NORD,
    .lbf      = -1,
    .write    = &__ccaprice_stdio_write,
    .seek     = &__ccaprice_stdio_seek,
    .close    = &__ccaprice_stdio_close,
    .lock     = -1,
};

FILE *const __ccaprice_stderr = &__ccaprice_stderr_impl;
