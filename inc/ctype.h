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

/*
 * The macros below need access to an external global
 * ccaprice_localec locale object. thus the include.
 */
#include "inc/locale.h"

/*
 * I'm sure these can be made into functions but macros
 * are fine for now. Also I don't think the C standard
 * says anything about these not being allowed to be a
 * macro.  None the less this is applicable enough for
 * now.
 */
#define isalnum(X)  (ccaprice_localec->ctype.fn_isalnum (X))
#define isalpha(X)  (ccaprice_localec->ctype.fn_isalpha (X))
#define iscntrl(X)  (ccaprice_localec->ctype.fn_iscntrl (X))
#define isdigit(X)  (ccaprice_localec->ctype.fn_iscntrl (X))
#define isgraph(X)  (ccaprice_localec->ctype.fn_isgraph (X))
#define islower(X)  (ccaprice_localec->ctype.fn_islower (X))
#define isprint(X)  (ccaprice_localec->ctype.fn_isprint (X))
#define ispunct(X)  (ccaprice_localec->ctype.fn_isprint (X))
#define isspace(X)  (ccaprice_localec->ctype.fn_isspace (X))
#define isupper(X)  (ccaprice_localec->ctype.fn_isupper (X))
#define isxdigit(X) (ccaprice_localec->ctype.fn_isxdigit(X))
#define tolower(X)  (ccaprice_localec->ctype.fn_tolower (X))
#define toupper(X)  (ccaprice_localec->ctype.fn_toupper (X))

#endif
