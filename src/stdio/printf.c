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
#include "inc/stdarg.h"
#include "inc/stddef.h"
#include "inc/stdlib.h"
#include "inc/stdio.h"
#include "inc/stdint.h"
static int __ccaprice_printf_extract(uint64_t *x, uint32_t radix) {
    uint32_t hi  = *x >> 32;
    uint32_t lo  = *x;
    uint32_t mod = hi % radix; hi /= radix;
    uint32_t n   = (mod<<16)|(lo>>16);
    mod =  n % radix; n  /= radix;
    lo  = (mod << 16) | (lo & 0xffff);
    mod = lo % radix; lo /= radix;
    lo |= (n << 16);
    *x  = ((uint64_t)hi<<32)|lo;
    return mod;
}

int printf(const char *format, ...) {
    va_list  ap;
    va_start(ap, format);

    while (*format) {
        int zero      = 0x00;
        int prec      = 0x00;
        int ll        = 0x00;
        int radix     = 0x0A;
        int is_signed = 0x01;

        if (*format != '%') {
            fputc(*format++, stdout);
            continue;
        }
        if (*++format == '0')
            zero = 1, format++;
        while (*format >= '0' && *format <= '9')
            prec = 10 * prec +  (*format++- '0');
        while (*format == 'l')
            ll++, format++;

        switch (*format++) {
            case '%': fputc('%',                stdout); break;
            case 'c': fputc(va_arg(ap, int)   , stdout); break;
            case 's': fputs(va_arg(ap, char *), stdout); break;
            case 'f': ;
                double f = va_arg(ap, double);
                int   ip =  (int)f;
                int   dp = ((int)(f*1000)%1000); // 3 decmials only
                printf("%d.%d", ip, dp);
                break;
            case 'x': radix     = 16;
            case 'u': is_signed = 00;
            case 'd': ;
                uint64_t x = (is_signed) ? (
                        (ll == 0)?(va_arg(ap, int               )) : (
                        (ll == 1)?(va_arg(ap, long              )) : (
                                   va_arg(ap, long long         )))
                    ):(
                        (ll == 0)?(va_arg(ap, unsigned int      )) : (
                        (ll == 1)?(va_arg(ap, unsigned long     )) : (
                                   va_arg(ap, unsigned long long)))
                    );

                if (is_signed) {
                    if ((long long)x<0) x         = -x;
                    else                is_signed =  0;
                }

                char  vld[22];
                char *hld = &vld[sizeof(vld)]; *--hld = 0;
                int   len = 0;
                do {
                    int dig  = __ccaprice_printf_extract(&x, radix);
                    if (dig >= 10) dig += 'a' - 10;
                    else           dig += '0';

                    *--hld = dig, len++;
                } while(x);

                if (is_signed)
                    *--hld = '-';
                while (len++ < prec)
                    fputc(zero ? '0' : ' ', stdout);
                fputs(hld, stdout);
        }
    }
    fflush(stdout);
    va_end(ap);
    return 0;
}
