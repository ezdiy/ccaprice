#include "inc/stdio.h"

int fputc(int c, FILE *fp) {
	if (!fp) return EOF;
	if (fp->buffer_pos + 1 > sizeof(fp->buffer_pos))
		fflush(fp); /* flush stream we're out of buffer space */
	
	/* buffer the data */
	fp->buffer_dat[++fp->buffer_pos] = c;	
	return 0;
}
