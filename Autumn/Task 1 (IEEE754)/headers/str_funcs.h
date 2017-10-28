#ifndef TEST_STRFUNCS_H
#define TEST_STRFUNCS_H

#include <stdio.h>

void str_rev(char *s);
char* read_line(char *invite, char *input_format, int (*check)(char *s), FILE *stream);
int check_word(char *s);

#endif //TEST_STRFUNCS_H
