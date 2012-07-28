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

static int __ccaprice_fseek(FILE *fp, off_t off, int whence) {
    if (whence == SEEK_CUR)
        off -= fp->rend - fp->rpos;
        
    if (fp->wpos > fp->base) {
        fp->write(fp, 0, 0);
        if (!fp->wpos)
            return -1;
    }
    
    fp->wpos   = 0;
    fp->base   = 0;
    fp->wend   = 0;
    
    if (fp->seek(fp, off, whence) < 0)
        return -1;
        
    fp->rpos   = 0;
    fp->rend   = 0;
    fp->flags &= ~__CCAPRICE_F_EOF;
    
    return 0;
}

int fseek(FILE *fp, long off, int whence) {
    int r;
    __CCAPRICE_FDOLOCK(fp);
    r = __ccaprice_fseek(fp, off, whence);
    __CCAPRICE_FUNLOCK(fp);
    return r;
}
