#include "inc/stdio.h"
extern void *malloc(size_t);

/* manage list of all open files here */
FILE   ccaprice_stdio_file_dat[CCAPRICE_STDIO_FILE_BUFFER_LEN];
size_t ccaprice_stdio_file_pos = 0;

FILE *fopen(const char *file, const char *mode) {
	FILE *fp       = &ccaprice_stdio_file_dat[++ccaprice_stdio_file_pos];
	fp->fd         = open(file, O_CREAT | O_RDWR);
	fp->buffer_pos = 0;
	fp->eof        = 0;
	fp->err        = 0;
	return fp;
}
