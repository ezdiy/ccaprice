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
#include "ccaprice.h"
#include <atomic.h>
#include <bits/syscall.h>
__CCAPRICE_INTERNAL_FUNC(void, __ccaprice_thread_wait, (volatile int *, volatile int *, int, int));
__CCAPRICE_INTERNAL_FUNC(void, __ccaprice_thread_wake, (volatile int *, int, int));

void __ccaprice_thread_lock(volatile int *p) {
    while (__ccaprice_atomic_swap(p, 1)) {
        __ccaprice_thread_wait (
            p+0,
            p+1,
            
            1,
            1
        );
    }
}

void __ccaprice_thread_unlock(volatile int *p) {
    __ccaprice_atomic_store(p, 0);
    if (p[1]) {
        __ccaprice_thread_wake(p, 1, 1);
    }
}


