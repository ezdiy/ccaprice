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
#ifndef  __CCAPRICE_WCHAR_HDR__
#define  __CCAPRICE_WCHAR_HDR__

#ifdef __cplusplus
extern "C" {
#endif

#include <ccaprice.h>
#include <bits/types.h> /* wchar_t, size_t */

__CCAPRICE_EXPORT wchar_t *wcschr (const wchar_t *, wchar_t);
__CCAPRICE_EXPORT wchar_t *wcsrchr(const wchar_t *, wchar_t);
__CCAPRICE_EXPORT size_t   wcslen (const wchar_t *);
__CCAPRICE_EXPORT wchar_t *wcscpy (wchar_t *, const wchar_t*);

#ifdef __cplusplus
}
#endif
#endif
