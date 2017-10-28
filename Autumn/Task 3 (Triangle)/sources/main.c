#include <stdio.h>
#include <math.h>
#include <values.h>

#include "../headers/triangle.h"


int main() {
    double a, b, c;

    printf(
            "╭---------------------------- BEGIN OF USAGE ----------------------------╮\n"
            "| Program checks whether three numbers satisfy Triangle requirement or   |\n"
            "| not and if yes prints his angles with precision to seconds.            |\n"
            "╰---------------------------- END OF USAGE ------------------------------╯\n\n"
    );

    printf("Please, input three numbers separated by spaces:\n");

    while (1)
    {
        char *s;
        size_t sz = 0;
        int gl_res = (int) getline(&s, &sz, stdin);
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
        double angle;
        double tmp;

        printf("Numbers satisfy Triangle inequality, his angles are:\n");

        angle = get_angle_in_degrees(a, b, c);
        printf(
                "First angle: %d degrees %d minutes %d seconds\n",
                (int) angle,
                (int) (tmp = (angle - (int) angle) * 60),
                (int) ((tmp - (int) tmp) * 60)
        );

        angle = get_angle_in_degrees(a, c, b);
        printf(
                "Second angle: %d degrees %d minutes %d seconds\n",
                (int) angle,
                (int) (tmp = (angle - (int) angle) * 60),
                (int) ((tmp - (int) tmp) * 60)
        );

        angle = get_angle_in_degrees(b, c, a);
        printf(
                "Third angle: %d degrees %d minutes %d seconds\n",
                (int) angle,
                (int) (tmp = (angle - (int) angle) * 60),
                (int) ((tmp - (int) tmp) * 60)
        );
    } else
        printf("Numbers don't satisfy Triangle inequality\n");

    return 0;
}