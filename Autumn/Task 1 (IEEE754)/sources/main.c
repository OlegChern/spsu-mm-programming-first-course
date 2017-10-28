#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

#include "../headers/str_funcs.h"
#include "../headers/bit_funcs.h"


int main()
{
    char *name, *surname, *patronymic;
    char *tmp;

    printf(
            "╭---------------------------- BEGIN OF USAGE ----------------------------╮\n"
            "| That program takes your name, surname and patronymic then counts their |\n"
            "| production and presents it in three formats:                           |\n"
            "|   1.) Two's complement code of negative production.                    |\n"
            "|   2.) IEEE754 with single precision code of positive production.       |\n"
            "|   3.) IEEE754 with double precision code of negative production.       |\n"
            "╰---------------------------- END OF USAGE ------------------------------╯\n\n"
    );

    name = read_line("Please, enter your name:", "<continuous string of letters>", check_word, stdin);
    surname = read_line("Please, enter your surname:", "<continuous string of letters>", check_word, stdin);
    patronymic = read_line("PLease, enter your patronymic:", "<continuous string of letters>", check_word, stdin);

    int prod = (int) (strlen(name) * strlen(surname) * strlen(patronymic));

    printf("In two's complement code:         %s\n", tmp = get_bin_repr_of_int(-prod, $32ARCH));
    free(tmp);

    printf("In IEEE754 with single precision: %s\n", tmp = get_bin_repr_of_ieee754(prod, SINGLE));
    free(tmp);

    printf("In IEEE754 with double precision: %s\n", tmp = get_bin_repr_of_ieee754(-prod, DOUBLE));
    free(tmp);

    return 0;
}