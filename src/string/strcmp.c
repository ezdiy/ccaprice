#include "inc/string.h"

int strcmp(const char *s1, const char *s2) {
	
	while ((*s1 && *s2) && (*s1 == *s2)) {
			s1++;
			s2++;
	}
			
	return (int) *s1 - (int) *s2;
}

int strncmp(const char *s1, const char *s2, register size_t cnt) {
	
	register unsigned char ucb1;
	register unsigned char ucb2;
	
	while (cnt-->0) {
		ucb1 = (unsigned char) *s1++;
		ucb2 = (unsigned char) *s2++;
		
		if (ucb1 != ucb2) return ucb1-ucb2;
		if (ucb1 == '\0') return 0;
	}
	return 0;
}
