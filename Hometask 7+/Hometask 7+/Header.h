#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

#define INITIAL_CAPACITY 16
#define MAX_CAPACITY 0x1000
#define RECALC 1.5

typedef struct _NODE
{
	char *key;
	void *value;
	struct _NODE *next;
} NODE;

typedef struct _HASHTABLE
{
	int size;
	int capacity;
	NODE **table;
} HASHTABLE;

HASHTABLE *create();
void *get(HASHTABLE *, char *);
void put(HASHTABLE *, char *, void *);
void delete(HASHTABLE *, char *);

#endif // __HASHTABLE_H__

