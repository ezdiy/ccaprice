#include "inc/string.h"

char *strchr(const char *src, int cmp) {
	
	do {
		if (*src == cmp)
			return (char*) src;
	} while (*src++);
	
	return 0;
}
