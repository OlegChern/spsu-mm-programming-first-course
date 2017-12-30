#pragma once

// example of using memory mapping on windows:
// https://eax.me/winapi-file-mapping/

#include			<io.h>			// _open()
#include			<fcntl.h>		// control options for _open()
#include			<time.h>

#include			<Windows.h>

#define TRUE        1
#define CHUNK		4
#define LARGECHUNK	128

typedef struct 
{
	HANDLE			hFile;
	HANDLE			hMapping;
	size_t			size;
	char			*dataPtr;
} FILEMAPPING;

typedef struct stat	STAT;

int					sortWithMemoryMapping(const char*);
int					compareStrings(const void*, const void*);
FILEMAPPING			*mmap(const char*, DWORD);
void				unmap(FILEMAPPING*);
char				*getString();