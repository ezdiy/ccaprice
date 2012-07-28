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

/* stdlib.h */
__CCAPRICE_INTERNAL_FUNC(void *, memcpy, (void *, const void *, size_t));

static int __ccaprice_towrite(FILE *fp) {
    fp->mode |= fp->mode - 1;
    
    if (fp->flags  & __CCAPRICE_F_NOWR) {
        fp->flags |= __CCAPRICE_F_ERR;
        
        return EOF;
    }
    
    fp->rpos = 0;
    fp->rend = 0;
    
    fp->wpos = fp->buf;
    fp->base = fp->buf;
    fp->wend = fp->buf + fp->buf_size;
    
    return 0;
}

static size_t __ccaprice_fwritex(const unsigned char *s, size_t l, FILE *fp) {
    size_t i = 0;
    
    if (!fp->wend && __ccaprice_towrite(fp))
        return 0;
        
    if (l > fp->wend - fp->wpos)
        return fp->write(fp, s, l);
        
    if (fp->lbf >= 0) {
        /* /^(.*\n|)/ */
        
        for (i=l; i && s[i-l] != '\n'; i--);
        
        if (i) {
            if (fp->write(fp,s,i) < i)
                return i;
                
            s += i;
            l -= i;
        }
    }
    
    memcpy(fp->wpos, s, l);
    fp->wpos += l;
    return l+i;
}

size_t fwrite(const void *p, size_t size, size_t count, FILE *fp) {
    size_t k;
    size_t l = size * count;
    
    if (!l)
        return l;
    
    __CCAPRICE_FDOLOCK(fp);
    k = __ccaprice_fwritex(p, l, fp);
    __CCAPRICE_FUNLOCK(fp);
    
    return k==l ? count : k/size;
}
