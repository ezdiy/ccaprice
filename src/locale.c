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
#include "inc/string.h"
#include "inc/stdlib.h"

ccaprice_locale_t *ccaprice_localec;                      /* Current Selected Locale */
ssize_t            ccaprice_locales = 0;                  /* Location in locales     */
ccaprice_locale_t  ccaprice_localed[CCAPRICE_LOCALE_MAX]; /* Array of Locales        */

#define LOCALE_INIT(N0) \
	ccaprice_locale_define (&N0##_locale)
#define LOCALE_INT LOCALE_INIT
#define LOCALE_DEFINE(                          \
	N00,N01,N02,N03,N04,N05,N06,N07,N08,N09,N10,\
	N11,N12,N13,N14,N15,N16,N17,N18,N19,N20,N21,\
	N22,N23,N24,N25,N26,N27,N28,N29,N30,N31,N32 \
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
    static ccaprice_locale_t N00##_locale = {   \
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
        .ident = #N00 N32                       \
    }

void ccaprice_locale_define(ccaprice_locale_t *l) {
	ccaprice_localed[ccaprice_locales] = *l;
	ccaprice_locales ++;
}

#define LOCALE_CODEPAGE_ISO88591 "" /* ascii should be nothing */
#define LOCALE_CODEPAGE_UTF8     ".utf8"
#define LOCALE_CODEPAGE_IBM850   ".ibm-850"

/*
 * This locale always gets included it's the default locale
 * for ccarpice. It's known as the "C" locale in the standard.
 */
#include "inc/locale/C.h"

/*
 * If all locale support is selected we'll include ALL
 * locales.  This takes up a insane amount of code space
 * because these are STATICALLY stored in the library.
 * 
 * Most of the time the library should only be compiled for
 * the target locale.
 */
#ifndef CCAPRICE_LOCALE_SET
	/*
	 * We should warn the person compiling that all locales are
	 * being built into the library since he/she did not specify
	 * which locale to use for the build.
	 */
	#warning "[ccaprice] No locale specified for CCAPRICE_LOCALE_SET compiling with all locales, this could take a lot of space"
	#include "inc/locale/en_US.h"
	#include "inc/locale/en_CA.h"
	#include "inc/locale/en_AU.h"
#else
	/*
	 * This just includes one LOCALE, the one set by CCAPRICE_LOCALE_SET
	 * the build file could search for this localed by checking the LANG
	 * enviroment variable.
	 */
	#undef   LOCALE_INT
	#define  LOCALE_INT(X)                   LOCALE_INIT ( X )  
	#define  LOCALE_STR(X)                   #X
	#define  LOCALE_INC(X)                   LOCALE_STR(inc/locale/X.h)
	#include LOCALE_INC(CCAPRICE_LOCALE_SET)
	#undef   LOCALE_STR
	#undef   LOCALE_INC
#endif
#undef LOCALE_CODEPAGE_IBM850   /* ????? */
#undef LOCALE_CODEPAGE_UTF8     /* UTF8  */
#undef LOCALE_CODEPAGE_ISO88591 /* ASCII */

void ccaprice_locale_init() {
	LOCALE_INIT(C);
	
	/*
	 * Add LOCALE initializations here so ccaprice
	 * can add the locale into it self for usage.
	 */
	#ifndef CCAPRICE_LOCALE_SET
		LOCALE_INT(en_US);
		LOCALE_INT(en_CA);
		LOCALE_INT(en_AU);
	#else
		LOCALE_INT(CCAPRICE_LOCALE_SET);
	#endif
	
	/*
	 * This is not to be changed, this sets the DEFAULT
	 * locale used by ccaprice.  This is the _DEFAULT_
	 * locale, DO NOT TOUCH.
	 */
	ccaprice_localec = &ccaprice_localed[0];
}

/*
 * Undefine this really nasty macro so people don't get
 * burnt in the near future.  It really should not be used
 * outside the scope of this file.
 */
#undef LOCALE_DEFINE
#undef LOCALE_INIT
#undef LOCALE_INT

/*
 * setlocale sets  the  specified  locale given an input name
 * the input  name  is  based on  the LOCALE_INIT()  name  as
 * seen above in ccaprice_locale_init(), as  well as the code
 * page type ".utf-8" for example.  Demostration if we wanted
 * to load the en_US.utf-8 locale one would pass "en_US.utf-8"
 * for the locale argument.
 */
char *setlocale(int cat, const char *cap) {
	
	/*
	 * Get the current locale from the system via
	 * getenv("LANG"). of no caption is specified
	 */
	if (!cap) {
		char *locale = getenv("LANG");
		if  (!locale) {
			/* No LANG set in enviroment .. BAIL */
			return NULL;
		}
		/*
		 * Search ccaprice locales for locale based
		 * on one in enviroment.
		 */
		size_t i;
		for (i = 0; i < ccaprice_locales; i++) {
			if (!strcmp(locale, ccaprice_localed[i].ident)) {
				ccaprice_localec = &ccaprice_localed[i];
				return locale;
			}
		}
		/*
		 * We've made it here which suggests a locale could
		 * not be found for the specificed request.  Try looking
		 * for something else simaler.  Perhaps non-UTF8?
		 */
		
		/* Truncate the string before the . */
		locale[strchr(locale,'.')-locale] = '\0';
		
		/*
		 * Lets try searching again this time we might find something
		 * suitable as an alternitive.
		 */
		for (i = 0; i < ccaprice_locales; i++) {
			if (!strcmp(locale, ccaprice_localed[i].ident)) {
				ccaprice_localec = &ccaprice_localed[i];
				return (char*)ccaprice_localed[i].ident;
			}
		}
		/*
		 * We could not find anything, bail, looks like the user doesn't
		 * speak at all. Perhaps he's mute or worse a caveman.  We should
		 * probably just return NULL.
		 */
		return NULL;
	}
	/* 
	 * Search for locale in list of all locales.
	 * This could be made a lot faster with a hash
	 * table or something of that nature. TODO!
	 */
	size_t i;
	for (i=0; i < ccaprice_locales; i++) {
		if (!strcmp(cap, ccaprice_localed[i].ident)) {
			ccaprice_localec = &ccaprice_localed[i];
			return (char*)cap;
			break;
		}
	}
	return NULL;
}

/*
 * Retrives the current lconv structure from the current selected
 * locale.  One recently set by the user via setlocale() or, one
 * set by ccaprice by default "C"
 */
struct lconv *localeconv() {
	return &ccaprice_localec->lconv;
}
