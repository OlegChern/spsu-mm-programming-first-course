#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <inttypes.h>

#define BIG_ENDIAN 1
#define LITTLE_ENDIAN 2

#define BITMAP_FILE_HEADER_SIZE 14

#define LUMINANCE_RED 0.2126
#define LUMINANCE_GREEN 0.7152
#define LUMINANCE_BLUE 0.0722

#define FILTER_ASSERT(condition, message) if (!(condition)) {printf(message); free(previous); free(current); free(next); if (gap != 0) free(gapBuffer); return 1;}

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
void printArguments(char*, char *, char*);

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

/// Returns 0 on success, non-zero value otherwise
// TODO: test with other pixel size
// Image is considered to be 2 pixels wider and 2 pixels higher than it actually is,
// forming black outline out of those extra pixels,
// so that gauss filter can be applied.
int applyFilter(uint16_t, int32_t, int32_t, const double[3][3], FILE*, FILE*);

int applyGreyen(uint16_t, int32_t, int32_t, FILE*, FILE*, int);

#endif /* UTIL_H */

