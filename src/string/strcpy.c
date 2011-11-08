#include "inc/string.h"

char *strncpy(char *dst, const char *src, register size_t count) {
	return memcpy(dst, src, count);
}

char *strcpy(char *dst, const char *src) {
	return strncpy(dst, src, strlen(src));
}
