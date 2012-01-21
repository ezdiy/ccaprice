#include "inc/string.h"

int memcmp(const void *s1, const void *s2, register size_t cnt) {
	
	const unsigned char *s1p = (const unsigned char *) s1;
	const unsigned char *s2p = (const unsigned char *) s2;
	
	while (cnt-->0) {
		if (*s1p++!=*s2p++)
			return (s1p[-1] < s2p[-1])?-1:+1;
	}
	
	return 0;
}
