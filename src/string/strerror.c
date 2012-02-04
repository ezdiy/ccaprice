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
#include "inc/errno.h"
static const char *ccaprice_strerror[] = {
	[E2BIG]           = "Argument list too long",
	[EACCES]          = "Permission defined",
	[EADDRINUSE]      = "Address in use",
	[EADDRNOTAVAIL]   = "Address not available",
	[EAFNOSUPPORT]    = "Address family not supported",
	[EAGAIN]          = "Resource temporarily unavailable",
	[EALREADY]        = "Connection already in progress",
	[EBADF]           = "Bad file descriptor",
	[EBADMSG]         = "Bad message",
	[EBUSY]           = "Resource busy",
	[ECANCELED]       = "Operation canceled",
	[ECHILD]          = "No child process",
	[ECONNABORTED]    = "Connection aborted",
	[ECONNREFUSED]    = "Connection refused",
	[ECONNRESET]      = "Connection reset",
	[EDEADLK]         = "Resource deadlock",
	[EDESTADDRREQ]    = "Destination address required",
	[EDOM]            = "Domain error",
	[EDQUOT]          = "Reserved",
	[EEXIST]          = "File exists",
	[EFAULT]          = "Bad address",
	[EFBIG]           = "File too large",
	[EHOSTUNREACH]    = "Host is unreachable",
	[EIDRM]           = "Identifier removed",
	[EILSEQ]          = "Illegal byte sequence",
	[EINPROGRESS]     = "Operation in progress",
	[EINTR]           = "Interrupted function call",
	[EINVAL]          = "Invalid argument",
	[EIO]             = "Input/output error",
	[EISCONN]         = "Socket is connected",
	[EISDIR]          = "Is a directory",
	[EMFILE]          = "Too many open files",
	[EMLINK]          = "Too many links",
	[EMSGSIZE]        = "Message too large",
	[EMULTIHOP]       = "Reserved",
	[ENAMETOOLONG]    = "Filename too long",
	[ENETDOWN]        = "Network is down",
	[ENETRESET]       = "The connection was aborted by the network",
	[ENETUNREACH]     = "Network unreachable",
	[ENFILE]          = "Too many file open in system",
	[ENOBUFS]         = "No buffer space available",
	[ENODATA]         = "No message available",
	[ENODEV]          = "No such device",
	[ENOENT]          = "No such file or directory",
	[ENOEXEC]         = "Executable file format error",
	[ENOLCK]          = "No locks available",
	[ENOLINK]         = "Reserved",
	[ENOMEM]          = "Not enough space",
	[ENOMSG]          = "No message of the desired type",
	[ENOPROTOOPT]     = "Protocol not available",
	[ENOSPC]          = "No space left on a device",
	[ENOSR]           = "No STREAM resources",
	[ENOSTR]          = "Not a STREAM",
	[ENOSYS]          = "Function not implemented",
	[ENOTCONN]        = "Socket not connected",
	[ENOTDIR]         = "Not a directory",
	[ENOTEMPTY]       = "Directory not empty",
	[ENOTSOCK]        = "Not a socket",
	[ENOTSUP]         = "Not supported",
	[ENOTTY]          = "Inappropriate I/O control operation",
	[ENXIO]           = "No such device or address",
	[EOPNOTSUPP]      = "Operation not supported on socket",
	[EOVERFLOW]       = "Value too large to be stored in data type",
	[EPERM]           = "Operation not permitted",
	[EPIPE]           = "Broken pipe",
	[EPROTO]          = "Protocol error",
	[EPROTONOSUPPORT] = "Protocol not supported",
	[EPROTOTYPE]      = "Protocol wrong type for socket",
	[ERANGE]          = "Result too large or too small",
	[EROFS]           = "Read only file system",
	[ESPIPE]          = "Invalid seek",
	[ESRCH]           = "No such process",
	[ESTALE]          = "Reserved",
	[ETIME]           = "STREAM ioctl() timeout",
	[ETIMEDOUT]       = "Connection timed out",
	[ETXTBSY]         = "Text file busy",
	[EWOULDBLOCK]     = "Operation would block",
	[EXDEV]           = "Improper link"
};

char *strerror(int errnum) {
	if (errnum < E2BIG || errnum > EXDEV)
		errno = EINVAL;
		
	return (char*)ccaprice_strerror[errnum];
}
