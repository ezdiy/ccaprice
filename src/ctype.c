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
#include "inc/ctype.h"

ccaprice_locale_t  ccaprice_localec;                      /* Current Selected Locale */
ccaprice_locale_t *ccaprice_locales = NULL;               /* Pointer to array below  */
ccaprice_locale_t  ccaprice_localed[CCAPRICE_LOCALE_MAX]; /* Array of Locales        */

#define LOCALE_INIT(N0)                    \
	extern ccaprice_locale_t N0##_locale;  \
	ccaprice_locale_define (&N0##_locale)
#define LOCALE_DEFINE(N0,N1,N2,N3,N4,N5,N6,N7,N8,N9,N10,N11,N12,N13)  \
	static int N0##_isalnum (int c) {N1}      \
	static int N0##_isalpha (int c) {N2}      \
	static int N0##_iscntrl (int c) {N3}      \
	static int N0##_isdigit (int c) {N4}      \
	static int N0##_isgraph (int c) {N5}      \
	static int N0##_islower (int c) {N6}      \
	static int N0##_isprint (int c) {N7}      \
	static int N0##_ispunct (int c) {N8}      \
	static int N0##_isspace (int c) {N9}      \
	static int N0##_isupper (int c) {N10}     \
	static int N0##_isxdigit(int c) {N11}     \
	static int N0##_toupper (int c) {N12}     \
	static int N0##_tolower (int c) {N13}     \
	ccaprice_locale_t N0##_locale = {         \
	    .ctype = {                            \
	        .fn_isalnum  = &N0##_isalnum,     \
	        .fn_isalpha  = &N0##_isalpha,     \
	        .fn_iscntrl  = &N0##_iscntrl,     \
	        .fn_isdigit  = &N0##_isdigit,     \
	        .fn_isgraph  = &N0##_isgraph,     \
	        .fn_islower  = &N0##_islower,     \
	        .fn_isprint  = &N0##_isprint,     \
	        .fn_ispunct  = &N0##_ispunct,     \
	        .fn_isspace  = &N0##_isspace,     \
	        .fn_isupper  = &N0##_isupper,     \
	        .fn_isxdigit = &N0##_isxdigit,    \
	        .fn_toupper  = &N0##_toupper,     \
	        .fn_tolower  = &N0##_tolower      \
	    },                                    \
	    .ident = #N0                          \
	}

void ccaprice_locale_define(ccaprice_locale_t *l) {
	if (!ccaprice_locales)
		ccaprice_locales = ccaprice_localed;
		
	ccaprice_locales = l;
	ccaprice_locales++;
}

void ccaprice_locale_init() {
	/*
	 * Add LOCALE initializations here so ccaprice
	 * can add the locale into it self for usage.
	 */
	LOCALE_INIT(C);
	
	/*
	 * This is no to be changed, this sets the DEFAULT
	 * locale used by ccaprice.  This is the _DEFAULT_
	 * locale, DO NOT TOUCH.
	 */
	ccaprice_localec = C_locale;
}

/* Include locales here */
#include "inc/locale/C.h"

/*
 * Undefine this really nasty macro so people don't get
 * burnt in the near future.  It really should not be used
 * outside the scope of this file.
 */
#undef LOCALE_DEFINE
#undef LOCALE_INIT
