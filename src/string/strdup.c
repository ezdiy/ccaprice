#include "inc/string.h"
#include "inc/stdlib.h"
char *strdup(const char *s) {
	if (!s) return NULL;
	
	size_t len = strlen(s);
	char *r = (char*)malloc(len);
	strncpy(r, s, len);
	return r;
}
