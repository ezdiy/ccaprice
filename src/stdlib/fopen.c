#include "inc/stdio.h"
extern void *malloc(size_t);
FILE *fopen(const char *file, const char *mode) {
	FILE *fp = malloc(sizeof(FILE));
	fp->fd = open(file, O_CREAT | O_RDWR);
	return fp;
}
