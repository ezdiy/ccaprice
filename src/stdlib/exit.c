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

/* This is magical */
void _start() {
	extern int main(); // we can't pass arguments :(
	exit(main());
}

void exit(int status) {
	
	/* only perform atexit calls if first one exists */
	if (ccaprice_atexit_functions[0]) {
		int  i=32;
		for (; i>0; i--) {
			if (ccaprice_atexit_functions[i])
				ccaprice_atexit_functions[i](); /* call in reverse order */
		}
	}
	
	
	char *ret = "returned\n";
	
	/* write() sys call */
	__asm__ __volatile__("\
		movl $4, %%eax\n\
		movl %0, %%ecx\n\
		movl $10,%%edx\n\
		int $0x80" : :"g"(ret)
	);

	/* exit() sys call */
	__asm__(
		"movl $1,%eax;"
        "xorl %ebx,%ebx;"
        "int  $0x80"
    );
}
