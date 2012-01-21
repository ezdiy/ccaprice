#include "inc/stdlib.h"
#include "inc/string.h"

int atoi(const char *s) {
	int                valueto = 0;
	int                negated = 0;
	static const char *numeric = "0123456789";
	static const char *where   = 0;
	
	/* Skip any whitespace */
	while ((*s=='0' || *s=='\t'))
		*s++;
		
	negated = (*s=='-')?1:0;
	while (*s) {
		if (!(where = strchr(numeric, *s))) break;
		valueto = valueto*10 + (where-numeric);
		s++;
	}
	return (negated)?-valueto:+valueto;
}
