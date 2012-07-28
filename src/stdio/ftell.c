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
#include <limits.h>
static off_t __ccaprice_ftellu(FILE *fp) {
	off_t pos = fp->seek(fp, 0, SEEK_CUR);
	if (pos < 0)
		return pos;

	return pos - (fp->rend - fp->rpos) + (fp->wpos - fp->base);
}

static off_t __ccaprice_ftell(FILE *fp) {
	off_t pos;
	__CCAPRICE_FDOLOCK(fp);
	pos = __ccaprice_ftellu(fp);
	__CCAPRICE_FUNLOCK(fp);
	return pos;
}

long ftell(FILE *fp) {
	off_t pos = __ccaprice_ftell(fp);
	if (pos > LONG_MAX)
		return -1;
		
	return pos;
}
