//
// Created by rinsl_000 on 24.11.2017.
//

#include <stdio.h>
#include <stdlib.h>
#include "../headers/errors.h"


/* Stops program because of error and returns error code */
void die(int code)
{
    printf("Program execution has been failed.\n");
    exit(code);
}