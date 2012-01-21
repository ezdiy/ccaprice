#include "inc/stdio.h"
#include "inc/stdlib.h"
int fclose(FILE *fp) {
	if (!fp) return EOF;
	int go = close(fp->fd);
	free(fp);
	return go;
}
