/*
 * Copyright (C) 2012 
 * 	Dale Weiler
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "inc/stdlib.h"
#include "inc/signal.h"
#include "inc/stdio.h"


CCAPRICE_INTERNAL_TYPE(FILE, ccaprice_stdio_file_dat[CCAPRICE_STDIO_FILE_BUFFER_LEN]);

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
	ccaprice_i_dat = &ccaprice_stdio_file_dat[0]; //malloc(sizeof(FILE));
	ccaprice_o_dat = &ccaprice_stdio_file_dat[1]; //malloc(sizeof(FILE));
	
	ccaprice_i_dat->fd = 0;
	ccaprice_o_dat->fd = 1;
	
	CCAPRICE_INTERNAL_FUNC(int, main, ());
	exit(((int (*)(int, char**))main)(argc, argv));
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
	_exit(status);
}
