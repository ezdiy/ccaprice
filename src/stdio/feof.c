#include "inc/stdio.h"

int feof(FILE *fp) {
	return fp->eof;
}	
