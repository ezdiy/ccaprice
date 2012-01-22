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

void *memset(void *dst, int ctr, register size_t len) {
	#ifdef STRING_MEMSET_OPTIMAL
		#ifdef STRING_MEMSET_X86_64
		/* memsets in 8-byte chunks (fast for 64-bit platforms) */
			size_t    left  = (len % 8);
			if(len >= 8) {
				uint64_t  value = 0;
				uint64_t* dstpt = (uint64_t*)dst;
				
				int i;
				for(i=0; i<8; i++) {
					value <<= 16;
					value |= ctr;
				}
				
				len /= 8;
				while (len--) {
					*dstpt ++ = value;
				}
			} 
			if (left > 0) {
				uint16_t  value = (uint16_t) ctr;
				uint16_t *dstpt = (uint16_t*)dst;
				
				switch (left) {
					case 7: *dstpt++ = value;
					case 6: *dstpt++ = value;
					case 5: *dstpt++ = value;
					case 4: *dstpt++ = value;
					case 3: *dstpt++ = value;
					case 2: *dstpt++ = value;
					case 1: *dstpt++ = value;
				}
			}
			return dst;
		#elif defined(STRING_MEMSET_X86)
			/* memsets in 4-byte chunks (fast for word-sized CPUs) */
			size_t left = (len % 4);
			if (len >= 4) {
				uint32_t  value = 0;
				uint32_t *dstpt = (uint32_t*)dst;
				
				int i;
				for(i = 0; i < 4; i++) {
					value <<= 8;
					value |=ctr;
				}
				
				len /= 4;
				while (len--) {
					*dstpt++ = value;
				}
			}
			if (left > 0) {
				uint8_t  value = (uint8_t) ctr;
				uint8_t *dstpt = (uint8_t*)dst;
				
				switch (left) {
					case 3: *dstpt++ = value;
					case 2: *dstpt++ = value;
					case 1: *dstpt++ = value;
				}
			}
			return dst;
		#else
			#define STRING_MEMSET_NONE
		#endif
	#else
		#define STRING_MEMSET_NONE
	#endif
	
	#ifdef STRING_MEMSET_NONE
		#warning "[ccaprice] no optimized memset implementation, using naive method (could be slow)"
		unsigned char *p=(unsigned char*)dsr;
		
		/* standard byte-by-byte memset */
		while (len--) {
			*p++ = (unsigned char)ctr;
		}
		
		return dst;
	#endif
	
	return 0;
}
	
