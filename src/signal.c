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
#include "inc/signal.h"
#include "inc/errno.h"
#include "src/crt/runtime.h"
#include "inc/posix/errno.h"

/*
 * Proper signum's
 * #define SIGABRT __ccaprice_signal_selector[0]
 * #define SIGILL  __ccaprice_signal_selector[1]
 * #define SIGSEGV __ccaprice_signal_selector[2]
 * #define SIGFPE  __ccaprice_signal_selector[3]
 * #define SIGINT  __ccaprice_signal_selector[4]
 * #define SIGTERM __ccaprice_signal_selector[5]
 */
#if defined(LINUX) || defined(BSD)
/*
 * All signal numbers are the same across all x86_32 / x86_64
 * linux systems and BSD's
 *
 * ARM and alpha support will require more fine-tuned regard
 * to signal numbers (when those architectures are supported)
 */
	int __ccaprice_signal_selector[6] = {
		/* SIGABRT */ 6,
		/* SIGILL  */ 4,
		/* SIGSEGV */ 11,
		/* SIGFPE  */ 8,
		/* SIGINT  */ 2,
		/* SIGTERM */ 15
	};
#else
#	error "No implemented __ccaprice_signal_selector for OS"
#endif

/* internal handlers */
int __ccaprice_signal_dfl(int sig) {
	return kill (
		getpid(),
		__ccaprice_signal_selector[sig]
	);
}
int __ccaprice_signal_ign(int sig) {
	return __ccaprice_signal_selector[sig];
}

int raise(int sig) {
	/*
	 * Execute the default signal action which is kill()
	 * this whole system is odd
	 */
	return __ccaprice_signal_dfl(sig);
}

/* TODO: implement signal and sig_atomic_t */
