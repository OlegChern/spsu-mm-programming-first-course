#pragma once

#define TRUE			1
#define FALSE			0
#define MAXLISTCOUNT	16
#define MAXCHUNKCOUNT	16

typedef unsigned char INDICES;

typedef struct
{
	char		isFree;
	INDICES		listIndex;
} CHUNK;

typedef struct
{
	CHUNK**		chunks;
	size_t		size;
} CHUNKLIST;

typedef struct
{
	CHUNKLIST**	lists;
	size_t		availableSize;
} MEMORY;

typedef struct
{
	float		position[3];
	float		rotation[4];
} TRANSFORM;								// struct for example

void			intExample();
void			structExample();

void*			myMalloc(size_t);
void			myFree(void*);
void*			myRealloc(void*, size_t);

void			init();						// initialize 
void			close();					// free all allocated memory
CHUNK*			findFreeChunk(CHUNKLIST*);

MEMORY			memory;