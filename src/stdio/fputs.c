#include "inc/stdio.h"
#include "inc/string.h"
int fputs(const char *str, FILE *fp) {
	if (!fp) return EOF;
	write(fp->fd, str, strlen(str));
	return 0;
}
