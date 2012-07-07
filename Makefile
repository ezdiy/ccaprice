#
# Copyright (C) 2012 
# 	Dale Weiler, Steven Braeger
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
CFLAGS += -Wall                          \
          -nostdlib                      \
          -nostdinc                      \
          -fno-builtin                   \
          -nostartfiles                  \
          -nodefaultlibs                 \
          -Wno-uninitialized             \
          -Wno-unused-parameter          \
          -Wno-sign-compare              \
          -fno-strict-aliasing           \
          -D__CCAPRICE_CP                \
          -DCCAPRICE_LOCALE_SET=en_US    \
          -Iinc/                         \
          -Iint/

# uncomment the following for softfpu
# and add to SRC=
#          src/math/abs.c
#          src/math/acos.c
#          src/math/atan.c
#          src/math/ceil.c
#          src/math/floor.c
#          src/math/fabs.c
#          src/math/finite.c 
#          src/math/isnan.c
#          src/math/frexp.c 
#          src/math/ilogb.c
#          src/math/sqrt.c
          
SRC     = src/assert.c                   \
          src/locale.c                   \
          src/signal.c                   \
          crt/runtime.c                  \
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
          src/stdlib/abs.c               \
          src/stdlib/atoi.c              \
          src/stdlib/atol.c              \
          src/stdlib/atoll.c             \
          src/stdlib/bsearch.c           \
          src/stdlib/exit.c              \
          src/stdlib/getenv.c            \
          src/stdlib/labs.c              \
          src/stdlib/llabs.c             \
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
          src/fenv/fegetexceptflag.c     \
          src/fenv/feholdexcept.c        \
          src/fenv/fesetexceptflag.c     \
          src/fenv/feupdateenv.c
          
ASM64  =  crt/x86_64.S                   \
          src/fenv/fenv_x86_64.S         \
          src/setjmp/jmp_x86_64.S        \
          src/math/x86_64/acos.S         \
          src/math/x86_64/asin.S         \
          src/math/x86_64/atan.S         \
          src/math/x86_64/ceil.S         \
          src/math/x86_64/fabs.S         \
          src/math/x86_64/fmod.S         \
          src/math/x86_64/log.S          \
          src/math/x86_64/log10.S        \
          src/math/x86_64/sqrt.S
          
ASM32  =  crt/x86_32.S                   \
          src/fenv/fenv_x86_32.S         \
          src/setjmp/jmp_x86_32.S        \
          src/math/x86_32/acos.S         \
          src/math/x86_32/asin.S         \
          src/math/x86_32/atan.S         \
          src/math/x86_32/ceil.S         \
          src/math/x86_32/fabs.S         \
          src/math/x86_32/fmod.S         \
          src/math/x86_32/log.S          \
          src/math/x86_32/log10.S        \
          src/math/x86_32/sqrt.S
          

# figure out host OS
# figure out linker architecture and bash shell
# we must use bash here (not any other shell)
ifneq (,$(findstring BSD,$(shell uname -s)))
	SHELL         = /usr/local/bin/bash
	LARCH_X86_32  = elf_i386_fbsd
	LARCH_X86_64  = elf_x86_64_fbsd
	OS            = BSD
	SYSDIR_X86_32 = sys/x86_32/
	SYSDIR_X86_64 = sys/x86_64/
	LFLAGS        =
	OUT           = ccaprice.a
else
ifneq (,$(findstring Windows,$(shell uname -s)))
	# use what ever Make starts with for shell
	# it most likely doesn't support colors.
	LARCH_X86_32  = i386pe
	LARCH_X86_64  = x86_64pe
	OS            = WIN
	LFLAGS        = -luser32 -lkernel32
	OUT           = ccaprice.lib
else
ifneq (,$(findstring Linux,$(shell uname -s)))
	SHELL         = /bin/bash
	LARCH_X86_32  = elf_i386
	LARCH_X86_64  = elf_x86_64
	OS            = LINUX
	SYSDIR_X86_32 = sys/x86_32/
	SYSDIR_X86_64 = sys/x86_64/
	LFLAGS        =
	OUT           = ccaprice.a
endif
endif
endif

ifeq (, $(TARGET))
	ifneq (,$(findstring x86_64, $(shell uname -m)))
		TARGET  = x86_64
		CFLAGS += -D__CCAPRICE_TARGET_X86_64 -m64 -I$(SYSDIR_X86_64)
		LFLAGS += -m$(LARCH_X86_64)
		AFLAGS  = -m64
		ASM     = $(ASM64)
	else
	ifneq (,$(findstring amd64, $(shell uname -m)))
		TARGET  = x86_64
		CFLAGS += -D__CCAPRICE_TARGET_X86_64 -m64 -I$(SYSDIR_X86_64)
		LFLAGS += -m$(LARCH_X86_64)
		AFLAGS  = -m64
		ASM     = $(ASM64)
	else
	ifneq (,$(findstring x86_32, $(shell uname -m)))
		TARGET  = x86_32
		CFLAGS += -D__CCAPRICE_TARGET_X86_32 -m32 -I$(SYSDIR_X86_32)
		LFLAGS += -m$(LARCH_X86_32)
		AFLAGS  = -m32
		ASM     = $(ASM32)
	else
	ifneq (,$(findstring i386, $(shell uname -m)))
		TARGET  = i386
		CFLAGS += -D__CCAPRICE_TARGET_X86_32 -m32 -I$(SYSDIR_X86_32)
		LFLAGS += -m$(LARCH_X86_32)
		AFLAGS  = -m32
		ASM     = $(ASM32)
	else
	ifneq (,$(findstring i486, $(shell uname -m)))
		TARGET  = i486
		CFLAGS += -D__CCAPRICE_TARGET_X86_32 -m32 -I$(SYSDIR_X86_32)
		LFLAGS += -m$(LARCH_X86_32)
		AFLAGS  = -m32
		ASM     = $(ASM32)
	else
	ifneq (,$(findstring i586, $(shell uname -m)))
		TARGET  = i586
		CFLAGS += -D__CCAPRICE_TARGET_X86_32 -m32 -I$(SYSDIR_X86_32)
		LFLAGS += -m$(LARCH_X86_32)
		AFLAGS  = -m32
		ASM     = $(ASM32)
	else
	ifneq (,$(findstring i686, $(shell uname -m)))
		TARGET  = i686
		CFLAGS += -D__CCAPRICE_TARGET_X86_32 -m32 -I$(SYSDIR_X86_32)
		LFLAGS += -m$(LARCH_X86_32)
		AFLAGS  = -m32
		ASM     = $(ASM32)
	endif
	endif
	endif
	endif
	endif
	endif
	endif
else
ifeq (x86_64, $(TARGET))
	TARGET  = x86_64
	CFLAGS += -D__CCAPRICE_TARGET_X86_64 -m64 -I$(SYSDIR_X86_64)
	LFLAGS += -m$(LARCH_X86_64)
	AFLAGS  = -m64
	ASM     = $(ASM64)
else
ifeq (amd64, $(TARGET))
	TARGET  = x86_64
	CFLAGS += -D__CCAPRICE_TARGET_X86_64 -m64 -I$(SYSDIR_X86_64)
	LFLAGS += -m$(LARCH_X86_64)
	AFLAGS  = -m64
	ASM     = $(ASM64)
else
ifeq (x86_32, $(TARGET))
	TARGET  = i386
	CFLAGS += -D__CCAPRICE_TARGET_X86_32 -m32 -I$(SYSDIR_X86_32)
	LFLAGS += -m$(LARCH_X86_32)
	AFLAGS  = -m32
	ASM     = $(ASM32)
else
ifeq (i386, $(TARGET))
	TARGET  = i386
	CFLAGS += -D__CCAPRICE_TARGET_X86_32 -m32 -I$(SYSDIR_X86_32)
	LFLAGS += -m$(LARCH_X86_32)
	AFLAGS  = -m32
	ASM     = $(ASM32)
else
ifeq (i486, $(TARGET))
	TARGET  = i386
	CFLAGS += -D__CCAPRICE_TARGET_X86_32 -m32 -I$(SYSDIR_X86_32)
	LFLAGS += -m$(LARCH_X86_32)
	AFLAGS  = -m32
	ASM     = $(ASM32)
else
ifeq (i586, $(TARGET))
	TARGET  = i386
	CFLAGS += -D__CCAPRICE_TARGET_X86_32 -m32 -I$(SYSDIR_X86_32)
	LFLAGS += -m$(LARCH_X86_32)
	AFLAGS  = -m32
	ASM     = $(ASM32)
else
ifeq (i686, $(TARGET))
	TARGET  = i386
	CFLAGS += -D__CCAPRICE_TARGET_X86_32 -m32 -I$(SYSDIR_X86_32)
	LFLAGS += -m$(LARCH_X86_32)
	AFLAGS  = -m32
	ASM     = $(ASM32)
endif
endif
endif
endif
endif
endif
endif
endif

#colors
ifeq (,$(VERBOSE))
	AT = @
endif
ifneq ($(OS), WIN)
	ifeq (,$(NOCOLOR))
		GREEN   = -e "\033[1;32m
		BLUE    = -e "\033[1;34m
		PURPLE  = -e "\033[1;35m
		RED     = -e "\033[1;31m
		CYAN    = \033[1;36m
		RRED    = \033[1;31m
		RPURPLE = \033[1;35m
		ENDSUP  = \033[m\c"
		ENDCOL  = \033[m"
	endif
endif

# allow debug
ifneq (, $(DEBUG))
	override CFLAGS += -g
endif

# we can try $CC if !CCC
ifeq (, $(CCC))
	ifneq (, $(CC))
		CCC = $(CC)
	endif
endif

# Prepreation
ifeq (, $(CCC))
	
	override CCC      = @echo
	override VERBOSE  = 1
	override AFLAGS   =
	override CFLAGS   = $(GREEN)Error: No target specified; try $(CYAN)\`make CC=[gcc/clang/pathcc] $(ENDSUP)
	override INC      =
	override EDGE     =
	override OBJC     = src/assert.o
	override OBJA     = src/crt/x86_64.o
	override DONOT    = 1
else
	# prevent pathcc from adding it's own stdlib stuff
    ifeq (pathcc, $(CCC))
		override CFLAGS += -OPT:fast_stdlib=OFF
	else
	
	#supress clang's 
	ifeq (clang, $(CCC))
		override CFLAGS += -Qunused-arguments
	endif
	endif
	
	override CFLAGS  += -D__INFO__="$(shell echo `uname -a`)"
	override INC      = -I.
	override EDGE     = -c $< -o $@
	override OBJC     = $(SRC:.c=.o)
	override OBJA     = $(ASM:.S=.o)
	override CFLAGS  += -D$(OS)
	override AFLAGS  += -D$(OS)
endif

# ignore output
ifneq ($(VERBOSE), 1)
ECHO = @echo
else
ECHO = @true
endif

# c rule
%.o : %.c | printendian
	$(AT) $(CCC) $(INC) $(CFLAGS) $(EDGE)
ifneq ($(VERBOSE), 1)
	@ if [[ $@ == *crt/*    ]]; then echo $(PURPLE) [crt]    $(RRED) Building a C99 object file $(CYAN) $@ $(ENDCOL); fi
	@ if [[ $@ == *stdio/*  ]]; then echo $(PURPLE) [stdio]  $(RRED) Building a C99 object file $(CYAN) $@ $(ENDCOL); fi
	@ if [[ $@ == *stdlib/* ]]; then echo $(PURPLE) [stdlib] $(RRED) Building a C99 object file $(CYAN) $@ $(ENDCOL); fi
	@ if [[ $@ == *string/* ]]; then echo $(PURPLE) [string] $(RRED) Building a C99 object file $(CYAN) $@ $(ENDCOL); fi
	@ if [[ $@ == *math/*   ]]; then echo $(PURPLE) [math]   $(RRED) Building a C99 object file $(CYAN) $@ $(ENDCOL); fi
	@ if [[ $@ == *fenv/*   ]]; then echo $(PURPLE) [fenv]   $(RRED) Building a C99 object file $(CYAN) $@ $(ENDCOL); fi
endif

#S rule

%.o : %.S | printendian
	$(AT) $(CCC) $(INC) $(AFLAGS) $(EDGE)
ifneq ($(VERBOSE), 1)
	@ if [[ $@ == *crt/*    ]]; then echo $(PURPLE) [crt]    $(RRED) Building a ASM object file $(CYAN) $@ $(ENDCOL); fi
	@ if [[ $@ == *fenv/*   ]]; then echo $(PURPLE) [fenv]   $(RRED) Building a ASM object file $(CYAN) $@ $(ENDCOL); fi
	@ if [[ $@ == *setjmp/* ]]; then echo $(PURPLE) [setjmp] $(RRED) Building a ASM object file $(CYAN) $@ $(ENDCOL); fi
	@ if [[ $@ == *math/*   ]]; then echo $(PURPLE) [math]   $(RRED) Building a ASM object file $(CYAN) $@ $(ENDCOL); fi
endif

# libc target
$(OUT): $(OBJC) $(OBJA)
	$(ECHO) $(BLUE) Creating static library ... $(ENDCOL)

ifneq ($(DONOT), 1)
	$(AT) ar rcs $(OUT) $(OBJC) $(OBJA)
	@ echo $(GREEN) Completed Build for $(TARGET) $(RPURPLE)(`file src/assert.o | sed -r -e 's@.*: *@@' | sed 's/, not stripped//'`) $(ENDCOL)
endif

# test target
test: test.o
ifneq ($(DONOT), 1)
	$(AT) ld $(LFLAGS) -o test test.o $(OUT)
endif
ifeq (, $(DEBUG))
	$(ECHO) $(PURPLE) Stripping ... $(ENDCOL)
	@ echo $(BLUE)   Before `du -s test` $(ENDCOL)
	@ strip test
	@ echo $(BLUE)   After  `du -s test` $(ENDCOL)
endif
	$(ECHO) $(GREEN) Completed Build for test $(RPURPLE)(`file test | sed -r -e 's@.*: *@@'`) $(ENDCOL)

printendian:
ifneq ($(DONOT), 1)
	$(AT)@echo -ne "                                            \n\
	#include <stdint.h>                                         \n\
	#include <stdio.h>                                          \n\
	#ifdef TYPE_CASE                                            \n\
	#    define EB \"Big\"                                      \n\
	#    define EL \"Little\"                                   \n\
	#    define EU \"Unknown\"                                  \n\
	#elif defined(INFO_CASE)                                    \n\
	#    define EB \"Supported\"                                \n\
	#    define EL \"Supported\"                                \n\
	#    define EU \"Unknown (programs might fail)\"            \n\
	#endif                                                      \n\
	int main() {                                                \n\
	   uint8_t b[4] = {0,1,2,3};                                \n\
	#ifdef DATA_CASE                                            \n\
	   FILE *f = fopen(\"endian.h\", \"w+\") ;                  \n\
	   if (!f)  return 1;                                       \n\
	   fputs(\"#ifndef __ENDIAN__\\\\n\",f);                    \n\
	   fputs(\"#define __ENDIAN__\\\\n\",f);                    \n\
	   fprintf(f,\"#\tdefine ENDIAN %d\\\\n\",*((uint32_t*)b)); \n\
	   printf(\"0x%08X\", *((uint32_t*)b));                     \n\
	   fputs(\"#endif\",f);                                     \n\
	   fclose(f);                                               \n\
	#else                                                       \n\
	   switch (*((uint32_t *)b)) {                              \n\
	        case 0x00010203: printf(EB); return 0;              \n\
	        case 0x03020100: printf(EL); return 0;              \n\
	        default:         printf(EU); return 0;              \n\
	   }                                                        \n\
	#endif                                                      \n\
	   return 0;                                                \n\
	}\n" > endian.c 
	$(AT) $(CCC) -DTYPE_CASE endian.c -o endian_type
	$(AT) $(CCC) -DINFO_CASE endian.c -o endian_info
	$(AT) $(CCC) -DDATA_CASE endian.c -o endian_data
	$(AT) echo $(PURPLE) Endianness Type: $(CYAN)`./endian_type`$(ENDCOL)
	$(AT) echo $(PURPLE) Endianness Info: $(CYAN)`./endian_info`$(ENDCOL)
	$(AT) echo $(PURPLE) Endianness Data: $(CYAN)`./endian_data`$(ENDCOL)
	$(AT) rm -f endian_type endian_info endian_data endian.c
endif

.PHONY: printendian


# clean target
# this removes all .o files.  I would use my OBJs here instead but they're
# unknown unless a TARGET is specified, we want to ensure removal of all
# without having to pass any additional make arguments.
# This is _safe_ it only removes .o's in directories that are part of the
# project. So if git decided to hide a .o inside one of it's hidden areas
# or even SVN (if someone wants to make an SVN of the code.)  This will not
# accidently ruin the SCM system.  If there are hoever .o's that need to
# be stored somewhere (for some insane reason) just create a hidden folder
# and this will ignore it.
clean:
	$(AT) find . -type f -name "*.o" -not -path "*/.*/*" -not -name ".*" -exec rm -f {} \;
	$(AT) rm -f ccaprice.lib ccaprice.a
	$(AT) rm -f endian endian.c endian_type endian_info endian_data endian.h
	$(AT) rm -f test
