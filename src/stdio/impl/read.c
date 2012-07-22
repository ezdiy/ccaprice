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
__CCAPRICE_INTERNAL_FUNC(int, read, (int, void *, size_t));
size_t __ccaprice_stdio_read(FILE *fp, unsigned char *buf, size_t len) {
    ssize_t cnt = 0;
    
    /*
     * TODO: future prospect support SYS_readv.
     * Why? It's one less syscall to the OS.
     */
    cnt = read(fp->fd, buf,len-!!fp->buf_size) +
          read(fp->fd, fp->buf,  fp->buf_size);
    
    /*
     * TODO main thread cleanup
     * if (__CCAPRICE_INSTANCE.mainthread) {
     *     thread_push(
     *         [](void *p) { 
     *             if (((FILE*)p)->lockcount) {
     *                 __ccaprice_file_unlock((FILE*)p);
     *             }
     *         }, fp
     *     );
     * 
     *     SYSCALLS
     * 
     *     thread_pop(NULL);
     */  
    
    if (cnt <= 0) {
        fp->flags |= __CCAPRICE_F_EOF ^ ((__CCAPRICE_F_ERR ^ __CCAPRICE_F_EOF) & cnt);
        fp->rpos   = 0;
        fp->rend   = 0;
        
        return cnt;
    }
    
    if (cnt < len - !!fp->buf_size)
        return cnt;
        
    cnt -= len - !!fp->buf_size;
    
    fp->rpos = fp->buf;
    fp->rend = fp->buf + cnt;
    
    if (fp->buf_size)
        buf[len-1] = *fp->rpos++;
        
    return len;
}
