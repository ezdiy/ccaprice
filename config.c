#include <stdio.h>
#include <stdlib.h>

#define LIB_DIR "/usr/lib"
#define INC_DIR "/usr/include/ccaprice"
#define BIN_DIR "/bin"
#define CFLAGS  "-nostdlib -nostdinc -fno-builtin -nostartfiles -nodefaultlibs"
#define LIBS    "ccaprice.a"

int main(int argc, char **argv) {
    argc--;
    argv++;

    if (argc < 1)
        return -1;

    while (argc) {
        if (argv[0][0] == '-' && argv[0][1] == '-') {
            char *cmp = &argv[0][2];
            if (!strcmp(cmp, "cflags")) {
                printf("-I%s/inc -I%s/int -I%s/sys/%s %s ", INC_DIR, INC_DIR, INC_DIR, ARCH, CFLAGS);
            } else if (!strcmp(cmp, "libs")) {
                printf("%s/ccaprice.a", LIB_DIR);
            }
        }
        argv++;
        argc--;
    }

    return 1;
}
