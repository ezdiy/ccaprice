CFLAGS += -Wall -nostdlib -std=c99 -fno-builtin -ffreestanding -fno-strict-aliasing -DCCAPRICE_CP -DCCAPRICE_LOCALE_SET=en_US
CCC     = $(CC)
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
          src/string/strcspn.c \
          src/string/strlen.c  \
          src/string/strncat.c \
          src/string/strncmp.c \
          src/string/strncpy.c \
          src/string/strdup.c  \
          src/string/strerror.c\
          src/string/strpbrk.c \
          src/string/strspn.c  \
          src/string/strstr.c  \
          src/stdlib/abort.c   \
          src/stdlib/atoi.c    \
          src/stdlib/exit.c    \
          src/stdlib/getenv.c  \
          src/stdlib/malloc.c  \
          src/stdlib/puts.c    \
          src/stdlib/rand.c    \
          src/stdio/fclose.c   \
          src/stdio/feof.c     \
          src/stdio/ferror.c   \
          src/stdio/fflush.c   \
          src/stdio/fopen.c    \
          src/stdio/fputc.c    \
          src/stdio/fputs.c    \
          src/stdio/fwrite.c   \
          src/stdio/printf.c   \
          src/stdio/remove.c   \
          src/math/abs.c       \
          src/math/atan.c      \
          src/math/ceil.c      \
          src/math/floor.c     \
          src/math/fabs.c      \
          src/math/finite.c    \
          src/math/isnan.c     \
          src/math/frexp.c     \
          src/math/ilogb.c     \
          src/posix/errno.c
OBJ     = $(SRC:.c=.o)
OUT     = ccaprice.a
INC     = -I.
EDGE    = -c $< -o $@
#copies
SRCD    = $(SRC)
OBJD    = $(SRCD:.c=.o)

ifeq (,$(VERBOSE))
	AT = @
endif

ifneq ($(FLAV), Windows)
	ifeq (,$(NOCOLOR))
		GREEN  = -e "\033[1;32m
		BLUE   = -e "\033[1;34m
		PURPLE = -e "\033[1;35m
		CYAN   = \033[1;36m
		RRED   = \033[1;31m
		ENDCOL = \033[m"
	endif
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
	else
	ifeq (i486, $(TARG))
		TARGET  = i486
		CFLAGS += -DCCAPRICE_TARGET_X86
	else
	ifeq (i586, $(TARG))
		TARGET  = i586
		CFLAGS += -DCCAPRICE_TARGET_X86
	else
	ifeq (i686, $(TARG))
		TARGET  = i686
		CFLAGS += -DCCAPRICE_TARGET_X86
	endif
	endif
	endif
	endif
	endif
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
		# no suitable TARG is set we need to stop the build process
		# this will ruin clean: so we must handle for clean after
		
		# replace compiler with echo
		CC     := @echo
		# clear out include flags
		INC    :=
		# edge is the output command 
		EDGE   :=
		# only compile one source file (for one echo)
		SRCD   := src/assert.c
		# do not actually do creation of library
		DONOT  := 1
		# dissalow output of build process
		VERBOSE:= 1
		CFLAGS := $(GREEN)Error: No target specified; try $(CYAN)\`make TARG=$(shell uname -m)\`$(ENDCOL)
	endif
endif

BIN = $(ASM:.S=.o)

.c.o:
ifneq ($(VERBOSE), 1)
	@ if [[ $@ == *crt*    ]]; then echo $(PURPLE) [crt]    $(RRED) Building a C99 object file $(CYAN) $@ $(ENDCOL); fi
	@ if [[ $@ == *stdio*  ]]; then echo $(PURPLE) [stdio]  $(RRED) Building a C99 object file $(CYAN) $@ $(ENDCOL); fi
	@ if [[ $@ == *stdlib* ]]; then echo $(PURPLE) [stdlib] $(RRED) Building a C99 object file $(CYAN) $@ $(ENDCOL); fi
	@ if [[ $@ == *string* ]]; then echo $(PURPLE) [string] $(RRED) Building a C99 object file $(CYAN) $@ $(ENDCOL); fi
	@ if [[ $@ == *math*   ]]; then echo $(PURPLE) [math]   $(RRED) Building a C99 object file $(CYAN) $@ $(ENDCOL); fi
	@ if [[ $@ == *posix*  ]]; then echo $(PURPLE) [posix]  $(RRED) Building a C99 object file $(CYAN) $@ $(ENDCOL); fi
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
	@ echo $(GREEN) Completed Build for $(TARGET) $(ENDCOL)
endif
	
clean:
	$(AT) rm -f src/crt/i386.o
	$(AT) rm -f src/crt/x86_64.o
	$(AT) rm -f $(OBJ) $(OUT)
