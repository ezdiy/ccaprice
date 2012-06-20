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
#include "inc/string.h"
void *memcpy(void *dst, const void *src, register size_t cnt) {
    #if defined(__STRING_MEMCPY_OPTIMAL) && (defined(__CCAPRICE_TARGET_X86_64) || defined(__CCAPRICE_TARGET_X86_32)) && !defined(__STRING_MEMCPY_OPTIMAL_SSE2)
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
    #elif defined(__STRING_MEMCPY_OPTIMAL_SSE2)
        /*
         * Some systems rep movs is not optimized to microcode.
         * Expecially some mobile CPU's.  So we need a better method.
         * I've tried using SSE intrinsics here, but this works faster.
         * The compiler doesn't seem to generate the assembly I want from
         * using intrinsics, this works perffectly.
         */
        void * ret = dst;
        size_t itr;

        /*
         * Prefetch for MOVSB:
         *     this actually gains  some  speed in
         *     most situations for some odd reason.
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
                        "=&D"(dst), "=&S"(src), "=&c"(dum) :
                          "0"(dst),   "1"(src),   "2"(dla) : "memory"
                );
            }

            itr  = cnt>>6;
            cnt &= 63;

            /* source is misaligned */
            if (((unsigned long)src)&15) {
                for (; itr>0; itr--) {
                    __asm__ __volatile__ (
                        "prefetchnta 320(%0)   \n\t"
                        "prefetchnta 352(%0)   \n\t"

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
                        "prefetchnta 320(%0)   \n\t"
                        "prefetchnta 352(%0)   \n\t"

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
                        "=&D"(dst), "=&S"(src), "=&c"(dum) :
                          "0"(dst),   "1"(src),   "2"(cnt) : "memory"
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
    #endif

    #ifdef __STRING_MEMCPY_NONE
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
