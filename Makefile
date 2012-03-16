#
# Copyright (C) 2012 
# 	Dale Weiler
#
# Permission is hereby granted, free of charge, to any person obtaining a copy of
# this software and associated documentation files (the "Software"), to deal in
# the Software without restriction, including without limitation the rights to
# use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
# of the Software, and to permit persons to whom the Software is furnished to do
# so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#

# compilation flags
CFLAGS += -Wall                 \
          -Wextra               \
          -nostdlib             \
          -fno-builtin          \
          -nostartfiles         \
          -nodefaultlibs        \
          -Wno-uninitialized    \
          -Wno-unused-parameter \
          -Wno-sign-compare     \
          -fno-strict-aliasing  \
          -DCCAPRICE_CP         \
          -DCCAPRICE_LOCALE_SET=en_US
          
# figure out target OS
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
          src/stdlib/bsearch.c           \
          src/stdlib/exit.c              \
          src/stdlib/getenv.c            \
          src/stdlib/malloc.c            \
          src/stdlib/puts.c              \
          src/stdlib/qsort.c             \
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
          src/math/acos.c                \
          src/math/atan.c                \
          src/math/ceil.c                \
          src/math/floor.c               \
          src/math/fabs.c                \
          src/math/finite.c              \
          src/math/isnan.c               \
          src/math/frexp.c               \
          src/math/ilogb.c               \
          src/math/sqrt.c                \
          src/fenv/fegetexceptflag.c     \
          src/fenv/feholdexcept.c        \
          src/fenv/fesetexceptflag.c     \
          src/fenv/feupdateenv.c         \
          src/posix/errno.c              \
          src/posix/strings/bcmp.c       \
          src/posix/strings/bcopy.c      \
          src/posix/strings/bzero.c      \
          src/posix/strings/ffs.c        \
          src/posix/strings/index.c      \
          src/posix/strings/rindex.c     \
          src/posix/strings/strcasecmp.c \
          src/posix/strings/strncasecmp.c

#library outfile   
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

# user32.dll and kernel32.dll needed for windows
ifeq ($(OS), WIN)
	LFLAGS = -luser32 -lkernel32
else
	LFLAGS =
endif

#colors
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

# naive code selection (selects slowest code)
ifneq (, $(NAIVE))
	CFLAGS += -DCCAPRICE_NAIVE
endif

# target architecture selection
ifneq (, $(TARG))
	ifeq (x86_64, $(TARG))
		TARGET  = x86_64
		CFLAGS += -DCCAPRICE_TARGET_X86_64
	else
	ifeq (amd64, $(TARG))
		TARGET  = amd64
		CFLAGS += -DCCAPRICE_TARGET_X86_64
	else
	ifeq (x86_32, $(TARG))
		TARGET  = x86_32
		CFLAGS += -DCCAPRICE_TARGET_X86_32
	else
	ifeq (i386, $(TARG))
		TARGET  = i386
		CFLAGS += -DCCAPRICE_TARGET_X86_32
		LFLAGS  = -m $(LARCH)
	else
	ifeq (i486, $(TARG))
		TARGET  = i486
		CFLAGS += -DCCAPRICE_TARGET_X86_32
		LFLAGS  = -m $(LARCH)
	else
	ifeq (i586, $(TARG))
		TARGET  = i586
		CFLAGS += -DCCAPRICE_TARGET_X86_32
		LFLAGS  = -m $(LARCH)
	else
	ifeq (i686, $(TARG))
		TARGET  = i686
		CFLAGS += -DCCAPRICE_TARGET_X86_32
		LFLAGS  = -m $(LARCH)
	endif
	endif
	endif
	endif
	endif
	endif
	endif
endif

# ensure target Os is valid
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

# setup for architecture
ifneq (,$(findstring -DCCAPRICE_TARGET_X86_64,$(CFLAGS)))
	ASM     = src/crt/x86_64.S
	FENV    = src/fenv/fenv_x86_64.S
	AFLAGS  =
else
	ifneq (,$(findstring -DCCAPRICE_TARGET_X86_32,$(CFLAGS)))
		ASM     = src/crt/x86_32.S
		FENV    = src/fenv/fenv_x86_32.S
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

# HOSTCC selection is invalid?
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

# assembler and compiler flags
CFLAGS += -D$(shell echo $(OS))
AFLAGS += -D$(shell echo $(OS))
BIN     = $(ASM:.S=.o)
FIN     = $(FENV:.S=.o)

# for all .c.o:
.c.o:
ifneq ($(VERBOSE), 1)
	@ if [[ $@ == *crt/*    ]]; then echo $(PURPLE) [crt]    $(RRED) Building a C99 object file $(CYAN) $@ $(ENDCOL); fi
	@ if [[ $@ == *stdio/*  ]]; then echo $(PURPLE) [stdio]  $(RRED) Building a C99 object file $(CYAN) $@ $(ENDCOL); fi
	@ if [[ $@ == *stdlib/* ]]; then echo $(PURPLE) [stdlib] $(RRED) Building a C99 object file $(CYAN) $@ $(ENDCOL); fi
	@ if [[ $@ == *string/* ]]; then echo $(PURPLE) [string] $(RRED) Building a C99 object file $(CYAN) $@ $(ENDCOL); fi
	@ if [[ $@ == *math/*   ]]; then echo $(PURPLE) [math]   $(RRED) Building a C99 object file $(CYAN) $@ $(ENDCOL); fi
	@ if [[ $@ == *posix/*  ]]; then echo $(PURPLE) [posix]  $(RRED) Building a C99 object file $(CYAN) $@ $(ENDCOL); fi
	@ if [[ $@ == *fenv/*   ]]; then echo $(PURPLE) [fenv]   $(RRED) Building a C99 object file $(CYAN) $@ $(ENDCOL); fi
endif
	$(AT) $(CCC) $(INC) $(CFLAGS) $(EDGE)

# main compilation routine
$(OUT): $(OBJD)
ifneq ($(VERBOSE), 1)
	@echo $(PURPLE) [crt]    $(RRED) Building a ASM object file $(CYAN) $(ASM) $(ENDCOL)
endif
ifneq ($(DONOT), 1)
	$(AT) $(CCC) $(AFLAGS) $(ASM) -c -o $(BIN)
endif
ifneq ($(VERBOSE), 1)
	@echo $(PURPLE) [fenv]   $(RRED) Building a ASM object file $(CYAN) $(FENV) $(ENDCOL)
endif
ifneq ($(DONOT), 1)
	$(AT) $(CCC) $(AFLAGS) $(FENV) -c -o $(FIN)
endif
ifneq ($(VERBOSE), 1)
	@echo $(BLUE) Creating static library ... $(ENDCOL)
endif
ifneq ($(DONOT), 1)
	$(AT) ar rcs $(OUT) $(BIN) $(FIN) $(OBJ)
endif
ifneq ($(VERBOSE), 1)
	@echo $(GREEN) Completed Build for $(TARGET) $(ENDCOL)
endif

# test target
test: test.o
ifneq ($(DONOT), 1)
	$(AT) ld $(LFLAGS) -o test test.o $(OUT)
endif
ifneq ($(VERBOSE), 1)
	@echo $(GREEN) Completed Build for test $(ENDCOL)
endif
	
clean:
	$(AT) rm -f src/crt/x86_32.o src/crt/x86_64.o
	$(AT) rm -f src/fenv/fenv_x86_32.o src/fenv/fenv_x86_64.o
	$(AT) rm -f ccaprice.lib ccaprice.a $(OUT) $(OBJ) test test.o
