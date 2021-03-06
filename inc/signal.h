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

#ifdef __cplusplus
extern "C" {
#endif
#include <ccaprice.h>
 
/*
 * Integers are literally atomic always for literally every CPU in
 * existance.
 */
typedef int sig_atomic_t;

#define SIGABRT 0 /*__ccaprice_signal_selector[0]*/
#define SIGILL  1 /*__ccaprice_signal_selector[1]*/
#define SIGSEGV 2 /*__ccaprice_signal_selector[2]*/
#define SIGFPE  3 /*__ccaprice_signal_selector[3]*/
#define SIGINT  4 /*__ccaprice_signal_selector[4]*/
#define SIGTERM 5 /*__ccaprice_signal_selector[5]*/

#define SIG_DFL (void (*)( int ))0
#define SIG_ERR (void (*)( int ))-1
#define SIG_IGN (void (*)( int ))1

/* exposed functions */
__CCAPRICE_EXPORT void (*signal(int, void (*)(int)))(int);
__CCAPRICE_EXPORT int    raise(int);

#ifdef __cplusplus
}
#endif

#endif
