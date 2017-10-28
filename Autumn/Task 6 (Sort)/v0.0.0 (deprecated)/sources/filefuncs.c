#include <stdio.h>


void filecpy(FILE *dest, FILE *src)
{
    const int BUF_SIZE = 1024;
    char buf[BUF_SIZE];

    size_t n;
    while ((n = fread(buf, 1, BUF_SIZE, src)) != 0)
        fwrite(buf, 1, n, dest);
}

long count_lines(FILE *f)
{
    fpos_t state;
    fgetpos(f, &state);

    rewind(f);

    long r = 0;
    int c;

    do
    {
        if ((c = fgetc(f)) == '\n')
            r++;
    } while (c != EOF);

    fsetpos(f, &state);

    return r;
}

void add_last_newline(FILE *f)
{
    fpos_t pos;
    fgetpos(f, &pos);

    fseek(f, -1, SEEK_END);
    int c = fgetc(f);
    if (c != '\n')
        fputc('\n', f);
    fflush(f);

    fsetpos(f, &pos);
}