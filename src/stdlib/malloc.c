/*
 * Copyright (C) 2012 
 * 	Dale Weiler
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "inc/string.h"
#include "inc/errno.h"
#include "inc/posix/errno.h"
/* Internal Imports */
CCAPRICE_INTERNAL_TYPE(void*,ccaprice_runtime_curbrk); 
CCAPRICE_INTERNAL_FUNC(int,  ccaprice_runtime_brk, (void*));

/* cheap slow and nasty malloc implementation */
struct ccaprice_malloc_block {
	int    used;
	size_t size;
};

static int   ccaprice_malloc_inited = 0;
static void *ccaprice_malloc_start  = NULL;
static void *ccaprice_malloc_last   = NULL;
static void* ccaprice_malloc_sbrk(size_t byte) {
	void *old;
	
	if (ccaprice_runtime_curbrk == NULL)
		if (ccaprice_runtime_brk(0) < 0)
			return (void*)-1;
	if (byte == 0)
		return ccaprice_runtime_curbrk;
		
	old = ccaprice_runtime_curbrk;
	if (ccaprice_runtime_brk((void*)((uintptr_t)old + byte)) < 0)
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
	if (!memp) {
		errno = ENOMEM;
		return NULL;
	}
	return memp;
}

void *calloc(size_t nmemb, size_t size) {
	/* TODO: check for overflow ...*/
	size *= nmemb;
	void *ret = malloc(size);
	if (ret)
		memset(ret, 0, size);
	return ret;
}
