#include "inc/stdlib.h"
#include "inc/signal.h"
#include "inc/assert.h"
#include "src/crt/runtime.h"

/*
 * C++ requires as least 32 atexit functions, C does not
 * however this needs to stay backwards compatible with
 * C++.
 */
static short  ccaprice_atexit_position = 0;
static void (*ccaprice_atexit_functions[32])() = {
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

void atexit(void (*fun)()) {
	if (fun && ccaprice_atexit_position + 1 < 32) {
		ccaprice_atexit_functions[ccaprice_atexit_position] = fun;
		ccaprice_atexit_position ++;
	} else {
		if (ccaprice_atexit_position +1 >= 32) {
			ccaprice_atexit_position =0;
		}
	}
}

/* This is magical */
void _start(int argc, char **argv) {
	extern int main();
	assert((int)&main);
	exit(((int (*)(int, char**))main)(argc, argv));
}

extern int ccaprice_syscall(int, ...);
void exit(int status) {
	
	/* only perform atexit calls if first one exists */
	if (ccaprice_atexit_functions[0]) {
		int  i=32;
		for (; i>0; i--) {
			if (ccaprice_atexit_functions[i])
				ccaprice_atexit_functions[i](); /* call in reverse order */
		}
	}
	_exit(status);
}
