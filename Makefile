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

# to use this makefile you need a few programs installed.  Virtually any *nix
# system should have these included with the base distribution
#
#	bash,     uname, echo, sed
#	binutils, find,  true, stty
#	rm,       grep,  find

# we search for them here and ensure they're installed!
ifneq ($(shell `which bash &> /dev/null`), no)
	APP = bash
else
ifneq ($(shell `which uname &> /dev/null`), no)
	APP = uname
else
ifneq ($(shell `which echo &> /dev/null`), no)
	APP = echo
else
ifneq ($(shell `which sed &> /dev/null`), no)
	APP = sed
else
ifneq ($(shell `which find &> /dev/null`), no)
	APP = find
else
ifneq ($(shell `which true &> /dev/null`), no)
	APP = true
else
ifneq ($(shell `which stty &> /dev/null`), no)
	APP = stty
else
ifneq ($(shell `which rm &> /dev/null`), no)
	APP = rm
else
ifneq ($(shell `which grep &> /dev/null`), no)
	APP = grep
else
ifneq ($(shell `which mkdir &> /dev/null`), no)
	APP = mkdir
else
ifneq ($(shell `which cp &> /dev/null/`), no)
	APP = cp
else
	APP = 0
endif
endif
endif
endif
endif
endif
endif
endif
endif
endif
endif

CFLAGS += -Wall                          \
          -nostdlib                      \
          -nostdinc                      \
          -fno-builtin                   \
          -fno-leading-underscore        \
          -nostartfiles                  \
          -nodefaultlibs                 \
          -Wno-uninitialized             \
          -Wno-unused-parameter          \
          -Wno-sign-compare              \
          -fno-strict-aliasing           \
          -mno-stack-arg-probe           \
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
          src/stdlib/div.c               \
          src/stdlib/exit.c              \
          src/stdlib/getenv.c            \
          src/stdlib/labs.c              \
          src/stdlib/ldiv.c              \
          src/stdlib/llabs.c             \
          src/stdlib/lldiv.c             \
          src/stdlib/malloc.c            \
          src/stdlib/puts.c              \
          src/stdlib/qsort.c             \
          src/stdlib/rand.c              \
          src/stdio/clearerr.c           \
          src/stdio/fclose.c             \
          src/stdio/feof.c               \
          src/stdio/ferror.c             \
          src/stdio/fflush.c             \
          src/stdio/fgetc.c              \
          src/stdio/fgetpos.c            \
          src/stdio/fopen.c              \
          src/stdio/fputc.c              \
          src/stdio/fputs.c              \
          src/stdio/fread.c              \
          src/stdio/fseek.c              \
          src/stdio/ftell.c              \
          src/stdio/fwrite.c             \
          src/stdio/printf.c             \
          src/stdio/putchar.c            \
          src/stdio/remove.c             \
          src/stdio/rename.c             \
          src/stdio/rewind.c             \
          src/stdio/impl/close.c         \
          src/stdio/impl/read.c          \
          src/stdio/impl/seek.c          \
          src/stdio/impl/stderr.c        \
          src/stdio/impl/stdin.c         \
          src/stdio/impl/stdout.c        \
          src/stdio/impl/write.c         \
          src/fenv/fegetexceptflag.c     \
          src/fenv/feholdexcept.c        \
          src/fenv/fesetexceptflag.c     \
          src/fenv/feupdateenv.c         \
          src/thread/lock.c              \
          src/thread/wait.c              \
          src/thread/wake.c
          
ASM64  =  crt/x86_64/crt1.S              \
          crt/x86_64/crti.S              \
          crt/x86_64/crtn.S              \
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
          
ASM32  =  crt/x86_32/crt1.S              \
          crt/x86_32/crti.S              \
          crt/x86_32/crtn.S              \
          crt/x86_32/udivdi3.S           \
          crt/x86_32/umoddi3.S           \
          src/fenv/fenv_x86_32.S         \
          src/setjmp/jmp_x86_32.S        \
          src/math/x86_32/acos.S         \
          src/math/x86_32/asin.S         \
          src/math/x86_32/atan.S         \
          src/math/x86_32/ceil.S         \
          src/math/x86_32/cos.S          \
          src/math/x86_32/fabs.S         \
          src/math/x86_32/fmod.S         \
          src/math/x86_32/log.S          \
          src/math/x86_32/log10.S        \
          src/math/x86_32/sin.S          \
          src/math/x86_32/sqrt.S
          
ASMARM =  crt/arm/crt1.S                 \
          crt/arm/crti.S                 \
          crt/arm/crtn.S                 \
          crt/arm/aeabi_d2iz.S           \
          crt/arm/aeabi_dmul.S           \
          crt/arm/aeabi_fdiv.S           \
          crt/arm/aeabi_fmul.S           \
          crt/arm/aeabi_uidiv.S          \
          crt/arm/aeabi_uidivmod.S       \
          crt/arm/syscall.S              \
          src/setjmp/jmp_arm.S
          

# figure out host OS
# figure out linker architecture and bash shell
# we must use bash here (not any other shell)
ifneq (,$(findstring BSD,$(shell uname -s)))
	SHELL         = /usr/local/bin/bash
	LARCH_X86_32  = elf_i386_fbsd
	LARCH_X86_64  = elf_x86_64_fbsd
	LARCH_ARM     = earmelf_fbsd
	OS            = BSD
	SYSDIR_X86_32 = sys/x86_32/
	SYSDIR_X86_64 = sys/x86_64/
	SYSDIR_ARM    = sys/arm
	LFLAGS        =
	OUT           = ccaprice.a
	SRC          += src/signal/posix/signal.c \
	                src/signal/posix/raise.c
else
ifneq (,$(findstring Linux,$(shell uname -s)))
	SHELL         = /bin/bash
	LARCH_X86_32  = elf_i386
	LARCH_X86_64  = elf_x86_64
	LARCH_ARM     = armelf_linux_eabi
	OS            = LINUX
	SYSDIR_X86_32 = sys/x86_32/
	SYSDIR_X86_64 = sys/x86_64/
	SYSDIR_ARM    = sys/arm/
	LFLAGS        =
	OUT           = ccaprice.a
	SRC          += src/signal/posix/signal.c \
	                src/signal/posix/raise.c
else
ifneq (,$(findstring MING,$(shell uname -s)))
	SHELL         = /bin/bash
	LARCH_X86_32  = i386pe
	LARCH_X86_64  = x64pe
	LARCH_ARM     = armpe
	OS            = WINDOWS
	SYSDIR_X86_32 = sys/x86_32/
	SYSDIR_X86_64 = sys/x86_64/
	SYSDIR_ARM    = sys/arm/
	LFLAGS        = --entry=_start
	OUT           = ccaprice.lib
	SRC          += src/signal/win32/signal.c \
	                src/signal/win32/raise.c
endif
endif
endif

ifeq (, $(TARGET))
	ifneq (,$(findstring x86_64, $(shell uname -m)))
		TARGET  = x86_64
		CFLAGS += -D__CCAPRICE_TARGET_X86_64 -m64 -I$(SYSDIR_X86_64)
		LFLAGS += -m$(LARCH_X86_64)
		AFLAGS  = -m64 -I$(SYSDIR_X86_64)
		ASM     = $(ASM64)
	else
	ifneq (,$(findstring amd64, $(shell uname -m)))
		TARGET  = x86_64
		CFLAGS += -D__CCAPRICE_TARGET_X86_64 -m64 -I$(SYSDIR_X86_64)
		LFLAGS += -m$(LARCH_X86_64)
		AFLAGS  = -m64 -I$(SYSDIR_X86_64)
		ASM     = $(ASM64)
	else
	ifneq (,$(findstring x86_32, $(shell uname -m)))
		TARGET  = x86_32
		CFLAGS += -D__CCAPRICE_TARGET_X86_32 -m32 -I$(SYSDIR_X86_32)
		LFLAGS += -m$(LARCH_X86_32)
		AFLAGS  = -m32 -I$(SYSDIR_X86_32)
		ASM     = $(ASM32)
	else
	ifneq (,$(findstring i386, $(shell uname -m)))
		TARGET  = i386
		CFLAGS += -D__CCAPRICE_TARGET_X86_32 -m32 -I$(SYSDIR_X86_32)
		LFLAGS += -m$(LARCH_X86_32)
		AFLAGS  = -m32 -I$(SYSDIR_X86_32)
		ASM     = $(ASM32)
	else
	ifneq (,$(findstring i486, $(shell uname -m)))
		TARGET  = i486
		CFLAGS += -D__CCAPRICE_TARGET_X86_32 -m32 -I$(SYSDIR_X86_32)
		LFLAGS += -m$(LARCH_X86_32)
		AFLAGS  = -m32 -I$(SYSDIR_X86_32)
		ASM     = $(ASM32)
	else
	ifneq (,$(findstring i586, $(shell uname -m)))
		TARGET  = i586
		CFLAGS += -D__CCAPRICE_TARGET_X86_32 -m32 -I$(SYSDIR_X86_32)
		LFLAGS += -m$(LARCH_X86_32)
		AFLAGS  = -m32 -I$(SYSDIR_X86_32)
		ASM     = $(ASM32)
	else
	ifneq (,$(findstring i686, $(shell uname -m)))
		TARGET  = i686
		CFLAGS += -D__CCAPRICE_TARGET_X86_32 -m32 -I$(SYSDIR_X86_32)
		LFLAGS += -m$(LARCH_X86_32)
		AFLAGS  = -m32 -I$(SYSDIR_X86_32)
		ASM     = $(ASM32)
	else
	ifneq (,$(findstring arm, $(shell uname -m)))
		TARGET  = arm
		CFLAGS += -D__CCAPRICE_TARGET_ARM -I$(SYSDIR_ARM)
		LFLAGS += -m$(LARCH_ARM) -I$(SYSDIR_ARM)
		ASM     = $(ASMARM)
	endif
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
	AFLAGS  = -m64 -I$(SYSDIR_X86_64)
	ASM     = $(ASM64)
else
ifeq (amd64, $(TARGET))
	TARGET  = x86_64
	CFLAGS += -D__CCAPRICE_TARGET_X86_64 -m64 -I$(SYSDIR_X86_64)
	LFLAGS += -m$(LARCH_X86_64)
	AFLAGS  = -m64 -I$(SYSDIR_X86_64)
	ASM     = $(ASM64)
else
ifeq (x86_32, $(TARGET))
	TARGET  = i386
	CFLAGS += -D__CCAPRICE_TARGET_X86_32 -m32 -I$(SYSDIR_X86_32)
	LFLAGS += -m$(LARCH_X86_32)
	AFLAGS  = -m32 -I$(SYSDIR_X86_32)
	ASM     = $(ASM32)
else
ifeq (i386, $(TARGET))
	TARGET  = i386
	CFLAGS += -D__CCAPRICE_TARGET_X86_32 -m32 -I$(SYSDIR_X86_32)
	LFLAGS += -m$(LARCH_X86_32)
	AFLAGS  = -m32 -I$(SYSDIR_X86_32)
	ASM     = $(ASM32)
else
ifeq (i486, $(TARGET))
	TARGET  = i386
	CFLAGS += -D__CCAPRICE_TARGET_X86_32 -m32 -I$(SYSDIR_X86_32)
	LFLAGS += -m$(LARCH_X86_32)
	AFLAGS  = -m32 -I$(SYSDIR_X86_32)
	ASM     = $(ASM32)
else
ifeq (i586, $(TARGET))
	TARGET  = i386
	CFLAGS += -D__CCAPRICE_TARGET_X86_32 -m32 -I$(SYSDIR_X86_32)
	LFLAGS += -m$(LARCH_X86_32)
	AFLAGS  = -m32 -I$(SYSDIR_X86_32)
	ASM     = $(ASM32)
else
ifeq (i686, $(TARGET))
	TARGET  = i386
	CFLAGS += -D__CCAPRICE_TARGET_X86_32 -m32 -I$(SYSDIR_X86_32)
	LFLAGS += -m$(LARCH_X86_32)
	AFLAGS  = -m32 -I$(SYSDIR_X86_32)
	ASM     = $(ASM32)
else
ifeq (arm, $(TARGET))
	TARGET  = arm
	CFLAGS += -D__CCAPRICE_TARGET_ARM -I$(SYSDIR_ARM)
	LFLAGS += -m$(LARCH_ARM) -I$(SYSDIR_ARM)
	ASM     = $(ASMARM)
endif
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
ifeq (,$(NOCOLOR))
	GREEN   = -e "\033[1;32m
	BLUE    = -e "\033[1;34m
	PURPLE  = -e "\033[1;35m
	RED     = -e "\033[1;31m
	CYAN    = \033[1;36m
	RRED    = \033[1;31m
	RGREEN  = \033[1;32m
	RPURPLE = \033[1;35m
	ENDSUP  = \033[m\c"
	ENDCOL  = \033[m"
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

# prevent on missing app
ifeq (0, $(APP))
	override CCC      =
endif

# Prepreation
ifeq (, $(CCC))
	override CCC      = @echo
	override VERBOSE  = 1
	override AFLAGS   =
	override INC      =
	override EDGE     =
	override OBJC     = src/assert.o
	override OBJA     =
	override DONOT    = 1
	
	#select right error message
	ifneq (, $(APP))
		override CFLAGS   = $(GREEN)Error: missing program $(CYAN)$(APP)$(RGREEN) (please install before continuing)\n$(ENDSUP)
	else
		override CFLAGS   = $(GREEN)Error: No target specified, or missing program try $(CYAN)\`make CC=[gcc/clang/pathcc]\n$(ENDSUP)
	endif
else
	# prevent pathcc from adding it's own stdlib stuff
    ifeq (pathcc, $(CCC))
		override CFLAGS += -OPT:fast_stdlib=OFF
	else
	
	#supress clang's 
	ifeq (clang, $(CCC))
		override CFLAGS +=     \
			-Qunused-arguments \
			-Wno-unused-value
	endif
	endif
	
	override CFLAGS  += -D__INFO__="\"$(shell uname -a)"\"
	override INC      = -I.
	override EDGE     = -c $< -o $@
	override OBJC     = $(SRC:.c=.o)
	override OBJA     = $(ASM:.S=.o)
	override CFLAGS  += -D$(OS) -D__OSOS__="\"$(OS)"\"
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
	@ if [[ $@ == *thread/* ]]; then echo $(PURPLE) [thread] $(RRED) Building a C99 object file $(CYAN) $@ $(ENDCOL); fi
	@ if [[ $@ == *signal/* ]]; then echo $(PURPLE) [signal] $(RRED) Building a C99 object file $(CYAN) $@ $(ENDCOL); fi
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
test_core: $(OUT) test.o
ifneq ($(DONOT), 1)
	$(AT) ld $(LFLAGS) -o test test.o $(OUT)
endif
ifeq (, $(DEBUG))
	$(ECHO) $(PURPLE) Stripping ... $(ENDCOL)
	@ echo $(BLUE)   Before `wc -c < test` $(ENDCOL)
	@ strip test
	@ echo $(BLUE)   After  `wc -c < test` $(ENDCOL)
endif
	
test: test_core
	$(ECHO) $(GREEN) Completed Build for test $(RPURPLE)(`file test | sed -r -e 's@.*: *@@'`) $(ENDCOL)
	$(ECHO) $(RED) Executing ./test `stty -a | grep 'columns' | sed -e 's/.*columns //' -e 's/;.*//' `$(ENDCOL)
	@ ./test `stty -a | grep 'columns' | sed -e 's/.*columns //' -e 's/;.*//'`
	
compare: test_core
	@ gcc test.c -static-libgcc -Wl,-Bstatic -lc -lm -o test_system
	$(ECHO) $(PURPLE) Stripping ... $(ENDCOL)
	$(ECHO) $(BLUE)   Before `wc -c < test_system` $(ENDCOL)
	@ strip test_system
	$(ECHO) $(BLUE)   After  `wc -c < test_system` $(ENDCOL)
	$(ECHO)
	$(ECHO) $(GREEN) Comparing system libc ... $(ENDCOL)
	$(ECHO) $(GREEN) systems:  $(RPURPLE) `printf \"%-20s\" \`wc -c < test_system\`` (bytes) $(ENDCOL)
	$(ECHO) $(GREEN) ccaprice: $(RPURPLE) `printf \"%-20s\" \`wc -c < test\`` (bytes) $(ENDCOL)
	@ rm -f test test_system

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

config:
	$(AT) $(CCC) config.c -DARCH=\"$(TARGET)\" -o ccaprice-config

install: config $(OUT)
	$(AT) mkdir -p    /usr/include/ccaprice/int/
	$(AT) mkdir -p    /usr/include/ccaprice/inc/
	$(AT) mkdir -p    /usr/include/ccaprice/sys/
	$(AT) cp -r int/* /usr/include/ccaprice/int
	$(AT) cp -r inc/* /usr/include/ccaprice/inc
	$(AT) cp -r sys/* /usr/include/ccaprice/sys
	$(AT) cp ccaprice.a      /usr/lib/ccaprice.a
	$(AT) cp ccaprice-config /bin/ccaprice-config
	$(AT) echo $(GREEN) Installed to: $(ENDCOL)
	$(AT) echo $(PURPLE)  /usr/include/ccaprice/  $(RRED)include$(ENDCOL)
	$(AT) echo $(PURPLE)  /usr/lib/               $(RRED)library$(ENDCOL)
	$(AT) echo $(PURPLE)  /bin/                   $(RRED)config $(ENDCOL)
	
uninstall:
	$(AT) rm -rf /usr/include/ccaprice
	$(AT) rm -f  /usr/lib/ccaprice.a
	$(AT) rm -f  /bin/ccaprice-config
	$(AT) echo $(GREEN) Uninstalled from directories:$(ENDCOL)
	$(AT) echo $(PURPLE)  /usr/include/ccaprice/  $(RRED)include$(ENDCOL)
	$(AT) echo $(PURPLE)  /usr/lib/               $(RRED)library$(ENDCOL)
	$(AT) echo $(PURPLE)  /bin/                   $(RRED)config $(ENDCOL)

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
	$(AT) rm -f endian.c endian.h
	$(AT) rm -f endian endian_type endian_info endian_data
	$(AT) rm -f test test_system ccaprice-config
	$(AT) rm -f *.exe
	$(ECHO) $(GREEN) Clean complete $(ENDCOL)
	
# nukes any install and cleans the current build
# this is convience recipe
nuke: uninstall clean
