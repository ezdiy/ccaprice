#include "inc/stdio.h"
#include "inc/stdlib.h"
int fclose(FILE *fp) {
	if (!fp) return EOF;
	fflush(fp); /* always flush buffer on close */
	return close(fp->fd);
}
