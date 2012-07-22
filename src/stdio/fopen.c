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
#include <string.h>
#include <bits/fcntl.h>

/* runtime.h */
__CCAPRICE_INTERNAL_FUNC(int, open,  (const char *, int));
__CCAPRICE_INTERNAL_FUNC(int, close, (int));
__CCAPRICE_INTERNAL_FUNC(int, fcntl, (int, int, int));
/* stdlib.h */
__CCAPRICE_INTERNAL_FUNC(void*, malloc, (size_t));
/* impl/ */
__CCAPRICE_INTERNAL_FUNC(size_t, __ccaprice_stdio_read , (FILE *, unsigned char *, size_t));
__CCAPRICE_INTERNAL_FUNC(size_t, __ccaprice_stdio_write, (FILE *, const unsigned char *, size_t));
__CCAPRICE_INTERNAL_FUNC(off_t,  __ccaprice_stdio_seek,  (FILE *, off_t, int));
__CCAPRICE_INTERNAL_FUNC(int,    __ccaprice_stdio_close, (FILE *));


static FILE *__ccaprice_fdopen(int fd, const char *mode) {
    FILE *fp;
    
    if (!strchr("rwa", *mode))
        return 0;
        
    if (!(fp = malloc(sizeof(FILE) + __CCAPRICE_UNGET + __CCAPRICE_BUFSIZE)))
        return 0;
        
    memset(fp, 0, sizeof(FILE));
    
    if (!!strchr(mode, '+'))
        fp->flags = (*mode == 'r') ? __CCAPRICE_F_NOWR :__CCAPRICE_F_NORD;
        
    if (*mode == 'a') {
        fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) | O_APPEND);
    }
    
    fp->fd       = fd;
    fp->buf      = (unsigned char*)fp + sizeof(FILE) + __CCAPRICE_UNGET;
    fp->buf_size = __CCAPRICE_BUFSIZE;
    fp->lbf      = EOF;
    
    
    //if (!(fp->flags & __CCAPRICE_F_NOWR) /* TODO: check TCGETS for '\n' */)
    //    fp->lbf = '\n';
    
    fp->read    = &__ccaprice_stdio_read;
    fp->write   = &__ccaprice_stdio_write;
    fp->seek    = &__ccaprice_stdio_seek;
    fp->close   = &__ccaprice_stdio_close;
    
    if (!__CCAPRICE_INSTANCE.threaded)
        fp->lock = -1;
        
    __CCAPRICE_OFDOLOCK();
        fp->next = __CCAPRICE_INSTANCE.file_head;
        if (__CCAPRICE_INSTANCE.file_head)
            ((FILE*)__CCAPRICE_INSTANCE.file_head)->prev = fp;
        __CCAPRICE_INSTANCE.file_head = (void*)fp;
    __CCAPRICE_OFUNLOCK();
    
    return fp;
}

FILE *fopen(const char *file, const char *mode) {
    FILE *fp;
    int   fd;
    int   flags;
    
    if (!strchr("rwa", *mode))
        return 0;
        
    flags = (!!strchr(mode, '+')) ?
        O_RDWR   :  (*mode=='r')  ?
        O_RDONLY :
        O_WRONLY ;
    
    if (*mode != 'r') flags |= O_CREAT;
    if (*mode == 'w') flags |= O_TRUNC;
    if (*mode == 'a') flags |= O_APPEND;
    
    if ((fd = open(file, flags|O_LARGEFILE)) < 0)
        return 0;
        
    if ((fp = __ccaprice_fdopen(fd, mode)))
        return fp;
    
    /* made it this far close and die */
    close(fd);
    return 0;
}
