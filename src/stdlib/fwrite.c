#include "inc/stdio.h"

size_t fwrite(const void *p, size_t size, size_t count, FILE *fp) {
	size_t times = count;
	while (times-->0)
		if(write(fp->fd, p, size) == -1)
			break;
	return (times==0)?count:times;
}
