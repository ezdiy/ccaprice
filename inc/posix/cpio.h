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
#ifndef __CCAPRICE_POSIX_CPIO_HDR__
#define __CCAPRICE_POSIX_CPIO_HDR__
#define MAGIC    "070707"

#define C_IRUSR  0000400 /* Read by owner      */
#define C_IWUSR  0000200 /* Write by owner     */
#define C_IXUSR  0000100 /* Execute by owner   */
#define C_IRGRP  0000040 /* Read by group      */
#define C_IWGRP  0000020 /* Write by group     */
#define C_IXGRP  0000010 /* Execute by group   */
#define C_IROTH  0000004 /* Read by others     */
#define C_IWOTH  0000002 /* Write by others    */
#define C_IXOTH  0000001 /* Execute by others  */
#define C_ISUID  0004000 /* Set user ID        */
#define C_ISGID  0002000 /* Set group ID       */
#define C_ISVXT  0001000 /* Restricted delflag */
#define C_ISDIR  0040000 /* Directory          */
#define C_ISFIFO 0010000 /* FIFO               */
#define C_ISREG  0100000 /* Regular file       */
#define C_ISBLK  0060000 /* Block special      */
#define C_ISCHR  0020000 /* Character special  */
#define C_ISCTG  0110000 /* Reserved           */
#define C_ISLNK  0120000 /* Symbolic link      */
#define C_ISSOCK 0x14000 /* Socket             */

#endif
