#ifndef TASK_10_SORT_FILEFUNCS_H
#define TASK_10_SORT_FILEFUNCS_H

#include <stdio.h>

void filecpy(FILE *dest, FILE *src);
long count_lines(FILE *f);
void add_last_newline(FILE *f);

#endif //TASK_10_SORT_FILEFUNCS_H
