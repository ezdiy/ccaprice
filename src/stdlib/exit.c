#include "inc/stdlib.h"
#include "inc/signal.h"
#include "inc/assert.h"
#include <syscall.h>

/*
 * These error handlers should really go
 * somewhere else.  This seems fine for
 * now though :).
 */
#ifdef __x86_64__
int ccaprice_syscall_error() {
	register int no __asm__("%rcx");
	__asm__ __volatile__ (
		"mov %rax, %rcx\n\t"
		"neg %rcx      \n\t"
	);
	return no;
}
#endif
#ifdef __i386__
int ccaprice_syscall_error() {
	register int no __asm__("%edx");
	__asm__ __volatile__ (
		"mov  %eax, %edx\n\t"
		"negl %edx      \n\t"
	);
	return no;
}
#endif

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
	ccaprice_syscall(SYS_exit,  1);
}
