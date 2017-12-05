#include <string.h>

#include "smartstrcpy.h"

char *dumbstrcpy(char *dst, const char *src)
{
    int index = 0;
    do
    {
        dst[index] = src[index];
        index++;
    } while (src[index] != '\0');
    return dst;
}

char *smartstrcpy(char *dst, const char *src)
{
    char *initial_dst = dst;
    int len = strlen(src);
    int len_32 = len / 32;
    int len_not_32 = len % 32;

    // Ensures '\0' is copied.
    *(dst++) = *(src++);

    // Copy items that can't be handled
    // by the main loop due to data shape mismatch
    for (int i = 0; i < len_not_32; i++)
    {
        *(dst++) = *(src++);
    }

    int *src_current = (int*) src;
    int *dst_current = (int*) dst;

    // Following optimisations are currently present:
    // - manually unrolled loop
    // - managing data as integer type
    //   (since byte handling speed
    //    is typically not faster than
    //    the one of handling integers)
    for (int i = 0; i < len_32; i++)
    {
        *(dst++) = *(src++);
        *(dst++) = *(src++);
        *(dst++) = *(src++);
        *(dst++) = *(src++);

        *(dst++) = *(src++);
        *(dst++) = *(src++);
        *(dst++) = *(src++);
        *(dst++) = *(src++);
    }
    return initial_dst;
}
