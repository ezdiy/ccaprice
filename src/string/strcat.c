#include "inc/string.h"

char *strncat(char *dst, const char *src, register size_t cnt) {
	size_t off = strlen(dst);
	strncpy(dst+off, src, cnt);
	return dst;
}

char *strcat(char *dst, const char *src) {
	size_t off = strlen(dst);
	strcpy(dst+off,src);
	return dst;
}
