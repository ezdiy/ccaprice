CFLAGS += -Wall -Wextra -nostdlib -fno-builtin -nostartfiles -nodefaultlibs -Wno-uninitialized -Wno-unused-parameter -Wno-sign-compare -fno-strict-aliasing -DCCAPRICE_CP -DCCAPRICE_LOCALE_SET=en_US
ifeq (BSD, $(OS))
	SHELL = /usr/local/bin/bash
	LARCH = elf_i386_fbsd
else
ifeq (WIN, $(OS))
	SHELL = /bin/bash
	LARCH = i386pe
else
	SHELL = /bin/bash
	LARCH = elf_i386
endif
endif
SRC     = src/assert.c                   \
          src/locale.c                   \
          src/signal.c                   \
          src/crt/runtime.c              \
          src/string/memchr.c            \
          src/string/memcmp.c            \
          src/string/memcpy.c            \
          src/string/memset.c            \
          src/string/memmove.c           \
          src/string/strcat.c            \
          src/string/strchr.c            \
          src/string/strcmp.c            \
          src/string/strcpy.c            \
          src/string/strcspn.c           \
          src/string/strlen.c            \
          src/string/strncat.c           \
          src/string/strncmp.c           \
          src/string/strncpy.c           \
          src/string/strpbrk.c           \
          src/string/strrchr.c           \
          src/string/strdup.c            \
          src/string/strerror.c          \
          src/string/strpbrk.c           \
          src/string/strspn.c            \
          src/string/strstr.c            \
          src/string/strtok.c            \
          src/stdlib/abort.c             \
          src/stdlib/atoi.c              \
          src/stdlib/exit.c              \
          src/stdlib/getenv.c            \
          src/stdlib/malloc.c            \
          src/stdlib/puts.c              \
          src/stdlib/rand.c              \
          src/stdio/fclose.c             \
          src/stdio/feof.c               \
          src/stdio/ferror.c             \
          src/stdio/fflush.c             \
          src/stdio/fopen.c              \
          src/stdio/fputc.c              \
          src/stdio/fputs.c              \
          src/stdio/fwrite.c             \
          src/stdio/printf.c             \
          src/stdio/remove.c             \
          src/math/abs.c                 \
          src/math/atan.c                \
          src/math/ceil.c                \
          src/math/floor.c               \
          src/math/fabs.c                \
          src/math/finite.c              \
          src/math/isnan.c               \
          src/math/frexp.c               \
          src/math/ilogb.c               \
          src/posix/errno.c              \
          src/posix/strings/bcmp.c       \
          src/posix/strings/bcopy.c      \
          src/posix/strings/bzero.c      \
          src/posix/strings/ffs.c        \
          src/posix/strings/index.c      \
          src/posix/strings/rindex.c     \
          src/posix/strings/strcasecmp.c \
          src/posix/strings/strncasecmp.c
          
ifeq ($(OS), WIN)
	OUT = ccaprice.lib
else
	OUT = ccaprice.a
endif

OBJ     = $(SRC:.c=.o)
INC     = -I.
EDGE    = -c $< -o $@
SRCD    = $(SRC)
OBJD    = $(SRCD:.c=.o)
CFLAGS += -D__INFO__="$(shell echo `uname -a`)"
# user32.dll and kernel32.dll needed
ifeq ($(OS), WIN)
	LFLAGS = -luser32 -lkernel32
else
	LFLAGS =
endif

ifeq (,$(VERBOSE))
	AT = @
endif

ifneq ($(OS), WIN)
	ifeq (,$(NOCOLOR))
		GREEN  = -e "\033[1;32m
		BLUE   = -e "\033[1;34m
		PURPLE = -e "\033[1;35m
		CYAN   = \033[1;36m
		RRED   = \033[1;31m
		ENDCOL = \033[m"
	endif
endif

# naive  selection
ifneq (, $(NAIVE))
	CFLAGS += -DCCAPRICE_NAIVE
endif

# target selection
ifneq (, $(TARG))
	ifeq (x86_64, $(TARG))
		TARGET  = x86_64
		CFLAGS += -DCCAPRICE_TARGET_X86_64
	else
	ifeq (x86_32, $(TARG))
		TARGET  = x86_32
		CFLAGS += -DCCAPRICE_TARGET_X86_64
	else
	ifeq (amd64, $(TARG))
		TARGET  = amd64
		CFLAGS += -DCCAPRICE_TARGET_X86_64
	else
	ifeq (i386, $(TARG))
		TARGET  = i386
		CFLAGS += -DCCAPRICE_TARGET_X86
		LFLAGS  = -m $(LARCH)
	else
	ifeq (i486, $(TARG))
		TARGET  = i486
		CFLAGS += -DCCAPRICE_TARGET_X86
		LFLAGS  = -m $(LARCH)
	else
	ifeq (i586, $(TARG))
		TARGET  = i586
		CFLAGS += -DCCAPRICE_TARGET_X86
		LFLAGS  = -m $(LARCH)
	else
	ifeq (i686, $(TARG))
		TARGET  = i686
		CFLAGS += -DCCAPRICE_TARGET_X86
		LFLAGS  = -m $(LARCH)
	endif
	endif
	endif
	endif
	endif
	endif
	endif
endif

# process
ifneq (LINUX, $(OS))
ifneq (BSD, $(OS))
ifneq (WIN, $(OS))
	override CCC    = @echo
	override INC    =
	override EDGE   =
	override SRCD   = src/assert.c
	override OBJD   = src/assert.o
	override DONOT  = 1
	override VERBOSE= 1
	override CFLAGS = $(GREEN)Error: No target specified; try $(CYAN)\`make CCC=[gcc/clang/pathcc] TARG=$(shell uname -m)\` OS=[WIN/BSD/LINUX]$(ENDCOL)
endif
endif
endif

ifneq (,$(findstring -DCCAPRICE_TARGET_X86_64,$(CFLAGS)))
	ASM     = src/crt/x86_64.S
	AFLAGS  =
else
	ifneq (,$(findstring -DCCAPRICE_TARGET_X86,$(CFLAGS)))
		ASM     = src/crt/i386.S
		CFLAGS += -m32
		ifeq ($(shell uname), FreeBSD)
			AFLAGS  = -m32 -DBSD
		else
			AFLAGS  = -m32
		endif
	else
		override CCC    = @echo
		override INC    =
		override EDGE   =
		override SRCD   = src/assert.c
		override OBJD   = src/assert.o
		override DONOT  = 1
		override VERBOSE= 1
		override CFLAGS = $(GREEN)Error: No target specified; try $(CYAN)\`make CCC=[gcc/clang/pathcc] TARG=$(shell uname -m)\` OS=[WIN/BSD/LINUX]$(ENDCOL)
	endif
endif

ifeq (, $(CCC))
	override CCC    = @echo
	override INC    =
	override EDGE   =
	override SRCD   = src/assert.c
	override OBJD   = src/assert.o
	override DONOT  = 1
	override VERBOSE= 1
	override CFLAGS = $(GREEN)Error: No target specified; try $(CYAN)\`make CCC=[gcc/clang/pathcc] TARG=$(shell uname -m)\` OS=[WIN/BSD/LINUX]$(ENDCOL)
endif

CFLAGS += -D$(shell echo $(OS))
AFLAGS += -D$(shell echo $(OS))
BIN     = $(ASM:.S=.o)

.c.o:
ifneq ($(VERBOSE), 1)
	@ if [[ $@ == *crt/*    ]]; then echo $(PURPLE) [crt]    $(RRED) Building a C99 object file $(CYAN) $@ $(ENDCOL); fi
	@ if [[ $@ == *stdio/*  ]]; then echo $(PURPLE) [stdio]  $(RRED) Building a C99 object file $(CYAN) $@ $(ENDCOL); fi
	@ if [[ $@ == *stdlib/* ]]; then echo $(PURPLE) [stdlib] $(RRED) Building a C99 object file $(CYAN) $@ $(ENDCOL); fi
	@ if [[ $@ == *string/* ]]; then echo $(PURPLE) [string] $(RRED) Building a C99 object file $(CYAN) $@ $(ENDCOL); fi
	@ if [[ $@ == *math/*   ]]; then echo $(PURPLE) [math]   $(RRED) Building a C99 object file $(CYAN) $@ $(ENDCOL); fi
	@ if [[ $@ == *posix/*  ]]; then echo $(PURPLE) [posix]  $(RRED) Building a C99 object file $(CYAN) $@ $(ENDCOL); fi
endif
	$(AT) $(CCC) $(INC) $(CFLAGS) $(EDGE)

$(OUT): $(OBJD)
ifneq ($(VERBOSE), 1)
	@echo $(PURPLE) [crt]    $(RRED) Building a ASM object file $(CYAN) $(ASM) $(ENDCOL)
endif
ifneq ($(DONOT), 1)
	$(AT) $(CCC) $(AFLAGS) $(ASM) -c -o $(BIN)
endif
ifneq ($(VERBOSE), 1)
	@echo $(BLUE) Creating static library ... $(ENDCOL)
endif
ifneq ($(DONOT), 1)
	$(AT) ar rcs $(OUT) $(BIN) $(OBJ)
endif
ifneq ($(VERBOSE), 1)
	@echo $(GREEN) Completed Build for $(TARGET) $(ENDCOL)
endif

test: test.o
ifneq ($(DONOT), 1)
	$(AT) ld $(LFLAGS) -o test test.o ccaprice.a
endif
ifneq ($(VERBOSE), 1)
	@echo $(GREEN) Completed Build for test $(ENDCOL)
endif
	
clean:
	$(AT) rm -f src/crt/i386.o src/crt/x86_64.o
	$(AT) rm -f ccaprice.lib ccaprice.a $(OUT) $(OBJ) test test.o
