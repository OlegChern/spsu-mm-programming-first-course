//
// Created by rinsler on 25.10.17.
//

#ifndef TEST_1_STRUCTURES_STR_FUNCS_H
#define TEST_1_STRUCTURES_STR_FUNCS_H

int starts_with(char *s1, char *s2);
int parse_int(char *s, int *error);
int getline(char **line, size_t *n, FILE *stream);
int split(const char *s, char ***result, size_t *result_len, char delim, int doFilter);

#endif //TEST_1_STRUCTURES_STR_FUNCS_H
