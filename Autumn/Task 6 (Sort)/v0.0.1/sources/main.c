#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "../headers/qsort.h"


int main(int argc, char* argv[])
{
    time_t beg;

    if (argc < 2)
    {
        printf("Error: not specified what to do: see usage by --help\n");
        return 1;
    }
    else if (strcmp(argv[1], "--help") == 0)
    {
        printf(
                "#---------------------------- BEGIN OF USAGE ----------------------------#\n"
                "| Program sorts file consisting of strings separated by '\\n'             |\n"
                "| Sorting description:                                                   |\n"
                "|  * quick_sort by using mapped files - fast variant but requires        |\n"
                "|    big part of RAM. It may not work on files with enormous amount      |\n"
                "|    of strings (depends on RAM size but around billion or more).        |\n"
                "| Params:                                                                |\n"
                "|  * <filename>                                                          |\n"
                "|    Sorts file.                                                         |\n"
                "|  * --help                                                              |\n"
                "|    Get usage.                                                          |\n"
                "| Usage example:                                                         |\n"
                "|  * sorter sample/file_with_strings.txt                                 |\n"
                "#---------------------------- END OF USAGE ------------------------------#\n"
        );
        return 0;
    }
    else
    {
        time(&beg);
        quick_sort(argv[1]);
    }

    time_t end;
    time(&end);

    printf("Program has been working %li seconds\n", end - beg);

    return 0;
}