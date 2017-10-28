#ifndef TEST_BITFUNCS_H
#define TEST_BITFUNCS_H

enum ARCH
{
    $32ARCH, $64ARCH
};

enum PRECISION
{
    SINGLE, DOUBLE
};

char* get_bin_repr_of_int(int n, enum ARCH ARCH_TYPE);
char* get_bin_repr_of_ieee754(double n, enum PRECISION PRECISION);

#endif //TEST_BITFUNCS_H
