CFLAGS += -ggdb3 -Wall -nostdlib -std=c99 -fno-builtin -ffreestanding -DCCAPRICE_COMPILING
CCC     = gcc
SRC     = src/assert.c         \
          src/locale.c         \
          src/signal.c         \
		  src/crt/runtime.c    \
          src/string/memchr.c  \
          src/string/memcmp.c  \
          src/string/memcpy.c  \
          src/string/memset.c  \
          src/string/memmove.c \
          src/string/strcat.c  \
          src/string/strchr.c  \
          src/string/strcmp.c  \
          src/string/strcpy.c  \
          src/string/strlen.c  \
          src/string/strncat.c \
          src/string/strncmp.c \
          src/string/strncpy.c \
          src/string/strdup.c  \
          src/string/strpbrk.c \
          src/stdlib/abort.c   \
          src/stdlib/abs.c     \
          src/stdlib/atoi.c    \
          src/stdlib/exit.c    \
          src/stdlib/malloc.c  \
          src/stdlib/puts.c    \
          src/stdio/fclose.c   \
          src/stdio/feof.c     \
          src/stdio/ferror.c   \
          src/stdio/fflush.c   \
          src/stdio/fopen.c    \
          src/stdio/fputc.c    \
          src/stdio/fputs.c    \
          src/stdio/fwrite.c   \
          src/posix/errno.c
OBJ     = $(SRC:.c=.o)
OUT     = ccaprice.a
INC     = -I.

ifneq (,$(findstring -DCCAPRICE_TARGET_X86_64,$(CFLAGS)))
ASM     = src/crt/x86_64.S
AFLAGS  =
else
ifneq (,$(findstring -DCCAPRICE_TARGET_X86,$(CFLAGS)))
ASM     = src/crt/i386.S
CFLAGS += -m32
AFLAGS  = -m32
endif
endif

BIN = $(ASM:.S=.o)

.c.o:
	$(CCC) $(INC) $(CFLAGS) -c $< -o $@
	
$(OUT): $(OBJ)
	$(CCC) $(AFLAGS) $(ASM) -c -o $(BIN)
	ar rcs $(OUT) $(BIN) $(OBJ)
	
clean:
	rm -f $(OBJ) $(BIN) $(OUT)
