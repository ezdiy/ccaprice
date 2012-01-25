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
#ifndef CCAPRICE_LOCALE_HDR
#define CCAPRICE_LOCALE_HDR
#include "ccaprice.h"
#include "inc/ctype.h"
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

#define LC_ALL      (1<<1)
#define LC_COLLATE  (1<<2)
#define LC_CTYPE    (1<<3)
#define LC_MONETARY (1<<4)
#define LC_NUMERIC  (1<<5)
#define LC_TIME     (1<<6)

/*
 * setlocale() depends on two paramaters:
 * 	-catageory
 * 	-locale
 *
 * The category specifes which parts of the
 * internal library change depending on the
 * selected locale.
 * 
 * The category can be any of the following
 * 	-LC_ALL       
 * 	-LC_COLLATE
 * 	-LC_CTYPE
 * 	-LC_MONETARY
 * 	-LC_NUMERIC
 * 	-LC_TIME
 * 
 * LC_ALL:      changes the behaviour of the entire locale
 * LC_COLLATE:  only affects the behaviour of strcoll, and strxfrm
 * LC_CTYPE:    changes the behaviour in <ctype.h>
 * LC_MONETARY  affects the monetary formatting returned by localeconv
 * LC_NUMERIC:  affects _ONLY_ the decimal point on I/O operations and
 *              non-monetary information returned by localeconv()
 * LC_TIME:     only changes the behaviour of strftime.
 * 
 * there is by default a "C" locale which is the minimal basic locale
 * specified by ccaprice. A null string ("") or NULL should select the
 * default enviroment locale.
 */
typedef struct lconv {
	 char *decimal_point;
	 char *thousands_sep;
	 char *grouping;
	 char *int_curr_symbol;
	 char *currency_symbol;
	 char *mon_decimal_point;
	 char *mon_thousands_sep;
	 char *mon_grouping;
	 char *positive_sign;
	 char *negative_sign;
	
	 char  int_fract_digits;
	 char  fract_digits;
	 char  p_cs_precedes;
	 char  n_cs_precedes;
	 char  p_sep_by_space;
	 char  n_sep_by_space;
	 char  p_sign_posn;
	 char  n_sign_posn;
} ccaprice_locale_c;

typedef struct {
	ccaprice_ctypes_t  ctype;
	struct lconv       lconv;
	const char        *ident; /* Name of the locale    */
} ccaprice_locale_t;

CCAPRICE_EXPORT ccaprice_locale_t* ccaprice_localec;

CCAPRICE_EXPORT struct lconv *localeconv();
CCAPRICE_EXPORT char         *setlocale (int, const char*);
#endif
