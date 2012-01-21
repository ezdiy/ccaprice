#include "inc/stdlib.h"
#include "inc/signal.h"
#include <syscall.h> /* this is fine I supose */

extern int ccaprice_syscall(int, ...);
int ccaprice_raise(int sig) {
	int pid = ccaprice_syscall(SYS_getpid);
	ccaprice_syscall(SYS_kill, pid, sig);
}

void ccaprice_abort(int sig) {
	ccaprice_raise(sig);
}

void abort() {
	ccaprice_abort(SIGABRT);
}
