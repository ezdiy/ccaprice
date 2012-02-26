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
#include "src/crt/runtime.h"

/* manage list of all open files here */
FILE   ccaprice_stdio_file_dat[CCAPRICE_STDIO_FILE_BUFFER_LEN];
size_t ccaprice_stdio_file_pos = 0;

FILE *fopen(const char *file, const char *mode) {
	
	size_t flags = O_RDONLY;
	size_t other = 0;
	
	/*
	 * Determine file mode.
	 */
	while (*mode) {
		switch (*mode) {
			case 'r': flags = O_RDONLY;                      break;
			case 'w': flags = O_WRONLY | O_CREAT | O_TRUNC;  break;
			case 'a': flags = O_WRONLY | O_CREAT | O_APPEND; break;
			case '+': other = 1;                             break;
		}
		mode++;
	}
	
	if (other) {
		flags = (flags &~(O_RDONLY|O_WRONLY))|O_RDWR;
	}
	/*
	 * On 32-bit systems  O_LARGEFILE needs  to be used to
	 * ensure file opens are 64-bit safe; otherwise errors
	 * could occur.
	 */
	#ifdef CCAPRICE_TARGET_X86
		/*
		 * (LFS) Allow files whose sizes cannot be represented in an off_t 
		 * (but can be represented in an off64_t) to be opened.
		 **/
		flags |= O_LARGEFILE;
	#endif
	
	FILE *fp       = &ccaprice_stdio_file_dat[ccaprice_stdio_file_pos];
	fp->fd         = open(file, flags);
	fp->buffer_pos = 0;
	fp->eof        = 0;
	fp->err        = 0;
	
	ccaprice_stdio_file_pos ++;
	return fp;
}
