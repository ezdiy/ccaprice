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
#include <errno.h>
#include <signal.h>
/* These need to be externed for raise.c */
void (*__ccaprice_sigabrt)(int) = SIG_DFL;
void (*__ccaprice_sigfpe) (int) = SIG_DFL;
void (*__ccaprice_sigill) (int) = SIG_DFL;
void (*__ccaprice_sigint) (int) = SIG_DFL;
void (*__ccaprice_sigsegv)(int) = SIG_DFL;
void (*__ccaprice_sigterm)(int) = SIG_DFL;

void (*signal(int sig, void (*func)(int)))(int) {
	void (*old)(int);
	if (sig <= 0 || func == SIG_ERR)
		return SIG_ERR;
		
	switch (sig) {
		case SIGABRT: old = __ccaprice_sigabrt, __ccaprice_sigabrt = func; break;
		case SIGFPE:  old = __ccaprice_sigfpe , __ccaprice_sigfpe  = func; break;
		case SIGILL:  old = __ccaprice_sigill , __ccaprice_sigill  = func; break;
		case SIGSEGV: old = __ccaprice_sigsegv, __ccaprice_sigsegv = func; break;
		case SIGTERM: old = __ccaprice_sigterm, __ccaprice_sigterm = func; break;
		
		default:
			errno = 1;
			return SIG_ERR;
	}
	return old;
}