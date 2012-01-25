/*
 * Copyright (C) 2012 
 * 	Dale Weiler
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "inc/string.h"
CCAPRICE_INTERNAL_TYPE(unsigned char, ccaprice_strspn_cycle);
CCAPRICE_INTERNAL_TYPE(unsigned char, ccaprice_strspn_table[0xFF]);
CCAPRICE_INTERNAL_FUNC(void,          ccaprice_strspn_init, (const unsigned char *, int));

size_t strcspn(const char *src, const char *reg) {
	const unsigned char *s = (const unsigned char*)src;
	
	size_t i;
	ccaprice_strspn_init((const unsigned char*)reg, 1);
	for (i = 0; ccaprice_strspn_table[s[i]] != ccaprice_strspn_cycle; i++);
		
	return i;
}
