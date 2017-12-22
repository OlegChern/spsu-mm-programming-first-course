#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "../headers/bit_funcs.h"
#include "../headers/str_funcs.h"

#define min(a,b) ({ __typeof__ (a) _a = (a); __typeof__ (b) _b = (b); _a < _b ? _a : _b; })


char* get_bin_repr_of_int(int n, enum ARCH ARCH_TYPE)
{
    size_t len = ARCH_TYPE == $32ARCH ? 32 : 64;

    char* buf = malloc(len + 1);
    memset(buf, '0', len);
    buf[len] = '\0';

    int sign = (n > 0) ? 1 : (n < 0 ? -1 : 0);
    n = abs(n);

    for (int i = (int) (len - 1); n > 0; i--, n /= 2)
        buf[i] = (char) (n % 2 ? '1' : '0');

    if (sign < 0)
    {
        /* Special case below: if the number is the lowest possible previous actions will
         * change the first sign digit into 1. And that's cool because we can just
         * leave that representation itself and it will be the right record of it. E.g:
         *          usual       one's_complement    two's_complement
         * -127   1111 1111         1000 0000           1000 0001
         * -128   ---------         ---------           1000 0000
         *
         * see https://en.wikipedia.org/wiki/Two%27s_complement#Converting_to_two.27s_complement_representation
         * for more info
         */
        if (buf[0] != '1')
        {
            buf[0] = '1';

            for (int i = 1; i < len; i++)
                buf[i] = (char) (buf[i] == '0' ? '1' : '0');

            int i;
            for (i = (int) (len - 1); buf[i] == '1'; i--)
                buf[i] = '0';
            buf[i] = '1';
        }
    }

    return buf;
}

char* get_bin_repr_of_ieee754(double n, enum PRECISION PRECISION)
{
    size_t len = PRECISION == SINGLE ? 32 : 64;

    char* buf = malloc(len + 1);
    memset(buf, '0', len);
    buf[len] = '\0';

    if (n == 0.0)
        return buf;

    /* counting of offset and non-shifted mantissa */

    char before_pt[len + 1];
    memset(before_pt, '0', len);
    before_pt[len] = '\0';
    char after_pt[len + 1];
    memset(after_pt, '0', len);
    after_pt[len] = '\0';

    int sign = (n > 0) ? 1 : (n < 0 ? -1 : 0);
    n = fabs(n);

    long long int_part = (long long) trunc(n);

    double fract_part = n - int_part;

    int before_shift = 0;
    for (int i = 0; int_part > 0; i++, int_part /= 2)
    {
        before_pt[i] = (char) (int_part % 2 ? '1' : '0');
        before_shift++;
    }
    before_pt[before_shift] = '\0';
    str_rev(before_pt);

    fract_part *= 2;
    for (int i = 0; i < len; i++)
    {
        after_pt[i] = (char) ((int) trunc(fract_part) % 2 ? '1' : '0');
        double lost;
        fract_part = modf(fract_part, &lost) * 2;
    }

    int after_shift = 0;
    while (after_pt[after_shift] == '0')
        after_shift++;

    int shift = (before_shift == 0 ? -(after_shift + 1) : before_shift - 1);
    int offset = shift + (PRECISION == SINGLE ? 127 : 1023);

    size_t offset_len = PRECISION == SINGLE ? 8 : 11;
    char offset_bin[offset_len];
    memset(offset_bin, '0', offset_len);
    for (int i = (int) (offset_len - 1); offset > 0; i--, offset /= 2)
        offset_bin[i] = (char) (offset % 2 ? '1' : '0');

    /* preparing of result */

    if (sign < 0)
        buf[0] = '1';

    strncpy(buf + 1, offset_bin, (size_t) offset_len);

    if (shift >= 0)
    {
        if (before_shift > 1)
            strncpy(buf + 1 + offset_len, before_pt + 1, min(shift, len - 1 - offset_len));

        if (len > 1 + offset_len + shift)
            strncpy(
                    buf + 1 + offset_len + shift,
                    after_pt,
                    (size_t) (len - (1 + offset_len + shift))
            );
    }
    else
    {
        shift = abs(shift);

        strncpy(
                buf + 1 + offset_len,
                after_pt + shift,
                (size_t) (min(len - 1 - offset_len, len - shift))
        );
    }

    return buf;
}


