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
int raise(int sig) {
	/*
	 * Validate sig is a valid signal if it's not
	 * we have to set an error code in errno. This
	 * is so odd; SUSv3 says it has to be though.
	 * There must be a faster way at doing this?
	 */
	 
	/*
	 * Work around systems with  no  SIGPOLL
	 * use SIGUSR1  again, double  check is
	 * of no harm.  It's just not all sytems
	 * have SIGPOLL.
	 */
	#ifndef SIGPOLL
		#define SIGPOLL SIGUSR1
	#endif
	
	if (sig != SIGABRT && sig != SIGALRM   && sig != SIGBUS  && 
	    sig != SIGCHLD && sig != SIGCONT   && sig != SIGFPE  &&
	    sig != SIGHUP  && sig != SIGILL    && sig != SIGINT  &&
	    sig != SIGKILL && sig != SIGPIPE   && sig != SIGQUIT &&
	    sig != SIGSEGV && sig != SIGSTOP   && sig != SIGTERM &&
	    sig != SIGTSTP && sig != SIGTTIN   && sig != SIGTTOU &&
	    sig != SIGUSR1 && sig != SIGUSR2   && sig != SIGPOLL &&
	    sig != SIGPROF && sig != SIGSYS    && sig != SIGTRAP &&
	    sig != SIGURG  && sig != SIGVTALRM && sig != SIGXCPU && sig != SIGXFSZ) {
			errno = EINVAL;
			return 1;
	}
	
	return kill(getpid(), sig);
}


