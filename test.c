#include "inc/stdlib.h"
#include "inc/assert.h"

int main() {
	
	char v[255], *b = v, c;
	puts("Hello World, This is the place to be");
	while (c != '\n') {
		read (1, &c, 1);
		*b++ = c;
	}
	write(0, v, strlen(v));
	return 0;
}
