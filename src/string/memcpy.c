#include "inc/string.h"

void *memcpy(void *dst, const void *src, register size_t cnt)
{
	__asm__("cld; rep movsb" :: 
		"c"(cnt),
		"S"(src),
		"D"(dst)
	);
	 return dst;
}
