#include "inc/stdlib.h"
#include "inc/string.h"
#include "inc/stdio.h"
#include "src/crt/runtime.h"

#define EOF -1

int fputs(const char *str, FILE *fp) {
	if (!fp) return EOF;
	write(fp->fd, str, strlen(str));
	return 0;
}		

int puts(const char *m) {
	int go;
	go = fputs(m   , stdout);
	go = fputs("\n", stdout);
	return go;
}


