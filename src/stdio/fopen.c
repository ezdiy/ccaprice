#include "inc/stdio.h"
extern void *malloc(size_t);

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
	
	FILE *fp       = &ccaprice_stdio_file_dat[++ccaprice_stdio_file_pos];
	fp->fd         = open(file, flags);
	fp->buffer_pos = 0;
	fp->eof        = 0;
	fp->err        = 0;
	return fp;
}
