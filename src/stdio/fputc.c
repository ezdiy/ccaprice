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

static int __ccaprice_ftowrite(FILE *f) {
    f->mode |= f->mode-1;
    
    if (f->flags  & __CCAPRICE_F_NOWR) {
        f->flags |= __CCAPRICE_F_ERR;
        return EOF;
    }
    
    /* clear the read buffer */
    f->rpos = 0;
    f->rend = 0;
    
    /* setup the writer */
    f->wpos = f->buf;
    f->base = f->buf;
    f->wend = f->buf + f->buf_size;
    
    return 0;
}

static int __ccaprice_foverflow(FILE *f, int c) {
    unsigned char d = c;
    
    if (!f->wend && __ccaprice_ftowrite(f))
        return EOF;
    
    if (f->wpos < f->wend && d != f->lbf)
        return *f->wpos++ = d;
        
    if (f->write(f, &d, 1) != 1)
        return EOF;
        
    return d;
    
}

int fputc(int c, FILE *f) {
    /*
     * TODO: locking for thread safety
     */
    return (
        (c != f->lbf && f->wpos < f->wend) ?
             *f->wpos++ = c :
        __ccaprice_foverflow(f,c)
    );
}
