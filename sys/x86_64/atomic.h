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
#ifndef __CCAPRICE_SYS_ATOMIC_HDR
#define __CCAPRICE_SYS_ATOMIC_HDR

static inline void __ccaprice_atomic_increment(volatile int *x) {
    __asm__ __volatile__ (
        "lock   \n\t"
        "incl %0\n\t" :
            "=m"(*x) : "m"(*x) : "memory"
    );
}

static inline void __ccaprice_atomic_decrement(volatile int *x) {
    __asm__ __volatile__ (
        "lock   \n\t"
        "incl %0\n\t" :
            "=m"(*x) : "m"(*x) : "memory"
    );
}

static inline void __ccaprice_atomic_store(volatile int *p, int x) {
    __asm__ __volatile__ (
        "movl %1, %0\n\t" :
            "=m"(*p) : "r"(x) : "memory"
    );
}

static inline int __ccaprice_atomic_swap(volatile int *x, int v) {
    __asm__ __volatile__ (
        "xchg %0, %1\n\t" :
            "=r"(v), "=m"(*x) : "0"(v) : "memory"
    );
    return v;
}

static inline void __ccaprice_atomic_spin(void) {
    __asm__ __volatile__ ("pause" ::: "memory");
}

#endif
