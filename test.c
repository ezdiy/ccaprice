#include "inc/stdlib.h"
#include "inc/assert.h"

int main() {
	char  *test = "Hello World, This is the place to be :D\n";
	int    size = strlen(test);
	write(0, test, size);
	return 0;
}
