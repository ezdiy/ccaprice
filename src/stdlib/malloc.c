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
#include "inc/string.h"
#include "inc/errno.h"
#include "inc/posix/errno.h"
#include "inc/stdint.h"

CCAPRICE_INTERNAL_FUNC(void*, ccaprice_malloc_small, (size_t));

void *malloc(size_t size) {
	void *ret = ccaprice_malloc_small(size);
	if (ret == (void*)-1) {
		errno = ENOMEM;
		return NULL;
	}
	return ret;
}

void *calloc(size_t m, size_t n) {
	void   *p;
	size_t *z;
	if (n && m > (size_t)-1/n) {
		errno = ENOMEM;
		return NULL;
	}
	n *= m;
	p  = malloc(n);
	if (!p) return NULL;
	
	if (((size_t*)p)[-1] & 7) {
		m = (n + sizeof(*z)-1)/sizeof(*z);
		for (z=p; m; m--, z++)
			if(*z) *z = 0;
	}
	return p;
}
