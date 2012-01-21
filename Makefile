CFLAGS += -g -O3 -Wall -nostdlib -std=c99 -fno-builtin -ffreestanding -pedantic-errors -DCCAPRICE_COMPILING
CCC     = gcc
SRC     = src/assert.c         \
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
          src/string/strdup.c  \
          src/string/strpbrk.c \
          src/stdlib/malloc.c  \
          src/stdlib/atoi.c    \
          src/stdlib/abs.c     \
          src/stdlib/exit.c    \
          src/stdlib/abort.c   
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
