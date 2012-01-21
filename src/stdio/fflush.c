#include "inc/stdio.h"

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
