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
void *memcpy(void *dst, const void *src, register size_t cnt) {	
	#ifdef STRING_MEMCPY_OPTIMAL
		#if defined(STRING_MEMCPY_X86_64)
		/*
		 * "rep movs"  is optimized in  microcode on
		 * modern  Intel  CPU's.  This  method works
		 * best for easy-copys (src-alligned?), this
		 * will give best  performance if src & dst
		 * are both equal (mod 64).  But  will still
		 * work if they're not.  This method is also
		 * faster than any SSE routine.
		 * 
		 * See: https://lkml.org/lkml/2011/9/1/229
		 * for more information regarding the matter.
		 */
		__asm__("cld; rep movsb" :: 
			"c"(cnt),
			"S"(src),
			"D"(dst)
		);
		return dst;
		#elif defined(STRING_MEMCPY_PPC)
		/*
		 * PowerPC architecture does not have post
		 * increment or deincrement instructions.
		 * This is why copying the naive method as
		 * seen below is actually a lot slower for
		 * PPC.  This can be worked around by using
		 * the pre-inc, and pre-dec for alternitives.
		 */
		char *d_byte = (char*)dst;
		char *s_byte = (char*)src;
		
		/*
		 * 6.5.6.8 in the C99 standard says this is undefined
		 * behaviour.  Some segmented architectures will trap
		 * on this; but not on PowerPCs.
		 */
		--s_byte;
		--d_byte;
		
		/*
		 * The use of count-- here is faster than --count.
		 * Despite of the fact the PPC architecture has no
		 * post decrement instruction.  GCC optimizes this
		 * to a rather interesting (2-byte) copy, and uses
		 * while (count -= 2).
		 */
		while (cnt --) {
			/*
			 * The compiler seems to look at this like:
			 * d_byte[0] = s_byte[0];
			 * d_byte[1] = s_byte[1];
			 * ++d_byte; ++d_byte;
			 * ++s_byte; ++s_byte;
			 */
			*++d_byte = *++s_byte;
		}
		return dst;
		#else
			#define STRING_MEMCPY_NONE
		#endif /* !STRING_MEMCPY_X86_64 */
	#else
		#define STRING_MEMCPY_NONE
	#endif /* !STRING_MEMCPY_OPTIMAL */
	
	#ifdef STRING_MEMCPY_NONE
		#warning "[ccaprice] no optimized memcpy implementation, using naive method (could be slow)"
		unsigned char *dst8 = (unsigned char *)dst;
		unsigned char *src8 = (unsigned char *)src;
		if (dst8 < src8)
			while (cnt--)
				*dst8++ = *src8++;
		else {
			unsigned char *ls = src8+(cnt-1);
			unsigned char *ld = dst8+(cnt-1);
			while (cnt--)
				*(char*)ld-- = *(char*)ls--;
		}
		return dst;
	#endif /* !STRING_MEMCPY_OPTIMAL */
}
