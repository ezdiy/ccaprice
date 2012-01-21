#include "inc/stdio.h"

int fputc(int c, FILE *fp) {
	if (!fp) return EOF;
	write(fp->fd, &c, 1);
	return 0;
}
