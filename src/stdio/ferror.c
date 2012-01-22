#include "inc/stdio.h"

int ferror(FILE *fp) {
	if (!fp) return 0;
	return fp->err;
}
