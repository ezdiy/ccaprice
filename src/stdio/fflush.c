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


CCAPRICE_INTERNAL_TYPE(size_t, ccaprice_stdio_file_pos);
CCAPRICE_INTERNAL_TYPE(FILE  , ccaprice_stdio_file_dat[CCAPRICE_STDIO_FILE_BUFFER_LEN]);
/*
 * fflush() is used to write out buffered data stuck in
 * the fp->buffer_dat.
 */
int fflush(FILE *fp) {
	/* If NULL is passed free all open files */
	if (!fp) {
		while(--ccaprice_stdio_file_pos>0) 
			fflush(&ccaprice_stdio_file_dat[ccaprice_stdio_file_pos]);
	}
			
	fwrite(fp->buffer_dat, fp->buffer_pos, 1, fp);
	fp->buffer_dat[0] = 0;
	fp->buffer_pos    = 0;
	return 0;
}
