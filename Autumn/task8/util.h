#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <inttypes.h>

#define BIG_ENDIAN 1
#define LITTLE_ENDIAN 2

#define BITMAP_FILE_HEADER_SIZE 14

const char *gauss;
const char *sobelx;
const char *sobely;
const char *greyen;

/// Returns whether user approves requested action or not.
int confirm(char*);

int exists(const char*, const char*);

/// Returns 0 on success, non-zero value otherwise
/// type[0] is supposed be '-'.
int choose(const char*, char*, char**, char**, char**);

/// Returns 0 on success, non-zero value otherwise
int handleArguments(int, char**, char**, char**, char**);

/// Returns 0 on success, non-zero value otherwise
int handleBitmapFileHeader(FILE*, uint16_t*, uint32_t*, uint16_t*, uint16_t*, uint32_t*, int*);

/// Returns 0 on success, non-zero value otherwise
int handleBitmapInfoHeader(FILE*, uint32_t*, int32_t*, int32_t*, uint16_t*, uint16_t*);

/// Returns 0 on success, non-zero value otherwise
int checkSizes(uint32_t, uint32_t, uint32_t, int32_t, int32_t, uint16_t);

/// Returns 0 on success, non-zero value otherwise
int copyHeader(FILE*, FILE*, uint32_t);

#endif /* UTIL_H */

