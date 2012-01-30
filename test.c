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
#include "inc/stdlib.h"
#include "inc/stdio.h"
#include "inc/ctype.h"
#include "inc/locale.h"
#include "inc/math.h"

#define TEST_DEF(NAME, CODE)                \
	NAME##_test() {                         \
		printf("Running test %s: ", #NAME); \
		CODE                                \
	}
#define TEST_RET(CONDITIONS) return (CONDITIONS);
#define TEST_TRY(NAME) printf("%s\n", NAME##_test()?"passed":"failed")

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
TEST_DEF(ilogb, {
	double f = 1024;
	int    i = ilogb(f);
	TEST_RET(i == 10);
})
TEST_DEF(ceil, {
	double f = 1024.654f;
	double t = ceil(1024);
	TEST_RET(t == 1024);
});

int main(int argc, char **argv, char **argp) {
	printf("Testing ...\n");
	
	printf("Printing all system enviroment variables\n");
	int  i = 0;
	while(*argp++ && *argp)
		printf("%05d:%s\n", ++i, *argp);
		
	printf("Determining system laanguage ...\n");
	char *l = getenv("LANG");
	if (l != NULL)
		printf("Language found: %s\n", l);
	else {
		printf("Failed to find language!\n");
		l = "C";
	}
		
	printf   ("Setting locale based on language %s\n", l);
	char *t = setlocale(LC_ALL, l);
	if (!t || strcmp(t,l) != 0)
		printf("Failed to set language to %s, locale not implemented yet?\n", l);
	else
		printf("Language succesfully switched to %s\n", l);
	
	TEST_TRY(abs);
	TEST_TRY(strstr);
	TEST_TRY(strspn);
	TEST_TRY(strpbrk);
	TEST_TRY(ilogb);
	TEST_TRY(ceil);
	
	printf("trying to print decmial value %f\n", 123.456f);
	printf("accepting input from user ... PLEASE ENTER SOMETHING\n");
	
	char  buffer[1024];
	char *bufptr = &buffer[0];
	char  inputs;
	while (inputs!='\n') {
		read(1, &inputs, 1);
		*bufptr++=inputs;
	}
	*bufptr--;        /* move backwards from '\0' */
	*bufptr-- = '\0'; /* remove '\n'              */
	printf("got input from stdin: %s\n", buffer);
	printf("now returning from main ...\n");
	return 0;
}
