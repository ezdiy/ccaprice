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
#include <bits/syscall.h>

struct iovec {
    void  *base;
    size_t size;
};

__CCAPRICE_INTERNAL_FUNC(int, write, (int, const void*, size_t));

size_t __ccaprice_stdio_write(FILE *fp, const unsigned char *buf, size_t len) {
    struct iovec iovs[] = {
        { .base = fp->base,   .size = fp->wpos - fp->base, },
        { .base = (void*)buf, .size = len                  }
    };
    struct iovec *iov = iovs;
    
    size_t  rem = iov[0].size + iov[1].size;
    int     icn = 2;
    ssize_t cnt;
    
    for (;;) {
        cnt = (ssize_t)__ccaprice_syscall_args_3(SYS_writev, fp->fd, (long int)iov, icn);
        if (cnt == rem) {
            fp->wend = fp->buf + fp->buf_size;
            fp->wpos = fp->buf;
            fp->base = fp->buf;
        
            return len;
        }
        
        if (cnt < 0) {
            fp->wpos   = 0;
            fp->base   = 0;
            fp->wend   = 0;
            fp->flags |= __CCAPRICE_F_ERR;
            
            return (icn == 2) ? 0 : len - iov[0].size;
        }
        
        rem -= cnt;
        
        if (cnt > iov[0].size) {
            fp->wpos = fp->buf;
            fp->base = fp->buf;
            
            iov++;
            icn--;
        }
        
        if (icn == 2) {
            fp->base += cnt;
        }
        
        iov[0].base  = (char*)iov[0].base + cnt;
        iov[0].size -= cnt;
    }
    
    return 0;
}
