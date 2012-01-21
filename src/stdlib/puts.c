#include "inc/stdlib.h"
#include "inc/string.h"
#include "src/crt/runtime.h"

int puts(const char *m) {
	char newl = '\n';
	write(0, m, strlen(m));
	write(0, &newl, 1);
}
