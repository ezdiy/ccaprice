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
#include <stdlib.h>

__CCAPRICE_INTERNAL_FUNC(int, close, (int));
int fclose(FILE *fp) {
    int r,p;
    
    if (!(p = fp->flags & __CCAPRICE_F_PERM)) {
        __CCAPRICE_OFDOLOCK();
            if (fp->prev) fp->prev->next = fp->next;
            if (fp->next) fp->next->prev = fp->prev;
            
            if (__CCAPRICE_INSTANCE.file_head == (void*)fp)
                __CCAPRICE_INSTANCE.file_head =  (void*)fp->next;
        __CCAPRICE_OFUNLOCK();
    }
    
    r  = fflush(fp);
    r |= fp->close(fp);
    
    if (!p)
        free(fp);

    return r;
}
