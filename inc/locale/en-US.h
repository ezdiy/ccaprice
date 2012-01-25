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
static const char en_US_data [257] = {
	0x00,
	0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
	0x20,0x28,0x28,0x28,0x28,0x28,0x20,0x20,
	0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
	0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
	0x88,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
	0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
	0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,
	0x04,0x04,0x10,0x10,0x10,0x10,0x10,0x10,
	0x10,0x41,0x41,0x41,0x41,0x41,0x41,0x01,
	0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
	0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
	0x01,0x01,0x01,0x10,0x10,0x10,0x10,0x10,
	0x10,0x42,0x42,0x42,0x42,0x42,0x42,0x02,
	0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,
	0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,
	0x02,0x02,0x02,0x10,0x10,0x10,0x10,0x20
};

/*
 * Locale creation is dead simple; create a new locale file like this
 * one in /inc/locale.  Copy this and change the name, and functions
 * to meet the critera for your locale.  After you're finished add a
 * #include "inc/locale/[yourlocale.h]" inside "src/locale.c". Then add
 * a LOCALE_INIT([yourlocale]); inside ccaprice_locale_init() as well
 * inside "src/locale.c" and you're finished.
 * 
 * The integral value for the charcater passed into the functions
 * is of name `c`, type lvalue int.
 *
 * you can use already specified locale specific functions inside the
 * use of another function by using the name as a prefix.  For example
 * C_isupper, and C_islower.  They DO need to created before the usage
 * i.e isalnum can't use tolower.
 */
LOCALE_DEFINE(en_US,
	{/*isalnum */ return en_US_data[(unsigned char)(c+1)]&0x07; },
	{/*isalpha */ return en_US_data[(unsigned char)(c+1)]&0x03; },
	{/*iscntrl */ return en_US_data[(unsigned char)(c+1)]&0x20; },
	{/*isdigit */ return en_US_data[(unsigned char)(c+1)]&0x04; },
	{/*isgraph */ return en_US_data[(unsigned char)(c+1)]&0x17; },
	{/*islower */ return en_US_data[(unsigned char)(c+1)]&0x02; },
	{/*isprint */ return en_US_data[(unsigned char)(c+1)]&0x57; },
	{/*ispunct */ return en_US_data[(unsigned char)(c+1)]&0x10; },
	{/*isspace */ return en_US_data[(unsigned char)(c+1)]&0x08; },
	{/*isupper */ return en_US_data[(unsigned char)(c+1)]&0x01; },
	{/*isxdigit*/ return en_US_data[(unsigned char)(c+1)]&0x80; },
	{/*tolower */ return en_US_islower(c)?(c-'a'+'A'):c; },
	{/*toupper */ return en_US_isupper(c)?(c-'A'+'a'):c; },
	
	/*decimal_point    */ ".",
	/*thousands_sep    */ ",",
	/*grouping         */ "3",
	/*int_curr_symbol  */ "USD",
	/*currency_symbol  */ "$",
	/*mon_decimal_point*/ ".",
	/*mon_thousands_sep*/ ",",
	/*mon_grouping     */ "\3",
	/*positive_sign    */ "+",
	/*negative_sign    */ "-",
	/*int_fract_digits */ 2,
	/*fract_digits     */ 2,
	/*p_cs_precedes    */ 1,
	/*n_cs_precedes    */ 1,
	/*p_sep_by_space   */ 2,
	/*n_sep_by_space   */ 2,
	/*p_sign_posn      */ 3,
	/*n_sign_posn      */ 3,
	
	LOCALE_CODEPAGE_ISO88591
);
