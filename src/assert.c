#include "inc/assert.h"
#include "inc/signal.h"
static void ccaprice_assert(const char *file, int line, int expr) {
	if (!expr) {
		raise(SIGABRT);
	}
}
