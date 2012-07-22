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

__CCAPRICE_INTERNAL_FUNC(int, open,  (const char *, int));
__CCAPRICE_INTERNAL_FUNC(int, close, (int));


FILE *fdopen(int fd, const char *name) {
    /*
     * TODO: implement
     */
     
    return __ccaprice_stdout;
}

FILE *fopen(const char *file, const char *mode) {
    FILE *fp;
    int   fd;
    int   flags;
    
    if (!strchr("rwa", *mode))
        return 0;
        
    flags = (!!strchr(mode, '+')) ?
        O_RDWR   : (*mode=='r')   ?
        O_RDONLY :
        O_WRONLY ;
    
    if (*mode != 'r') flags |= O_CREAT;
    if (*mode == 'w') flags |= O_TRUNC;
    if (*mode == 'a') flags |= O_APPEND;
    
    if ((fd = open(file, flags|O_LARGEFILE)) < 0)
        return 0;
        
    if ((fp = fdopen(fd, mode)))
        return fp;
    
    /* made it this far close and die */
    close(fd);
    return 0;
}
