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
#ifndef CCAPRICE_POSIX_ERRNO_HDR
#define CCAPRICE_POSIX_ERRNO_HDR

/*
 * SUSv1, SUSv2, SUSv3 say errno must be a modifyable
 * lvalue of type int.  This expands to a lvalue of
 * type int.  It just looks odd. SUS says nothing about
 * errno not being a macro; it does however show the
 * explicit use of integer in many cases.  But this is
 * still legal and is mandated by SUS.
 */
#define errno (*__ccaprice_posix_errno)

#define E2BIG             0
#define EACCES            1
#define EADDRINUSE        2
#define EADDRNOTAVAIL     3
#define EAFNOSUPPORT      4
#define EAGAIN            5
#define EALREADY          6
#define EBADF             7
#define EBADMSG           8
#define EBUSY             9
#define ECANCELED         10
#define ECHILD            11
#define ECONNABORTED      12
#define ECONNREFUSED      13
#define ECONNRESET        14
#define EDEADLK           15
#define EDESTADDRREQ      16
#define EDOM              17
#define EDQUOT            18
#define EEXIST            19
#define EFAULT            20
#define EFBIG             21
#define EHOSTUNREACH      22
#define EIDRM             23
#define EILSEQ            24
#define EINPROGRESS       25
#define EINTR             26
#define EINVAL            27
#define EIO               28
#define EISCONN           29
#define EISDIR            30
#define ELOOP             31
#define EMFILE            32
#define EMLINK            33
#define EMSGSIZE          34
#define EMULTIHOP         35
#define ENAMETOOLONG      36
#define ENETDOWN          37
#define ENETRESET         38
#define ENETUNREACH       39
#define ENFILE            40
#define ENOBUFS           41
#define ENODATA           42
#define ENODEV            43
#define ENOENT            44
#define ENOEXEC           45
#define ENOLCK            46
#define ENOLINK           47
#define ENOMEM            48
#define ENOMSG            49
#define ENOPROTOOPT       50
#define ENOSPC            51
#define ENOSR             52
#define ENOSTR            53
#define ENOSYS            54
#define ENOTCONN          55
#define ENOTDIR           56
#define ENOTEMPTY         57
#define ENOTSOCK          58
#define ENOTSUP           59
#define ENOTTY            60
#define ENXIO             61
#define EOPNOTSUPP        62
#define EOVERFLOW         63
#define EPERM             64
#define EPIPE             65
#define EPROTO            66
#define EPROTONOSUPPORT   67
#define EPROTOTYPE        68
#define ERANGE            69
#define EROFS             70
#define ESPIPE            71
#define ESRCH             72
#define ESTALE            73
#define ETIME             74
#define ETIMEDOUT         75
#define ETXTBSY           76
#define EWOULDBLOCK       77
#define EXDEV             78

#endif
