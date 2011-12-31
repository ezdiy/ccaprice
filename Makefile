CFLAGS  = -g -O3 -Wall -nostdlib -std=c99 -fno-builtin -pedantic-errors -DCCAPRICE_COMPILING -DCCAPRICE_TARGET_X86_64
CCC     = gcc
SRC     = src/string/memchr.c  \
          src/string/memcmp.c  \
          src/string/memcpy.c  \
          src/string/memset.c  \
          src/string/memmove.c \
          src/string/strcat.c  \
          src/string/strchr.c  \
          src/string/strcmp.c  \
          src/string/strcpy.c  \
          src/string/strlen.c  \
          src/stdlib/abs.c     \
          src/stdlib/exit.c    \
          src/assert.c
OBJ     = $(SRC:.c=.o)
OUT     = ccaprice.a
INC     = -I.

.c.o:
	$(CCC) $(INC) $(CFLAGS) -c $< -o $@
	
$(OUT): $(OBJ)
	ar rcs $(OUT) $(OBJ)
	
clean:
	rm -f $(OBJ) $(OUT)

