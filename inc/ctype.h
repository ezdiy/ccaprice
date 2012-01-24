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
#ifndef CCAPRICE_CTYPE_HDR
#define CCAPRICE_CTYPE_HDR
#include "ccaprice.h"
/*
 * Increase this number if more locales are ever required
 * There is a high probability this number will have to be
 * increased since there is simply too many languages and
 * varations of languages on this earth.  It seems like a
 * sad waste when we have English.  The universal everyone
 * likes language that is viable for any situation.  It's
 * a pity others don't learn it. Oh well who cares? No one
 * speaks properly these days, and many languages borrow
 * from each other.  For example English borrows a lot from
 * old latin.  I thought you should know this, it's nice to
 * learn something new and interesting while reading source
 * code comments.  Anyways go learn English if you can't
 * read this.
 */
#define CCAPRICE_LOCALE_MAX 512

/*
 * Standard says these need to be locale conformant
 * We'll use a structure to define the ctype locale
 * data.
 * 
 * Note: The only implemented locale is the default
 * C locale, future locales will come when required.
 */
typedef struct {
	int (*fn_isalnum) (int);
	int (*fn_isalpha) (int);
	int (*fn_iscntrl) (int);
	int (*fn_isdigit) (int);
	int (*fn_isgraph) (int);
	int (*fn_islower) (int);
	int (*fn_isprint) (int);
	int (*fn_ispunct) (int);
	int (*fn_isspace) (int);
	int (*fn_isupper) (int);
	int (*fn_isxdigit)(int);
	int (*fn_tolower) (int);
	int (*fn_toupper) (int);
} ccaprice_ctypes_t;

typedef struct {
	ccaprice_ctypes_t  ctype;
	const char        *ident; /* Name of the locale    */
} ccaprice_locale_t;

CCAPRICE_EXPORT ccaprice_locale_t ccaprice_localec;

#define isalnum(X)  (ccaprice_localec.ctype.fn_isalnum (X))
#define isalpha(X)  (ccaprice_localec.ctype.fn_isalpha (X))
#define iscntrl(X)  (ccaprice_localec.ctype.fn_iscntrl (X))
#define isdigit(X)  (ccaprice_localec.ctype.fn_iscntrl (X))
#define isgraph(X)  (ccaprice_localec.ctype.fn_isgraph (X))
#define islower(X)  (ccaprice_localec.ctype.fn_islower (X))
#define isprint(X)  (ccaprice_localec.ctype.fn_isprint (X))
#define ispunct(X)  (ccaprice_localec.ctype.fn_isprint (X))
#define isspace(X)  (ccaprice_localec.ctype.fn_isspace (X))
#define isupper(X)  (ccaprice_localec.ctype.fn_isupper (X))
#define isxdigit(X) (ccaprice_localec.ctype.fn_isxdigit(X))
#define tolower(X)  (ccaprice_localec.ctype.fn_tolower (X))
#define toupper(X)  (ccaprice_localec.ctype.fn_toupper (X))

#endif
