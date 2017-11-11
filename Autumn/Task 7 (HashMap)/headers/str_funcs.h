//
// Created by rinsler on 25.10.17.
//

#ifndef TEST_1_STRUCTURES_STR_FUNCS_H
#define TEST_1_STRUCTURES_STR_FUNCS_H

extern const int EMPTY;
extern const int TOO_BIG;
extern const int NAN;


int parse_int(char *s, int *error);
int getline(char **line, size_t *n, FILE *stream);
int split(const char *s, char ***result, size_t *result_len, char delim, int do_filter);
int is_consisted_of_letters(const char *s);

#endif //TEST_1_STRUCTURES_STR_FUNCS_H
