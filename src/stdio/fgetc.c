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

static int __ccaprice_uflow(FILE *fp) {
	unsigned char c;
	if ((fp->rend || !__ccaprice_toread(fp)) && fp->read(fp, &c, 1) == 1)
		return c;
		
	return EOF;
}

static int __ccaprice_fgetc(FILE *fp) {
	return ((fp->rpos < fp->rend) ? *fp->rpos++ : __ccaprice_uflow(fp));
}

int fgetc(FILE *fp) {
	int c;
	if (fp->lock < 0 || !__ccaprice_file_dolock(fp))
		return __ccaprice_fgetc(fp);
	c = __ccaprice_fgetc(fp);
	__ccaprice_file_unlock(fp);
	return c;
}
