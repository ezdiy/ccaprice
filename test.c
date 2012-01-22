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
int main() {
	
	char v[255], *b = v, c;
	puts("Hello World");
	
	int *p = malloc(9000);
	*p = 100;
	free(p);
	
	while (c != '\n') {
		read (1, &c, 1);
		*b++ = c;
	}
	
	p = malloc(9000);
	*p = 101;
	FILE *fp = fopen("test.txt", "w");
	fputs(v, fp);
	fwrite(v, strlen(v), 1, fp);
	fwrite(&*p, sizeof(int), 1, fp);
	fclose(fp);
	free(p);
	
	return 0;
}
