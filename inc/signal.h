/*
 * Copyright (C) 2012
 *  Dale Weiler
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
#ifndef __CCAPRICE_SIGNAL_HDR__
#define __CCAPRICE_SIGNAL_HDR__
#include "inc/ccaprice.h"
/*
 * The C standard only states that the following be implemented:
 * SIGABRT
 * SIGILL
 * SIGSEGV
 * SIGFPE
 * SIGINT
 * SIGTERM
 *
 * handlers:
 * SIG_DFL
 * SIG_IGN
 *
 * To properly select the right signum we compose an array which when
 * indexed by one of these will select the right signum for it.
 */

#define SIGABRT 0 /*__ccaprice_signal_selector[0]*/
#define SIGILL  1 /*__ccaprice_signal_selector[1]*/
#define SIGSEGV 2 /*__ccaprice_signal_selector[2]*/
#define SIGFPE  3 /*__ccaprice_signal_selector[3]*/
#define SIGINT  4 /*__ccaprice_signal_selector[4]*/
#define SIGTERM 5 /*__ccaprice_signal_selector[5]*/

#define SIG_DFL (&__ccaprice_signal_dfl)
#define SIG_IGN (&__ccaprice_signal_ign)

/* internal functions */
__CCAPRICE_EXPORT int __ccaprice_signal_dfl(int);
__CCAPRICE_EXPORT int __ccaprice_signal_ign(int);

/* exposed functions */
__CCAPRICE_EXPORT int raise(int);
#endif
