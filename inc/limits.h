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
#ifndef __CCAPRICE_LIMITS_HDR__
#define __CCAPRICE_LIMITS_HDR__
/*
 * Macro to make min constants universal.  This determins min sizes from
 * max sizes (which are platform specific).
 */
#define __CCAPRICE_MIN(X) ((-X##_MAX)-1)

/*
 * Universal min constants; we don't specify CHAR here because of the, odd
 * cases where compile compilers support -unsigned-char and define a macro
 * which overrides the constants.
 */
#	define  SHRT_MIN	__CCAPRICE_MIN(SHRT)
#	define  SCHAR_MIN	__CCAPRICE_MIN(SCHAR)
#	define  LLONG_MIN	__CCAPRICE_MIN(LLONG)
#	define  INT_MIN		__CCAPRICE_MIN(INT)

#ifdef __CCAPRICE_TARGET_X86_64
#	define LONG_MAX   0x7FFFFFFFFFFFFFFFL
#	define LLONG_MAX  0x7FFFFFFFFFFFFFFFLL
#	define LONG_BIT   64
#	define CHAR_BIT   8
	/*
	 * GCC and GCC like compilers when used with -unsigned-char flag define
	 * a special constant __CHAR_UNSIGNED__ that needs to modify the behaviour
	 * of the following constants below.
	 */
#	ifdef __CHAR_UNSIGNED__
#		define	CHAR_MAX UCHAR_MAX
#		define	CHAR_MIN 0
#	else
#		define	CHAR_MAX SCHAR_MAX
#		define	CHAR_MIN SCHAR_MIN
#	endif
#	define	SCHAR_MAX    0x7F
#	define	UCHAR_MAX    0xFFU
#	define	USHRT_MAX    0xFFFFU
#	define	SHRT_MAX     0x7FFF
#	define	UINT_MAX     0xFFFFFFFFU
#	define	INT_MAX      0x7FFFFFFF
#	define	ULLONG_MAX   0xFFFFFFFFFFFFFFFFULL
#	define	LLONG_MAX    0x7FFFFFFFFFFFFFFFLL
#elif defined(CCAPRICE_TARGET_X86_32)
#	define LONG_MAX      0x7FFFFFFFL
#	define LLONG_MAX     0x7FFFFFFFFFFFFFFLL
#	define LONG_BIT      32
#	define CHAR_BIT      8
	/*
	 * GCC and GCC like compilers when used with -unsigned-char flag define
	 * a special constant __CHAR_UNSIGNED__ that needs to modify the behaviour
	 * of the following constants below.
	 */
#	ifdef __CHAR_UNSIGNED__
#		define	CHAR_MAX UCHAR_MAX
#		define	CHAR_MIN 0
#	else
#		define	CHAR_MAX SCHAR_MAX
#		define	CHAR_MIN SCHAR_MIN
#	endif
#	define  SCHAR_MAX    0x7F
#	define  UCHAR_MAX    0xFF
#	define  USHRT_MAX    0xFFFF
#	define  SHRT_MAX     0x7FFF
#	define  UINT_MAX     0xFFFFFFFFU
#	define  INT_MAX      0x7FFFFFFF
#	define  ULLONG_MAX   0xFFFFFFFFFFFFFFFFULL
#	define	LLONG_MAX    0x7FFFFFFFFFFFFFFFLL
#endif

/*
 * More universal constants follow:
 * only define SSIZE_MAX if we're not defined as _ANSI_SOURCE
 */
#if !defined(_ANSI_SOURCE)
#	define SSIZE_MAX    INT_MAX
#endif

/*
 * Don't allow into the global namespace. We don't need this anymore
 * though technically it's not in the global namespace as it's prefixed
 * with two underscores.
 */
#undef __CCAPRICE_MIN
#endif
