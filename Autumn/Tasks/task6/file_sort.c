#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

#include <sys/stat.h>
#include <fcntl.h>
#include <zconf.h>

#include "prog_work_time.h"

char *input, *output;

typedef struct LineList
{
    unsigned long int begin;
    unsigned long int end;
    struct LineList *next;
} LineList;

typedef struct Line
{
    unsigned long int begin;
    unsigned long int end;
} Line;

typedef struct CharList
{
    char c;
    struct CharList *next;
} CharList;

int cmp(const void *a, const void *b)
{
    unsigned long int i = ((Line *) a)->begin;
    unsigned long int a_end = ((Line *) a)->end;

    unsigned long int j = ((Line *) b)->begin;
    unsigned long int b_end = ((Line *) b)->end;

    for (; i < a_end && j < b_end && (input[i] == input[j]); ++i, ++j);

    if (input[i] > input[j]) return 1;
    if (input[i] < input[j]) return -1;

    return 0;
}

char *scan_line()
{
    char *s;
    CharList *list = (CharList *) malloc(sizeof(CharList));
    CharList *temp_list = list;

    int n = 0;
    while ((temp_list->c = getchar()) != '\n')
    {
        temp_list->next = (CharList *) malloc(sizeof(CharList));
        temp_list = temp_list->next;
        ++n;
    }
    temp_list->c = '\0';
    ++n;

    s = (char *) malloc(sizeof(char) * n);
    for (int i = 0; i < n; ++i)
    {
        temp_list = list->next;
        s[i] = list->c;
        free(list);
        list = temp_list;
    }

    return s;
}


int main()
{
    time_start();
    //----------------------

    printf("Enter input full path:\n");
    const char *input_path = scan_line();

    printf("Enter output full path:\n");
    const char *output_path = scan_line();


    unsigned long int file_size = 0;

    int fdin, fdout;
    struct stat statbuf;

    // Open
    if ((fdin = open(input_path, O_RDONLY)) < 0)
    {
        printf("READ ERROR: \"%s\"\n", input_path);
    }
    if ((fdout = open(output_path, O_TRUNC | O_RDWR)) < 0)
    {
        printf("READ ERROR: \"%s\"\n", output_path);
    }

    // Input file
    if (fstat(fdin, &statbuf) < 0) printf("ERROR : fstat\n");
    else file_size = (unsigned long) (statbuf.st_size);
    printf("Input size : %lu B ~ %lu KB ~ %lu MB\n",
           file_size,
           file_size / 1024,
           file_size / 1024 / 1024);

    if ((input = mmap(0, file_size, PROT_READ, MAP_SHARED, fdin, 0)) == MAP_FAILED)
    {
        printf("ERROR : mmap : input file\n");
    }

    // Output file
    if (lseek(fdout, file_size - 1, SEEK_SET) == -1) printf("ERROR : lseek : output file\n");
    if (write(fdout, "", 1) != 1) printf("ERROR : write : output file\n");

    if ((output = mmap(0, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, fdout, 0)) == MAP_FAILED)
    {
        printf("ERROR : mmap : output file\n");
    }


    // READING
    LineList *list = (LineList *) malloc(sizeof(LineList));
    LineList *temp_list = list;

    unsigned long int N = 0;

    for (unsigned long int pos = 0, next_pos = 0; pos < file_size; pos = next_pos + 1, next_pos = pos)
    {
        while (next_pos < file_size && input[next_pos] != '\n') ++next_pos;

        // push
        temp_list->begin = pos;
        temp_list->end = next_pos;
        temp_list->next = (LineList *) malloc(sizeof(LineList));

        temp_list = temp_list->next;
        ++N;
    }


    // SORTING
    Line *lines = (Line *) malloc(sizeof(Line) * N);

    for (int i = 0; i < N; ++i)
    {
        temp_list = list->next;

        lines[i].begin = list->begin;
        lines[i].end = list->end;

        free(list);
        list = temp_list;
    }

    qsort(lines, N, sizeof(Line), (int (*)(const void *, const void *)) cmp);


    // WRITING
    unsigned long int cnt = 0;

    unsigned long int begin;
    unsigned long int end;
    for (unsigned long int i = 0; i < N; ++i)
    {
        begin = lines[i].begin;
        end = lines[i].end;
        for (unsigned long int j = begin; j < end; ++j)
        {
            output[cnt] = input[j];
            ++cnt;
        }

        output[cnt] = '\n';
        ++cnt;
    }



    //----------------------
    long time = time_stop();
    printf("Done : %lims ~ %lis\n", time, (time + time / 200) / 1000);

    return 0;
}
