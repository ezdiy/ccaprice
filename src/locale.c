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
#include "inc/locale.h"

ccaprice_locale_t  ccaprice_localec;                      /* Current Selected Locale */
ccaprice_locale_t *ccaprice_locales = NULL;               /* Pointer to array below  */
ccaprice_locale_t  ccaprice_localed[CCAPRICE_LOCALE_MAX]; /* Array of Locales        */

#define LOCALE_INIT(N0)                         \
	extern ccaprice_locale_t N0##_locale_ctype; \
	ccaprice_locale_define (&N0##_locale_ctype)
	
#define LOCALE_DEFINE(                          \
	N00,N01,N02,N03,N04,N05,N06,N07,N08,N09,N10,\
	N11,N12,N13,N14,N15,N16,N17,N18,N19,N20,N21,\
	N22,N23,N24,N25,N26,N27,N28,N29,N30,N31     \
)                                               \
	static int N00##_isalnum (int c) {N01}      \
	static int N00##_isalpha (int c) {N02}      \
	static int N00##_iscntrl (int c) {N03}      \
	static int N00##_isdigit (int c) {N04}      \
	static int N00##_isgraph (int c) {N05}      \
	static int N00##_islower (int c) {N06}      \
	static int N00##_isprint (int c) {N07}      \
	static int N00##_ispunct (int c) {N08}      \
	static int N00##_isspace (int c) {N09}      \
	static int N00##_isupper (int c) {N10}      \
	static int N00##_isxdigit(int c) {N11}      \
	static int N00##_toupper (int c) {N12}      \
	static int N00##_tolower (int c) {N13}      \
	ccaprice_locale_t N00##_locale = {          \
	    .ctype = {                              \
	        .fn_isalnum  = &N00##_isalnum,      \
	        .fn_isalpha  = &N00##_isalpha,      \
	        .fn_iscntrl  = &N00##_iscntrl,      \
	        .fn_isdigit  = &N00##_isdigit,      \
	        .fn_isgraph  = &N00##_isgraph,      \
	        .fn_islower  = &N00##_islower,      \
	        .fn_isprint  = &N00##_isprint,      \
	        .fn_ispunct  = &N00##_ispunct,      \
	        .fn_isspace  = &N00##_isspace,      \
	        .fn_isupper  = &N00##_isupper,      \
	        .fn_isxdigit = &N00##_isxdigit,     \
	        .fn_toupper  = &N00##_toupper,      \
	        .fn_tolower  = &N00##_tolower       \
	    },                                      \
	    .lconv = {                              \
            N14,N15,N16,N17,N18,N19,N20,N21,N22,\
            N23,N24,N25,N26,N27,N28,N29,N30,N31 \
		},                                      \
	    .ident = #N00                           \
	}

void ccaprice_locale_define(ccaprice_locale_t *l) {
	if (!ccaprice_locales)
		ccaprice_locales = ccaprice_localed;
		
	ccaprice_locales = l;
	ccaprice_locales++;
}

/* Include locales here */
#include "inc/locale/C.h"

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

/*
 * Undefine this really nasty macro so people don't get
 * burnt in the near future.  It really should not be used
 * outside the scope of this file.
 */
#undef LOCALE_DEFINE
#undef LOCALE_INIT
