#include "inc/stdlib.h"
#include "inc/assert.h"

#include <fcntl.h> 
int main() {
	
	char v[255], *b = v, c;
	puts("Hello World, This is the place to be");
	while (c != '\n') {
		read (1, &c, 1);
		*b++ = c;
	}
	int fd = open("test.txt", O_CREAT | O_RDWR);
	write(0, v, strlen(v));
	write(fd, v, strlen(v));
	close(fd);
	return 0;
}
