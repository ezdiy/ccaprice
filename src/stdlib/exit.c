#include "inc/stdlib.h"
#include "inc/signal.h"

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

void exit(int status) {
	int  i=32;
	for (; i>0; i--) {
		ccaprice_atexit_functions[i](); /* call in reverse order */
	}
	
	raise(SIGKILL);
	
	/* fall back method, will work every time */
	int  *a = 0; *a = 0;
	exit(*a);
}
