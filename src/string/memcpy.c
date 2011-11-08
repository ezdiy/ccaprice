#include "inc/string.h"

void *memcpy(void *dst, const void *src, register size_t cnt)
{
	/*
	 * Highly optimized SSE memcpy, specialized for <256 byte
	 * as well as larger chunks.  Including but not limited to
	 * unalligned, and alligned data.
	 */
	#ifdef STRING_MEMCPY_SSE
	void  *ret = dst;
	size_t itr;
	
	/* 
	 * Prefetch for MOVSB:
	 * 	this actually gains  some  speed in
	 * 	most situations for some odd reason.
	 */
	__asm__ __volatile__ (
		"prefetchnta    (%0)\n\t"
		"prefetchnta 32 (%0)\n\t"
		"prefetchnta 64 (%0)\n\t"
		"prefetchnta 96 (%0)\n\t"
		"prefetchnta 128(%0)\n\t"
		"prefetchnta 192(%0)\n\t"
		"prefetchnta 224(%0)\n\t"
		"prefetchnta 256(%0)\n\t"
		"prefetchnta 288(%0)\n\t" :: "r"(src)
	);
	
	/* 64-byte blocks only */
	if (cnt >= 0x40) {
		register unsigned long int dla = ((unsigned long int)dst)&(16-1);
		if (dla) {
			register unsigned long dum;
			dla = 16-dla;
			cnt-=    dla;
			
			/* Fast memcpy for <256 bytes */
			__asm__ __volatile__ (
				"rep; movsb" :
					"=&D"(dst),
					"=&S"(src),
					"=&c"(dum) :
						"0"(dst),
						"1"(src),
						"2"(dla) : "memory"
			);
		}
		
		itr  = cnt>>6;
		cnt &= 63;
		
		/* source is misaligned */
		if (((unsigned long)src)&15) {
			for (; itr>0; itr--) {
				__asm__ __volatile__ (
					"prefetchnta 320(%0)\n\t"
					"prefetchnta 352(%0)\n\t"
					
					"movups    (%0), %%xmm0\n\t"
					"movups  16(%0), %%xmm1\n\t"
					"movups  32(%0), %%xmm2\n\t"
					"movups  48(%0), %%xmm3\n\t"
					
					"movntps %%xmm0,   (%1)\n\t"
					"movntps %%xmm1, 16(%1)\n\t"
					"movntps %%xmm2, 32(%1)\n\t"
					"movntps %%xmm3, 48(%1)\n\t" ::
						"r"(src),
						"r"(dst) : "memory"
				);
				
				src = (const unsigned char *)src + 64;
				dst =       (unsigned char *)dst + 64;
			}
		}
		
		/* 
		 * source is aligned  on  16-byte  boundry.  This  will
		 * allow the use of movaps, which is faster then movups.
		 */
		else {
			for (; itr>0; itr--) {
				/* prefetch and move on 16-byte boundry */
				__asm__ __volatile__ (
					"prefetchnta 320(%0)\n\t"
					"prefetchnta 352(%0)\n\t"
					
					"movaps    (%0), %%xmm0\n\t"
					"movaps  16(%0), %%xmm1\n\t"
					"movaps  32(%0), %%xmm2\n\t"
					"movaps  48(%0), %%xmm3\n\t"
					
					"movntps %%xmm0,   (%1)\n\t"
					"movntps %%xmm1, 16(%1)\n\t"
					"movntps %%xmm2, 32(%1)\n\t"
					"movntps %%xmm3, 48(%1)\n\t" ::
						"r"(src),
						"r"(dst) : "memory"
				);
				src = (const unsigned char *)src + 64;
				dst =       (unsigned char *)dst + 64;
			}
			
			/* reorder data, as movntq is weakly-ordered. */
			__asm__ __volatile__ ("sfence" ::: "memory");
			__asm__ __volatile__ ("emms"   ::: "memory");
		}
	}
	/* tail of block */
	if (cnt) {
		/* use faster memcpy for data <256 bytes */
		if (cnt < 4) {
			/* Fast memcpy for <256 bytes */
			register unsigned long int dum;
			__asm__ __volatile__ (
				"rep; movsb" :
					"=&D"(dst),
					"=&S"(src),
					"=&c"(dum) :
						"0"(dst),
						"1"(src),
						"2"(cnt) : "memory"
			);
		}
		/* faster memcpy for >256 bytes */
		else {
			int dump[3];
			/* 
			 * The following fast memcpy for tail of block is optimized
			 * for larger chunks of data.
			 */
			__asm__ __volatile__ (
				"rep;  movsl \n\t"
				"testb $2,%b4\n\t"
				"je    1f    \n\t"
				"movsw       \n"
				"1:\t"
					"testb $1,%b4\n\t"
					"je    2f    \n\t"
					"movsb       \n"
				"2:\t" :
					"=&c"(dump[0]),
					"=&D"(dump[1]),
					"=&S"(dump[2]) :
						"0"(cnt/4),
						"q"(cnt),
						"1"((long)dst),
						"2"((long)src) : "memory"
			);
		}
	}
	return ret;
	
	/* Fast X86_64 memcpy for most types of data */
	#else
	__asm__("cld; rep movsb" :: 
		"c"(cnt),
		"S"(src),
		"D"(dst)
	);
	return dst;
	#endif
}
