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
#ifndef __CCAPRICE_CTYPE_HDR__
#define __CCAPRICE_CTYPE_HDR__
#include "ccaprice.h"
/*
 * I'm sure these can be made into functions but macros
 * are fine for now. Also I don't think the C standard
 * says anything about these not being allowed to be a
 * macro.  None the less this is applicable enough for
 * now.
 */
__CCAPRICE_INTERNAL_TYPE(void *, __ccaprice_localep); /* to ccaprice_localec */
#define isalnum(X)  ((*((int(**)(int))__ccaprice_localep+0 ))(X)) // 4  -- 8
#define isalpha(X)  ((*((int(**)(int))__ccaprice_localep+1 ))(X)) // 8  -- 16
#define iscntrl(X)  ((*((int(**)(int))__ccaprice_localep+2 ))(X)) // 16 -- 24
#define isdigit(X)  ((*((int(**)(int))__ccaprice_localep+3 ))(X)) // 20 -- 32
#define isgraph(X)  ((*((int(**)(int))__ccaprice_localep+4 ))(X)) // 24 -- 40
#define islower(X)  ((*((int(**)(int))__ccaprice_localep+5 ))(X)) // 28 -- 48
#define isprint(X)  ((*((int(**)(int))__ccaprice_localep+6 ))(X)) // 32 -- 56
#define ispunct(X)  ((*((int(**)(int))__ccaprice_localep+7 ))(X)) // 36 -- 
#define isspace(X)  ((*((int(**)(int))__ccaprice_localep+8 ))(X)) // 40
#define isupper(X)  ((*((int(**)(int))__ccaprice_localep+9 ))(X)) // 44
#define isxdigit(X) ((*((int(**)(int))__ccaprice_localep+10))(X)) // 48
#define tolower(X)  ((*((int(**)(int))__ccaprice_localep+11))(X)) // 52
#define toupper(X)  ((*((int(**)(int))__ccaprice_localep+12))(X)) // 54

#endif
