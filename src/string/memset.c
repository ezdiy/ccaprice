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
	
