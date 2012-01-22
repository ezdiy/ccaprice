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
