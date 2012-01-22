#include "inc/stdlib.h"
#include "inc/stdio.h"
int main() {
	
	char v[255], *b = v, c;
	
	fputs ("Hello World", stdout);
	fflush(stdout);
	
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
