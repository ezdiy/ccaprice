#include "inc/string.h"

#define CCAPRICE_MALLOC_RAMSIZE ((void*)0x100000)

/* cheap slow and nasty malloc implementation */
struct ccaprice_malloc_block {
	int    used;
	size_t size;
};

static int   ccaprice_malloc_inited = 0;
static void *ccaprice_malloc_start  = NULL;
static void *ccaprice_malloc_last   = NULL;

extern char _end[];
void* ccaprice_malloc_end = (void*)_end; /* this is nasty ... */
static void* ccaprice_malloc_sbrk(size_t byte) {
	static void *heap = NULL;
	void        *base;
	
	if (heap == NULL)
		heap = ccaprice_malloc_end;
		
	//if (((uintptr_t)CCAPRICE_MALLOC_RAMSIZE - (uintptr_t)heap) >= 0) {
		base = heap;
		heap = (void*)((uintptr_t)heap + byte);
		return (base);
	//}
	//return ((void*)-1);
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
