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
#include "inc/stdlib.h"
/*
 * Optimizations:
 *     This is non-recurisive, instead a stack of pointers store the next
 *     array (partition) to sort, this is immensly sped up by allocating
 *     CHAR_BIT * sizeof(size_t) worth space on the stack for the array.
 *
 *     We use a median-of-three decision tree to determine pivot elements,
 *     this reduces the likelyhood of selecting a pivot value which may
 *     be bad, or already selected (prevent extra comparisions).
 *
 *     We only actually quick sort on E/T worth paritions, leaving the
 *     insertion sort to sort the T worth items within each of the
 *     partitions, this works well since insertion sort works fast on
 *     semi-sorted, small, array segments; which at this point it's already
 *     guranteed to be.
 *
 *     The larger of the sub paritions is pushed onto the stack before
 *     others, this allows the sorter to work on smaller partitions.  This
 *     gurantees no more than O(1) space complexity.
 *
 *     The internal swapping taking care of the sorting mechanisims uses
 *     a fall-through swap for data less than 8, and a duffs-device for
 *     array segements > 8, this gurantees comparision-less, branchless
 *     swapping for short-width segements < 8, and may-speed up for larger
 *     segements depending on the system, if not, no actual overhead is added
 *     compared to a traditional naive swap.
 *
 *     When doing the pivot swap there is a goto used to skip the next pivot
 *  if the check passes for the given partition. This allows us to ignore
 *     potential branches. This might not actually be the optimal case depending
 *     on certian variables. This can be overrode however where branches will
 *     be used instead.
 *
 *    When performing swapping, pushing to the stack, or popping from the
 *     stack no function call overhead is added.  Instead macros are used for
 *     absolute inlinability, this in some cases can offer greater performance
 *     over a function call (that the compiler might not inline).
 *
 *     No memory is allocated dynamically, it should be noted memory is still
 *     allocated on the stack, but thats cheap.  This qsort doesn't perform a
 *     single dynamic allocation.
 *
 *     When searching for the first element during insertion sort we use an
 *     unrolled loop, which is mostly faster since we only have to search for
 *     inside half of the range max worth elements.
 */
#ifdef CCAPRICE_STDLIB_QSORT_OPTIMAL
#    define CCAPRICE_QSORT_GOTO /* Use goto jump for jump check */
#    define CCAPRICE_QSORT_SWAP /* Use optimal swap function    */
#    define CCAPRICE_QSORT_LOOP
#endif

typedef struct {
    char *l; /* pointer to LO */
    char *h; /* pointer to HI */
} ccaprice_qsort_node;

/*
 * The maximum range require before large-sized sort path
 * is used, anything >= to this is just insert sort.  Which
 * is fast for small sets of data.  This value can be changed
 * I suggest is stays sizeof(int64_t), for all x86 and x86_64
 * CPUs.  But never > 8 since thats when insertion sort starts
 * to get slow.  If this is however changed I suggest that the
 * CCAPRICE_QSORT_SMALLMAX be changed to half this and that the
 * necessary macros are constructed for the loop unrolling in
 * the SMALLE implementation.
 */
#define CCAPRICE_QSORT_RANGEMAX 8

/*
 * Pushes back lo (L) & hi (H) into node (N)
 * in single statement, and increments node.
 */
#define CCAPRICE_QSORT_PUSHDATA(N,L,H) ( \
    (void) (                             \
((N)->l=(L)),                    \
((N)->h=(H)),                    \
++(N)                            \
    )                                    \
)
/*
 * Pushes back lo (L) & hi (H) into node (N-1)
 * om single statement, and decrements node.
 */
#define CCAPRICE_QSORT_POPSDATA(N,L,H) ( \
    (void) (                             \
        --(N),                           \
        ((L)=(N)->l),                    \
        ((H)=(N)->h)                     \
    )                                    \
)

/*
 * We can use goto to rid of some branching.  Who knows if this is
 * actually faster or slower on some systems.  This is really here
 * just to make debugging simpler.  Branches area much easier to
 * follow compared to jumps.
 */
#ifdef CCAPRICE_QSORT_GOTO
    #define CCAPRICE_QSORT_JUMPCHECK0(N)                      \
        do {                                                  \
        } while(0)
    #define CCAPRICE_QSORT_JUMPCHECK1(F1, F2, S1, S2, TT)     \
        if ((*cmp)((void *)F1, (void *)F2)<0) {               \
            CCAPRICE_QSORT_SWAP(S1, S2, size);                \
        }
    #define CCAPRICE_QSORT_JUMPCHECK2(F1, F2, S1, S2, TT)     \
        CCAPRICE_QSORT_JUMPCHECK1(F1, F2, S1, S2, TT)         \
        else {                                                \
            goto gotojump;                                    \
        }
    #define CCAPRICE_QSORT_JUMPLABEL() gotojump:
    #define CCAPRICE_QSORT_JUMPAFTER()                        \
        if ((*cmp)((void *)md, (void *)lo)<0) {               \
            CCAPRICE_QSORT_SWAP(md, lo, size);                \
        }
#else /* no goto path */
    #define CCAPRICE_QSORT_JUMPCHECK0(N)                      \
        int (N) = 0
    #define CCAPRICE_QSORT_JUMPCHECK1(F1, F2, S1, S2, TT)     \
        if ((*cmp)((void*)F1, (void*)F2)<0) {                 \
            CCAPRICE_QSORT_SWAP(S1, S2, size);                \
            if ((*cmp)((void*)md, (void*)lo)<0 && (TT)==0) {  \
                TT = 1;                                       \
                CCAPRICE_QSORT_SWAP(md, lo, size);            \
            }                                                 \
        }
    #define CCAPRICE_QSORT_JUMPCHECK2 CCAPRICE_QSORT_JUMPCHECK1
    #define CCAPRICE_QSORT_JUMPLABEL()                        \
        do {                                                  \
        } while(0)
    #define CCAPRICE_QSORT_JUMPAFTER()                        \
        do {                                                  \
        } while(0)
#endif

/*
 * We can unroll the loop when searching for smallest element, since that
 * data will never be > CCAPRICE_QSORT_RANGEMAX / (CCAPRICE_QSORT_RANGEMAX - 2).
 * A manually unrolled loop might be faster, or not; the compiler might
 * do weird things for us that are more optimal in certian cases.
 */
#ifdef CCAPRICE_QSORT_LOOP
    /* MUST ALWAYS BE HALF OF CCAPRICE_QSORT_RANGEMAX (MUST BE CONSTANT) */
    #define CCAPRICE_QSORT_SMALLMAX 4
    #define CCAPRICE_QSORT_SMALLE1                        \
    do {                                                  \
        if ((*cmp)((void*)run, (void*)tmp) < 0) {         \
            tmp = run;                                    \
        }                                                 \
        run += size;                                      \
    } while (0)
    #define CCAPRICE_QSORT_SMALLE2   CCAPRICE_QSORT_SMALLE1; CCAPRICE_QSORT_SMALLE1
    #define CCAPRICE_QSORT_SMALLE3   CCAPRICE_QSORT_SMALLE2; CCAPRICE_QSORT_SMALLE1
    #define CCAPRICE_QSORT_SMALLE4   CCAPRICE_QSORT_SMALLE3; CCAPRICE_QSORT_SMALLE1
    #define CCAPRICE_QSORT_AROUND(N) CCAPRICE_QSORT_SMALLE##N
    #define CCAPRICE_QSORT_SMALLE(N) CCAPRICE_QSORT_AROUND (N)
#else
    #define CCAPRICE_QSORT_SMALLMAX 0
    #define CCAPRICE_QSORT_SMALLE(N)                      \
        do {                                              \
            if ((*cmp)((void*)run, (void*)tmp) < 0) {     \
                tmp = run;                                \
            }                                             \
            run += size;                                  \
        } while (0)
#endif
/*
 * This is a highly optimized swap function for qsort functionality.
 *
 * This function works well for large or small widths of data.  It unrolls
 * the while(W--) { } loop which would be used in a naive implementation.
 * A naive implementation works well where performance is not a concern,
 * need it be reminded this is a QSORT implementation and performance is
 * very important.  Note: This can actually be slower depending on the
 * compiler and system at play.
 *
 * This is faster for me at least on my system, compared to the alternitive
 * inline swap below, system info:
 *         gcc version 4.6.2 20120120 (prerelease) (GCC)
 *         Linux graphitemaster 3.2.6-2-ARCH #1 SMP PREEMPT Thu Feb 16 10:10:02 CET 2012 x86_64
 */
#ifdef  CCAPRICE_QSORT_SWAP
#undef  CCAPRICE_QSORT_SWAP
#define CCAPRICE_QSORT_SWAP(EA, EB, EW)                   \
    do {                                                  \
        register char  C;                                 \
        register char  T;                                 \
        register char *A = (EA);                          \
        register char *B = (EB);                          \
        if (EW < 16) {                                    \
            switch(EW) {                                  \
                case 15: T = *A,*A++ = *B,*B++ = T;       \
                case 14: T = *A,*A++ = *B,*B++ = T;       \
                case 13: T = *A,*A++ = *B,*B++ = T;       \
                case 12: T = *A,*A++ = *B,*B++ = T;       \
                case 11: T = *A,*A++ = *B,*B++ = T;       \
                case 10: T = *A,*A++ = *B,*B++ = T;       \
                case 9:  T = *A,*A++ = *B,*B++ = T;       \
                case 8:  T = *A,*A++ = *B,*B++ = T;       \
                case 7:  T = *A,*A++ = *B,*B++ = T;       \
                case 6:  T = *A,*A++ = *B,*B++ = T;       \
                case 5:  T = *A,*A++ = *B,*B++ = T;       \
                case 4:  T = *A,*A++ = *B,*B++ = T;       \
                case 3:  T = *A,*A++ = *B,*B++ = T;       \
                case 2:  T = *A,*A++ = *B,*B++ = T;       \
                case 1:  T = *A,*A++ = *B,*B++ = T;       \
            }                                             \
        } else {                                          \
    size_t S = (EW);                              \
    do {                                          \
        T = *A, *A++ = *B, *B++ = T;              \
            } while (--S > 0);                            \
        }                                                 \
    } while (0)
#else
/*
 * The above method may actually not be the fastest depending
 * in the system, and compiler.  This is a naive fall back method
 * which could be faster than above in some cases.
 */
#define CCAPRICE_QSORT_SWAP(EA, EB, EW)                   \
    do {                                                  \
        size_t  S = (EW);                                 \
        char   *A = (EA);                                 \
        char   *B = (EB);                                 \
        char    T;                                        \
        do {                                              \
            T = *A, *A++ = *B, *B++ = T;                  \
        } while (--S > 0);                                \
    } while (0)
#endif

void qsort(void * ebase, size_t items, size_t size, int (*cmp)(const void *, const void *)) {
    ccaprice_qsort_node  sdata   [CHAR_BIT * sizeof(size_t)];
    ccaprice_qsort_node *stack = sdata;
    char                *pbase = (char*)ebase;
    size_t               thold = CCAPRICE_QSORT_RANGEMAX * size;
    char *run, *end;
    char *tmp, *thr;

    if (items == 0)
        return;

    if (items > CCAPRICE_QSORT_RANGEMAX) {
        char *lo = pbase;
        char *hi = &pbase[size * (items-1)];

        CCAPRICE_QSORT_PUSHDATA(stack, NULL, NULL);
        while (sdata < stack) {
            char *lp, *rp;
            char *md = lo + size * ((hi - lo) / size >> 1);

            /* Jump check */
            CCAPRICE_QSORT_JUMPCHECK0(tt);
            CCAPRICE_QSORT_JUMPCHECK1(md, lo, md, lo, tt);
            CCAPRICE_QSORT_JUMPCHECK2(hi, md, md, hi, tt);
            CCAPRICE_QSORT_JUMPLABEL ();
            CCAPRICE_QSORT_JUMPAFTER ();
            lp = lo + size;
            rp = hi - size;

            /* Tight inner loops collapsing the walls performance sort */
            do {
                while((*cmp)((void *)lp, (void *)md)<0) lp += size;
                while((*cmp)((void *)md, (void *)rp)<0) rp -= size;

                if (lp < rp) {
                    CCAPRICE_QSORT_SWAP(lp, rp, size);
                    if      (md == lp) md = rp;
                    else if (md == rp) md = lp;
                    lp += size, rp -= size;
                }
                else if (lp == rp) {
                    lp += size, rp -= size;
                    break;
                }
            } while (lp <= rp);

            /* Setup next iteration */
            if ((size_t)(rp - lo) <= thold) {
                if ((size_t)(hi - lp) <= thold)
                    CCAPRICE_QSORT_POPSDATA(stack, lo, hi);
                else
                    lo = lp;
            }
            else if ((size_t)(hi - lp) <= thold)
                hi = rp;
            else if ((rp - lo) > (hi - lp)) {
                CCAPRICE_QSORT_PUSHDATA(stack, lo, rp);
                lo = lp;
            } else {
                CCAPRICE_QSORT_PUSHDATA(stack, lp, hi);
                hi = rp;
            }
        }
    }
    tmp = pbase;
    end = &pbase[size * (items-1)];
    thr = (end < (pbase+thold)) ? end : pbase+thold;

    /* Smallest element first */
    for (run = tmp + size; run <= thr; run += size)
        CCAPRICE_QSORT_SMALLE(CCAPRICE_QSORT_SMALLMAX);
    if (tmp != pbase)
        CCAPRICE_QSORT_SWAP(tmp, pbase, size);

    /* Insertion sort */
    run = pbase + size;
    while((run += size) <= end) {
        tmp = run - size;
        while ((*cmp)((void*)run, (void*)tmp) < 0)
            tmp -= size;
        tmp += size;
        if (tmp != run) {
            char *trav = run + size;
            while (--trav >= run) {
                char  cc = *trav;
                char *hi, *lo;
                for (hi = lo = trav; (lo -= size) >= tmp; hi = lo)
                    *hi = *lo;
                *hi = cc;
            }
        }
    }
}
/*
 * We don't want these to get into any global scope.  We have no use from
 * here on in for these.  Note: Add any additional SMALLE loop unroll macros
 * here so they too don't get stuck in the global namespace.
 */
#undef CCAPRICE_QSORT_AROUND
#undef CCAPRICE_QSORT_JUMPAFTER
#undef CCAPRICE_QSORT_JUMPCHECK0
#undef CCAPRICE_QSORT_JUMPCHECK1
#undef CCAPRICE_QSORT_JUMPCHECK2
#undef CCAPRICE_QSORT_JUMPLABEL
#undef CCAPRICE_QSORT_POPSDATA
#undef CCAPRICE_QSORT_PUSHDATA
#undef CCAPRICE_QSORT_SMALLE
#undef CCAPRICE_QSORT_SMALLE1
#undef CCAPRICE_QSORT_SMALLE2
#undef CCAPRICE_QSORT_SMALLE3
#undef CCAPRICE_QSORT_SMALLE4
#undef CCAPRICE_QSORT_SMALLMAX
#undef CCAPRICE_QSORT_SWAP
