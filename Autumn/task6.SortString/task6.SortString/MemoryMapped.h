#include "windows.h"

typedef struct {
	HANDLE hFile;
	HANDLE hMapping;
	size_t fsize;
	unsigned char* dataPtr;
}FileMapping;

FileMapping *createFileMaping(char *nameOfFile);

void closeMapping(FileMapping *mapping);
