/*
 * Copyright (C) 2012
 *     Dale Weiler
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
#include <stdio.h>
#include <stdlib.h>

/*
 * These may be modified to further relfect the target system directory
 * structure.
 */ 

#define LIB_DIR "/lib"
#define INC_DIR "/include/ccaprice"
#define BIN_DIR "/bin"
#define PRF_DIR "/usr"

/*
 * Bump when needed.  There is rarely anything that needs to be changed
 * here except maybe ccaprice.a (version in file name for future legacy)
 */  
#define CFLAGS  "-nostdlib -nostdinc -fno-builtin -nostartfiles -nodefaultlibs"
#define LIBS    "ccaprice.a"

int main(int argc, char **argv) {
    char *prefix = PRF_DIR;

    argc--;
    argv++;

    if (argc < 1)
        return -1;

    while (argc) {
        if (argv[0][0] == '-' && argv[0][1] == '-') {
            char *cmp = &argv[0][2];

            /*
             * All commandline option checks go here.  We're using the
             * standard --cflags and --libs options present in literally
             * every library config helper program.
             */
            if (!strncmp(cmp, "prefix", 6) && cmp[6] == '=' && strlen(&cmp[7]))
                prefix = strdup(&cmp[7]);

            if (!strcmp(cmp, "cflags"))
                printf("-I%s%s/inc -I%s%s/int -I%s%s/sys/%s %s\n", prefix, INC_DIR, prefix, INC_DIR, prefix, INC_DIR, ARCH, CFLAGS);

            if (!strcmp(cmp, "libs"))
                printf("%s%s/ccaprice.a\n", prefix, LIB_DIR);
        }
        argv++;
        argc--;
    }

    return 1;
}
