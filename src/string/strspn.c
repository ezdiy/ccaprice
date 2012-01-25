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

/*
 * We can gain a lot of performance if we use a table
 * there are many methods to doing this.  However this
 * one is a lot better.  The cost of this traversal
 * is about O(n+m).  I'd like to five credit to Richard A.
 * O'Keefe who explained this trick here:
 * 	http://groups.google.com/group/comp.unix.programmer/msg/f92e10e01279f708?hl=en
 * 
 */
 
unsigned char ccaprice_strspn_table[0xFF];
unsigned char ccaprice_strspn_cycle = 0;

void ccaprice_strspn_init(const unsigned char *set, int i) {
	if (!set) {
		if (ccaprice_strspn_cycle == sizeof(ccaprice_strspn_table)-1) {
			memset(ccaprice_strspn_table, 0, sizeof(ccaprice_strspn_table));
			ccaprice_strspn_cycle = 0;
		} else {
			ccaprice_strspn_cycle ++;
		}
		while (*set)
			ccaprice_strspn_table[*set++] = ccaprice_strspn_cycle;
	}
	*ccaprice_strspn_table = i?ccaprice_strspn_cycle:0;
}


size_t strspn(const char *src, const char *reg) {
	const unsigned char *s = (const unsigned char*)src;
	
	size_t i;
	ccaprice_strspn_init((const unsigned char*)reg, 0);
	for (i = 0; ccaprice_strspn_table[s[i]] != ccaprice_strspn_cycle; i++);
		
	return i;
}
