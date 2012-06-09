/*
 * Copyright (C) 2012
 * 	Dale Weiler
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
#include "inc/stdio.h"
#include "inc/posix/errno.h"

__CCAPRICE_INTERNAL_TYPE(int * , __ccaprice_posix_errno);
__CCAPRICE_INTERNAL_TYPE(size_t, __ccaprice_stdio_file_pos);
__CCAPRICE_INTERNAL_TYPE(FILE  , __ccaprice_stdio_file_dat[__CCAPRICE_STDIO_FILE_BUFFER_LEN]);
/*
 * fflush() is used to write out buffered data stuck in
 * the fp->buffer_dat.
 */
int fflush(FILE *fp) {
	/* If NULL is passed free all open files */
	//if (!fp && !fp->self) {
	//	while(--ccaprice_stdio_file_pos>0) {
	//		/* Recursive call: SELF required to ensure EBADF */
	//		ccaprice_stdio_file_dat[ccaprice_stdio_file_pos].self = 1;
	//		fflush(&ccaprice_stdio_file_dat[ccaprice_stdio_file_pos]);
	//	}
	//} else if (!fp) {
	//	errno = EBADF;
	//	return EOF;
	//}

	fwrite(fp->buffer_dat, fp->buffer_pos, 1, fp);
	fp->buffer_dat[0] = 0;
	fp->buffer_pos    = 0;
	fp->self          = 0;
	return 0;
}
