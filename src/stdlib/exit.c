#include "inc/stdlib.h"
#include "inc/signal.h"
#include "inc/assert.h"
#include "inc/stdio.h"
#include "src/crt/runtime.h"

/* this is nasty ... */
FILE *ccaprice_o_dat = ((void*)0);
FILE *ccaprice_i_dat = ((void*)0);
FILE *ccaprice_stdout() { return ccaprice_o_dat; }
FILE *ccaprice_stdin () { return ccaprice_i_dat; }

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
	/* setup stdout at startup */
	ccaprice_i_dat = malloc(sizeof(FILE));
	ccaprice_o_dat = malloc(sizeof(FILE));
	
	ccaprice_i_dat->fd = 0;
	ccaprice_o_dat->fd = 1;
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
