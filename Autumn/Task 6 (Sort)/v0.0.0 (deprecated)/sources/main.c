#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>

#include "../headers/qsort.h"

/*
 * Generates file that consists of random strings.
 * n - strings count.
 * low - min length of each string.
 * hi - max length of each string.
 */
void genstr(const char *filename, int n, int low, int hi)
{
    FILE *f = fopen(filename, "w+");

    srand((unsigned int) time(NULL));
    for (int i = 0; i < n; ++i)
    {
        int len = low + rand() % (hi - low + 1);

        for (int j = 0; j < len; ++j)
            fputc(97 + rand() % (122 - 97 + 1), f);
        fputc('\n', f);
    }

    fclose(f);
}


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
                "╭---------------------------- BEGIN OF USAGE ----------------------------╮\n"
                "| Program sorts file consisting of strings separated by '\\n'             |\n"
                "| It can use two types of sorting:                                       |\n"
                "|  * quicksort by using mapped files - fast variant but requires         |\n"
                "|    big part of RAM. It may not work on files with enormous amount      |\n"
                "|    of strings (depends on RAM size but around billion or more).        |\n"
                "|  * quicksort by using temp files - slow variant but needs very small   |\n"
                "|    amount of RAM and doesn't depend on its size.                       |\n"
                "|    Must always work correctly.                                         |\n"
                "| Params:                                                                |\n"
                "|  * --gen-test cnt low hi <filename>                                    |\n"
                "|    For developers only. It creates file that consists of random        |\n"
                "|    strings for testing. Requires three number after it (strings count, |\n"
                "|    min length of generated string, max length of generated string)     |\n"
                "|    and filename after it.                                              |\n"
                "|  * --qsort <filename>                                                  |\n"
                "|    Sorts file by using mapped files.                                   |\n"
                "|  * --qsort-without-ram <filename>                                      |\n"
                "|    Sorts file by using temp files.                                     |\n"
                "╰---------------------------- END OF USAGE ------------------------------╯\n"
        );
        return 0;
    }
    else if (strcmp(argv[1], "--gen-test") == 0)
    {
        if (argc != 6)
        {
            printf("Error: incorrect amount of params: see usage by --help\n");
            return 1;
        }
        else
        {
            int cnt = (int) strtol(argv[2], NULL, 10);
            int low = (int) strtol(argv[3], NULL, 10);
            int hi  = (int) strtol(argv[4], NULL, 10);

            if (cnt <= 0 || low < 0 || hi <= 0 || low >= hi)
            {
                printf("Error: incorrect params: see usage by --help\n");
                return 1;
            }

            time(&beg);
            genstr(argv[5], cnt, low, hi);
        }
    }
    else if (strcmp(argv[1], "--qsort") == 0)
    {
        time(&beg);
        quicksort(argv[2]);
    }
    else if (strcmp(argv[1], "--qsort-without-ram") == 0)
    {
        time(&beg);
        quicksort_without_ram(argv[2]);
    }
    else
    {
        printf("Error: action type is specified incorrectly: see usage by --help\n");
        return 1;
    }

    time_t end;
    time(&end);

    printf("Program has been working %li seconds\n", end - beg);

    return 0;
}