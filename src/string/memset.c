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
#include "inc/stdint.h"
void *memset(void *dst, int ctr, register size_t len) {
	#if  defined(__STRING_MEMSET_OPTIMAL)  && \
		(defined(__CCAPRICE_TARGET_X86_64) || defined(__CCAPRICE_TARGET_X86_32))
		size_t    search = (len % 4);
		uint32_t  check4 = (ctr | (ctr << 8) | (ctr << 16) | (ctr << 24));
		uint8_t   check1 = (uint8_t)ctr;
		uint32_t *destp4;
		uint8_t  *destp1;

		destp4 = (uint32_t*)dst;
		len /= 4;
		while (len--)
			*destp4++ = check4;

		destp1 = (uint8_t*)destp4;
		switch (search) {
			case 3: *destp1++ = check1;
			case 2: *destp1++ = check1;
			case 1: *destp1++ = check1;
		}

		return dst;
	#else
		#warning "[ccaprice] no optimized memset implementation, using naive method (could be slow)"
		register unsigned char *p=(unsigned char*)dst;
		while (len--)
			*p++ = ctr;
		return dst;
	#endif
	return NULL;
}
