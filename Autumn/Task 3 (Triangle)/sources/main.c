#include <stdio.h>

#include "../headers/triangle.h"
#include "../headers/str_funcs.h"


int main() {
    double a, b, c;

    printf(
            "#---------------------------- BEGIN OF USAGE ----------------------------#\n"
            "| Program checks whether three numbers satisfy Triangle requirement or   |\n"
            "| not and if yes prints his angles with precision to seconds.            |\n"
            "#---------------------------- END OF USAGE ------------------------------#\n\n"
    );

    printf("Please, input three numbers separated by spaces:\n");

    while (1)
    {
        char *s = NULL;
        size_t sz = 0;
        int gl_res = getline(&s, &sz, stdin);
        int sc_res = sscanf(s, "%lf %lf %lf", &a, &b, &c);

        if (gl_res == -1)
            printf("Can't read a line: check that your input stream is correct. Try again:\n");
        else if (sc_res != 3)
            printf("Can't read three numbers: numbers must be separated by spaces. Try again:\n");
        else if (a < 0)
            printf("First number is incorrect: number must be positive. Try again:\n");
        else if (b < 0)
            printf("Second number is incorrect: number must be positive. Try again:\n");
        else if (c < 0)
            printf("Third number is incorrect: number must be positive. Try again:\n");
        else
            break;
    }

    if (is_triangle(a, b, c))
    {
        int degrees;
        int minutes;
        int seconds;

        printf("Numbers satisfy Triangle inequality, his angles are:\n");

        get_angle(a, b, c, &degrees, &minutes, &seconds);
        printf("    1.) %d degrees %d minutes %d seconds.\n", degrees, minutes, seconds);

        get_angle(a, c, b, &degrees, &minutes, &seconds);
        printf("    2.) %d degrees %d minutes %d seconds.\n", degrees, minutes, seconds);

        get_angle(b, c, a, &degrees, &minutes, &seconds);
        printf("    3.) %d degrees %d minutes %d seconds.\n", degrees, minutes, seconds);;
    } else
        printf("Numbers don't satisfy Triangle inequality.\n");

    return 0;
}