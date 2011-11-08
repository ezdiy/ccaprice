#include "inc/string.h"

void *memchr(const void *src, int cmp, register size_t cnt)
{
	unsigned long        val = (unsigned char)cmp;
	unsigned long        bit[3];
	const unsigned long *clp;
	
	if (4 <= cnt) {
		unsigned long kip[3] = {
			0x01010101UL<<0,
			0x01010101UL<<7
		};
		kip[2] = (val<<24)|(val<<16)|(val<<8)|val;
		
		/* check unalligned area first */
		{
			long align = (long)src&3;
			if  (align == 0)
				clp = (unsigned long*)src - 1;
			else {
				const long    byte = (4 - align);
				unsigned long mask = 0xFFFFFFFFUL << (byte<<3);
				
				clp    = (unsigned long*)((char*)src-align);
				bit[0] = (*clp ^ kip[2]) | mask;
				bit[1] = bit[0]- kip[0];
				bit[2] = kip[1]&~bit[0];
				
				if (bit[1] & bit[2])
					goto found_area;
				cnt -= byte;
			}
		}
		
		/* Check word-alligned areas */
		{
			long words = cnt >> 2;
			while (0 < words) {
				bit[0] = *++clp &  kip[2];
				bit[1] = bit[0] -  kip[0];
				bit[2] = kip[1] &~ bit[0];
				
				if (bit[1] & bit[2])
					goto found_area;
				words--;
			}
		}
		
		/* Check remainder areas */
		{
			long remain = cnt & 3;
			if  (remain != 0) {
				bit[0] = (*clp++ ^  kip[2]) | (0xFFFFFFFFUL >> (remain << 3));
				bit[1] =  bit[0] -  kip[0];
				bit[2] =  kip[1] &~ bit[0];
				
				if (bit[1] & bit[2])
					goto found_area;
			}
		}
	}
	else {
		const unsigned char *src8 = (const unsigned char*)src;
		while (0 < cnt) {
			if (*src8 == val)
				return (void*)src8;
			src8++;
			cnt --;
		}
	}
	
	return NULL;
	
	/* Return exact pointer to position in word */
	found_area:
		if ((bit[0] & 0xFF000000UL) == 0) return (void*)clp;
		if ((bit[0] & 0x00FF0000UL) == 0) return (void*)((char*)clp+1);
		if ((bit[0] & 0x0000FF00UL) == 0) return (void*)((char*)clp+2);
		                                  return (void*)((char*)clp+3);
}
