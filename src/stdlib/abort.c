#include "inc/stdlib.h"
#include "inc/signal.h"

void ccaprice_abort(int sig) {
	raise(sig);
}

void abort() {
	ccaprice_abort(SIGABRT);
}
