#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>

#include "smartstrcpy.h"

const char *src = "In the C programming language, Duff's device is a way of manually implementing loop unrolling by interleaving two syntactic constructs of C: the do-while loop and a switch statement. Its discovery is credited to Tom Duff in November 1983, when Duff was working for Lucasfilm and used it to speed up a real-time animation program. Loop unrolling attempts to reduce the overhead of conditional branching needed to check whether a loop is done, by executing a batch of loop bodies per iteration. To handle cases where the number of iterations is not divisible by the unrolled-loop increments, a common technique among assembly language programmers is to jump directly into the middle of the unrolled loop body to handle the remainder. Duff implemented this technique in C by using C's case label fall-through feature to jump into the unrolled body.";
char dst[1024];
const int count = 2000000;

void test(char *(*func)(char *, const char *), const char *name)
{
    clock_t start;
    clock_t end;

    assert(!strcmp(src, func(strclear(dst), src)));

    printf("%s: ", name);

    start = clock();
    for (int i = 0; i < count; i++)
        func(dst, src);
    end = clock();

    printf("%.02f seconds.\n", (double) (end - start) / CLOCKS_PER_SEC);
}

int main(void)
{
    printf("Testing string copying on %d examples of length %d.\n", count, (int) strlen(src));

    test(&strcpy, "Library strcpy");
    test(&smartstrcpy, "Smart strcpy");
    test(&smartstrcpy2, "Smart strcpy 2");
    test(&dumbstrcpy, "Dumb strcpy");

    return 0;
}
