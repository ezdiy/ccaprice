#include "inc/stdio.h"
#include "inc/string.h"
int fputs(const char *str, FILE *fp) {
	if (!fp) return EOF;
	
	/* 
	 * The function begins copying from the address specified (str) 
	 * until it reaches the terminating null character ('\0'). 
	 * This final null-character is not copied to the stream.
	 */
	while (*str != '\0') {
		fp->buffer_dat[fp->buffer_pos] = *str;
		fp->buffer_pos ++, str++;
	}
	return 0;
}
