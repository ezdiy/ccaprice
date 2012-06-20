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
#define __CCAPRICE_EXTENSIONS /* Enable extensions in ccaprice */
#include "inc/stdlib.h"
#include "inc/stdio.h"
#include "inc/string.h"
#include "inc/ctype.h"
#include "inc/locale.h"
#include "inc/math.h"
#include "inc/errno.h"
#include "inc/stdint.h"
#include "inc/fenv.h"
#include "inc/limits.h"
#include "inc/stdnoreturn.h"
#include "inc/setjmp.h"

#include "inc/posix/errno.h"
#include "inc/posix/strings.h"

int PADD = 80;
#define TEST_DEF(SPACE, NAME, ...)    \
    int NAME##_test() {               \
char  c[]= {                          \
    "Running test \033[35m["#SPACE    \
    "]\033[0m "#NAME":"               \
};                                    \
fwrite(c, strlen(c), 1, stdout);      \
fflush(stdout);                       \
size_t l=PADD-strlen(c);              \
while (l-->0) { fputc(' ', stdout); } \
__VA_ARGS__                           \
    }
#define TEST_RET(CONDITIONS) return (CONDITIONS);
#define TEST_TRY(NAME) printf("%s\n", NAME##_test()?"\033[32mpassed\033[0m":"\033[31mfailed\033[0m")

TEST_DEF(string, memchr, {
    const char  data[] = "Example string";
    char       *find   = (char*)memchr(data, 'p', sizeof(data));
    TEST_RET(find != NULL)
})

TEST_DEF(string, memcmp, {
    const char  data1[] = "This string";
    const char  data2[] = "This string";
    TEST_RET(memcmp(data1, data2, sizeof(data1)) == 0)
})

TEST_DEF(string, memcpy, {
    char  data[] = "Sample";
    char  copy[sizeof(data)];
    memcpy(copy, data, sizeof(data));

    TEST_RET(copy[0] == 'S' && copy[1] == 'a' &&
             copy[2] == 'm' && copy[3] == 'p' &&
             copy[4] == 'l' && copy[5] == 'e')

})

TEST_DEF(string, memmove, {
    char data[] = ":..:..#";
    memmove(data+1, data+6, 1);
    TEST_RET(data[0] == ':' && data[1] == '#' &&
             data[2] == '.' && data[3] == ':')
})

TEST_DEF(string, memset, {
    char   data[] = "Just large, for this ...";
    memset(data, '-', 5);
    TEST_RET(data[0] == '-' && data[1] == '-' &&
             data[2] == '-' && data[3] == '-' &&
             data[4] == '-')
})

TEST_DEF(string, strcat, {
    char   data[80] = "these ";
    strcat(data, "strings ");
    strcat(data, "are ");
    strcat(data, "concatenated.");
    TEST_RET(data[0]  == 't' && data[6]  == 's' &&
             data[14] == 'a' && data[18] == 'c')
})

TEST_DEF(string, strchr, {
    char  data[] = "This is a string";
    char *find   = strchr(data, 'a');
    TEST_RET(find != NULL)
})

TEST_DEF(string, strcmp, {
    char data[] = "apple";
    TEST_RET(strcmp(data, data) == 0)
})

TEST_DEF(string, strcpy, {
    char data1[] = "Hello";
    char data2[sizeof(data1)];
    strcpy(data2, data1);
    TEST_RET(data2[0] == 'H' && data2[1] == 'e' &&
             data2[2] == 'l' && data2[3] == 'l' &&
             data2[4] == 'o');
})

TEST_DEF(string, strcspn, {
    char  data[] = "fcba73";
    char  find[] = "1234567890";
    TEST_RET(strcspn(data, find) == 4)
})

TEST_DEF(string, strerror, {
    errno = EDOM;
    TEST_RET(strerror(errno) != NULL)
})

TEST_DEF(string, strlen, {
    TEST_RET(strlen("Testing this; 1:2:3\n") == 20)
})

TEST_DEF(string, strncat, {
    char data1[20] = "To be ";
    char data2[20] = "or not to be";
    strncat(data1, data2, 6);
    TEST_RET(data1[0]  == 'T' && data1[1]  == 'o' &&
             data1[2]  == ' ' && data1[3]  == 'b' &&
             data1[4]  == 'e' && data1[5]  == ' ' &&
             data1[6]  == 'o' && data1[7]  == 'r' &&
             data1[8]  == ' ' && data1[9]  == 'n' &&
             data1[10] == 'o' && data1[11] == 't')
})

TEST_DEF(string, strncmp, {
    char data[] = "R2D2";
    TEST_RET(strncmp(data, "R2xx", 2) == 0)
})

TEST_DEF(string, strncpy, {
    char data1[] = "To be or not to be";
    char data2[6];
    strncpy(data2, data1, 5); data2[5] = '\0';
    TEST_RET(data2[0] == 'T' && data2[1] == 'o' &&
             data2[2] == ' ' && data2[3] == 'b' &&
             data2[4] == 'e')
})

TEST_DEF(string, strpbrk, {
    const char *data    = "This is a sample string";
    char       *look    = NULL;
    int         iter    = 0;
    char        find[]  = "aeiou";
    char        core[6];

    look = strpbrk(data, find);
    while (look != NULL)
        core[iter] = *look, iter++, look = strpbrk(look+1, find);
    TEST_RET(core[0] == 'i' && core[1] == 'i' &&
             core[2] == 'a' && core[3] == 'a' &&
             core[4] == 'e' && core[5] == 'i')
})

TEST_DEF(string, strrchr, {
    const char *data = "This is a sample string";
    char       *find = strrchr(data, 's');
    TEST_RET(find-data+1 == 18)
})

TEST_DEF(string, strspn, {
    const char *data = "129th";
    const char *find = "1234567890";
    TEST_RET(strspn(data, find) == 3)
})

TEST_DEF(string, strstr, {
    const char *data = "hello world";
    const char *find = "world";
    TEST_RET(strstr(data, find) != NULL)
})

TEST_DEF(string, strtok, {
    char data[] = "- This, a sample string.";
    char find[] = ",.-";
    TEST_RET(strtok(data, find) != NULL)
})

TEST_DEF(stdlib, min, { TEST_RET(MIN(100,50) ==  50) })
TEST_DEF(stdlib, max, { TEST_RET(MAX(50,100) == 100) })

int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

TEST_DEF(stdlib, qsort, {
    int d[] = { 0,  64, 22, 65, 21, 87, 32, 76, 43, 99, 100, 54, 32, 87, 69 };
    qsort(d, sizeof(d)/sizeof(int), sizeof(int), cmp);
    TEST_RET(d[0]  == 0  && d[1]  == 21 && d[2]  == 22 && d[3]  == 32 &&
             d[4]  == 32 && d[5]  == 43 && d[6]  == 54 && d[7]  == 64 &&
             d[8]  == 65 && d[9]  == 69 && d[10] == 76 && d[11] == 87 &&
             d[12] == 87 && d[13] == 99 && d[14] == 100);
});
TEST_DEF(stdlib, bsearch, {
    int  d[] = { 10, 20, 25, 40, 90, 100 };
    int  k   = 40;
    int *i   = bsearch(&k, d, sizeof(d)/sizeof(*d), sizeof(int), cmp);
    TEST_RET(*i == k);
});

TEST_DEF(stdlib, malloc, {
    char *data = malloc(5);
    data[0] = 'h';
    data[1] = 'e';
    data[2] = 'l';
    data[3] = 'l';
    data[4] = 'o';

    TEST_RET(strncmp(data, "hello", 5) == 0);
});

TEST_DEF(stdlib, free, {
    char *data = malloc(5);
    data[0] = 'h';
    data[1] = 'e';
    data[2] = 'l';
    data[3] = 'l';
    data[4] = 'o';
    free(data);
    char *copy = malloc(5); /* allocator will reuse chunk = same address */
    copy[0] = 'H';
    copy[1] = 'E';
    copy[2] = 'L';
    copy[3] = 'L';
    copy[4] = 'O';
    
    /*
     * should be the same since the `data` is the `copy` in the
     * allocator address to understand read how the allocator works.
     */
    TEST_RET(strncmp(copy, data, 5) == 0);
});

TEST_DEF(stdlib, calloc, {
    char *data = calloc(5, sizeof(char));
    data[0] = 'h';
    data[1] = 'e';
    data[2] = 'l';
    data[3] = 'l';
    data[4] = 'o';
    
    TEST_RET(strncmp(data, "hello", 5) == 0);
});

TEST_DEF(setjmp, jmpbuf, {
    jmp_buf env;
    int     val = setjmp(env);
    
    if (!val)
        longjmp(env, 1);
        
    TEST_RET(val);
});

TEST_DEF(posix\040, bcmp, {
    const char  data1[] = "This string";
    const char  data2[] = "This string";
    TEST_RET(bcmp(data1, data2, sizeof(data1)) == 0)
})

TEST_DEF(posix\040, bcopy, {
    char  data[] = "Sample";
    char  copy[sizeof(data)];
    bcopy(data, copy, sizeof(data));

    TEST_RET(copy[0] == 'S' && copy[1] == 'a' &&
             copy[2] == 'm' && copy[3] == 'p' &&
             copy[4] == 'l' && copy[5] == 'e')
})

TEST_DEF(posix\040, bzero, {
    int data[] = { 1, 2, 3 };
    bzero(data, sizeof(int) * 3);
    TEST_RET(data[0] == 0 && data[1] == 0 && data[2] == 0)
})

TEST_DEF(posix\040, ffs, {
    int data = 0x00FF0000;
    int find = ffs(data);
    TEST_RET(find == 14)
})

TEST_DEF(posix\040, index, {
    char  data[] = "This is a string";
    char *find   = index(data, 'a');
    TEST_RET(find != NULL)
})

TEST_DEF(posix\040, rindex, {
    const char *data = "This is a sample string";
    char       *find = rindex(data, 's');
    TEST_RET(find-data+1 == 18)
})

/*
 * There is a better way to do these checks since precision isn't exactly
 * guranteed for things this large.
 */
TEST_DEF(math\040\040, acos, {    
    TEST_RET(acos(0.5)*180.0/M_PI==60.000000000000007);
})
TEST_DEF(math\040\040, acosf, {
    float a = acosf(0.5f)*180.0f/(float)M_PI
    float b = 60.0f;
    TEST_RET(a == b);
})
TEST_DEF(math\040\040, acosl, {
    TEST_RET((acosl(0.5l)*180.0l/(long double)M_PI)==60.000000000000002338407245616735963l);
})

TEST_DEF(math\040\040, asin, {
    TEST_RET(asin(0.5)*180.0/M_PI==30.000000000000004);
})
TEST_DEF(math\040\040, asinf, {
    float a = asinf(0.5f)*180.0f/(float)M_PI;
    float b = 30.0f;
    TEST_RET(a == b);
})
TEST_DEF(math\040\040, asinl, {
    TEST_RET((asinl(0.5l)*180.0l/(long double)M_PI)==30.000000000000001169203622808367982l);
})

TEST_DEF(math\040\040, atan, {
    TEST_RET(atan(1.0)*180.0/M_PI==45.0);
})
TEST_DEF(math\040\040, atanf, {
    float a = atanf(1.0f)*180.0f/(float)M_PI;
    float b = 45.0f;
    TEST_RET(a == b);
})
TEST_DEF(math\040\040, atanl, {
    TEST_RET((atanl(1.0l)*180.0l/(long double)M_PI)==45.000000000000001752070710736575165l);
})

TEST_DEF(math\040\040, atan2, {
    TEST_RET(atan2(10.0, -10.0)*180.0/M_PI==135.0);
})
TEST_DEF(math\040\040, atan2f, {
    float a = atan2f(10.0f, -10.0f)*180.0f/(float)M_PI;
    float b = 135.0f;
    TEST_RET(a == b);
})
TEST_DEF(math\040\040, atan2l, {
    TEST_RET((atan2l(10.0l, -10.0l)*180.0l/(long double)M_PI)==135.00000000000000525968157916167911l);
})

/*
 * TODO: ceil, ceilf, ceill, fabs, fabsf, fabsl, sqrt, sqrtf, sqrtl tests
 */

int main(int argc, char **argv, char **argp) {
    PADD = 80+3;

    int  i = 0;
    while(*argp++ && *argp)
        printf("%05d : \033[36m%s\033[0m\n", ++i, *argp);

    printf("\nCCAPRICE_BUILD_DATE: \033[33m%s\033[0m\n",   __CCAPRICE_BUILD_DATE);
    printf(  "CCAPRICE_BUILD_TIME: \033[33m%s\033[0m\n",   __CCAPRICE_BUILD_TIME);
    printf(  "CCAPRICE_BUILD_INFO: \033[33m%s\033[0m\n",   __CCAPRICE_BUILD_INFO);
    printf(  "CCAPRICE_BUILD_HOST: \033[33m%s\033[0m\n",   __CCAPRICE_BUILD_HOST);
    printf(  "CCAPRICE_BUILD_COMP: \033[33m%s\033[0m\n\n", __CCAPRICE_BUILD_COMP);

    TEST_TRY(memchr);
    TEST_TRY(memcmp);
    TEST_TRY(memcpy);
    TEST_TRY(memmove);
    TEST_TRY(memset);
    TEST_TRY(strcat);
    TEST_TRY(strchr);
    TEST_TRY(strcmp);
    TEST_TRY(strcpy);
    TEST_TRY(strcspn);
    TEST_TRY(strerror);
    TEST_TRY(strlen);
    TEST_TRY(strncat);
    TEST_TRY(strncmp);
    TEST_TRY(strncpy);
    TEST_TRY(strpbrk);
    TEST_TRY(strrchr);
    TEST_TRY(strspn);
    TEST_TRY(strstr);
    TEST_TRY(strtok);

    TEST_TRY(min);
    TEST_TRY(max);
    TEST_TRY(qsort);
    TEST_TRY(bsearch);
    TEST_TRY(malloc);
    TEST_TRY(free);
    TEST_TRY(calloc);
    
    TEST_TRY(jmpbuf);

    TEST_TRY(bcmp);
    TEST_TRY(bcopy);
    TEST_TRY(bzero);
    TEST_TRY(ffs);
    TEST_TRY(index);
    TEST_TRY(rindex);
    
    TEST_TRY(acos);
    TEST_TRY(acosf);
    TEST_TRY(acosl);
    TEST_TRY(asin);
    TEST_TRY(asinf);
    TEST_TRY(asinl);
    TEST_TRY(atan);
    TEST_TRY(atanf);
    TEST_TRY(atanl);
    TEST_TRY(atan2);
    TEST_TRY(atan2f);
    TEST_TRY(atan2l);   
    return 0;
}
