#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <zconf.h>
#include <time.h>

#include "../headers/filefuncs.h"

/* Checks whether string has been finished by searching '\n' in buffer */
static int has_finished(const char *buf, int sz)
{
    for (int i = 0; i < sz; ++i)
        if (buf[i] == '\n')
            return 1;

    return 0;
}

/*
 * Compares two strings by pointers on their beginnings in mapped file.
 * Uses buffers to speed up the process and save up memory.
 */
int strcomparator(const void *a, const void *b)
{
    char *p1 = *(char **) a;
    char *p2 = *(char **) b;

    const int BUF_SZ = 4;

    char buf1[BUF_SZ + 1];
    char buf2[BUF_SZ + 1];

    int s1_finished = 0;
    int s2_finished = 0;

    while (!s1_finished && !s2_finished)
    {
        memcpy(buf1, p1, BUF_SZ);
        buf1[BUF_SZ] = 0;
        p1 += BUF_SZ;
        s1_finished = has_finished(buf1, BUF_SZ);

        memcpy(buf2, p2, BUF_SZ);
        buf2[BUF_SZ] = 0;
        p2 += BUF_SZ;
        s2_finished = has_finished(buf2, BUF_SZ);

        int cmp = strcmp(buf1, buf2);
        if (cmp != 0)
            return cmp;
    }

    return s1_finished && s2_finished ? 0 : s1_finished ? -1 : 1;
}

/* Sorts file by using mapped files */
void quicksort(const char *filename)
{
    int f_des = open(filename, O_RDWR);

    struct stat statbuf;
    fstat(f_des, &statbuf);

    char *f;
    if ((f = mmap(0, (size_t) statbuf.st_size + 1, PROT_READ | PROT_WRITE, MAP_SHARED, f_des, 0)) == MAP_FAILED)
        exit(1);

    long n = 0;
    for (long i = 0; i < statbuf.st_size; ++i)
        if (f[i] == '\n')
            n++;

    if (f[statbuf.st_size - 1] != '\n')
    {
        ftruncate(f_des, statbuf.st_size + 1);
        f[statbuf.st_size++] = '\n';
        n++;
    }

    char **a = malloc(sizeof(char *) * n);
    if (a == NULL)
        exit(1);

    long c = 0;
    for (long i = 0; i < n; ++i)
    {
        a[i] = f + c;

        while (f[c] != '\n')
            c++;
        c++;
    }

    qsort(a, (size_t) n, sizeof(char *), strcomparator);

    remove("tmp");
    int tmp_des = open("tmp", O_RDWR | O_CREAT | O_TRUNC);
    char *tmp = mmap(0, (size_t) statbuf.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, tmp_des, 0);
    ftruncate(tmp_des, statbuf.st_size);

    c = 0;
    for (long i = 0; i < n; ++i)
    {
        for (char *j = a[i]; *j != '\n'; j++)
            tmp[c++] = *j;

        tmp[c++] = '\n';
    }

    free(a);

    memcpy(f, tmp, (size_t) statbuf.st_size);

    close(f_des);
    close(tmp_des);
    remove("tmp");
}


/* -------------------------- another realisation ---------------------------------*/


FILE *f;

/*
 * Compares two strings by pointers on their beginnings in files.
 * Uses buffers to speed up the process and save up memory.
 */
int compare_in_file(const fpos_t *a, const fpos_t *b)
{
    fpos_t p1 = *a;
    fpos_t p2 = *b;

    const int BUF_SZ = 4;

    char buf1[BUF_SZ + 1];
    char buf2[BUF_SZ + 1];

    int s1_finished = 0;
    int s2_finished = 0;

    while (!s1_finished && !s2_finished)
    {
        fsetpos(f, &p1);
        fread(buf1, 1, BUF_SZ, f);
        buf1[BUF_SZ] = 0;
        s1_finished = has_finished(buf1, BUF_SZ);
        fgetpos(f, &p1);

        fsetpos(f, &p2);
        fread(buf2, 1, BUF_SZ, f);
        buf2[BUF_SZ] = 0;
        s2_finished = has_finished(buf2, BUF_SZ);
        fgetpos(f, &p2);

        int cmp = strcmp(buf1, buf2);
        if (cmp != 0)
            return cmp;
    }

    return s1_finished && s2_finished ? 0 : s1_finished ? -1 : 1;
}

void quicksort_rec(long l, long r);

/* Shell of sorting func. Prepares file and launches recursive sorting func */
void quicksort_without_ram(const char *filename)
{
    f = fopen(filename, "r+");

    add_last_newline(f);
    long n = count_lines(f);

    srand((unsigned int) time(NULL));
    quicksort_rec(0, n);

    fclose(f);
}

/* Copies string by her file pos ptr to the file. */
void copy_str_from_pos(fpos_t *p, FILE *t)
{
    fsetpos(f, p);
    for (int c; (c = fgetc(f)) != '\n'; )
        fputc(c, t);

    fputc('\n', t);
}

/* Recursive func of sorting file almost without RAM using */
void quicksort_rec(long l, long r)
{
    if (r - l <= 1)
        return;

    fpos_t f_in_beg_pos;
    fgetpos(f, &f_in_beg_pos);

    long x_pos = rand() % (r - l);

    for (long i = 0; i < x_pos; )
        if (fgetc(f) == '\n')
            i++;

    fpos_t pivot_pos;
    fgetpos(f, &pivot_pos);

    fsetpos(f, &f_in_beg_pos);

    FILE *f_l = tmpfile();
    FILE *f_e = tmpfile();
    FILE *f_r = tmpfile();

    long f_l_lines_cnt = 0;
    long f_e_lines_cnt = 0;

    for (long i = 0; i < r - l; ++i)
    {
        fpos_t cur_pos;
        fgetpos(f, &cur_pos);

        int cmp = compare_in_file(&cur_pos, &pivot_pos);
        if (cmp < 0)
        {
            copy_str_from_pos(&cur_pos, f_l);
            f_l_lines_cnt++;
        }
        else if (cmp == 0)
        {
            copy_str_from_pos(&cur_pos, f_e);
            f_e_lines_cnt++;
        }
        else
        {
            copy_str_from_pos(&cur_pos, f_r);
        }
    }

    fsetpos(f, &f_in_beg_pos);

    rewind(f_l);
    rewind(f_e);
    rewind(f_r);

    filecpy(f, f_l);
    filecpy(f, f_e);

    fpos_t f_in_before_r_pos;
    fgetpos(f, &f_in_before_r_pos);

    filecpy(f, f_r);

    fclose(f_l);
    fclose(f_e);
    fclose(f_r);

    fsetpos(f, &f_in_beg_pos);
    quicksort_rec(l, l + f_l_lines_cnt);
    fsetpos(f, &f_in_before_r_pos);
    quicksort_rec(l + f_l_lines_cnt + f_e_lines_cnt, r);
}