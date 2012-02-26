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
#define CCAPRICE_EXTENSIONS /* Enable extensions in ccaprice */
#include "inc/stdlib.h"
#include "inc/stdio.h"
#include "inc/ctype.h"
#include "inc/locale.h"
#include "inc/math.h"

int PADD = 80;
#define TEST_DEF(NAME, CODE)                  \
	NAME##_test() {                           \
	    char  c[]= {                          \
	        "Running test " #NAME ":"         \
	    };                                    \
	    fwrite(c, strlen(c), 1, stdout);      \
	    fflush(stdout);                       \
	    size_t l=PADD-strlen(c);              \
	    while (l-->0) { fputc(' ', stdout); } \
	    CODE                                  \
	}
#define TEST_RET(CONDITIONS) return (CONDITIONS);
#define TEST_TRY(NAME) printf("%s\n", NAME##_test()?"\033[32mpassed\033[0m":"\033[31mfailed\033[0m")

TEST_DEF(abs, {
	int n = abs(+23);
	int m = abs(-11);	
	TEST_RET(n==23&&m==11);
})
TEST_DEF(strstr, {
	const char *needle = "stack";
	const char *haystk = "data for hay stack string";
	TEST_RET(strstr(haystk, needle));
})
TEST_DEF(strspn, {
	const char *txt = "129";
	const char *set = "1234567890";
	TEST_RET(strspn(txt, set) == 3);
})
TEST_DEF(strpbrk, {
	char        buf[10];
	char       *ptr     = &buf[0];
	const char *str     = "This is a sample string";
	const char *key     = "aeiou";
	char       *pch     = strpbrk(str, key);
	while (pch != NULL) {
		*ptr  = *pch;
		 pch  = strpbrk(pch+1, key);
		 ptr++;
	}
	TEST_RET(
		buf[0] == 'i' && buf[1] == 'i' &&
		buf[2] == 'a' && buf[3] == 'a' &&
		buf[4] == 'e' && buf[5] == 'i'
	);
})
TEST_DEF(file, {
	FILE  *fp = fopen("Output", "w"); 
	fputs("Output", fp);
	TEST_RET(!fclose(fp));
})
TEST_DEF(ilogb  ,  { TEST_RET(ilogb(1024) == 10  ); })
TEST_DEF(ceil   ,  { TEST_RET(ceil (1024) == 1024); })
TEST_DEF(floor  ,  { TEST_RET(floor(3.8)  == 03.0); })
TEST_DEF(atan   ,  { TEST_RET(floor(atan (1.0)*180/M_PI) == 45.0); })
TEST_DEF(toupper,  { TEST_RET(toupper('a') == 'A'); })
TEST_DEF(tolower,  { TEST_RET(tolower('A') == 'a'); })
TEST_DEF(remove ,  { TEST_RET(!remove("Output"));   })

#include <sys/ioctl.h>
int main(int argc, char **argv, char **argp) {
	struct winsize ws;
	ioctl(1, TIOCGWINSZ, &ws);
	PADD = ws.ws_col-6;
	
	int  i = 0;
	while(*argp++ && *argp)
		printf("%05d : \033[36m%s\033[0m\n", ++i, *argp);
		
	printf("\nCCAPRICE_BUILD_DATE: \033[33m%s\033[0m\n",   CCAPRICE_BUILD_DATE);
	printf(  "CCAPRICE_BUILD_INFO: \033[33m%s\033[0m\n",   CCAPRICE_BUILD_INFO);
	printf(  "CCAPRICE_BUILD_COMP: \033[33m%s\033[0m\n\n", CCAPRICE_BUILD_COMP);
	
	TEST_TRY(abs);
	TEST_TRY(strstr);
	TEST_TRY(strspn);
	TEST_TRY(strpbrk);
	TEST_TRY(ilogb);
	TEST_TRY(ceil);
	TEST_TRY(floor);
	TEST_TRY(atan);
	TEST_TRY(toupper);
	TEST_TRY(tolower);
	TEST_TRY(file);
	TEST_TRY(remove);
	
	return 0;
}
