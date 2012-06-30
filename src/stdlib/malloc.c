/*
 * Copyright (C) 2012
 *     Dale Weiler
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
 
/*
 * Features:
 * 
 * [*] Threadsafe
 * [*] Multi-Heap
 * [*] Heap unmapping
 * [*] Bounds checking
 * [*] Double free protection
 * [*] Invalid pointer protection
 * [*] Signature heap protection
 * [*] Debug messages
 * [*] Configurable
 * [*] Retargetable
 */
 
#define _DWMALLOC_GETPAGESIZE 1
/*#define _DWMALLOC_THREADSAFE*/
/*#define _DWMALLOC_DEBUG     */


#include "inc/stddef.h"   /* size_t / ptrdiff_t / NULL */
#include "crt/runtime.h"

#include "bits/mman.h"
#include "bits/limits.h"
#define getpagesize() PAGE_SIZE

/*
 * -D_DWMALLOC_THREADSAFE to turn on thread safety
 * requires posix threads to function, otherwise leave
 * it undefined for unsafe allocations, reallocations, releases
 * and resizes.
 * 
 * TODO: Try adding support for windows mutexs and what ever
 *       apple OS X uses (I suspect pthread's mutex would work there)
 * 
 *       Could also handroll our own mutex system, or try our hands at
 *       some sort of atomic memory barriers.
 */
#ifdef _DWMALLOC_THREADSAFE
#    include <pthread.h>
#    define _DWMALLOC_LOCK()   do { pthread_mutex_lock  (&_dwmalloc_mutex); } while (0)
#    define _DWMALLOC_UNLOCK() do { pthread_mutex_unlock(&_dwmalloc_mutex); } while (0)
     static pthread_mutex_t _dwmalloc_mutex = PTHREAD_MUTEX_INITIALIZER;
#else
#    define _DWMALLOC_LOCK()
#    define _DWMALLOC_UNLOCK()
#endif

static size_t _dwmalloc_pagesize = 0;

#define _DWMALLOC_MMAP(size) (mmap(0, (size), PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0))

#ifdef _DWMALLOC_DEBUG
#    include <stdio.h>         /* fprintf / stderr */
#    define _DWMALLOC_ERROR(X) fprintf(stderr, "%s: %d\t%s\n", __func__, __LINE__, X)
#else
#    define _DWMALLOC_ERROR(X)
#endif

/*
 * Heap helpers to check if heap is actually a heap, and to check
 * if a heap is free or not.
 */
#define _DWMALLOC_IS_HEAP_REAL(HEAP)                  \
    ((HEAP->signature == _DWMALLOC_SIGNATURE_HEAP) && \
     (HEAP->heapsize  == _dwmalloc_pagesize))
#define _DWMALLOC_IS_HEAP_FREE(HEAP) \
    ((_DWMALLOC_IS_HEAP_REAL(HEAP)) ? HEAP->fchunkoff != -1 : 0)

typedef struct dwmalloc_heap {
    size_t signature;
    size_t chunksize;
    
    int    usedchunks;
    int    freechunks;
    
    ptrdiff_t fchunkoff;
    ptrdiff_t rchunkoff;
    
    size_t heapsize;
    
    struct dwmalloc_heap *prev;
    struct dwmalloc_heap *next;
    struct dwmalloc_copy *copy;
} dwmalloc_heap_t;

/*
 * A shallow raw copy of dwmalloc_heap types
 * this is aliased.
 */
typedef struct dwmalloc_copy {
    size_t    signature;
    size_t    chunksize;
    int         totalheap;
    
    dwmalloc_heap_t *ready;
    dwmalloc_heap_t *first;
    dwmalloc_heap_t *recent;
    dwmalloc_heap_t *last;
} dwmalloc_copy_t;

/*
 * Signature describing copy and non-copy'ed heaps
 * these are required to stay.
 */
#define _DWMALLOC_SIGNATURE_COPY ((size_t)0x99887766)
#define _DWMALLOC_SIGNATURE_HEAP ((size_t)0xFFEEDDCC)
#define _DWMALLOC_COPY_FILL(X)   \
    { _DWMALLOC_SIGNATURE_COPY, X, 0, NULL, NULL, NULL, NULL }

static int             _dwmalloc_copyn = 20;
static dwmalloc_copy_t _dwmalloc_copys[] = {
    _DWMALLOC_COPY_FILL(   8), _DWMALLOC_COPY_FILL(  16),
    _DWMALLOC_COPY_FILL(  24), _DWMALLOC_COPY_FILL(  32),
    _DWMALLOC_COPY_FILL(  40), _DWMALLOC_COPY_FILL(  48),
    _DWMALLOC_COPY_FILL(  56), _DWMALLOC_COPY_FILL(  64),
    _DWMALLOC_COPY_FILL(  72), _DWMALLOC_COPY_FILL(  96),
    _DWMALLOC_COPY_FILL( 128), _DWMALLOC_COPY_FILL( 192),
    _DWMALLOC_COPY_FILL( 256), _DWMALLOC_COPY_FILL( 320),
    _DWMALLOC_COPY_FILL( 384), _DWMALLOC_COPY_FILL( 512),
    _DWMALLOC_COPY_FILL(1024), _DWMALLOC_COPY_FILL(1536),
    _DWMALLOC_COPY_FILL(2048)
};

static dwmalloc_heap_t *dwmalloc_heap_new(size_t size, void *prev, void *next) {
    dwmalloc_heap_t *heap;
    void            *peap;
    void            *chuk;
    
    size_t           bestchuk;
    size_t           tinyheap;
    size_t           heapsize;
    
    int ir;
    int ch;
    
    if (!size) {
        _DWMALLOC_ERROR("size = 0");
        return (dwmalloc_heap_t*)0;
    }
    
    for (ir = 0; ir < _dwmalloc_copyn; ir++) {
        if (_dwmalloc_copys[ir].chunksize >= size) {
            break;
        }
    }
        
    bestchuk = (ir < _dwmalloc_copyn) ?  _dwmalloc_copys[ir].chunksize : size;
    tinyheap = sizeof(dwmalloc_heap_t) + sizeof(ptrdiff_t) + bestchuk + sizeof(ptrdiff_t);
    if (tinyheap <  _dwmalloc_pagesize) {
        heapsize =  _dwmalloc_pagesize;
        ch       = (_dwmalloc_pagesize - sizeof(dwmalloc_heap_t)) / (sizeof(ptrdiff_t) + bestchuk + sizeof(ptrdiff_t));
    } else {
        heapsize =  _dwmalloc_pagesize * (tinyheap / _dwmalloc_pagesize + 1);
        ch       =  1;
    }
    
    if ((peap = _DWMALLOC_MMAP(heapsize)) == MAP_FAILED) {
        _DWMALLOC_ERROR("mmap() returned MAP_FAILED");
        return (dwmalloc_heap_t*)0;
    }
    
    heap             = (dwmalloc_heap_t*)peap;
    heap->signature  = _DWMALLOC_SIGNATURE_HEAP;
    heap->chunksize  = bestchuk;
    heap->usedchunks = ch;
    heap->freechunks = ch;
    heap->fchunkoff  = sizeof(dwmalloc_heap_t) + sizeof(ptrdiff_t);
    heap->rchunkoff  = sizeof(dwmalloc_heap_t) + sizeof(ptrdiff_t);
    heap->heapsize   = heapsize;
    
    if (ir < _dwmalloc_copyn) {
        heap->copy = &_dwmalloc_copys[ir];
        if(!(heap->copy)->ready) {
            (heap->copy)->ready  = heap;
            (heap->copy)->first  = heap;
            (heap->copy)->recent = heap;
            (heap->copy)->last   = heap;
            
            /* this is an odd tree system */
             heap->prev = NULL;
             heap->next = NULL;
        } else {
            (heap->copy)->recent = heap;
             heap->prev          = (heap->copy)->last;
             heap->next          = NULL;
             
            if  ((heap->copy)->last) {
                ((heap->copy)->last)->next = heap;
            }
                ((heap->copy)->last)       = heap;
            if (!(heap->copy)->first) {
                 (heap->copy)->first = heap;
            }
        }
        (heap->copy)->totalheap ++;
    } else {
        heap->copy = (dwmalloc_copy_t*)0;
        heap->prev = NULL;
        heap->next = NULL;
    }
    
    /*
     * This is quite the for loop:
     *     Essentially the process is quite basic, we're finding head
     *     way inside the chunk.
     */
    for (
        chuk = peap + sizeof(dwmalloc_heap_t);
        chuk +  sizeof(ptrdiff_t) + bestchuk + sizeof(ptrdiff_t) <= peap + heapsize;
        chuk += sizeof(ptrdiff_t) + bestchuk + sizeof(ptrdiff_t)
    ) {
        *(ptrdiff_t*)chuk = -(chuk + sizeof(ptrdiff_t) - peap);
    }
    
    return heap;
}

dwmalloc_heap_t *dwmalloc_heap_fffh(dwmalloc_copy_t *copy) {
    dwmalloc_heap_t *heap;
    
    if (!copy) {
        _DWMALLOC_ERROR("copy = 0");
        return (dwmalloc_heap_t*)0;
    }
    
    if (copy->signature != _DWMALLOC_SIGNATURE_COPY) {
        _DWMALLOC_ERROR("invalid heap row");
        return (dwmalloc_heap_t*)0;
    }
    
    for (heap = copy->ready; heap; heap = heap->next) {
        if (!_DWMALLOC_IS_HEAP_REAL(heap)) {
            _DWMALLOC_ERROR("invalid heap found");
            return (dwmalloc_heap_t*)0;
        }
        if (_DWMALLOC_IS_HEAP_FREE(heap))
            break;
    }
    
    return heap;
}

void *dwmalloc_alloc(size_t size, dwmalloc_heap_t *heap) {
    void *recent = NULL;
    void *chunk  = NULL;
    void *point  = NULL;
    
    if (!_DWMALLOC_IS_HEAP_REAL(heap)) {
        _DWMALLOC_ERROR("invalid heap");
        return NULL;
    }
    
    if (!size) {
        _DWMALLOC_ERROR("size = 0");
        return NULL;
    }
    
    if (!_DWMALLOC_IS_HEAP_FREE(heap)) {
        _DWMALLOC_ERROR("non-free heap");
        return NULL;
    }
    
    /*
     * Yes the conditional below is ugly, I wanted this code to be
     * self documenting, good luck :3
     */
    recent = (void*)heap + heap->rchunkoff;
    chunk  = (*(ptrdiff_t*)(recent - sizeof(ptrdiff_t)) < 0) ? recent : (void*)heap + heap->fchunkoff;
    
    *(ptrdiff_t*)(chunk - sizeof(ptrdiff_t)) = chunk - (void*)heap;
    
    heap->rchunkoff  = chunk - (void*)heap;
    heap->freechunks --;
    
    for (
    point = (void*)heap + sizeof(dwmalloc_heap_t) + sizeof(ptrdiff_t);
    point +  heap->chunksize + sizeof(ptrdiff_t) <= (void*)heap + heap->heapsize;
    point += heap->chunksize + sizeof(ptrdiff_t) + sizeof(ptrdiff_t)
    ) {
        if (*(ptrdiff_t*)(point - sizeof(ptrdiff_t)) < 0) {
            heap->fchunkoff = point - (void*)heap;
            break;
        }
    }
    
    /*
     * No more free chunks at ye point who enter here. Handle and unmap
     * for the OS.
     */
    if (point + heap->chunksize + sizeof(ptrdiff_t) > (void*)heap + heap->heapsize) {
        heap->fchunkoff = -1;
        if  (heap->copy) {
            (heap->copy)->recent = heap;
            if (heap == (heap->copy)->first)
            (heap->copy)->first = dwmalloc_heap_fffh(heap->copy);
        }
    }
    
    return chunk;
}

void dwmalloc_release(dwmalloc_heap_t *heap) {
    dwmalloc_copy_t *copy;
    
    if (!heap) {
        _DWMALLOC_ERROR("heap = 0");
        return;
    }
    
    if (!_DWMALLOC_IS_HEAP_REAL(heap)) {
        _DWMALLOC_ERROR("invalid heap");
        return;
    }
    
    if (heap->freechunks != heap->usedchunks) {
        _DWMALLOC_ERROR("freechunks != usedchunks, can't release heap");
        return;
    }
    
    /*
     * The relocation of heaps commences here, we need to keep
     * the heap tree balanced.
     */
    if ((copy = heap->copy)) {
        if (heap->prev)
            (heap->prev)->next = heap->next;
        if (heap->next)
            (heap->next)->prev = heap->prev;
        
        /*
         * Manage the ready and last heaps if they're in the
         * rotation this heap release.
         */
        if (copy->ready == heap)
            copy->ready =  heap->next;
        if (copy->last  == heap)
            copy->last  =  heap->prev;
            
        /*
         * Find a free heap and assign to the first raw copy
         * if the existing one is already the heap.
         */
        if (copy->first == heap)
            copy->first = dwmalloc_heap_fffh(copy);
            
        copy->recent = copy->last;
    }
    
    if (munmap((void*)heap, heap->heapsize) != 0) {
        _DWMALLOC_ERROR("munmap() failed");
        return;
    }
    
    if (copy)
        copy->totalheap ++;
}

/*
 * The heap system is complete, the actually allocator code begins now
 * please be noted that while these may have the libc names such as:
 * free, realloc, malloc, they're not actually the ones to be used
 * which is why they're marked STATIC, these come after which are locked
 * and unlocked for thread safety.
 */
void dwmalloc_free(void *chunk) {
    dwmalloc_heap_t *heap;
    ptrdiff_t        offs;
    
    if (!chunk) {
        _DWMALLOC_ERROR("chunk = 0");
        return;
    }
    
    if ((offs = *(ptrdiff_t*)(chunk - sizeof(ptrdiff_t))) < 0) {
        _DWMALLOC_ERROR("double free");
        return;
    }
    
    if (offs < sizeof(dwmalloc_heap_t) + sizeof(ptrdiff_t)) {
        _DWMALLOC_ERROR("invalid pointer");
        return;
    }
    
    heap = (dwmalloc_heap_t*)(chunk - offs);
    if (!_DWMALLOC_IS_HEAP_REAL(heap)) {
        _DWMALLOC_ERROR("invalid pointer");
        return;
    }
    
    *(ptrdiff_t*)(chunk - sizeof(ptrdiff_t)) = -offs;
    heap->rchunkoff = offs;
    if (heap->fchunkoff == -1 || heap->fchunkoff > offs)
    heap->fchunkoff = offs;
    heap->freechunks ++;
    
    /*
     * Free the heap if there is not chunks in it, unmap it from
     * the OS to make everyone happy.
     */
    if (heap->freechunks == heap->usedchunks) {
        dwmalloc_release(heap);
        return;
    }
    
    /*
     * Keep everything rotational and working
     * this really is an important step.
     */
    if (heap->copy) {
        (heap->copy)->recent = heap;
        if (!(heap->copy)->first)
             (heap->copy)->first = heap;
    }
}

/*
 * Finally the actually allocator after only 400 lines we can actuall
 * do some sort of allocation.
 */
static void *dwmalloc_malloc(size_t size) {
    size_t           alloc;
    void            *chunk;
    dwmalloc_heap_t *heap;
    
    int i;
    
    if (size == 0)
    return NULL;
    if (_dwmalloc_pagesize == 0)
        _dwmalloc_pagesize = getpagesize();
    
    /*
     * Aligned allocation by guessing (this can be done 100% better)
     * TODO: make better
     */
    for (i = 0; i < _dwmalloc_copyn; i++) {
        if (_dwmalloc_copys[i].chunksize >= size) {
            alloc = _dwmalloc_copys[i].chunksize;
            break;
        }
    }
    
    if (i == _dwmalloc_copyn) {
        if (!(heap = dwmalloc_heap_new(size, NULL, NULL))) {
            _DWMALLOC_ERROR("failed to create new heap, returned NULL");
            return NULL;
        }
        
        /* 
         * We got the allocated size we need which means it fits the
         * alignment and will work.
         */
        alloc = size;
    } else {
        /*
         * Try the existing raws, before attempting to create a new heap
         * this usually is the case for applications that free memory as
         * they use it.
         */
        if (_dwmalloc_copys[i].recent && _DWMALLOC_IS_HEAP_FREE(_dwmalloc_copys[i].recent))
            heap = _dwmalloc_copys[i].recent;
        else if (_dwmalloc_copys[i].first)
            heap = _dwmalloc_copys[i].first;
            
        /*
         * Otherwise create a new heap (assuming an application has to
         * breach this well fuck them for using so much ram like that.
         */
        else if (!(heap = dwmalloc_heap_new(_dwmalloc_copys[i].chunksize, _dwmalloc_copys[i].last, NULL))) {
            _DWMALLOC_ERROR("failed to create a new heap, returned NULL");
            return NULL;
        }
    }
    
    /*
     * Lets create the chunk now and return it WHOO! This is the end of
     * this allocator.
     */
    if (!(chunk = dwmalloc_alloc(alloc, heap)))
        _DWMALLOC_ERROR("failed to allocate chunk for heap, returned NULL");
    
    return chunk;
}

static void *dwmalloc_realloc(void *p, size_t size) {
    dwmalloc_heap_t *heap;
    ptrdiff_t        offs;
    
    void            *newp;
    void            *tap1;
    void            *tap2;
    
    if (!p) {
        if (!size) {
            _DWMALLOC_ERROR("cannot allocate zero");
            return NULL;
        }
        newp = dwmalloc_malloc(size);
    } else {
        if (size == 0) {
            dwmalloc_free(p);
            return NULL;
        }
        offs = *(ptrdiff_t*)(p - sizeof(ptrdiff_t));
        if (offs < 0) {
            _DWMALLOC_ERROR("attempt to realloc free chunk");
            return NULL;
        }
        
        heap = (dwmalloc_heap_t*)(p - offs);
        if (!_DWMALLOC_IS_HEAP_REAL(heap)) {
            _DWMALLOC_ERROR("invalid pointer");
            return NULL;
        }
        
        /*
         * We don't need to reallocate or do anything
         * if it already fits.
         */
        if (size <= heap->chunksize)
            return p;
            
        if ((newp = dwmalloc_malloc(size)) == NULL) {
            _DWMALLOC_ERROR("can't allocate new size");
            return NULL;
        }
        
        /*
         * This is a byte copy and isn't optimized: Perhaps we should use memcpy?
         * that would require another include this is suppose to stay self hosting
         * we could add it as an option!  Or write our own optimized one.
         * 
         * TODO: memcpy? ourown? SSE ... ???
         */
        for (tap1 = p, tap2 = newp; tap1 < p + heap->chunksize; tap1++, tap2++)
            *(char*)tap2 = *(char*)tap1;
            
        dwmalloc_free(p);
    }
    
    return newp;
}

/*
 * Now the actuall interface
 *     malloc
 *     realloc
 *     free
 *     calloc
 */
void *malloc(size_t size) {
    void *r;
    
    _DWMALLOC_LOCK();
    /*
     * This is behaviour of glibc being emulated
     */
    if (!size) ++size;
    r = dwmalloc_malloc(size);
    _DWMALLOC_UNLOCK();
    
    return r;
}

void *realloc(void *p, size_t size) {
    void *r;
    
    _DWMALLOC_LOCK();
    r = dwmalloc_realloc(p, size);
    _DWMALLOC_UNLOCK();
    
    return r;
}

void free(void *p) {
    _DWMALLOC_LOCK();
    if (p)
    dwmalloc_free(p);
    _DWMALLOC_UNLOCK();
}

void *calloc(size_t nmemb, size_t size) {
    size_t tap;
    void  *ret;
    int    off;
    
    _DWMALLOC_LOCK();
    tap = nmemb * size;
    ret = dwmalloc_malloc(tap);
    
    /* Null terminate please */
    if (ret) {
    for (off = 0; off < tap; off++)
        *(char*)(ret+off) = '\0';
    }
        
    _DWMALLOC_UNLOCK();
    return ret;
}
