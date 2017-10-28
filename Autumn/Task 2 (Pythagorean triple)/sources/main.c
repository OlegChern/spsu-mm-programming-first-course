#include <stdio.h>
#include <values.h>
#include "../headers/pythagorean.h"


int main() {
    int a, b, c;

    printf(
        "╭---------------------------- BEGIN OF USAGE ----------------------------╮\n"
        "| Program checks whether three numbers satisfy Pythagorean triple        |\n"
        "| requirement or not and if yes whether are primitive Pythagorean triple.|\n"
        "╰---------------------------- END OF USAGE ------------------------------╯\n\n"
    );

    printf("Please, input three numbers separated by spaces:\n");

    while (1)
    {
        char *s;
        size_t sz = 0;
        int gl_res = (int) getline(&s, &sz, stdin);
        int sc_res = sscanf(s, "%d %d %d", &a, &b, &c);

        if (gl_res == -1)
            printf("Can't read a line: check that your input stream is correct. Try again:\n");
        else if (sc_res != 3)
            printf("Can't read three numbers: numbers must be separated by spaces. Try again:\n");
        else if (!(1 <= a && a <= INT_MAX))
            printf("First number is incorrect: number must be positive integer. Try again:\n");
        else if (!(1 <= b && b <= INT_MAX))
            printf("Second number is incorrect: number must be positive integer. Try again:\n");
        else if (!(1 <= c && c <= INT_MAX))
            printf("Third number is incorrect: number must be positive integer. Try again:\n");
        else
            break;
    }

    int are_pyth = are_pythagorean_triple(a, b, c);
    int are_rel_prime = are_relative_prime(a, b, c);

    printf("Numbers are %sPythagorean triple.\n",
           are_pyth ? (are_rel_prime ? "primitive " : "") : ("not "));

    return 0;
}