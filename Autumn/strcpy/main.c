#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>

#include "smartstrcpy.h"

#define STATS() printf("%.02f seconds.\n", (double) (end - start) / CLOCKS_PER_SEC)

const char *src = "In the C programming language, Duff's device is a way of manually implementing loop unrolling by interleaving two syntactic constructs of C: the do-while loop and a switch statement. Its discovery is credited to Tom Duff in November 1983, when Duff was working for Lucasfilm and used it to speed up a real-time animation program. Loop unrolling attempts to reduce the overhead of conditional branching needed to check whether a loop is done, by executing a batch of loop bodies per iteration. To handle cases where the number of iterations is not divisible by the unrolled-loop increments, a common technique among assembly language programmers is to jump directly into the middle of the unrolled loop body to handle the remainder. Duff implemented this technique in C by using C's case label fall-through feature to jump into the unrolled body.";
const int count = 2000000;

int main(void)
{
    clock_t start;
    clock_t end;
    char *dst = malloc(sizeof(char) * 1024);

    assert(!strcmp(src, strcpy(dst, src)));
    assert(!strcmp(src, dumbstrcpy(dst, src)));
    assert(!strcmp(src, smartstrcpy(dst, src)));

    printf("Testing string copying on %d examples of length %d.\n", count, strlen(src));

    printf("Library strcpy: ");
    start = clock();
    for (int i = 0; i < count; i++)
        strcpy(dst, src);
    end = clock();
    STATS();

    printf("Dumb strcpy: ");
    start = clock();
    for (int i = 0; i < count; i++)
        dumbstrcpy(dst, src);
    end = clock();
    STATS();

    printf("Smart strcpy: ");
    start = clock();
    for (int i = 0; i < count; i++)
        smartstrcpy(dst, src);
    end = clock();
    STATS();
    printf(dst);

    return 0;
}
