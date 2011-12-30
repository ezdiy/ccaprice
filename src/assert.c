#include "inc/assert.h"
#include "inc/signal.h"
void ccaprice_assert(const char *file, int line, int expr) {
	if (!expr) {
		/* todo print */
		raise(SIGABRT);
	}
}
