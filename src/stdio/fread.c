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

__CCAPRICE_INTERNAL_FUNC(void *, memcpy, (void*, const void*, size_t));

static int __ccaprice_toread(FILE *fp) {
	fp->mode |= fp->mode - 1;

	if (fp->wpos > fp->buf)
		fp->write(fp, 0, 0);

	fp->wpos = 0;
	fp->base = 0;
	fp->wend = 0;

	if (fp->flags & (__CCAPRICE_F_EOF | __CCAPRICE_F_NORD)) {
		if (fp->flags & __CCAPRICE_F_NORD)
			fp->flags |= __CCAPRICE_F_ERR;

		return EOF;
	}
	fp->rpos = fp->buf;
	fp->rend = fp->buf;

	return 0;
}

size_t fread(void *dest, size_t size, size_t num, FILE *fp) {
    unsigned char *dst = dest;
    size_t         len = size*num;
    size_t         l   = len;
    size_t         k;

    if (!l) return 0;

    __CCAPRICE_FDOLOCK(fp);

    if (fp->rend - fp->rpos > 0) {
        memcpy(dst, fp->rpos, (k = fp->rend - fp->rpos < l ? fp->rend - fp->rpos : l));

        fp->rpos +=k;
        dst      +=k;
        l        -=k;
    }

    for (; l; l-=k, dst +=k) {
        if ((k = __ccaprice_toread(fp) ? 0 : fp->read(fp, dst, l)) + 1 <= 1) {
            __CCAPRICE_FUNLOCK(fp);
            return (len - l) / size;
        }
    }

    __CCAPRICE_FUNLOCK(fp);
    return num;
}
