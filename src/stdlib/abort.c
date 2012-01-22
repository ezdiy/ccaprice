#include "inc/stdlib.h"
#include "inc/signal.h"
#include "src/crt/runtime.h"

int raise(int sig) {
	return kill(getpid(), sig);
}
void abort() {
	raise(SIGABRT);
}
