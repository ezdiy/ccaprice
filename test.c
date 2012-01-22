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
