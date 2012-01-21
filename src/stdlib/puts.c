#include "inc/stdlib.h"
#include "inc/string.h"
#include "src/crt/runtime.h"

int puts(const char *m) {
	write(0, m, strlen(m));
}
