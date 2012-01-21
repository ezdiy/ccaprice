#include "inc/string.h"

char *strdup(const char *s) {
	if (!s) return NULL;
	
	size_t len = strlen(s);
	char *r = malloc(len);
	strncpy(r, s, len);
	return r;
}
