#include "inc/stdio.h"

int fclose(FILE *fp) {
	if (!fp) return EOF;
	return close(fp->fd);
}
