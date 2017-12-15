#pragma once

#include <stdlib.h>
#include <string.h>

#define DEFAULTTABLESIZE 4	// default number of chains in table
#define MAXCHAINSIZE 4		// max number elements in chain

typedef struct
{
	char*				key;
	int					value;
} HashTableElement;

typedef struct
{
	HashTableElement	**elements; // array of pointers to elements
	int					elementCount; // count of elements in chain
} HashTableChain;

typedef struct
{
	HashTableChain		**chains; // array of pointers to chains
	int					chainCount; // count of chains
} HashTable;

// add new key and value
void					addKey(HashTable*, char*, int);

// find pointer to value with given key, returns 0 if key wasn't found
int						findValue(int*, HashTable*, char*);

// remove key and value
void					removeKey(HashTable*, char*);

void					printTable(HashTable*);

// hash key, just using sum of char indices mod size
int						hash(HashTable*, char*);

// create new hash table
HashTable				*newHashTable();

HashTableChain			*addEmptyChain(HashTable*);

// find address of element with given hashKey, returns NULL if key wasn't found
HashTableElement		*findElementInChain(HashTableChain*, char*);

int						findElementIndexInChain(HashTableChain*, char*);

// rebalance table, just recalculating hashKeys
void					rebalance(HashTable*);
