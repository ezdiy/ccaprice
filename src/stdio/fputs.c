#include "inc/stdio.h"
#include "inc/string.h"
int fputs(const char *str, FILE *fp) {
	
	/*
	 * Invalid file pointer passed to fputs
	 * return EOF.
	 */
	if (!fp)
		return EOF;
	
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
