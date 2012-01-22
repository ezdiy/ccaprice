#include "inc/stdio.h"

int puts(const char *m) {
	int go;
	go = fputs(m   , stdout);
	go = fputc('\n', stdout);
	
	fflush(stdout);
	return go;
}


