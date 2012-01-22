#include "inc/string.h"
#include <syscall.h>

/* cheap slow and nasty malloc implementation */
struct ccaprice_malloc_block {
	int    used;
	size_t size;
};

static int   ccaprice_malloc_inited = 0;
static void *ccaprice_malloc_start  = NULL;
static void *ccaprice_malloc_last   = NULL;
static void *ccaprice_malloc_curbrk = NULL;

static int   ccaprice_malloc_brk (void *address) {
	#ifdef CCAPRICE_TARGET_X86
		void *vfbrk, *vfscr;
		__asm__ __volatile__ (
			"movl %%ebx , %1   \n\t"
			"movl %3    , %%ebx\n\t"
			"int  $0x80 # %2   \n\t"
			"movl %1    , %%ebx\n\t" :
				"=a"(vfbrk),
				"=r"(vfscr) : 
					"0"(SYS_brk),
					"g"(address)
		);
		ccaprice_malloc_curbrk = vfbrk;
		return (vfbrk < address)?-1:0;
	#elif defined(CCAPRICE_TARGET_X86_64)
		void *vfbrk;
		register unsigned long res;
		register unsigned long adr __asm__("rdi") = (unsigned long)address;
		__asm__ __volatile__ (
			"movq %1, %%rax\n\t"
			"syscall       \n\t" :
				"=a"(res) :
					"i"(SYS_brk), "r"(adr) :
						"memory","cc", "r11", "cx"
		);
		if ((unsigned long)res>=(unsigned long)-4095)
			res = (unsigned long)-1;
			
		ccaprice_malloc_curbrk = vfbrk = (void*)res;
		return (vfbrk < address)?-1:0;
	#endif
}
	
static void* ccaprice_malloc_sbrk(size_t byte) {
	
	void *old;
	
	if (ccaprice_malloc_curbrk == NULL) {
		if (ccaprice_malloc_brk(0) < 0)
			return (void*)-1;
	}
	
	if (byte == 0)
		return ccaprice_malloc_curbrk;
		
	old = ccaprice_malloc_curbrk;
	if (ccaprice_malloc_brk((void*)((uintptr_t)old + byte)) < 0)
		return (void*)-1;
		
	return old;
}

static void  ccaprice_malloc_init() {
	ccaprice_malloc_last   = ccaprice_malloc_sbrk(0);
	ccaprice_malloc_start  = ccaprice_malloc_last;
	ccaprice_malloc_inited = 1;
}


/* malloc and free implementation */
void free(void *p) {
	struct ccaprice_malloc_block *m;
	
	if (!p)
		return;
	
	m       = (void*)((uintptr_t)p - sizeof(struct ccaprice_malloc_block));
	m->used = 0;
	m->size = 0;
	return;
}

void* malloc(size_t bytes) {
	void                         *curp = NULL;
	struct ccaprice_malloc_block *curm = NULL;
	void                         *memp = NULL;
	
	/* Initialize the mem manager */
	if (!ccaprice_malloc_inited) {
		 ccaprice_malloc_init();
	}
	
	bytes += sizeof(struct ccaprice_malloc_block);
	curp   = ccaprice_malloc_start;
	
	/* Search blocks */
	while (curp != ccaprice_malloc_last) {
		curm = (struct ccaprice_malloc_block*)curp;
		if (!curm->used) {
			if (curm->size >= bytes) {
				curm->used  = 1;
				memp        = curp;
				break;
			}
		}
		curp = (void*)((uintptr_t)curp + curm->size);
	}
	if (!memp) {
		ccaprice_malloc_sbrk(bytes);
		
		memp                  = ccaprice_malloc_last;
		ccaprice_malloc_last  = (void*)((uintptr_t)ccaprice_malloc_last + bytes);
		curm                  = memp;
		curm->used            = 1;
		curm->size            = bytes;
	}
	memp  = (void*)((uintptr_t)memp + sizeof(struct ccaprice_malloc_block));
	return memp;
}
