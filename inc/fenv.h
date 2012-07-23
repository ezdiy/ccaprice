/*
 * Copyright (C) 2012
 *  Dale Weiler
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
#ifndef __CCAPRICE_FENV_HDR__
#define __CCAPRICE_FENV_HDR__

#ifdef __cplusplus
extern "C" {
#endif
    
#include <ccaprice.h>
#include <bits/fenv.h>

__CCAPRICE_EXPORT int feclearexcept  (int);
__CCAPRICE_EXPORT int feraiseexcept  (int);

__CCAPRICE_EXPORT int fegetexceptflag(fexcept_t*, int);
__CCAPRICE_EXPORT int fesetexceptflag(const fexcept_t*, int);
__CCAPRICE_EXPORT int fetestexcept   (int);
__CCAPRICE_EXPORT int fesetround     (int);
__CCAPRICE_EXPORT int fegetround     ();

__CCAPRICE_EXPORT int fegetenv       (fenv_t*);
__CCAPRICE_EXPORT int feholdexcept   (fenv_t*);

__CCAPRICE_EXPORT int fesetenv       (const fenv_t*);
__CCAPRICE_EXPORT int feupdateenv    (const fenv_t*);

#ifdef __cplusplus
}
#endif

#endif
