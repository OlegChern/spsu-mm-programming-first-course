#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>


/* Compares two strings by pointers on their beginnings right in mapped memory */
int str_comparator(const void *a, const void *b)
{
    char *p1 = *(char**) a;
    char *p2 = *(char**) b;

    for (; *p1 != '\n' && *p2 != '\n'; p1++, p2++)
    {
        if (*p1 - *p2)
            return *p1 - *p2;
    }

    return (*p1 == '\n' && *p2 != '\n') ? -1 : (*p1 != '\n' && *p2 == '\n') ? 1 : 0;
}

/* Sorts file by using mapped files */
void quick_sort(const char *file_name)
{
    int f_des = open(file_name, O_RDWR);
    int err = errno;
    if (err) {
        printf("Error: %s\n", strerror(err));
        exit(1);
    }

    struct stat stat_buf;
    fstat(f_des, &stat_buf);

    char *f;
    if ((f = mmap(0, (size_t) stat_buf.st_size + 1, PROT_READ | PROT_WRITE, MAP_SHARED, f_des, 0)) == MAP_FAILED)
        exit(1);

    long n = 0;
    for (long i = 0; i < stat_buf.st_size; ++i)
        if (f[i] == '\n')
            n++;

    if (f[stat_buf.st_size - 1] != '\n')
    {
        ftruncate(f_des, stat_buf.st_size + 1);
        f[stat_buf.st_size++] = '\n';
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

    qsort(a, (size_t) n, sizeof(char *), str_comparator);

    remove("tmp");
    int tmp_des = open("tmp", O_RDWR | O_CREAT | O_TRUNC);
    char *tmp = mmap(0, (size_t) stat_buf.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, tmp_des, 0);
    ftruncate(tmp_des, stat_buf.st_size);

    c = 0;
    for (long i = 0; i < n; ++i)
    {
        for (char *j = a[i]; *j != '\n'; j++, c++)
            tmp[c] = *j;

        tmp[c++] = '\n';
    }

    free(a);

    memcpy(f, tmp, (size_t) stat_buf.st_size);

    close(f_des);
    close(tmp_des);
    remove("tmp");
}