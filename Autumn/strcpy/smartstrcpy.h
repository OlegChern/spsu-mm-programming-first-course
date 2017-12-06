#ifndef SMARTSTRCPY_H
#define SMARTSTRCPY_H

/// Simply copy the string, byte-by-byte
char *dumbstrcpy(char *dst, const char *src);

/// Attemp to implement optimizations
char *smartstrcpy(char *dst, const char *src);

char *smartstrcpy2(char *dst, const char *src);

char *strclear(char *str);

#endif // SMARTSTRCPY_H