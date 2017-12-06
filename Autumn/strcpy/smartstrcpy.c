#include <string.h>

#include "smartstrcpy.h"

char *dumbstrcpy(char *dst, const char *src)
{
    int index = 0;
    do
    {
        dst[index] = src[index];
        index++;
    } while (src[index - 1] != '\0');
    return dst;
}

/**
 * Following optimisations
 * are currently present in the main loop:
 * - manually unrolled loop
 * - managing data as integer type
 *   (since byte handling speed
 *    is typically not faster than
 *    the one of handling integers)
 */
char *smartstrcpy(char *dst, const char *src)
{
    // This value has to be saved
    // so that to be returned later on
    char *initial_dst = dst;

    // "+ 1" here ensures '\0' is copied as well.
    int len = strlen(src) + 1;
    int len_32 = len / 32;
    int len_not_32 = len % 32;

    // Yet another loop unrolling
    // could have been implemented here,
    // but it is hardly worth it

    // Copy items that can't be handled
    // by the main loop due to data shape mismatch
    for (int i = 0; i < len_not_32; i++)
        *(dst++) = *(src++);

    int *int_dst = (int *) dst;
    int *int_src = (int *) src;

    // The main loop:
    for (int i = 0; i < len_32; i++)
    {
        *(int_dst++) = *(int_src++);
        *(int_dst++) = *(int_src++);
        *(int_dst++) = *(int_src++);
        *(int_dst++) = *(int_src++);

        *(int_dst++) = *(int_src++);
        *(int_dst++) = *(int_src++);
        *(int_dst++) = *(int_src++);
        *(int_dst++) = *(int_src++);
    }
    return initial_dst;
}

char *smartstrcpy2(char *dst, const char *src)
{
    char *initial_dst = dst;
    int len = strlen(src) + 1;
    int len_4 = len / 4;
    int len_not_4 = len % 4;

    for (int i = 0; i < len_not_4; i++)
        *(dst++) = *(src++);

    int *int_dst = (int *) dst;
    int *int_src = (int *) src;

    for (int i = 0; i < len_4; i++)
    {
        *(int_dst++) = *(int_src++);
    }
    return initial_dst;
}

char *strclear(char *str)
{
    int index = 0;
    while (str[index] != '\0')
    {
        str[index] = 0;
        index++;
    }
    return str;
}
