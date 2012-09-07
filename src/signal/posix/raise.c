/*
 * Copyright (C) 2012
 *     Dale Weiler
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
#include <stdio.h>
#include <signal.h>
#include <bits/types.h>

/* required */
__CCAPRICE_INTERNAL_FUNC(int,   kill,   (pid_t, int));
__CCAPRICE_INTERNAL_FUNC(pid_t, getpid, ());

/* signal funptrs */
__CCAPRICE_INTERNAL_TYPE(void (*__ccaprice_sigabrt)(int),);
__CCAPRICE_INTERNAL_TYPE(void (*__ccaprice_sigfpe)(int),);
__CCAPRICE_INTERNAL_TYPE(void (*__ccaprice_sigill)(int),);
__CCAPRICE_INTERNAL_TYPE(void (*__ccaprice_sigint)(int),);
__CCAPRICE_INTERNAL_TYPE(void (*__ccaprice_sigsegv)(int),);
__CCAPRICE_INTERNAL_TYPE(void (*__ccaprice_sigterm)(int),);

int raise(int sig) {
	static const int selector[6] = {
		/* SIGABRT */ 6,
		/* SIGILL  */ 4,
		/* SIGSEGV */ 11,
		/* SIGFPE  */ 8,
		/* SIGINT  */ 2,
		/* SIGTERM */ 15
	};

	const char *msg;
	void (*hnd)(int) = NULL;
	
	switch (sig) {
		case SIGABRT: hnd = __ccaprice_sigabrt; msg = "Aborted"; break;
		case SIGFPE:  hnd = __ccaprice_sigfpe;  msg = "Arithmetic expression"; break;
		case SIGILL:  hnd = __ccaprice_sigill;  msg = "Killed"; break;
		case SIGINT:  hnd = __ccaprice_sigint;  msg = "Interrupt"; break;
		case SIGSEGV: hnd = __ccaprice_sigsegv; msg = "Segmentation fault"; break;
		case SIGTERM: hnd = __ccaprice_sigterm; msg = "Terminated"; break;
		
		default:
			fprintf(stderr, "Illegal signal %d\n", sig);
			kill(getpid(), -1);
	}
	
	if (hnd == SIG_DFL) {
		fputs(msg, stderr);
		kill(getpid(), selector[sig]);
	} else if (hnd != SIG_IGN) {
		hnd = signal(sig, SIG_DFL);
		hnd(sig);
	}
	return 0;
}