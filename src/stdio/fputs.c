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
#include "inc/string.h"
#include "inc/posix/errno.h"

CCAPRICE_INTERNAL_TYPE(int *, ccaprice_posix_errno);

int fputs(const char *str, FILE *fp) {
	if (!str) return EOF;
	/*
	 * Invalid file pointer passed to fputs
	 * return EOF.
	 */
	if (!fp) {
		errno = EBADF;
		return EOF;
	}
	
	/* 
	 * The function begins copying from the address specified (str) 
	 * until it reaches the terminating null character ('\0'). 
	 * This final null-character is not copied to the stream.
	 */
	while (*str != '\0') {
		/* 
		 * We're out of bufferable space
		 * we better flush the stream.
		 */
		if (fp->buffer_pos + 1 > sizeof(fp->buffer_dat))
			fflush(fp);
		
		/* 
		 * Buffer the data, while incrementing
		 * str and the current buffer position.
		 */
		fp->buffer_dat[fp->buffer_pos] = *str;
		fp->buffer_pos ++, str++;
	}
	
	return 0;
}
