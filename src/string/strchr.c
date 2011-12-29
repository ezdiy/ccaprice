#include "inc/string.h"

char *strchr(const char *src, int cmp) {
	return memchr((void*)src, cmp, strlen(src));
}
