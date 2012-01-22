#include "inc/stdlib.h"
#include "inc/stdio.h"
int main() {
	
	char v[255], *b = v, c;
	
	//fputs ("Hello World\n", stdout);
	//fflush(stdout);
	puts("Hello World");
	
	int *p = malloc(9000);
	*p = 100;
	free(p);
	
	while (c != '\n') {
		read (1, &c, 1);
		*b++ = c;
	}
	FILE *fp = fopen("test.txt", "w");
	fputs(v, fp);
	fwrite(v, strlen(v), 1, fp);
	fclose(fp);
	
	return 0;
}
