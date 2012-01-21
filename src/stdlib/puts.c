#include "inc/stdio.h"

int puts(const char *m) {
	int go;
	go = fputs(m   , stdout);
	go = fputs("\n", stdout);
	return go;
}


