#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Reverses a string */
void str_rev(char *s)
{
    char *l, *r;

    if (s == NULL)
        return;

    l = s;
    for (r = s; *r != '\0'; r++)
        ;
    r--;

    while (l < r)
    {
        char tmp = *l;
        *l = *r;
        *r = tmp;

        l++;
        r--;
    }
}

/* Read line in specified format. If it finds mistake prints error message and asks to repeat input*/
char* read_line(char *invite, char *input_format, int (*check)(char *s), FILE *stream)
{
    char *buf = NULL;
    size_t buf_sz = 0;
    ssize_t len = 0;

    if (invite != NULL)
        printf("%s\n", invite);

    int flag = 1;
    do {
        if (len < 0)
            printf("Can't read line. Try to reload program or repeat input.\n");
        if (!flag)
        {
            if (input_format == NULL)
                printf("Wrong input. Try again:\n");
            else
                printf("Wrong input. requires format: %s. Try again:\n", input_format);
        }

        len = getline(&buf, &buf_sz, stream);
        if (len > 0 && buf[len - 1] == '\n')
            buf[len - 1] = '\0';

    } while (len == -1 || !(flag = check(buf)));

    return buf;
}

/* Checks that string is a continuous sequence of english characters */
int check_word(char *s)
{
    size_t len;
    if (s == NULL || (len = strlen(s)) == 0)
        return 0;

    int flag = 1;
    for (int i = 0; i < len; i++)
    {
        if (!isalpha(s[i]))
        {
            if (isblank(s[i]))
                printf("Incorrect character: <blank>.\n");
            else
                printf("Incorrect character: %c.\n", s[i]);
            flag = 0;
            break;
        }
    }

    return flag;
}