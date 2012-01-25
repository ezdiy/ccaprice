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
#define STRN(X) #X
#define EXIT(X) void exit ## X (){puts("atexit called exit"STRN(X));}
EXIT(1) EXIT(2)
EXIT(3) EXIT(4)
EXIT(5) EXIT(6)
EXIT(7) EXIT(8)
EXIT(9) EXIT(10)
EXIT(11) EXIT(12)
EXIT(13) EXIT(14)
EXIT(15) EXIT(16)
EXIT(17) EXIT(18)
EXIT(19) EXIT(20)
int main(int argc, char **argv, char **argp) {
	atexit(&exit1);atexit(&exit2);
	atexit(&exit3);atexit(&exit4);
	atexit(&exit5);atexit(&exit6);
	atexit(&exit7);atexit(&exit8);
	atexit(&exit9);atexit(&exit10);
	atexit(&exit11);atexit(&exit12);
	atexit(&exit13);atexit(&exit14);
	atexit(&exit15);atexit(&exit16);
	atexit(&exit17);atexit(&exit18);
	atexit(&exit19);atexit(&exit20);
	char v[255], *b = v, c;
	puts("Hello World");
	puts(argv[0]);
	if (argv[1]) puts(argv[1]);
	
	size_t i = 0;
	while(argp[i] != 0)
		puts(argp[i]), i++;
	
	char buffer[] = "this is a buffer of data";
	
	char *pizzat = "pizza 2";
	char *pizzaf = "pi 1";
	
	if(strstr(pizzat, "pizza"))
		puts("pizza true pass");
	if(strstr(pizzaf, "pizza"))
		puts("pizza false true"); /* never print or bug!> */
	
	struct lconv *l = localeconv();
	puts(ccaprice_localec->ident);
	
	puts("trying en_US");
	setlocale(LC_ALL, "en_US");
	l = localeconv();
	puts("int_curr_symbol");
	puts(l->int_curr_symbol);
	
	puts("trying NULL (system locale)");
	setlocale(LC_ALL, NULL);
	l = localeconv();
	puts("int_curr_symbol");
	puts(l->int_curr_symbol);
	
	puts(buffer);
	char vv = 'v';
	char VV = toupper(vv);
	puts("the upper is: ");
	puts(&VV);
	
	char *mail = getenv("MAIL");
	puts("mail is: ");
	puts(mail);
	
	while (c != '\n') {
		read (1, &c, 1);
		*b++ = c;
	}
	
	FILE *fp = fopen("test.txt", "w");
	fputs(v, fp);
	fwrite(v, strlen(v), 1, fp);
	//fwrite(&*p, sizeof(int), 1, fp);
	fclose(fp);
	//free(p);
	
	return 0;
}
